#pragma once

#include "base/sat_base.h"
#include "gui/sat_gui_base.h"
#include "gui/sat_skin.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_DefaultSkin
: public SAT_Skin
{
    public:

        SAT_DefaultSkin();
        virtual ~SAT_DefaultSkin();

};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

SAT_DefaultSkin::SAT_DefaultSkin()
: SAT_Skin()
{
    setBackgroundColor(SAT_Color(0.50, 0.50, 0.50));
    setBackgroundColor(SAT_Color(0.60, 0.60, 0.60), SAT_SKIN_HOVER,                     SAT_SKIN_MODE_MATCH);
    setBackgroundColor(SAT_Color(0.60, 0.20, 0.20), SAT_SKIN_SELECTED,                  SAT_SKIN_MODE_MATCH);
    setBackgroundColor(SAT_Color(0.70, 0.30, 0.30), SAT_SKIN_SELECTED | SAT_SKIN_HOVER, SAT_SKIN_MODE_MATCH);

    setForegroundColor(SAT_Black);

    setTextColor(SAT_Color(0.00, 0.00, 0.00));
    setTextColor(SAT_Color(0.00, 0.00, 0.00), SAT_SKIN_HOVER,                     SAT_SKIN_MODE_MATCH);
    setTextColor(SAT_Color(1.00, 1.00, 1.00), SAT_SKIN_SELECTED,                  SAT_SKIN_MODE_MATCH);
    setTextColor(SAT_Color(1.00, 1.00, 1.00), SAT_SKIN_SELECTED | SAT_SKIN_HOVER, SAT_SKIN_MODE_MATCH);

    setTextSize(10.0);

    setBorderColor(SAT_Black);
    setBorderColor(SAT_White, SAT_SKIN_HOVER, SAT_SKIN_MODE_MATCH);

    setBorderWidth(1.0);

}

SAT_DefaultSkin::~SAT_DefaultSkin()
{
}
