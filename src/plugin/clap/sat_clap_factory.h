#pragma once

#include "base/sat_base.h"
#include "extern/plugin/sat_clap.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_ClapFactory
{
    public:
        SAT_ClapFactory() {}
        virtual ~SAT_ClapFactory() {}
    public:
        virtual const char* getId()       { return nullptr; }   // ""; }
        virtual const void* getPtr()      { return nullptr; }   // plugin side struct
};
