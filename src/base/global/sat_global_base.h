#pragma once

#include "base/sat_base.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_GlobalSystem;
class SAT_GlobalPrint;
class SAT_GlobalDebug;
class SAT_GlobalLog;
class SAT_GlobalTest;
class SAT_GlobalGui;
class SAT_GlobalStatistics;
class SAT_GlobalRegistry;

void SAT_PrintNothing(const char*,...) {}

#ifdef SAT_DEBUG
    #define SAT_GLOBAL_PRINT_PREFIX MGlobal->PRINT->setPrefix( __FILE__, __FUNCTION__, __LINE__ )
    #define SAT_GLOBAL_PRINT        SAT_GLOBAL_PRINT_PREFIX; MGlobal->PRINT->print
    #define SAT_GLOBAL_DPRINT       MGlobal->PRINT->print
    #define SAT_GLOBAL_TRACE        SAT_GLOBAL_PRINT_PREFIX; MGlobal->PRINT->print("\n")
#else
    #define SAT_GLOBAL_PRINT_PREFIX {}
    #define SAT_GLOBAL_PRINT        SAT_PrintNothing
    #define SAT_GLOBAL_DPRINT       SAT_PrintNothing
    #define SAT_GLOBAL_TRACE        {}
#endif

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_GlobalBase
{
    public:
        SAT_GlobalBase();
        virtual ~SAT_GlobalBase();
    public:
        SAT_GlobalSystem*       SYSTEM      = nullptr;
        SAT_GlobalPrint*        PRINT       = nullptr;
        SAT_GlobalDebug*        DEBUG       = nullptr;
        SAT_GlobalLog*          LOG         = nullptr;
        SAT_GlobalTest*         TEST        = nullptr;
        SAT_GlobalGui*          GUI         = nullptr;
        SAT_GlobalStatistics*   STATISTICS  = nullptr;
        SAT_GlobalRegistry*     REGISTRY    = nullptr;
};

//----------------------------------------------------------------------
//
// implementation
//
//----------------------------------------------------------------------

SAT_GlobalBase::SAT_GlobalBase()
{
}

SAT_GlobalBase::~SAT_GlobalBase()
{
}
