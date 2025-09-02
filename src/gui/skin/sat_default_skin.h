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
    setBackgroundColor( SAT_Color(0.50,0.50,0.50) );
    setBackgroundColor( SAT_Color(0.45,0.45,0.45), SAT_SKIN_HOVER );
    setBackgroundColor( SAT_Color(0.30,0.30,0.70), SAT_SKIN_SELECTED );
    setBackgroundColor( SAT_Color(0.20,0.20,0.80), SAT_SKIN_SELECTED | SAT_SKIN_HOVER, true );

    setForegroundColor( SAT_Black );

    setTextColor( SAT_Black );
    setTextColor( SAT_White,        SAT_SKIN_SELECTED );
    setTextColor( SAT_BrightYellow, SAT_SKIN_HOVER );
    setTextColor( SAT_BrightRed,    SAT_SKIN_SELECTED | SAT_SKIN_HOVER, true );

    setTextSize( 10.0 );

    setBorderColor( SAT_Black );
    //setBorderColor( SAT_White, SAT_SKIN_HOVER );

    setBorderWidth( 1.0 );

}

SAT_DefaultSkin::~SAT_DefaultSkin()
{
}
