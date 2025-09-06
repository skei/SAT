#pragma once

#include "base/sat_base.h"
#include "plugin/sat_processor.h"
#include "plugin/sat_voice.h"
#include "plugin/processor/sat_process_context.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

template <class VOICE, int COUNT>
class SAT_VoiceProcessor
: public SAT_Processor
{

    public:

        SAT_VoiceProcessor(SAT_ProcessorOwner* AOwner);
        virtual ~SAT_VoiceProcessor();

    public:

        void process(SAT_ProcessContext* AContext) override;

    private:

        SAT_Voice<VOICE>    MVoices[COUNT] = {};
     // SAT_VoiceContext    MContext = {};
};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

template <class VOICE, int COUNT>
SAT_VoiceProcessor<VOICE,COUNT>::SAT_VoiceProcessor(SAT_ProcessorOwner* AOwner)
: SAT_Processor(AOwner)
{
    // MContext.process                = nullptr;
    // MContext.previous_steady_time   = -1;
    // MContext.sample_rate            = 0.0;
    // MContext.current_frame          = 0;
    for (uint32_t i=0; i<COUNT; i++)
    {
        // MVoices[i].setup(&MContext);
    }
}

template <class VOICE, int COUNT>
SAT_VoiceProcessor<VOICE,COUNT>::~SAT_VoiceProcessor()
{
    for (uint32_t i=0; i<COUNT; i++)
    {
        // MVoices[i].cleanup(this);
    }
}

//------------------------------
//
//------------------------------

template <class VOICE, int COUNT>
void SAT_VoiceProcessor<VOICE,COUNT>::process(SAT_ProcessContext* AContext)
{
}
