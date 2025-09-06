#pragma once

/*
    fill the update_rect completely with yellow before painting..
    and draw a red rect around it afterwards..
    plus prints out a bunch of painting related tings..
*/

// #define SAT_WINDOW_DEBUG_PAINTING

/*
    prints out a bunch of mouse click, move, enter/release, etc..
*/

// #define SAT_WINDOW_DEBUG_MOUSE_EVENTS

/*
    note to self:
        remember to keep the widget part in sync with the window parts (size, rect, etc)

    todo / consider:

    *   layers
            multiple layers of widgets..
            background that doesn't change (buffered, just blit)
            popup boxes, menus, dialog boxes, tooltips, ..

    *   clipping
            there seems to be some off-by-one pixel issues with update-rect, vs clipping
            maybe because all painting is using float/double, while clipping and
            update_rect is pixels/ints (coming from the os/system)..
            but also, x11 does some weird things sometimes.. :-/
            TODO: double-check, test, hunt down where this could happen.. rounding? (
        
*/

#include "base/sat_base.h"
#include "base/system/sat_timer.h"
#include "gui/widget/sat_widget_owner.h"
#include "gui/window/sat_paint_window.h"
#include "gui/window/sat_window_listener.h"
#include "gui/skin/sat_default_skin.h"
#include "gui/sat_animator.h"
#include "gui/sat_painter.h"
#include "gui/sat_renderer.h"
#include "gui/sat_widget.h"
#include "gui/sat_window.h"

//------------------------------
// queues
//------------------------------

// write:
// read:
// typedef SAT_SPSCQueue<SAT_Widget*,SAT_QUEUE_SIZE_UPDATE>    SAT_WidgetUpdateQueue;

// write: do_widget_realign
// read: handleTimer

typedef SAT_SPSCQueue<SAT_Widget*,SAT_QUEUE_SIZE_REALIGN>   SAT_WidgetRealignQueue;

// ouch.. written to, in two different places!
// but both are in the gui thread, and as a result of x11 messages,
// so they shouldn't ever be called concurrently

// write: do_widget_redraw. handleTimer
// read: handleTimer

typedef SAT_SPSCQueue<SAT_Widget*,SAT_QUEUE_SIZE_REDRAW>    SAT_WidgetRedrawQueue;

// write: handleTimer
// read: paintWidgets (from on_window_paint)

typedef SAT_SPSCQueue<SAT_Widget*,SAT_QUEUE_SIZE_PAINT>     SAT_WidgetPaintQueue;

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

struct SAT_Window_State
{
 // bool                    needFullRealignment = false;            // force full alignment (all widgets)
    bool                    needFullRepaint     = false;            // force full repaint (all widgets)
    bool                    mouseInsideWindow   = false;
    sat_coord_t             scale               = 1.0;
    uint32_t                currentTimerTick    = 0;                // increasing tick counter
    sat_atomic_bool_t       timerBlocked        {false};            // if this is true, timer handler returns immediately
    sat_atomic_bool_t       isClosing           {false};            // if this is true, timer handler returns immediately
};

struct SAT_Window_Widgets
{
    SAT_WidgetArray         timer               = {};               // array of widgets that want timer ticks
    SAT_Widget*             hint                = nullptr;          // widget receiving hints
    SAT_Widget*             hover               = nullptr;          // currently hovering over
    SAT_Widget*             modal               = nullptr;          // exclusive widget, all other widgets ignored
    SAT_Widget*             mouseCaptured       = nullptr;          // send mouse events directly to this
    SAT_Widget*             keyCaptured         = nullptr;          // send key events directoy to this
    uint32_t                capturedButton      = SAT_BUTTON_NONE;  // button that caused the capture
 // SAT_Widget*             drag                = nullptr;          // drag'n'drop, start widget (drag from)
};

struct SAT_Window_Queues
{
 // SAT_WidgetUpdateQueue   update              = {};               // value changed (parameter/plugin)
    SAT_WidgetRealignQueue  realign             = {};               // needs to be realigned
    SAT_WidgetRedrawQueue   redraw              = {};               // needs to be redrawn
    SAT_WidgetPaintQueue    paint               = {};               // will be painted
};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_WidgetWindow
: public SAT_PaintWindow
, public SAT_WidgetOwner
//, public SAT_Widget
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
        virtual void        handleTimer(uint32_t ATimerId, double ADelta, bool AInTimerThread=false);
        virtual void        paintBackground(SAT_PaintContext* AContext);
        virtual void        paintWidgets(SAT_PaintContext* AContext);
        virtual void        paintOverlay(SAT_PaintContext* AContext);
        virtual sat_coord_t calcScale(uint32_t ANewWidth, uint32_t ANewHeight, uint32_t AInitialWidth, uint32_t AInitialHeight);
        virtual void        updateHover(int32_t AXpos, int32_t AYpos, uint32_t ATime);

    public:

        void                on_timer_listener_update(SAT_Timer* ATimer, double ADelta) override;
        void                on_window_paint(SAT_PaintContext* AContext) override;

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
        sat_coord_t         do_widget_owner_get_scale(SAT_Widget* AWidget) override;
        bool                do_widget_owner_register_timer(SAT_Widget* AWidget) override;
        bool                do_widget_owner_unregister_timer(SAT_Widget* AWidget) override;

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
        // void                on_widget_anim(uint32_t AId, uint32_t AType, uint32_t ANumValues, double* AValues) override;
        // void                on_widget_hint(uint32_t AType, const char* AHint) override;
        // void                on_widget_mouse_click(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATime) override;
        // void                on_widget_mouse_dbl_click(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATime) override;
        // void                on_widget_mouse_release(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATime) override;
        // void                on_widget_mouse_move(int32_t AXpos, int32_t AYpos, uint32_t AState, uint32_t ATime) override;
        // void                on_widget_key_press(uint32_t AKey, uint32_t AChar, uint32_t AState, uint32_t ATime) override;
        // void                on_widget_key_release(uint32_t AKey, uint32_t AChar, uint32_t AState, uint32_t ATime) override;
        // void                on_widget_mouse_enter(SAT_Widget* AFrom, int32_t AXpos, int32_t AYpos, uint32_t ATime) override;
        // void                on_widget_mouse_leave(SAT_Widget* ATo, int32_t AXpos, int32_t AYpos, uint32_t ATime) override;

    public:

        void                do_widget_update(SAT_Widget* AWidget, uint32_t AIndex=0) override;
        void                do_widget_realign(SAT_Widget* AWidget) override;
        void                do_widget_redraw(SAT_Widget* AWidget) override;
        void                do_widget_anim(SAT_Widget* AWidget, SAT_AnimChain* AChain) override;
        void                do_widget_notify(SAT_Widget* AWidget, uint32_t AType, int32_t AValue) override;
        void                do_widget_hint(SAT_Widget* AWidget, uint32_t AType, const char* AHint) override;
        void                do_widget_modal(SAT_Widget* AWidget) override;
        void                do_widget_cursor(SAT_Widget* AWidget, uint32_t ACursor) override;
        void                do_widget_capture_mouse(SAT_Widget* AWidget) override;
        void                do_widget_capture_keyboard(SAT_Widget* AWidget) override;

    private:

        SAT_WindowListener* MListener       = nullptr;
        SAT_Timer*          MTimer          = nullptr;
        SAT_Animator        MAnimator       = {};
        SAT_DefaultSkin     MDefaultSkin    = {};

        SAT_Window_State    State           = {};
        SAT_Window_Queues   Queues          = {};
        SAT_Window_Widgets  Widgets         = {};

};

//----------------------------------------------------------------------
//
// implementation
//
//----------------------------------------------------------------------

SAT_WidgetWindow::SAT_WidgetWindow(uint32_t AWidth, uint32_t AHeight, intptr_t AParent)
: SAT_PaintWindow(AWidth, AHeight, AParent)
, SAT_Widget(SAT_Rect(AWidth,AHeight))
{
    WidgetBase.widgetTypeName       = "SAT_WidgetWindow";
    WidgetRecursive.opaque_parent   = this;
    WidgetVisual.skin               = &MDefaultSkin;
    MTimer                          = new SAT_Timer(this);
};

SAT_WidgetWindow::~SAT_WidgetWindow()
{
    if (MTimer)
    {
        if (MTimer->isRunning()) MTimer->stop();
        delete MTimer;
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
    Widgets.hint = AWidget;
}

void SAT_WidgetWindow::appendTimerWidget(SAT_Widget* AWidget)
{
    SAT_Assert(AWidget);
    Widgets.timer.append(AWidget);
}

void SAT_WidgetWindow::removeTimerWidget(SAT_Widget* AWidget)
{
    SAT_Assert(AWidget);
    Widgets.timer.remove(AWidget);
}

/*
    TODO: widget redrawing originating from audio automation & modulation (MWidgetUpdateQueue?)
    AInTimerThread is true if we're called from a timer,
    or false if we have redirected it to the gui thread..
*/

void SAT_WidgetWindow::handleTimer(uint32_t ATimerId, double ADelta, bool AInTimerThread)
{
    // we don't want any new timer tickes until we finished processing this one..
    // (this is no set in the timer handler itself (see on_timer_listener_update)
    // set to false at the end of this func)
    // MTimerBlocked = true;

    // ----- widget timers -----

    for (uint32_t i=0; i<Widgets.timer.size(); i++)
    {
        Widgets.timer[i]->on_widget_timer(ATimerId,ADelta);
    }

    // ----- animation -----

    MAnimator.process(ADelta);

    // ----- realign queue -----

    uint32_t count = 0;
    SAT_Widget* widget;
    while (Queues.realign.read(&widget))
    {
        //widget->realignChildren();
        widget->on_widget_realign();
        Queues.redraw.write(widget);
        count += 1;
    }
    // SAT.STATISTICS.report_WindwRealignQueue(count);

    // ----- redraw queue -----

    count = 0;
    SAT_Rect update_rect;
    while (Queues.redraw.read(&widget))
    {
        // .. possibly do some checking and culling..

        if (count == 0) update_rect = widget->WidgetRecursive.clip_rect;  // WidgetRecursive.rect;
        else update_rect.combine(widget->WidgetRecursive.clip_rect);      // WidgetRecursive.rect);

        Queues.paint.write(widget);
        count += 1;
    }
    // SAT.STATISTICS.report_WindwRedrawQueue(count,rect);

    // ----- invalidate -----

    if (update_rect.isNotEmpty())
    {
        //SAT_PRINT("invalidate\n");
        invalidate(update_rect.x,update_rect.y,update_rect.w,update_rect.h);
    }

    // -----
    
    State.currentTimerTick += 1;
    State.timerBlocked = false;
}

/*
    first, redraw anything inside the update_rect
    (paint any background widgets intersecting the update rect)

    we haven't 'dived down' into each widget that needs to be drawn yet,
    so clipping is set to the update_rect, that encompass/surround all
    the (unclipped) widgets that are to be drawn, not just the changed parts..
    (when we set a widget 'dirty', we don't know which part of will be clipped)
*/

void SAT_WidgetWindow::paintBackground(SAT_PaintContext* AContext)
{
    // if (MClearBackground)
    // {
    //     SAT_Assert(AContext->painter);
    //     AContext->painter->setFillColor(MBackgroundColor);
    //     AContext->painter->fillRect(WidgetRecursive.rect);
    // }
    #ifdef SAT_WINDOW_DEBUG_PAINTING
        AContext->painter->setDrawColor(SAT_Yellow);
        AContext->painter->fillRect(AContext->update_rect);
    #endif
}

/*
    paint widgets, after background have been drawn
    MNeedFullRepaint set in on_window_show and on_window_resize

    lots of messy stuff here left from testing and debugging..
    needs to be cleaned up.. find out what's actually needed, etc..
*/

//SAT_Rect
void SAT_WidgetWindow::paintWidgets(SAT_PaintContext* AContext)
{
    uint32_t paint_count = 0;
    SAT_Widget* widget = nullptr;

    if (State.needFullRepaint)
    {

        // if (MClearBackground)
        // {
        //     SAT_Assert(AContext->painter);
        //     AContext->painter->setFillColor(MBackgroundColor);
        //     AContext->painter->fillRect(WidgetRecursive.rect);
        // }

        //SAT_PRINT("full repaint\n");
        uint32_t num = getNumChildren();
        for (uint32_t i=0; i<num; i++)
        {
            widget = getChild(i);
            widget->on_widget_paint(AContext);
            widget->WidgetUpdate.last_painted = AContext->current_frame;
            // if (have_painted_rect) painted_rect.combine(widget->getRect());
            // else painted_rect = widget->getRect();
            // have_painted_rect = true;
        }
        // flush queue, so we don't re-draw them next time..
        while (Queues.paint.read(&widget)) { paint_count += 1; }

        // SAT.STATISTICS.report_WindowPaintAll();
        State.needFullRepaint = false;
    }
    else
    {
        while (Queues.paint.read(&widget))
        {
            #ifdef SAT_WINDOW_DEBUG_PAINTING
                SAT_PRINT("frame %i, count %i\n",AContext->current_frame,paint_count);
            #endif

            // widget->WidgetUpdate.last_painted_count = 0;
            //if ((widget->WidgetUpdate.last_painted == AContext->current_frame) && (widget->WidgetUpdate.last_painted_count == paint_count))

            if (widget->WidgetUpdate.last_painted == AContext->current_frame)
            {
                #ifdef SAT_WINDOW_DEBUG_PAINTING
                    SAT_PRINT("skipping %s, already painted (frame %i)\n",widget->getName(),widget->WidgetUpdate.last_painted);
                #endif
            }
            else
            {
                //SAT_PRINT("painting widget %i\n",paint_count);
                //widget->pushRecursiveClip(AContext);
                //widget->pushClip(AContext);

                SAT_Widget* opaque_parent = widget->WidgetRecursive.opaque_parent;
                if (opaque_parent != widget)
                {
                    #ifdef SAT_WINDOW_DEBUG_PAINTING
                        SAT_PRINT("%s is opaque, drawing opaque_parent %s\n",widget->getName(),opaque_parent->getName());
                        // paint_count still sount this as 1..
                    #endif
                    opaque_parent->pushRecursiveClip(AContext);
                    opaque_parent->on_widget_paint(AContext);
                    /*
                        eventual widgets inbtween the opaque_parent and this widget itself
                        will not be marked as redrawn, will they?
                        maybe we need to add a "widget.mark_children_as_painted(uint32_t AFrame)"?
                        .. actually, SAT_VisualWidget.on_widget_paint() calls paintChildren,
                        which sets last_painted = current frame for each child..
                    */
                    opaque_parent->WidgetUpdate.last_painted = AContext->current_frame;
                    //opaque_parent->WidgetUpdate.last_painted_count = paint_count;
                }
                else
                {
                    #ifdef SAT_WINDOW_DEBUG_PAINTING
                        SAT_PRINT("painting %s (opaque_parent %s)\n",widget->getName(),opaque_parent->getName());
                    #endif
                    widget->pushRecursiveClip(AContext);
                    widget->on_widget_paint(AContext);
                    widget->WidgetUpdate.last_painted = AContext->current_frame;
                    // widget->WidgetUpdate.last_painted_count = paint_count;
                }
                widget->popClip(AContext);
            }
            paint_count += 1;
        }
        // SAT.STATISTICS.report_WindowPaintQueue(paint_count);
    }

    //return painted_rect;
    //return AContext->update_rect;
}

/*
    after widgets have been drawn, we might need to repaint the overlay on top of them
    (paint any overlay widgets intersecting the update rect)

    for debugging, we draw a red suqare around the entire update_rect..
*/

void SAT_WidgetWindow::paintOverlay(SAT_PaintContext* AContext)
{
    #ifdef SAT_WINDOW_DEBUG_PAINTING
        AContext->painter->setDrawColor(SAT_Red);
        AContext->painter->setLineWidth(2);
        AContext->painter->drawRect(AContext->update_rect);
        AContext->painter->setLineWidth(0);
    #endif
}

/*
    calculate scale
    how much we can scale the window proportionally from the initial/original size,
    and still fit within the new window size..
*/

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

/*
    update hovering state..
    find which (topmost) widget mouse cursor is hovering above..
    sends mouse enter/leave message to the relevant widgets..
    also see on_window_mouse_leave (sends mouse leave msg to hover wdg)

    todo: take widget->isActive into account
    if we can't interact with it, don't respøond to hover events???
    (also consider drag/drop, disabled)


*/

void SAT_WidgetWindow::updateHover(int32_t AXpos, int32_t AYpos, uint32_t ATime)
{
    SAT_Widget* hover = nullptr;

    int32_t winw = (int32_t)getWidth();
    int32_t winh = (int32_t)getHeight();
    if ( (AXpos >= 0) && (AXpos < winw) && (AYpos >= 0) && (AYpos < winh) ) State.mouseInsideWindow = true;
    else State.mouseInsideWindow = false;
    //SAT_PRINT("inside window: %i\n",MMouseInsideWindow);

    if (State.mouseInsideWindow)
    {
        if (Widgets.modal) hover = Widgets.modal->findChildAt(AXpos,AYpos);
        else hover = findChildAt(AXpos,AYpos);
        // hover        = new hover
        // MHoverWidget = previous hover (if null = just entered window)
        if (!Widgets.hover)
        {
            // we have just entered the window, didn't leave anything            
            #ifdef SAT_WINDOW_DEBUG_MOUSE_EVENTS            
                SAT_PRINT("entering: %s %s\n",hover->getWidgetTypeName(), hover->getName());
            #endif
            hover->WidgetState.hovering = true;
            hover->on_widget_mouse_enter(Widgets.hover,AXpos,AYpos,ATime);
            Widgets.hover = hover;
        }
        else
        {
            // are we hovering over the same, or a different widget?
            if (hover != Widgets.hover)
            {
                // differemt, leave the old, enter the new
                #ifdef SAT_WINDOW_DEBUG_MOUSE_EVENTS            
                    SAT_PRINT("leaving: %s %s\n",MHoverWidget->getWidgetTypeName(),MHoverWidget->getName());
                #endif
                Widgets.hover->WidgetState.hovering = false;
                Widgets.hover->on_widget_mouse_leave(hover,AXpos,AYpos,ATime);
                #ifdef SAT_WINDOW_DEBUG_MOUSE_EVENTS            
                    SAT_PRINT("entering: %s %s\n",hover->getWidgetTypeName(), hover->getName());
                #endif
                hover->WidgetState.hovering = true;
                hover->on_widget_mouse_enter(Widgets.hover,AXpos,AYpos,ATime);
                Widgets.hover = hover;
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
    if (State.timerBlocked)
    {
        // double time = SAT_GetTime();
        // SAT.STATISTICS.report_WindowTimerBlocked(time);
        return;
    }
    if (State.isClosing)
    {
        // double time = SAT_GetTime();
        // SAT.STATISTICS.report_WindowTimerWhen WindowIsClosing(time);
        return;
    }

    // set to false at the end of handleTimer()
    State.timerBlocked = true;

    #ifdef SAT_WINDOW_REDIRECT_TIMER_TO_GUI_THREAD
        sendClientMessage(SAT_WINDOW_USER_MESSAGE_TIMER,0);
        // see on_window_timer(), which will call handleTimer()...
    #else
        // don't do this!
        // this is dagerous! handleTimer reads from the
        // MTimerWidgets array, calls MAnimator, writes to MRedrawQueue..
        handleTimer(ATimerId,ADelta,true);
    #endif
};

void SAT_WidgetWindow::on_window_paint(SAT_PaintContext* AContext)
{
    paintBackground(AContext);
    paintWidgets(AContext);
    paintOverlay(AContext);
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
        SAT_Widget* child = getChild(i);
        child->on_widget_show(this);
    }
    State.needFullRepaint = true;
    realignChildren();
    State.isClosing = false;
    State.timerBlocked = false;
    MTimer->start(SAT_WINDOW_TIMER_MS);
}

void SAT_WidgetWindow::on_window_hide()
{
    State.isClosing = true;
    setOwner(nullptr);
    if (MTimer->isRunning()) MTimer->stop();
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
    State.scale = calcScale(AWidth,AHeight,WidgetVisual.initialRect.w,WidgetVisual.initialRect.h);
    //SAT_PRINT("scale: %.3f\n",MWindowScale);
    SAT_PaintWindow::windowResize(AWidth,AHeight);
    WidgetRecursive.rect = SAT_Rect(AWidth,AHeight);
    realignChildren();
    State.needFullRepaint = true;
}

// void SAT_WidgetWindow::on_window_paint(int32_t AXpos, int32_t AYpos, uint32_t AWidth, uint32_t AHeight)
// {
// }

/*
    TODO:
        if WidgetOptions.drag_drop - MMDragDropWidget = this
        (or widget must initiate it with do_widget_start_drag()
*/

void SAT_WidgetWindow::on_window_mouse_click(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATime)
{
    if (Widgets.mouseCaptured)
    {
        // a widget is captured, and we clicked another button
        #ifdef SAT_WINDOW_DEBUG_MOUSE_EVENTS
            SAT_PRINT("clicked another button -> captured: %s\n",MCapturedMouseWidget->getName());
        #endif
        Widgets.mouseCaptured->on_widget_mouse_click(AXpos,AYpos,AButton,AState,ATime);
    }
    else if (Widgets.hover)
    {
        if (Widgets.hover->WidgetOptions.auto_capture)
        {
            if ((AButton == SAT_BUTTON_LEFT) || (AButton == SAT_BUTTON_MIDDLE) || (AButton == SAT_BUTTON_RIGHT))
            {
                #ifdef SAT_WINDOW_DEBUG_MOUSE_EVENTS
                    SAT_PRINT("capture widget: %s\n",MHoverWidget->getName());
                #endif
                Widgets.mouseCaptured = Widgets.hover;
                Widgets.capturedButton = AButton;
            }
        }
        #ifdef SAT_WINDOW_DEBUG_MOUSE_EVENTS
            SAT_PRINT("mouse click: %s\n",MHoverWidget->getName());
        #endif
        Widgets.hover->on_widget_mouse_click(AXpos,AYpos,AButton,AState,ATime);
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
    if (Widgets.mouseCaptured)
    {
        #ifdef SAT_WINDOW_DEBUG_MOUSE_EVENTS
            SAT_PRINT("mouse release -> captured: %s\n",MCapturedMouseWidget->getName());
        #endif
        Widgets.mouseCaptured->on_widget_mouse_release(AXpos,AYpos,AButton,AState,ATime);
        if (Widgets.capturedButton == AButton)
        {
            #ifdef SAT_WINDOW_DEBUG_MOUSE_EVENTS
                SAT_PRINT("un-capture: %s\n",MCapturedMouseWidget->getName());
            #endif
            Widgets.mouseCaptured = nullptr;
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
    if (Widgets.mouseCaptured)
    {
        #ifdef SAT_WINDOW_DEBUG_MOUSE_EVENTS
            SAT_PRINT("mouse move -> captured: %s\n",MCapturedMouse->getName());
        #endif
        Widgets.mouseCaptured->on_widget_mouse_move(AXpos,AYpos,AState,ATime);
        // if (is_dragging)
        // {
        // }
    }
    else 
    {
        //SAT_Assert(MHoverWidget);
        if (Widgets.hover)
        {
            if (Widgets.hover->WidgetOptions.want_hover_events)
            {
                #ifdef SAT_WINDOW_DEBUG_MOUSE_EVENTS
                    SAT_PRINT("mouse move -> want hover: %s\n",Widgets.hover->getName());
                #endif
                Widgets.hover->on_widget_mouse_move(AXpos,AYpos,AState,ATime);
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
    if (Widgets.keyCaptured)
    {
        Widgets.keyCaptured->on_widget_key_press(AKey,AChar,AState,ATime);
    }
}

void SAT_WidgetWindow::on_window_key_release(uint32_t AKey, uint32_t AChar, uint32_t AState, uint32_t ATime)
{
    if (Widgets.keyCaptured)
    {
        Widgets.keyCaptured->on_widget_key_release(AKey,AChar,AState,ATime);
    }
}

void SAT_WidgetWindow::on_window_mouse_enter(int32_t AXpos, int32_t AYpos, uint32_t ATime)
{
    updateHover(AXpos,AYpos,ATime);
}

void SAT_WidgetWindow::on_window_mouse_leave(int32_t AXpos, int32_t AYpos, uint32_t ATime)
{
    //SAT_Assert(MHoverWidget);
    if (Widgets.hover)
    {
        #ifdef SAT_WINDOW_DEBUG_MOUSE_EVENTS
            SAT_PRINT("leaving: %s %s\n",MHoverWidget->getWidgetTypeName(), MHoverWidget->getName());
        #endif
        Widgets.hover->WidgetState.hovering = false;
        Widgets.hover->on_widget_mouse_leave(nullptr,AXpos,AYpos,ATime);
        Widgets.hover = nullptr;
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

SAT_Painter* SAT_WidgetWindow::do_widget_owner_get_painter(SAT_Widget* AWidget)
{
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

sat_coord_t SAT_WidgetWindow::do_widget_owner_get_scale(SAT_Widget* AWidget)
{
    return State.scale;
}

bool SAT_WidgetWindow::do_widget_owner_register_timer(SAT_Widget* AWidget)
{
    Widgets.timer.append(AWidget);
    return true;
}

bool SAT_WidgetWindow::do_widget_owner_unregister_timer(SAT_Widget* AWidget)
{
    Widgets.timer.remove(AWidget);
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
// void SAT_WidgetWindow::on_widget_anim(uint32_t AId, uint32_t AType, uint32_t ANumValues, double* AValues)
// void SAT_WidgetWindow::on_widget_hint(uint32_t AType, const char* AHint)
// void SAT_WidgetWindow::on_widget_mouse_click(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATime)
// void SAT_WidgetWindow::on_widget_mouse_dbl_click(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATime)
// void SAT_WidgetWindow::on_widget_mouse_release(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATime)
// void SAT_WidgetWindow::on_widget_mouse_move(int32_t AXpos, int32_t AYpos, uint32_t AState, uint32_t ATime)
// void SAT_WidgetWindow::on_widget_key_press(uint32_t AKey, uint32_t AChar, uint32_t AState, uint32_t ATime)
// void SAT_WidgetWindow::on_widget_key_release(uint32_t AKey, uint32_t AChar, uint32_t AState, uint32_t ATime)
// void SAT_WidgetWindow::on_widget_mouse_enter(SAT_Widget* AFrom, int32_t AXpos, int32_t AYpos, uint32_t ATime)
// void SAT_WidgetWindow::on_widget_mouse_leave(SAT_Widget* ATo, int32_t AXpos, int32_t AYpos, uint32_t ATime)

//------------------------------
// do_widget
//------------------------------

void SAT_WidgetWindow::do_widget_update(SAT_Widget* AWidget, uint32_t AIndex)
{
    void* parameter = AWidget->getParameter();
    if (MListener && parameter)
    {
        MListener->do_widget_update(AWidget,AIndex);
    }
}

void SAT_WidgetWindow::do_widget_realign(SAT_Widget* AWidget)
{
    // #ifdef SAT_NO_WINDOW_BUFFERING
    //     AWidget->realignChildren();
    //     AWidget->do_Widget_redraw(AWidget);
    // #else
        Queues.realign.write(AWidget);
    // #endif
}

/*
    we handle opaque_parent != widget in paintWidgets()
*/

void SAT_WidgetWindow::do_widget_redraw(SAT_Widget* AWidget)
{
    // #ifdef SAT_NO_WINDOW_BUFFERING
    //     // if not buffered, we draw directly..
    //     SAT_Rect rect = AWidget->getRect();
    //     invalidate(rect.x,rect.y,rect.w,rect.h);
    // #else
        Queues.redraw.write(AWidget);
    // #endif
}

void SAT_WidgetWindow::do_widget_anim(SAT_Widget* AWidget, SAT_AnimChain* AChain)
{
    // Note: this is read in the timerHandler!
    MAnimator.appendChain(AChain);
}

void SAT_WidgetWindow::do_widget_notify(SAT_Widget* AWidget, uint32_t AType, int32_t AValue)
{
}

void SAT_WidgetWindow::do_widget_hint(SAT_Widget* AWidget, uint32_t AType, const char* AHint)
{
    if (Widgets.hint) Widgets.hint->on_widget_hint(AType,AHint);
}

void SAT_WidgetWindow::do_widget_modal(SAT_Widget* AWidget)
{
    Widgets.modal = AWidget;
}

void SAT_WidgetWindow::do_widget_cursor(SAT_Widget* AWidget, uint32_t ACursor)
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

void SAT_WidgetWindow::do_widget_capture_mouse(SAT_Widget* AWidget)
{
    Widgets.mouseCaptured = AWidget;
}

void SAT_WidgetWindow::do_widget_capture_keyboard(SAT_Widget* AWidget)
{
    Widgets.keyCaptured = AWidget;
}
