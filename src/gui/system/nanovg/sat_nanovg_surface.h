#pragma once

#include "sat/sat_base.h"
#include "gui/sat_gui_base.h"
#include "gui/system/nanovg/sat_nanovg.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_NanoVgSurface
: public SAT_BaseSurface
, public SAT_PaintSource
, public SAT_PaintTarget
{
    public:
        SAT_NanovgSurface(SAT_SurfaceOwner* AOwner, uint32_t AWidth, uint32_t AHeight, uint32_t ADepth=0)
        virtual ~SAT_BaseSurface()
    public:
        virtual int32_t getImageFromRenderBuffer() final;
        virtual void    selectRenderBuffer() final;
    private:
        NVGcontext*         MContext        = nullptr;
        NVGLUframebuffer*   MFrameBuffer    = nullptr;
};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

/*
    NVGimageFlags
        NVG_IMAGE_GENERATE_MIPMAPS  Generate mipmaps during creation of the image.
        NVG_IMAGE_REPEATX           Repeat image in X direction.
        NVG_IMAGE_REPEATY           Repeat image in Y direction.
        NVG_IMAGE_FLIPY             Flips (inverses) image in Y direction when rendered.
        NVG_IMAGE_PREMULTIPLIED     Image data has premultiplied alpha.
        NVG_IMAGE_NEAREST           Image interpolation is Nearest instead Linear
    // additional flags on top of NVGimageFlags.
    NVGimageFlagsGL
        NVG_IMAGE_NODELETE          Do not delete GL texture handle.
*/

// owner = SAT_NanoVgPainter, not Sat_X11Window (like SAT_X11Surface)

SAT_NanoVgSurface::SAT_NanovgSurface(SAT_SurfaceOwner* AOwner, uint32_t AWidth, uint32_t AHeight, uint32_t ADepth=0)
{
    MContext = AOwner->getnanoVgContext();
    int flags = 0;
    MFrameBuffer = nvgluCreateFramebuffer(MContext,AWidth,AHeight,flags);
}

SAT_NanoVgSurface::~SAT_BaseSurface()
{
    nvgluBindFramebuffer(nullptr);
    nvgluDeleteFramebuffer(MFrameBuffer);
}

//------------------------------
// paint source/target
//------------------------------

/*
    get image from fbo/renderbuffer
    (use as fillImage)
*/

int32_t SAT_NanoVgSurface::getImageFromRenderBuffer()
{
    //SAT_Assert(MFrameBuffer);
    if (MFrameBuffer) return MFrameBuffer->image;
    return nullptr;
}

/*
    set fbo/renderbuffer as target for painting
*/

void SAT_NanoVgSurface::selectRenderBuffer()
{
    if (MFrameBuffer) nvgluBindFramebuffer(MFrameBuffer);
}

