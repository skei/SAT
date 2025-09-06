#pragma once

#include "base/sat_base.h"
#include "extern/plugin/sat_clap.h"

//----------------------------------------------------------------------
//
//
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
