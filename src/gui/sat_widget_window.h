#pragma once

#include "base/sat_base.h"
#include "gui/sat_gui_base.h"
#include "gui/sat_painter.h"
#include "gui/sat_renderer.h"
#include "gui/sat_widget.h"
#include "gui/sat_window.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_WidgetWindow
: public SAT_Window
, public SAT_WidgetOwner
, public SAT_Widget
{
    public:
        SAT_WidgetWindow(uint32_t AWidth, uint32_t AHeight, intptr_t AParent=0);
        virtual ~SAT_WidgetWindow();
    public: // base window
     // void            on_window_show() override;
     // void            on_window_hide() override;
     // void            on_window_move(int32_t AXpos, int32_t AYpos) override;
     // void            on_window_resize(uint32_t AWidth, uint32_t AHeight) override;
     // void            on_window_paint(int32_t AXpos, int32_t AYpos, uint32_t AWidth, uint32_t AHeight) override;
     // void            on_window_mouse_click(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATime) override;
     // void            on_window_mouse_release(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATime) override;
     // void            on_window_mouse_move(int32_t AXpos, int32_t AYpos, uint32_t AState, uint32_t ATime) override;
     // void            on_window_key_press(uint32_t AKey, uint32_t AChar, uint32_t AState, uint32_t ATime) override;
     // void            on_window_key_release(uint32_t AKey, uint32_t AChar, uint32_t AState, uint32_t ATime) override;
     // void            on_window_mouse_enter(int32_t AXpos, int32_t AYpos, uint32_t ATime) override;
     // void            on_window_mouse_leave(int32_t AXpos, int32_t AYpos, uint32_t ATime) override;
     // void            on_window_client_message(uint32_t AData) override;  
     // void            on_window_timer(double ADelta) override;
    public: // window
     // void            on_window_paint(SAT_PaintContext* AContext) override;
    public: // widget owner
        SAT_Painter*    do_widget_owner_get_painter(SAT_Widget* AWidget);
        uint32_t        do_widget_owner_get_width(SAT_Widget* AWidget);
        uint32_t        do_widget_owner_get_height(SAT_Widget* AWidget);
        bool            do_widget_owner_register_timer(SAT_Widget* AWidget);
        bool            do_widget_owner_unregister_timer(SAT_Widget* AWidget);
    public: // widget
        void            do_widget_update(SAT_Widget* AWidget, uint32_t AMode=SAT_WIDGET_UPDATE_VALUE, uint32_t AIndex=0) override;
        void            do_widget_realign(SAT_Widget* AWidget, uint32_t AMode=SAT_WIDGET_REALIGN_PARENT, uint32_t AIndex=0) override;
        void            do_widget_redraw(SAT_Widget* AWidget, uint32_t AMode=SAT_WIDGET_REDRAW_SELF, uint32_t AIndex=0) override;
    private:
        SAT_WidgetArray MTimerWidgets = {};
};

//----------------------------------------------------------------------
//
// implementation
//
//----------------------------------------------------------------------

SAT_WidgetWindow::SAT_WidgetWindow(uint32_t AWidth, uint32_t AHeight, intptr_t AParent)
: SAT_Window(AWidth, AHeight, AParent)
, SAT_Widget(SAT_Rect(AWidth,AHeight))
{
}

SAT_WidgetWindow::~SAT_WidgetWindow()
{
}

//------------------------------
// base window
//------------------------------

#if 0

void SAT_WidgetWindow::on_window_show()
{
}

void SAT_WidgetWindow::on_window_hide()
{
}

void SAT_WidgetWindow::on_window_move(int32_t AXpos, int32_t AYpos)
{
}

void SAT_WidgetWindow::on_window_resize(uint32_t AWidth, uint32_t AHeight)
{
}

void SAT_WidgetWindow::on_window_paint(int32_t AXpos, int32_t AYpos, uint32_t AWidth, uint32_t AHeight)
{
}

void SAT_WidgetWindow::on_window_mouse_click(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATime)
{
}

void SAT_WidgetWindow::on_window_mouse_release(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATime)
{
}

void SAT_WidgetWindow::on_window_mouse_move(int32_t AXpos, int32_t AYpos, uint32_t AState, uint32_t ATime)
{
}

void SAT_WidgetWindow::on_window_key_press(uint32_t AKey, uint32_t AChar, uint32_t AState, uint32_t ATime)
{
}

void SAT_WidgetWindow::on_window_key_release(uint32_t AKey, uint32_t AChar, uint32_t AState, uint32_t ATime)
{
}

void SAT_WidgetWindow::on_window_mouse_enter(int32_t AXpos, int32_t AYpos, uint32_t ATime)
{
}

void SAT_WidgetWindow::on_window_mouse_leave(int32_t AXpos, int32_t AYpos, uint32_t ATime)
{
}

void SAT_WidgetWindow::on_window_client_message(uint32_t AData)  
{
}

void SAT_WidgetWindow::on_window_timer(double ADelta)
{
}

#endif // 0

//------------------------------
// window
//------------------------------

// void SAT_WidgetWindow::on_window_paint(SAT_PaintContext* AContext)
// {
// }

//------------------------------
// widget owner
//------------------------------

SAT_Painter* SAT_WidgetWindow::do_widget_owner_get_painter(SAT_Widget* AWidget)
{
    //return MPainter;
    return getPainter();
}

uint32_t SAT_WidgetWindow::do_widget_owner_get_width(SAT_Widget* AWidget)
{
    return getWidth();
}

uint32_t SAT_WidgetWindow::do_widget_owner_get_height(SAT_Widget* AWidget)
{
    return getWidth();
}

bool SAT_WidgetWindow::do_widget_owner_register_timer(SAT_Widget* AWidget)
{
    MTimerWidgets.append(AWidget);
    return true;
}

bool SAT_WidgetWindow::do_widget_owner_unregister_timer(SAT_Widget* AWidget)
{
    MTimerWidgets.remove(AWidget);
    return true;
}

//------------------------------
// widget
//------------------------------

void SAT_WidgetWindow::do_widget_update(SAT_Widget* AWidget, uint32_t AMode, uint32_t AIndex)
{
}

void SAT_WidgetWindow::do_widget_realign(SAT_Widget* AWidget, uint32_t AMode, uint32_t AIndex)
{
}

void SAT_WidgetWindow::do_widget_redraw(SAT_Widget* AWidget, uint32_t AMode, uint32_t AIndex)
{
}
