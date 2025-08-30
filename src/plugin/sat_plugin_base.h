#pragma once

/*
    todo:
    save previous total sample count, so we can compare it when stafrting a new audioblock,
    to detect jumps, and if we have been sleeping/bypasssed, etc..
    update lfo's, etc..
*/

#include "base/sat_base.h"
#include "plugin/sat_parameter.h"

//----------------------------------------------------------------------
//
// queue items
//
//----------------------------------------------------------------------

struct SAT_Note
{
};

struct NoteEvent
{
    // uint32_t    type;
    // uint32_t    id;
    // double      value;
};

struct ParameterEvent
{
};

//----------------------------------------------------------------------
//
// editor
//
//----------------------------------------------------------------------

/*
    aka plugin
    setup
*/

class SAT_EditorOwner
{
    public:
        // getDefaultSize
        // getParameters
};

/*
    aka plugin?
    runtime, editor -> plugin
*/

class SAT_EditorListener
{
    public:
        virtual void do_editor_update_parameter(SAT_Parameter* AParameter, sat_param_t AValue) {};
};

// class SAT_BaseEditor
// {
// };

//----------------------------------------------------------------------
//
// processor
//
//----------------------------------------------------------------------

/*
    info for current process call
    todo:
        parameters (for audio processing)
        oversampling
*/

struct SAT_ProcessContext
{
    const clap_process_t*   process                 = nullptr;
    int64_t                 previous_steady_time    = -1;
    double                  sample_rate             = 0.0;
    uint32_t                current_frame           = 0;
};

/*
    required info when creating processor
*/

class SAT_ProcessorOwner
{
    public:
        virtual uint32_t    getMinBlockSize()   { return 0; }
        virtual uint32_t    getMaxBlockSize()   { return 0; }
        virtual double      getSampleRate()     { return 0.0; }
};

/*
    processor -> plugin
*/

class SAT_ProcessorListener
{
    public:
        virtual void do_processor_update_parameter(uint32_t AId, sat_param_t AValue) {};
};

//----------------------------------------------------------------------
//
// wrapper
//
//----------------------------------------------------------------------


