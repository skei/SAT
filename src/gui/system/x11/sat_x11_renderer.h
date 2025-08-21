#pragma once

#include "base/sat.h"
#include "gui/sat_gui_base.h"
#include "gui/system/x11/sat_x11.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_X11Renderer
: public SAT_BaseRenderer {

    public:

        SAT_X11Renderer(SAT_RendererOwner* AOwner, SAT_RenderTarget* ATarget);
        virtual ~SAT_X11Renderer();

    public: // BaseRenderer

        void setCurrent(bool ACurrent=true) override;
        void setViewport(SAT_Rect AViewport) override;
        void swapBuffers() override;
        void setVSync(bool ASync) override;
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

//----------

void SAT_X11Renderer::setCurrent(bool ACurrent)
{
}

void SAT_X11Renderer::setViewport(SAT_Rect AViewport)
{
}

void SAT_X11Renderer::swapBuffers()
{
}

void SAT_X11Renderer::setVSync(bool ASync)
{
}
