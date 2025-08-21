#pragma once

/*
    - animation (via timer)
    - tweening
    - movable, sizable
    - layers (transparency)
    - buffered/cached
    - parent/owner (autosize text, alloc buffers, ..)
*/

#include "base/sat_base.h"
#include "gui/sat_gui_base.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_Widget
: public SAT_BaseWidget
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
: SAT_BaseWidget(ARect)
{
}

SAT_Widget::~SAT_Widget()
{
}
