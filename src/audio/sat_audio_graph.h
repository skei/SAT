#pragma once

#include "base/sat_base.h"
#include "audio/sat_audio_module.h"

//----------------------------------------------------------------------

typedef SAT_Array<SAT_BaseModule*>  SAT_ModuleArray;

class SAT_AudioGraph
{
    public:
        SAT_AudioGraph();
        virtual ~SAT_AudioGraph();
    public:
        // bool                activate();
        // bool                deactivate();
        // bool                prepare();
        // void                process();
        // void                processSlice();
        // void                processSample();
        // uint32_t            compile();
    private:
        SAT_ModuleArray MModules;
};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

SAT_AudioGraph::SAT_AudioGraph()
{
}

SAT_AudioGraph::~SAT_AudioGraph()
{
}
