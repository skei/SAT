#pragma once

#include "base/sat_base.h"
#include "gui/keyboard/sat_base_keyboard_handler.h"
#include "gui/window/sat_base_window.h"
#include "gui/sat_widget.h"

//------------------------------
//
//------------------------------


//------------------------------
//
//------------------------------

#define SAT_DEFAULT_KEYBOARD_STATE(State)           \
    public:                                         \
        State(SAT_BaseKeyboardHandler* AHandler)    \
        : SAT_KeyboardState(AHandler) {}            \
        virtual ~State() {}

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_KeyboardState
{
    public:
        SAT_KeyboardState(SAT_BaseKeyboardHandler* AHandler);
        virtual ~SAT_KeyboardState();

    public:

        virtual uint32_t        id();
        virtual void            enterState(int32_t AFromState);
        virtual void            leaveState(int32_t AToState);

        virtual int32_t         timer(double ADelta);
        virtual int32_t         press(uint32_t AKey, uint32_t AState, uint32_t ATime);
        virtual int32_t         release(uint32_t AKey, uint32_t AState, uint32_t ATime);

    public:

        double                  currentTime()       { return MHandler->MCurrentTime; }
        uint32_t                currentKeys()       { return MHandler->MCurrentKeys; }
        uint32_t                currentModKeys()    { return MHandler->MCurrentModKeys; }

        SAT_Widget*             prevWidget()        { return MHandler->MPrevWidget; }

        uint32_t                pressedKey()        { return MHandler->MPressedKey; }
        uint32_t                pressedModKeys()    { return MHandler->MPressedModKeys; }
        double                  pressedTime()       { return MHandler->MPressedTime; }

        uint32_t                releasedKey()       { return MHandler->MReleasedKey; }
        uint32_t                releasedModKeys()   { return MHandler->MReleasedModKeys; }
        double                  releasedTime()      { return MHandler->MReleasedTime; }

        SAT_Widget*             capturedWidget()    { return MHandler->MCapturedWidget; }

    protected:

        uint32_t                sendEvent(SAT_Widget* AWidget, uint32_t AEvent);

    protected:

        SAT_BaseKeyboardHandler*    MHandler    = nullptr;
        SAT_WidgetWindow*           MWindow     = nullptr;
};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

SAT_KeyboardState::SAT_KeyboardState(SAT_BaseKeyboardHandler* AHandler)
{
    MHandler = AHandler;
    MWindow = AHandler->getWindow();
}

SAT_KeyboardState::~SAT_KeyboardState()
{
}

//------------------------------
//
//------------------------------

uint32_t SAT_KeyboardState::id()
{
    return SAT_KEYBOARD_STATE_IDLE;
}

void SAT_KeyboardState::enterState(int32_t AFromState)
{
    // SAT_PRINT("enterState from %i -> return %i\n",AFromState,id());
}

void SAT_KeyboardState::leaveState(int32_t AToState)
{
    // SAT_PRINT("leaveState to %i -> return %i\n",AToState,AToState);
}

//------------------------------
//
//------------------------------

int32_t SAT_KeyboardState::timer(double ADelta)
{
    return SAT_KEYBOARD_STATE_NONE;
}

int32_t SAT_KeyboardState::press(uint32_t AKey, uint32_t AState, uint32_t ATime)
{
    return SAT_KEYBOARD_STATE_NONE;
}

int32_t SAT_KeyboardState::release(uint32_t AKey, uint32_t AState, uint32_t ATime)
{
    return SAT_KEYBOARD_STATE_NONE;
}

//------------------------------
//
//------------------------------

uint32_t SAT_KeyboardState::sendEvent(SAT_Widget* AWidget, uint32_t AEvent)
{
    if (AWidget && (AWidget->Options.wantKeyboardEvents & AEvent))
    {
        uint32_t retval = AWidget->on_widget_keyboard_event(AEvent,this);
        return retval;
    }
    return SAT_KEYBOARD_EVENT_RESPONSE_NONE;
}
