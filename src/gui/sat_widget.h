#pragma once

/*
    todo / consider
        - context menu
*/

#include "base/sat_base.h"
#include "gui/sat_gui_base.h"
#include "gui/widget/base/sat_value_widget.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_Widget
: public SAT_ValueWidget
{
    public:
        SAT_Widget(SAT_Rect ARect);
        virtual ~SAT_Widget();
};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

SAT_Widget::SAT_Widget(SAT_Rect ARect)
: SAT_ValueWidget(ARect)
{
}

SAT_Widget::~SAT_Widget()
{
}
