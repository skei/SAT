#pragma once

#include "base/sat_base.h"
#include "gui/window/sat_widget_window.h"
#include "gui/sat_widget.h"

class SAT_KeyboardHandler;
class SAT_KeyboardState;

struct SAT_KeyboardEvent
{
    uint32_t                type    = SAT_KEYBOARD_EVENT_NONE;
    SAT_KeyboardHandler*    handler = nullptr;
    uint32_t                key     = SAT_KEY_NONE;
    uint32_t                modkeys = SAT_STATE_KEY_NONE;
    double                  time    = 0.0;
};

struct SAT_KeyboardGesture
{
    uint32_t                type    = SAT_KEYBOARD_GESTURE_NONE;
    SAT_KeyboardHandler*    handler = nullptr;
    SAT_KeyboardState*      state   = nullptr;
    // uint32_t                key     = SAT_KEY_NONE;
    // uint32_t                modkeys = SAT_STATE_KEY_NONE;
    // double                  time    = 0.0;
};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_BaseKeyboardHandler
{

    friend class SAT_KeyboardState;

    public:

        SAT_BaseKeyboardHandler() {}
        ~SAT_BaseKeyboardHandler() {}

    public:
        virtual SAT_WidgetWindow*   getWindow()         { return nullptr; }
        virtual SAT_KeyboardState*  getCurrentState()   { return nullptr; }
        virtual SAT_KeyboardEvent*  getEvent()          { return nullptr; }
        virtual double              getCurrentTime()    { return 0.0; }
        virtual SAT_Widget*         getActiveWidget()   { return nullptr; }
        virtual SAT_Widget*         getCapturedWidget() { return nullptr; }
    public:
        virtual void                captureWidget(SAT_Widget* AWidget) {}

        virtual const char*         eventName(uint32_t AEvent) { return ""; }
        virtual const char*         gestureName(uint32_t AGesture) { return ""; }
        virtual const char*         stateName(int32_t AState) { return ""; }

    public:

        virtual void                timer(double ADelta) {}
        virtual void                press(uint32_t AKey, uint32_t AState, uint32_t ATime) {}
        virtual void                release(uint32_t AKey, uint32_t AState, uint32_t ATime) {}

    protected:

};
