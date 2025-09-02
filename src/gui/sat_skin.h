#pragma once

#include "gui/sat_gui_base.h"

#define SAT_SKIN_NORMAL     0
#define SAT_SKIN_HOVER      0x01
#define SAT_SKIN_ENABLED    0
#define SAT_SKIN_DISABLED   0x02
#define SAT_SKIN_SELECTED   0x04
#define SAT_SKIN_INTERACT   0x08
#define SAT_SKIN_ALL        0x0F

#define SAT_SKIN_NUM_STATES 16

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_Skin
{
    public:

        SAT_Skin();
        virtual ~SAT_Skin();

    public:

        virtual SAT_Color   getBackgroundColor(uint32_t AState);
        virtual SAT_Color   getForegroundColor(uint32_t AState);
        virtual SAT_Color   getTextColor(uint32_t AState);
        virtual sat_coord_t getTextSize(uint32_t AState);
        virtual SAT_Color   getBorderColor(uint32_t AState);
        virtual sat_coord_t getBorderWidth(uint32_t AState);
       
        virtual void        setBackgroundColor(uint32_t AState, SAT_Color AColor);
        virtual void        setForegroundColor(uint32_t AState, SAT_Color AColor);
        virtual void        setTextColor(uint32_t AState, SAT_Color AColor);
        virtual void        setTextSize(uint32_t AState, sat_coord_t ASize);
        virtual void        setBorderColor(uint32_t AState, SAT_Color AColor);
        virtual void        setBorderWidth(uint32_t AState, sat_coord_t AWidth);

    protected:

        SAT_Color   MBackgroundColors[SAT_SKIN_NUM_STATES]  = {};
        SAT_Color   MForegroundColors[SAT_SKIN_NUM_STATES]  = {};
        SAT_Color   MTextColors[SAT_SKIN_NUM_STATES]        = {};
        sat_coord_t MTextSizes[SAT_SKIN_NUM_STATES]         = {};
        SAT_Color   MBorderColors[SAT_SKIN_NUM_STATES]      = {};
        sat_coord_t MBorderWidths[SAT_SKIN_NUM_STATES]      = {};

};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

SAT_Skin::SAT_Skin()
{
}

SAT_Skin::~SAT_Skin()
{
}

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

void SAT_Skin::setBackgroundColor(uint32_t AState, SAT_Color AColor)
{
    if ((AState==SAT_SKIN_NORMAL) || (AState==SAT_SKIN_ALL)) MBackgroundColors[0] = AColor;
    for (uint32_t i=1; i<SAT_SKIN_NUM_STATES; i++)
    {
        if (i & AState) MBackgroundColors[i] = AColor;
    }
}

void SAT_Skin::setForegroundColor(uint32_t AState, SAT_Color AColor)
{
    if ((AState==SAT_SKIN_NORMAL) || (AState==SAT_SKIN_ALL)) MForegroundColors[0] = AColor;
    for (uint32_t i=1; i<SAT_SKIN_NUM_STATES; i++)
    {
        if (i & AState) MForegroundColors[i] = AColor;
    }
}

void SAT_Skin::setTextColor(uint32_t AState, SAT_Color AColor)
{
    if ((AState==SAT_SKIN_NORMAL) || (AState==SAT_SKIN_ALL)) MTextColors[0] = AColor;
    for (uint32_t i=1; i<SAT_SKIN_NUM_STATES; i++)
    {
        if (i & AState) MTextColors[i] = AColor;
    }
}

void SAT_Skin::setTextSize(uint32_t AState, sat_coord_t ASize)
{
    if ((AState==SAT_SKIN_NORMAL) || (AState==SAT_SKIN_ALL)) MTextSizes[0] = ASize;
    for (uint32_t i=1; i<SAT_SKIN_NUM_STATES; i++)
    {
        if (i & AState) MTextSizes[i] = ASize;
    }
}

void SAT_Skin::setBorderColor(uint32_t AState, SAT_Color AColor)
{
    if ((AState==SAT_SKIN_NORMAL) || (AState==SAT_SKIN_ALL)) MBorderColors[0] = AColor;
    for (uint32_t i=1; i<SAT_SKIN_NUM_STATES; i++)
    {
        if (i & AState) MBorderColors[i] = AColor;
    }
}

void SAT_Skin::setBorderWidth(uint32_t AState, sat_coord_t AWidth)
{
    if ((AState==SAT_SKIN_NORMAL) || (AState==SAT_SKIN_ALL)) MBorderWidths[0] = AWidth;
    for (uint32_t i=1; i<SAT_SKIN_NUM_STATES; i++)
    {
        if (i & AState) MBorderWidths[i] = AWidth;
    }
}

