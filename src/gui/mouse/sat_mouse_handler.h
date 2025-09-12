#pragma once

#include "base/sat_base.h"
#include "gui/mouse/sat_base_mouse_handler.h"
#include "gui/mouse/sat_mouse_states.h"
#include "gui/window/sat_widget_window.h"
#include "gui/sat_widget.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_MouseHandler
: public SAT_BaseMouseHandler
{

    friend class SAT_Window;

    public:

        SAT_MouseHandler(SAT_WidgetWindow* AWindow);
        virtual ~SAT_MouseHandler();

    public:

        SAT_WidgetWindow*   getWindow() override;

    private:

        void                setupStates();
        void                handleState(int32_t AState);

        void                captureWidget(SAT_Widget* AWidget);

        void                lockCursor(SAT_Widget* AWidget);
        void                unlockCursor();
        SAT_MouseCoords     adjustPos(SAT_MouseCoords APos);

    public:
    
        void                timer(double ADelta) override;
        void                click(SAT_MouseCoords APos, uint32_t AButton, uint32_t AState, uint32_t ATime) override;
        void                release(SAT_MouseCoords APos, uint32_t AButton, uint32_t AState, uint32_t ATime) override;
        void                move(SAT_MouseCoords APos, uint32_t AState, uint32_t ATime) override;
        void                enter(SAT_MouseCoords APos, uint32_t ATime) override;
        void                leave(SAT_MouseCoords APos, uint32_t ATime) override;

    private:

        SAT_WidgetWindow*   MWindow                             = nullptr;
        SAT_MouseState*     MMouseStates[SAT_MOUSE_STATE_COUNT] = {};
        SAT_MouseState*     MCurrentState                       = nullptr;
        uint32_t            MCurrentStateId                     = SAT_MOUSE_STATE_IDLE;

};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

SAT_MouseHandler::SAT_MouseHandler(SAT_WidgetWindow* AWindow)
: SAT_BaseMouseHandler()
{
    MWindow = AWindow;
    setupStates();
    MCurrentState = MMouseStates[SAT_MOUSE_STATE_IDLE];
}

SAT_MouseHandler::~SAT_MouseHandler()
{
    #ifndef SAT_NO_AUTODELETE
        for (uint32_t i=0; i<SAT_MOUSE_STATE_COUNT; i++) delete MMouseStates[i];
    #endif
}

SAT_WidgetWindow* SAT_MouseHandler::getWindow()
{
    return MWindow;
}

//------------------------------
//
//------------------------------

void SAT_MouseHandler::setupStates()
{
    MMouseStates[SAT_MOUSE_STATE_IDLE]      = new SAT_IdleMouseState(this);
    MMouseStates[SAT_MOUSE_STATE_HOVER]  = new SAT_HoverMouseState(this);
}

void SAT_MouseHandler::handleState(int32_t AState)
{
    SAT_Assert(AState < SAT_MOUSE_STATE_COUNT);
    if (AState >= 0)
    {
        SAT_PRINT("%i\n",AState);
        MWindow->handleMouseStateChange(MCurrentState,AState);
        int32_t current_state_id = MCurrentState->id();
        int32_t new_state_id = AState;
        if (new_state_id != current_state_id)
        {
            new_state_id = MCurrentState->leaveState(new_state_id);
            SAT_MouseState* new_state = MMouseStates[new_state_id];
            new_state_id = new_state->enterState(current_state_id);
            MCurrentState = MMouseStates[new_state_id];
        }
    }
}

void SAT_MouseHandler::captureWidget(SAT_Widget* AWidget)
{
    MCapturedWidget = AWidget;
}

void SAT_MouseHandler::lockCursor(SAT_Widget* AWidget)
{
    MLocked = true;
    MLockedPos = MCurrentPos;
    MLockedVirtualPos = MCurrentPos;
    MLockedWidget = AWidget;
}

void SAT_MouseHandler::unlockCursor()
{
    MLocked = false;
}

SAT_MouseCoords SAT_MouseHandler::adjustPos(SAT_MouseCoords APos)
{
    if (MLocked)
    {
        if ((APos.x != MLockedPos.x) || (APos.y != MLockedPos.y))
        {
            int32_t xdiff = APos.x - MLockedPos.x;
            int32_t ydiff = APos.y - MLockedPos.y;
            MLockedVirtualPos.x += xdiff;
            MLockedVirtualPos.y += ydiff;
            MWindow->setMouseCursorPos(MLockedPos.x,MLockedPos.y);
            return MLockedVirtualPos;
        }
    }
    return APos;
}

//------------------------------
//
//------------------------------

void SAT_MouseHandler::timer(double ADelta)
{
    MCurrentTime += ADelta;
    // SAT_PRINT("MCurrentTime %.3f MPrevTimeMoved %.3f\n",MCurrentTime,MPrevTimeMoved);
    int32_t state = MCurrentState->timer(ADelta);
    handleState(state);

    /*
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
            Mouse.c    MMouse.waitingForTooltip = false;
                MMouse.tooltipVisible = true;
                showTooltip(MMouse.currentPos.x,MMouse.currentPos.y,MMouse.tooltipWidget);
            }
            MMouse.tooltipAllowed = false;
        }
    }
    */
}

void SAT_MouseHandler::click(SAT_MouseCoords APos, uint32_t AButton, uint32_t AState, uint32_t ATime)
{
    MClickedPos = APos;
    MClickedButton = AButton;
    MClickedModKeys = AState;
    MClickedTime = MCurrentTime;
    MClickedWidget = MCurrentWidget;
    MCurrentButtons |= (uint32_t)(1 << (AButton - 1));
    if (MCurrentWidget && MCurrentWidget->Options.wantMouseEvent & SAT_MOUSE_EVENT_CLICK) MCurrentWidget->on_widget_mouse_event(SAT_MOUSE_EVENT_CLICK,MCurrentState);
    int32_t state = MCurrentState->click(APos,AButton,AState,ATime);
    handleState(state);
}

void SAT_MouseHandler::release(SAT_MouseCoords APos, uint32_t AButton, uint32_t AState, uint32_t ATime)
{
    MReleasedPos = APos;
    MReleasedButton = AButton;
    MReleasedModKeys = AState;
    MReleasedTime = MCurrentTime;
    MReleasedWidget = MCurrentWidget;
    MCurrentButtons &= ~(uint32_t)(1 << (AButton - 1));
    if (MCurrentWidget && MCurrentWidget->Options.wantMouseEvent & SAT_MOUSE_EVENT_RELEASE) MCurrentWidget->on_widget_mouse_event(SAT_MOUSE_EVENT_RELEASE,MCurrentState);
    int32_t state = MCurrentState->release(APos,AButton,AState,ATime);
    handleState(state);
}

void SAT_MouseHandler::move(SAT_MouseCoords APos, uint32_t AState, uint32_t ATime)
{
    APos = adjustPos(APos);
    MPrevPos = MCurrentPos;
    MPrevTimeMoved = MCurrentTime;
    MCurrentPos = APos;
    MCurrentModKeys = AState;
    MPrevWidget = MCurrentWidget;
    MCurrentWidget = MWindow->findChildAt(APos.x,APos.y);
    if (MCurrentWidget != MPrevWidget)
    {
        if (MPrevWidget && MPrevWidget->Options.wantMouseEvent & SAT_MOUSE_EVENT_LEAVE) MPrevWidget->on_widget_mouse_event(SAT_MOUSE_EVENT_LEAVE,MCurrentState);
        if (MCurrentWidget && MCurrentWidget->Options.wantMouseEvent & SAT_MOUSE_EVENT_ENTER) MCurrentWidget->on_widget_mouse_event(SAT_MOUSE_EVENT_ENTER,MCurrentState);
    }
    if (MCurrentWidget && MCurrentWidget->Options.wantMouseEvent & SAT_MOUSE_EVENT_MOVE) MCurrentWidget->on_widget_mouse_event(SAT_MOUSE_EVENT_MOVE,MCurrentState);
    int32_t state = MCurrentState->move(APos,AState,ATime);
    handleState(state);
}

void SAT_MouseHandler::enter(SAT_MouseCoords APos, uint32_t ATime)
{
}

void SAT_MouseHandler::leave(SAT_MouseCoords APos, uint32_t ATime)
{
    MCurrentWidget = nullptr;
}

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

#if 0

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

void SAT_Window::on_window_mouse_click(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATime)
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

void SAT_Window::on_window_mouse_release(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATime)
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

void SAT_Window::on_window_mouse_move(int32_t AXpos, int32_t AYpos, uint32_t AState, uint32_t ATime)
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

void SAT_Window::on_window_mouse_enter(int32_t AXpos, int32_t AYpos, uint32_t ATime)
{
    updateHover(AXpos,AYpos,ATime);
    MMouse.tooltipAllowed = true;
}

void SAT_Window::on_window_mouse_leave(int32_t AXpos, int32_t AYpos, uint32_t ATime)
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

#endif // 0
