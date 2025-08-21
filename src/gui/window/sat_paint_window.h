#pragma once

#include "base/sat_base.h"
#include "gui/sat_gui_base.h"
#include "gui/sat_window.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_PaintWindow
: public SAT_Window
{
    public:
        SAT_PaintWindow(uint32_t AWidth, uint32_t AHeight, intptr_t AParent=0);
        virtual ~SAT_PaintWindow();
    private:
        SAT_Renderer*   MRenderer = nullptr;
        SAT_Painter*    MPainter = nullptr;
};

//----------------------------------------------------------------------
//
// implementation
//
//----------------------------------------------------------------------

SAT_PaintWindow::SAT_PaintWindow(uint32_t AWidth, uint32_t AHeight, intptr_t AParent)
: SAT_Window(AWidth, AHeight, AParent)
{
}

SAT_PaintWindow::~SAT_PaintWindow()
{
}
