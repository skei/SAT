#pragma once

#include "base/sat_base.h"
#include "base/global/sat_global_base.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_GlobalSystem
{
    public:
        SAT_GlobalSystem();
        ~SAT_GlobalSystem();
        void activate(SAT_GlobalBase* AGlobal);
        void deactivate(SAT_GlobalBase* AGlobal);
    public:
        uint32_t        getOs();
        const char*     getOSString();
    private:
        bool            MIsActivated    = false;
        SAT_GlobalBase* MGlobal         = nullptr;
};

//----------------------------------------------------------------------
//
// implementation
//
//----------------------------------------------------------------------

SAT_GlobalSystem::SAT_GlobalSystem()
{
}

SAT_GlobalSystem::~SAT_GlobalSystem()
{
}

void SAT_GlobalSystem::activate(SAT_GlobalBase* AGlobal)
{
    if (!MIsActivated)
    {
        MGlobal = AGlobal;
        MIsActivated = true;
    }
}

void SAT_GlobalSystem::deactivate(SAT_GlobalBase* AGlobal)
{
    if (MIsActivated)
    {
        MGlobal = nullptr;
        MIsActivated = false;
    }
}

//------------------------------
//
//------------------------------

uint32_t SAT_GlobalSystem::getOs()
{
    return SAT_OS_LINUX;
}

const char* SAT_GlobalSystem::getOSString()
{
    return "Linux";
}

