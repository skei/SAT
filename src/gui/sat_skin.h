#pragma once

#include "base/sat_base.h"

#define SAT_SKIN_STATE_NORMAL           0
#define SAT_SKIN_STATE_HOVERING         0x01
#define SAT_SKIN_STATE_DISABLED         0x02
#define SAT_SKIN_STATE_HIGHLIGHTED      0x04
#define SAT_SKIN_STATE_INTERACT         0x08
#define SAT_SKIN_STATE_ALL              0x0F
#define SAT_SKIN_STATE_COUNT            16

#define SAT_SKIN_MODE_ALL               0
#define SAT_SKIN_MODE_SINGLE            1
#define SAT_SKIN_MODE_MATCH             2
#define SAT_SKIN_MODE_ANY               3

//----------

#define SAT_SKIN_BACKGROUND_NONE        0
#define SAT_SKIN_BACKGROUND_COLOR       1
#define SAT_SKIN_BACKGROUND_GRADIENT    2
#define SAT_SKIN_BACKGROUND_IMAGE       3

#define SAT_SKIN_GRADIENT_NONE          0
#define SAT_SKIN_GRADIENT_VERTICAL      1

#define SAT_SKIN_DROP_SHADOW_NONE       0
#define SAT_SKIN_DROP_SHADOW_INNER      1
#define SAT_SKIN_DROP_SHADOW_OUTER      2

#define SAT_SKIN_BORDER_NONE            0
#define SAT_SKIN_BORDER_RECT            1
#define SAT_SKIN_BORDER_ROUNDED         2

#define SAT_SKIN_TEXT_NONE              0
#define SAT_SKIN_TEXT_NORMAL            1

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_Skin
{
    public:

        // SAT_Skin();
        // virtual ~SAT_Skin();

    public:

        uint32_t    getBackgroundMode(uint32_t AState);
        SAT_Color   getBackgroundColor(uint32_t AState);

        uint32_t    getGradientMode(uint32_t AState);
        SAT_Color   getGradientColor(uint32_t AState);

        intptr_t    getImage(uint32_t AState);

        uint32_t    getDropShadowMode(uint32_t AState);
        SAT_Color   getDropShadowColor(uint32_t AState);
        sat_coord_t getDropShadowSize(uint32_t AState);

        uint32_t    getBorderMode(uint32_t AState);
        SAT_Color   getBorderColor(uint32_t AState);
        sat_coord_t getBorderWidth(uint32_t AState);
        sat_coord_t getBorderRadius(uint32_t AState);
        uint32_t    getBorderCorners(uint32_t AState);
        uint32_t    getBorderEdges(uint32_t AState);

        uint32_t    getTextMode(uint32_t AState);
        SAT_Color   getTextColor(uint32_t AState);
        sat_coord_t getTextSize(uint32_t AState);
        uint32_t    getTextAlignment(uint32_t AState);
        intptr_t    getTextFont(uint32_t AState);
       
    public:

        void        setBackgroundMode(uint32_t AMode, uint32_t AState=SAT_SKIN_STATE_ALL, uint32_t AWhich=SAT_SKIN_MODE_ALL);
        void        setBackgroundColor(SAT_Color AColor, uint32_t AState=SAT_SKIN_STATE_ALL, uint32_t AWhich=SAT_SKIN_MODE_ALL);

        void        setGradientMode(uint32_t AMode, uint32_t AState=SAT_SKIN_STATE_ALL, uint32_t AWhich=SAT_SKIN_MODE_ALL);
        void        setGradientColor(SAT_Color AColor, uint32_t AState=SAT_SKIN_STATE_ALL, uint32_t AWhich=SAT_SKIN_MODE_ALL);

        void        setImage(intptr_t AImage, uint32_t AState=SAT_SKIN_STATE_ALL, uint32_t AWhich=SAT_SKIN_MODE_ALL);

        void        setDropShadowMode(uint32_t AMode, uint32_t AState=SAT_SKIN_STATE_ALL, uint32_t AWhich=SAT_SKIN_MODE_ALL);
        void        setDropShadowColor(SAT_Color AColor, uint32_t AState=SAT_SKIN_STATE_ALL, uint32_t AWhich=SAT_SKIN_MODE_ALL);
        void        setDropShadowSize(sat_coord_t ASize, uint32_t AState=SAT_SKIN_STATE_ALL, uint32_t AWhich=SAT_SKIN_MODE_ALL);

        void        setBorderMode(uint32_t AMode, uint32_t AState=SAT_SKIN_STATE_ALL, uint32_t AWhich=SAT_SKIN_MODE_ALL);
        void        setBorderColor(SAT_Color AColor, uint32_t AState=SAT_SKIN_STATE_ALL, uint32_t AWhich=SAT_SKIN_MODE_ALL);
        void        setBorderWidth(sat_coord_t AWidth, uint32_t AState=SAT_SKIN_STATE_ALL, uint32_t AWhich=SAT_SKIN_MODE_ALL);
        void        setBorderRadius(sat_coord_t ARadius, uint32_t AState=SAT_SKIN_STATE_ALL, uint32_t AWhich=SAT_SKIN_MODE_ALL);
        void        setBorderCorners(uint32_t ACorners, uint32_t AState=SAT_SKIN_STATE_ALL, uint32_t AWhich=SAT_SKIN_MODE_ALL);
        void        setBorderEdges(uint32_t AEdges, uint32_t AState=SAT_SKIN_STATE_ALL, uint32_t AWhich=SAT_SKIN_MODE_ALL);

        void        setTextMode(uint32_t AMode, uint32_t AState=SAT_SKIN_STATE_ALL, uint32_t AWhich=SAT_SKIN_MODE_ALL);
        void        setTextColor(SAT_Color AColor, uint32_t AState=SAT_SKIN_STATE_ALL, uint32_t AWhich=SAT_SKIN_MODE_ALL);
        void        setTextSize(sat_coord_t ASize, uint32_t AState=SAT_SKIN_STATE_ALL, uint32_t AWhich=SAT_SKIN_MODE_ALL);
        void        setTextAlignment(uint32_t AAlignment, uint32_t AState=SAT_SKIN_STATE_ALL, uint32_t AWhich=SAT_SKIN_MODE_ALL);
        void        setTextFont(intptr_t AFont, uint32_t AState=SAT_SKIN_STATE_ALL, uint32_t AWhich=SAT_SKIN_MODE_ALL);

    private:

        bool        check_state(uint32_t i, uint32_t AState, uint32_t AMode);

    protected:

        uint32_t            MBackgroundModes[SAT_SKIN_STATE_COUNT]  = {};
        SAT_Color           MBackgroundColors[SAT_SKIN_STATE_COUNT] = {};

        uint32_t            MGradientModes[SAT_SKIN_STATE_COUNT]    = {};
        SAT_Color           MGradientColors[SAT_SKIN_STATE_COUNT]   = {};

        intptr_t            MImages[SAT_SKIN_STATE_COUNT]           = {};

        uint32_t            MDropShadowModes[SAT_SKIN_STATE_COUNT]  = {};
        SAT_Color           MDropShadowColors[SAT_SKIN_STATE_COUNT] = {};
        sat_coord_t         MDropShadowSizes[SAT_SKIN_STATE_COUNT]  = {};

        uint32_t            MBorderModes[SAT_SKIN_STATE_COUNT]      = {};
        SAT_Color           MBorderColors[SAT_SKIN_STATE_COUNT]     = {};
        sat_coord_t         MBorderWidths[SAT_SKIN_STATE_COUNT]     = {};
        sat_coord_t         MBorderRadiuses[SAT_SKIN_STATE_COUNT]   = {};
        uint32_t            MBorderCorners[SAT_SKIN_STATE_COUNT]    = {};
        uint32_t            MBorderEdges[SAT_SKIN_STATE_COUNT]      = {};

        uint32_t            MTextModes[SAT_SKIN_STATE_COUNT]        = {};
        SAT_Color           MTextColors[SAT_SKIN_STATE_COUNT]       = {};
        sat_coord_t         MTextSizes[SAT_SKIN_STATE_COUNT]        = {};
        uint32_t            MTextAlignments[SAT_SKIN_STATE_COUNT]   = {};
        intptr_t            MTextFonts[SAT_SKIN_STATE_COUNT]        = {};

        // MDropShadowMode
        // MDropShadowColor
        // MDropShadowSize
};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

//------------------------------
// background
//------------------------------

uint32_t SAT_Skin::getBackgroundMode(uint32_t AState)
{
    SAT_Assert(AState < SAT_SKIN_STATE_COUNT);
    return MBackgroundModes[AState];
}

SAT_Color SAT_Skin::getBackgroundColor(uint32_t AState)
{
    SAT_Assert(AState < SAT_SKIN_STATE_COUNT);
    return MBackgroundColors[AState];
}

//------------------------------
// (background) gradient
//------------------------------

uint32_t SAT_Skin::getGradientMode(uint32_t AState)
{
    SAT_Assert(AState < SAT_SKIN_STATE_COUNT);
    return MGradientModes[AState];
}

SAT_Color SAT_Skin::getGradientColor(uint32_t AState)
{
    SAT_Assert(AState < SAT_SKIN_STATE_COUNT);
    return MGradientColors[AState];
}

//------------------------------
// (background) inage
//------------------------------

intptr_t SAT_Skin::getImage(uint32_t AState)
{
    SAT_Assert(AState < SAT_SKIN_STATE_COUNT);
    return MImages[AState];
}

//------------------------------
// (background) drop shadow
//------------------------------

uint32_t SAT_Skin::getDropShadowMode(uint32_t AState)
{
    SAT_Assert(AState < SAT_SKIN_STATE_COUNT);
    return MDropShadowModes[AState];
}

SAT_Color SAT_Skin::getDropShadowColor(uint32_t AState)
{
    SAT_Assert(AState < SAT_SKIN_STATE_COUNT);
    return MDropShadowColors[AState];
}

sat_coord_t SAT_Skin::getDropShadowSize(uint32_t AState)
{
    SAT_Assert(AState < SAT_SKIN_STATE_COUNT);
    return MDropShadowSizes[AState];
}

//------------------------------
// border
//------------------------------

uint32_t SAT_Skin::getBorderMode(uint32_t AState)
{
    SAT_Assert(AState < SAT_SKIN_STATE_COUNT);
    return MBorderModes[AState];
}

SAT_Color SAT_Skin::getBorderColor(uint32_t AState)
{
    SAT_Assert(AState < SAT_SKIN_STATE_COUNT);
    return MBorderColors[AState];
}

sat_coord_t SAT_Skin::getBorderWidth(uint32_t AState)
{
    SAT_Assert(AState < SAT_SKIN_STATE_COUNT);
    return MBorderWidths[AState];
}

sat_coord_t SAT_Skin::getBorderRadius(uint32_t AState)
{
    SAT_Assert(AState < SAT_SKIN_STATE_COUNT);
    return MBorderRadiuses[AState];
}

uint32_t SAT_Skin::getBorderCorners(uint32_t AState)
{
    SAT_Assert(AState < SAT_SKIN_STATE_COUNT);
    return MBorderCorners[AState];
}

uint32_t SAT_Skin::getBorderEdges(uint32_t AState)
{
    SAT_Assert(AState < SAT_SKIN_STATE_COUNT);
    return MBorderEdges[AState];
}

//------------------------------
// text
//------------------------------

uint32_t SAT_Skin::getTextMode(uint32_t AState)
{
    SAT_Assert(AState < SAT_SKIN_STATE_COUNT);
    return MTextModes[AState];
}

SAT_Color SAT_Skin::getTextColor(uint32_t AState)
{
    SAT_Assert(AState < SAT_SKIN_STATE_COUNT);
    return MTextColors[AState];
}

sat_coord_t SAT_Skin::getTextSize(uint32_t AState)
{
    SAT_Assert(AState < SAT_SKIN_STATE_COUNT);
    return MTextSizes[AState];
}

uint32_t SAT_Skin::getTextAlignment(uint32_t AState)
{
    SAT_Assert(AState < SAT_SKIN_STATE_COUNT);
    return MTextAlignments[AState];
}

intptr_t SAT_Skin::getTextFont(uint32_t AState)
{
    SAT_Assert(AState < SAT_SKIN_STATE_COUNT);
    return MTextFonts[AState];
}

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

//------------------------------
// background
//------------------------------

void SAT_Skin::setBackgroundMode(uint32_t AMode, uint32_t AState, uint32_t AWhich)
{
    SAT_Assert(AState < SAT_SKIN_STATE_COUNT);
    for (uint32_t i=0; i<SAT_SKIN_STATE_COUNT; i++)
        if (check_state(i,AState,AWhich)) MBackgroundModes[i] = AMode;
}

void SAT_Skin::setBackgroundColor(SAT_Color AColor, uint32_t AState, uint32_t AWhich)
{
    SAT_Assert(AState < SAT_SKIN_STATE_COUNT);
    for (uint32_t i=0; i<SAT_SKIN_STATE_COUNT; i++)
        if (check_state(i,AState,AWhich)) MBackgroundColors[i] = AColor;
}

//------------------------------
// (background) gradient
//------------------------------

void SAT_Skin::setGradientMode(uint32_t AMode, uint32_t AState, uint32_t AWhich)
{
    SAT_Assert(AState < SAT_SKIN_STATE_COUNT);
    for (uint32_t i=0; i<SAT_SKIN_STATE_COUNT; i++)
        if (check_state(i,AState,AWhich)) MGradientModes[i] = AMode;
}

void SAT_Skin::setGradientColor(SAT_Color AColor, uint32_t AState, uint32_t AWhich)
{
    SAT_Assert(AState < SAT_SKIN_STATE_COUNT);
    for (uint32_t i=0; i<SAT_SKIN_STATE_COUNT; i++)
        if (check_state(i,AState,AWhich)) MGradientColors[i] = AColor;
}

//------------------------------
// (background) image
//------------------------------

void SAT_Skin::setImage(intptr_t AImage, uint32_t AState, uint32_t AWhich)
{
    SAT_Assert(AState < SAT_SKIN_STATE_COUNT);
    for (uint32_t i=0; i<SAT_SKIN_STATE_COUNT; i++)
        if (check_state(i,AState,AWhich)) MImages[i] = AImage;
}

//------------------------------
// (background) drop shadow
//------------------------------

void SAT_Skin::setDropShadowMode(uint32_t AMode, uint32_t AState, uint32_t AWhich)
{
    SAT_Assert(AState < SAT_SKIN_STATE_COUNT);
    for (uint32_t i=0; i<SAT_SKIN_STATE_COUNT; i++)
        if (check_state(i,AState,AWhich)) MDropShadowModes[i] = AMode;
}

void SAT_Skin::setDropShadowColor(SAT_Color AColor, uint32_t AState, uint32_t AWhich)
{
    SAT_Assert(AState < SAT_SKIN_STATE_COUNT);
    for (uint32_t i=0; i<SAT_SKIN_STATE_COUNT; i++)
        if (check_state(i,AState,AWhich)) MDropShadowColors[i] = AColor;
}

void SAT_Skin::setDropShadowSize(sat_coord_t ASize, uint32_t AState, uint32_t AWhich)
{
    SAT_Assert(AState < SAT_SKIN_STATE_COUNT);
    for (uint32_t i=0; i<SAT_SKIN_STATE_COUNT; i++)
        if (check_state(i,AState,AWhich)) MDropShadowSizes[i] = ASize;
}

//------------------------------
// border
//------------------------------

void SAT_Skin::setBorderMode(uint32_t AMode, uint32_t AState, uint32_t AWhich)
{
    SAT_Assert(AState < SAT_SKIN_STATE_COUNT);
    for (uint32_t i=0; i<SAT_SKIN_STATE_COUNT; i++)
        if (check_state(i,AState,AWhich)) MBorderModes[i] = AMode;
}

void SAT_Skin::setBorderColor(SAT_Color AColor, uint32_t AState, uint32_t AWhich)
{
    SAT_Assert(AState < SAT_SKIN_STATE_COUNT);
    for (uint32_t i=0; i<SAT_SKIN_STATE_COUNT; i++)
        if (check_state(i,AState,AWhich)) MBorderColors[i] = AColor;
}

void SAT_Skin::setBorderWidth(sat_coord_t AWidth, uint32_t AState, uint32_t AWhich)
{
    SAT_Assert(AState < SAT_SKIN_STATE_COUNT);
    for (uint32_t i=0; i<SAT_SKIN_STATE_COUNT; i++)
        if (check_state(i,AState,AWhich)) MBorderWidths[i] = AWidth;
}

void SAT_Skin::setBorderRadius(sat_coord_t ARadius, uint32_t AState, uint32_t AWhich)
{
    SAT_Assert(AState < SAT_SKIN_STATE_COUNT);
    for (uint32_t i=0; i<SAT_SKIN_STATE_COUNT; i++)
        if (check_state(i,AState,AWhich)) MBorderRadiuses[i] = ARadius;
}

void SAT_Skin::setBorderCorners(uint32_t ACorners, uint32_t AState, uint32_t AWhich)
{
    SAT_Assert(AState < SAT_SKIN_STATE_COUNT);
    for (uint32_t i=0; i<SAT_SKIN_STATE_COUNT; i++)
        if (check_state(i,AState,AWhich)) MBorderCorners[i] = ACorners;
}

void SAT_Skin::setBorderEdges(uint32_t AEdges, uint32_t AState, uint32_t AWhich)
{
    SAT_Assert(AState < SAT_SKIN_STATE_COUNT);
    for (uint32_t i=0; i<SAT_SKIN_STATE_COUNT; i++)
        if (check_state(i,AState,AWhich)) MBorderEdges[i] = AEdges;
}

//------------------------------
// text
//------------------------------

void SAT_Skin::setTextMode(uint32_t AMode, uint32_t AState, uint32_t AWhich)
{
    SAT_Assert(AState < SAT_SKIN_STATE_COUNT);
    for (uint32_t i=0; i<SAT_SKIN_STATE_COUNT; i++)
        if (check_state(i,AState,AWhich)) MTextModes[i] = AMode;
}

void SAT_Skin::setTextColor(SAT_Color AColor, uint32_t AState, uint32_t AWhich)
{
    SAT_Assert(AState < SAT_SKIN_STATE_COUNT);
    for (uint32_t i=0; i<SAT_SKIN_STATE_COUNT; i++)
        if (check_state(i,AState,AWhich)) MTextColors[i] = AColor;
}

void SAT_Skin::setTextSize(sat_coord_t ASize, uint32_t AState, uint32_t AWhich)
{
    SAT_Assert(AState < SAT_SKIN_STATE_COUNT);
    for (uint32_t i=0; i<SAT_SKIN_STATE_COUNT; i++)
        if (check_state(i,AState,AWhich)) MTextSizes[i] = ASize;
}

void SAT_Skin::setTextAlignment(uint32_t AAlignment, uint32_t AState, uint32_t AWhich)
{
    SAT_Assert(AState < SAT_SKIN_STATE_COUNT);
    for (uint32_t i=0; i<SAT_SKIN_STATE_COUNT; i++)
        if (check_state(i,AState,AWhich)) MTextAlignments[i] = AAlignment;
}

void SAT_Skin::setTextFont(intptr_t AFont, uint32_t AState, uint32_t AWhich)
{
    SAT_Assert(AState < SAT_SKIN_STATE_COUNT);
    for (uint32_t i=0; i<SAT_SKIN_STATE_COUNT; i++)
        if (check_state(i,AState,AWhich)) MTextFonts[i] = AFont;
}

//------------------------------
//
//------------------------------

bool SAT_Skin::check_state(uint32_t i, uint32_t AState, uint32_t AWhich)
{
    switch (AWhich)
    {
        case SAT_SKIN_MODE_ALL:
            return true;
        case SAT_SKIN_MODE_SINGLE:
            if (i == AState) return true;
            return false;
        case SAT_SKIN_MODE_MATCH:
            if ((i & AState) == AState) return true;
            return false;
        case SAT_SKIN_MODE_ANY:
            if ((i & AState)) return true;
            break;
    }
    return false;
}
