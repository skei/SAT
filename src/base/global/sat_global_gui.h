#pragma once

#include "base/sat_base.h"
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
        void        setDoubleClickTime(double ASeconds);
        void        setLongPressTime(double ASeconds);
        void        setTooltipDelayTime(double ASeconds);
    public:
        double      getDoubleClickTime();
        double      getLongPressTime();
        double      getTooltipDelayTime();
    public:
        SAT_Skins   SKINS = {};
    private:
        double      MDoubleClickTime    = SAT_MOUSE_DOUBLE_CLICK_SEC;
        double      MLongPressTime      = SAT_MOUSE_LONGPRESS_SEC;
        double      MTooltipDelayTime   = SAT_MOUSE_TOOLTIP_SEC;
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

//------------------------------
//
//------------------------------

void SAT_GlobalGui::setDoubleClickTime(double ASeconds)     { MDoubleClickTime = ASeconds; }
void SAT_GlobalGui::setLongPressTime(double ASeconds)       { MLongPressTime = ASeconds; }
void SAT_GlobalGui::setTooltipDelayTime(double ASeconds)    { MTooltipDelayTime = ASeconds; }

double SAT_GlobalGui::getDoubleClickTime()  { return MDoubleClickTime; }
double SAT_GlobalGui::getLongPressTime()    { return MLongPressTime; }
double SAT_GlobalGui::getTooltipDelayTime() { return MTooltipDelayTime; }
