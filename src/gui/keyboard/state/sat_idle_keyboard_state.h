#pragma once

#include "base/sat_base.h"
#include "gui/keyboard/sat_keyboard_state.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_IdleKeyboardState
: public SAT_KeyboardState
{
    public:
        SAT_IdleKeyboardState(SAT_BaseKeyboardHandler* AHandler);
        virtual ~SAT_IdleKeyboardState();
    public:
        void        enter(int32_t AFromState) override;
        void        leave(int32_t AToState) override;
    public:
        int32_t     timer(double ADelta) override; 
        int32_t     press(SAT_KeyboardEvent* AEvent) override; 
        int32_t     release(SAT_KeyboardEvent* AEvent) override; 
};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

SAT_IdleKeyboardState::SAT_IdleKeyboardState(SAT_BaseKeyboardHandler* AHandler)
: SAT_KeyboardState(AHandler)
{
    type = SAT_KEYBOARD_STATE_IDLE;
    name = "IDLE";
}

SAT_IdleKeyboardState::~SAT_IdleKeyboardState()
{
}

//------------------------------
//
//------------------------------

void SAT_IdleKeyboardState::enter(int32_t AFromState)
{
    SAT_PRINT("from %s\n",handler->stateName(AFromState));
}

void SAT_IdleKeyboardState::leave(int32_t AToState)
{
}

//------------------------------
//
//------------------------------

int32_t SAT_IdleKeyboardState::timer(double ADelta)
{
    return SAT_KEYBOARD_STATE_NONE;
}

int32_t SAT_IdleKeyboardState::press(SAT_KeyboardEvent* AEvent)
{
    return SAT_KEYBOARD_STATE_NONE;
}

int32_t SAT_IdleKeyboardState::release(SAT_KeyboardEvent* AEvent)
{
    return SAT_KEYBOARD_STATE_NONE;
}
