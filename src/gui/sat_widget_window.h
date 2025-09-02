#pragma once

/*
    note to self:
    remember to keep the widget part in sync with the window parts (size, rect, etc)

    consider:
        multiple layers of widgets..
            background that doesn't change (buffered, just blit)
            popup boxes, menus, dialog boxes, tooltips, ..
*/

#include "base/sat_base.h"
#include "base/system/sat_timer.h"
#include "gui/sat_gui_base.h"
#include "gui/sat_painter.h"
#include "gui/sat_renderer.h"
#include "gui/sat_tween_manager.h"
#include "gui/sat_widget.h"
#include "gui/sat_window.h"
#include "gui/skin/sat_default_skin.h"

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
        virtual void        handleTimer(uint32_t ATimerId, double ADelta, bool AInTimerThread=false);
        virtual void        paintQueuedWidgets(SAT_PaintContext* AContext);
        virtual sat_coord_t calcScale(uint32_t ANewWidth, uint32_t ANewHeight, uint32_t AInitialWidth, uint32_t AInitialHeight);
        virtual void        updateHover(int32_t AXpos, int32_t AYpos, uint32_t ATime);

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

        // void                on_widget_show(SAT_WidgetOwner* AOwner) override;
        // void                on_widget_hide(SAT_WidgetOwner* AOwner) override;
        // void                on_widget_paint(SAT_PaintContext* AContext, uint32_t AMode=SAT_WIDGET_PAINT_NORMAL, uint32_t AIndex=0) override;
        // void                on_widget_pre_paint(SAT_PaintContext* AContext, uint32_t AMode=SAT_WIDGET_PAINT_NORMAL, uint32_t AIndex=0) override;
        // void                on_widget_post_paint(SAT_PaintContext* AContext, uint32_t AMode=SAT_WIDGET_PAINT_NORMAL, uint32_t AIndex=0) override;
        // void                on_widget_realign(uint32_t AMode=SAT_WIDGET_REALIGN_CHILDREN, uint32_t AIndex=0) override;
        // SAT_Rect            on_widget_pre_align(SAT_Rect ARect, uint32_t AMode=SAT_WIDGET_REALIGN_CHILDREN, uint32_t AIndex=0) override;
        // SAT_Rect            on_widget_post_align(SAT_Rect ARect, uint32_t AMode=SAT_WIDGET_REALIGN_CHILDREN, uint32_t AIndex=0) override;
        // void                on_widget_timer(uint32_t ATimerId, double ADelta) override;
        // void                on_widget_tween(uint32_t AId, uint32_t AType, uint32_t ANumValues, double* AValues) override;
        // void                on_widget_hint(uint32_t AType, const char* AHint) override;
        // void                on_widget_mouse_click(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATime) override;
        // void                on_widget_mouse_dbl_click(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATime) override;
        // void                on_widget_mouse_release(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATime) override;
        // void                on_widget_mouse_move(int32_t AXpos, int32_t AYpos, uint32_t AState, uint32_t ATime) override;
        // void                on_widget_key_press(uint32_t AKey, uint32_t AChar, uint32_t AState, uint32_t ATime) override;
        // void                on_widget_key_release(uint32_t AKey, uint32_t AChar, uint32_t AState, uint32_t ATime) override;
        // void                on_widget_mouse_enter(SAT_BaseWidget* AFrom, int32_t AXpos, int32_t AYpos, uint32_t ATime) override;
        // void                on_widget_mouse_leave(SAT_BaseWidget* ATo, int32_t AXpos, int32_t AYpos, uint32_t ATime) override;

    public:

        void                do_widget_update(SAT_BaseWidget* AWidget, uint32_t AIndex=0) override;
        void                do_widget_realign(SAT_BaseWidget* AWidget) override;
        void                do_widget_redraw(SAT_BaseWidget* AWidget) override;
        void                do_widget_tween(SAT_BaseWidget* AWidget, SAT_TweenChain* AChain) override;
        void                do_widget_notify(SAT_BaseWidget* AWidget, uint32_t AType, int32_t AValue) override;
        void                do_widget_hint(SAT_BaseWidget* AWidget, uint32_t AType, const char* AHint) override;
        void                do_widget_modal(SAT_BaseWidget* AWidget) override;
        void                do_widget_cursor(SAT_BaseWidget* AWidget, uint32_t ACursor) override;
        void                do_widget_capture_mouse(SAT_BaseWidget* AWidget) override;
        void                do_widget_capture_keyboard(SAT_BaseWidget* AWidget) override;

    private:

        SAT_WindowListener*     MListener               = nullptr;          // aka editor
        SAT_TweenManager        MTweenManager           = {};               // widget animations
        SAT_Timer*              MWindowTimer            = nullptr;          // timer
        SAT_BaseWidgetArray     MTimerWidgets           = {};               // array of widgets that want timer ticks
        uint32_t                MCurrentTimerTick       = 0;                // increasing tick counter
        sat_atomic_bool_t       MTimerBlocked           {false};            // if this is true, timer handler returns immediately
        sat_atomic_bool_t       MWindowIsClosing        {false};            // if this is true, timer handler returns immediately

    private:

     // SAT_WidgetUpdateQueue   MWidgetUpdateQueue      = {};               // value changed
        SAT_WidgetRealignQueue  MWidgetRealignQueue     = {};               // needs to be realigned
        SAT_WidgetRedrawQueue   MWidgetRedrawQueue      = {};               // needs to be redrawn
        SAT_WidgetPaintQueue    MWidgetPaintQueue       = {};               // will be painted

    private:

        SAT_BaseWidget*         MCapturedKeyWidget      = nullptr;          // send key events directoy to this
        SAT_BaseWidget*         MCapturedMouseWidget    = nullptr;          // send mouse events directly to this
        uint32_t                MCapturedMouseButton    = SAT_BUTTON_NONE;  // button that caused the capture
        SAT_BaseWidget*         MDragWidget             = nullptr;          // drag'n'drop, start widget (drag from)
        SAT_BaseWidget*         MHintWidget             = nullptr;          // widget receiving hints
        SAT_BaseWidget*         MHoverWidget            = nullptr;          // currently hovering over
        SAT_BaseWidget*         MModalWidget            = nullptr;          // exclusive widget, all other widgets ignored
        bool                    MMouseInsideWindow      = false;

    private:

     // bool                    MNeedFullRealignment    = false;            // force full alignment (all widgets)
        bool                    MNeedFullRepaint        = false;            // force full repaint (all widgets)
        sat_coord_t             MWindowScale            = 1.0;
        SAT_DefaultSkin         MDefaultSkin            = {};
     // bool                    MClearBackground        = true;
     // SAT_Color               MBackgroundColor        = SAT_Black;



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
    MWidgetTypeName         = "SAT_WidgetWindow";
    Recursive.opaque_parent = this;
    MSkin                   = &MDefaultSkin;
    MWindowTimer            = new SAT_Timer(this);
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
    TODO: widget redrawing originating from audio automation & modulation
    (MWidgetUpdateQueue?)

    AInTimerThread is true if we're called from a timer, or false if we
    have redirected it to the gui thread..
*/

void SAT_WidgetWindow::handleTimer(uint32_t ATimerId, double ADelta, bool AInTimerThread)
{
    // we don't want any new timer tickes until we finished processing this one..
    // (we set this in the timer handler itself, set to false at the end of this func)
    //MTimerBlocked = true;

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
        widget->on_widget_realign();
    }
    // SAT.STATISTICS.report_WindwRealignQueue(count);

    // ----- redraw queue -----
    
    count = 0;
    SAT_Rect rect;
    while (MWidgetRedrawQueue.read(&widget))
    {
        count += 1;
        rect.combine(widget->Recursive.rect);
        MWidgetPaintQueue.write(widget);
    }
    // SAT.STATISTICS.report_WindwRedrawQueue(count,rect);

    // ----- invalidate -----

    if (rect.isNotEmpty())
    {
        //SAT_PRINT("invalidate\n");
        invalidate(rect.x,rect.y,rect.w,rect.h);
    }

    // -----
    
    MCurrentTimerTick += 1;
    MTimerBlocked = false;
}

/*
    MNeedFullRepaint set in on_window_show and on_window_resize
*/

void SAT_WidgetWindow::paintQueuedWidgets(SAT_PaintContext* AContext)
{

    // SAT_Painter* painter = AContext->painter;
    // uint32_t screenwidth = getWidth();
    // uint32_t screenheight = getHeight();
    // painter->setClipRect(SAT_Rect(0,0,screenwidth,screenheight));
    // painter->setClip(SAT_Rect(0,0,screenwidth,screenheight));

    uint32_t paint_count = 0;
    uint32_t paint_skipped = 0;
    SAT_BaseWidget* widget = nullptr;

    if (MNeedFullRepaint)
    {

        // if (MClearBackground)
        // {
        //     SAT_Assert(AContext->painter);
        //     AContext->painter->setFillColor(MBackgroundColor);
        //     AContext->painter->fillRect(Recursive.rect);
        // }

        //SAT_PRINT("full repaint\n");
        uint32_t num = getNumChildren();
        for (uint32_t i=0; i<num; i++)
        {
            widget = getChild(i);
            widget->on_widget_paint(AContext);
            widget->UpdateState.last_painted = AContext->current_frame;
        }
        // flush queue, so we don't re-draw them next time..
        while (MWidgetPaintQueue.read(&widget)) { paint_count += 1; }

        // SAT.STATISTICS.report_WindowPaintAll();
        MNeedFullRepaint = false;
    }
    else
    {
        while (MWidgetPaintQueue.read(&widget))
        {
            if (widget->UpdateState.last_painted != AContext->current_frame)
            {

                //SAT_PRINT("painting widget %i\n",paint_count);
                widget->pushRecursiveClip(AContext);
                widget->on_widget_paint(AContext);
                widget->popClip(AContext);
                paint_count += 1;
                widget->UpdateState.last_painted = AContext->current_frame;
            }
            else
            {
                paint_skipped += 1;
            }
        }
        // SAT.STATISTICS.report_WindowPaintQueue(paint_count,paint_skipped);
    }

    // painter->resetClip();

}

sat_coord_t SAT_WidgetWindow::calcScale(uint32_t ANewWidth, uint32_t ANewHeight, uint32_t AInitialWidth, uint32_t AInitialHeight)
{
    sat_coord_t scale = 1.0;
    if ((AInitialWidth > 0) && (AInitialHeight > 0))
    {
        sat_coord_t xscale = (sat_coord_t)ANewWidth  / (sat_coord_t)AInitialWidth;
        sat_coord_t yscale = (sat_coord_t)ANewHeight / (sat_coord_t)AInitialHeight;
        if (xscale < yscale) scale = xscale;
        else scale =  yscale;
    }
    return scale;
}

void SAT_WidgetWindow::updateHover(int32_t AXpos, int32_t AYpos, uint32_t ATime)
{
    SAT_BaseWidget* hover = nullptr;

    int32_t winw = (int32_t)getWidth();
    int32_t winh = (int32_t)getHeight();
    if ( (AXpos >= 0) && (AXpos < winw) && (AYpos >= 0) && (AYpos < winh) ) MMouseInsideWindow = true;
    else MMouseInsideWindow = false;
    //SAT_PRINT("inside window: %i\n",MMouseInsideWindow);

    if (MMouseInsideWindow)
    {
        if (MModalWidget) hover = MModalWidget->findChildAt(AXpos,AYpos);
        else hover = findChildAt(AXpos,AYpos);
        // hover        = new hover
        // MHoverWidget = previous hover (if null = just entered window)
        if (!MHoverWidget)
        {
            // we have just entered the window, didn't leave anything            
            SAT_PRINT("entering: %s %s\n",hover->getWidgetTypeName(), hover->getName());
            hover->State.hovering = true;
            hover->on_widget_mouse_enter(MHoverWidget,AXpos,AYpos,ATime);
            MHoverWidget = hover;
        }
        else
        {
            // are we hovering over the same, or a different widget?
            if (hover != MHoverWidget)
            {
                // differemt, leave the old, enter the new
                SAT_PRINT("leaving: %s %s\n",MHoverWidget->getWidgetTypeName(),MHoverWidget->getName());
                MHoverWidget->State.hovering = false;
                MHoverWidget->on_widget_mouse_leave(hover,AXpos,AYpos,ATime);
                SAT_PRINT("entering: %s %s\n",hover->getWidgetTypeName(), hover->getName());
                hover->State.hovering = true;
                hover->on_widget_mouse_enter(MHoverWidget,AXpos,AYpos,ATime);
                MHoverWidget = hover;
            }
            else
            {
                // the same, don't do anything..
            }
        }
    }
    else
    {
        // we are outside the window, but we might get move mesages
        // because we captured a widget..
        // don't set new MHoverWidget
    }
}

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

// [TIMER THREAD]
void SAT_WidgetWindow::on_timer_listener_update(SAT_Timer* ATimer, double ADelta)
{
    if (MTimerBlocked)
    {
        // double time = SAT_GetTime();
        // SAT.STATISTICS.report_WindowTimerBlocked(time);
        return;
    }
    if (MWindowIsClosing)
    {
        // double time = SAT_GetTime();
        // SAT.STATISTICS.report_WindowTimerWhen WindowIsClosing(time);
        return;
    }

    // set to false at the end of handleTimer()
    MTimerBlocked = true;

    #ifdef SAT_WINDOW_REDIRECT_TIMER_TO_GUI_THREAD
        sendClientMessage(SAT_WINDOW_USER_MESSAGE_TIMER,0);
        // see on_window_timer(), which will call handleTimer()...
    #else
        // don't do this!
        // this is dagerous! handleTimer reads from the
        // MTimerWidgets array, calls MTweenManager, writes to MRedrawQueue..
        handleTimer(ATimerId,ADelta,true);
    #endif
};

void SAT_WidgetWindow::on_window_paint(SAT_PaintContext* AContext, bool ABuffered)
{
    // SAT_Window::on_window_paint(AContext,ABuffered);
    paintQueuedWidgets(AContext);
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
    MNeedFullRepaint = true;
    realignChildren();
    MWindowIsClosing = false;
    MTimerBlocked = false;
    MWindowTimer->start(SAT_WINDOW_TIMER_MS);
}

void SAT_WidgetWindow::on_window_hide()
{
    MWindowIsClosing = true;
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
    MWindowScale = calcScale(AWidth,AHeight,MInitialRect.w,MInitialRect.h);
    //SAT_PRINT("scale: %.3f\n",MWindowScale);
    SAT_Window::windowResize(AWidth,AHeight);
    Recursive.rect = SAT_Rect(AWidth,AHeight);
    realignChildren();
    MNeedFullRepaint = true;
}

// void SAT_WidgetWindow::on_window_paint(int32_t AXpos, int32_t AYpos, uint32_t AWidth, uint32_t AHeight)
// {
// }

/*
    TODO:
        if Options.drag_drop - MMDragDropWidget = this
        (or widget must initiate it with do_widget_start_drag()
*/

void SAT_WidgetWindow::on_window_mouse_click(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATime)
{
    //SAT_Assert(MHoverWidget);
    if (MCapturedMouseWidget)
    {
        // a widget is captured, and we clicked another button
        SAT_PRINT("clicked another button -> captured: %s\n",MCapturedMouseWidget->getName());
        MCapturedMouseWidget->on_widget_mouse_click(AXpos,AYpos,AButton,AState,ATime);
    }
    else if (MHoverWidget)
    {
        if (MHoverWidget->Options.auto_capture)
        {
            if ((AButton == SAT_BUTTON_LEFT) || (AButton == SAT_BUTTON_MIDDLE) || (AButton == SAT_BUTTON_RIGHT))
            {
                SAT_PRINT("capture widget: %s\n",MHoverWidget->getName());
                MCapturedMouseWidget = MHoverWidget;
                MCapturedMouseButton = AButton;
            }
        }
        SAT_PRINT("mouse click: %s\n",MHoverWidget->getName());
        MHoverWidget->on_widget_mouse_click(AXpos,AYpos,AButton,AState,ATime);
    }
    else
    {
        //SAT_PRINT("MHoverWidget = null.. MMouseInsideWindow = %s -> ignore\n",MMouseInsideWindow?"true":"false");
        // we are probably outside of the window..
        // ignore..
    }
}

/*
    TODO:
        if MMDragDropWidget, ask hover widget if it accepts dropping (data)
        (or did we do that in mouse-move/enter? set MHoverWidgetAcceptsDrop?)
        if yes, drop(data), tell captured widget about it?
*/

void SAT_WidgetWindow::on_window_mouse_release(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATime)
{
    if (MCapturedMouseWidget)
    {
        SAT_PRINT("mouse release -> captured: %s\n",MCapturedMouseWidget->getName());
        MCapturedMouseWidget->on_widget_mouse_release(AXpos,AYpos,AButton,AState,ATime);
        if (MCapturedMouseButton == AButton)
        {
            SAT_PRINT("un-capture: %s\n",MCapturedMouseWidget->getName());
            MCapturedMouseWidget = nullptr;
        }
    }
}

/*
    TODO:
        if MMDragDropWidget, check if hover widget accepts dropping (data)
        yes : set mouse cursor accept, else set mouse cursor not-accept
        (tell captured widget about it?)
*/

void SAT_WidgetWindow::on_window_mouse_move(int32_t AXpos, int32_t AYpos, uint32_t AState, uint32_t ATime)
{
    updateHover(AXpos,AYpos,ATime);
    if (MCapturedMouseWidget)
    {
        SAT_PRINT("mouse move -> captured: %s\n",MCapturedMouseWidget->getName());
        MCapturedMouseWidget->on_widget_mouse_move(AXpos,AYpos,AState,ATime);
        // if (is_dragging)
        // {
        // }
    }
    else 
    {
        //SAT_Assert(MHoverWidget);
        if (MHoverWidget)
        {
            if (MHoverWidget->Options.want_hover_events)
            {
                SAT_PRINT("mouse move -> want hover: %s\n",MHoverWidget->getName());
                MHoverWidget->on_widget_mouse_move(AXpos,AYpos,AState,ATime);
            }
        }
        else
        {
            //SAT_PRINT("MCapturedMouseWidget = null, MHoverWidget = null.. MMouseInsideWindow = %s -> ignore\n",MMouseInsideWindow?"true":"false");
            // probably outside of the window (hoverwidget = null), ignore
        }
    }
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
    updateHover(AXpos,AYpos,ATime);
}

void SAT_WidgetWindow::on_window_mouse_leave(int32_t AXpos, int32_t AYpos, uint32_t ATime)
{
    //SAT_Assert(MHoverWidget);
    if (MHoverWidget)
    {
        SAT_PRINT("leaving: %s %s\n",MHoverWidget->getWidgetTypeName(), MHoverWidget->getName());
        MHoverWidget->State.hovering = false;
        MHoverWidget->on_widget_mouse_leave(nullptr,AXpos,AYpos,ATime);
        MHoverWidget = nullptr;
    }
    else
    {
        //SAT_PRINT("mouse leave message.. but MHoverWidget == nullptr\n");
    }
}

void SAT_WidgetWindow::on_window_client_message(uint32_t AData)  
{
    SAT_PRINT("AData = %i\n",AData);
}

// [GUI THREAD]
void SAT_WidgetWindow::on_window_timer(uint32_t ATimerId, double ADelta)
{
    handleTimer(ATimerId,ADelta,false);
}

//------------------------------
// widget owner
//------------------------------

SAT_Painter* SAT_WidgetWindow::do_widget_owner_get_painter(SAT_BaseWidget* AWidget)
{
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

bool SAT_WidgetWindow::do_widget_owner_register_timer(SAT_BaseWidget* AWidget)
{
    MTimerWidgets.append(AWidget);
    return true;
}

bool SAT_WidgetWindow::do_widget_owner_unregister_timer(SAT_BaseWidget* AWidget)
{
    MTimerWidgets.remove(AWidget);
    return true;
}

//------------------------------
// on_widget
//------------------------------

// void SAT_WidgetWindow::on_widget_show(SAT_WidgetOwner* AOwner)
// void SAT_WidgetWindow::on_widget_hide(SAT_WidgetOwner* AOwner)
// void SAT_WidgetWindow::on_widget_paint(SAT_PaintContext* AContext, uint32_t AMode, uint32_t AIndex)
// void SAT_WidgetWindow::on_widget_pre_paint(SAT_PaintContext* AContext, uint32_t AMode, uint32_t AIndex)
// void SAT_WidgetWindow::on_widget_post_paint(SAT_PaintContext* AContext, uint32_t AMode, uint32_t AIndex)
// void SAT_WidgetWindow::on_widget_realign(uint32_t AMode, uint32_t AIndex)
// SAT_Rect on_widget_pre_align(SAT_Rect ARect, uint32_t AMode, uint32_t AIndex)
// SAT_Rect on_widget_post_align(SAT_Rect ARect, uint32_t AMode, uint32_t AIndex)
// void SAT_WidgetWindow::on_widget_timer(uint32_t ATimerId, double ADelta)
// void SAT_WidgetWindow::on_widget_tween(uint32_t AId, uint32_t AType, uint32_t ANumValues, double* AValues)
// void SAT_WidgetWindow::on_widget_hint(uint32_t AType, const char* AHint)
// void SAT_WidgetWindow::on_widget_mouse_click(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATime)
// void SAT_WidgetWindow::on_widget_mouse_dbl_click(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATime)
// void SAT_WidgetWindow::on_widget_mouse_release(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATime)
// void SAT_WidgetWindow::on_widget_mouse_move(int32_t AXpos, int32_t AYpos, uint32_t AState, uint32_t ATime)
// void SAT_WidgetWindow::on_widget_key_press(uint32_t AKey, uint32_t AChar, uint32_t AState, uint32_t ATime)
// void SAT_WidgetWindow::on_widget_key_release(uint32_t AKey, uint32_t AChar, uint32_t AState, uint32_t ATime)
// void SAT_WidgetWindow::on_widget_mouse_enter(SAT_BaseWidget* AFrom, int32_t AXpos, int32_t AYpos, uint32_t ATime)
// void SAT_WidgetWindow::on_widget_mouse_leave(SAT_BaseWidget* ATo, int32_t AXpos, int32_t AYpos, uint32_t ATime)

//------------------------------
// do_widget
//------------------------------

void SAT_WidgetWindow::do_widget_update(SAT_BaseWidget* AWidget, uint32_t AIndex)
{
    void* parameter = AWidget->getParameter();
    if (MListener && parameter)
    {
        MListener->do_widget_update(AWidget,AIndex);
    }
}

void SAT_WidgetWindow::do_widget_realign(SAT_BaseWidget* AWidget)
{
    // #ifdef SAT_NO_WINDOW_BUFFERING
    //     AWidget->realignChildren();
    //     AWidget->do_Widget_redraw(AWidget);
    // #else
        MWidgetRealignQueue.write(AWidget);
    // #endif
}

void SAT_WidgetWindow::do_widget_redraw(SAT_BaseWidget* AWidget)
{
    // #ifdef SAT_NO_WINDOW_BUFFERING
    //     // if not buffered, we draw directly..
    //     SAT_Rect rect = AWidget->getRect();
    //     invalidate(rect.x,rect.y,rect.w,rect.h);
    // #else
        // MWidgetRedrawQueue.write(AWidget);
        SAT_BaseWidget* opaque_parent = AWidget->Recursive.opaque_parent;
        SAT_Assert(opaque_parent);
        MWidgetRedrawQueue.write(opaque_parent);
    // #endif
}

void SAT_WidgetWindow::do_widget_tween(SAT_BaseWidget* AWidget, SAT_TweenChain* AChain)
{
    // Note: this is read in the timerHandler!
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

void SAT_WidgetWindow::do_widget_cursor(SAT_BaseWidget* AWidget, uint32_t ACursor)
{
    /*
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
    */
}

void SAT_WidgetWindow::do_widget_capture_mouse(SAT_BaseWidget* AWidget)
{
    MCapturedMouseWidget = AWidget;
}

void SAT_WidgetWindow::do_widget_capture_keyboard(SAT_BaseWidget* AWidget)
{
    MCapturedKeyWidget = AWidget;
}
