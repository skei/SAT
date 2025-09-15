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
    SAT_MouseCoords(int32_t ax, int32_t ay) { x=ax; y=ay; }
};

struct SAT_MouseEvent
{
    uint32_t            type    = SAT_MOUSE_EVENT_NONE;
    SAT_MouseHandler*   handler = nullptr;
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
        virtual double              getCurrentTime()    { return 0.0; }
        virtual SAT_Widget*         getHoverWidget()    { return nullptr; }
        virtual SAT_Widget*         getActiveWidget()   { return nullptr; }
        virtual SAT_Widget*         getCapturedWidget() { return nullptr; }
    public:
        virtual void                captureWidget(SAT_Widget* AWidget) {}
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

    protected:



};






    /*
        uint32_t                    activeButton           = SAT_MOUSE_BUTTON_NONE;
        SAT_MouseCoords             activePos              = {0,0};
        double                      activeTime             = 0.0;
        SAT_Widget*                 activeWidget          = nullptr;
        SAT_Widget*                 capturedWidget         = nullptr;
        SAT_MouseCoords             clickedPos             = {0,0};
        uint32_t                    clickedButton          = SAT_MOUSE_BUTTON_NONE;
        uint32_t                    clickedModKeys         = SAT_STATE_KEY_NONE;
        double                      clickedTime            = 0.0;
        SAT_Widget*                 clickedWidget          = nullptr;
        double                      currentTime            = 0.0;
        SAT_MouseCoords             currentPos             = {0,0};
        uint32_t                    currentButtons         = 0;
        uint32_t                    currentModKeys         = SAT_STATE_KEY_NONE;
        SAT_Widget*                 currentWidget          = nullptr;
        int32_t                     currentCursor          = SAT_CURSOR_DEFAULT;
        bool                        locked                 = false;
        SAT_MouseCoords             lockedPos              = {0,0};
        SAT_MouseCoords             lockedVirtualPos       = {0,0};
        SAT_Widget*                 lockedWidget           = nullptr;
        SAT_MouseCoords             prevClickedPos         = {0,0};
        uint32_t                    prevClickedButton      = SAT_MOUSE_BUTTON_NONE;
        double                      prevClickedTime        = 0.0;
        SAT_Widget*                 prevClickedWidget      = nullptr;
        SAT_MouseCoords             prevPos                = {0,0};
        double                      prevTimeMoved          = 0.0;
        SAT_Widget*                 prevWidget             = nullptr;
        int32_t                     prevCursor             = SAT_CURSOR_DEFAULT;
        SAT_MouseCoords             releasedPos            = {0,0};
        uint32_t                    releasedButton         = SAT_MOUSE_BUTTON_NONE;
        uint32_t                    releasedModKeys        = SAT_STATE_KEY_NONE;
        double                      releasedTime           = 0.0;
        SAT_Widget*                 releasedWidget         = nullptr;
    */

