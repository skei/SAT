#pragma once

#include "base/sat_base.h"
#include "gui/window/sat_widget_window.h"
#include "gui/sat_widget.h"

class SAT_MouseState;

struct SAT_MouseCoords
{
    int32_t x;
    int32_t y;
    SAT_MouseCoords(int32_t ax, int32_t ay) { x=ax; y=ay; }
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

        virtual void                reset() {}
        virtual SAT_WidgetWindow*   getWindow() { return nullptr; }
        virtual SAT_MouseState*     getState() { return nullptr; }

    public:

        virtual void                captureWidget(SAT_Widget* AWidget) {}
        virtual void                setCursor(int32_t ACursor) {}
        virtual void                resetCursor() {}
        virtual void                showCursor() {}
        virtual void                hideCursor() {}
        virtual void                pushCursor(int32_t ACursor) {}
        virtual void                popCursor() {}
        virtual void                lockCursor(SAT_Widget* AWidget) {}
        virtual void                unlockCursor() {}

    public:

        virtual void                timer(double ADelta) {}
        virtual void                click(SAT_MouseCoords APos, uint32_t AButton, uint32_t AState, uint32_t ATime) {}
        virtual void                release(SAT_MouseCoords APos, uint32_t AButton, uint32_t AState, uint32_t ATime) {}
        virtual void                move(SAT_MouseCoords APos, uint32_t AState, uint32_t ATime) {}
        virtual void                enter(SAT_MouseCoords APos, uint32_t ATime) {}
        virtual void                leave(SAT_MouseCoords APos, uint32_t ATime) {}

    protected:

        uint32_t                    MActiveButton           = SAT_MOUSE_BUTTON_NONE;
        SAT_MouseCoords             MActivePos              = {0,0};
        double                      MActiveTime             = 0.0;
    
        SAT_Widget*                 MCapturedWidget         = nullptr;
        SAT_MouseCoords             MClickedPos             = {0,0};
        uint32_t                    MClickedButton          = SAT_MOUSE_BUTTON_NONE;
        uint32_t                    MClickedModKeys         = SAT_STATE_KEY_NONE;
        double                      MClickedTime            = 0.0;
        SAT_Widget*                 MClickedWidget          = nullptr;
        double                      MCurrentTime            = 0.0;
        SAT_MouseCoords             MCurrentPos             = {0,0};
        uint32_t                    MCurrentButtons         = 0;
        uint32_t                    MCurrentModKeys         = SAT_STATE_KEY_NONE;
        SAT_Widget*                 MCurrentWidget          = nullptr;
        int32_t                     MCurrentCursor          = SAT_CURSOR_DEFAULT;
        bool                        MLocked                 = false;
        SAT_MouseCoords             MLockedPos              = {0,0};
        SAT_MouseCoords             MLockedVirtualPos       = {0,0};
        SAT_Widget*                 MLockedWidget           = nullptr;

        SAT_MouseCoords             MPrevClickedPos         = {0,0};
        uint32_t                    MPrevClickedButton      = SAT_MOUSE_BUTTON_NONE;
        double                      MPrevClickedTime        = 0.0;
        SAT_Widget*                 MPrevClickedWidget      = nullptr;

        SAT_MouseCoords             MPrevPos                = {0,0};
        double                      MPrevTimeMoved          = 0.0;
        SAT_Widget*                 MPrevWidget             = nullptr;
        int32_t                     MPrevCursor             = SAT_CURSOR_DEFAULT;
        SAT_MouseCoords             MReleasedPos            = {0,0};
        uint32_t                    MReleasedButton         = SAT_MOUSE_BUTTON_NONE;
        uint32_t                    MReleasedModKeys        = SAT_STATE_KEY_NONE;
        double                      MReleasedTime           = 0.0;
        SAT_Widget*                 MReleasedWidget         = nullptr;

};

