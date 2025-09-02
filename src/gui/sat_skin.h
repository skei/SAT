#pragma once

#include "gui/sat_gui_base.h"

#define SAT_SKIN_NORMAL     0
#define SAT_SKIN_HOVER      0x01
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
       
        virtual void        setBackgroundColor(uint32_t AIndex, SAT_Color AColor);
        virtual void        setForegroundColor(uint32_t AIndex, SAT_Color AColor);
        virtual void        setTextColor(uint32_t AIndex, SAT_Color AColor);
        virtual void        setTextSize(uint32_t AIndex, sat_coord_t ASize);
        virtual void        setBorderColor(uint32_t AIndex, SAT_Color AColor);
        virtual void        setBorderWidth(uint32_t AIndex, sat_coord_t AWidth);

        virtual void        setBackgroundColors(SAT_Color AColor, uint32_t AState=SAT_SKIN_ALL, bool AUnique=false);
        virtual void        setForegroundColors(SAT_Color AColor, uint32_t AState=SAT_SKIN_ALL, bool AUnique=false);
        virtual void        setTextColors(SAT_Color AColor, uint32_t AState=SAT_SKIN_ALL, bool AUnique=false);
        virtual void        setTextSizes(sat_coord_t ASize, uint32_t AState=SAT_SKIN_ALL, bool AUnique=false);
        virtual void        setBorderColors(SAT_Color AColor, uint32_t AState=SAT_SKIN_ALL, bool AUnique=false);
        virtual void        setBorderWidths(sat_coord_t AWidth, uint32_t AState=SAT_SKIN_ALL, bool AUnique=false);

    private:

        bool                check_state(uint32_t i, uint32_t AState, bool AUnique=false);

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

void SAT_Skin::setBackgroundColor(uint32_t AIndex, SAT_Color AColor)
{
    SAT_Assert(AIndex < SAT_SKIN_NUM_STATES);
    MBackgroundColors[AIndex] = AColor;
}

void SAT_Skin::setForegroundColor(uint32_t AIndex, SAT_Color AColor)
{
    SAT_Assert(AIndex < SAT_SKIN_NUM_STATES);
    MForegroundColors[AIndex] = AColor;
}

void SAT_Skin::setTextColor(uint32_t AIndex, SAT_Color AColor)
{
    SAT_Assert(AIndex < SAT_SKIN_NUM_STATES);
    MTextColors[AIndex] = AColor;
}

void SAT_Skin::setTextSize(uint32_t AIndex, sat_coord_t ASize)
{
    SAT_Assert(AIndex < SAT_SKIN_NUM_STATES);
    MTextSizes[AIndex] = ASize;
}

void SAT_Skin::setBorderColor(uint32_t AIndex, SAT_Color AColor)
{
    SAT_Assert(AIndex < SAT_SKIN_NUM_STATES);
    MBorderColors[AIndex] = AColor;
}

void SAT_Skin::setBorderWidth(uint32_t AIndex, sat_coord_t AWidth)
{
    SAT_Assert(AIndex < SAT_SKIN_NUM_STATES);
    MBorderWidths[AIndex] = AWidth;
}

//------------------------------
//
//------------------------------

void SAT_Skin::setBackgroundColors(SAT_Color AColor, uint32_t AState, bool AUnique)
{
    SAT_Assert(AState < SAT_SKIN_NUM_STATES);
    for (uint32_t i=0; i<SAT_SKIN_NUM_STATES; i++)
    {
        if (check_state(i,AState,AUnique)) MBackgroundColors[i] = AColor;
    }
}

void SAT_Skin::setForegroundColors(SAT_Color AColor, uint32_t AState, bool AUnique)
{
    SAT_Assert(AState < SAT_SKIN_NUM_STATES);
    for (uint32_t i=0; i<SAT_SKIN_NUM_STATES; i++)
    {
        if (check_state(i,AState,AUnique)) MForegroundColors[i] = AColor;
    }
}

void SAT_Skin::setTextColors(SAT_Color AColor, uint32_t AState, bool AUnique)
{
    SAT_Assert(AState < SAT_SKIN_NUM_STATES);
    for (uint32_t i=0; i<SAT_SKIN_NUM_STATES; i++)
    {
        if (check_state(i,AState,AUnique)) MTextColors[i] = AColor;
    }
}

void SAT_Skin::setTextSizes(sat_coord_t ASize, uint32_t AState, bool AUnique)
{
    SAT_Assert(AState < SAT_SKIN_NUM_STATES);
    for (uint32_t i=0; i<SAT_SKIN_NUM_STATES; i++)
    {
        if (check_state(i,AState,AUnique)) MTextSizes[i] = ASize;
    }
}

void SAT_Skin::setBorderColors(SAT_Color AColor, uint32_t AState, bool AUnique)
{
    SAT_Assert(AState < SAT_SKIN_NUM_STATES);
    for (uint32_t i=0; i<SAT_SKIN_NUM_STATES; i++)
    {
        if (check_state(i,AState,AUnique)) MBorderColors[i] = AColor;
    }
}

void SAT_Skin::setBorderWidths(sat_coord_t AWidth, uint32_t AState, bool AUnique)
{
    SAT_Assert(AState < SAT_SKIN_NUM_STATES);
    for (uint32_t i=0; i<SAT_SKIN_NUM_STATES; i++)
    {
        if (check_state(i,AState,AUnique)) MBorderWidths[i] = AWidth;
    }
}

//------------------------------
//
//------------------------------

bool SAT_Skin::check_state(uint32_t i, uint32_t AState, bool AUnique)
{
    SAT_Assert(i < SAT_SKIN_NUM_STATES);
    SAT_Assert(AState < SAT_SKIN_NUM_STATES);
    if  ( (i==0) && ((AState==SAT_SKIN_NORMAL) || (AState==SAT_SKIN_ALL)) ) return true;
    if (AUnique) { if ((i & AState) == AState) return true; }
    else         { if (i & AState)             return true; }
    return false;
}