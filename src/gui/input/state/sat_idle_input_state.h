#pragma once

#include "base/sat_base.h"
#include "gui/input/sat_input_state.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_IdleInputState
: public SAT_InputState
{
    public:
        SAT_IdleInputState(SAT_BaseInputHandler* AHandler);
        virtual ~SAT_IdleInputState();
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
    public:
        double      MLastMovedTime      = 0.0;
        //SAT_Widget* MLastMovedWidget    = nullptr;
};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

SAT_IdleInputState::SAT_IdleInputState(SAT_BaseInputHandler* AHandler)
: SAT_InputState(AHandler)
{
    type = SAT_INPUT_STATE_IDLE;
    name = "IDLE";
}

SAT_IdleInputState::~SAT_IdleInputState()
{
}

//------------------------------
//
//------------------------------

void SAT_IdleInputState::enter(int32_t AFromState)
{
    //SAT_TRACE;
    MLastMovedTime = stateInfo->currentTime;
}

void SAT_IdleInputState::leave(int32_t AToState)
{
}

//------------------------------
//
//------------------------------

int32_t SAT_IdleInputState::timer(double ADelta)
{
    // if time elapsed sice last moved > SAT.GUI->getMouseHoverHoldTime()
    // enter mouse hover state
    // notify lasthoverwidget

    double elapsed = stateInfo->currentTime - MLastMovedTime;
    if (elapsed > SAT.GUI->getMouseHoverHoldTime())
    {
        //SAT_PRINT("hover\n");
        return SAT_INPUT_STATE_MOUSE_HOVERING;
    }

    return SAT_INPUT_STATE_NONE;
}

int32_t SAT_IdleInputState::mouseClick(SAT_InputEvent* AEvent)
{
    return SAT_INPUT_STATE_MOUSE_CLICKED;
}

int32_t SAT_IdleInputState::mouseRelease(SAT_InputEvent* AEvent)
{
    return SAT_INPUT_STATE_NONE;
}

int32_t SAT_IdleInputState::mouseMove(SAT_InputEvent* AEvent)
{
    MLastMovedTime = AEvent->stateInfo->time;
    // MLastHoveredWidget = AEvent->stateInfo.hoverWidget;
    return SAT_INPUT_STATE_NONE;
}

int32_t SAT_IdleInputState::keyPress(SAT_InputEvent* AEvent)
{
    return SAT_INPUT_STATE_NONE;
}

int32_t SAT_IdleInputState::keyRelease(SAT_InputEvent* AEvent)
{
    return SAT_INPUT_STATE_NONE;
}
