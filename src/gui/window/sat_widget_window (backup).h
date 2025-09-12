#pragma once

/*
    TODO / consider:
    *   Mouse.waitStartTime, waitPos .. related to waitingFor...
        - error margin for longpress, tooltip.. (and doubleclick?)..
        - delayedShow, ala tooltip.. waitingForShow, showStartWaitTime, showWidget, 
        - delayedHide, move out of widget, hide after some time..  waitingForHide, hideStartWaitTime, hideWidget, 
    *   tooltip:
        - hide (if visible) when mouse leaves widget? (currently, when moving)
        - offset/flags (offset: relative to mouse or widget,.. flags: visible while dragging, ..)
        - movement error margin
    * double-click:
        - movement error margin



    if widget has Options.realignIfInvisible set, it will be aligned and positioned just as if it was visible..




    delayedShow/Hide..
    - widget can be aligned in place, but invisible, inactive..
      (how can we receive enter/leave?)

    hover enter widget (!visible, !active)
        Options.delayed = true -> call do_widget_delayedShow
    hover leave widget with Options.delayed
        call do_widget_delayedHide
*/

#include "base/sat_base.h"
#include "base/system/sat_timer.h"
#include "gui/skin/sat_default_skin.h"
#include "gui/window/sat_paint_window.h"
#include "gui/window/sat_window_listener.h"
#include "gui/sat_animator.h"
#include "gui/sat_painter.h"
#include "gui/sat_renderer.h"

#include "gui/widget/sat_widget_owner.h"
#include "gui/sat_widget.h"

struct SAT_MouseCoords
{
    int16_t x;
    int16_t y;
};

//------------------------------
// queues
//------------------------------

// typedef SAT_SPSCQueue<SAT_Widget*,SAT_QUEUE_SIZE_UPDATE>    SAT_WidgetUpdateQueue;
typedef SAT_SPSCQueue<SAT_Widget*,SAT_QUEUE_SIZE_REALIGN>   SAT_WidgetRealignQueue;
typedef SAT_SPSCQueue<SAT_Widget*,SAT_QUEUE_SIZE_REDRAW>    SAT_WidgetRedrawQueue;
typedef SAT_SPSCQueue<SAT_Widget*,SAT_QUEUE_SIZE_PAINT>     SAT_WidgetPaintQueue;

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

// struct SAT_MouseCoords
// {
//     int16_t x;
//     int16_t y;
// };

//----------

struct SAT_Window__Mouse
{
    double                  currentTime         = 0.0;
    SAT_MouseCoords         currentPos          = {0,0};
    int32_t                 currentCursor       = SAT_CURSOR_DEFAULT;

    SAT_Widget*             hoverWidget         = nullptr;
    SAT_Widget*             modalWidget         = nullptr;

    double                  prevMovedTime       = 0.0;

    SAT_Widget*             clickedWidget       = nullptr;
    SAT_MouseCoords         clickedPos          = {0,0};
    uint32_t                clickedButton       = SAT_BUTTON_NONE;
    uint32_t                clickedState        = SAT_KEY_STATE_NONE;
    double                  clickedTime         = 0.0;

    SAT_Widget*             releasedWidget      = nullptr;
    uint32_t                releasedButton      = SAT_BUTTON_NONE;
    double                  releasedTime        = 0.0;

    SAT_Widget*             capturedWidget      = nullptr;
    uint32_t                capturedButton      = SAT_BUTTON_NONE;

    bool                    locked              = false;
 // SAT_Widget*             lockedWidget        = nullptr;
    SAT_MouseCoords         lockedPos           = {0,0};
    SAT_MouseCoords         lockedVirtualPos    = {0,0};

    bool                    waitingForDrag      = false;
    bool                    waitingForLongpress = false;
    bool                    waitingForTooltip   = false;

    bool                    tooltipAllowed      = false;
    bool                    tooltipVisible      = false;
    SAT_Widget*             tooltipWidget       = nullptr;

 // bool                    delayedShow         = false;
 // double                  delayedShowTime     = false;
 // bool                    delayedShowVisible  = false;
 // SAT_Widget*             delayedShowWidget   = nullptr;

};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_WidgetWindow
: public SAT_PaintWindow
, public SAT_Widget
, public SAT_WidgetOwner
, public SAT_TimerListener
{
    public:

        SAT_WidgetWindow(uint32_t AWidth, uint32_t AHeight, intptr_t AParent=0);
        virtual ~SAT_WidgetWindow();

    public: // window

        virtual void        setListener(SAT_WindowListener* AListener);
        virtual sat_coord_t calcScale(uint32_t ANewWidth, uint32_t ANewHeight, uint32_t AInitialWidth, uint32_t AInitialHeight);

        void                on_timer_listener_update(SAT_Timer* ATimer, double ADelta) override;

    public: // widgets

        virtual void        setHintWidget(SAT_Widget* AWidget);
        virtual void        showTooltip(int32_t AXpos, int32_t AYpos, SAT_Widget* AWidget);
        virtual void        hideTooltip();

    public: // timer

        virtual void        appendTimerWidget(SAT_Widget* AWidget);
        virtual void        removeTimerWidget(SAT_Widget* AWidget);
        virtual void        handleTimer(uint32_t ATimerId, double ADelta, bool AInTimerThread=false);

    public: // painting

        virtual void        paintWidgets(SAT_PaintContext* AContext);
        virtual void        paintBackground(SAT_PaintContext* AContext);
        virtual void        paintOverlay(SAT_PaintContext* AContext);

        void                on_window_paint(SAT_PaintContext* AContext) override;

    public: // mouse

        virtual void        handleMouseTimer(double ADelta);
        virtual void        updateHover(int32_t AXpos, int32_t AYpos, uint32_t ATime, SAT_Widget* APrevHover=nullptr);
        virtual bool        updateLockedMouse(int32_t AXpos, int32_t AYpos);
        virtual void        lockMouseCursor();
        virtual void        unlockMouseCursor();

    public:

        void                on_window_show() override;
        void                on_window_hide() override;
        void                on_window_move(int32_t AXpos, int32_t AYpos) override;
        void                on_window_resize(uint32_t AWidth, uint32_t AHeight) override;
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

        void                do_widget_update(SAT_Widget* AWidget, uint32_t AIndex=0) override;
        void                do_widget_realign(SAT_Widget* AWidget, uint32_t AMode=SAT_WIDGET_REALIGN_PARENT) override;
        void                do_widget_redraw(SAT_Widget* AWidget, uint32_t AMode=SAT_WIDGET_REDRAW_SELF) override;
        void                do_widget_anim(SAT_Widget* AWidget, SAT_AnimChain* AChain) override;
        void                do_widget_notify(SAT_Widget* AWidget, uint32_t AType, int32_t AValue) override;
        void                do_widget_hint(SAT_Widget* AWidget, uint32_t AType, const char* AHint) override;
        void                do_widget_modal(SAT_Widget* AWidget) override;
        void                do_widget_cursor(SAT_Widget* AWidget, int32_t ACursor) override;
        void                do_widget_capture_mouse(SAT_Widget* AWidget) override;
        void                do_widget_capture_keyboard(SAT_Widget* AWidget) override;

    private: // window
    private: // widgets

        SAT_WindowListener*     MListener           = nullptr;
        SAT_Animator            MAnimator           = {};
        SAT_WidgetArray         MBackgroundWidgets  = {};
        SAT_WidgetArray         MOverlayWidgets     = {};

        sat_coord_t             MWindowScale        = 1.0;
        sat_atomic_bool_t       MIsClosing          {false};
        bool                    MNeedFullRepaint    = false;

        SAT_Timer*              MTimer              = nullptr;
        SAT_WidgetArray         MTimerWidgets       = {};
        uint32_t                MCurrentTimerTick   = 0;
        sat_atomic_bool_t       MTimerBlocked       {false};

        SAT_Widget*             MHintReceiver       = nullptr;
        SAT_Widget*             MKeyCapturedWidget  = nullptr;

     // SAT_WidgetUpdateQueue   MUpdateQueue        = {};
        SAT_WidgetRealignQueue  MRealignQueue       = {};
        SAT_WidgetRedrawQueue   MRedrawQueue        = {};
        SAT_WidgetPaintQueue    MPaintQueue         = {};

        //----------

        SAT_Window__Mouse       MMouse              = {};

        // SAT_MouseHandler     MMouse              = {};
        //SAT_MouseHandler*       MMouseHandler       = nullptr;

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
    MTypeName = "SAT_WidgetWindow";
    MRecursiveOpaqueParent = this;
    MTimer = new SAT_Timer(this);
    MSkin = SAT.GUI->SKINS.find("Default");
    //MMouseHandler = new SAT_MouseHandler(this);
};

SAT_WidgetWindow::~SAT_WidgetWindow()
{
    if (MTimer)
    {
        if (MTimer->isRunning()) MTimer->stop();
        delete MTimer;
    }
    //delete MMouseHandler;
}

//------------------------------
// window
//------------------------------

void SAT_WidgetWindow::setListener(SAT_WindowListener* AListener)
{
    MListener = AListener;
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

// [TIMER THREAD]
void SAT_WidgetWindow::on_timer_listener_update(SAT_Timer* ATimer, double ADelta)
{
    if (MTimerBlocked) return;
    if (MIsClosing) return;
    MTimerBlocked = true;
    #ifdef SAT_WINDOW_REDIRECT_TIMER_TO_GUI_THREAD
        sendClientMessage(SAT_WINDOW_USER_MESSAGE_TIMER,0);
        // see on_window_timer(), which will call handleTimer()...
    #else
        // don't do this! this is dagerous! handleTimer reads from the
        // MTimerWidgets array, calls MAnimator, writes to MRedrawQueue..
        handleTimer(ATimerId,ADelta,true);
    #endif
};

//------------------------------
// widgets
//------------------------------

void SAT_WidgetWindow::setHintWidget(SAT_Widget* AWidget)
{
    MHintReceiver = AWidget;
}

void SAT_WidgetWindow::showTooltip(int32_t AXpos, int32_t AYpos, SAT_Widget* AWidget)
{
    const char* name    = MMouse.tooltipWidget->getName();
    const char* tooltip = MMouse.tooltipWidget->getTooltip();
    SAT_PRINT("Show tooltip: pos %i,%i widget %s = '%s'\n",AXpos,AYpos,name,tooltip);
}

// void SAT_WidgetWindow::updateTooltip(int32_t AXpos, int32_t AYpos, SAT_Widget* AWidget)
// {
// }

void SAT_WidgetWindow::hideTooltip()
{
    SAT_PRINT("Hide tooltip\n");
}

//------------------------------
// timer
//------------------------------

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
    for (uint32_t i=0; i<MTimerWidgets.size(); i++)
    {
        MTimerWidgets[i]->on_widget_timer(ATimerId,ADelta);
    }
    // ----- animation -----
    MAnimator.process(ADelta);
    // ----- realign queue -----
    uint32_t count = 0;
    SAT_Widget* widget;
    while (MRealignQueue.read(&widget))
    {
        widget->on_widget_realign();
        MRedrawQueue.write(widget);
        count += 1;
    }
    // SAT.STATISTICS.report_WindwRealignQueue(count);
    // ----- redraw queue -----
    count = 0;
    SAT_Rect update_rect;
    while (MRedrawQueue.read(&widget))
    {
        // .. possibly do some more checking and culling here..
        if (count == 0) update_rect = widget->MRecursiveClipRect;
        else update_rect.combine(widget->MRecursiveClipRect);

        MPaintQueue.write(widget);
        count += 1;
    }
    // SAT.STATISTICS.report_WindwRedrawQueue(count,rect);
    // ----- invalidate -----
    if (update_rect.isNotEmpty())
    {
        invalidate(update_rect.x,update_rect.y,update_rect.w,update_rect.h);
    }
    MCurrentTimerTick += 1;
    MTimerBlocked = false;
}

//------------------------------
// painting
//------------------------------

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
    if (MNeedFullRepaint)
    {
        SAT_PRINT("full repaint\n");
        while (MPaintQueue.read(&widget))
        {
            paint_count += 1;
        }
        for (uint32_t i=0; i<getNumChildren(); i++)
        {
            widget = getChild(i);
            paintWidget(AContext,widget);
        }
        // SAT.STATISTICS.report_WindowPaintAll();
        MNeedFullRepaint = false;
    }
    else
    {
        while (MPaintQueue.read(&widget))
        {
            if (widget->MLastPainted != AContext->current_frame)
            {
                SAT_Widget* opaque_parent = widget->MRecursiveOpaqueParent;
                SAT_PRINT("painting: %s (opaque_parent: %s)\n",widget->getName(),opaque_parent->getName());
                if (opaque_parent != widget) paintWidget(AContext,opaque_parent);
                else paintWidget(AContext,widget);
            }
            paint_count += 1;
        }
        // SAT.STATISTICS.report_WindowPaintQueue(paint_count);
    }
}

/*
    draw any background widgets that intersect the update_rect
*/

void SAT_WidgetWindow::paintBackground(SAT_PaintContext* AContext)
{
    for (uint32_t i=0; i<MBackgroundWidgets.size(); i++)
    {
        SAT_Widget* widget = MBackgroundWidgets[i];
        SAT_Rect rect = widget->getRect();
        if (rect.intersects(AContext->update_rect))
        {
            paintWidget(AContext,widget);
        }
    }
}

/*
    draw any overlay widgets that intersect the update_rect
*/

void SAT_WidgetWindow::paintOverlay(SAT_PaintContext* AContext)
{
    for (uint32_t i=0; i<MOverlayWidgets.size(); i++)
    {
        SAT_Widget* widget = MOverlayWidgets[i];
        SAT_Rect rect = widget->getRect();
        if (rect.intersects(AContext->update_rect))
        {
            paintWidget(AContext,widget);
        }
    }
}

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
// mouse
//------------------------------

void SAT_WidgetWindow::handleMouseTimer(double ADelta)
{
    MMouse.currentTime += ADelta;
    if (MMouse.waitingForLongpress)
    {
        if ((MMouse.currentTime - MMouse.clickedTime) >= SAT.GUI->getLongPressTime()) // >= SAT_MOUSE_LONGPRESS_SEC
        {
            SAT_Assert(MMouse.clickedWidget);
            int32_t x = MMouse.clickedPos.x;
            int32_t y = MMouse.clickedPos.y;
            uint32_t b = MMouse.clickedButton;
            uint32_t s = MMouse.clickedState;
            uint32_t t = MMouse.clickedTime + (uint32_t)(SAT.GUI->getLongPressTime() * 1000); // SAT_MOUSE_LONGPRESS_SEC * 1000
            //SAT_PRINT("longpress  - %s\n",MMouse.clickedWidget->getName());
            if (MMouse.clickedWidget->Options.wantLongPress)
                MMouse.clickedWidget->on_widget_mouse_longpress(x,y,b,s,t);
            MMouse.waitingForLongpress = false;
            // MMouse.waitingForDrag = false;
        }
    }
    if (MMouse.waitingForTooltip)
    {
        if ((MMouse.currentTime - MMouse.prevMovedTime) >= SAT.GUI->getTooltipDelayTime()) // >= SAT_MOUSE_TOOLTIP_SEC
        {
            SAT_Assert(MMouse.tooltipWidget);
            if (MMouse.tooltipWidget->Options.hasTooltip)
            {
                MMouse.waitingForTooltip = false;
                MMouse.tooltipVisible = true;
                showTooltip(MMouse.currentPos.x,MMouse.currentPos.y,MMouse.tooltipWidget);
            }
            MMouse.tooltipAllowed = false;
        }
    }
}

/*
    update hovering state..
    find which (topmost) widget mouse cursor is hovering above..
    sets State.hovering for entered, leaved widget
    and calls on_widget_mouse_enter/leave, unless a captured witget has CaptureHover
    also updates active, visible flags if active/visibleIfHovering is set

    see also on_window_mouse_leave (sends mouse leave msg to hover wdg)
*/

void SAT_WidgetWindow::updateHover(int32_t AXpos, int32_t AYpos, uint32_t ATime, SAT_Widget* APrevHover)
{

    // outside of window?

    int32_t winw = (int32_t)getWidth();
    int32_t winh = (int32_t)getHeight();
    if ((AXpos < 0) || (AXpos >= winw) || (AYpos < 0) || (AYpos >= winh)) return;

    // if a modal widget is active, only search from that one,
    // otherwise search from the top..

    SAT_Widget* hover = nullptr;
    if (MMouse.modalWidget) hover = MMouse.modalWidget->findHoveringChild(AXpos,AYpos);
    else hover = findHoveringChild(AXpos,AYpos);

    // compare with current hovered widget, or argument?

    SAT_Widget* prev_hover;
    if (APrevHover) prev_hover = APrevHover;
    else prev_hover = MMouse.hoverWidget;
    
    // are we hovering over a different widget?

    SAT_Widget* entered_widget = nullptr;
    SAT_Widget* left_widget = nullptr;
    if (hover != prev_hover)
    {
        left_widget = prev_hover;
        entered_widget = hover;
        MMouse.tooltipAllowed = true;
    }

    // don't send enter/leave messages if a captured widget has captureHover flag..

    bool send_hover_events = true;
    if (MMouse.capturedWidget && MMouse.capturedWidget->Options.captureHover) send_hover_events = false;

    if (left_widget)
    {
        // MMouse.hoverWidget = nullptr;
        left_widget->State.hovering = false;
        if (left_widget->Options.activeIfHovering) left_widget->State.active = false;
        if (left_widget->Options.visibleIfHovering) left_widget->State.visible = false;
        if (send_hover_events) left_widget->on_widget_mouse_leave(entered_widget,AXpos,AYpos,ATime);
        }
    if (entered_widget)
    {
        MMouse.hoverWidget = entered_widget;
        entered_widget->State.hovering = true;
        if (entered_widget->Options.activeIfHovering) entered_widget->State.active = true;
        if (entered_widget->Options.visibleIfHovering) entered_widget->State.visible = true;
        if (send_hover_events) entered_widget->on_widget_mouse_enter(left_widget,AXpos,AYpos,ATime);
    }

}

bool SAT_WidgetWindow::updateLockedMouse(int32_t AXpos, int32_t AYpos)
{
    if ((AXpos == MMouse.lockedPos.x) && (AYpos == MMouse.lockedPos.y))
    {
        // not moved
        // (might be because of the previous setMouseCursorPos)
        return false;
    }
    int32_t xdiff = AXpos - MMouse.lockedPos.x;
    int32_t ydiff = AYpos - MMouse.lockedPos.y;
    MMouse.lockedVirtualPos.x += xdiff;
    MMouse.lockedVirtualPos.y += ydiff;
    setMouseCursorPos(MMouse.lockedPos.x,MMouse.lockedPos.y);
    return true;
}

void SAT_WidgetWindow::lockMouseCursor()
{
    MMouse.locked = true;
    MMouse.lockedPos.x = MMouse.currentPos.x;
    MMouse.lockedPos.y = MMouse.currentPos.y;
    MMouse.lockedVirtualPos.x = MMouse.currentPos.x;
    MMouse.lockedVirtualPos.y = MMouse.currentPos.y;
}

void SAT_WidgetWindow::unlockMouseCursor()
{
    MMouse.locked = false;
    // MMouse.currentPos.x = MMouse.lockedVirtualPos.x;
    // MMouse.currentPos.y = MMouse.lockedVirtualPos.y;
}




















//------------------------------
//
//------------------------------

//------------------------------
// base window
//------------------------------

void SAT_WidgetWindow::on_window_show()
{
    MIsClosing = false;
    MTimerBlocked = false;
    MNeedFullRepaint = true;
    MMouse.currentTime = 0.0;
    MMouse.tooltipAllowed = true;
    // reset more? (window hide/show vs delete/create)
    showOwner(this);
    realignChildren();
    MTimer->start(SAT_WINDOW_TIMER_MS);
}

void SAT_WidgetWindow::on_window_hide()
{
    MIsClosing = true;
    if (MTimer->isRunning()) MTimer->stop();
    hideOwner(this);
}

void SAT_WidgetWindow::on_window_move(int32_t AXpos, int32_t AYpos)
{
}

void SAT_WidgetWindow::on_window_resize(uint32_t AWidth, uint32_t AHeight)
{
    MWindowScale = calcScale(AWidth,AHeight,MInitialRect.w,MInitialRect.h);
    SAT_Rect rect = SAT_Rect(AWidth,AHeight);
    MRect = rect;
    MRecursiveClipRect = rect;
    realignChildren();
    SAT_PaintWindow::windowResize(AWidth,AHeight);
    MNeedFullRepaint = true;
}

/*
    TODO:
    if Options.drag_drop - MMDragDropWidget = this
    (or widget must initiate it with do_widget_start_drag()
*/

void SAT_WidgetWindow::on_window_mouse_click(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATime)
{
    MMouse.clickedTime = MMouse.currentTime;
    MMouse.clickedPos.x = AXpos;
    MMouse.clickedPos.y = AXpos;
    MMouse.clickedButton = AButton;
    MMouse.clickedState = AState;
    // MMouse.clicked_widget = nullptr;
    // MMouse.waiting_longpress = true;
    MMouse.waitingForLongpress = false;
    MMouse.waitingForTooltip = false;

    // tooltip

    if (MMouse.tooltipVisible)
    {
        MMouse.tooltipVisible = false;
        hideTooltip();
    }

    // click

    // if mouse is captured && have captureClick, events are sent to the
    // captured widget.. otherwise they are sent to the hovered widget

    SAT_Widget* clicked =nullptr;
    if (MMouse.capturedWidget && MMouse.capturedWidget->Options.captureClick)
    {
        clicked = MMouse.capturedWidget;
    }
    else
    {
        clicked = MMouse.hoverWidget;
    }

    MMouse.clickedWidget = clicked;

    // if clicked widget is not active, just return..
    if (!clicked->State.active) return;
    
    // did we double click?

    SAT_Widget* double_clicked = nullptr;
    if ((AButton == MMouse.releasedButton) && (MMouse.hoverWidget == MMouse.releasedWidget))
    {
        if ((MMouse.currentTime - MMouse.releasedTime) <= SAT.GUI->getDoubleClickTime())  // <= SAT_MOUSE_DOUBLE_CLICK_SEC)
        {
            double_clicked = MMouse.hoverWidget;
        }
    }

    // if we double-clicked, and the last cliked button wants them,
    // send dbl-click message, otherwise just sent as regular click

    if (double_clicked && clicked->Options.wantDoubleClick)
    {
        clicked->on_widget_mouse_double_click(AXpos,AYpos,AButton,AState,ATime);
    }
    else if (clicked)
    {
        clicked->on_widget_mouse_click(AXpos,AYpos,AButton,AState,ATime);
    }

    // if we aren't already captured, and the clicked widget wants to be captured,
    // set new captured widget..

    if (!MMouse.capturedWidget && clicked->Options.mouseCapture)
    {
        if ((AButton == SAT_BUTTON_LEFT) || (AButton == SAT_BUTTON_MIDDLE) || (AButton == SAT_BUTTON_RIGHT))
        {
            MMouse.capturedWidget = clicked;//MMouse.hoverWidget;
            MMouse.capturedButton = AButton;
        }
    }

    //MMouse.clickedWidget = clicked;
    MMouse.waitingForDrag = true;
    MMouse.waitingForLongpress = true;

}

/*
    TODO:
    if MMDragDropWidget, ask hover widget if it accepts dropping (data)
    (or did we do that in mouse-move/enter? set MHoverWidgetAcceptsDrop?)
    if yes, drop(data), tell captured widget about it?
*/

void SAT_WidgetWindow::on_window_mouse_release(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATime)
{
    MMouse.releasedButton = AButton;
    MMouse.releasedTime = MMouse.currentTime;
    MMouse.releasedWidget = MMouse.hoverWidget;

    MMouse.waitingForLongpress = false;
    MMouse.waitingForDrag = false;

    // only captured widgets gets release messages..

    if (MMouse.capturedWidget)
    {
        MMouse.capturedWidget->on_widget_mouse_release(AXpos,AYpos,AButton,AState,ATime);
        MMouse.tooltipAllowed = true;

        // if we released the same button as started the capture, un-capture..
        // and update hover state..

        if (MMouse.capturedButton == AButton)
        {
            SAT_Widget* was_captured = MMouse.capturedWidget;
            MMouse.capturedWidget->State.hovering = false;
            MMouse.capturedWidget = nullptr;
            //MMouse.hoverWidget = nullptr; // force 'rescan'..
            //updateHover(AXpos,AYpos,ATime);
            updateHover(AXpos,AYpos,ATime,was_captured);
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
    MMouse.prevMovedTime = MMouse.currentTime;
    MMouse.waitingForLongpress = false;
    MMouse.waitingForTooltip = false;

    // get rid of tooltip if it is visible..

    if (MMouse.tooltipVisible)
    {
        hideTooltip();
        MMouse.tooltipVisible = false;
    }

    // are we waiting for the first mose movement to start a drag?

    if (MMouse.waitingForDrag)
    {
        // do the clicked widget want tot drag start message?
        if (MMouse.clickedWidget->Options.wantStartDrag)
        {
            // if a widget is captured, and we clicked another one,
            // don't start dragging, else send drag-start message to clicked widget

            bool can_start_drag = true;
            if (MMouse.capturedWidget && (MMouse.capturedWidget != MMouse.clickedWidget)) can_start_drag = false;
            if (can_start_drag)
            {
                MMouse.clickedWidget->on_widget_mouse_start_drag(MMouse.clickedPos.x,MMouse.clickedPos.y,MMouse.clickedButton,AState,ATime);
            }
        }
        MMouse.waitingForDrag = false;
    }

    // if mouse is locked, update virtual coord, and set mouse back..

    if (MMouse.locked)
    {
        if (updateLockedMouse(AXpos,AYpos))
        {
            if (MMouse.capturedWidget)
            {
                int32_t x = MMouse.lockedVirtualPos.x;
                int32_t y = MMouse.lockedVirtualPos.y;
                MMouse.capturedWidget->on_widget_mouse_move(x,y,AState,ATime);
            }
        }
    }

    // otherwise, update hover state..

    else
    {
        MMouse.currentPos.x = AXpos;
        MMouse.currentPos.y = AYpos;
        updateHover(AXpos,AYpos,ATime);

        // if a widget is captured..
        if (MMouse.capturedWidget)
        {
            // .. send move messages to it
            MMouse.capturedWidget->on_widget_mouse_move(AXpos,AYpos,AState,ATime);

            // if it's not the hovered one..
            if (MMouse.capturedWidget != MMouse.hoverWidget)
            {
                // .. and hover is not captured..
                if (!MMouse.capturedWidget->Options.captureHover)
                {
                    // .. allow/wait for tooltip
                    if (MMouse.tooltipAllowed)
                    {
                        MMouse.waitingForTooltip = true;
                        MMouse.tooltipWidget = MMouse.hoverWidget; // capturedWidget;
                    }
                }
            }
        }

        // .. else, if no captured widget..

        else 
        {
            if (MMouse.hoverWidget)
            {
                // .. send move msg if hovered widget wants it..
                if (MMouse.hoverWidget->Options.wantHoverAlways)
                {
                    MMouse.hoverWidget->on_widget_mouse_move(AXpos,AYpos,AState,ATime);
                }
                // .. and prepare for tooltip..
                if (MMouse.tooltipAllowed)
                {
                    MMouse.waitingForTooltip = true;
                    MMouse.tooltipWidget = MMouse.hoverWidget;
                }
            }
        }

    }
}

void SAT_WidgetWindow::on_window_key_press(uint32_t AKey, uint32_t AChar, uint32_t AState, uint32_t ATime)
{
    if (MKeyCapturedWidget)
    {
        MKeyCapturedWidget->on_widget_key_press(AKey,AChar,AState,ATime);
    }
}

void SAT_WidgetWindow::on_window_key_release(uint32_t AKey, uint32_t AChar, uint32_t AState, uint32_t ATime)
{
    if (MKeyCapturedWidget)
    {
        MKeyCapturedWidget->on_widget_key_release(AKey,AChar,AState,ATime);
    }
}

void SAT_WidgetWindow::on_window_mouse_enter(int32_t AXpos, int32_t AYpos, uint32_t ATime)
{
    updateHover(AXpos,AYpos,ATime);
    MMouse.tooltipAllowed = true;
}

void SAT_WidgetWindow::on_window_mouse_leave(int32_t AXpos, int32_t AYpos, uint32_t ATime)
{
    if (MMouse.tooltipVisible)
    {
        MMouse.tooltipVisible = false;
        hideTooltip();
    }
    MMouse.waitingForTooltip = false;
    MMouse.tooltipAllowed = false;
    MMouse.waitingForLongpress = false;
    if (MMouse.hoverWidget)
    {
        MMouse.hoverWidget->State.hovering = false;
        MMouse.hoverWidget->on_widget_mouse_leave(nullptr,AXpos,AYpos,ATime);
        //if (MMouse.hoverWidget->Options.redrawIfHovering) MMouse.hoverWidget->do_widget_redraw(MMouse.hoverWidget);
        MMouse.hoverWidget = nullptr;
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
    return MWindowScale;
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

void SAT_WidgetWindow::do_widget_realign(SAT_Widget* AWidget, uint32_t AMode)
{
    //SAT_PRINT("widget '%s'\n",AWidget->getName());
    // #ifdef SAT_NO_WINDOW_BUFFERING
    //     AWidget->realignChildren();
    //     AWidget->do_Widget_redraw(AWidget);
    // #else
    //    MRealignQueue.write(AWidget);
    // #endif

    SAT_Widget* parent;
    switch (AMode)
    {
        case SAT_WIDGET_REALIGN_SELF:
            MRealignQueue.write(AWidget);
            break;
        case SAT_WIDGET_REALIGN_PARENT:
            parent = AWidget->getParent();
            if (parent) MRealignQueue.write(parent);
            break;
        default:
            SAT_PRINT("Error! unhandled realign mode: %i\n",AMode);
    }
}

/*
    we handle opaque_parent != widget in paintWidgets()
*/

void SAT_WidgetWindow::do_widget_redraw(SAT_Widget* AWidget, uint32_t AMode)
{
    //SAT_PRINT("widget '%s'\n",AWidget->getName());
    // #ifdef SAT_NO_WINDOW_BUFFERING
    //     // if not buffered, we draw directly..
    //     SAT_Rect rect = AWidget->getRect();
    //     invalidate(rect.x,rect.y,rect.w,rect.h);
    // #else
    //    MRedrawQueue.write(AWidget);
    // #endif

    SAT_Widget* parent;
    switch (AMode)
    {
        case SAT_WIDGET_REDRAW_SELF:
            MRedrawQueue.write(AWidget);
            break;
        case SAT_WIDGET_REDRAW_PARENT:
            parent = AWidget->getParent();
            if (parent) MRedrawQueue.write(parent);
            break;
        //case SAT_WIDGET_REDRAW_OPAQUE_PARENT:
        //    parent = AWidget->getOpaqueParent();
        //    if (parent) MRedrawQueue.write(parent);
        //    break;
        default:
            SAT_PRINT("Error! unhandled redraw mode: %i\n",AMode);
    }

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
    //SAT_PRINT("widget '%s' type %i hint %i\n",AWidget->getName(),AType,AHint);
    if (MHintReceiver)
    {
        //intptr_t hint = (intptr_t)AWidget->getHint();
        switch (AType)
        {
            case SAT_WIDGET_HINT_NORMAL:
                MHintReceiver->on_widget_notify(AWidget,SAT_WIDGET_NOTIFY_HINT,(intptr_t)AHint);
                break;
            case SAT_WIDGET_HINT_CLEAR:
                MHintReceiver->on_widget_notify(AWidget,SAT_WIDGET_NOTIFY_HINT,(intptr_t)AHint);
                break;
            default:
                SAT_PRINT("Error! unknown hint type: %i\n",AType);
        }
    }
}

void SAT_WidgetWindow::do_widget_modal(SAT_Widget* AWidget)
{
    //SAT_PRINT("widget '%s'\n",AWidget->getName());
    MMouse.modalWidget = AWidget;
}

void SAT_WidgetWindow::do_widget_cursor(SAT_Widget* AWidget, int32_t ACursor)
{
    switch(ACursor)
    {
        case SAT_CURSOR_SHOW:  
        {
            showMouseCursor();
            setMouseCursorShape(MMouse.currentCursor);
            break;
        }
        case SAT_CURSOR_HIDE:
        {
            hideMouseCursor();
            break;
        }
        case SAT_CURSOR_LOCK:
        {
            lockMouseCursor();
            break;
        }
        case SAT_CURSOR_RESET:
        {
            if (MMouse.currentCursor != SAT_CURSOR_DEFAULT)
            {
                setMouseCursorShape(SAT_CURSOR_DEFAULT);
                MMouse.currentCursor = SAT_CURSOR_DEFAULT;
            }
        }
        case SAT_CURSOR_UNLOCK:
        {
            unlockMouseCursor();
            break;
        }
        default:
        {
            if (ACursor != MMouse.currentCursor)
            {
                setMouseCursorShape(ACursor);
                MMouse.currentCursor = ACursor;
            }
        }
    }
}

void SAT_WidgetWindow::do_widget_capture_mouse(SAT_Widget* AWidget)
{
    //SAT_PRINT("widget '%s'\n",AWidget->getName());
    MMouse.capturedWidget = AWidget;
}

void SAT_WidgetWindow::do_widget_capture_keyboard(SAT_Widget* AWidget)
{
    //SAT_PRINT("widget '%s'\n",AWidget->getName());
    MKeyCapturedWidget = AWidget;
}
