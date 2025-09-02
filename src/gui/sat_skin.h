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
       
        virtual void        setBackgroundColor(SAT_Color AColor, uint32_t AState=SAT_SKIN_ALL, bool AUnique=false);
        virtual void        setForegroundColor(SAT_Color AColor, uint32_t AState=SAT_SKIN_ALL, bool AUnique=false);
        virtual void        setTextColor(SAT_Color AColor, uint32_t AState=SAT_SKIN_ALL, bool AUnique=false);
        virtual void        setTextSize(sat_coord_t ASize, uint32_t AState=SAT_SKIN_ALL, bool AUnique=false);
        virtual void        setBorderColor(SAT_Color AColor, uint32_t AState=SAT_SKIN_ALL, bool AUnique=false);
        virtual void        setBorderWidth(sat_coord_t AWidth, uint32_t AState=SAT_SKIN_ALL, bool AUnique=false);

    private:

        bool    correct_state(uint32_t i, uint32_t AState, bool AUnique=false);

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

void SAT_Skin::setBackgroundColor(SAT_Color AColor, uint32_t AState, bool AUnique)
{
    //if ((AState==SAT_SKIN_NORMAL) || (AState==SAT_SKIN_ALL)) MBackgroundColors[0] = AColor;
    for (uint32_t i=0; i<SAT_SKIN_NUM_STATES; i++)
    {
        //if (i & AState) MBackgroundColors[i] = AColor;
        if (correct_state(i,AState,AUnique)) MBackgroundColors[i] = AColor;
    }
}

void SAT_Skin::setForegroundColor(SAT_Color AColor, uint32_t AState, bool AUnique)
{
    //if ((AState==SAT_SKIN_NORMAL) || (AState==SAT_SKIN_ALL)) MForegroundColors[0] = AColor;
    for (uint32_t i=0; i<SAT_SKIN_NUM_STATES; i++)
    {
        //if (i & AState) MForegroundColors[i] = AColor;
        if (correct_state(i,AState,AUnique)) MForegroundColors[i] = AColor;
    }
}

void SAT_Skin::setTextColor(SAT_Color AColor, uint32_t AState, bool AUnique)
{
    //if ((AState==SAT_SKIN_NORMAL) || (AState==SAT_SKIN_ALL)) MTextColors[0] = AColor;
    for (uint32_t i=0; i<SAT_SKIN_NUM_STATES; i++)
    {
        //if (i & AState) MTextColors[i] = AColor;
        if (correct_state(i,AState,AUnique)) MTextColors[i] = AColor;
    }
}

void SAT_Skin::setTextSize(sat_coord_t ASize, uint32_t AState, bool AUnique)
{
    //if ((AState==SAT_SKIN_NORMAL) || (AState==SAT_SKIN_ALL)) MTextSizes[0] = ASize;
    for (uint32_t i=0; i<SAT_SKIN_NUM_STATES; i++)
    {
        //if (i & AState) MTextSizes[i] = ASize;
        if (correct_state(i,AState,AUnique)) MTextSizes[i] = ASize;
    }
}

void SAT_Skin::setBorderColor(SAT_Color AColor, uint32_t AState, bool AUnique)
{
    //if ((AState==SAT_SKIN_NORMAL) || (AState==SAT_SKIN_ALL)) MBorderColors[0] = AColor;
    for (uint32_t i=0; i<SAT_SKIN_NUM_STATES; i++)
    {
        //if (i & AState) MBorderColors[i] = AColor;
        if (correct_state(i,AState,AUnique)) MBorderColors[i] = AColor;
    }
}

void SAT_Skin::setBorderWidth(sat_coord_t AWidth, uint32_t AState, bool AUnique)
{
    //if ((AState==SAT_SKIN_NORMAL) || (AState==SAT_SKIN_ALL)) MBorderWidths[0] = AWidth;
    for (uint32_t i=0; i<SAT_SKIN_NUM_STATES; i++)
    {
        //if (i & AState) MBorderWidths[i] = AWidth;
        if (correct_state(i,AState,AUnique)) MBorderWidths[i] = AWidth;
    }
}

//------------------------------
//
//------------------------------

bool SAT_Skin::correct_state(uint32_t i, uint32_t AState, bool AUnique)
{
    if  ( (i==0) && ((AState==SAT_SKIN_NORMAL) || (AState==SAT_SKIN_ALL)) ) return true;
    if (AUnique) { if ((i & AState) == AState) return true; }
    else         { if (i & AState)             return true; }
    return false;
}