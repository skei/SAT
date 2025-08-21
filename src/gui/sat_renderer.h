#pragma once

#include "base/sat_base.h"
#include "gui/sat_gui_base.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

#if defined SAT_RENDERER_X11
    #include "gui/system/x11/sat_x11_renderer.h"
    typedef SAT_X11Renderer SAT_ImplementedRenderer;
#elif defined SAT_RENDERER_WIN32
    #error NOT IMPLEMENTED YET
#else
    #error NO RENDERER DEFINED
#endif

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_Renderer
: public SAT_ImplementedRenderer
{
    public:
        SAT_Renderer(SAT_RendererOwner* AOwner, SAT_RenderTarget* ATarget);
        virtual ~SAT_Renderer();
};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

SAT_Renderer::SAT_Renderer(SAT_RendererOwner* AOwner, SAT_RenderTarget* ATarget)
: SAT_ImplementedRenderer(AOwner,ATarget)
{
}

SAT_Renderer::~SAT_Renderer()
{
}
