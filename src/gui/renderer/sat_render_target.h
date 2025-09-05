#pragma once

#include "base/sat_base.h"

#ifdef SAT_USE_X11
    #include "extern/gui/sat_x11.h"
#endif

//----------------------------------------------------------------------
//
//
//
//---------------------------------------------------------------------

class SAT_RenderTarget
{
    public:
        #ifdef SAT_USE_X11
            virtual xcb_drawable_t getXcbDrawable() = 0;
        #endif
};
