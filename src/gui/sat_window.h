#pragma once

#include "base/sat_base.h"
#include "gui/sat_gui_base.h"
#include "gui/sat_painter.h"
#include "gui/sat_renderer.h"
#include "gui/sat_window_buffer.h"

//----------

#if defined SAT_WINDOW_X11
    #include "gui/system/x11/sat_x11_window.h"
    typedef SAT_X11Window SAT_ImplementedWindow;
#elif defined SAT_WINDOW_WIN32
    #error NOT IMPLEMENTED YET
#elif defined SAT_WINDOW_WAYLAND
    #error NOT IMPLEMENTED YET
#elif defined SAT_WINDOW_COCOA
    #error NOT IMPLEMENTED YET
#else
    #error NO WINDOW_DEFINED
#endif

typedef SAT_SPSCQueue<uint64_t,SAT_QUEUE_SIZE_RESIZE> SAT_ResizeQueue;

//----------------------------------------------------------------------
//
// 
//
//----------------------------------------------------------------------

class SAT_Window
: public SAT_ImplementedWindow
{
    public:
        SAT_Window(uint32_t AWidth, uint32_t AHeight, intptr_t AParent=0);
        virtual ~SAT_Window();
    public:
        SAT_Renderer*           getRenderer();
        SAT_Painter*            getPainter();
        bool                    resizedWindow();
    public: // base window
        void                    on_window_resize(uint32_t AWidth, uint32_t AHeight) override;
        void                    on_window_paint(int32_t AXpos, int32_t AYpos, uint32_t AWidth, uint32_t AHeight) override;
        virtual void            on_window_paint(SAT_PaintContext* AContext) {}
    protected: // window
        virtual void            windowResize(uint32_t AWidth, uint32_t AHeight);
        virtual void            windowPrePaint(int32_t AXpos, int32_t AYpos, uint32_t AWidth, uint32_t AHeight);
        virtual void            windowPaint();
        virtual void            windowPostPaint();
    private:
        void                    handleResizing();
        void                    paintToScreen();
        #ifndef SAT_NO_WINDOW_BUFFERING        
            void                paintToBuffer();
            void                copyBufferToScreen();
        #endif
    private:
        SAT_Renderer*           MRenderer       = nullptr;
        SAT_RenderContext       MRenderContext  = {};
        SAT_Painter*            MPainter        = nullptr;
        SAT_PaintContext        MPaintContext   = {};
        SAT_ResizeQueue         MResizeQueue    = {};
        bool                    MResizedWindow  = false;
        #ifndef SAT_NO_WINDOW_BUFFERING        
            bool                MResizedBuffer  = false;
            SAT_WindowBuffer*   MBuffer         = nullptr;
        #endif
};

//----------------------------------------------------------------------
//
// implementation
//
//----------------------------------------------------------------------

SAT_Window::SAT_Window(uint32_t AWidth, uint32_t AHeight, intptr_t AParent)
: SAT_ImplementedWindow(AWidth, AHeight, AParent)
{
    MRenderer = new SAT_Renderer(this,this);
    SAT_Assert(MRenderer);
    MRenderContext.renderer = MRenderer;
    MPainter = new SAT_Painter(this,this);
    SAT_Assert(MPainter);
    MPaintContext.painter = MPainter;
    #ifndef SAT_NO_WINDOW_BUFFERING        
        MBuffer = new SAT_WindowBuffer(this,this,AWidth,AHeight);
        SAT_Assert(MBuffer);
        // MResizedBuffer = true;  // force buffer redraw
    #endif
}

SAT_Window::~SAT_Window()
{
    #ifndef SAT_NO_WINDOW_BUFFERING        
        SAT_Assert(MBuffer);
        delete MBuffer;
    #endif
    SAT_Assert(MPainter);
    delete MPainter;
    SAT_Assert(MRenderer);
    delete MRenderer;
}

//------------------------------
//
//------------------------------

SAT_Renderer* SAT_Window::getRenderer()
{
    return MRenderer;
}

SAT_Painter* SAT_Window::getPainter()
{
    // if (MResizedBuffer) return MBuffer->getPainter();
    return MPainter;
}

bool SAT_Window::resizedWindow()
{
    return MResizedWindow;
}

//------------------------------
// base window
//------------------------------

void SAT_Window::on_window_resize(uint32_t AWidth, uint32_t AHeight)
{
    windowResize(AWidth,AHeight);
}

void SAT_Window::on_window_paint(int32_t AXpos, int32_t AYpos, uint32_t AWidth, uint32_t AHeight)
{
    windowPrePaint(AXpos,AYpos,AWidth,AHeight);
    windowPaint();
    windowPostPaint();
}

//------------------------------
// window
//------------------------------

void SAT_Window::windowResize(uint32_t AWidth, uint32_t AHeight)
{
    uint64_t size = AWidth;
    size = (size << 32) + AHeight;
    bool ok = MResizeQueue.write(size);
    SAT_Assert(ok);
}

void SAT_Window::windowPrePaint(int32_t AXpos, int32_t AYpos, uint32_t AWidth, uint32_t AHeight)
{
    MPaintContext.update_rect = SAT_Rect(AXpos,AYpos,AWidth,AHeight);
    MPaintContext.current_time = SAT_GetTime();
    handleResizing();
}

void SAT_Window::windowPaint()
{
    #ifndef SAT_NO_WINDOW_BUFFERING        
        paintToBuffer();
        copyBufferToScreen();
    #else
        paintToScreen();
    #endif
}

void SAT_Window::windowPostPaint()
{
    #ifndef SAT_NO_WINDOW_BUFFERING        
        MResizedBuffer = false;
    #endif
    MResizedWindow = false;
    MPaintContext.previous_time = MPaintContext.current_time;
    MPaintContext.current_frame += 1;
}

//------------------------------
// private
//------------------------------

void SAT_Window::handleResizing()
{
    uint64_t size = 0;
    uint32_t count = 0;
    // flush the queue, and keep the last entry only..
    while (MResizeQueue.read(&size)) count += 1;
    if (count > 0)
    {
        uint32_t width  = (size & 0xffffffff00000000) >> 32;
        uint32_t height = (size & 0x00000000ffffffff);
        // todo: check if new size != prevous size?
        // SAT.STATISTICS->report_WindowResizeQueue(count,width,height);
        MResizedWindow = true;
        #ifndef SAT_NO_WINDOW_BUFFERING
            MResizedBuffer = MBuffer->resizeBuffer(width,height);
            // SAT.STATISTICS->report_WindowBufferResize(width,height);
        #endif
    }
}

void SAT_Window::paintToScreen()
{
    SAT_Painter* painter = getPainter();
    SAT_Assert(painter);
    MPaintContext.painter = painter;
    painter->beginPainting(getWidth(),getHeight());
    on_window_paint(&MPaintContext);
    painter->endPainting();
}

#ifndef SAT_NO_WINDOW_BUFFERING        

    void SAT_Window::paintToBuffer()
    {
        SAT_Painter* painter = MBuffer->getPainter();
        SAT_Assert(painter);
        MPaintContext.painter = painter;
        painter->beginPainting(getWidth(),getHeight()); // buffer width/height?
        on_window_paint(&MPaintContext);
        painter->endPainting();
    }

    void SAT_Window::copyBufferToScreen()
    {
        SAT_Painter* painter = getPainter();
        SAT_Assert(painter);
        SAT_Rect rect = MPaintContext.update_rect;
        MPaintContext.painter = painter;
        painter->beginPainting(getWidth(),getHeight());
        painter->drawImage(rect.x,rect.y,MBuffer->getSurface(),rect);
        painter->endPainting();
    }

#endif
