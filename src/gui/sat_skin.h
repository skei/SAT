#pragma once

#include "base/sat_base.h"

#define SAT_SKIN_NORMAL     0
#define SAT_SKIN_HOVER      0x01
#define SAT_SKIN_DISABLED   0x02
#define SAT_SKIN_SELECTED   0x04
#define SAT_SKIN_INTERACT   0x08
#define SAT_SKIN_ALL        0x0F

#define SAT_SKIN_NUM_STATES 16

/*
    todo:
        s#define SAT_SKIN_HIGHLIGHT
*/

//----------


#define SAT_SKIN_MODE_ALL       0
#define SAT_SKIN_MODE_SINGLE    1
#define SAT_SKIN_MODE_MATCH     2
#define SAT_SKIN_MODE_ANY       3

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

        SAT_Color   getBackgroundColor(uint32_t AState);
        SAT_Color   getForegroundColor(uint32_t AState);
        SAT_Color   getTextColor(uint32_t AState);
        sat_coord_t getTextSize(uint32_t AState);
        SAT_Color   getBorderColor(uint32_t AState);
        sat_coord_t getBorderWidth(uint32_t AState);
       
        void        setBackgroundColor(SAT_Color AColor, uint32_t AState=SAT_SKIN_ALL, uint32_t AMode=SAT_SKIN_MODE_ALL);
        void        setForegroundColor(SAT_Color AColor, uint32_t AState=SAT_SKIN_ALL, uint32_t AMode=SAT_SKIN_MODE_ALL);
        void        setTextColor(SAT_Color AColor, uint32_t AState=SAT_SKIN_ALL, uint32_t AMode=SAT_SKIN_MODE_ALL);
        void        setTextSize(sat_coord_t ASize, uint32_t AState=SAT_SKIN_ALL, uint32_t AMode=SAT_SKIN_MODE_ALL);
        void        setBorderColor(SAT_Color AColor, uint32_t AState=SAT_SKIN_ALL, uint32_t AMode=SAT_SKIN_MODE_ALL);
        void        setBorderWidth(sat_coord_t AWidth, uint32_t AState=SAT_SKIN_ALL, uint32_t AMode=SAT_SKIN_MODE_ALL);

    private:

        bool        check_state(uint32_t i, uint32_t AState, uint32_t AMode);

    protected:

        SAT_Color           MBackgroundColors[SAT_SKIN_NUM_STATES]  = {};
        SAT_Color           MForegroundColors[SAT_SKIN_NUM_STATES]  = {};
        SAT_Color           MTextColors[SAT_SKIN_NUM_STATES]        = {};
        sat_coord_t         MTextSizes[SAT_SKIN_NUM_STATES]         = {};
        SAT_Color           MBorderColors[SAT_SKIN_NUM_STATES]      = {};
        sat_coord_t         MBorderWidths[SAT_SKIN_NUM_STATES]      = {};

};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

// SAT_Skin::SAT_Skin()
// {
// }

// SAT_Skin::~SAT_Skin()
// {
// }

//------------------------------
//
//------------------------------

SAT_Color SAT_Skin::getBackgroundColor(uint32_t AState)
{
    SAT_Assert(AState < SAT_SKIN_NUM_STATES);
    return MBackgroundColors[AState];
}

SAT_Color SAT_Skin::getForegroundColor(uint32_t AState)
{
    SAT_Assert(AState < SAT_SKIN_NUM_STATES);
    return MForegroundColors[AState];
}

SAT_Color SAT_Skin::getTextColor(uint32_t AState)
{
    SAT_Assert(AState < SAT_SKIN_NUM_STATES);
    return MTextColors[AState];
}

sat_coord_t SAT_Skin::getTextSize(uint32_t AState)
{
    SAT_Assert(AState < SAT_SKIN_NUM_STATES);
    return MTextSizes[AState];
}

SAT_Color SAT_Skin::getBorderColor(uint32_t AState)
{
    SAT_Assert(AState < SAT_SKIN_NUM_STATES);
    return MBorderColors[AState];
}

sat_coord_t SAT_Skin::getBorderWidth(uint32_t AState)
{
    SAT_Assert(AState < SAT_SKIN_NUM_STATES);
    return MBorderWidths[AState];
}

//------------------------------
//
//------------------------------

void SAT_Skin::setBackgroundColor(SAT_Color AColor, uint32_t AState, uint32_t AMode)
{
    SAT_Assert(AState < SAT_SKIN_NUM_STATES);
    for (uint32_t i=0; i<SAT_SKIN_NUM_STATES; i++)
        if (check_state(i,AState,AMode)) MBackgroundColors[i] = AColor;
}

void SAT_Skin::setForegroundColor(SAT_Color AColor, uint32_t AState, uint32_t AMode)
{
    SAT_Assert(AState < SAT_SKIN_NUM_STATES);
    for (uint32_t i=0; i<SAT_SKIN_NUM_STATES; i++)
        if (check_state(i,AState,AMode)) MForegroundColors[i] = AColor;
}

void SAT_Skin::setTextColor(SAT_Color AColor, uint32_t AState, uint32_t AMode)
{
    SAT_Assert(AState < SAT_SKIN_NUM_STATES);
    for (uint32_t i=0; i<SAT_SKIN_NUM_STATES; i++)
        if (check_state(i,AState,AMode)) MTextColors[i] = AColor;
}

void SAT_Skin::setTextSize(sat_coord_t ASize, uint32_t AState, uint32_t AMode)
{
    SAT_Assert(AState < SAT_SKIN_NUM_STATES);
    for (uint32_t i=0; i<SAT_SKIN_NUM_STATES; i++)
        if (check_state(i,AState,AMode)) MTextSizes[i] = ASize;
}

void SAT_Skin::setBorderColor(SAT_Color AColor, uint32_t AState, uint32_t AMode)
{
    SAT_Assert(AState < SAT_SKIN_NUM_STATES);
    for (uint32_t i=0; i<SAT_SKIN_NUM_STATES; i++)
        if (check_state(i,AState,AMode)) MBorderColors[i] = AColor;
}

void SAT_Skin::setBorderWidth(sat_coord_t AWidth, uint32_t AState, uint32_t AMode)
{
    SAT_Assert(AState < SAT_SKIN_NUM_STATES);
    for (uint32_t i=0; i<SAT_SKIN_NUM_STATES; i++)
        if (check_state(i,AState,AMode)) MBorderWidths[i] = AWidth;
}

//------------------------------
//
//------------------------------

bool SAT_Skin::check_state(uint32_t i, uint32_t AState, uint32_t AMode)
{
    switch (AMode)
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
