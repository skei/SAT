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

class SAT_SurfaceOwner
{
    public:
        // TODO: move to SAT_Global.GUI
        #ifdef SAT_USE_NANOVG
            virtual NVGcontext*         getNanoVgContext() = 0;
        #endif
        #ifdef SAT_USE_X11
            virtual xcb_connection_t*   getXcbConnection() = 0;
            virtual xcb_drawable_t      getXcbDrawable() = 0;
        #endif
};

