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
        void        setMouseDoubleClickTime(double ASeconds);
        void        setMouseHoverHoldTime(double ASeconds);
        void        setMouseLongPressTime(double ASeconds);
        void        setMouseMovementSlack(double ADistance);
        void        setMouseTooltipDelayTime(double ASeconds);
    public:
        double      getMouseDoubleClickTime();
        double      getMouseHoverHoldTime();
        double      getMouseLongPressTime();
        double      getMouseMovementSlack();
        double      getMouseTooltipDelayTime();
    public:
        SAT_Skins   SKINS = {};
    private:
        double      MMouseDoubleClickTime    = SAT_MOUSE_DOUBLE_CLICK_SEC;
        double      MMouseHoverHoldTime      = SAT_MOUSE_HOVER_HOLD_TIME_SEC;
        double      MMouseLongPressTime      = SAT_MOUSE_LONGPRESS_SEC;
        double      MMouseMovementSlack      = SAT_MOUSE_MOVEMENT_SLACK;
        double      MMouseTooltipDelayTime   = SAT_MOUSE_TOOLTIP_DELAY_SEC;
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

void SAT_GlobalGui::setMouseDoubleClickTime(double ASeconds)     { MMouseDoubleClickTime = ASeconds; }
void SAT_GlobalGui::setMouseHoverHoldTime(double ASeconds)       { MMouseHoverHoldTime = ASeconds; }
void SAT_GlobalGui::setMouseLongPressTime(double ASeconds)       { MMouseLongPressTime = ASeconds; }
void SAT_GlobalGui::setMouseMovementSlack(double ASeconds)       { MMouseMovementSlack = ASeconds; }
void SAT_GlobalGui::setMouseTooltipDelayTime(double ASeconds)    { MMouseTooltipDelayTime = ASeconds; }

double SAT_GlobalGui::getMouseDoubleClickTime()     { return MMouseDoubleClickTime; }
double SAT_GlobalGui::getMouseHoverHoldTime()       { return MMouseHoverHoldTime; }
double SAT_GlobalGui::getMouseLongPressTime()       { return MMouseLongPressTime; }
double SAT_GlobalGui::getMouseMovementSlack()       { return MMouseMovementSlack; }
double SAT_GlobalGui::getMouseTooltipDelayTime()    { return MMouseTooltipDelayTime; }
