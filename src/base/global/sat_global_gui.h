#pragma once

//#include "base/sat_base.h"
#include "gui/sat_skins.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

#if defined SAT_LINUX
    #include "base/global/linux/sat_global_linux_gui.h"
    typedef SAT_LinuxGlobalGui SAT_ImplementedGlobalGui;
#elif defined SAT_WIN32
    #error NOT IMPLEMENTED YET
#elif defined SAT_MAC
    #error NOT IMPLEMENTED YET
#else
    #error NO OS DEFINED
#endif

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------


class SAT_GlobalGui
: public SAT_ImplementedGlobalGui
{
    public:
        SAT_GlobalGui();
        ~SAT_GlobalGui();
        void activate(SAT_GlobalBase* AGlobal);
        void deactivate(SAT_GlobalBase* AGlobal);
    public:
        SAT_Skins   SKINS = {};
};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

SAT_GlobalGui::SAT_GlobalGui()
: SAT_ImplementedGlobalGui()
{
}

SAT_GlobalGui::~SAT_GlobalGui()
{
}

void SAT_GlobalGui::activate(SAT_GlobalBase* AGlobal)
{
    SAT_ImplementedGlobalGui::activate(AGlobal);
    SKINS.initialize();
}

void SAT_GlobalGui::deactivate(SAT_GlobalBase* AGlobal)
{
    SKINS.cleanup();
    SAT_ImplementedGlobalGui::deactivate(AGlobal);
}
