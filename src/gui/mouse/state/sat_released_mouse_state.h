#pragma once

#include "base/sat_base.h"
#include "gui/mouse/sat_mouse_state.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_ReleasedMouseState
: public SAT_MouseState
{
    public:
        SAT_ReleasedMouseState(SAT_BaseMouseHandler* AHandler);
        virtual ~SAT_ReleasedMouseState();
    public:
        void        enter(int32_t AFromState) override;
        void        leave(int32_t AToState) override;
    public:
        int32_t     timer(double ADelta) override; 
        int32_t     click(SAT_MouseEvent* AEvent) override; 
        int32_t     release(SAT_MouseEvent* AEvent) override; 
        int32_t     move(SAT_MouseEvent* AEvent) override; 
};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

SAT_ReleasedMouseState::SAT_ReleasedMouseState(SAT_BaseMouseHandler* AHandler)
: SAT_MouseState(AHandler)
{
    type = SAT_MOUSE_STATE_RELEASED;
    name = "RELEASED";
}

SAT_ReleasedMouseState::~SAT_ReleasedMouseState()
{
}

//------------------------------
//
//------------------------------

void SAT_ReleasedMouseState::enter(int32_t AFromState)
{
    SAT_PRINT("from %s\n",handler->stateName(AFromState));
}

void SAT_ReleasedMouseState::leave(int32_t AToState)
{
}

//------------------------------
//
//------------------------------

int32_t SAT_ReleasedMouseState::timer(double ADelta)
{
    return SAT_MOUSE_STATE_NONE;
}

int32_t SAT_ReleasedMouseState::click(SAT_MouseEvent* AEvent)
{
    return SAT_MOUSE_STATE_CLICKED;
}

int32_t SAT_ReleasedMouseState::release(SAT_MouseEvent* AEvent)
{
    return SAT_MOUSE_STATE_NONE;
}

int32_t SAT_ReleasedMouseState::move(SAT_MouseEvent* AEvent)
{
    return SAT_MOUSE_STATE_NONE;
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
