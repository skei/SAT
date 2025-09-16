#pragma once

#include "base/sat_base.h"
#include "gui/window/sat_widget_window.h"
#include "gui/sat_widget.h"

class SAT_MouseHandler;
class SAT_MouseState;

struct SAT_MouseCoords
{
    int32_t x;
    int32_t y;
};

struct SAT_MouseEvent
{
    uint32_t            type    = SAT_MOUSE_EVENT_NONE;
    SAT_MouseHandler*   handler = nullptr;
    SAT_MouseState*     state   = nullptr;
    SAT_MouseCoords     pos     = {0,0};
    uint32_t            button  = SAT_MOUSE_BUTTON_NONE;
    uint32_t            modkeys = SAT_STATE_KEY_NONE;
    double              time    = 0.0;
};

struct SAT_MouseGesture
{
    uint32_t            type    = SAT_MOUSE_GESTURE_NONE;
    SAT_MouseHandler*   handler = nullptr;
    SAT_MouseState*     state   = nullptr;
 // SAT_MouseCoords     pos     = {0,0};
 // uint32_t            button  = SAT_MOUSE_BUTTON_NONE;
 // uint32_t            modkeys = SAT_STATE_KEY_NONE;
 // double              time    = 0.0;
};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_BaseMouseHandler
{

    friend class SAT_MouseState;

    public:

        SAT_BaseMouseHandler() {}
        ~SAT_BaseMouseHandler() {}

    public:

        virtual SAT_WidgetWindow*   getWindow()         { return nullptr; }
        virtual SAT_MouseState*     getCurrentState()   { return nullptr; }
        virtual SAT_MouseEvent*     getEvent()          { return nullptr; }
        virtual SAT_MouseGesture*   getGesture()        { return nullptr; }
        virtual double              getCurrentTime()    { return 0.0; }
        virtual SAT_Widget*         getHoverWidget()    { return nullptr; }
        virtual SAT_Widget*         getActiveWidget()   { return nullptr; }
        virtual SAT_Widget*         getCapturedWidget() { return nullptr; }

    public:

        virtual void                captureWidget(SAT_Widget* AWidget) {}
        virtual void                modalWidget(SAT_Widget* AWidget) {}

        virtual void                setCursor(int32_t ACursor) {}
        virtual void                resetCursor() {}
        virtual void                showCursor() {}
        virtual void                hideCursor() {}
        virtual void                lockCursor(SAT_Widget* AWidget) {}
        virtual void                unlockCursor() {}
        virtual void                pushCursor(int32_t ACursor) {}
        virtual void                popCursor() {}

        virtual const char*         eventName(uint32_t AEvent) { return ""; }
        virtual const char*         gestureName(uint32_t AGesture) { return ""; }
        virtual const char*         stateName(int32_t AState) { return ""; }

    public:

        virtual void                timer(double ADelta) {}
        virtual void                click(SAT_MouseCoords APos, uint32_t AButton, uint32_t AState, uint32_t ATime) {}
        virtual void                release(SAT_MouseCoords APos, uint32_t AButton, uint32_t AState, uint32_t ATime) {}
        virtual void                move(SAT_MouseCoords APos, uint32_t AState, uint32_t ATime) {}
        virtual void                enter(SAT_MouseCoords APos, uint32_t ATime) {}
        virtual void                leave(SAT_MouseCoords APos, uint32_t ATime) {}

};
