#pragma once

#include "base/sat_base.h"
#include "gui/surface/sat_surface_owner.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_BaseSurface
{
   public:
        SAT_BaseSurface(SAT_SurfaceOwner* AOwner, uint32_t AWidth, uint32_t AHeight, uint32_t ADepth=0) {}
        virtual ~SAT_BaseSurface() {}
    public:
     // virtual void fill(SAT_Color AColor) = 0;
     // virtual void uploadBitmap(SAT_Bitmap* ABitmap) = 0;
};
