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

//#include "gui/sat_tween_manager.h"
class SAT_TweenChain;

class SAT_Widget;
typedef SAT_Array<SAT_Widget*> SAT_WidgetArray;

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

struct SAT_WidgetLayout
{
    uint32_t    anchor;
    uint32_t    stretch;
    uint32_t    fill;
    uint32_t    relative;
    uint32_t    stack;
    SAT_Rect    inner_border;
    SAT_Rect    outer_border;
    SAT_Point   spacing;
    double      scale;
};

struct SAT_WidgetOptions
{
    bool auto_capture;
    bool auto_clip;
    bool auto_cursor_shape;
    bool auto_cursor_lock;
    bool auto_cursor_hide;
    bool auto_hint;
    bool auto_scale;
    bool want_hover_events;
};

struct SAT_WidgetState
{
    bool visible;
    bool active;
    bool disabled;
    bool opaque;
    bool interactive;
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
        virtual SAT_Rect    getRect();
        virtual void*       getParameter();
    public:
        virtual void        appendChild(SAT_Widget* AWidget);
        virtual void        removeChild(SAT_Widget* AWidget);
        virtual void        deleteChildren();
        virtual void        paintChildren(SAT_PaintContext* AContext);
        virtual void        realignChildren();
        virtual SAT_Widget* findHoverWidget();
        virtual SAT_Widget* findOpaqueParent();
        virtual SAT_Rect    findRecursiveClipRect();
        virtual bool        isRecursivelyActive();
        virtual bool        isRecursivelyDisabled();
        virtual bool        isRecursivelyOpaque();
        virtual bool        isRecursivelyVisible();
    public:
        virtual void        on_widget_show(SAT_WidgetOwner* AOwner);
        virtual void        on_widget_hide(SAT_WidgetOwner* AOwner);
        virtual void        on_widget_paint(SAT_PaintContext* AContext, uint32_t AMode=SAT_WIDGET_REDRAW_SELF, uint32_t AIndex=0);
        virtual void        on_widget_realign(uint32_t AMode=SAT_WIDGET_REALIGN_PARENT, uint32_t AIndex=0);
        virtual void        on_widget_timer(uint32_t ATimerId, double ADelta);
        virtual void        on_widget_tween(uint32_t AId, uint32_t AType, uint32_t ANumValues, double* AValues);
        virtual void        on_widget_hint(uint32_t AType, const char* AHint);
        virtual void        on_widget_mouse_click(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATime);
        virtual void        on_widget_mouse_dbl_click(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATime);
        virtual void        on_widget_mouse_release(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATime);
        virtual void        on_widget_mouse_move(int32_t AXpos, int32_t AYpos, uint32_t AState, uint32_t ATime);
        virtual void        on_widget_key_press(uint32_t AKey, uint32_t AChar, uint32_t AState, uint32_t ATime);
        virtual void        on_widget_key_release(uint32_t AKey, uint32_t AChar, uint32_t AState, uint32_t ATime);
        virtual void        on_widget_mouse_enter(SAT_Widget* AFrom, int32_t AXpos, int32_t AYpos, uint32_t ATime);
        virtual void        on_widget_mouse_leave(SAT_Widget* ATo, int32_t AXpos, int32_t AYpos, uint32_t ATime);


        // virtual bool        on_widget_drag_accept(SAT_Widget* ASrc, int32_t ADragId);
        // virtual void        on_widget_drag_drop(SAT_Widget* AFrom, int32_t ADragId, void* ADragData);
        // virtual void        on_widget_drag_accepted(SAT_Widget* ADst, int32_t ADragId);

    public:
        virtual void        do_widget_update(SAT_Widget* AWidget, uint32_t AMode=SAT_WIDGET_UPDATE_VALUE, uint32_t AIndex=0);
        virtual void        do_widget_realign(SAT_Widget* AWidget, uint32_t AMode=SAT_WIDGET_REALIGN_PARENT, uint32_t AIndex=0);
        virtual void        do_widget_redraw(SAT_Widget* AWidget, uint32_t AMode=SAT_WIDGET_REDRAW_SELF, uint32_t AIndex=0);
        virtual void        do_widget_tween(SAT_Widget* AWidget, SAT_TweenChain* AChain);
        virtual void        do_widget_notify(SAT_Widget* AWidget, uint32_t AType=0, int32_t AValue=0);
        virtual void        do_widget_hint(SAT_Widget* AWidget, uint32_t AType, const char* AHint);
        virtual void        do_widget_modal(SAT_Widget* AWidget);
        virtual void        do_widget_cursor(SAT_Widget* AWidget, uint32_t ACursor);
        virtual void        do_widget_capture_mouse(SAT_Widget* AWidget);
        virtual void        do_widget_capture_keyboard(SAT_Widget* AWidget);

        // virtual void        do_widget_drag_start(SAT_Widget* AWidget, int32_t ADragId, void* ADragData);

    public: // options
        SAT_WidgetLayout Layout =
        {
            .anchor             = SAT_WIDGET_LAYOUT_ANCHOR_TOP_LEFT,
            .stretch            = SAT_WIDGET_LAYOUT_STRETCH_NONE,
            .fill               = SAT_WIDGET_LAYOUT_FILL_NONE,
            .relative           = SAT_WIDGET_LAYOUT_RELATIVE_LAYOUT,
            .stack              = SAT_WIDGET_LAYOUT_STACK_NONE,
            .inner_border       = {0,0,0,0},
            .outer_border       = {0,0,0,0},
            .spacing            = {0,0},
            .scale              = 1.0
        };
        SAT_WidgetOptions Options =
        {
            .auto_capture       = true,
            .auto_clip          = true,
            .auto_cursor_shape  = true,
            .auto_cursor_lock   = true,
            .auto_cursor_hide   = true,
            .auto_hint          = false,
            .auto_scale         = false,
            .want_hover_events  = false
        };
        SAT_WidgetState State =
        {
            .visible            = true,
            .active             = true,
            .disabled           = false,
            .opaque             = false,
            .interactive        = false

        };
    protected: // hierarvhy
        SAT_WidgetOwner*    MOwner              = nullptr;
        SAT_Widget*         MParent             = nullptr;
        SAT_WidgetArray     MChildren           = {};
    private: // visual
        SAT_Rect            MRect               = {};
        SAT_Rect            MInitialRect        = {};
        SAT_Point           MScreenOffset       = {};
        SAT_Rect            MContentRect        = {};
    private: // state
        void*               MParameter          = nullptr;

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

SAT_Rect    SAT_Widget::getRect()       { return MRect; }
void*       SAT_Widget::getParameter()  { return MParameter; }

//------------------------------
// hierarchy
//------------------------------

void SAT_Widget::appendChild(SAT_Widget* AWidget)
{
    AWidget->MParent = this;
    MChildren.append(AWidget);
}

void SAT_Widget::removeChild(SAT_Widget* AWidget)
{
    AWidget->MParent = nullptr;
    MChildren.remove(AWidget);
}

void SAT_Widget::deleteChildren()
{
    for (uint32_t i=0; i<MChildren.size(); i++) delete MChildren[i];
}

void SAT_Widget::paintChildren(SAT_PaintContext* AContext)
{
}

void SAT_Widget::realignChildren()
{
}

SAT_Widget* SAT_Widget::findHoverWidget()
{
    return nullptr;
}

SAT_Widget* SAT_Widget::findOpaqueParent()
{
    return nullptr;
}

SAT_Rect SAT_Widget::findRecursiveClipRect()
{
    return SAT_Rect();;
}

bool SAT_Widget::isRecursivelyActive()
{
    return true;
}

bool SAT_Widget::isRecursivelyDisabled()
{
    return false;
}

bool SAT_Widget::isRecursivelyOpaque()
{
    return false;
}

bool SAT_Widget::isRecursivelyVisible()
{
    return true;
}

//------------------------------
// on widget
//------------------------------

void SAT_Widget::on_widget_show(SAT_WidgetOwner* AOwner)
{
    MOwner = AOwner;
    for (uint32_t i=0; i<MChildren.size(); i++)
    {
        MChildren[i]->on_widget_show(AOwner);
    }
}

void SAT_Widget::on_widget_hide(SAT_WidgetOwner* AOwner)
{
    MOwner = nullptr;
    for (uint32_t i=0; i<MChildren.size(); i++)
    {
        MChildren[i]->on_widget_hide(AOwner);
    }
}

void SAT_Widget::on_widget_paint(SAT_PaintContext* AContext, uint32_t AMode, uint32_t AIndex)
{
    paintChildren(AContext);
}

void SAT_Widget::on_widget_realign(uint32_t AMode, uint32_t AIndex)
{
    realignChildren();
}

void SAT_Widget::on_widget_timer(uint32_t ATimerId, double ADelta)
{
}

void SAT_Widget::on_widget_tween(uint32_t AId, uint32_t AType, uint32_t ANumValues, double* AValues)
{
}

void SAT_Widget::on_widget_hint(uint32_t AType, const char* AHint)
{
}

void SAT_Widget::on_widget_mouse_click(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATime)
{
}

void SAT_Widget::on_widget_mouse_dbl_click(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATime)
{
}

void SAT_Widget::on_widget_mouse_release(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATime)
{
}

void SAT_Widget::on_widget_mouse_move(int32_t AXpos, int32_t AYpos, uint32_t AState, uint32_t ATime)
{
}

void SAT_Widget::on_widget_key_press(uint32_t AKey, uint32_t AChar, uint32_t AState, uint32_t ATime)
{
}

void SAT_Widget::on_widget_key_release(uint32_t AKey, uint32_t AChar, uint32_t AState, uint32_t ATime)
{
}

void SAT_Widget::on_widget_mouse_enter(SAT_Widget* AFrom, int32_t AXpos, int32_t AYpos, uint32_t ATime)
{
}

void SAT_Widget::on_widget_mouse_leave(SAT_Widget* ATo, int32_t AXpos, int32_t AYpos, uint32_t ATime)
{
}

//------------------------------
// do widget
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

void SAT_Widget::do_widget_tween(SAT_Widget* AWidget, SAT_TweenChain* AChain)
{
    if (MParent) MParent->do_widget_tween(AWidget,AChain);
}

void SAT_Widget::do_widget_notify(SAT_Widget* AWidget, uint32_t AType, int32_t AValue)
{
    if (MParent) MParent->do_widget_notify(AWidget,AType,AValue);
}

void SAT_Widget::do_widget_hint(SAT_Widget* AWidget, uint32_t AType, const char* AHint)
{
    if (MParent) MParent->do_widget_hint(AWidget,AType,AHint);
}

void SAT_Widget::do_widget_modal(SAT_Widget* AWidget)
{
    if (MParent) MParent->do_widget_modal(AWidget);
}

void SAT_Widget::do_widget_cursor(SAT_Widget* AWidget, uint32_t ACursor)
{
    if (MParent) MParent->do_widget_cursor(AWidget,ACursor);
}

void SAT_Widget::do_widget_capture_mouse(SAT_Widget* AWidget)
{
    if (MParent) MParent->do_widget_capture_mouse(AWidget);
}

void SAT_Widget::do_widget_capture_keyboard(SAT_Widget* AWidget)
{
    if (MParent) MParent->do_widget_capture_keyboard(AWidget);
}

//------------------------------
//
//------------------------------

