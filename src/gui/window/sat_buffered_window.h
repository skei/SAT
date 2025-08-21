#pragma once

#include "base/sat_base.h"
#include "gui/sat_gui_base.h"
#include "gui/window/sat_paint_window.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_BufferedWindow
: public SAT_PaintWindow
{
    public:
        SAT_BufferedWindow(uint32_t AWidth, uint32_t AHeight, intptr_t AParent=0);
        virtual ~SAT_BufferedWindow();
    private:
        SAT_Surface*    MBuffer         = nullptr;
        uint32_t        MBufferWidth    = 0; // allocated width
        uint32_t        MBufferHeight   = 0; // allocated height
};

//----------------------------------------------------------------------
//
// implementation
//
//----------------------------------------------------------------------

SAT_BufferedWindow::SAT_BufferedWindow(uint32_t AWidth, uint32_t AHeight, intptr_t AParent)
: SAT_PaintWindow(AWidth, AHeight, AParent)
{
}

SAT_BufferedWindow::~SAT_BufferedWindow()
{
}
