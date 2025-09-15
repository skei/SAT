#pragma once

#include "base/sat_base.h"
#include "gui/mouse/sat_mouse_state.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_ClickedMouseState
: public SAT_MouseState
{
    public:
        SAT_ClickedMouseState(SAT_BaseMouseHandler* AHandler);
        virtual ~SAT_ClickedMouseState();
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

SAT_ClickedMouseState::SAT_ClickedMouseState(SAT_BaseMouseHandler* AHandler)
: SAT_MouseState(AHandler)
{
    type = SAT_MOUSE_STATE_CLICKED;
    name = "CLICKED";
}

SAT_ClickedMouseState::~SAT_ClickedMouseState()
{
}

//------------------------------
//
//------------------------------

void SAT_ClickedMouseState::enter(int32_t AFromState)
{
    SAT_PRINT("from %s\n",handler->stateName(AFromState));
}

void SAT_ClickedMouseState::leave(int32_t AToState)
{
}

//------------------------------
//
//------------------------------

int32_t SAT_ClickedMouseState::timer(double ADelta)
{
    return SAT_MOUSE_STATE_NONE;
}

int32_t SAT_ClickedMouseState::click(SAT_MouseEvent* AEvent)
{
    return SAT_MOUSE_STATE_NONE;
}

int32_t SAT_ClickedMouseState::release(SAT_MouseEvent* AEvent)
{
    return SAT_MOUSE_STATE_IDLE;
}

int32_t SAT_ClickedMouseState::move(SAT_MouseEvent* AEvent)
{
    return SAT_MOUSE_STATE_DRAGGING;
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

class SAT_ClickedMouseState
: public SAT_MouseState
{
    SAT_DEFAULT_MOUSE_STATE(SAT_ClickedMouseState)
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

uint32_t SAT_ClickedMouseState::id()
{
    return SAT_MOUSE_STATE_CLICKED;
}

const char* SAT_ClickedMouseState::name()
{
    return "CLICKED";
}

void SAT_ClickedMouseState::enterState(int32_t AFromState)
{
    SAT_PRINT("enter from %s\n",AFromState,MHandler->stateName(AFromState));
    activeButton(clickedButton());
    // activePos(clickedPos());
    activeTime(clickedTime());
    sendGesture(SAT_MOUSE_GESTURE_CLICK);
}

void SAT_ClickedMouseState::leaveState(int32_t AToState)
{
    //SAT_PRINT("leaveState to %i\n",id(),AToState);
}

//------------------------------
//
//------------------------------

int32_t SAT_ClickedMouseState::timer(double ADelta)
{
    double elapsed = currentTime() - activeTime();
    if (elapsed >= SAT.GUI->getLongPressTime())
    {
        return SAT_MOUSE_STATE_LONG_CLICKED;
    }
    return SAT_MOUSE_STATE_NONE;
}

int32_t SAT_ClickedMouseState::click(SAT_MouseCoords APos, uint32_t AButton, uint32_t AState, uint32_t ATime)
{
    //SAT_PRINT("ignored: clicked button %i\n",AButton);
    return SAT_MOUSE_STATE_NONE;
}

int32_t SAT_ClickedMouseState::release(SAT_MouseCoords APos, uint32_t AButton, uint32_t AState, uint32_t ATime)
{
    if (AButton == activeButton())
    {
        return SAT_MOUSE_STATE_RELEASED;
    }
    else
    {
        //SAT_PRINT("ignored: released button %i\n",AButton);
    }
    return SAT_MOUSE_STATE_NONE;
}

int32_t SAT_ClickedMouseState::move(SAT_MouseCoords APos, uint32_t AState, uint32_t ATime)
{
    return SAT_MOUSE_STATE_DRAGGING;
}

#endif
