#pragma once

#include "base/sat_base.h"
#include "plugin/processor/sat_process_context.h"
#include "plugin/processor/sat_processor_listener.h"
#include "plugin/processor/sat_processor_owner.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_Processor
{
    public:
        SAT_Processor(SAT_ProcessorOwner* AOwner);
        virtual ~SAT_Processor();

    public:

        virtual void process(SAT_ProcessContext* AContext);


    public:
};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

SAT_Processor::SAT_Processor(SAT_ProcessorOwner* AOwner)
{
}

SAT_Processor::~SAT_Processor()
{
}

//------------------------------
//
//------------------------------

void SAT_Processor::process(SAT_ProcessContext* AContext)
{
}
