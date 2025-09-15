#pragma once

#include "base/sat_base.h"
#include "gui/mouse/sat_mouse_state.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_DoubleClickedMouseState
: public SAT_MouseState
{
    public:
        SAT_DoubleClickedMouseState(SAT_BaseMouseHandler* AHandler);
        virtual ~SAT_DoubleClickedMouseState();
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

SAT_DoubleClickedMouseState::SAT_DoubleClickedMouseState(SAT_BaseMouseHandler* AHandler)
: SAT_MouseState(AHandler)
{
    type = SAT_MOUSE_STATE_DOUBLE_CLICKED;
    name = "DOUBLE CLICKED";
}

SAT_DoubleClickedMouseState::~SAT_DoubleClickedMouseState()
{
}

//------------------------------
//
//------------------------------

void SAT_DoubleClickedMouseState::enter(int32_t AFromState)
{
    SAT_PRINT("from %s\n",handler->stateName(AFromState));
}

void SAT_DoubleClickedMouseState::leave(int32_t AToState)
{
}

//------------------------------
//
//------------------------------

int32_t SAT_DoubleClickedMouseState::timer(double ADelta)
{
    return SAT_MOUSE_STATE_NONE;
}

int32_t SAT_DoubleClickedMouseState::click(SAT_MouseEvent* AEvent)
{
    return SAT_MOUSE_STATE_NONE;
}

int32_t SAT_DoubleClickedMouseState::release(SAT_MouseEvent* AEvent)
{
    return SAT_MOUSE_STATE_NONE;
}

int32_t SAT_DoubleClickedMouseState::move(SAT_MouseEvent* AEvent)
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

class SAT_DoubleClickedMouseState
: public SAT_MouseState
{
    SAT_DEFAULT_MOUSE_STATE(SAT_DoubleClickedMouseState)
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
        uint32_t    MClickedButton = SAT_MOUSE_BUTTON_NONE;
        double      MClickedTime = 0.0;
};

//------------------------------
//
//------------------------------

uint32_t SAT_DoubleClickedMouseState::id()
{
    return SAT_MOUSE_STATE_DOUBLE_CLICKED;
}

const char* SAT_DoubleClickedMouseState::name()
{
    return "DOUBLE CLICKED";
}

void SAT_DoubleClickedMouseState::enterState(int32_t AFromState)
{
    //SAT_PRINT("enterState from %i\n",AFromState);
}

void SAT_DoubleClickedMouseState::leaveState(int32_t AToState)
{
    //SAT_PRINT("leaveState to %i\n",AToState);
}

//------------------------------
//
//------------------------------

int32_t SAT_DoubleClickedMouseState::timer(double ADelta)
{
    return SAT_MOUSE_STATE_NONE;
}

int32_t SAT_DoubleClickedMouseState::click(SAT_MouseCoords APos, uint32_t AButton, uint32_t AState, uint32_t ATime)
{
    //SAT_PRINT("ignored: clicked button %i\n",AButton);
    return SAT_MOUSE_STATE_NONE;
}

int32_t SAT_DoubleClickedMouseState::release(SAT_MouseCoords APos, uint32_t AButton, uint32_t AState, uint32_t ATime)
{
    if (AButton == activeButton())
    {
        return SAT_MOUSE_STATE_DOUBLE_RELEASED;
    }
    else
    {
        //SAT_PRINT("ignored: released button %i\n",AButton);
    }
    return SAT_MOUSE_STATE_NONE;
}

int32_t SAT_DoubleClickedMouseState::move(SAT_MouseCoords APos, uint32_t AState, uint32_t ATime)
{
    return SAT_MOUSE_STATE_DOUBLE_DRAGGING;
}

#endif

