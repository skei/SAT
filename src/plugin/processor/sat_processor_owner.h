#pragma once

#include "base/sat_base.h"

//----------------------------------------------------------------------
//
//
//
//---------------------------------------------------------------------

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
