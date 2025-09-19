#pragma once

#include "base/sat_base.h"
#include "gui/input/sat_input_state.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_MouseDraggingInputState
: public SAT_InputState
{
    public:
        SAT_MouseDraggingInputState(SAT_BaseInputHandler* AHandler);
        virtual ~SAT_MouseDraggingInputState();
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
    private:
        double      MPrevMoveTime       = 0.0;
        SAT_Widget* MPrevHoverWidget    = nullptr;
        bool        MWaitingForHover    = false;
};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

SAT_MouseDraggingInputState::SAT_MouseDraggingInputState(SAT_BaseInputHandler* AHandler)
: SAT_InputState(AHandler)
{
    type = SAT_INPUT_STATE_MOUSE_DRAGGING;
    name = "MOUSE DRAGGING";
}

SAT_MouseDraggingInputState::~SAT_MouseDraggingInputState()
{
}

//------------------------------
//
//------------------------------

void SAT_MouseDraggingInputState::enter(int32_t AFromState)
{
    SAT_Widget* widget = stateInfo->activeWidget; // hover_widget;
    uint32_t gesture = SAT_INPUT_GESTURE_BEGIN | SAT_INPUT_GESTURE_MOUSE_DRAG;
    handler->sendGesture(widget,gesture);    
    MPrevMoveTime = stateInfo->currentTime;
    MPrevHoverWidget = stateInfo->hoverWidget;
    MWaitingForHover = false;
}

void SAT_MouseDraggingInputState::leave(int32_t AToState)
{
}

//------------------------------
//
//------------------------------

int32_t SAT_MouseDraggingInputState::timer(double ADelta)
{
    if (MWaitingForHover)
    {
        double elapsed = stateInfo->currentTime - MPrevMoveTime;
        if (elapsed > SAT.GUI->getMouseHoverHoldTime())
        {
            SAT_Widget* widget = stateInfo->activeWidget;
            uint32_t gesture = SAT_INPUT_GESTURE_DRAG | SAT_INPUT_GESTURE_MOUSE_HOVER;
            handler->sendGesture(widget,gesture);    
            MWaitingForHover = false;
        }
    }
    return SAT_INPUT_STATE_NONE;
}

int32_t SAT_MouseDraggingInputState::mouseClick(SAT_InputEvent* AEvent)
{
    SAT_Widget* widget = stateInfo->activeWidget;
    uint32_t gesture = SAT_INPUT_GESTURE_DRAG | SAT_INPUT_GESTURE_MOUSE_CLICK;
    handler->sendGesture(widget,gesture);
    MWaitingForHover = false;
    return SAT_INPUT_STATE_NONE;
}

int32_t SAT_MouseDraggingInputState::mouseRelease(SAT_InputEvent* AEvent)
{
    // if we release the button that stared the drag,
    // send end drag gesture, and return to released state
    if (stateInfo->mouseButton == stateInfo->activeButton)
    {
        SAT_Widget* widget = stateInfo->activeWidget;
        uint32_t gesture = SAT_INPUT_GESTURE_END | SAT_INPUT_GESTURE_MOUSE_DRAG;
        handler->sendGesture(widget,gesture);
        return SAT_INPUT_STATE_MOUSE_RELEASED;
    }
    else
    {
        SAT_Widget* widget = stateInfo->activeWidget;
        uint32_t gesture = SAT_INPUT_GESTURE_DRAG | SAT_INPUT_GESTURE_MOUSE_RELEASE;
        handler->sendGesture(widget,gesture);
        MWaitingForHover = false;
    }
    return SAT_INPUT_STATE_NONE;
}

int32_t SAT_MouseDraggingInputState::mouseMove(SAT_InputEvent* AEvent)
{
    // if we cross to another widget, start accepting hover events
    if (stateInfo->hoverWidget != MPrevHoverWidget)
    {
        MPrevHoverWidget = stateInfo->hoverWidget;
        MWaitingForHover = true;
    }
    MPrevMoveTime = stateInfo->currentTime;

    SAT_Widget* widget = stateInfo->activeWidget;
    uint32_t gesture = SAT_INPUT_GESTURE_MOUSE_DRAG;
    handler->sendGesture(widget,gesture);
    return SAT_INPUT_STATE_NONE;
}

int32_t SAT_MouseDraggingInputState::keyPress(SAT_InputEvent* AEvent)
{
    SAT_Widget* widget = stateInfo->activeWidget;
    uint32_t gesture = SAT_INPUT_GESTURE_DRAG | SAT_INPUT_GESTURE_KEY_PRESS;
    handler->sendGesture(widget,gesture);
    return SAT_INPUT_STATE_NONE;
}

int32_t SAT_MouseDraggingInputState::keyRelease(SAT_InputEvent* AEvent)
{
    SAT_Widget* widget = stateInfo->activeWidget;
    uint32_t gesture = SAT_INPUT_GESTURE_DRAG | SAT_INPUT_GESTURE_KEY_RELEASE;
    handler->sendGesture(widget,gesture);
    return SAT_INPUT_STATE_NONE;
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

class SAT_DraggingMouseState
: public SAT_MouseState
{
    SAT_DEFAULT_MOUSE_STATE(SAT_DraggingMouseState)
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

uint32_t SAT_DraggingMouseState::id()
{
    return SAT_MOUSE_STATE_DRAGGING;
}

const char* SAT_DraggingMouseState::name()
{
    return "DRAGGING";
}

void SAT_DraggingMouseState::enterState(int32_t AFromState)
{
    //SAT_PRINT("enterState from %i\n",AFromState);
    // if clicked widget have audo_hide, auto_lock, do it here..
    // lock at activePos?
    sendGesture(SAT_MOUSE_GESTURE_DRAG);
}

void SAT_DraggingMouseState::leaveState(int32_t AToState)
{
    //SAT_PRINT("leaveState to %i\n",AToState);
}

//------------------------------
//
//------------------------------

int32_t SAT_DraggingMouseState::timer(double ADelta)
{
    return SAT_MOUSE_STATE_NONE;
}

int32_t SAT_DraggingMouseState::click(SAT_MouseCoords APos, uint32_t AButton, uint32_t AState, uint32_t ATime)
{
    //SAT_PRINT("ignored: clicked button %i\n",AButton);
    return SAT_MOUSE_STATE_NONE;
}

int32_t SAT_DraggingMouseState::release(SAT_MouseCoords APos, uint32_t AButton, uint32_t AState, uint32_t ATime)
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

int32_t SAT_DraggingMouseState::move(SAT_MouseCoords APos, uint32_t AState, uint32_t ATime)
{
    //SAT_TRACE;
    sendGesture(SAT_MOUSE_GESTURE_DRAG);
    return SAT_MOUSE_STATE_NONE;
}



#endif
