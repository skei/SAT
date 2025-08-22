#pragma once

#include "base/sat_base.h"
#include "base/util/sat_intmath.h"
#include "gui/sat_gui_base.h"
#include "gui/sat_painter.h"
#include "gui/sat_renderer.h"

typedef SAT_SPSCQueue<uint64_t,32> SAT_ResizeQueue;

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
        virtual bool createBuffer(uint32_t AWidth, uint32_t AHeight);
        virtual void deleteBuffer();
        virtual bool resizeBuffer(uint32_t AWidth, uint32_t AHeight);
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
    private: // buffer
        // SAT_Surface*        MBuffer                 = nullptr;
        uint32_t                MBufferWidth            = 0;
        uint32_t                MBufferHeight           = 0;
        uint32_t                MPreviousWindowWidth    = 0;
        uint32_t                MPreviousWindowHeight   = 0;
    protected: // painting
        SAT_Renderer*           MRenderer               = nullptr;
        SAT_Painter*            MPainter                = nullptr;
        SAT_PaintContext        MPaintContext           = {};
        SAT_ResizeQueue         MResizeQueue            = {};
        

    
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
    uint32_t width  = SAT_NextPowerOfTwo(AWidth);
    uint32_t height = SAT_NextPowerOfTwo(AHeight);
    createBuffer(width,height);
    MPreviousWindowWidth = AWidth;
    MPreviousWindowWidth = AHeight;
}

SAT_Window::~SAT_Window()
{
    deleteBuffer();
    delete MPainter;
    delete MRenderer;
}

//------------------------------
// buffer
//------------------------------

bool SAT_Window::createBuffer(uint32_t AWidth, uint32_t AHeight)
{
    MBufferWidth = AWidth;
    MBufferHeight = AHeight;
    //SAT_PRINT("creating buffer: %i,%i\n",MBufferWidth,MBufferHeight);
    return true;
}

void SAT_Window::deleteBuffer()
{
    //SAT_PRINT("deleting buffer\n");
    MBufferWidth = 0;
    MBufferHeight = 0;
}

/*
    returns true if buffer were actually resized, and needs to be redrawn
    (checked for PowerOfTwo..)
*/

bool SAT_Window::resizeBuffer(uint32_t AWidth, uint32_t AHeight)
{
    uint32_t width  = SAT_NextPowerOfTwo(AWidth);
    uint32_t height = SAT_NextPowerOfTwo(AHeight);
    if ((width != MBufferWidth) || (height != MBufferHeight))
    {
        SAT_PRINT("buffer resized!\n");
        deleteBuffer();
        if (!createBuffer(width,height))
        {
            SAT_PRINT("error! couldn't create buffer (%i,%i)\n",width,height);
            return false;
        }
        else
        {
            return true;
        }
    }
    return false;
}

//------------------------------
// base window
//------------------------------

void SAT_Window::on_window_resize(uint32_t AWidth, uint32_t AHeight)
{
    //SAT_ImplementedWindow::on_window_resize(AWidth,AHeight);
    uint64_t size = AWidth;
    size = (size << 32) + AHeight;
    if (!MResizeQueue.write(size)) { SAT_PRINT("couldn't write to resize queue\n"); }
}

void SAT_Window::on_window_paint(int32_t AXpos, int32_t AYpos, uint32_t AWidth, uint32_t AHeight)
{
    //SAT_ImplementedWindow::on_window_paint(AXpos,AYpos,AWidth,AHeight)
    uint32_t new_width  = getWidth();
    uint32_t new_height = getHeight();

    // flush the queue, and keep the last entry only..
    uint64_t size = 0;
    uint32_t resize_count = 0;
    while (MResizeQueue.read(&size)) resize_count += 1;
    if (resize_count > 0)
    {
        // SAT.STATISTICS->report_resize_queue_count(count);
        new_width  = (size & 0xffffffff00000000) >> 32;
        new_height = (size & 0x00000000ffffffff);
        SAT_PRINT("window resized: %i,%i\n",new_width,new_height);
    }

    // check if window is actually the same size as the last resize event
    // SAT_Assert(new_width == getWidth());
    // SAT_Assert(new_height == getHeight());

    if ((new_width != MPreviousWindowWidth) || (new_height != MPreviousWindowHeight))
    {
        if (resizeBuffer(new_width,new_height))
        {
            // redraw
        }
    }

    MPreviousWindowWidth = new_width; // getWidth();
    MPreviousWindowHeight = new_height; // getHeight();
}

//------------------------------
//
//------------------------------
