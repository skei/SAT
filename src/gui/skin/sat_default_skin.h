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
    setBackgroundColor( SAT_SKIN_ALL,       SAT_Grey        );
    setForegroundColor( SAT_SKIN_ALL,       SAT_DarkGrey    );
    setTextColor(       SAT_SKIN_ALL,       SAT_Black       );
    setTextSize(        SAT_SKIN_ALL,       10.0            );
    setBorderColor(     SAT_SKIN_ALL,       SAT_DarkestGrey );
    setBorderWidth(     SAT_SKIN_ALL,       1.0             );

    setBackgroundColor( SAT_SKIN_SELECTED,  SAT_LightGrey   );
    setForegroundColor( SAT_SKIN_SELECTED,  SAT_DarkerGrey  );
    setTextColor(       SAT_SKIN_SELECTED,  SAT_White       );
}

SAT_DefaultSkin::~SAT_DefaultSkin()
{
}
