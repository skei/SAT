#pragma once

/*
    TODO:
    should we put the NVGcontxt* in SAT_Global.GUI?
    nanovg surface needs the context, but this (nanovg_painter) might not be created yet
*/

#include "sat/sat_base.h"
#include "gui/sat_gui_base.h"
#include "gui/system/nanovg/sat_nanovg.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_NanoVgPainter
: public SAT_BasePainter
//, public SAT_SurfaceOwner
{
    public:
        SAT_NanoVgPainter(SAT_PainterOwner* AOwner, SAT_PaintTarget* ATarget) {}
        virtual ~SAT_NanoVgPainter() {}
    public:
        NVGcontext* getNanoVgContext() final;
/*  
    public:
        virtual void        beginPainting(uint32_t AWidth, uint32_t AHeight) = 0;
        virtual void        endPainting() = 0;
     // virtual void        setPaintTarget(SAT_PaintTarget* ATarget) = 0;
     // virtual void        resetPaintTarget(SAT_PaintTarget* ATarget) = 0;
        virtual void        setClip(int32_t AXpos, int32_t AYpos, uint32_t AWidth, uint32_t AHeight) = 0;
        virtual void        resetClip() = 0;
    public: // state
        virtual void        setDrawColor(SAT_Color AColor) = 0;
        virtual void        setFillColor(SAT_Color AColor) = 0;
        virtual void        setTextColor(SAT_Color AColor) = 0;
        virtual void        setLineWidth(sat_coord_t AWidth) = 0;
    public: // raster
        virtual void        drawLine(sat_coord_t AX1, sat_coord_t AY1, sat_coord_t AX2, sat_coord_t AY2) = 0;
        virtual void        drawRect(sat_coord_t AXpos, sat_coord_t AYpos, sat_coord_t AWidth, sat_coord_t AHeight) = 0;
        virtual void        drawArc(sat_coord_t AXpos, sat_coord_t AYpos, sat_coord_t ARadius, sat_coord_t AAngle1, sat_coord_t AAngle2) = 0;
        virtual void        fillRect(sat_coord_t AXpos, sat_coord_t AYpos, sat_coord_t AWidth, sat_coord_t AHeight) = 0;
        virtual void        fillArc(sat_coord_t AXposx, sat_coord_t AYpos, sat_coord_t ARadius, sat_coord_t AAngle1, sat_coord_t AAngle2) = 0;
        virtual void        drawText(sat_coord_t AXpos, sat_coord_t AYpos, const char* AText) = 0;
        virtual void        drawText(SAT_Rect ARect, const char* AText, uint32_t AAlignment) = 0;
        virtual sat_coord_t getTextBounds(const char* AText, sat_coord_t* ABounds) = 0;
        virtual sat_coord_t getTextWidth(const char* AText) = 0;
        virtual sat_coord_t getTextHeight(const char* AText) = 0;
        virtual void        drawImage(sat_coord_t AXpos, sat_coord_t AYpos, SAT_PaintSource* ASource) = 0;
        virtual void        drawImage(sat_coord_t AXpos, sat_coord_t AYpos, SAT_PaintSource* ASource, SAT_Rect ASrc) = 0;
        virtual void        drawImage(SAT_Rect ADst, SAT_PaintSource* ASource, SAT_Rect ASrc) = 0;
    public: // vector
        // TODO
*/
    private:
        NVGcontext*         MContext        = nullptr;

};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

/*
    NVGcreateFlags
        NVG_ANTIALIAS       // Flag indicating if geometry based anti-aliasing is used (may not be needed when using MSAA).
        NVG_STENCIL_STROKES // Flag indicating if strokes should be drawn using stencil buffer. The rendering will be a little
                            // slower, but path overlaps (i.e. self-intersecting or sharp turns) will be drawn just once.
        NVG_DEBUG           // Flag indicating that additional debug checks are done.
*/

// assumes opengl context already made current
// NVG_ANTIALIAS, NVG_STENCIL_STROKES, NVG_DEBUG

SAT_NanoVGPainter(SAT_PainterOwner* AOwner, SAT_PaintTarget* ATarget)
: SAT_BasePainter(AOwner,ATarget)
{
    //ARenderer->makeCurrent();
    #if defined SAT_GUI_WAYLAND
        MContext = nvgCreateGLES3(NVG_ANTIALIAS);
    #elif defined SAT_GUI_WIN32
        MContext = nvgCreateGL3(NVG_ANTIALIAS);
    #elif defined SAT_GUI_X11
        MContext = nvgCreateGL3(NVG_ANTIALIAS);
        //MContext = nvgCreateGLES3(NVG_ANTIALIAS);
    #endif
    SAT_Assert(MContext);
    //ARenderer->resetCurrent();
}

/*
    will nvgDelete also delete images and fonts?
*/

SAT_NanoVGPainter::~SAT_NanoVGPainter()
{
    #if defined(SAT_GUI_WAYLAND)
        nvgDeleteGLES3(MContext);
    #elif defined(SAT_GUI_WIN32)
        nvgDeleteGL3(MContext);
    #elif defined(SAT_GUI_X11)
        nvgDeleteGL3(MContext);
        //nvgDeleteGLES3(MContext);
    #endif
    // delete fonts?
    // (nvgCreateFontMem in constructor)
}

//------------------------------
// surface owner
//------------------------------

NVGcontext* SAT_NanoVGPainter::getNanoVgContext()
{
    return MContext;
}
