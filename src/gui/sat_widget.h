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

class SAT_Widget;
typedef SAT_Array<SAT_Widget*> SAT_WidgetArray;

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_Widget
{
    public:
        SAT_Widget(SAT_Rect ARect);
        virtual ~SAT_Widget();
    public:
        virtual void appendChild(SAT_Widget* AWidget);
        virtual void deleteChildren();
    public:
        virtual void on_widget_show(SAT_WidgetOwner* AOwner);
        virtual void on_widget_hide(SAT_WidgetOwner* AOwner);
        virtual void on_widget_paint(SAT_PaintContext* AContext);
        virtual void on_widget_realign();
    public:
        virtual void do_widget_update(SAT_Widget* AWidget, uint32_t AMode=SAT_WIDGET_UPDATE_VALUE, uint32_t AIndex=0);
        virtual void do_widget_realign(SAT_Widget* AWidget, uint32_t AMode=SAT_WIDGET_REALIGN_PARENT, uint32_t AIndex=0);
        virtual void do_widget_redraw(SAT_Widget* AWidget, uint32_t AMode=SAT_WIDGET_REDRAW_SELF, uint32_t AIndex=0);
    private:
        SAT_WidgetOwner*    MOwner      = nullptr;
        SAT_Widget*         MParent     = nullptr;
        SAT_WidgetArray     MChildren   = {};
};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

SAT_Widget::SAT_Widget(SAT_Rect ARect)
{
}

SAT_Widget::~SAT_Widget()
{
}

//------------------------------
//
//------------------------------

void SAT_Widget::appendChild(SAT_Widget* AWidget)
{
}

void SAT_Widget::deleteChildren()
{
}

//------------------------------
//
//------------------------------

/*
    called when window containing the widget is opened, or shown..
    here the widget can for example register timers, ask the owner
    for its painter, so it can allocate buffers, look at font sizes
    to auto-size itself, etc..
*/

void SAT_Widget::on_widget_show(SAT_WidgetOwner* AOwner)
{
    MOwner = AOwner;
}

/*
    the 'inverse' of show..
*/

void SAT_Widget::on_widget_hide(SAT_WidgetOwner* AOwner)
{
}

void SAT_Widget::on_widget_paint(SAT_PaintContext* AContext)
{
}

void SAT_Widget::on_widget_realign()
{
}

//------------------------------
//
//------------------------------

void SAT_Widget::do_widget_update(SAT_Widget* AWidget, uint32_t AMode, uint32_t AIndex)
{
    if (MParent) MParent->do_widget_update(AWidget,AMode);
}

void SAT_Widget::do_widget_realign(SAT_Widget* AWidget, uint32_t AMode, uint32_t AIndex)
{
    if (MParent) MParent->do_widget_realign(AWidget,AMode);
}

void SAT_Widget::do_widget_redraw(SAT_Widget* AWidget, uint32_t AMode, uint32_t AIndex)
{
    if (MParent) MParent->do_widget_redraw(AWidget,AMode);
}
