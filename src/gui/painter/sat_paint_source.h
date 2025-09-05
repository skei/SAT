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

class SAT_PaintSource
{
    public:
        virtual bool                            isBitmap()                  { return false; }
        virtual bool                            isSurface()                 { return false; }
        virtual uint32_t                        getWidth()                  { return 0; }
        virtual uint32_t                        getHeight()                 { return 0; }
        virtual uint32_t                        getDepth()                  { return 0; }
        virtual uint32_t                        getBufferSize()             { return 0; }
        virtual uint32_t*                       getBuffer()                 { return 0; }
        #ifdef SAT_USE_NANOVG
            virtual int32_t                     getImageFromRenderBuffer()  { return 0; }
        #endif
        #ifdef SAT_USE_X11
            virtual xcb_drawable_t              getXcbDrawable()            { return 0; } // = 0;
            #ifdef SAT_USE_X11_XRENDER
                virtual xcb_render_picture_t    getXcbPicture()             { return 0; }// = 0;
            #endif
        #endif
};
