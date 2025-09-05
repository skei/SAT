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

class SAT_RendererOwner
{
    public:
        #ifdef SAT_USE_X11
            virtual Display* getX11Display() = 0;
        #endif
};
