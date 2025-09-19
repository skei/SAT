#pragma once

#include "base/sat_base.h"
#include "base/util/sat_math.h"
#include "gui/input/sat_base_input_handler.h"
#include "gui/window/sat_base_window.h"
#include "gui/sat_widget.h"

//------------------------------
//
//------------------------------

// class SAT_InputHandler;

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_InputState
{
    public:
        SAT_InputState(SAT_BaseInputHandler* AHandler);
        virtual ~SAT_InputState();
    public:
        virtual void                enter(int32_t AFromState)               { }
        virtual void                leave(int32_t AToState)                 { }
    public:
        virtual int32_t             timer(double ADelta)                    { return SAT_INPUT_STATE_NONE; }
        virtual int32_t             mouseClick(SAT_InputEvent* AEvent)      { return SAT_INPUT_STATE_NONE; }
        virtual int32_t             mouseRelease(SAT_InputEvent* AEvent)    { return SAT_INPUT_STATE_NONE; }
        virtual int32_t             mouseMove(SAT_InputEvent* AEvent)       { return SAT_INPUT_STATE_NONE; }
        virtual int32_t             keyPress(SAT_InputEvent* AEvent)        { return SAT_INPUT_STATE_NONE; }
        virtual int32_t             keyRelease(SAT_InputEvent* AEvent)      { return SAT_INPUT_STATE_NONE; }
    public:
        int32_t                     type        = SAT_INPUT_STATE_NONE;
        const char*                 name        ="";
        SAT_BaseInputHandler*       handler     = nullptr;
        SAT_WidgetWindow*           window      = nullptr;
        SAT_StateInfo*              stateInfo   = nullptr;
};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

SAT_InputState::SAT_InputState(SAT_BaseInputHandler* AHandler)
{
    handler = AHandler;
    window  = AHandler->getWindow();
    stateInfo = AHandler->getStateInfo();
}

SAT_InputState::~SAT_InputState()
{
}

