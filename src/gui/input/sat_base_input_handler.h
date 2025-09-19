#pragma once

#include "base/sat_base.h"
#include "gui/window/sat_widget_window.h"
#include "gui/sat_widget.h"

class SAT_InputHandler;
class SAT_InputState;

//------------------------------
//
//------------------------------

struct SAT_MouseCoords
{
    int32_t x;
    int32_t y;
};

struct SAT_StateInfo
{
    double              currentTime     = 0.0;
    // current (event)
    double              time            = 0.0;
    SAT_Widget*         hoverWidget     = nullptr;
    SAT_MouseCoords     mousePos        = {0,0};
    uint32_t            mouseButton     = SAT_MOUSE_BUTTON_NONE;
    uint32_t            modKeys         = SAT_MOD_KEY_NONE;
    uint32_t            key             = SAT_KEY_NONE;
    // state
    SAT_MouseCoords     activePos       = {0,0};
    uint32_t            activeButton    = 0;
    SAT_Widget*         activeWidget    = nullptr;
    double              activeTime      = 0.0;
    uint32_t            activeKey       = SAT_KEY_NONE;
};

struct SAT_InputEvent
{
    SAT_InputHandler*   handler         = nullptr;
    uint32_t            type            = SAT_INPUT_EVENT_NONE;
    SAT_StateInfo*      stateInfo       = nullptr;
};

struct SAT_InputGesture
{
    SAT_InputHandler*   handler         = nullptr;
    uint32_t            type            = SAT_INPUT_GESTURE_NONE;
    SAT_StateInfo*      stateInfo       = nullptr;
};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_BaseInputHandler
{

    friend class SAT_InputState;

    public:

        SAT_BaseInputHandler() {}
        ~SAT_BaseInputHandler() {}

    public:

        virtual SAT_WidgetWindow*   getWindow()                         { return nullptr; }
        virtual SAT_InputState*     getCurrentState()                   { return nullptr; }
        virtual SAT_StateInfo*      getStateInfo()                      { return nullptr; }
        virtual double              getCurrentTime()                    { return 0.0; }

      //virtual SAT_Widget*         getClickedWidget(uint32_t AButton)  { return nullptr; }
        
    public:

        virtual bool                wantEvent(SAT_Widget* AWidget, uint32_t AEvent) { return true; }
        virtual bool                sendEvent(SAT_Widget* AWidget, uint32_t AEvent) { return true; }
        virtual bool                wantGesture(SAT_Widget* AWidget, uint32_t AGesture) { return true; }
        virtual void                sendGesture(SAT_Widget* AWidget, uint32_t AGesture) {}
      //virtual bool                wantState(SAT_Widget* AWidget, uint32_t AGState) { return true; }

        virtual void                keyCapture(SAT_Widget* AWidget) {}
        virtual void                mouseCapture(SAT_Widget* AWidget) {}
        virtual void                modal(SAT_Widget* AWidget) {}

        virtual void                setMouseCursor(int32_t ACursor) {}
        virtual void                resetMouseCursor() {}
        virtual void                showMouseCursor() {}
        virtual void                hideMouseCursor() {}
        virtual void                lockMouseCursor(SAT_Widget* AWidget) {}
        virtual void                unlockMouseCursor() {}
        virtual void                pushMouseCursor(int32_t ACursor) {}
        virtual void                popMouseCursor() {}

        virtual const char*         eventName(uint32_t AEvent) { return ""; }
        virtual const char*         gestureName(uint32_t AGesture) { return ""; }
        virtual const char*         stateName(int32_t AState) { return ""; }

    public:

        virtual void                timer(double ADelta) {}
        virtual void                mouseClick(SAT_MouseCoords APos, uint32_t AButton, uint32_t AState, uint32_t ATime) {}
        virtual void                mouseRelease(SAT_MouseCoords APos, uint32_t AButton, uint32_t AState, uint32_t ATime) {}
        virtual void                mouseMove(SAT_MouseCoords APos, uint32_t AState, uint32_t ATime) {}
        virtual void                mouseEnter(SAT_MouseCoords APos, uint32_t ATime) {}
        virtual void                mouseLeave(SAT_MouseCoords APos, uint32_t ATime) {}
        virtual void                keyPress(uint32_t AKey, uint32_t AState, uint32_t ATime) {}
        virtual void                keyRelease(uint32_t AKey, uint32_t AState, uint32_t ATime) {}
};
