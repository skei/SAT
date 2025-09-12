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
        int32_t     enterState(int32_t AFromState) override;
        int32_t     leaveState(int32_t AToState) override;
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

int32_t SAT_IdleKeyboardState::enterState(int32_t AFromState)
{
    // SAT_PRINT("enterState from %i to %i\n",AFromState,id());
    return id();
}

int32_t SAT_IdleKeyboardState::leaveState(int32_t AToState)
{
    // SAT_PRINT("leaveState from %i to to %i\n",id(),AToState);
    return AToState;
}

//------------------------------
//
//------------------------------

int32_t SAT_IdleKeyboardState::timer(double ADelta)
{
    return SAT_KEYBOARD_STATE_NO_CHANGE;
}

int32_t SAT_IdleKeyboardState::press(uint32_t AKey, uint32_t AState, uint32_t ATime)
{
    return SAT_KEYBOARD_STATE_NO_CHANGE;
}

int32_t SAT_IdleKeyboardState::release(uint32_t AKey, uint32_t AState, uint32_t ATime)
{
    return SAT_KEYBOARD_STATE_NO_CHANGE;
}

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------
