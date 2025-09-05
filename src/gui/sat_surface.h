#pragma once

#include "base/sat_base.h"
#include "gui/surface/sat_base_surface.h"
#include "gui/surface/sat_surface_owner.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

#if defined SAT_SURFACE_X11
    #include "gui/surface/sat_x11_surface.h"
    typedef SAT_X11Surface SAT_ImplementedSurface;
#elif defined SAT_SURFACE_WIN32
    #error NOT IMPLEMENTED YET
#else
    #error NO SURFACE DEFINED
#endif

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_Surface
: public SAT_ImplementedSurface
{
    public:
        SAT_Surface(SAT_SurfaceOwner* AOwner, uint32_t AWidth, uint32_t AHeight, uint32_t ADepth=0);
        virtual ~SAT_Surface();
};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

SAT_Surface::SAT_Surface(SAT_SurfaceOwner* AOwner, uint32_t AWidth, uint32_t AHeight, uint32_t ADepth)
: SAT_ImplementedSurface(AOwner,AWidth,AHeight,ADepth)
{
}

SAT_Surface::~SAT_Surface()
{
}
