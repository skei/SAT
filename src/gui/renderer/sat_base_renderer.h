#pragma once

#include "base/sat_base.h"
#include "gui/renderer/sat_renderer_owner.h"
#include "gui/renderer/sat_render_source.h"
#include "gui/renderer/sat_render_target.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_BaseRenderer
{
    public:
        SAT_BaseRenderer(SAT_RendererOwner* AOwner, SAT_RenderTarget* ATarget) {}
        virtual ~SAT_BaseRenderer() {}
    public:
        virtual bool makeCurrent() = 0;
        virtual bool resetCurrent() = 0;
        virtual bool beginRendering() = 0;
        virtual bool beginRendering(int32_t AWidth, int32_t AHeight) = 0;
        virtual bool endRendering() = 0;
        virtual bool setViewport(int32_t AXpos, int32_t AYpos, int32_t AWidth, int32_t AHeight) = 0;
        virtual bool swapBuffers() = 0;
        virtual bool enableVSync() = 0;
        virtual bool disableVSync() = 0;
};
