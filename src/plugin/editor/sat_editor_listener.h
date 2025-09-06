#pragma once

#include "base/sat_base.h"

class SAT_Parameter;

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_EditorListener
{
    public:
        virtual void do_editor_listener_update_parameter(SAT_Parameter* AParameter, sat_param_t AValue) {};
        // virtual void do_editor_listener_note_event(uint32_t ANote, sat_param_t AVelocity) {};
};
