#pragma once

#include "base/sat_base.h"

class SAT_Widget;

//----------------------------------------------------------------------
//
// painter
//
//----------------------------------------------------------------------

class SAT_WindowListener
{
    public:
        virtual void do_widget_update(SAT_Widget* AWidget, uint32_t AIndex=0) {}
};
