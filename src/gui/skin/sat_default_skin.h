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
    setBackgroundColors( SAT_Color(0.50,0.50,0.50) );
    setBackgroundColors( SAT_Color(0.45,0.45,0.45), SAT_SKIN_HOVER );
    setBackgroundColors( SAT_Color(0.30,0.30,0.70), SAT_SKIN_SELECTED );
    setBackgroundColors( SAT_Color(0.20,0.20,0.80), SAT_SKIN_SELECTED | SAT_SKIN_HOVER, true );

    setForegroundColors( SAT_Black );

    setTextColors( SAT_Black );
    setTextColors( SAT_White,        SAT_SKIN_SELECTED );
    setTextColors( SAT_BrightYellow, SAT_SKIN_HOVER );
    setTextColors( SAT_BrightRed,    SAT_SKIN_SELECTED | SAT_SKIN_HOVER, true );

    setTextSizes( 10.0 );

    setBorderColors( SAT_Black );
    //setBorderColors( SAT_White, SAT_SKIN_HOVER );

    setBorderWidths( 1.0 );

}

SAT_DefaultSkin::~SAT_DefaultSkin()
{
}
