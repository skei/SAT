#pragma once

#include "base/sat_base.h"

class SAT_Parameter;

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

/*
    aka plugin?
    runtime, editor -> plugin
*/

class SAT_EditorListener
{
    public:
        virtual void do_editor_listener_update_parameter(SAT_Parameter* AParameter, sat_param_t AValue) {};
};
