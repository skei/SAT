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
        SAT_Renderer*           MRenderer               = nullptr;
        SAT_Painter*            MPainter                = nullptr;
        SAT_WindowBuffer        MBuffer                 = {};
        SAT_PaintContext        MPaintContext           = {};
        SAT_RealignQueue        MRealignQueue           = {};
        SAT_RedrawQueue         MRedrawQueue            = {};
        SAT_PaintQueue          MPaintQueue             = {};
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
    MBuffer.initBuffer(AWidth,AHeight);
}

SAT_Window::~SAT_Window()
{
/*
    deleteBuffer();
*/
    MBuffer.deleteBuffer();
    delete MPainter;
    delete MRenderer;
}

//------------------------------
// buffer
//------------------------------


//------------------------------
// base window
//------------------------------

void SAT_Window::on_window_resize(uint32_t AWidth, uint32_t AHeight)
{
    //SAT_PRINT("%i,%i\n",AWidth,AHeight);
    //SAT_ImplementedWindow::on_window_resize(AWidth,AHeight);
    MBuffer.requestResize(AWidth,AHeight);
}

void SAT_Window::on_window_paint(int32_t AXpos, int32_t AYpos, uint32_t AWidth, uint32_t AHeight)
{
    //SAT_PRINT("%i,%i,%i,%i\n",AXpos,AYpos,AWidth,AHeight);;
    //SAT_ImplementedWindow::on_window_paint(AXpos,AYpos,AWidth,AHeight)
    uint32_t width = getWidth();
    uint32_t height = getHeight();
    bool resized = MBuffer.checkSize(width,height);
    if (resized)
    {
        // buffer resized, redraw entire window..
        // uint32_t buffer_width = MBuffer.getWidth();
        // uint32_t buffer_height = MBuffer.getHeight();

    }
}

//------------------------------
//
//------------------------------
