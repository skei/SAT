#pragma once

/*
    we could have a watchdog timer here...
*/

#include "base/sat_base.h"
#include "base/global/sat_global_base.h"

#include "base/global/sat_global_debug.h"
#include "base/global/sat_global_gui.h"
#include "base/global/sat_global_log.h"
#include "base/global/sat_global_print.h"
#include "base/global/sat_global_registry.h"
#include "base/global/sat_global_statistics.h"
#include "base/global/sat_global_system.h"
#include "base/global/sat_global_test.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_Global
: public SAT_GlobalBase
{
    public:
        SAT_Global();
        virtual ~SAT_Global();
    public:
        void        initialize();
        void        cleanup();
        void        activate(SAT_GlobalBase* AGlobal);
        void        deactivate(SAT_GlobalBase* AGlobal);
    private:
        bool        MIsInitialized  = false;
        bool        MIsActivated    = false;
};

//----------------------------------------------------------------------
//
// implementation
//
//----------------------------------------------------------------------

SAT_Global::SAT_Global()
: SAT_GlobalBase()
{
    initialize();
    activate(this);
}

SAT_Global::~SAT_Global()
{
    deactivate(this);
    cleanup();
}

void SAT_Global::initialize()
{
    if (!MIsInitialized)
    {
        SYSTEM      = new SAT_GlobalSystem();
        PRINT       = new SAT_GlobalPrint();
        DEBUG       = new SAT_GlobalDebug();
        LOG         = new SAT_GlobalLog();
        TEST        = new SAT_GlobalTest();
        GUI         = new SAT_GlobalGui();
        STATISTICS  = new SAT_GlobalStatistics();
        REGISTRY    = new SAT_GlobalRegistry();
        MIsInitialized = true;
        //PRINT->setPrefix(__FILE__, __FUNCTION__, __LINE__); PRINT->print("\n");
    }
}

void SAT_Global::cleanup()
{
    if (MIsInitialized)
    {
        //PRINT->setPrefix(__FILE__, __FUNCTION__, __LINE__); PRINT->print("\n");
        delete REGISTRY;
        delete STATISTICS;
        delete GUI;
        delete TEST;
        delete LOG;
        delete DEBUG;
        delete PRINT;
        delete SYSTEM;
        MIsInitialized = false;
    }
}

void SAT_Global::activate(SAT_GlobalBase* ASelf)
{
    if (MIsInitialized && !MIsActivated)
    {
        //PRINT->setPrefix(__FILE__, __FUNCTION__, __LINE__); PRINT->print("\n");
        SYSTEM->activate(this);
        PRINT->activate(this);
        DEBUG->activate(this);
        LOG->activate(this);
        TEST->activate(this);
        GUI->activate(this);
        STATISTICS->activate(this);
        REGISTRY->activate(this);
        MIsActivated = true;
    }
}

void SAT_Global::deactivate(SAT_GlobalBase* ASelf)
{
    if (MIsInitialized && MIsActivated)
    {
        //PRINT->setPrefix(__FILE__, __FUNCTION__, __LINE__); PRINT->print("\n");
        REGISTRY->deactivate(this);
        STATISTICS->deactivate(this);
        GUI->deactivate(this);
        TEST->deactivate(this);
        LOG->deactivate(this);
        DEBUG->deactivate(this);
        PRINT->deactivate(this);
        SYSTEM->deactivate(this);
        MIsActivated = false;
    }
}
