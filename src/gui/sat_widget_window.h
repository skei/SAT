#pragma once

#include "base/sat_base.h"
#include "base/system/sat_timer.h"
#include "gui/sat_gui_base.h"
#include "gui/sat_painter.h"
#include "gui/sat_renderer.h"
#include "gui/sat_widget.h"
#include "gui/sat_window.h"

/*
    NOTE: all using SPSC queues!
*/

typedef SAT_SPSCQueue<SAT_Widget*,SAT_WINDOW_REALIGN_QUEUE_SIZE> SAT_WidgetRealignQueue;
typedef SAT_SPSCQueue<SAT_Widget*,SAT_WINDOW_REDRAW_QUEUE_SIZE> SAT_WidgetRedrawQueue;
typedef SAT_SPSCQueue<SAT_Widget*,SAT_WINDOW_PAINT_QUEUE_SIZE> SAT_WidgetPaintQueue;

/*
    parameter updates -> widget redraws coming in from the audio thread..
        processor calls processor_listener = plugin
        plugin calls plugin_listener -> editor
        editor calls editor_listener -> window
        window writes to update_queue -> timer
        timer writes to paint_queue -> gui
        gui >_ paints...
*/

typedef SAT_SPSCQueue<SAT_Widget*,SAT_WINDOW_UPDATE_QUEUE_SIZE> SAT_WidgetUpdateQueue;


//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_WidgetWindow
: public SAT_Window
, public SAT_WidgetOwner
, public SAT_Widget
, public SAT_TimerListener
{
    public:
        SAT_WidgetWindow(uint32_t AWidth, uint32_t AHeight, intptr_t AParent=0);
        virtual ~SAT_WidgetWindow();
    public:
        virtual void        setHintWidget(SAT_Widget* AWidget);
        virtual void        appendTimerWidget(SAT_Widget* AWidget);
        virtual void        removeTimerWidget(SAT_Widget* AWidget);
        virtual void        handleTweening(double ADelta);
        virtual void        flushRealignQueue();
        virtual SAT_Rect    flushRedrawQueue();
    public: // timer
        void                on_TimerListener_update(SAT_Timer* ATimer, double ADelta) final;
    public: // window
        void                on_window_paint(SAT_PaintContext* AContext, bool AResized=false) override;
    public: // base window
        void                on_window_show() override;
        void                on_window_hide() override;
        void                on_window_move(int32_t AXpos, int32_t AYpos) override;
        void                on_window_resize(uint32_t AWidth, uint32_t AHeight) override;
        //void              on_window_paint(int32_t AXpos, int32_t AYpos, uint32_t AWidth, uint32_t AHeight) override;
        void                on_window_mouse_click(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATime) override;
        void                on_window_mouse_release(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATime) override;
        void                on_window_mouse_move(int32_t AXpos, int32_t AYpos, uint32_t AState, uint32_t ATime) override;
        void                on_window_key_press(uint32_t AKey, uint32_t AChar, uint32_t AState, uint32_t ATime) override;
        void                on_window_key_release(uint32_t AKey, uint32_t AChar, uint32_t AState, uint32_t ATime) override;
        void                on_window_mouse_enter(int32_t AXpos, int32_t AYpos, uint32_t ATime) override;
        void                on_window_mouse_leave(int32_t AXpos, int32_t AYpos, uint32_t ATime) override;
        void                on_window_client_message(uint32_t AData) override;  
        void                on_window_timer(uint32_t ATimerId, double ADelta) override;
    public: // widget owner
        SAT_Painter*        do_widget_owner_get_painter(SAT_Widget* AWidget);
        uint32_t            do_widget_owner_get_width(SAT_Widget* AWidget);
        uint32_t            do_widget_owner_get_height(SAT_Widget* AWidget);
        bool                do_widget_owner_register_timer(SAT_Widget* AWidget);
        bool                do_widget_owner_unregister_timer(SAT_Widget* AWidget);
    public: // widget
        void                do_widget_update(SAT_Widget* AWidget, uint32_t AMode=SAT_WIDGET_UPDATE_VALUE, uint32_t AIndex=0) override;
        void                do_widget_realign(SAT_Widget* AWidget, uint32_t AMode=SAT_WIDGET_REALIGN_PARENT, uint32_t AIndex=0) override;
        void                do_widget_redraw(SAT_Widget* AWidget, uint32_t AMode=SAT_WIDGET_REDRAW_SELF, uint32_t AIndex=0) override;
        void                do_widget_notify(SAT_Widget* AWidget, uint32_t AType, int32_t AValue) override;
        void                do_widget_hint(SAT_Widget* AWidget, uint32_t AType, const char* AHint) override;
        void                do_widget_modal(SAT_Widget* AWidget) override;
        void                do_widget_cursor(SAT_Widget* AWidget, uint32_t ACursor) override;
        void                do_widget_capture_mouse(SAT_Widget* AWidget) override;
        void                do_widget_capture_keyboard(SAT_Widget* AWidget) override;
    private:
        SAT_WidgetUpdateQueue   MWidgetUpdateQueue      = {};
        SAT_WidgetRealignQueue  MWidgetRealignQueue     = {};
        SAT_WidgetRedrawQueue   MWidgetRedrawQueue      = {};
        SAT_WidgetPaintQueue    MWidgetPaintQueue       = {};
    private:
        SAT_Timer*              MWindowTimer            = nullptr;
        uint32_t                MCurrentTimerTick       = 0;
        SAT_WidgetArray         MTimerWidgets           = {};
    private:
        SAT_Widget*             MHoverWidget            = nullptr;
        SAT_Widget*             MModalWidget            = nullptr;
        SAT_Widget*             MCapturedMouseWidget    = nullptr;
        SAT_Widget*             MCapturedKeyWidget      = nullptr;
        SAT_Widget*             MClickedWidget          = nullptr;
        SAT_Widget*             MDragWidget             = nullptr;
        SAT_Widget*             MHintWidget             = nullptr;
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
    MWindowTimer = new SAT_Timer(this);
}

SAT_WidgetWindow::~SAT_WidgetWindow()
{
    if (MWindowTimer)
    {
        if (MWindowTimer->isRunning()) MWindowTimer->stop();
        delete MWindowTimer;
    }
}

//------------------------------
//
//------------------------------

void SAT_WidgetWindow::setHintWidget(SAT_Widget* AWidget)
{
    MHintWidget = AWidget;
}

/*
    only call these in the gui-thread!
    timer (via x11 user message) might be reading the queue
*/

void SAT_WidgetWindow::appendTimerWidget(SAT_Widget* AWidget)
{
    SAT_Assert(AWidget);
    MTimerWidgets.append(AWidget);
}

void SAT_WidgetWindow::removeTimerWidget(SAT_Widget* AWidget)
{
    SAT_Assert(AWidget);
    MTimerWidgets.remove(AWidget);
}

void SAT_WidgetWindow::handleTweening(double ADelta)
{
    //TODO
}

/*
    save previous_realign_timertick, and previous_redraw_timertick in widgets
    compare with MCurrentTimerTick, if same, already processed/nhandles this tick..
*/

void SAT_WidgetWindow::flushRealignQueue()
{
    SAT_Widget* widget;
    while (MWidgetRealignQueue.read(&widget))
    {
        widget->realignChildren();
        MWidgetRedrawQueue.write(widget);
    }
}

SAT_Rect SAT_WidgetWindow::flushRedrawQueue()
{
    SAT_Rect rect;
    SAT_Widget* widget;
    while (MWidgetRedrawQueue.read(&widget))
    {
        rect.combine(widget->getRect());
        MWidgetPaintQueue.write(widget);
    }
    return SAT_Rect();
}

//------------------------------
// timer
//------------------------------

/*
    [TIMER-THREAD]
    don't handle the tick here..
    post an x11 user/client messsage, and handle the event when it comes back
    via the event thread and we're in the gui thread..
*/

void SAT_WidgetWindow::on_TimerListener_update(SAT_Timer* ATimer, double ADelta)
{
    sendClientMessage(SAT_WINDOW_USER_MESSAGE_TIMER,0);
};

//------------------------------
// window
//------------------------------

void SAT_WidgetWindow::on_window_paint(SAT_PaintContext* AContext, bool AResized)
{
    //paintChildren();
    SAT_Widget* widget;
    while (MWidgetPaintQueue.read(&widget))
    {
        //widget->on_widget_paint(AContext);
        widget->paintChildren(AContext);
    }
}

//------------------------------
// base window
//------------------------------

void SAT_WidgetWindow::on_window_show()
{
    for (uint32_t i=0; i<MChildren.size(); i++)
    {
        MChildren[i]->on_widget_show(this);
    }
    MWindowTimer->start(SAT_WINDOW_TIMER_MS);
}

void SAT_WidgetWindow::on_window_hide()
{
    if (MWindowTimer->isRunning()) MWindowTimer->stop();
    for (uint32_t i=0; i<MChildren.size(); i++)
    {
        MChildren[i]->on_widget_hide(this);
    }
}

void SAT_WidgetWindow::on_window_move(int32_t AXpos, int32_t AYpos)
{
}

void SAT_WidgetWindow::on_window_resize(uint32_t AWidth, uint32_t AHeight)
{
    SAT_Window::windowResize(AWidth,AHeight);
    realignChildren();
}

// void SAT_WidgetWindow::on_window_paint(int32_t AXpos, int32_t AYpos, uint32_t AWidth, uint32_t AHeight)
// {
// }

void SAT_WidgetWindow::on_window_mouse_click(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATime)
{
    if (MHoverWidget) {
        MClickedWidget = MHoverWidget;
        if (MClickedWidget->Options.auto_capture) MCapturedMouseWidget = MClickedWidget;
        MHoverWidget->on_widget_mouse_click(AXpos,AYpos,AButton,AState,ATime);
    }
}

void SAT_WidgetWindow::on_window_mouse_release(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATime)
{
    MClickedWidget = nullptr;
    if (MCapturedMouseWidget)
    {
        MCapturedMouseWidget->on_widget_mouse_release(AXpos,AYpos,AButton,AState,ATime);
        MCapturedMouseWidget = nullptr;
    }
}

/*
    hover
    on_widget_drag_start/move/drop..
*/

void SAT_WidgetWindow::on_window_mouse_move(int32_t AXpos, int32_t AYpos, uint32_t AState, uint32_t ATime)
{
    MHoverWidget = findHoverWidget();
    if (MCapturedMouseWidget)
    {
        MCapturedMouseWidget->on_widget_mouse_move(AXpos,AYpos,AState,ATime);
        // if (is_dragging)
        // {
        // }
    }
    // else 
    // {
    //     if (MHoverWidget)
    //     {
    //         if (MHoverWidget->Options & SAT_WIDGET_OPTION_WANT_HOVER_EVENTS)        
    //         {
    //             MHoverWidget->on_widget_mouse_move(AXpos,AYpos,AState,ATime);
    //         }
    //     }
    // }
}

void SAT_WidgetWindow::on_window_key_press(uint32_t AKey, uint32_t AChar, uint32_t AState, uint32_t ATime)
{
    if (MCapturedKeyWidget)
    {
        MCapturedKeyWidget->on_widget_key_press(AKey,AChar,AState,ATime);
    }
}

void SAT_WidgetWindow::on_window_key_release(uint32_t AKey, uint32_t AChar, uint32_t AState, uint32_t ATime)
{
    if (MCapturedKeyWidget)
    {
        MCapturedKeyWidget->on_widget_key_release(AKey,AChar,AState,ATime);
    }
}

void SAT_WidgetWindow::on_window_mouse_enter(int32_t AXpos, int32_t AYpos, uint32_t ATime)
{
    MHoverWidget = findHoverWidget();
    if (MHoverWidget) MHoverWidget->on_widget_mouse_enter(nullptr,AXpos,AYpos,ATime);
}

void SAT_WidgetWindow::on_window_mouse_leave(int32_t AXpos, int32_t AYpos, uint32_t ATime)
{
    if (MHoverWidget) MHoverWidget->on_widget_mouse_leave(nullptr,AXpos,AYpos,ATime);
    MHoverWidget = nullptr;
}

void SAT_WidgetWindow::on_window_client_message(uint32_t AData)  
{
    SAT_PRINT("AData = %i\n",AData);
}

/*
    1. handle widgets requesting timer ticks
    2. tweening..
    3. flush realign queue, handle realigning..
    4. flush redraw queue, post to paint queue
    5. invalidate
*/

void SAT_WidgetWindow::on_window_timer(uint32_t ATimerId, double ADelta)
{
    for (uint32_t i=0; i<MTimerWidgets.size(); i++)
    {
        MTimerWidgets[i]->on_widget_timer(ATimerId,ADelta);
    }
    handleTweening(ADelta);
    flushRealignQueue();
    SAT_Rect rect = flushRedrawQueue();
    if (rect.isNotEmpty())
    {
        SAT_PRINT("invalidate\n");
        invalidate(rect.x,rect.y,rect.w,rect.h);
    }
    MCurrentTimerTick += 1;
}

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

/*
    if window is open (after show() has been called),
    the MTimerWidgets array might be read in timer-thread!!!
    either register the timers _before_ the window is opened,
    or guard with lock/mutex!
*/

bool SAT_WidgetWindow::do_widget_owner_register_timer(SAT_Widget* AWidget)
{
    MTimerWidgets.append(AWidget);
    return true;
}

/*
    see register_timer()
*/

bool SAT_WidgetWindow::do_widget_owner_unregister_timer(SAT_Widget* AWidget)
{
    MTimerWidgets.remove(AWidget);
    return true;
}

//------------------------------
// widget
//------------------------------

/*
    -> editor -> plugin -> processor
*/

void SAT_WidgetWindow::do_widget_update(SAT_Widget* AWidget, uint32_t AMode, uint32_t AIndex)
{
    // if (MListener) MListener->do_widget_update(AWidget);
}

void SAT_WidgetWindow::do_widget_realign(SAT_Widget* AWidget, uint32_t AMode, uint32_t AIndex)
{
    MWidgetRealignQueue.write(AWidget);
}

void SAT_WidgetWindow::do_widget_redraw(SAT_Widget* AWidget, uint32_t AMode, uint32_t AIndex)
{
    MWidgetRedrawQueue.write(AWidget);
}

void SAT_WidgetWindow::do_widget_notify(SAT_Widget* AWidget, uint32_t AType, int32_t AValue)
{
}

void SAT_WidgetWindow::do_widget_hint(SAT_Widget* AWidget, uint32_t AType, const char* AHint)
{
    if (MHintWidget) MHintWidget->on_widget_hint(AType,AHint);
}

void SAT_WidgetWindow::do_widget_modal(SAT_Widget* AWidget)
{
    MModalWidget = AWidget;
}

void SAT_WidgetWindow::do_widget_cursor(SAT_Widget* AWidget, uint32_t ACursor)
{
}

void SAT_WidgetWindow::do_widget_capture_mouse(SAT_Widget* AWidget)
{
}

void SAT_WidgetWindow::do_widget_capture_keyboard(SAT_Widget* AWidget)
{
}
