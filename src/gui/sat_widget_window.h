#pragma once

/*
    note to self:
    remember to keep the widget part in sync with the window parts (size, rect, etc)
*/

#include "base/sat_base.h"
#include "base/system/sat_timer.h"
#include "gui/sat_gui_base.h"
#include "gui/sat_painter.h"
#include "gui/sat_renderer.h"
#include "gui/sat_tween_manager.h"
#include "gui/sat_widget.h"
#include "gui/sat_window.h"

/*
    NOTE: all SPSC queues!
*/

// typedef SAT_SPSCQueue<SAT_Widget*,SAT_QUEUE_SIZE_UPDATE>    SAT_WidgetUpdateQueue;
typedef SAT_SPSCQueue<SAT_Widget*,SAT_QUEUE_SIZE_REALIGN>   SAT_WidgetRealignQueue;
typedef SAT_SPSCQueue<SAT_Widget*,SAT_QUEUE_SIZE_REDRAW>    SAT_WidgetRedrawQueue;
typedef SAT_SPSCQueue<SAT_Widget*,SAT_QUEUE_SIZE_PAINT>     SAT_WidgetPaintQueue;

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
        virtual void        setListener(SAT_WindowListener* AListener);
        virtual void        setHintWidget(SAT_Widget* AWidget);
        virtual void        appendTimerWidget(SAT_Widget* AWidget);
        virtual void        removeTimerWidget(SAT_Widget* AWidget);
        virtual void        handleTimer(uint32_t ATimerId, double ADelta);
        virtual void        handlePainting(SAT_PaintContext* AContext);
    public:
        void                on_timer_listener_update(SAT_Timer* ATimer, double ADelta) override;
        void                on_window_paint(SAT_PaintContext* AContext, bool ABuffered=false) override;
    public:
        void                on_window_show() override;
        void                on_window_hide() override;
        void                on_window_move(int32_t AXpos, int32_t AYpos) override;
        void                on_window_resize(uint32_t AWidth, uint32_t AHeight) override;
     // void                on_window_paint(int32_t AXpos, int32_t AYpos, uint32_t AWidth, uint32_t AHeight) override;
        void                on_window_mouse_click(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATime) override;
        void                on_window_mouse_release(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATime) override;
        void                on_window_mouse_move(int32_t AXpos, int32_t AYpos, uint32_t AState, uint32_t ATime) override;
        void                on_window_key_press(uint32_t AKey, uint32_t AChar, uint32_t AState, uint32_t ATime) override;
        void                on_window_key_release(uint32_t AKey, uint32_t AChar, uint32_t AState, uint32_t ATime) override;
        void                on_window_mouse_enter(int32_t AXpos, int32_t AYpos, uint32_t ATime) override;
        void                on_window_mouse_leave(int32_t AXpos, int32_t AYpos, uint32_t ATime) override;
        void                on_window_client_message(uint32_t AData) override;  
        void                on_window_timer(uint32_t ATimerId, double ADelta) override;
    public:
        SAT_Painter*        do_widget_owner_get_painter(SAT_Widget* AWidget) override;
        uint32_t            do_widget_owner_get_width(SAT_Widget* AWidget) override;
        uint32_t            do_widget_owner_get_height(SAT_Widget* AWidget) override;
        bool                do_widget_owner_register_timer(SAT_Widget* AWidget) override;
        bool                do_widget_owner_unregister_timer(SAT_Widget* AWidget) override;
    public:
        void                do_widget_update(SAT_Widget* AWidget, uint32_t AMode=SAT_WIDGET_UPDATE_VALUE, uint32_t AIndex=0) override;
        void                do_widget_realign(SAT_Widget* AWidget, uint32_t AMode=SAT_WIDGET_REALIGN_PARENT, uint32_t AIndex=0) override;
        void                do_widget_redraw(SAT_Widget* AWidget, uint32_t AMode=SAT_WIDGET_REDRAW_SELF, uint32_t AIndex=0) override;
        void                do_widget_tween(SAT_Widget* AWidget, SAT_TweenChain* AChain) override;
        void                do_widget_notify(SAT_Widget* AWidget, uint32_t AType, int32_t AValue) override;
        void                do_widget_hint(SAT_Widget* AWidget, uint32_t AType, const char* AHint) override;
        void                do_widget_modal(SAT_Widget* AWidget) override;
        void                do_widget_cursor(SAT_Widget* AWidget, uint32_t ACursor) override;
        void                do_widget_capture_mouse(SAT_Widget* AWidget) override;
        void                do_widget_capture_keyboard(SAT_Widget* AWidget) override;
    private:
        SAT_WindowListener*     MListener               = nullptr;  // aka editor
        SAT_TweenManager        MTweenManager           = {};       // widget animations
        SAT_Timer*              MWindowTimer            = nullptr;  // timer
        SAT_WidgetArray         MTimerWidgets           = {};       // array of widgets that want timer ticks
        uint32_t                MCurrentTimerTick       = 0;        // increasing tick counter
        sat_atomic_bool_t       MTimerBlocked           {false};    // if this is true, timer handler returns immediately
    private:
     // SAT_WidgetUpdateQueue   MWidgetUpdateQueue      = {};       // value changed
        SAT_WidgetRealignQueue  MWidgetRealignQueue     = {};       // needs to be realigned
        SAT_WidgetRedrawQueue   MWidgetRedrawQueue      = {};       // needs to be redrawn
        SAT_WidgetPaintQueue    MWidgetPaintQueue       = {};       // will be painted
    private:
        SAT_Widget*             MCapturedKeyWidget      = nullptr;  // send key events directoy to this
        SAT_Widget*             MCapturedMouseWidget    = nullptr;  // send mouse events directly to this
        SAT_Widget*             MClickedWidget          = nullptr;  // clicked widget
        SAT_Widget*             MDragWidget             = nullptr;  // drag'n'drop, start widget (drag from)
        SAT_Widget*             MHintWidget             = nullptr;  // widget receiving hints
        SAT_Widget*             MHoverWidget            = nullptr;  // currently hovering over
        SAT_Widget*             MModalWidget            = nullptr;  // exclusive widget, all other widgets ignored
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

void SAT_WidgetWindow::setListener(SAT_WindowListener* AListener)
{
    MListener = AListener;
}

void SAT_WidgetWindow::setHintWidget(SAT_Widget* AWidget)
{
    MHintWidget = AWidget;
}

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

/*
    TODO: widget redrawing originating from audio automation & modulation
    MWidgetUpdateQueue ?
*/

void SAT_WidgetWindow::handleTimer(uint32_t ATimerId, double ADelta)
{
    MTimerBlocked = true;
    // ----- widget timers -----
    for (uint32_t i=0; i<MTimerWidgets.size(); i++)
    {
        MTimerWidgets[i]->on_widget_timer(ATimerId,ADelta);
    }
    // ----- tweening -----
    MTweenManager.process(ADelta);
    // ----- realign queue -----
    uint32_t count = 0;
    SAT_Widget* widget;
    while (MWidgetRealignQueue.read(&widget))
    {
        count += 1;
        //widget->realignChildren();
        widget->on_widget_realign();
        MWidgetRedrawQueue.write(widget);
    }
    // SAT.STATISTICS.report_WindwRealignQueue(count);
    // ----- redraw queue -----
    count = 0;
    SAT_Rect rect;
    while (MWidgetRedrawQueue.read(&widget))
    {
        count += 1;
        rect.combine(widget->getRect());
        MWidgetPaintQueue.write(widget);
    }
    // SAT.STATISTICS.report_WindwRedrawQueue(count,rect);
    // ----- invalidate -----
    if (rect.isNotEmpty())
    {
        SAT_PRINT("invalidate\n");
        invalidate(rect.x,rect.y,rect.w,rect.h);
    }
    // -----
    MCurrentTimerTick += 1;
    MTimerBlocked = false;
}

void SAT_WidgetWindow::handlePainting(SAT_PaintContext* AContext)
{
    uint32_t count = 0;
    SAT_Widget* widget;
    while (MWidgetPaintQueue.read(&widget))
    {
        count += 1;
        //widget->paintChildren(AContext);
        widget->on_widget_paint(AContext);
    }
    // SAT.STATISTICS.report_WindwPaintQueue(count);
}

//------------------------------
//
//------------------------------

/*
    [TIMER-THREAD]
*/

void SAT_WidgetWindow::on_timer_listener_update(SAT_Timer* ATimer, double ADelta)
{
    if (MTimerBlocked)
    {
        // double time = SAT_GetTime();
        // SAT.STATISTICS.report_WindowTimerBlocked(time);
        return;
    }
    sendClientMessage(SAT_WINDOW_USER_MESSAGE_TIMER,0);
};

void SAT_WidgetWindow::on_window_paint(SAT_PaintContext* AContext, bool ABuffered)
{
    // SAT_Window::on_window_paint(AContext,ABuffered);
    handlePainting(AContext);
}

//------------------------------
// base window
//------------------------------

void SAT_WidgetWindow::on_window_show()
{
    uint32_t num = getNumChildren();
    for (uint32_t i=0; i<num; i++)
    {
        SAT_Widget* child = getChild(i);
        child->on_widget_show(this);
    }
    MWindowTimer->start(SAT_WINDOW_TIMER_MS);
}

void SAT_WidgetWindow::on_window_hide()
{
    if (MWindowTimer->isRunning()) MWindowTimer->stop();
    uint32_t num = getNumChildren();
    for (uint32_t i=0; i<num; i++)
    {
        SAT_Widget* child = getChild(i);
        child->on_widget_hide(this);
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
    [GUI THREAD]
*/

void SAT_WidgetWindow::on_window_timer(uint32_t ATimerId, double ADelta)
{
    handleTimer(ATimerId,ADelta);
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
    widget value has changed..
    if it is connected to a parameter, we notify the editor (window_listener)
*/

void SAT_WidgetWindow::do_widget_update(SAT_Widget* AWidget, uint32_t AMode, uint32_t AIndex)
{
    void* parameter = AWidget->getParameter();
    if (MListener && parameter)
    {
        MListener->do_widget_update(AWidget);
    }
}

void SAT_WidgetWindow::do_widget_realign(SAT_Widget* AWidget, uint32_t AMode, uint32_t AIndex)
{
    MWidgetRealignQueue.write(AWidget);
}

void SAT_WidgetWindow::do_widget_redraw(SAT_Widget* AWidget, uint32_t AMode, uint32_t AIndex)
{
    MWidgetRedrawQueue.write(AWidget);
}

void SAT_WidgetWindow::do_widget_tween(SAT_Widget* AWidget, SAT_TweenChain* AChain)
{
    MTweenManager.appendChain(AChain);
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
