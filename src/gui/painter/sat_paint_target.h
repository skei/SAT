#pragma once

#include "base/sat_base.h"

#ifdef SAT_USE_X11
    #include "extern/gui/sat_x11.h"
#endif

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_PaintTarget
{
    public:
        virtual bool                            isBitmap()                  { return false; }
        virtual bool                            isSurface()                 { return false; }
        virtual bool                            isWindow()                  { return false; }
        #ifdef SAT_USE_NANOVG
            virtual void                        selectRenderBuffer()        { }
        #endif
        #ifdef SAT_USE_X11
            virtual xcb_drawable_t              getXcbDrawable()            { return 0; } // = 0;
        #endif
};
