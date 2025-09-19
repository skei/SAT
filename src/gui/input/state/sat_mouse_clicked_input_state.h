#pragma once

#include "base/sat_base.h"
#include "gui/input/sat_input_state.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_MouseClickedInputState
: public SAT_InputState
{
    public:
        SAT_MouseClickedInputState(SAT_BaseInputHandler* AHandler);
        virtual ~SAT_MouseClickedInputState();
    public:
        void        enter(int32_t AFromState) override;
        void        leave(int32_t AToState) override;
    public:
        int32_t     timer(double ADelta) override; 
        int32_t     mouseClick(SAT_InputEvent* AEvent) override; 
        int32_t     mouseRelease(SAT_InputEvent* AEvent) override; 
        int32_t     mouseMove(SAT_InputEvent* AEvent) override;
        int32_t     keyPress(SAT_InputEvent* AEvent) override;
        int32_t     keyRelease(SAT_InputEvent* AEvent) override;
};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

SAT_MouseClickedInputState::SAT_MouseClickedInputState(SAT_BaseInputHandler* AHandler)
: SAT_InputState(AHandler)
{
    type = SAT_INPUT_STATE_MOUSE_CLICKED;
    name = "MOUSE CLICKED";
}

SAT_MouseClickedInputState::~SAT_MouseClickedInputState()
{
}

//------------------------------
//
//------------------------------

void SAT_MouseClickedInputState::enter(int32_t AFromState)
{
    SAT_Widget* widget = stateInfo->hoverWidget;
    stateInfo->activeTime = stateInfo->time;
    stateInfo->activePos = stateInfo->mousePos;
    stateInfo->activeButton = stateInfo->mouseButton;
    stateInfo->activeWidget = widget;
    uint32_t gesture = SAT_INPUT_GESTURE_MOUSE_CLICK;
    handler->sendGesture(widget,gesture);
}

void SAT_MouseClickedInputState::leave(int32_t AToState)
{
}

//------------------------------
//
//------------------------------

int32_t SAT_MouseClickedInputState::timer(double ADelta)
{
    // if SAT.GUI->getMouseLongPressTime() pass while holding the button,
    // enter long click state

    double elapsed = stateInfo->currentTime - stateInfo->activeTime;
    if (elapsed > SAT.GUI->getMouseLongPressTime())
    {
        // return SAT_INPUT_STATE_MOUSE_LONG_CLICK;
    }
    return SAT_INPUT_STATE_NONE;
}

int32_t SAT_MouseClickedInputState::mouseClick(SAT_InputEvent* AEvent)
{
    return SAT_INPUT_STATE_NONE;
}

int32_t SAT_MouseClickedInputState::mouseRelease(SAT_InputEvent* AEvent)
{
    // if released button is the same as the onc we clicked,
    // switch to released state

    if (stateInfo->mouseButton == stateInfo->activeButton)
    {
        return SAT_INPUT_STATE_MOUSE_RELEASED;
    }
    return SAT_INPUT_STATE_NONE;
}

int32_t SAT_MouseClickedInputState::mouseMove(SAT_InputEvent* AEvent)
{

    // only start drag if we move a tiny bit?

    SAT_MouseCoords src = AEvent->stateInfo->mousePos;
    SAT_MouseCoords dst = AEvent->stateInfo->activePos;
    double dist = SAT.GUI->getMouseMovementSlack();
    if (SAT_DistanceAbove(src.x,src.y,dst.x,dst.y,dist))
    {
        return SAT_INPUT_STATE_MOUSE_DRAGGING;
    }
    return SAT_INPUT_STATE_NONE;
}

int32_t SAT_MouseClickedInputState::keyPress(SAT_InputEvent* AEvent)
{
    return SAT_INPUT_STATE_NONE;
}

int32_t SAT_MouseClickedInputState::keyRelease(SAT_InputEvent* AEvent)
{
    return SAT_INPUT_STATE_NONE;
}










#if 0

#pragma once

#include "base/sat_base.h"
#include "gui/mouse/sat_mouse_state.h"
// #include "gui/window/sat_base_window.h"
// #include "gui/sat_widget.h"

//----------------------------------------------------------------------
//
// idle
//
//----------------------------------------------------------------------

class SAT_ClickedMouseState
: public SAT_MouseState
{
    SAT_DEFAULT_MOUSE_STATE(SAT_ClickedMouseState)
    public:
        uint32_t    id() override;
        const char* name() override;
        void        enterState(int32_t AFromState) override;
        void        leaveState(int32_t AToState) override;
    public:
        int32_t     timer(double ADelta) override; 
        int32_t     click(SAT_MouseCoords APos, uint32_t AButton, uint32_t AState, uint32_t ATime) override; 
        int32_t     release(SAT_MouseCoords APos, uint32_t AButton, uint32_t AState, uint32_t ATime) override; 
        int32_t     move(SAT_MouseCoords APos, uint32_t AState, uint32_t ATime) override; 
    private:
};

//------------------------------
//
//------------------------------

uint32_t SAT_ClickedMouseState::id()
{
    return SAT_MOUSE_STATE_CLICKED;
}

const char* SAT_ClickedMouseState::name()
{
    return "CLICKED";
}

void SAT_ClickedMouseState::enterState(int32_t AFromState)
{
    SAT_PRINT("enter from %s\n",AFromState,MHandler->stateName(AFromState));
    activeButton(clickedButton());
    // activePos(clickedPos());
    activeTime(clickedTime());
    sendGesture(SAT_MOUSE_GESTURE_CLICK);
}

void SAT_ClickedMouseState::leaveState(int32_t AToState)
{
    //SAT_PRINT("leaveState to %i\n",id(),AToState);
}

//------------------------------
//
//------------------------------

int32_t SAT_ClickedMouseState::timer(double ADelta)
{
    double elapsed = currentTime() - activeTime();
    if (elapsed >= SAT.GUI->getLongPressTime())
    {
        return SAT_MOUSE_STATE_LONG_CLICKED;
    }
    return SAT_MOUSE_STATE_NONE;
}

int32_t SAT_ClickedMouseState::click(SAT_MouseCoords APos, uint32_t AButton, uint32_t AState, uint32_t ATime)
{
    //SAT_PRINT("ignored: clicked button %i\n",AButton);
    return SAT_MOUSE_STATE_NONE;
}

int32_t SAT_ClickedMouseState::release(SAT_MouseCoords APos, uint32_t AButton, uint32_t AState, uint32_t ATime)
{
    if (AButton == activeButton())
    {
        return SAT_MOUSE_STATE_RELEASED;
    }
    else
    {
        //SAT_PRINT("ignored: released button %i\n",AButton);
    }
    return SAT_MOUSE_STATE_NONE;
}

int32_t SAT_ClickedMouseState::move(SAT_MouseCoords APos, uint32_t AState, uint32_t ATime)
{
    return SAT_MOUSE_STATE_DRAGGING;
}

#endif
