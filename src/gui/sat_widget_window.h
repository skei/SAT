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
typedef SAT_SPSCQueue<SAT_BaseWidget*,SAT_QUEUE_SIZE_REALIGN>   SAT_WidgetRealignQueue;
typedef SAT_SPSCQueue<SAT_BaseWidget*,SAT_QUEUE_SIZE_REDRAW>    SAT_WidgetRedrawQueue;
typedef SAT_SPSCQueue<SAT_BaseWidget*,SAT_QUEUE_SIZE_PAINT>     SAT_WidgetPaintQueue;

//typedef SAT_Array<SAT_Widget*> SAT_WidgetArray;

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_WidgetWindow
: public SAT_Window
, public SAT_WidgetOwner
//, public SAT_BaseWidget
, public SAT_Widget
, public SAT_TimerListener
{
    public:
        SAT_WidgetWindow(uint32_t AWidth, uint32_t AHeight, intptr_t AParent=0);
        virtual ~SAT_WidgetWindow();
    // public:
    //     virtual sat_coord_t getWindowScale();
    public:
        virtual void        setListener(SAT_WindowListener* AListener);
        virtual void        setHintWidget(SAT_BaseWidget* AWidget);
        virtual void        appendTimerWidget(SAT_BaseWidget* AWidget);
        virtual void        removeTimerWidget(SAT_BaseWidget* AWidget);
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
        SAT_Painter*        do_widget_owner_get_painter(SAT_BaseWidget* AWidget) override;
        uint32_t            do_widget_owner_get_width(SAT_BaseWidget* AWidget) override;
        uint32_t            do_widget_owner_get_height(SAT_BaseWidget* AWidget) override;
        sat_coord_t         do_widget_owner_get_scale(SAT_BaseWidget* AWidget) override;
        bool                do_widget_owner_register_timer(SAT_BaseWidget* AWidget) override;
        bool                do_widget_owner_unregister_timer(SAT_BaseWidget* AWidget) override;
    public:
        void                do_widget_update(SAT_BaseWidget* AWidget, uint32_t AMode=SAT_WIDGET_UPDATE_VALUE, uint32_t AIndex=0) override;
        void                do_widget_realign(SAT_BaseWidget* AWidget, uint32_t AMode=SAT_WIDGET_REALIGN_PARENT, uint32_t AIndex=0) override;
        void                do_widget_redraw(SAT_BaseWidget* AWidget, uint32_t AMode=SAT_WIDGET_REDRAW_SELF, uint32_t AIndex=0) override;
        void                do_widget_tween(SAT_BaseWidget* AWidget, SAT_TweenChain* AChain) override;
        void                do_widget_notify(SAT_BaseWidget* AWidget, uint32_t AType, int32_t AValue) override;
        void                do_widget_hint(SAT_BaseWidget* AWidget, uint32_t AType, const char* AHint) override;
        void                do_widget_modal(SAT_BaseWidget* AWidget) override;
        void                do_widget_cursor(SAT_BaseWidget* AWidget, uint32_t ACursor) override;
        void                do_widget_capture_mouse(SAT_BaseWidget* AWidget) override;
        void                do_widget_capture_keyboard(SAT_BaseWidget* AWidget) override;
    private:
        SAT_WindowListener*     MListener               = nullptr;  // aka editor
        SAT_TweenManager        MTweenManager           = {};       // widget animations
        SAT_Timer*              MWindowTimer            = nullptr;  // timer
        SAT_BaseWidgetArray     MTimerWidgets           = {};       // array of widgets that want timer ticks
        uint32_t                MCurrentTimerTick       = 0;        // increasing tick counter
        sat_atomic_bool_t       MTimerBlocked           {false};    // if this is true, timer handler returns immediately
    private:
     // SAT_WidgetUpdateQueue   MWidgetUpdateQueue      = {};       // value changed
        SAT_WidgetRealignQueue  MWidgetRealignQueue     = {};       // needs to be realigned
        SAT_WidgetRedrawQueue   MWidgetRedrawQueue      = {};       // needs to be redrawn
        SAT_WidgetPaintQueue    MWidgetPaintQueue       = {};       // will be painted
    private:
        SAT_BaseWidget*         MCapturedKeyWidget      = nullptr;  // send key events directoy to this
        SAT_BaseWidget*         MCapturedMouseWidget    = nullptr;  // send mouse events directly to this
        SAT_BaseWidget*         MClickedWidget          = nullptr;  // clicked widget
        SAT_BaseWidget*         MDragWidget             = nullptr;  // drag'n'drop, start widget (drag from)
        SAT_BaseWidget*         MHintWidget             = nullptr;  // widget receiving hints
        SAT_BaseWidget*         MHoverWidget            = nullptr;  // currently hovering over
        SAT_BaseWidget*         MModalWidget            = nullptr;  // exclusive widget, all other widgets ignored
    private:
     // bool                    MNeedFullRealignment    = false;    // force full alignment (all widgets)
        bool                    MNeedFullRepaint        = false;    // force full repaint (all widgets)
        sat_coord_t             MWindowScale            = 1.0;
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
};

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

// sat_coord_t SAT_WidgetWindow::getWindowScale()
// {
//     return MWindowScale;
// }

//------------------------------
//
//------------------------------

void SAT_WidgetWindow::setListener(SAT_WindowListener* AListener)
{
    MListener = AListener;
}

void SAT_WidgetWindow::setHintWidget(SAT_BaseWidget* AWidget)
{
    MHintWidget = AWidget;
}

void SAT_WidgetWindow::appendTimerWidget(SAT_BaseWidget* AWidget)
{
    SAT_Assert(AWidget);
    MTimerWidgets.append(AWidget);
}

void SAT_WidgetWindow::removeTimerWidget(SAT_BaseWidget* AWidget)
{
    SAT_Assert(AWidget);
    MTimerWidgets.remove(AWidget);
}

/*
    if SAT_WINDOW_REDIRECT_TIMER_TO_GUI_THREAD is defined, this is called
    on the gui thread (x11 event handler), otherwise it's called directly
    from the timer callback (timer thread)..

    TODO: widget redrawing originating from audio automation & modulation
    (MWidgetUpdateQueue?)
*/

void SAT_WidgetWindow::handleTimer(uint32_t ATimerId, double ADelta)
{

    // MTimerDelta += ADelta;
    // if (MIsClosing)  return;
    // if (MIsPainting) return;

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
    SAT_BaseWidget* widget;
    while (MWidgetRealignQueue.read(&widget))
    {
        count += 1;
        // widget->realignChildren();
        // MWidgetRedrawQueue.write(widget); // called during realignment..
        widget->on_widget_realign(SAT_WIDGET_REALIGN_CHILDREN,0);
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
    if (MNeedFullRepaint)
    {
        // AContext->update_rect = MRect;
        uint32_t num = getNumChildren();
        for (uint32_t i=0; i<num; i++)
        {
            SAT_BaseWidget* child = getChild(i);
            child->on_widget_paint(AContext);
        }
        // SAT.STATISTICS.report_WindowPaintAll();
        MNeedFullRepaint = false;
    }
    else
    {
        uint32_t count = 0;
        SAT_BaseWidget* widget;
        while (MWidgetPaintQueue.read(&widget))
        {
            count += 1;
            //widget->paintChildren(AContext);
            widget->on_widget_paint(AContext);
        }
        // SAT.STATISTICS.report_WindowPaintQueue(count);
    }
}

/*
    double calcScale(int32_t AWidth, int32_t AHeight)
    {
        double scale = 1.0;
        if ((MInitialWidth > 0) && (MInitialHeight > 0))
        {
            double xscale = (double)AWidth / (double)MInitialWidth;
            double yscale = (double)AHeight / (double)MInitialHeight;
            if (xscale < yscale) scale = xscale;
            else scale =  yscale;
        }
        return scale;
    }
*/


/*
    void updateHover(uint32_t AXpos, uint32_t AYpos, uint32_t ATime)
    {
        if (MRootWidget)
        {
            SAT_Widget* hover;
            if (MModalWidget) hover = MModalWidget->findWidget(AXpos,AYpos);
            else hover = MRootWidget->findWidget(AXpos,AYpos);
            if (hover)
            {
                if (hover != MHoverWidget)
                {
                    if (MHoverWidget) MHoverWidget->on_Widget_leave(hover,AXpos,AYpos,ATime);
                    hover->on_Widget_enter(MHoverWidget,AXpos,AYpos,ATime);
                    MHoverWidget = hover;
                }
            }
            else
            {
                if (MHoverWidget) MHoverWidget->on_Widget_leave(nullptr,AXpos,AYpos,ATime);
                MHoverWidget = nullptr;
            }
        }
    }
*/

// will be called just before renderer.beginRendering()
// void preRender(uint32_t AWidth, uint32_t AHeight)
// {
// }

// will be called just after renderer.endRendering()
// void postRender()
// {
// }

// will be called just before painter.beginPainting()
// void prePaint(uint32_t AWidth, uint32_t AHeight)
// {
// }

// will be called just after painter.endPainting()
// void postPaint()
// {
// }

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
    #ifdef SAT_WINDOW_REDIRECT_TIMER_TO_GUI_THREAD
        sendClientMessage(SAT_WINDOW_USER_MESSAGE_TIMER,0);
    #else
        // this is dagerous! handleTimer reads from the
        // MTimerWidgets array, calls MTweenManager, writes to MRedrawQueue..
        handleTimer(ATimerId,ADelta);
    #endif
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
    setOwner(this);
    uint32_t num = getNumChildren();
    for (uint32_t i=0; i<num; i++)
    {
        SAT_BaseWidget* child = getChild(i);
        child->on_widget_show(this);
    }
    realignChildren();
    MNeedFullRepaint = true;
    MWindowTimer->start(SAT_WINDOW_TIMER_MS);
}

void SAT_WidgetWindow::on_window_hide()
{
    setOwner(nullptr);
    if (MWindowTimer->isRunning()) MWindowTimer->stop();
    uint32_t num = getNumChildren();
    for (uint32_t i=0; i<num; i++)
    {
        SAT_BaseWidget* child = getChild(i);
        child->on_widget_hide(this);
    }
}

void SAT_WidgetWindow::on_window_move(int32_t AXpos, int32_t AYpos)
{
}

void SAT_WidgetWindow::on_window_resize(uint32_t AWidth, uint32_t AHeight)
{
    SAT_Window::windowResize(AWidth,AHeight);
    MRect = SAT_Rect(AWidth,AHeight);
    realignChildren();
    MNeedFullRepaint = true;
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
    //MHoverWidget = findHoverWidget();
    MHoverWidget = findWidgetAt(AXpos,AYpos,true);
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
    //MHoverWidget = findHoverWidget();
    MHoverWidget = findWidgetAt(AXpos,AYpos,true);
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

SAT_Painter* SAT_WidgetWindow::do_widget_owner_get_painter(SAT_BaseWidget* AWidget)
{
    //return MPainter;
    return getPainter();
}

uint32_t SAT_WidgetWindow::do_widget_owner_get_width(SAT_BaseWidget* AWidget)
{
    return getWidth();
}

uint32_t SAT_WidgetWindow::do_widget_owner_get_height(SAT_BaseWidget* AWidget)
{
    return getWidth();
}

sat_coord_t SAT_WidgetWindow::do_widget_owner_get_scale(SAT_BaseWidget* AWidget)
{
    return MWindowScale;
}

/*
    if window is open (after show() has been called),
    the MTimerWidgets array might be read in timer-thread!!!
    either register the timers _before_ the window is opened,
    or guard with lock/mutex!
*/

bool SAT_WidgetWindow::do_widget_owner_register_timer(SAT_BaseWidget* AWidget)
{
    MTimerWidgets.append(AWidget);
    return true;
}

/*
    see register_timer()
*/

bool SAT_WidgetWindow::do_widget_owner_unregister_timer(SAT_BaseWidget* AWidget)
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

void SAT_WidgetWindow::do_widget_update(SAT_BaseWidget* AWidget, uint32_t AMode, uint32_t AIndex)
{
    void* parameter = AWidget->getParameter();
    if (MListener && parameter)
    {
        MListener->do_widget_update(AWidget);
    }
}

/*
    void on_WidgetListener_realign(SAT_Widget* AWidget, uint32_t AMode=SAT_WIDGET_REALIGN_SELF) override
    {
        #ifdef SAT_WINDOW_QUEUE_WIDGETS
            switch (AMode)
            {
                case SAT_WIDGET_REALIGN_SELF:
                {
                    MQueues.queueRealign(AWidget);
                    //MQueues.queueRedraw(AWidget);
                    break;
                }
                case SAT_WIDGET_REALIGN_PARENT:
                {
                    SAT_Widget* parent = AWidget->getParent();
                    if (parent)
                    {
                        MQueues.queueRealign(parent);
                        //MQueues.queueRedraw(parent);
                    }
                    break;
                }
                case SAT_WIDGET_REALIGN_ROOT:
                {
                    break;
                }
            }
        #else // ! SAT_WINDOW_QUEUE_WIDGETS
            switch (AMode)
            {
                case SAT_WIDGET_REALIGN_SELF:
                {
                    AWidget->realignChildren();
                    AWidget->do_Widget_redraw(AWidget);
                    break;
                }
                case SAT_WIDGET_REALIGN_PARENT:
                {
                    SAT_Widget* parent = AWidget->getParent();
                    if (parent)
                    {
                        parent->realignChildren();
                        parent->do_Widget_redraw(parent);
                    }
                    break;
                }
                case SAT_WIDGET_REALIGN_ROOT:
                {
                    break;
                }
            }
        #endif // SAT_WINDOW_QUEUE_WIDGETS
    }
*/

void SAT_WidgetWindow::do_widget_realign(SAT_BaseWidget* AWidget, uint32_t AMode, uint32_t AIndex)
{
    MWidgetRealignQueue.write(AWidget);
}

/*
    for buffered windows, which doesn't redraw everything from the root down:

    we might want to have some way to specify certain widgets that might be
    drawn on top of all the others (see sa_demo, the animated splines)..
    currently, the widget system is designed so that child widgets is clipped to,
    and always inside it's parent widgets..
    when a widget is being redrawn, we iterate upwards in the hierarchy,
    to find the topmost widget/parent set  as opaque (entirely fills its rect),
    ultimately reaching the root widget..
    (if all widgets are kept as opaque (the default), the entire window will be redrawn)

    if there is a widget other than the parent overlaying the widget, it is ignored..
    animated widgets will then be redrawn next frame (when itself sends a redraw message)..
    resulting in flickering..

    and possibly:
    because of clipping being ints, and painting being doubles (fractional pixels),
    clipping can flicker, half-pixels being redrawn, etc..
    needs testing and checking!

    MRaisedWidget, MFrontWidget, MUpperWidget?
*/

/*

    void on_WidgetListener_redraw(SAT_Widget* AWidget, uint32_t AIndex=0, uint32_t AMode=SAT_WIDGET_REDRAW_SELF)
    {
        #ifdef SAT_WINDOW_QUEUE_WIDGETS
            #ifdef SAT_WINDOW_BUFFERED
                switch (AMode)
                {
                    case SAT_WIDGET_REDRAW_SELF:
                    {
                        if (AWidget->State.opaque) MQueues.queueRedraw(AWidget);
                        else
                        {
                            SAT_Widget* opaque_parent = AWidget->findOpaqueParent();
                            if (opaque_parent) MQueues.queueRedraw(opaque_parent);
                            else MQueues.queueRedraw(AWidget);
                        }
                        break;
                    }
                    case SAT_WIDGET_REDRAW_PARENT:
                    {
                        SAT_Widget* widget = AWidget->getParent();
                        if (widget)
                        {
                            if (widget->State.opaque) MQueues.queueRedraw(widget);
                            else
                            {
                                SAT_Widget* opaque_parent = widget->findOpaqueParent();
                                if (opaque_parent) MQueues.queueRedraw(opaque_parent);
                                else MQueues.queueRedraw(widget);
                            }
                        }
                        break;
                    }
                    case SAT_WIDGET_REDRAW_ROOT:
                    {
                        MQueues.queueRedraw(MRootWidget);
                        break;
                    }
                } // switch AMode
            #else // SAT_WINDOW_BUFFERED
                MQueues.queueRedraw(MRootWidget);
            #endif // SAT_WINDOW_BUFFERED
        // TODO: draw 'always overlay' widgets? (not SAT_OverlayWidget,
        // which is meant for menus, etc, and is normally inactive)..
        #else // SAT_WINDOW_QUEUE_WIDGETS
            SAT_Rect rect = AWidget->getRect();
            invalidate(rect.x,rect.y,rect.w,rect.h);
        #endif
    }
*/

void SAT_WidgetWindow::do_widget_redraw(SAT_BaseWidget* AWidget, uint32_t AMode, uint32_t AIndex)
{
    MWidgetRedrawQueue.write(AWidget);
}

void SAT_WidgetWindow::do_widget_tween(SAT_BaseWidget* AWidget, SAT_TweenChain* AChain)
{
    MTweenManager.appendChain(AChain);
}

void SAT_WidgetWindow::do_widget_notify(SAT_BaseWidget* AWidget, uint32_t AType, int32_t AValue)
{
}

void SAT_WidgetWindow::do_widget_hint(SAT_BaseWidget* AWidget, uint32_t AType, const char* AHint)
{
    if (MHintWidget) MHintWidget->on_widget_hint(AType,AHint);
}

void SAT_WidgetWindow::do_widget_modal(SAT_BaseWidget* AWidget)
{
    MModalWidget = AWidget;
}

/*
    void on_WidgetListener_set_cursor(SAT_Widget* AWidget, int32_t ACursor)
    {
        switch(ACursor)
        {
            case SAT_CURSOR_LOCK:
                lockMouseCursor();
                break;
            case SAT_CURSOR_UNLOCK:
                unlockMouseCursor();
                break;
            case SAT_CURSOR_SHOW:  
                showMouseCursor();
                setMouseCursorShape(MMouseCurrentCursor);
                break;
            case SAT_CURSOR_HIDE:
                hideMouseCursor();
                break;
            default:
                if (ACursor != MMouseCurrentCursor)
                {
                    setMouseCursorShape(ACursor);
                    MMouseCurrentCursor = ACursor;
                }
        }
    }
*/

void SAT_WidgetWindow::do_widget_cursor(SAT_BaseWidget* AWidget, uint32_t ACursor)
{
}

void SAT_WidgetWindow::do_widget_capture_mouse(SAT_BaseWidget* AWidget)
{
}

void SAT_WidgetWindow::do_widget_capture_keyboard(SAT_BaseWidget* AWidget)
{
}
