#pragma once

#include "base/sat_base.h"

//----------------------------------------------------------------------

typedef void (*SAT_ModuleCallback)();

// struct SAT_ModulePin
// {
// };

// struct SAT_ModuleConnection
// {
// };

//------------------------------
//
//------------------------------

class SAT_BaseModule
{
    public:
        SAT_BaseModule();
        virtual ~SAT_BaseModule();
    public:
        // virtual const char*         getName();
        // virtual const char*         getDescription();
        // virtual uint32_t            getNumInputs();
        // virtual uint32_t            getNumOutputs();
        // virtual uint32_t            getInputTypes();
        // virtual uint32_t            getOutputTypes();
    public:
        // virtual bool                activate();
        // virtual bool                deactivate();
        // virtual bool                connect();
        // virtual bool                disconnect();
        // virtual bool                prepare();
        // virtual void                process();
        // virtual void                processSlice();
        // virtual void                processSample();
    public:
        // virtual uint32_t            compile();
        // virtual SAT_ModuleCallback  getCallback();
        // virtual const char*         getCode();
};

//------------------------------
//
//------------------------------

template<class MODULE>
class SAT_AudioModule
: public SAT_BaseModule
{
    public:
        SAT_AudioModule();
        virtual ~SAT_AudioModule();
    private:
        MODULE  MModule = {};
};

//----------------------------------------------------------------------
//
// base module
//
//----------------------------------------------------------------------

SAT_BaseModule::SAT_BaseModule()
{
}

SAT_BaseModule::~SAT_BaseModule()
{
}

//----------------------------------------------------------------------
//
// audio module
//
//----------------------------------------------------------------------

template<class MODULE>
SAT_AudioModule<MODULE>::SAT_AudioModule()
: SAT_BaseModule()
{
}

template<class MODULE>
SAT_AudioModule<MODULE>::~SAT_AudioModule()
{
}
