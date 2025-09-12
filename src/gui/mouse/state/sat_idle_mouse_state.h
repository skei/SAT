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

class SAT_IdleMouseState
: public SAT_MouseState
{
    SAT_DEFAULT_MOUSE_STATE(SAT_IdleMouseState)
    public:
        uint32_t    id() override;
        int32_t     enterState(int32_t AFromState) override;
        int32_t     leaveState(int32_t AToState) override;
    public:
        int32_t     timer(double ADelta) override; 
        int32_t     click(SAT_MouseCoords APos, uint32_t AButton, uint32_t AState, uint32_t ATime) override; 
        int32_t     release(SAT_MouseCoords APos, uint32_t AButton, uint32_t AState, uint32_t ATime) override; 
        int32_t     move(SAT_MouseCoords APos, uint32_t AState, uint32_t ATime) override; 
};

//------------------------------
//
//------------------------------

uint32_t SAT_IdleMouseState::id()
{
    return SAT_MOUSE_STATE_IDLE;
}

int32_t SAT_IdleMouseState::enterState(int32_t AFromState)
{
    // SAT_PRINT("enterState from %i to %i\n",AFromState,id());
    return id();
}

int32_t SAT_IdleMouseState::leaveState(int32_t AToState)
{
    // SAT_PRINT("leaveState from %i to to %i\n",id(),AToState);
    return AToState;
}

//------------------------------
//
//------------------------------

int32_t SAT_IdleMouseState::timer(double ADelta)
{
    return SAT_MOUSE_STATE_NO_CHANGE;
}

int32_t SAT_IdleMouseState::click(SAT_MouseCoords APos, uint32_t AButton, uint32_t AState, uint32_t ATime)
{
    return SAT_MOUSE_STATE_NO_CHANGE;
}

int32_t SAT_IdleMouseState::release(SAT_MouseCoords APos, uint32_t AButton, uint32_t AState, uint32_t ATime)
{
    return SAT_MOUSE_STATE_NO_CHANGE;
}

int32_t SAT_IdleMouseState::move(SAT_MouseCoords APos, uint32_t AState, uint32_t ATime)
{
    return SAT_MOUSE_STATE_NO_CHANGE;
}

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------
