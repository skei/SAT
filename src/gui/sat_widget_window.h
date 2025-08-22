#pragma once

#include "base/sat_base.h"
#include "gui/sat_gui_base.h"
#include "gui/sat_window.h"
#include "gui/sat_widget.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_WidgetWindow
: public SAT_Window
, public SAT_WidgetOwner
, public SAT_Widget
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
: SAT_Window(AWidth, AHeight, AParent)
, SAT_Widget(SAT_Rect(AWidth,AHeight))
{
}

SAT_WidgetWindow::~SAT_WidgetWindow()
{
}
