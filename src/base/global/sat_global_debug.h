#pragma once

#include "base/sat_base.h"
#include "base/global/sat_global_base.h"

#include "base/global/debug/sat_debug_assert.h"
#include "base/global/debug/sat_debug_breakpoint.h"
#include "base/global/debug/sat_debug_callstack.h"
#include "base/global/debug/sat_debug_crash_handler.h"
#include "base/global/debug/sat_debug_memtrace.h"
#include "base/global/debug/sat_debug_observer.h"
#include "base/global/debug/sat_debug_window.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_GlobalDebug
{
    public:
        SAT_GlobalDebug();
        ~SAT_GlobalDebug();
        void activate(SAT_GlobalBase* AGlobal);
        void deactivate(SAT_GlobalBase* AGlobal);
    public:
        SAT_CrashHandler*   CRASH_HANDLER   = nullptr;
        SAT_CallStack*      CALLSTACK       = nullptr;
        SAT_MemTrace*       MEMTRACE        = nullptr;
        SAT_Observer*       OBSERVER        = nullptr;
        SAT_DebugWindow*    WINDOW          = nullptr;
    private:
        bool                MIsActivated    = false;
        SAT_GlobalBase*     MGlobal         = nullptr;
};

//----------------------------------------------------------------------
//
// implementation
//
//----------------------------------------------------------------------

SAT_GlobalDebug::SAT_GlobalDebug()
{
    CALLSTACK       = new SAT_CallStack();
    CRASH_HANDLER   = new SAT_CrashHandler();
    MEMTRACE        = new SAT_MemTrace();
    OBSERVER        = new SAT_Observer();
    WINDOW          = new SAT_DebugWindow();
}

SAT_GlobalDebug::~SAT_GlobalDebug()
{
    delete WINDOW;
    delete OBSERVER;
    delete MEMTRACE;
    delete CRASH_HANDLER;
    delete CALLSTACK;
}

void SAT_GlobalDebug::activate(SAT_GlobalBase* AGlobal)
{
    if (!MIsActivated)
    {
        MGlobal = AGlobal;
        CALLSTACK->activate(AGlobal);
        CRASH_HANDLER->activate(AGlobal,CALLSTACK,OBSERVER);
        MEMTRACE->activate(AGlobal);
        OBSERVER->activate(AGlobal);
        WINDOW->activate(AGlobal);
        MIsActivated = true;
    }
}

void SAT_GlobalDebug::deactivate(SAT_GlobalBase* AGlobal)
{
    if (MIsActivated)
    {
        WINDOW->deactivate(AGlobal);
        OBSERVER->deactivate(AGlobal);
        MEMTRACE->deactivate(AGlobal);
        CRASH_HANDLER->deactivate(AGlobal);
        CALLSTACK->deactivate(AGlobal);
        MGlobal = nullptr;
        MIsActivated = false;
    }
}

//------------------------------
//
//------------------------------

