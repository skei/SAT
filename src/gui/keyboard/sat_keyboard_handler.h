#pragma once

#include "base/sat_base.h"
#include "gui/keyboard/sat_base_keyboard_handler.h"
#include "gui/keyboard/sat_keyboard_states.h"
#include "gui/keyboard/sat_keyboard_state.h"
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

    //friend class SAT_Window;

    public:

        SAT_KeyboardHandler(SAT_WidgetWindow* AWindow);
        virtual ~SAT_KeyboardHandler();

    public:

        SAT_WidgetWindow*   getWindow()         override    { return nullptr; }
        SAT_KeyboardState*  getCurrentState()   override    { return MCurrentState; }
        SAT_KeyboardEvent*  getEvent()          override    { return &MEvent; }
        double              getCurrentTime()    override    { return MCurrentTime; }
        SAT_Widget*         getCapturedWidget() override    { return MCapturedWidget; }

    public:

        void                captureWidget(SAT_Widget* AWidget) override;

        const char*         eventName(uint32_t AEvent) override;
        const char*         gestureName(uint32_t AGesture) override;
        const char*         stateName(int32_t AState) override;

    public:

        void                timer(double ADelta) override;
        void                press(uint32_t AKey, uint32_t AState, uint32_t ATime) override;
        void                release(uint32_t AKey, uint32_t AState, uint32_t ATime) override;

    public:

        void                reset();

    private:

        void                setupStates();
        bool                sendEvent(SAT_Widget* AWidget, SAT_KeyboardEvent* AEvent);
        void                updateState(int32_t AState);

    private:

        SAT_WidgetWindow*   MWindow                                     = nullptr;
        SAT_KeyboardState*  MCurrentState                               = nullptr;
        SAT_KeyboardState*  MKeyboardStates[SAT_KEYBOARD_STATE_COUNT]   = {};
        SAT_KeyboardEvent   MEvent                                      = {};
        double              MCurrentTime                                = 0.0;
        SAT_Widget*         MCapturedWidget                             = nullptr;
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
    // SAT_Assert(MCursorStack.isEmpty());
}

//------------------------------
//
//------------------------------

void SAT_KeyboardHandler::captureWidget(SAT_Widget* AWidget)
{
    MCapturedWidget = AWidget;
}

const char* SAT_KeyboardHandler::eventName(uint32_t AEvent)
{
    switch (AEvent)
    {
        case SAT_KEYBOARD_EVENT_NONE:       return "NONE";
        case SAT_KEYBOARD_EVENT_PRESS:      return "PRESS";
        case SAT_KEYBOARD_EVENT_RELEASE:    return "RELEASE";
        default:                            return "UNKNOWN";
    }
    return "?";
}

const char* SAT_KeyboardHandler::gestureName(uint32_t AGesture)
{
    switch (AGesture)
    {
        case SAT_KEYBOARD_GESTURE_NONE:     return "NONE";
        case SAT_KEYBOARD_GESTURE_PRESS:    return "PRESS";
        case SAT_KEYBOARD_GESTURE_RELEASE:  return "RELEASE";
        default:                            return "UNKNOWN";
    }
    return "?";
}

const char* SAT_KeyboardHandler::stateName(int32_t AState)
{
    switch (AState)
    {
        case SAT_KEYBOARD_STATE_NONE:   return "NONE";
        case SAT_KEYBOARD_STATE_IDLE:   return "IDLE";
        default:                        return "UNKNOWN";
    }
    return "?";
}

//------------------------------
//
//------------------------------

void SAT_KeyboardHandler::timer(double ADelta)
{
    int32_t state = MCurrentState->timer(ADelta);
    updateState(state);
    MCurrentTime += ADelta;
}

void SAT_KeyboardHandler::press(uint32_t AKey, uint32_t AState, uint32_t ATime)
{
    MEvent.type     = SAT_KEYBOARD_EVENT_PRESS;
    MEvent.key      = AKey;
    MEvent.modkeys  = AState;
    MEvent.time     = MCurrentTime;
    if (sendEvent(MCapturedWidget,&MEvent))
    {
        int32_t state = MCurrentState->press(&MEvent);
        updateState(state);
    }
}

void SAT_KeyboardHandler::release(uint32_t AKey, uint32_t AState, uint32_t ATime)
{
    MEvent.type     = SAT_KEYBOARD_EVENT_RELEASE;
    MEvent.key      = AKey;
    MEvent.modkeys  = AState;
    MEvent.time     = MCurrentTime;
    if (sendEvent(MCapturedWidget,&MEvent))
    {
        int32_t state = MCurrentState->release(&MEvent);
        updateState(state);
    }
}

//------------------------------
//
//------------------------------

void SAT_KeyboardHandler::reset()
{
    SAT_TRACE;
    MEvent.handler = this;
    MCurrentTime = 0.0;
    MCapturedWidget = nullptr;
    MCurrentState = nullptr;
    updateState(SAT_KEYBOARD_STATE_IDLE);
}

//------------------------------
//
//------------------------------

void SAT_KeyboardHandler::setupStates()
{
    MKeyboardStates[SAT_KEYBOARD_STATE_IDLE] = new SAT_IdleKeyboardState(this);
}

// return false if event shopuld be ignored..

bool SAT_KeyboardHandler::sendEvent(SAT_Widget* AWidget, SAT_KeyboardEvent* AEvent)
{
    uint32_t response = SAT_KEYBOARD_EVENT_RESPONSE_NONE;
    if (AWidget && AWidget->Options.wantKeyboardEvents & MEvent.type)
    {
        response = AWidget->on_widget_keyboard_event(&MEvent);
    }
    switch (response)
    {
        case SAT_KEYBOARD_EVENT_RESPONSE_NONE:
            return true;
        case SAT_KEYBOARD_EVENT_RESPONSE_IGNORE:
            return false;
        case SAT_KEYBOARD_EVENT_RESPONSE_CAPTURE:
            captureWidget(AWidget);
            return true;
        case SAT_KEYBOARD_EVENT_RESPONSE_RELEASE:
            captureWidget(nullptr);
            return true;
    }
    return true;
}

void SAT_KeyboardHandler::updateState(int32_t AState)
{
    SAT_Assert(AState < SAT_KEYBOARD_STATE_COUNT);
    if (AState == SAT_KEYBOARD_STATE_NONE) return;
    int32_t from_state = SAT_KEYBOARD_STATE_NONE;
    int32_t to_state = AState;
    if (MCurrentState)
    {
        from_state = MCurrentState->type;
        if (from_state == to_state) return;
        MCurrentState->leave(to_state);
    }
    MCurrentState = MKeyboardStates[to_state];
    MCurrentState->enter(from_state);
}

