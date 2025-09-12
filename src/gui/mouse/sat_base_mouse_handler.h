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

        virtual SAT_WidgetWindow*   getWindow() { return nullptr; }

    public:

        virtual void                timer(double ADelta) {}
        virtual void                click(SAT_MouseCoords APos, uint32_t AButton, uint32_t AState, uint32_t ATime) {}
        virtual void                release(SAT_MouseCoords APos, uint32_t AButton, uint32_t AState, uint32_t ATime) {}
        virtual void                move(SAT_MouseCoords APos, uint32_t AState, uint32_t ATime) {}
        virtual void                enter(SAT_MouseCoords APos, uint32_t ATime) {}
        virtual void                leave(SAT_MouseCoords APos, uint32_t ATime) {}

    protected:
    
        double                      MCurrentTime            = 0.0;
        SAT_MouseCoords             MCurrentPos             = {0,0};
        uint32_t                    MCurrentButtons         = 0;
        uint32_t                    MCurrentModKeys         = SAT_STATE_KEY_NONE;
        SAT_Widget*                 MCurrentWidget          = nullptr;

        SAT_MouseCoords             MPrevPos                = {0,0};
        double                      MPrevTimeMoved          = 0.0;
        SAT_Widget*                 MPrevWidget             = nullptr;
        
        SAT_MouseCoords             MClickedPos             = {0,0};
        uint32_t                    MClickedButton          = SAT_MOUSE_BUTTON_NONE;
        uint32_t                    MClickedModKeys         = SAT_STATE_KEY_NONE;
        double                      MClickedTime            = 0.0;
        SAT_Widget*                 MClickedWidget          = nullptr;

        SAT_MouseCoords             MReleasedPos            = {0,0};
        uint32_t                    MReleasedButton         = SAT_MOUSE_BUTTON_NONE;
        uint32_t                    MReleasedModKeys        = SAT_STATE_KEY_NONE;
        double                      MReleasedTime           = 0.0;
        SAT_Widget*                 MReleasedWidget         = nullptr;

        bool                        MLocked                 = false;
        SAT_MouseCoords             MLockedPos              = {0,0};
        SAT_MouseCoords             MLockedVirtualPos       = {0,0};
        SAT_Widget*                 MLockedWidget           = nullptr;

        SAT_Widget*                 MCapturedWidget         = nullptr;
      
      //int32_t                     MCurrentCursor          = SAT_CURSOR_DEFAULT;

};

