#pragma once

#include "base/sat_base.h"
#include "gui/sat_gui_base.h"
#include "gui/window/sat_buffered_window.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_WidgetWindow
: public SAT_BufferedWindow
{
    public:
        SAT_WidgetWindow(uint32_t AWidth, uint32_t AHeight, intptr_t AParent=0);
        virtual ~SAT_WidgetWindow();
    private:
        SAT_Widget* MRootWidget = nullptr;
};

//----------------------------------------------------------------------
//
// implementation
//
//----------------------------------------------------------------------

SAT_WidgetWindow::SAT_WidgetWindow(uint32_t AWidth, uint32_t AHeight, intptr_t AParent)
: SAT_BufferedWindow(AWidth, AHeight, AParent)
{
}

SAT_WidgetWindow::~SAT_WidgetWindow()
{
}
