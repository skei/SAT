#pragma once

#include "base/sat_base.h"
#include "gui/input/sat_input_state.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_MouseHoveringInputState
: public SAT_InputState
{
    public:
        SAT_MouseHoveringInputState(SAT_BaseInputHandler* AHandler);
        virtual ~SAT_MouseHoveringInputState();
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

SAT_MouseHoveringInputState::SAT_MouseHoveringInputState(SAT_BaseInputHandler* AHandler)
: SAT_InputState(AHandler)
{
    type = SAT_INPUT_STATE_MOUSE_HOVERING;
    name = "MOUSE HOVERING";
}

SAT_MouseHoveringInputState::~SAT_MouseHoveringInputState()
{
}

//------------------------------
//
//------------------------------

void SAT_MouseHoveringInputState::enter(int32_t AFromState)
{
    //SAT_TRACE;

    SAT_Widget* widget = stateInfo->hoverWidget;
    //stateInfo->activeTime = stateInfo->time;
    //stateInfo->activePos = stateInfo->mousePos;
    //stateInfo->activeButton = SAT_MOUSE_BUTTON_NONE;
    stateInfo->activeWidget = widget;
    uint32_t gesture = SAT_INPUT_GESTURE_MOUSE_HOVER;
    handler->sendGesture(widget,gesture);
}

void SAT_MouseHoveringInputState::leave(int32_t AToState)
{
}

//------------------------------
//
//------------------------------

int32_t SAT_MouseHoveringInputState::timer(double ADelta)
{
    return SAT_INPUT_STATE_NONE;
}

int32_t SAT_MouseHoveringInputState::mouseClick(SAT_InputEvent* AEvent)
{
    return SAT_INPUT_STATE_MOUSE_CLICKED;
}

int32_t SAT_MouseHoveringInputState::mouseRelease(SAT_InputEvent* AEvent)
{
    return SAT_INPUT_STATE_NONE;
}

int32_t SAT_MouseHoveringInputState::mouseMove(SAT_InputEvent* AEvent)
{
    // if we move mouse of of the hovering widget, go back to idle
    if (stateInfo->hoverWidget != stateInfo->activeWidget)
    {
        return SAT_INPUT_STATE_IDLE;
    }
    return SAT_INPUT_STATE_NONE;
}

int32_t SAT_MouseHoveringInputState::keyPress(SAT_InputEvent* AEvent)
{
    return SAT_INPUT_STATE_NONE;
}

int32_t SAT_MouseHoveringInputState::keyRelease(SAT_InputEvent* AEvent)
{
    return SAT_INPUT_STATE_NONE;
}
