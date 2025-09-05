#pragma once

#include "base/sat_base.h"
#include "gui/painter/sat_painter_owner.h"
#include "gui/painter/sat_paint_source.h"
#include "gui/painter/sat_paint_target.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_BasePainter
{
    public:
        SAT_BasePainter(SAT_PainterOwner* AOwner, SAT_PaintTarget* ATarget) {}
        virtual ~SAT_BasePainter() {}
    public:
        virtual void        beginPainting(uint32_t AWidth, uint32_t AHeight) = 0;
        virtual void        endPainting() = 0;
        virtual void        setClip(SAT_Rect ARect) = 0;
        virtual void        resetClip() = 0;
    public: // state
        virtual void        setDrawColor(SAT_Color AColor) = 0;
        virtual void        setFillColor(SAT_Color AColor) = 0;
        virtual void        setTextColor(SAT_Color AColor) = 0;
        virtual void        setLineWidth(sat_coord_t AWidth) = 0;
    public: // raster
        virtual void        drawLine(SAT_Point AFrom, SAT_Point ATo) = 0;
        virtual void        drawRect(SAT_Rect ARect) = 0;
        virtual void        drawArc(SAT_Point APos, sat_coord_t ARadius, sat_coord_t AAngle1, sat_coord_t AAngle2) = 0;
        virtual void        fillRect(SAT_Rect ARect) = 0;
        virtual void        fillArc(SAT_Point APos, sat_coord_t ARadius, sat_coord_t AAngle1, sat_coord_t AAngle2) = 0;
        virtual void        drawText(SAT_Point APos, const char* AText) = 0;
        virtual void        drawText(SAT_Rect ARect, const char* AText, uint32_t AAlignment) = 0;
        virtual sat_coord_t getTextBounds(const char* AText, sat_coord_t* ABounds) = 0;
        virtual sat_coord_t getTextWidth(const char* AText) = 0;
        virtual sat_coord_t getTextHeight(const char* AText) = 0;
        virtual void        drawImage(SAT_Point APos, SAT_PaintSource* ASource) = 0;
        virtual void        drawImage(SAT_Point APos, SAT_PaintSource* ASource, SAT_Rect ASrc) = 0;
        virtual void        drawImage(SAT_Rect ADst, SAT_PaintSource* ASource, SAT_Rect ASrc) = 0;
    public: // vector
        // TODO
};
