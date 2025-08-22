#pragma once

#include "base/sat_base.h"
#include "plugin/sat_plugin_base.h"

class SAT_Processor
{
    public:
        SAT_Processor(SAT_ProcessorOwner* AOwner);
        virtual ~SAT_Processor();
    public:
        virtual void prepare(SAT_ProcessorListener* AListener);
};

