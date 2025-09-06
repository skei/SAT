#pragma once

#include "base/sat_base.h"

//----------------------------------------------------------------------
//
//
//
//---------------------------------------------------------------------

class SAT_ProcessorListener
{
    public:
        virtual void do_processor_listener_update_parameter(uint32_t AId, sat_param_t AValue) {};
};

