#pragma once

#include "base/sat_base.h"
#include "gui/sat_gui_base.h"
#include "gui/sat_painter.h"
#include "gui/sat_renderer.h"
#include "gui/sat_window_buffer.h"

typedef SAT_SPSCQueue<SAT_Widget*,SAT_WINDOW_REALIGN_QUEUE_SIZE> SAT_RealignQueue;
typedef SAT_SPSCQueue<SAT_Widget*,SAT_WINDOW_REDRAW_QUEUE_SIZE> SAT_RedrawQueue;
typedef SAT_SPSCQueue<SAT_Widget*,SAT_WINDOW_PAINT_QUEUE_SIZE> SAT_PaintQueue;

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

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
        void        checkResized();
    public:
     // void        on_window_show() override;
     // void        on_window_hide() override;
     // void        on_window_move(int32_t AXpos, int32_t AYpos) override;
        void        on_window_resize(uint32_t AWidth, uint32_t AHeight) override;
        void        on_window_paint(int32_t AXpos, int32_t AYpos, uint32_t AWidth, uint32_t AHeight) override;
     // void        on_window_mouse_click(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATime) override;
     // void        on_window_mouse_release(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATime) override;
     // void        on_window_mouse_move(int32_t AXpos, int32_t AYpos, uint32_t AState, uint32_t ATime) override;
     // void        on_window_key_press(uint32_t AKey, uint32_t AChar, uint32_t AState, uint32_t ATime) override;
     // void        on_window_key_release(uint32_t AKey, uint32_t AChar, uint32_t AState, uint32_t ATime) override;
     // void        on_window_mouse_enter(int32_t AXpos, int32_t AYpos, uint32_t ATime) override;
     // void        on_window_mouse_leave(int32_t AXpos, int32_t AYpos, uint32_t ATime) override;
     // void        on_window_client_message(uint32_t AData) override;  
     // void        on_window_timer(double ADelta) override;
    protected: // painting
        SAT_Renderer*           MRenderer       = nullptr;
        SAT_Painter*            MPainter        = nullptr;
        SAT_PaintContext        MPaintContext   = {};
        SAT_ResizeQueue         MResizeQueue    = {};
        SAT_RealignQueue        MRealignQueue   = {};
        SAT_RedrawQueue         MRedrawQueue    = {};
        SAT_PaintQueue          MPaintQueue     = {};
        bool                    MResizedWindow  = false;
        #ifndef SAT_NO_WINDOW_BUFFERING        
            SAT_WindowBuffer    MBuffer         = {};
            bool                MResizedBuffer  = false;
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
    MPainter = new SAT_Painter(this,this);
    MPaintContext.painter = MPainter;
    #ifndef SAT_NO_WINDOW_BUFFERING        
        MBuffer.initialize(this,this,getWidth(),getHeight());
    #endif
}

SAT_Window::~SAT_Window()
{
    #ifndef SAT_NO_WINDOW_BUFFERING        
        MBuffer.cleanup();
    #endif
    delete MPainter;
    delete MRenderer;
}

//------------------------------
// base window
//------------------------------

void SAT_Window::on_window_resize(uint32_t AWidth, uint32_t AHeight)
{
    //SAT_PRINT("%i,%i\n",AWidth,AHeight);
    //SAT_ImplementedWindow::on_window_resize(AWidth,AHeight);
    uint64_t size = AWidth;
    size = (size << 32) + AHeight;
    bool ok = MResizeQueue.write(size);
    SAT_Assert(ok);
}

void SAT_Window::on_window_paint(int32_t AXpos, int32_t AYpos, uint32_t AWidth, uint32_t AHeight)
{
    //SAT_PRINT("%i,%i,%i,%i\n",AXpos,AYpos,AWidth,AHeight);;
    //SAT_ImplementedWindow::on_window_paint(AXpos,AYpos,AWidth,AHeight)
    checkResized();
    #ifndef SAT_NO_WINDOW_BUFFERING        
        if (MResizedBuffer)
        {
            SAT_PRINT("buffer has been resized (%i,%i). redrawing\n",MBuffer.getWidth(),MBuffer.getHeight());
        }
    #endif
    if (MResizedWindow)
    {
        SAT_PRINT("window has been resized (%i,%i). realigning/redrawing\n",getWidth(),getHeight());
    }

}

//------------------------------
//
//------------------------------

/*
    window.on_window_resize(w,h) is called before width/height is set internally in the window,
    we just stuff the resize request into a queue, which means we can rely on the
    window.getWidth/Height size to already be set to the newest sizes,
    and don't really need to rely on the sizes in the resuze queue... ???
*/

void SAT_Window::checkResized()
{
    MResizedWindow = false;
    uint32_t width  = 0;    // getWidth();
    uint32_t height = 0;    // getHeight();
    uint64_t size = 0;
    uint32_t resize_count = 0;
    // flush the queue, and keep the last entry only..
    while (MResizeQueue.read(&size)) resize_count += 1;
    // SAT.STATISTICS->report_resize_queue_count(count);
    if (resize_count > 0)
    {
        // todo: check if new size != prevous size?
        MResizedWindow = true;
        #ifndef SAT_NO_WINDOW_BUFFERING
            MResizedBuffer = false;
            width  = (size & 0xffffffff00000000) >> 32;
            height = (size & 0x00000000ffffffff);
            MResizedBuffer = MBuffer.resizeBuffer(width,height);
        #endif
    }
}
