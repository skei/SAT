#pragma once

#include "base/sat.h"
#include "gui/surface/sat_base_surface.h"
#include "gui/painter/sat_paint_source.h"
#include "gui/painter/sat_paint_target.h"
#include "gui/surface/sat_surface_owner.h"
#include "extern/gui/sat_x11.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_X11Surface
: public SAT_BaseSurface
, public SAT_PaintSource
, public SAT_PaintTarget
{
    public:
    
        SAT_X11Surface(SAT_SurfaceOwner* AOwner, uint32_t AWidth, uint32_t AHeight, uint32_t ADepth=0);
        virtual ~SAT_X11Surface();

    public:

        bool                isSurface() final;
        uint32_t            getWidth() final;
        uint32_t            getHeight() final;
        uint32_t            getDepth() final;
        xcb_drawable_t      getXcbDrawable() final;

    private: // X11

        xcb_connection_t*   MConnection = nullptr;
        xcb_pixmap_t        MPixmap     = XCB_NONE;

        #ifdef SAT_X11_USE_XRENDER
            xcb_render_picture_t  MPicture = 0;
        #endif


    private: // state

        uint32_t            MWidth      = 0;
        uint32_t            MHeight     = 0;
        uint32_t            MDepth      = 0;

};

//----------------------------------------------------------------------
//
// implementation
//
//----------------------------------------------------------------------

/*
    xcb_create_pixmap:
    Creates a pixmap. The pixmap can only be used on the same screen as drawable
    is on and only with drawables of the same depth.
*/

SAT_X11Surface::SAT_X11Surface(SAT_SurfaceOwner* AOwner, uint32_t AWidth, uint32_t AHeight, uint32_t ADepth)
: SAT_BaseSurface(AOwner,AWidth,AHeight,ADepth)
{
    MWidth = AWidth;
    MHeight = AHeight;
    if (ADepth == 0) MDepth = SAT.GUI->getScreenDepth();
    else MDepth = ADepth;
    MConnection = AOwner->getXcbConnection();
    MPixmap = xcb_generate_id(MConnection);
    xcb_create_pixmap(
        MConnection,
        MDepth,
        MPixmap,
        AOwner->getXcbDrawable(), // Drawable to get the screen from.
        MWidth,
        MHeight
    );
    #ifdef SAT_X11_USE_XRENDER
        const xcb_render_query_pict_formats_reply_t *fmt_rep = xcb_render_util_query_formats(MConnection);
        xcb_render_pictforminfo_t *fmt;
        if (MDepth == 24) fmt = xcb_render_util_find_standard_format( fmt_rep, XCB_PICT_STANDARD_RGB_24 );
        else fmt = xcb_render_util_find_standard_format( fmt_rep, XCB_PICT_STANDARD_ARGB_32 );
        uint32_t pict_mask = XCB_RENDER_CP_POLY_EDGE | XCB_RENDER_CP_POLY_MODE;
        uint32_t pict_mask_values[] = { XCB_RENDER_POLY_EDGE_SMOOTH, XCB_RENDER_POLY_MODE_IMPRECISE };
        MPicture = xcb_generate_id(MConnection);
        xcb_render_create_picture(
            MConnection,
            MPicture,
            MPixmap,
            fmt->id,
            pict_mask,
            pict_mask_values
        );
        SAT_Assert(MPicture);
    #endif
    xcb_flush(MConnection);
}

SAT_X11Surface::~SAT_X11Surface()
{
    #ifdef SAT_X11_USE_XRENDER
        xcb_render_free_picture(MConnection,MPicture);
    #endif
    xcb_free_pixmap(MConnection,MPixmap);
}

//------------------------------
// paint source/target
//------------------------------

bool            SAT_X11Surface::isSurface()         { return true; }
uint32_t        SAT_X11Surface::getWidth()          { return MWidth; }
uint32_t        SAT_X11Surface::getHeight()         { return MHeight; }
uint32_t        SAT_X11Surface::getDepth()          { return MDepth; }
xcb_drawable_t  SAT_X11Surface::getXcbDrawable()    { return MPixmap; }

//------------------------------
//
//------------------------------
