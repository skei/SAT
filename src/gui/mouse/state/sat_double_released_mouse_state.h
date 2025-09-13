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

class SAT_DoubleReleasedMouseState
: public SAT_MouseState
{
    SAT_DEFAULT_MOUSE_STATE(SAT_DoubleReleasedMouseState)
    public:
        uint32_t    id() override;
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

uint32_t SAT_DoubleReleasedMouseState::id()
{
    return SAT_MOUSE_STATE_DOUBLE_RELEASED;
}

void SAT_DoubleReleasedMouseState::enterState(int32_t AFromState)
{
    SAT_PRINT("enterState from %i\n",AFromState);
}

void SAT_DoubleReleasedMouseState::leaveState(int32_t AToState)
{
    //SAT_PRINT("leaveState to %i\n",AToState);
}

//------------------------------
//
//------------------------------

int32_t SAT_DoubleReleasedMouseState::timer(double ADelta)
{
    return SAT_MOUSE_STATE_NONE;
}

int32_t SAT_DoubleReleasedMouseState::click(SAT_MouseCoords APos, uint32_t AButton, uint32_t AState, uint32_t ATime)
{
    int32_t event_response = sendEvent(currentWidget(),SAT_MOUSE_EVENT_CLICK);
    if (event_response != SAT_MOUSE_EVENT_RESPONSE_IGNORE)
    {
        return SAT_MOUSE_STATE_CLICKED;
    }
    return SAT_MOUSE_STATE_NONE;
}

int32_t SAT_DoubleReleasedMouseState::release(SAT_MouseCoords APos, uint32_t AButton, uint32_t AState, uint32_t ATime)
{
    int32_t event_response = sendEvent(currentWidget(),SAT_MOUSE_EVENT_RELEASE);
    if (event_response != SAT_MOUSE_EVENT_RESPONSE_IGNORE)
    {
        SAT_PRINT("ignored: released button %i\n",AButton);
        return SAT_MOUSE_STATE_IDLE;
    }
    return SAT_MOUSE_STATE_NONE;
}

int32_t SAT_DoubleReleasedMouseState::move(SAT_MouseCoords APos, uint32_t AState, uint32_t ATime)
{
    if (currentWidget() != prevWidget())
    {
        int32_t prev_response = sendEvent(prevWidget(),SAT_MOUSE_EVENT_LEAVE);
        int32_t current_response = sendEvent(currentWidget(),SAT_MOUSE_EVENT_ENTER);
    }
    int32_t event_response = sendEvent(currentWidget(),SAT_MOUSE_EVENT_MOVE);
    if (event_response != SAT_MOUSE_EVENT_RESPONSE_IGNORE)
    {
        // todo: wait until we have moved a few pixels until we return do idle?
        // to 'switch off' double clicking..
        return SAT_MOUSE_STATE_IDLE;
    }
    return SAT_MOUSE_STATE_NONE;
}

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------
