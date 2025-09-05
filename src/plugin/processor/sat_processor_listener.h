#pragma once

#include "base/sat_base.h"

//----------------------------------------------------------------------
//
//
//
//---------------------------------------------------------------------

/*
    processor -> plugin
*/

class SAT_ProcessorListener
{
    public:
        virtual void do_processor_update_parameter(uint32_t AId, sat_param_t AValue) {};
};

