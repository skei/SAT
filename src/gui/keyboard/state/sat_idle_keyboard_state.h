#pragma once

#include "base/sat_base.h"
#include "gui/keyboard/sat_keyboard_state.h"

//----------------------------------------------------------------------
//
// idle
//
//----------------------------------------------------------------------

class SAT_IdleKeyboardState
: public SAT_KeyboardState
{
    SAT_DEFAULT_KEYBOARD_STATE(SAT_IdleKeyboardState)
    public:
        uint32_t    id() override;
        void        enterState(int32_t AFromState) override;
        void        leaveState(int32_t AToState) override;
    public:
        int32_t     timer(double ADelta) override; 
        int32_t     press(uint32_t AKey, uint32_t AState, uint32_t ATime) override; 
        int32_t     release(uint32_t AKey, uint32_t AState, uint32_t ATime) override; 
};

//------------------------------
//
//------------------------------

uint32_t SAT_IdleKeyboardState::id()
{
    return SAT_KEYBOARD_STATE_IDLE;
}

void SAT_IdleKeyboardState::enterState(int32_t AFromState)
{
    SAT_PRINT("enterState from %i to %i\n",AFromState,id());
}

void SAT_IdleKeyboardState::leaveState(int32_t AToState)
{
    SAT_PRINT("leaveState from %i to to %i\n",id(),AToState);
}

//------------------------------
//
//------------------------------

int32_t SAT_IdleKeyboardState::timer(double ADelta)
{
    return SAT_KEYBOARD_STATE_NONE;
}

int32_t SAT_IdleKeyboardState::press(uint32_t AKey, uint32_t AState, uint32_t ATime)
{
    int32_t event_response = sendEvent(capturedWidget(),SAT_KEYBOARD_EVENT_PRESS);
    if (event_response != SAT_KEYBOARD_EVENT_RESPONSE_IGNORE)
    {
    }
    return SAT_KEYBOARD_STATE_NONE;
}

int32_t SAT_IdleKeyboardState::release(uint32_t AKey, uint32_t AState, uint32_t ATime)
{
    int32_t event_response = sendEvent(capturedWidget(),SAT_KEYBOARD_EVENT_RELEASE);
    if (event_response != SAT_KEYBOARD_EVENT_RESPONSE_IGNORE)
    {
    }
    return SAT_KEYBOARD_STATE_NONE;
}

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------
