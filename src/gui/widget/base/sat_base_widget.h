#pragma once

#include "base/sat_base.h"
#include "gui/sat_gui_base.h"
#include "gui/sat_skin.h"

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
    uint32_t        anchor                  = SAT_WIDGET_LAYOUT_ANCHOR_TOP_LEFT;    // snap widget pos to parent
    uint32_t        stretch                 = SAT_WIDGET_LAYOUT_STRETCH_NONE;       // stretch widget sides (after snapping)
    uint32_t        crop                    = SAT_WIDGET_LAYOUT_CROP_NONE;          // crop widget rect out of 'available' layout rect (for following widgets)
    uint32_t        relative                = SAT_WIDGET_LAYOUT_RELATIVE_NONE;      // pos/size relative to parent, layout (percentages)
    uint32_t        stack                   = SAT_WIDGET_LAYOUT_STACK_NONE;         // horiz/vert stacked (icon view)
    SAT_Rect        inner_border            = {0,0,0,0};                            // border around child widgets
    SAT_Rect        outer_border            = {0,0,0,0};                            // border around widget itself (in parent widget)
    SAT_Point       spacing                 = {0,0};                                // space between widgets
    SAT_Point       minSize                 = {-1,-1};                              // minimum widget size (-1 for none)
    SAT_Point       maxSize                 = {-1,-1};                              // maximum widget size (-1 for none)
};

struct SAT_WidgetOptions
{
    bool            auto_capture            = true;                                 // auto capture mouse when clicking
    bool            auto_clip               = true;                                 // clip child widgets
    bool            auto_cursor_shape       = true;                                 // set cursor shape when hovering over widget
    bool            auto_cursor_lock        = true;                                 // lock cursor in place (when dragging)
    bool            auto_cursor_hide        = true;                                 // auto hide cursor when dragging
    bool            auto_hint               = false;                                // auto send hint when hovering
    bool            auto_size               = false;                                // scale/zoom widget (content) relative to rect/size (f.ex. font size)
    bool            want_hover_events       = false;                                // want hover, move, etc mouse events even when not captured
    bool            realign_if_invisible    = false;                                // realign (child) widgets, even if not visible (menus, etc)
    bool            auto_redraw_hover       = false;                                // realign (child) widgets, even if not visible (menus, etc)
};

struct SAT_WidgetState
{
    bool            active                  = true;                                 // handles events
    bool            enabled                 = true;                                 // if false, draw 'disabled'state (greyed out)
    bool            opaque                  = true;                                 // set to true if widget fills it's entire rect
    bool            visible                 = true;                                 // drawing/alignment
    bool            hovering                = false;                                // mouse cursor is hovering over widget
    bool            interacting             = false;                                // interacting with widget
};

struct SAT_WidgetRecursive
{
    SAT_Rect        rect                    = {};
    SAT_Rect        clip_rect               = {};
    SAT_Rect        content_rect            = {};
    sat_coord_t     scale                   = 1.0;
    SAT_BaseWidget* opaque_parent           = nullptr;
 // bool            active                  = true;
 // bool            enabled                 = true;
 // bool            opaque                  = true;
 // bool            visible                 = true;
 // SAT_Skin        skin                    = {};
 // SAT_Color       background              = SAT_Grey;
};

struct SAT_WidgetUpdateState
{
    uint32_t        last_painted            = SAT_UINT32_MAX;
 // uint32_t        last_painted_count      = 0;
 // uint32_t        last_redrawn            = SAT_UINT32_MAX;
 // uint32_t        last_realigned          = SAT_UINT32_MAX;
 // uint32_t        last_updated            = SAT_UINT32_MAX;
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

        virtual void                setName(const char* AName);
        virtual void                setHint(const char* AHint);

        virtual const char*         getName();
        virtual const char*         getHint();
        virtual const char*         getWidgetTypeName();

    public: // hierarchy

        virtual void                setOwner(SAT_WidgetOwner* AOwner)                                   { }
        virtual void                setParent(SAT_BaseWidget* AParent)                                  { }
        virtual void                setIndex(uint32_t AIndex)                                           { }

        virtual SAT_WidgetOwner*    getOwner()                                                          { return nullptr; }
        virtual SAT_BaseWidget*     getParent()                                                         { return nullptr; }
        virtual uint32_t            getIndex()                                                          { return 0; }

        virtual SAT_BaseWidget*     appendChild(SAT_BaseWidget* AWidget)                                { return AWidget; }
        virtual void                deleteChildren()                                                    { }
        virtual void                removeChild(SAT_BaseWidget* AWidget)                                { }
        virtual uint32_t            getNumChildren()                                                    { return 0; }
        virtual SAT_BaseWidget*     getChild(uint32_t AIndex)                                           { return nullptr; }

        virtual SAT_BaseWidget*     findChild(const char* AName)                                        { return nullptr; }

    public: // visual

        virtual void                setOpaque(bool AState=true)                                         { }
        virtual void                setVisible(bool AState=true)                                        { }
        virtual void                setChildrenVisible(bool AState=true)                                { }
        virtual void                setScale(sat_coord_t AScale)                                        { }
        virtual void                setSkin(SAT_Skin* ASkin, bool AReplace=true)                        { }
        virtual void                setChildrenSkin(SAT_Skin* ASkin, bool AReplace=true)                { }

     // virtual void                setRect(SAT_Rect ARect)                                             { }
     // virtual void                setBaseRect(SAT_Rect ARect)                                         { }

        virtual bool                isOpaque()                                                          { return false; }
        virtual bool                isVisible()                                                         { return false; }
        virtual sat_coord_t         getScale()                                                          { return 1.0; }
        virtual SAT_Skin*           getSkin()                                                           { return nullptr; }

        virtual SAT_Rect            getRect()                                                           { return SAT_Rect(); }
        virtual SAT_Rect            getClipRect()                                                       { return SAT_Rect(); }
        virtual SAT_Rect            getContentRect()                                                    { return SAT_Rect(); }
        virtual SAT_BaseWidget*     getOpaqueParent()                                                   { return nullptr; }

        virtual SAT_BaseWidget*     findChildAt(int32_t AXpos, int32_t AYpos)                           { return nullptr; }

        virtual void                pushClip(SAT_PaintContext* AContext)                                { }
        virtual void                pushRecursiveClip(SAT_PaintContext* AContext)                       { }
        virtual void                popClip(SAT_PaintContext* AContext)                                 { }

        virtual sat_coord_t         getPaintScale()                                                     { return 1.0; }
        virtual void                paintChildren(SAT_PaintContext* AContext)                           { }

    public: // layout

        virtual void                realignChildren()                                                   { }

    public: // interactive

        virtual void                setActive(bool AState=true)                                         { }
        virtual void                setChildrenActive(bool AState=true)                                 { }
        virtual void                setEnabled(bool AState=true)                                        { }
        virtual void                setChildrenEnabled(bool AState=true)                                { }

        virtual bool                isActive()                                                          { return false; }
        virtual bool                isEnabled()                                                         { return false; }

     // virtual void                activateVisibleChildren()                                           { }
     // virtual void                deactivateInvisibleChildren()                                       { }

    public: // value

        virtual sat_param_t         getValue(uint32_t AIndex=0)                                         { return 0.0; }
        virtual SAT_Parameter*      getParameter(uint32_t AIndex=0)                                     { return nullptr; }
        virtual void                setValue(sat_param_t AValue, uint32_t AIndex=0)                     { }
        virtual void                setParameter(SAT_Parameter* AParameter, uint32_t AIndex=0)          { }

    public: // on_

        virtual void                on_widget_show(SAT_WidgetOwner* AOwner)                                                                     {}
        virtual void                on_widget_hide(SAT_WidgetOwner* AOwner)                                                                     {}
        virtual void                on_widget_paint(SAT_PaintContext* AContext)                                                                 {}
        virtual void                on_widget_pre_paint(SAT_PaintContext* AContext)                                                             {}
        virtual void                on_widget_post_paint(SAT_PaintContext* AContext)                                                            {}
        virtual void                on_widget_realign()                                                                                         {}
        virtual SAT_Rect            on_widget_pre_align(SAT_Rect ARect)                                                                         { return SAT_Rect(); }
        virtual SAT_Rect            on_widget_post_align(SAT_Rect ARect)                                                                        { return SAT_Rect(); }
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

        virtual void                do_widget_update(SAT_BaseWidget* AWidget, uint32_t AIndex=0);
        virtual void                do_widget_realign(SAT_BaseWidget* AWidget);
        virtual void                do_widget_redraw(SAT_BaseWidget* AWidget);
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
        SAT_WidgetRecursive         Recursive       = {};
        SAT_WidgetUpdateState       UpdateState     = {};

    protected: // base
    
        const char*                 MName           = "";
        const char*                 MHint           = "";
        const char*                 MWidgetTypeName = "SAT_BaseWidget";
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

void SAT_BaseWidget::setName(const char* AName)
{
    MName = AName;
}

void SAT_BaseWidget::setHint(const char* AHint)
{
    MHint = AHint;
}

const char* SAT_BaseWidget::getName()
{
    return MName;
}

const char* SAT_BaseWidget::getHint()
{
    return MHint;
}

const char* SAT_BaseWidget::getWidgetTypeName()
{
    return MWidgetTypeName;
}


//------------------------------
// do_
//------------------------------

void SAT_BaseWidget::do_widget_update(SAT_BaseWidget* AWidget, uint32_t AIndex)
{
    SAT_BaseWidget* parent = getParent();
    if (parent) parent->do_widget_update(AWidget,AIndex);
}

void SAT_BaseWidget::do_widget_realign(SAT_BaseWidget* AWidget)
{
    SAT_BaseWidget* parent = getParent();
    if (parent) parent->do_widget_realign(AWidget);
}

void SAT_BaseWidget::do_widget_redraw(SAT_BaseWidget* AWidget)
{
    SAT_BaseWidget* parent = getParent();
    if (parent) parent->do_widget_redraw(AWidget);
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
