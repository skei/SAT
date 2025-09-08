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
    setName("Default");

    setBackgroundMode(SAT_SKIN_BACKGROUND_COLOR);
    setBackgroundColor(SAT_Color(0.20, 0.20, 0.20));

    setGradientMode(SAT_SKIN_GRADIENT_NONE);
    setGradientColor(SAT_Color(0.10, 0.10, 0.10));

    setImage(0);

    setDropShadowMode(SAT_SKIN_DROP_SHADOW_NONE);
    setDropShadowColor(SAT_Color(0.00,0.00,0.00,0.25));
    setDropShadowSize(10.0);

    setBorderMode(SAT_SKIN_BORDER_RECT);
    setBorderColor(SAT_Color(0.30, 0.30, 0.30));
    setBorderWidth(1.0);
    setBorderRadius(5.0);
    setBorderCorners(SAT_CORNER_ALL);
    setBorderEdges(SAT_EDGE_ALL);

    setTextMode(SAT_SKIN_TEXT_NORMAL);
    setTextColor(SAT_Color(0.60, 0.60, 0.60));
    setTextSize(10.0);
    setTextAlignment(SAT_TEXT_ALIGN_CENTER);
    setTextFont(0);
}

//------------------------------
//
//------------------------------

SAT_DefaultPanelSkin::SAT_DefaultPanelSkin()
: SAT_DefaultSkin()
{
    setName("DefaultPanel");
    setBackgroundColor(SAT_Color(0.25, 0.25, 0.25));
    setBorderColor(SAT_Color(0.35, 0.35, 0.35));
}

//------------------------------
//
//------------------------------

SAT_DefaultTextSkin::SAT_DefaultTextSkin()
: SAT_DefaultPanelSkin()
{
    setName("DefaultText");
    setBackgroundColor(SAT_Color(0.30, 0.30, 0.30));
    setBackgroundColor(SAT_Color(0.35, 0.35, 0.35), SAT_SKIN_STATE_HOVERING, SAT_SKIN_MATCH_MATCH);
    setBackgroundColor(SAT_Color(0.40, 0.40, 0.40), SAT_SKIN_STATE_HIGHLIGHTED, SAT_SKIN_MATCH_MATCH);
    setBackgroundColor(SAT_Color(0.45, 0.45, 0.45), SAT_SKIN_STATE_HIGHLIGHTED | SAT_SKIN_STATE_HOVERING, SAT_SKIN_MATCH_MATCH);

    setBorderColor(SAT_Color(0.40, 0.40, 0.40));
    setBorderColor(SAT_Color(0.45, 0.45, 0.45), SAT_SKIN_STATE_HOVERING, SAT_SKIN_MATCH_MATCH);
    setBorderColor(SAT_Color(0.50, 0.50, 0.50), SAT_SKIN_STATE_HIGHLIGHTED, SAT_SKIN_MATCH_MATCH);
    setBorderColor(SAT_Color(0.55, 0.55, 0.55), SAT_SKIN_STATE_HIGHLIGHTED | SAT_SKIN_STATE_HOVERING, SAT_SKIN_MATCH_MATCH);

    setTextColor(SAT_Color(0.70, 0.70, 0.70), SAT_SKIN_STATE_HOVERING, SAT_SKIN_MATCH_MATCH);
    setTextColor(SAT_Color(0.80, 0.80, 0.80), SAT_SKIN_STATE_HIGHLIGHTED, SAT_SKIN_MATCH_MATCH);
    setTextColor(SAT_Color(0.90, 0.90, 0.90), SAT_SKIN_STATE_HIGHLIGHTED | SAT_SKIN_STATE_HOVERING, SAT_SKIN_MATCH_MATCH);
}
