#pragma once

/*
    defines what a widget IS..
    how a (widget-) window can handle/manage widgets..
    and how they interact
*/

//----------------------------------------------------------------------

#include "base/sat_base.h"
#include "gui/sat_gui_base.h"

class SAT_TweenChain;
class SAT_Parameter;
class SAT_BaseWidget;
typedef SAT_Array<SAT_BaseWidget*> SAT_BaseWidgetArray;

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

struct SAT_WidgetLayout
{
    uint32_t    anchor          = SAT_WIDGET_LAYOUT_ANCHOR_TOP_LEFT;    // snap widget pos to parent
    uint32_t    stretch         = SAT_WIDGET_LAYOUT_STRETCH_NONE;       // stretch widget sides (after snapping)
    uint32_t    fill            = SAT_WIDGET_LAYOUT_FILL_NONE;          // crop widget rect out of 'available' layout rect (for following widgets)
    uint32_t    relative        = SAT_WIDGET_LAYOUT_RELATIVE_NONE;      // pos/size relative to parent, layout (percentages)
    uint32_t    stack           = SAT_WIDGET_LAYOUT_STACK_NONE;         // horiz/vert stacked (icon view)
    SAT_Rect    inner_border    = {0,0,0,0};                            // border around child widgets
    SAT_Rect    outer_border    = {0,0,0,0};                            // border around widget itself (in parent widget)
    SAT_Point   spacing         = {0,0};                                // space between widgets
    SAT_Point   minSize         = {-1,-1};                              // minimum widget size (-1 for none)
    SAT_Point   maxSize         = {-1,-1};                              // maximum widget size (-1 for none)
 // double      scale           = 1.0;                                  // scaling of child widgets
};

struct SAT_WidgetOptions
{
    bool auto_capture           = true;     // auto capture mouse when clicking
    bool auto_clip              = true;     // clip child widgets
    bool auto_cursor_shape      = true;     // set cursor shape when hovering over widget
    bool auto_cursor_lock       = true;     // lock cursor in place (when dragging)
    bool auto_cursor_hide       = true;     // auto hide cursor when dragging
    bool auto_hint              = false;    // auto send hint when hovering
    bool auto_scale             = false;    // scale/zoom widget (or content) relative to rect/size (text/font)
    bool want_hover_events      = false;    // want hover, move, etc mouse events even when not captured
    bool realign_if_invisible   = false;    // realign (child) widgets, even if not visible (menus, etc)
};

struct SAT_WidgetState
{
    bool active         = true;     // handles events
    bool visible        = true;     // drawing/alignment
    bool interactive    = false;    // is currently interacting (mouse/keys)
    bool enabled        = false;    // if false, draw 'disabled'state (greyed out)
    bool opaque         = false;    // set to true if widget fills it's entire rect
};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_BaseWidget
{
    public:

        SAT_BaseWidget();
        virtual ~SAT_BaseWidget();

    public: // base

        virtual uint32_t            getWidgetType();
        virtual const char*         getWidgetTypeName();
        virtual const char*         getName();
        virtual void                setName(const char* AName);

    public: // hierarchy

        virtual SAT_WidgetOwner*    getOwner()                                                          { return nullptr; }
        virtual SAT_BaseWidget*     getParent()                                                         { return nullptr; }
        virtual uint32_t            getNumChildren()                                                    { return 0; }
        virtual SAT_BaseWidget*     getChild(uint32_t AIndex)                                           { return nullptr; }
        virtual uint32_t            getIndex()                                                          { return 0; }
        virtual void                setOwner(SAT_WidgetOwner* AOwner)                                   { }
        virtual void                setParent(SAT_BaseWidget* AParent)                                  { }
        virtual void                setIndex(uint32_t AIndex)                                           { }
        virtual SAT_BaseWidget*     appendChild(SAT_BaseWidget* AWidget)                                { return AWidget; }
        virtual void                removeChild(SAT_BaseWidget* AWidget)                                { }
        virtual void                deleteChildren()                                                    { }
        virtual SAT_BaseWidget*     findWidget(const char* AName, bool ARecursive=true)                 { return nullptr; }

    public: // visual

        virtual SAT_Rect            getRect()                                                           { return SAT_Rect(0); }
        virtual bool                isVisible()                                                         { return false; }
        virtual bool                isOpaque()                                                          { return false; }
        virtual void                setRect(SAT_Rect ARect)                                             { }
        virtual void                setVisible(bool AState=true, bool ARecursive=true)                  { }
        virtual void                setOpaque(bool AState=true, bool ARecursive=true)                   { }
        virtual SAT_BaseWidget*     findWidgetAt(int32_t AXpos, int32_t AYpos, bool ARecursive=true)    { return nullptr; }
        virtual SAT_Rect            findParentClipRect(SAT_Rect ARect)                                  { return SAT_Rect(0); }
        virtual SAT_BaseWidget*     findOpaqueParent(SAT_Rect ARect)                                    { return nullptr; }
        virtual bool                isRecursivelyVisible()                                              { return false; }
        virtual bool                isRecursivelyOpaque()                                               { return false; }

    public: // layout

        virtual SAT_Rect            getBaseRect()                                                       { return SAT_Rect(0); }
        virtual SAT_Rect            getInitialRect()                                                    { return SAT_Rect(0); }
        virtual SAT_Rect            getContentRect()                                                    { return SAT_Rect(0); }

    public: // interactive

        virtual bool                isActive()                                                          { return false; }
        virtual bool                isInteractive()                                                     { return false; }
        virtual bool                isEnabled()                                                         { return false; }
        virtual void                setActive(bool AState=true, bool ARecursive=true)                   { }
        virtual void                setInteractive(bool AState=true, bool ARecursive=true)              { }
        virtual void                setEnabled(bool AState=true, bool ARecursive=true)                  { }
        virtual bool                isRecursivelyActive()                                               { return false; }
        virtual bool                isRecursivelyEnabled()                                              { return false; }

    public: // value

        virtual sat_param_t         getValue(uint32_t AIndex=0)                                         { return 0.0; }
        virtual SAT_Parameter*      getParameter(uint32_t AIndex=0)                                     { return nullptr; }
        virtual void                setValue(sat_param_t AValue, uint32_t AIndex=0)                     { }
        virtual void                setParameter(SAT_Parameter* AParameter, uint32_t AIndex=0)          { }

    public: // on_

        virtual void                on_widget_show(SAT_WidgetOwner* AOwner)                                                                     {}
        virtual void                on_widget_hide(SAT_WidgetOwner* AOwner)                                                                     {}
        virtual void                on_widget_paint(SAT_PaintContext* AContext, uint32_t AMode=SAT_WIDGET_PAINT_NORMAL, uint32_t AIndex=0)      {}
        virtual void                on_widget_pre_paint(SAT_PaintContext* AContext, uint32_t AMode=SAT_WIDGET_PAINT_NORMAL, uint32_t AIndex=0)  {}
        virtual void                on_widget_post_paint(SAT_PaintContext* AContext, uint32_t AMode=SAT_WIDGET_PAINT_NORMAL, uint32_t AIndex=0) {}
        virtual void                on_widget_realign(uint32_t AMode=SAT_WIDGET_REALIGN_CHILDREN, uint32_t AIndex=0)                            {}
        virtual SAT_Rect            on_widget_pre_align(SAT_Rect ARect, uint32_t AMode=SAT_WIDGET_REALIGN_CHILDREN, uint32_t AIndex=0)          { return SAT_Rect(0); }
        virtual SAT_Rect            on_widget_post_align(SAT_Rect ARect, uint32_t AMode=SAT_WIDGET_REALIGN_CHILDREN, uint32_t AIndex=0)         { return SAT_Rect(0); }
        virtual void                on_widget_timer(uint32_t ATimerId, double ADelta)                                                           {}
        virtual void                on_widget_tween(uint32_t AId, uint32_t AType, uint32_t ANumValues, double* AValues)                         {}
        virtual void                on_widget_hint(uint32_t AType, const char* AHint)                                                           {}
        virtual void                on_widget_mouse_click(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATime)      {}
        virtual void                on_widget_mouse_dbl_click(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATime)  {}
        virtual void                on_widget_mouse_release(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATime)    {}
        virtual void                on_widget_mouse_move(int32_t AXpos, int32_t AYpos, uint32_t AState, uint32_t ATime)                         {}
        virtual void                on_widget_key_press(uint32_t AKey, uint32_t AChar, uint32_t AState, uint32_t ATime)                         {}
        virtual void                on_widget_key_release(uint32_t AKey, uint32_t AChar, uint32_t AState, uint32_t ATime)                       {}
        virtual void                on_widget_mouse_enter(SAT_BaseWidget* AFrom, int32_t AXpos, int32_t AYpos, uint32_t ATime)                  {}
        virtual void                on_widget_mouse_leave(SAT_BaseWidget* ATo, int32_t AXpos, int32_t AYpos, uint32_t ATime)                    {}

    public: // do_

        virtual void                do_widget_update(SAT_BaseWidget* AWidget, uint32_t AMode=SAT_WIDGET_UPDATE_VALUE, uint32_t AIndex=0);
        virtual void                do_widget_realign(SAT_BaseWidget* AWidget, uint32_t AMode=SAT_WIDGET_REALIGN_PARENT, uint32_t AIndex=0);
        virtual void                do_widget_redraw(SAT_BaseWidget* AWidget, uint32_t AMode=SAT_WIDGET_REDRAW_SELF, uint32_t AIndex=0);
        virtual void                do_widget_tween(SAT_BaseWidget* AWidget, SAT_TweenChain* AChain);
        virtual void                do_widget_notify(SAT_BaseWidget* AWidget, uint32_t AType=SAT_WIDGET_NOTIFY_NONE, int32_t AValue=0);
        virtual void                do_widget_hint(SAT_BaseWidget* AWidget, uint32_t AType, const char* AHint);
        virtual void                do_widget_modal(SAT_BaseWidget* AWidget);
        virtual void                do_widget_cursor(SAT_BaseWidget* AWidget, uint32_t ACursor);
        virtual void                do_widget_capture_mouse(SAT_BaseWidget* AWidget);
        virtual void                do_widget_capture_keyboard(SAT_BaseWidget* AWidget);

    public: // options

        SAT_WidgetLayout            Layout          = {};
        SAT_WidgetOptions           Options         = {};
        SAT_WidgetState             State           = {};

    protected: // base
    
        uint32_t                    MWidgetType     = 0;
        const char*                 MWidgetTypeName = "SAT_BaseWidget";
        const char*                 MName           = "";
};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

SAT_BaseWidget::SAT_BaseWidget()
{
}

SAT_BaseWidget::~SAT_BaseWidget()
{
}

//------------------------------
// base
//------------------------------

uint32_t SAT_BaseWidget::getWidgetType()
{
    return MWidgetType;
}

const char* SAT_BaseWidget::getWidgetTypeName()
{
    return MWidgetTypeName;
}

const char* SAT_BaseWidget::getName()
{
    return MName;
}

void SAT_BaseWidget::setName(const char* AName)
{
    MName = AName;
}

//------------------------------
// do_
//------------------------------

void SAT_BaseWidget::do_widget_update(SAT_BaseWidget* AWidget, uint32_t AMode, uint32_t AIndex)
{
    SAT_BaseWidget* parent = getParent();
    if (parent) parent->do_widget_update(AWidget,AMode);
}

void SAT_BaseWidget::do_widget_realign(SAT_BaseWidget* AWidget, uint32_t AMode, uint32_t AIndex)
{
    SAT_BaseWidget* parent = getParent();
    if (parent) parent->do_widget_realign(AWidget,AMode);
}

void SAT_BaseWidget::do_widget_redraw(SAT_BaseWidget* AWidget, uint32_t AMode, uint32_t AIndex)
{
    SAT_BaseWidget* parent = getParent();
    if (parent) parent->do_widget_redraw(AWidget,AMode);
}

void SAT_BaseWidget::do_widget_tween(SAT_BaseWidget* AWidget, SAT_TweenChain* AChain)
{
    SAT_BaseWidget* parent = getParent();
    if (parent) parent->do_widget_tween(AWidget,AChain);
}

void SAT_BaseWidget::do_widget_notify(SAT_BaseWidget* AWidget, uint32_t AType, int32_t AValue)
{
    SAT_BaseWidget* parent = getParent();
    if (parent) parent->do_widget_notify(AWidget,AType,AValue);
}

void SAT_BaseWidget::do_widget_hint(SAT_BaseWidget* AWidget, uint32_t AType, const char* AHint)
{
    SAT_BaseWidget* parent = getParent();
    if (parent) parent->do_widget_hint(AWidget,AType,AHint);
}

void SAT_BaseWidget::do_widget_modal(SAT_BaseWidget* AWidget)
{
    SAT_BaseWidget* parent = getParent();
    if (parent) parent->do_widget_modal(AWidget);
}

void SAT_BaseWidget::do_widget_cursor(SAT_BaseWidget* AWidget, uint32_t ACursor)
{
    SAT_BaseWidget* parent = getParent();
    if (parent) parent->do_widget_cursor(AWidget,ACursor);
}

void SAT_BaseWidget::do_widget_capture_mouse(SAT_BaseWidget* AWidget)
{
    SAT_BaseWidget* parent = getParent();
    if (parent) parent->do_widget_capture_mouse(AWidget);
}

void SAT_BaseWidget::do_widget_capture_keyboard(SAT_BaseWidget* AWidget)
{
    SAT_BaseWidget* parent = getParent();
    if (parent) parent->do_widget_capture_keyboard(AWidget);
}
