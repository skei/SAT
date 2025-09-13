#pragma once

#include "base/sat_base.h"
#include "gui/keyboard/sat_base_keyboard_handler.h"
#include "gui/keyboard/sat_keyboard_states.h"
#include "gui/window/sat_widget_window.h"
#include "gui/sat_widget.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_KeyboardHandler
: public SAT_BaseKeyboardHandler
{

    friend class SAT_Window;

    public:

        SAT_KeyboardHandler(SAT_WidgetWindow* AWindow);
        virtual ~SAT_KeyboardHandler();

    public:

        void                reset() override;
        SAT_WidgetWindow*   getWindow() override;
        SAT_KeyboardState*  getState() override;

    public:

        void                captureWidget(SAT_Widget* AWidget);

    public:
    
        void                timer(double ADelta) override;
        void                press(uint32_t AKey, uint32_t AState, uint32_t ATime) override;
        void                release(uint32_t AKey, uint32_t AState, uint32_t ATime) override;

    private:

        void                setupStates();
        void                changeState(int32_t AState);

    private:

        SAT_WidgetWindow*   MWindow                                     = nullptr;
        SAT_KeyboardState*  MCurrentState                               = nullptr;
        SAT_KeyboardState*  MKeyboardStates[SAT_KEYBOARD_STATE_COUNT]   = {};

};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

SAT_KeyboardHandler::SAT_KeyboardHandler(SAT_WidgetWindow* AWindow)
: SAT_BaseKeyboardHandler()
{
    MWindow = AWindow;
    setupStates();
    reset();
}

SAT_KeyboardHandler::~SAT_KeyboardHandler()
{
    #ifndef SAT_NO_AUTODELETE
        for (uint32_t i=0; i<SAT_KEYBOARD_STATE_COUNT; i++) delete MKeyboardStates[i];
    #endif
}

//------------------------------
//
//------------------------------

void SAT_KeyboardHandler::reset()
{
    MCapturedWidget     = nullptr;
    MCurrentTime        = 0.0;
    MCurrentKeys        = 0;
    MCurrentModKeys     = SAT_STATE_KEY_NONE;
    MPrevWidget         = MWindow;
    MPressedKey         = SAT_KEY_NONE;
    MPressedModKeys     = SAT_STATE_KEY_NONE;
    MPressedTime        = 0.0;
    MReleasedKey        = SAT_KEY_NONE;
    MReleasedModKeys    = SAT_STATE_KEY_NONE;
    MReleasedTime       = 0.0;
    
    changeState(SAT_KEYBOARD_STATE_IDLE);
}

SAT_WidgetWindow* SAT_KeyboardHandler::getWindow()
{
    return MWindow;
}

SAT_KeyboardState* SAT_KeyboardHandler::getState()
{
    return MCurrentState;
}

//------------------------------
//
//------------------------------

void SAT_KeyboardHandler::captureWidget(SAT_Widget* AWidget)
{
    MCapturedWidget = AWidget;
}

//------------------------------
//
//------------------------------

void SAT_KeyboardHandler::timer(double ADelta)
{
    MCurrentTime += ADelta;
    if (!MCurrentState) return;
    // SAT_PRINT("MCurrentTime %.3f MPrevTimeMoved %.3f\n",MCurrentTime,MPrevTimeMoved);
    int32_t state = MCurrentState->timer(ADelta);
    changeState(state);
}

void SAT_KeyboardHandler::press(uint32_t AKey, uint32_t AState, uint32_t ATime)
{
    MPressedKey = AKey;
    MPressedModKeys = AState;
    MPressedTime = MCurrentTime;
    // MCurrentKeys |= (uint32_t)(1 << (AKey - 1));
    if (!MCurrentState) return;
    //int32_t event_response = sendEvent(MCapturedWidget,SAT_KEYBOARD_EVENT_PRESS);
    //if (event_response != SAT_KEYBOARD_EVENT_RESPONSE_IGNORE)
    //{
        int32_t state = MCurrentState->press(AKey,AState,ATime);
        changeState(state);
    //}
}

void SAT_KeyboardHandler::release(uint32_t AKey, uint32_t AState, uint32_t ATime)
{
    MReleasedKey = AKey;
    MReleasedModKeys = AState;
    MReleasedTime = MCurrentTime;
    // MCurrentKeys &= ~(uint32_t)(1 << (AKey - 1));
    if (!MCurrentState) return;
    //int32_t event_response = sendEvent(MCapturedWidget,SAT_KEYBOARD_EVENT_RELEASE);
    //if (event_response != SAT_KEYBOARD_EVENT_RESPONSE_IGNORE)
    //{
        int32_t state = MCurrentState->release(AKey,AState,ATime);
        changeState(state);
    //}
}

//------------------------------
// private
//------------------------------

void SAT_KeyboardHandler::setupStates()
{
    MKeyboardStates[SAT_KEYBOARD_STATE_IDLE] = new SAT_IdleKeyboardState(this);
}

void SAT_KeyboardHandler::changeState(int32_t AState)
{
    SAT_Assert(AState < SAT_KEYBOARD_STATE_COUNT);
    if (AState >= 0)
    {
        if (MCurrentState)
        {
            int32_t prev_state = MCurrentState->id();
            if (AState != prev_state)
            {
                MCurrentState->leaveState(AState);
                MCurrentState = MKeyboardStates[AState];
                MCurrentState->enterState(prev_state);
                MWindow->changeKeyboardState(MCurrentState);
            }
        }
        else
        {
            MCurrentState = MKeyboardStates[AState];
            MCurrentState->enterState(SAT_KEYBOARD_STATE_NONE);
            MWindow->changeKeyboardState(MCurrentState);
        }
    }
}
