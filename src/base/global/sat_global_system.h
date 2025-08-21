#pragma once

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

#include "base/sat_base.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

#if defined SAT_LINUX
    #include "base/global/linux/sat_global_linux_system.h"
#elif defined SAT_WIN32
    #error NOT IMPLEMENTED YET
#elif defined SAT_MAC
    #error NOT IMPLEMENTED YET
#else
     #error NO OS (LINUX/WIN32/MAC) DEFINED
#endif
