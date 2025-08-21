#pragma once

#include "base/sat_base.h"
#include "gui/sat_gui_base.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

#if defined SAT_SURFACE_X11
    #include "gui/system/x11/sat_x11_surface.h"
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
        SAT_Surface(SAT_SurfaceOwner* AOwner, uint32_t AWidth, uint32_t AHeight, uint32_t ADepth);
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
