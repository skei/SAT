#pragma once

#include "base/sat_base.h"
#include "gui/window/sat_widget_window.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_Window
: public SAT_WidgetWindow
{
    public:
        SAT_Window(uint32_t AWidth, uint32_t AHeight, intptr_t AParent=0);
        virtual ~SAT_Window();
};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

SAT_Window::SAT_Window(uint32_t AWidth, uint32_t AHeight, intptr_t AParent)
: SAT_WidgetWindow(AWidth,AHeight,AParent)
{
}

SAT_Window::~SAT_Window()
{
}
