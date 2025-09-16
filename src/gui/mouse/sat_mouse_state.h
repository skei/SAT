#pragma once

#include "base/sat_base.h"
#include "gui/mouse/sat_base_mouse_handler.h"
#include "gui/window/sat_base_window.h"
#include "gui/sat_widget.h"

//------------------------------
//
//------------------------------

// class SAT_MouseHandler;

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_MouseState
{
    public:
        SAT_MouseState(SAT_BaseMouseHandler* AHandler);
        virtual ~SAT_MouseState();
    public:
        virtual void                enter(int32_t AFromState)       { }
        virtual void                leave(int32_t AToState)         { }
    public:
        virtual int32_t             timer(double ADelta)            { return SAT_MOUSE_STATE_NONE; }
        virtual int32_t             click(SAT_MouseEvent* AEvent)   { return SAT_MOUSE_STATE_NONE; }
        virtual int32_t             release(SAT_MouseEvent* AEvent) { return SAT_MOUSE_STATE_NONE; }
        virtual int32_t             move(SAT_MouseEvent* AEvent)    { return SAT_MOUSE_STATE_NONE; }
    public:
        SAT_BaseMouseHandler*       handler = nullptr;
        SAT_WidgetWindow*           window  = nullptr;
        int32_t                     type    = SAT_MOUSE_STATE_NONE;
        const char*                 name    ="";
};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

SAT_MouseState::SAT_MouseState(SAT_BaseMouseHandler* AHandler)
{
    handler = AHandler;
    window = AHandler->getWindow();
}

SAT_MouseState::~SAT_MouseState()
{
}

//------------------------------
//
//------------------------------

