#pragma once

/*
    fill the update_rect completely with yellow before painting..
    and draw a red rect around it afterwards..
    plus prints out a bunch of painting related tings..
*/

/*
    prints out a bunch of mouse click, move, enter/release, etc..
*/

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

/*
    TODO?
    - backgroundWidgets
    - overlayWidgets
*/

struct SAT_MouseCoords
{
    int16_t x;
    int16_t y;
};

//----------

struct SAT_Window_State
{
 // bool                    needFullRealignment = false;            // force full alignment (all widgets)
    bool                    needFullRepaint     = false;            // force full repaint (all widgets)
    bool                    mouseInsideWindow   = false;
    sat_coord_t             scale               = 1.0;
    uint32_t                currentTimerTick    = 0;                // increasing tick counter
    sat_atomic_bool_t       timerBlocked        {false};            // if this is true, timer handler returns immediately
    sat_atomic_bool_t       isClosing           {false};            // if this is true, timer handler returns immediately

    // bool waiting_for_tooltip
    // bool waiting_for_longpress
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

    // widget tooptip
    // double time_last_mouse_move

    // widget longpress
    // double time_last_mouse_click

};

struct SAT_Window_Queues
{
 // SAT_WidgetUpdateQueue   update              = {};               // value changed (parameter/plugin)
    SAT_WidgetRealignQueue  realign             = {};               // needs to be realigned
    SAT_WidgetRedrawQueue   redraw              = {};               // needs to be redrawn
    SAT_WidgetPaintQueue    paint               = {};               // will be painted
};

struct SAT_Window_Mouse
{
    SAT_MouseCoords         currentPos          = {0,0};
    double                  currentTime         = 0.0;
    double                  lastMovedTime       = 0.0;
    double                  clickedTime         = 0.0;
    SAT_MouseCoords         clickedPos          = {0,0};
    uint32_t                clickedButton       = SAT_BUTTON_NONE;
    uint32_t                clickedState        = SAT_KEY_STATE_NONE;
    SAT_Widget*             clickedWidget       = nullptr;
    bool                    waitingForDrag      = false;
    bool                    waitingForLongpress = false;
    uint32_t                longpressTime       = 0;
    bool                    waitingForTooltip   = false;
    bool                    tooltipVisible      = false;
    SAT_Widget*             tooltipWidget       = nullptr;
    bool                    tooltipExpected     = false;
    bool                    locked              = false;
    SAT_MouseCoords         lockedPos           = {0,0};
    SAT_MouseCoords         lockedVirtualPos    = {0,0};
    int32_t                 currentCursor       = SAT_CURSOR_DEFAULT;
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
        virtual void        handleMouseTimer(double ADelta);
        virtual void        lockMouseCursor();
        virtual void        unlockMouseCursor();
        virtual bool        updateLockedMouse(int32_t AXpos, int32_t AYpos);
        virtual void        showTooltip(int32_t AXpos, int32_t AYpos, SAT_Widget* AWidget);
        virtual void        hideTooltip();
        virtual sat_coord_t calcScale(uint32_t ANewWidth, uint32_t ANewHeight, uint32_t AInitialWidth, uint32_t AInitialHeight);
        virtual void        updateHover(int32_t AXpos, int32_t AYpos, uint32_t ATime);
     // virtual void        paintWidget(SAT_PaintContext* AContext, SAT_Widget* AWidget);
        virtual void        paintWidgets(SAT_PaintContext* AContext);
        virtual void        paintBackground(SAT_PaintContext* AContext);
        virtual void        paintOverlay(SAT_PaintContext* AContext);

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
        void                do_widget_cursor(SAT_Widget* AWidget, int32_t ACursor) override;
        void                do_widget_capture_mouse(SAT_Widget* AWidget) override;
        void                do_widget_capture_keyboard(SAT_Widget* AWidget) override;

    private:

        SAT_WindowListener* MListener       = nullptr;
        SAT_Timer*          MTimer          = nullptr;
        SAT_Animator        MAnimator       = {};

        SAT_Window_State    State           = {};
        SAT_Window_Queues   Queues          = {};
        SAT_Window_Widgets  Widgets         = {};
        SAT_Window_Mouse    Mouse           = {};
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
    MTimer                          = new SAT_Timer(this);
    WidgetVisual.skin               = SAT.GUI->SKINS.find("Default");
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
    // MTimerBlocked = true;
    // ----- mouse -----
    handleMouseTimer(ADelta);
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
        // .. possibly do some more checking and culling here..
        if (count == 0) update_rect = widget->WidgetRecursive.clip_rect;
        else update_rect.combine(widget->WidgetRecursive.clip_rect);

        Queues.paint.write(widget);
        count += 1;
    }
    // SAT.STATISTICS.report_WindwRedrawQueue(count,rect);
    // ----- invalidate -----
    if (update_rect.isNotEmpty())
    {
        invalidate(update_rect.x,update_rect.y,update_rect.w,update_rect.h);
    }
    State.currentTimerTick += 1;
    State.timerBlocked = false;
}

void SAT_WidgetWindow::handleMouseTimer(double ADelta)
{
    Mouse.currentTime += ADelta;
    if (Mouse.waitingForLongpress)
    {
        if ((Mouse.currentTime - Mouse.clickedTime) >= SAT.GUI->getLongPressTime()) // >= SAT_MOUSE_LONGPRESS_SEC
        {
            SAT_Assert(Mouse.clickedWidget);
            int32_t x = Mouse.clickedPos.x;
            int32_t y = Mouse.clickedPos.y;
            uint32_t b = Mouse.clickedButton;
            uint32_t s = Mouse.clickedState;
            uint32_t t = Mouse.longpressTime + (uint32_t)(SAT.GUI->getLongPressTime() * 1000); // SAT_MOUSE_LONGPRESS_SEC * 1000
            on_widget_mouse_longpress(x,y,b,s,t);
            Mouse.waitingForLongpress = false;
        }
    }
    if (Mouse.waitingForTooltip)
    {
        if ((Mouse.currentTime - Mouse.lastMovedTime) >= SAT.GUI->getTooltipDelayTime()) // >= SAT_MOUSE_TOOLTIP_SEC
        {
            SAT_Assert(Mouse.tooltipWidget);
            if (Mouse.tooltipWidget->WidgetOptions.tooltip)
            {
                Mouse.waitingForTooltip = false;
                Mouse.tooltipVisible = true;
                showTooltip(Mouse.currentPos.x,Mouse.currentPos.y,Mouse.tooltipWidget);
            }
            Mouse.tooltipExpected = false;
        }
    }
}

void SAT_WidgetWindow::lockMouseCursor()
{
    Mouse.locked = true;
    Mouse.lockedPos.x = Mouse.currentPos.x;
    Mouse.lockedPos.y = Mouse.currentPos.y;
    Mouse.lockedVirtualPos.x = Mouse.currentPos.x;
    Mouse.lockedVirtualPos.y = Mouse.currentPos.y;
}

void SAT_WidgetWindow::unlockMouseCursor()
{
    Mouse.locked = false;
    // Mouse.currentPos.x = Mouse.lockedVirtualPos.x;
    // Mouse.currentPos.y = Mouse.lockedVirtualPos.y;
}

/*
    updates Mouse.lockedVirtualPos
*/

bool SAT_WidgetWindow::updateLockedMouse(int32_t AXpos, int32_t AYpos)
{
    if ((AXpos == Mouse.lockedPos.x) && (AYpos == Mouse.lockedPos.y))
    {
        // not moved
        // (might be because of the previous setMouseCursorPos)
        return false;
    }
    int32_t xdiff = AXpos - Mouse.lockedPos.x;
    int32_t ydiff = AYpos - Mouse.lockedPos.y;
    Mouse.lockedVirtualPos.x += xdiff;
    Mouse.lockedVirtualPos.y += ydiff;
    setMouseCursorPos(Mouse.lockedPos.x,Mouse.lockedPos.y);
    return true;
}

void SAT_WidgetWindow::showTooltip(int32_t AXpos, int32_t AYpos, SAT_Widget* AWidget)
{
    const char* name    = Mouse.tooltipWidget->getName();
    const char* tooltip = Mouse.tooltipWidget->getTooltip();
    SAT_PRINT("Show tooltip: pos %i,%i widget %s = '%s'\n",AXpos,AYpos,name,tooltip);
}

// void SAT_WidgetWindow::updateTooltip(int32_t AXpos, int32_t AYpos, SAT_Widget* AWidget)
// {
// }

void SAT_WidgetWindow::hideTooltip()
{
    SAT_PRINT("Hide tooltip\n");
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
    SAT_Widget* new_hover = nullptr;
    int32_t winw = (int32_t)getWidth();
    int32_t winh = (int32_t)getHeight();
    if ( (AXpos >= 0) && (AXpos < winw) && (AYpos >= 0) && (AYpos < winh) ) State.mouseInsideWindow = true;
    else State.mouseInsideWindow = false;
    if (State.mouseInsideWindow)
    {
        if (Widgets.modal) new_hover = Widgets.modal->findChildAt(AXpos,AYpos);
        else new_hover = findChildAt(AXpos,AYpos);
        if (!Widgets.hover)
        {
            // we have just entered the window, didn't leave anything            
            new_hover->WidgetState.hovering = true;
            new_hover->on_widget_mouse_enter(Widgets.hover,AXpos,AYpos,ATime);
            if (new_hover->WidgetOptions.redraw_if_hovering) new_hover->do_widget_redraw(new_hover);
            Widgets.hover = new_hover;
        }
        else
        {
            // are we hovering over the same, or a different widget?
            if (new_hover != Widgets.hover)
            {
                // differemt, leave the old, enter the new
                Widgets.hover->WidgetState.hovering = false;
                Widgets.hover->on_widget_mouse_leave(new_hover,AXpos,AYpos,ATime);
                Mouse.tooltipExpected = true;
                if (Widgets.hover->WidgetOptions.redraw_if_hovering) Widgets.hover->do_widget_redraw(Widgets.hover);
                new_hover->WidgetState.hovering = true;
                new_hover->on_widget_mouse_enter(Widgets.hover,AXpos,AYpos,ATime);
                if (new_hover->WidgetOptions.redraw_if_hovering) new_hover->do_widget_redraw(new_hover);
                Widgets.hover = new_hover;
            }
        }
    }
}

/*
    paint widgets, after background have been drawn
    MNeedFullRepaint set in on_window_show and on_window_resize
    todo: lots of messy stuff here left from testing and debugging..
    needs to be cleaned up.. find out what's actually needed, etc..
*/

void SAT_WidgetWindow::paintWidgets(SAT_PaintContext* AContext)
{
    uint32_t paint_count = 0;
    SAT_Widget* widget = nullptr;
    if (State.needFullRepaint)
    {
        while (Queues.paint.read(&widget))
        {
            paint_count += 1;
        }
        for (uint32_t i=0; i<getNumChildren(); i++)
        {
            widget = getChild(i);
            paintWidget(AContext,widget);
        }
        // SAT.STATISTICS.report_WindowPaintAll();
        State.needFullRepaint = false;
    }
    else
    {
        while (Queues.paint.read(&widget))
        {
            if (widget->WidgetUpdate.last_painted != AContext->current_frame)
            {
                SAT_Widget* opaque_parent = widget->WidgetRecursive.opaque_parent;
                if (opaque_parent != widget) paintWidget(AContext,opaque_parent);
                else paintWidget(AContext,widget);
            }
            paint_count += 1;
        }
        // SAT.STATISTICS.report_WindowPaintQueue(paint_count);
    }
}

/*
    first, redraw anything inside the update_rect
    (paint any background widgets intersecting the update rect)
    note we haven't 'dived down' into each widget that needs to be drawn yet,
    so clipping is set to the update_rect, that encompass/surround all
    the (unclipped) widgets that are to be drawn, not just the changed parts..
    (when we set a widget 'dirty', we don't know which part of will be clipped)
    todo: check through background_widgets (?), if any of them intersects the
    update_rect, redraw them first..
*/

void SAT_WidgetWindow::paintBackground(SAT_PaintContext* AContext)
{
}

/*
    after widgets have been drawn, we might need to repaint the overlay on top of them
    (paint any overlay widgets intersecting the update rect)
    todo: check through overlay_widgets (?), if any of them intersects the
    update_rect, redraw them on top..
*/

void SAT_WidgetWindow::paintOverlay(SAT_PaintContext* AContext)
{
}

//------------------------------
//
//------------------------------

// [TIMER THREAD]
void SAT_WidgetWindow::on_timer_listener_update(SAT_Timer* ATimer, double ADelta)
{
    if (State.timerBlocked) return;
    if (State.isClosing) return;
    State.timerBlocked = true;
    #ifdef SAT_WINDOW_REDIRECT_TIMER_TO_GUI_THREAD
        sendClientMessage(SAT_WINDOW_USER_MESSAGE_TIMER,0);
        // see on_window_timer(), which will call handleTimer()...
    #else
        // don't do this! this is dagerous! handleTimer reads from the
        // MTimerWidgets array, calls MAnimator, writes to MRedrawQueue..
        handleTimer(ATimerId,ADelta,true);
    #endif
};

/*
    clipping is set up (by SAT_PaintWindow)
    around the update_rect
*/

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
    State.isClosing = false;
    State.timerBlocked = false;
    State.needFullRepaint = true;
    Mouse.currentTime = 0.0;
    Mouse.tooltipExpected = true;
    // reset more? (window hide/show vs delete/create)
    showOwner(this);
    realignChildren();
    MTimer->start(SAT_WINDOW_TIMER_MS);
}

void SAT_WidgetWindow::on_window_hide()
{
    State.isClosing = true;
    if (MTimer->isRunning()) MTimer->stop();
    hideOwner(this);
}

void SAT_WidgetWindow::on_window_move(int32_t AXpos, int32_t AYpos)
{
}

void SAT_WidgetWindow::on_window_resize(uint32_t AWidth, uint32_t AHeight)
{
    State.scale = calcScale(AWidth,AHeight,WidgetVisual.initialRect.w,WidgetVisual.initialRect.h);
    SAT_Rect rect = SAT_Rect(AWidth,AHeight);
    WidgetRecursive.rect = rect;
    WidgetRecursive.clip_rect = rect;
    realignChildren();
    SAT_PaintWindow::windowResize(AWidth,AHeight);
    State.needFullRepaint = true;
}

/*
    TODO:
    if WidgetOptions.drag_drop - MMDragDropWidget = this
    (or widget must initiate it with do_widget_start_drag()
*/

void SAT_WidgetWindow::on_window_mouse_click(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATime)
{
    Mouse.clickedTime = Mouse.currentTime;
    Mouse.clickedPos.x = AXpos;
    Mouse.clickedPos.y = AXpos;
    Mouse.clickedButton = AButton;
    Mouse.clickedState = AState;
    Mouse.longpressTime = ATime;
    // Mouse.clicked_widget = nullptr;
    // Mouse.waiting_longpress = true;
    Mouse.waitingForLongpress = false;
    Mouse.waitingForTooltip = false;
    Mouse.waitingForDrag = true;
    if (Mouse.tooltipVisible)
    {
        Mouse.tooltipVisible = false;
        hideTooltip();
    }
    if (Widgets.mouseCaptured)
    {
        // a widget is captured, and we clicked another button
        Mouse.clickedWidget = Widgets.mouseCaptured;
        Mouse.waitingForLongpress = true;
        Widgets.mouseCaptured->on_widget_mouse_click(AXpos,AYpos,AButton,AState,ATime);
    }
    else if (Widgets.hover)
    {
        if (Widgets.hover->WidgetOptions.mouse_capture)
        {
            if ((AButton == SAT_BUTTON_LEFT) || (AButton == SAT_BUTTON_MIDDLE) || (AButton == SAT_BUTTON_RIGHT))
            {
                Widgets.mouseCaptured = Widgets.hover;
                Widgets.capturedButton = AButton;
            }
        }
        Mouse.clickedWidget = Widgets.hover;
        Mouse.waitingForLongpress = true;
        Widgets.hover->on_widget_mouse_click(AXpos,AYpos,AButton,AState,ATime);
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
    // Mouse.clicked_time = ATime;
    // Mouse.clicked_pos.x = AXpos;
    // Mouse.clicked_pos.y = AXpos;
    // Mouse.clicked_button = AButton;
    // Mouse.clicked_widget = nullptr;
    Mouse.waitingForLongpress = false;
    Mouse.waitingForDrag = false;
    if (Widgets.mouseCaptured)
    {
        Widgets.mouseCaptured->on_widget_mouse_release(AXpos,AYpos,AButton,AState,ATime);
        Mouse.tooltipExpected = true;
        if (Widgets.capturedButton == AButton)
        {
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
    Mouse.lastMovedTime = Mouse.currentTime;
    Mouse.waitingForLongpress = false;
    Mouse.waitingForTooltip = false;
    if (Mouse.tooltipVisible)
    {
        Mouse.tooltipVisible = false;
        hideTooltip();
    }
    if (Mouse.waitingForDrag)
    {
        Mouse.clickedWidget->on_widget_mouse_start_drag(AXpos,AYpos,AState,ATime);
        Mouse.waitingForDrag = false;
    }
    if (Mouse.locked)
    {
        if (updateLockedMouse(AXpos,AYpos))
        {
            if (Widgets.mouseCaptured)
            {
                int32_t x = Mouse.lockedVirtualPos.x;
                int32_t y = Mouse.lockedVirtualPos.y;
                Widgets.mouseCaptured->on_widget_mouse_move(x,y,AState,ATime);
            }
        }
    }
    else
    {
        Mouse.currentPos.x = AXpos;
        Mouse.currentPos.y = AYpos;
        updateHover(AXpos,AYpos,ATime);
        if (Widgets.mouseCaptured)
        {
            if (Mouse.tooltipExpected)
            {
                Mouse.waitingForTooltip = true;
                Mouse.tooltipWidget = Widgets.mouseCaptured;
            }
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
                if (Mouse.tooltipExpected)
                {
                    Mouse.waitingForTooltip = true;
                    Mouse.tooltipWidget = Widgets.hover;
                }
                if (Widgets.hover->WidgetOptions.want_hover_events)
                {
                    Widgets.hover->on_widget_mouse_move(AXpos,AYpos,AState,ATime);
                }
            }
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
    Mouse.tooltipExpected = true;
}

void SAT_WidgetWindow::on_window_mouse_leave(int32_t AXpos, int32_t AYpos, uint32_t ATime)
{
    if (Mouse.tooltipVisible)
    {
        Mouse.tooltipVisible = false;
        hideTooltip();
    }
    Mouse.waitingForTooltip = false;
    Mouse.tooltipExpected = false;
    Mouse.waitingForLongpress = false;
    if (Widgets.hover)
    {
        Widgets.hover->WidgetState.hovering = false;
        Widgets.hover->on_widget_mouse_leave(nullptr,AXpos,AYpos,ATime);
        if (Widgets.hover->WidgetOptions.redraw_if_hovering) Widgets.hover->do_widget_redraw(Widgets.hover);
        Widgets.hover = nullptr;
    }
    // do_widget_cursor(this,SAT_CURSOR_DEFAULT);
    // do_widget_hint(this,0,WidgetBase.hint);
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
// void SAT_WidgetWindow::on_widget_mouse_longpress(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATime)
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
    //SAT_PRINT("widget '%s' index %i\n",AWidget->getName(),AIndex);
    void* parameter = AWidget->getParameter();
    if (MListener && parameter)
    {
        MListener->do_widget_update(AWidget,AIndex);
    }
}

void SAT_WidgetWindow::do_widget_realign(SAT_Widget* AWidget)
{
    //SAT_PRINT("widget '%s'\n",AWidget->getName());
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
    //SAT_PRINT("widget '%s'\n",AWidget->getName());
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
    //SAT_PRINT("widget '%s'\n",AWidget->getName());
    // Note: this is read in the timerHandler!
    MAnimator.appendChain(AChain);
}

void SAT_WidgetWindow::do_widget_notify(SAT_Widget* AWidget, uint32_t AType, int32_t AValue)
{
    //SAT_PRINT("widget '%s' type %i value %i\n",AWidget->getName(),AType,AValue);
}

void SAT_WidgetWindow::do_widget_hint(SAT_Widget* AWidget, uint32_t AType, const char* AHint)
{
    //if (Widgets.hint) Widgets.hint->on_widget_hint(AType,AHint);
    //SAT_PRINT("widget '%s' type %i hint %i\n",AWidget->getName(),AType,AHint);
}

void SAT_WidgetWindow::do_widget_modal(SAT_Widget* AWidget)
{
    //SAT_PRINT("widget '%s'\n",AWidget->getName());
    Widgets.modal = AWidget;
}

void SAT_WidgetWindow::do_widget_cursor(SAT_Widget* AWidget, int32_t ACursor)
{
    switch(ACursor)
    {
        case SAT_CURSOR_LOCK:
        {
            lockMouseCursor();
            break;
        }
        case SAT_CURSOR_UNLOCK:
        {
            unlockMouseCursor();
            break;
        }
        case SAT_CURSOR_SHOW:  
        {
            showMouseCursor();
            setMouseCursorShape(Mouse.currentCursor);
            break;
        }
        case SAT_CURSOR_HIDE:
        {
            hideMouseCursor();
            break;
        }
        default:
        {
            if (ACursor != Mouse.currentCursor)
            {
                setMouseCursorShape(ACursor);
                Mouse.currentCursor = ACursor;
            }
        }
    }
}

void SAT_WidgetWindow::do_widget_capture_mouse(SAT_Widget* AWidget)
{
    //SAT_PRINT("widget '%s'\n",AWidget->getName());
    Widgets.mouseCaptured = AWidget;
}

void SAT_WidgetWindow::do_widget_capture_keyboard(SAT_Widget* AWidget)
{
    //SAT_PRINT("widget '%s'\n",AWidget->getName());
    Widgets.keyCaptured = AWidget;
}
