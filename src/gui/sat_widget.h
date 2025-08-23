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

struct SAT_WidgetLayout
{
    uint32_t    flags           = SAT_WIDGET_LAYOUT_ANCHOR_TOP_LEFT;
    SAT_Rect    inner_border    = {};
    SAT_Rect    outer_border    = {};
    SAT_Point   spacing         = {};
};

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
    public:
        SAT_WidgetLayout    layout          = {};
        uint32_t            options         = 0;
        uint32_t            state           = SAT_WIDGET_STATE_ACTIVE | SAT_WIDGET_STATE_VISIBLE;
    protected:
        SAT_WidgetOwner*    MOwner          = nullptr;
        SAT_Widget*         MParent         = nullptr;
        SAT_WidgetArray     MChildren       = {};
        SAT_Rect            MRect           = {};
    private:
        SAT_Rect            MInitialRect    = {};
        SAT_Point           MScreenOffset   = {};
};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

SAT_Widget::SAT_Widget(SAT_Rect ARect)
{
    MInitialRect = ARect;
}

SAT_Widget::~SAT_Widget()
{
    #ifndef SAT_NO_AUTODELETE
        deleteChildren();
    #endif
}

//------------------------------
// hierarchy
//------------------------------

void SAT_Widget::appendChild(SAT_Widget* AWidget)
{
    AWidget->MParent = this;
    MChildren.append(AWidget);
}

void SAT_Widget::deleteChildren()
{
    for (uint32_t i=0; i<MChildren.size(); i++) delete MChildren[i];
}

//------------------------------
// widget
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

void SAT_Widget::on_widget_hide(SAT_WidgetOwner* AOwner)
{
}

void SAT_Widget::on_widget_paint(SAT_PaintContext* AContext)
{
}

void SAT_Widget::on_widget_realign()
{
}

// mouse
// keyboard
// timer
// ..

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
