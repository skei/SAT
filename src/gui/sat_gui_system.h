#pragma once

#include "base/sat_base.h"

#ifdef SAT_USE_X11
    #include "gui/system/x11/sat_x11.h"
#endif

// class SAT_Painter;
// class SAT_Renderer;
// class SAT_Surface;
// class SAT_Window;

// class SAT_BaseWidget;

//----------------------------------------------------------------------
//
// painter
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

//------------------------------

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

//------------------------------

class SAT_PainterOwner
{
    public:
        #ifdef SAT_USE_X11
            virtual xcb_connection_t*   getXcbConnection() = 0;
        #endif
};

//----------------------------------------------------------------------
//
// renderer
//
//----------------------------------------------------------------------

class SAT_RenderSource
{
};

//------------------------------

class SAT_RenderTarget
{
    public:
        #ifdef SAT_USE_X11
            virtual xcb_drawable_t getXcbDrawable() = 0;
        #endif
};

//------------------------------

class SAT_RendererOwner
{
    public:
        #ifdef SAT_USE_X11
            virtual Display* getX11Display() = 0;
        #endif
};

//----------------------------------------------------------------------
//
// surface
//
//----------------------------------------------------------------------

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
