#pragma once

#include "base/sat_base.h"
#include "gui/sat_skin.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_DefaultSkin : public SAT_Skin
{
    public:
        SAT_DefaultSkin();
};

//------------------------------
//
//------------------------------

class SAT_DefaultPanelSkin : public SAT_DefaultSkin
{
    public:
        SAT_DefaultPanelSkin();
};

//------------------------------
//
//------------------------------

class SAT_DefaultTextSkin : public SAT_DefaultPanelSkin
{
    public:
        SAT_DefaultTextSkin();
};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

SAT_DefaultSkin::SAT_DefaultSkin()
{
    setBackgroundColor(SAT_Color(0.20, 0.20, 0.20));
    setForegroundColor(SAT_Color(0.80, 0.80, 0.80));
    setTextColor(SAT_Color(0.60, 0.60, 0.60));
    setTextSize(10.0);
    setBorderColor(SAT_Color(0.30, 0.30, 0.30));
    setBorderWidth(1.0);
}

//------------------------------
//
//------------------------------

SAT_DefaultPanelSkin::SAT_DefaultPanelSkin()
: SAT_DefaultSkin()
{
    setBackgroundColor(SAT_Color(0.25, 0.25, 0.25));
}

//------------------------------
//
//------------------------------

SAT_DefaultTextSkin::SAT_DefaultTextSkin()
: SAT_DefaultPanelSkin()
{
    setBackgroundColor( SAT_Color(0.30, 0.30, 0.30));
    setBackgroundColor( SAT_Color(0.35, 0.35, 0.35), SAT_SKIN_HOVER,                     SAT_SKIN_MODE_MATCH);
    setBackgroundColor( SAT_Color(0.40, 0.40, 0.40), SAT_SKIN_SELECTED,                  SAT_SKIN_MODE_MATCH);
    setBackgroundColor( SAT_Color(0.45, 0.45, 0.45), SAT_SKIN_SELECTED | SAT_SKIN_HOVER, SAT_SKIN_MODE_MATCH);

    setTextColor(       SAT_Color(0.70, 0.70, 0.70), SAT_SKIN_HOVER,                     SAT_SKIN_MODE_MATCH);
    setTextColor(       SAT_Color(0.80, 0.80, 0.80), SAT_SKIN_SELECTED,                  SAT_SKIN_MODE_MATCH);
    setTextColor(       SAT_Color(0.90, 0.90, 0.90), SAT_SKIN_SELECTED | SAT_SKIN_HOVER, SAT_SKIN_MODE_MATCH);
}
