#pragma once

#include "base/sat_base.h"
#include "gui/mouse/sat_mouse_state.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_DoubleDraggingMouseState
: public SAT_MouseState
{
    public:
        SAT_DoubleDraggingMouseState(SAT_BaseMouseHandler* AHandler);
        virtual ~SAT_DoubleDraggingMouseState();
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

SAT_DoubleDraggingMouseState::SAT_DoubleDraggingMouseState(SAT_BaseMouseHandler* AHandler)
: SAT_MouseState(AHandler)
{
    type = SAT_MOUSE_STATE_DOUBLE_DRAGGING;
    name = "DOUBLE DRAGGING";
}

SAT_DoubleDraggingMouseState::~SAT_DoubleDraggingMouseState()
{
}

//------------------------------
//
//------------------------------

void SAT_DoubleDraggingMouseState::enter(int32_t AFromState)
{
    SAT_PRINT("from %s\n",handler->stateName(AFromState));
}

void SAT_DoubleDraggingMouseState::leave(int32_t AToState)
{
}

//------------------------------
//
//------------------------------

int32_t SAT_DoubleDraggingMouseState::timer(double ADelta)
{
    return SAT_MOUSE_STATE_NONE;
}

int32_t SAT_DoubleDraggingMouseState::click(SAT_MouseEvent* AEvent)
{
    return SAT_MOUSE_STATE_NONE;
}

int32_t SAT_DoubleDraggingMouseState::release(SAT_MouseEvent* AEvent)
{
    return SAT_MOUSE_STATE_NONE;
}

int32_t SAT_DoubleDraggingMouseState::move(SAT_MouseEvent* AEvent)
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

class SAT_DoubleDraggingMouseState
: public SAT_MouseState
{
    SAT_DEFAULT_MOUSE_STATE(SAT_DoubleDraggingMouseState)
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

uint32_t SAT_DoubleDraggingMouseState::id()
{
    return SAT_MOUSE_STATE_DOUBLE_DRAGGING;
}

const char* SAT_DoubleDraggingMouseState::name()
{
    return "DOUBLE DRAGGING";
}

void SAT_DoubleDraggingMouseState::enterState(int32_t AFromState)
{
    //SAT_PRINT("enterState from %i\n",AFromState);
}

void SAT_DoubleDraggingMouseState::leaveState(int32_t AToState)
{
    //SAT_PRINT("leaveState to %i\n",AToState);
}

//------------------------------
//
//------------------------------

int32_t SAT_DoubleDraggingMouseState::timer(double ADelta)
{
    return SAT_MOUSE_STATE_NONE;
}

int32_t SAT_DoubleDraggingMouseState::click(SAT_MouseCoords APos, uint32_t AButton, uint32_t AState, uint32_t ATime)
{
    //SAT_PRINT("ignored: clicked button %i\n",AButton);
    return SAT_MOUSE_STATE_NONE;
}

int32_t SAT_DoubleDraggingMouseState::release(SAT_MouseCoords APos, uint32_t AButton, uint32_t AState, uint32_t ATime)
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

int32_t SAT_DoubleDraggingMouseState::move(SAT_MouseCoords APos, uint32_t AState, uint32_t ATime)
{
    return SAT_MOUSE_STATE_NONE;
}

#endif

