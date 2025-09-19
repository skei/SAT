#pragma once

#include "base/sat_base.h"
#include "gui/input/sat_input_state.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_MouseReleasedInputState
: public SAT_InputState
{
    public:
        SAT_MouseReleasedInputState(SAT_BaseInputHandler* AHandler);
        virtual ~SAT_MouseReleasedInputState();
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
    private:
        double MReleasedTime = 0.0;
};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

SAT_MouseReleasedInputState::SAT_MouseReleasedInputState(SAT_BaseInputHandler* AHandler)
: SAT_InputState(AHandler)
{
    type = SAT_INPUT_STATE_MOUSE_RELEASED;
    name = "MOUSE RELEASED";
}

SAT_MouseReleasedInputState::~SAT_MouseReleasedInputState()
{
}

//------------------------------
//
//------------------------------

void SAT_MouseReleasedInputState::enter(int32_t AFromState)
{
    MReleasedTime = stateInfo->currentTime;
    //SAT_PRINT("from %s\n",handler->stateName(AFromState));
    SAT_Widget* widget = stateInfo->activeWidget;
    uint32_t gesture = SAT_INPUT_GESTURE_MOUSE_RELEASE;
    handler->sendGesture(widget,gesture);    
}

void SAT_MouseReleasedInputState::leave(int32_t AToState)
{
    //SAT_PRINT("to %s\n",handler->stateName(AToState));
}

//------------------------------
//
//------------------------------

int32_t SAT_MouseReleasedInputState::timer(double ADelta)
{
    // if too long time have passed, return to idle (too late for double clicking)
    double elapsed = stateInfo->currentTime - MReleasedTime;
    if (elapsed > SAT.GUI->getMouseDoubleClickTime())
    {
        return SAT_INPUT_STATE_IDLE;
    }
    return SAT_INPUT_STATE_NONE;
}

int32_t SAT_MouseReleasedInputState::mouseClick(SAT_InputEvent* AEvent)
{
    double elapsed = stateInfo->time - stateInfo->activeTime; // MReleasedTime
    if (stateInfo->mouseButton == stateInfo->activeButton)
    {
        if (elapsed < SAT.GUI->getMouseDoubleClickTime())
        {
            SAT_PRINT("double click\n");
            //return SAT_MOUSE_STATE_DOUBLE_CLICK;
        }
    }
    return SAT_INPUT_STATE_MOUSE_CLICKED;
}

int32_t SAT_MouseReleasedInputState::mouseRelease(SAT_InputEvent* AEvent)
{
    return SAT_INPUT_STATE_NONE;
}

int32_t SAT_MouseReleasedInputState::mouseMove(SAT_InputEvent* AEvent)
{
    // if we moved the mouse, so we can't double click
    // (within SAT.GUI->getMouseMovementSlack()?)
    // return SAT_INPUT_STATE_IDLE;

    return SAT_INPUT_STATE_NONE;
}

int32_t SAT_MouseReleasedInputState::keyPress(SAT_InputEvent* AEvent)
{
    return SAT_INPUT_STATE_NONE;
}

int32_t SAT_MouseReleasedInputState::keyRelease(SAT_InputEvent* AEvent)
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

class SAT_ReleasedMouseState
: public SAT_MouseState
{
    SAT_DEFAULT_MOUSE_STATE(SAT_ReleasedMouseState)
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

uint32_t SAT_ReleasedMouseState::id()
{
    return SAT_MOUSE_STATE_RELEASED;
}

const char* SAT_ReleasedMouseState::name()
{
    return "RELEASED";
}

void SAT_ReleasedMouseState::enterState(int32_t AFromState)
{
    //SAT_PRINT("enterState from %i\n",AFromState);
    sendGesture(SAT_MOUSE_GESTURE_RELEASE);
}

void SAT_ReleasedMouseState::leaveState(int32_t AToState)
{
    //SAT_PRINT("leaveState to %i\n",AToState);
}

//------------------------------
//
//------------------------------

int32_t SAT_ReleasedMouseState::timer(double ADelta)
{
    return SAT_MOUSE_STATE_NONE;
}

int32_t SAT_ReleasedMouseState::click(SAT_MouseCoords APos, uint32_t AButton, uint32_t AState, uint32_t ATime)
{
    if (AButton == activeButton())
    {
        double elapsed = currentTime() - activeTime();
        if (elapsed <= SAT.GUI->getDoubleClickTime())
        {
            return SAT_MOUSE_STATE_DOUBLE_CLICKED;
        }
    }
    return SAT_MOUSE_STATE_CLICKED;
}

int32_t SAT_ReleasedMouseState::release(SAT_MouseCoords APos, uint32_t AButton, uint32_t AState, uint32_t ATime)
{
    //SAT_PRINT("ignored: released button %i\n",AButton);
    return SAT_MOUSE_STATE_IDLE;
}

int32_t SAT_ReleasedMouseState::move(SAT_MouseCoords APos, uint32_t AState, uint32_t ATime)
{
    // todo: wait until we have moved a few pixels until we return do idle?
    // to 'switch off' double clicking..
    return SAT_MOUSE_STATE_IDLE;
}

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------


#endif
