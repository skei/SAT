#pragma once

#include "base/sat.h"
#include "gui/renderer/sat_base_renderer.h"
#include "gui/renderer/sat_renderer_owner.h"
#include "gui/renderer/sat_render_source.h"
#include "gui/renderer/sat_render_target.h"
#include "extern/gui/sat_x11.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_X11Renderer
: public SAT_BaseRenderer
{
    public:
        SAT_X11Renderer(SAT_RendererOwner* AOwner, SAT_RenderTarget* ATarget);
        virtual ~SAT_X11Renderer();
    public: // BaseRenderer
        bool makeCurrent() final;
        bool resetCurrent() final;
        bool beginRendering() final;
        bool beginRendering(int32_t AWidth, int32_t AHeight) final;
        bool endRendering() final;
        bool setViewport(int32_t AXpos, int32_t AYpos, int32_t AWidth, int32_t AHeight) final;
        bool swapBuffers() final;
        bool enableVSync() final;
        bool disableVSync() final;
};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

SAT_X11Renderer::SAT_X11Renderer(SAT_RendererOwner* AOwner, SAT_RenderTarget* ATarget)
: SAT_BaseRenderer(AOwner,ATarget)
{
}

SAT_X11Renderer::~SAT_X11Renderer()
{
}

//------------------------------
// base renderer
//------------------------------

bool SAT_X11Renderer::makeCurrent()
{
    return true;
}

bool SAT_X11Renderer::resetCurrent()
{
    return true;
}

bool SAT_X11Renderer::beginRendering()
{
    return true;
}

bool SAT_X11Renderer::beginRendering(int32_t AWidth, int32_t AHeight)
{
    return true;
}

bool SAT_X11Renderer::endRendering()
{
    return true;
}

bool SAT_X11Renderer::setViewport(int32_t AXpos, int32_t AYpos, int32_t AWidth, int32_t AHeight)
{
    return true;
}

bool SAT_X11Renderer::swapBuffers()
{
    return true;
}

bool SAT_X11Renderer::enableVSync()
{
    return true;
}

bool SAT_X11Renderer::disableVSync()
{
    return true;
}
