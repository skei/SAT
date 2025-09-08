#pragma once

#include "base/sat_base.h"
#include "gui/sat_skin.h"
#include "gui/painter/sat_paint_context.h"
#include "gui/widget/sat_widget_owner.h"

class SAT_AnimChain;
class SAT_Parameter;
class SAT_Widget;

typedef SAT_Array<SAT_Widget*> SAT_WidgetArray;

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

struct SAT_Widget_Base
{
    const char*         widgetTypeName                      = "SAT_Widget";         // widget type (todo: enum too?)
    const char*         name                                = "";                   // name of widget
    const char*         hint                                = "";                   // hint/description
    const char*         tooltip                             = "";                   // hint/description
    uint32_t            cursor                              = SAT_CURSOR_DEFAULT;   // hint/description
};

struct SAT_Widget_Hierarchy
{
    SAT_WidgetOwner*    owner                               = nullptr;      // aka (widget-) window
    SAT_Widget*         parent                              = nullptr;      // parent widget
    uint32_t            index                               = 0;            // index (in parent's child-widgets)
    SAT_WidgetArray     children                            = {};           // sub-widgets
};

struct SAT_Widget_Visual
{
    SAT_Rect            baseRect                            = {};           // base rect, basis for layout/alignment
    SAT_Rect            initialRect                         = {};           // rect from creation (may be percentages, etc)
    sat_coord_t         scale                               = 1.0;          // current window scale
    SAT_Skin*           skin                                = nullptr;      // widget skin
};

struct SAT_Widget_Value
{
    uint32_t            index                               = 0;            // current selected value (index)
    sat_param_t         values[SAT_WIDGET_NUM_VALUES]       = {};           // values.. normalized (if control)
    SAT_Parameter*      parameters[SAT_WIDGET_NUM_VALUES]   = {};           // connected parameters
};

//----------

struct SAT_Widget_Layout
{
    uint32_t            anchor                  = SAT_WIDGET_LAYOUT_ANCHOR_TOP_LEFT;    // snap widget pos to parent
    uint32_t            stretch                 = SAT_WIDGET_LAYOUT_STRETCH_NONE;       // stretch widget sides (after snapping)
    uint32_t            crop                    = SAT_WIDGET_LAYOUT_CROP_NONE;          // crop widget rect out of 'available' layout rect (for following widgets)
    uint32_t            relative                = SAT_WIDGET_LAYOUT_RELATIVE_NONE;      // pos/size relative to parent, layout (percentages)
    uint32_t            stack                   = SAT_WIDGET_LAYOUT_STACK_NONE;         // horiz/vert stacked (icon view)
    SAT_Rect            inner_border            = {};                                   // border around child widgets
    SAT_Rect            outer_border            = {};                                   // border around widget itself (in parent widget)
    SAT_Point           spacing                 = {};                                   // space between widgets
    SAT_Point           minSize                 = {-1,-1};                              // minimum widget size (-1 for none)
    SAT_Point           maxSize                 = {-1,-1};                              // maximum widget size (-1 for none)
};

struct SAT_Widget_Options
{
    bool                mouse_capture           = true;                                 // capture mouse when clicking
    bool                clip                    = true;                                 // clip child widgets
    bool                tooltip                 = false;
    bool                want_hover_events       = false;                                // want hover, move, etc mouse events even when not captured
    bool                realign_if_invisible    = false;                                // realign (child) widgets, even if not visible (menus, etc)
    bool                redraw_if_hovering      = false;                                // realign (child) widgets, even if not visible (menus, etc)
    bool                auto_hint               = false;                                // auto send hint when hovering
    bool                auto_mouse_cursor       = true;                                 // set cursor shape when hovering over widget
    bool                auto_mouse_lock         = true;                                 // lock cursor in place (when dragging)
    bool                auto_mouse_hide         = true;                                 // auto hide cursor when dragging
 // bool                auto_size               = false;                                // scale/zoom widget (content) relative to rect/size (f.ex. font size)
    // bool movable
    // bool sizable
};

struct SAT_Widget_State
{
    bool                active                  = true;                                 // handles events
    bool                visible                 = true;                                 // drawing/alignment
    bool                opaque                  = true;                                 // set to true if widget fills it's entire rect
    bool                hovering                = false;                                // mouse cursor is hovering over widget
    bool                enabled                 = true;                                 // if false, draw 'disabled'state (greyed out)
    bool                interact                = false;                                // interacting with widget
    bool                highlighted             = false;                                // selected, on, ..
};

struct SAT_Widget_Recursive
{
    SAT_Rect            rect                    = {};
    SAT_Rect            clip_rect               = {};
    SAT_Rect            content_rect            = {};
    sat_coord_t         scale                   = 1.0;
    SAT_Widget*         opaque_parent           = nullptr;
};

struct SAT_Widget_Update
{
    uint32_t            last_painted            = SAT_UINT32_MAX;
 // uint32_t            last_redrawn            = SAT_UINT32_MAX;
 // uint32_t            last_realigned          = SAT_UINT32_MAX;
 // uint32_t            last_updated            = SAT_UINT32_MAX;
};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_BaseWidget
{

    friend class SAT_WidgetWindow;

    public:

        SAT_BaseWidget()                                                                        { }
        virtual ~SAT_BaseWidget()                                                               { }

    public: // base

        virtual void                setName(const char* AName)                                  { }
        virtual void                setHint(const char* AHint)                                  { }
        virtual void                setTooltip(const char* ATooltip)                            { }
        virtual const char*         getName()                                                   { return ""; }
        virtual const char*         getHint()                                                   { return ""; }
        virtual const char*         getTooltip()                                                { return ""; }
        virtual const char*         getWidgetTypeName()                                         { return ""; }

    public: // hierarchy

     // virtual void                setOwner(SAT_WidgetOwner* AOwner)                           { }
        virtual void                setParent(SAT_Widget* AParent)                              { }
        virtual void                setIndex(uint32_t AIndex)                                   { }
        virtual SAT_WidgetOwner*    getOwner()                                                  { return nullptr; }
        virtual SAT_Widget*         getParent()                                                 { return nullptr; }
        virtual uint32_t            getIndex()                                                  { return 0; }
        virtual SAT_Widget*         appendChild(SAT_Widget* AWidget)                            { return AWidget; }
        virtual void                deleteChildren()                                            { }
        virtual void                removeChild(SAT_Widget* AWidget, bool ADelete=true)         { }
        virtual uint32_t            getNumChildren()                                            { return 0; }
        virtual SAT_Widget*         getChild(uint32_t AIndex)                                   { return nullptr; }
        virtual SAT_Widget*         findChild(const char* AName)                                { return nullptr; }
        virtual void                showOwner(SAT_WidgetOwner* AOwner)                          { }
        virtual void                hideOwner(SAT_WidgetOwner* AOwner)                          { }

    public: // visual

        virtual void                setOpaque(bool AState=true)                                 { }
        virtual void                setVisible(bool AState=true)                                { }
        virtual void                setChildrenVisible(bool AState=true)                        { }
        virtual void                setScale(sat_coord_t AScale)                                { }
        virtual void                setSkin(SAT_Skin* ASkin, bool AReplace=true)                { }
        virtual void                setChildrenSkin(SAT_Skin* ASkin, bool AReplace=true)        { }
     // virtual void                setRect(SAT_Rect ARect)                                     { }
     // virtual void                setBaseRect(SAT_Rect ARect)                                 { }
        virtual bool                isOpaque()                                                  { return false; }
        virtual bool                isVisible()                                                 { return false; }
        virtual sat_coord_t         getScale()                                                  { return 1.0; }
        virtual SAT_Skin*           getSkin()                                                   { return nullptr; }
        virtual SAT_Rect            getRect()                                                   { return SAT_Rect(); }
        virtual SAT_Rect            getClipRect()                                               { return SAT_Rect(); }
        virtual SAT_Rect            getContentRect()                                            { return SAT_Rect(); }
        virtual SAT_Widget*         getOpaqueParent()                                           { return nullptr; }
        virtual SAT_Widget*         findChildAt(int32_t AXpos, int32_t AYpos)                   { return nullptr; }
        virtual void                pushClip(SAT_PaintContext* AContext)                        { }
        virtual void                pushRecursiveClip(SAT_PaintContext* AContext)               { }
        virtual void                popClip(SAT_PaintContext* AContext)                         { }
        virtual sat_coord_t         getPaintScale()                                             { return 1.0; }
        virtual uint32_t            getPaintState()                                             { return 0; }
        virtual void                paintChildren(SAT_PaintContext* AContext)                   { }

    public: // layout

        virtual void                realignChildren()                                           { }

    public: // interactive

        virtual void                setActive(bool AState=true)                                 { }
        virtual void                setChildrenActive(bool AState=true)                         { }
        virtual void                setEnabled(bool AState=true)                                { }
        virtual void                setChildrenEnabled(bool AState=true)                        { }
        virtual bool                isActive()                                                  { return false; }
        virtual bool                isEnabled()                                                 { return false; }
     // virtual void                activateVisibleChildren()                                   { }
     // virtual void                deactivateInvisibleChildren()                               { }

    public: // value

        virtual uint32_t            getValueIndex()                                             { return 0; }
        virtual sat_param_t         getValue()                                                  { return 0.0; }
        virtual sat_param_t         getValue(uint32_t AIndex)                                   { return 0.0; }
        virtual SAT_Parameter*      getParameter()                                              { return nullptr; }
        virtual SAT_Parameter*      getParameter(uint32_t AIndex)                               { return nullptr; }
        virtual void                setValueIndex(uint32_t AIndex)                              { }
        virtual void                setValue(sat_param_t AValue)                                { }
        virtual void                setValue(sat_param_t AValue, uint32_t AIndex)               { }
        virtual void                setParameter(SAT_Parameter* AParameter)                     { }
        virtual void                setParameter(SAT_Parameter* AParameter, uint32_t AIndex)    { }

    public: // on_

        virtual void                on_widget_show(SAT_WidgetOwner* AOwner)                                                                     { }
        virtual void                on_widget_hide(SAT_WidgetOwner* AOwner)                                                                     { }
        virtual void                on_widget_paint(SAT_PaintContext* AContext)                                                                 { }
        virtual void                on_widget_pre_paint(SAT_PaintContext* AContext)                                                             { }
        virtual void                on_widget_post_paint(SAT_PaintContext* AContext)                                                            { }
        virtual void                on_widget_realign()                                                                                         { }
        virtual SAT_Rect            on_widget_pre_align(SAT_Rect ARect)                                                                         { return SAT_Rect(); }
        virtual SAT_Rect            on_widget_post_align(SAT_Rect ARect)                                                                        { return SAT_Rect(); }
        virtual void                on_widget_timer(uint32_t ATimerId, double ADelta)                                                           { }
        virtual void                on_widget_anim(uint32_t AId, uint32_t AType, uint32_t ANumValues, double* AValues)                          { }
     // virtual void                on_widget_hint(uint32_t AType, const char* AHint)                                                           { }
     // virtual void                on_widget_tooltip(uint32_t AType, const char* ATooltip)                                                     { }
        virtual void                on_widget_mouse_click(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATime)      { }
        virtual void                on_widget_mouse_dbl_click(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATime)  { }
        virtual void                on_widget_mouse_longpress(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATime)  { }
        virtual void                on_widget_mouse_release(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATime)    { }
        virtual void                on_widget_mouse_move(int32_t AXpos, int32_t AYpos, uint32_t AState, uint32_t ATime)                         { }
        virtual void                on_widget_mouse_enter(SAT_Widget* AFrom, int32_t AXpos, int32_t AYpos, uint32_t ATime)                      { }
        virtual void                on_widget_mouse_leave(SAT_Widget* ATo, int32_t AXpos, int32_t AYpos, uint32_t ATime)                        { }
        virtual void                on_widget_key_press(uint32_t AKey, uint32_t AChar, uint32_t AState, uint32_t ATime)                         { }
        virtual void                on_widget_key_release(uint32_t AKey, uint32_t AChar, uint32_t AState, uint32_t ATime)                       { }

    public: // do_

        virtual void                do_widget_update(SAT_Widget* AWidget, uint32_t AIndex=0)                                                    { }
        virtual void                do_widget_realign(SAT_Widget* AWidget)                                                                      { }
        virtual void                do_widget_redraw(SAT_Widget* AWidget)                                                                       { }
        virtual void                do_widget_anim(SAT_Widget* AWidget, SAT_AnimChain* AChain)                                                  { }
        virtual void                do_widget_notify(SAT_Widget* AWidget, uint32_t AType=SAT_WIDGET_NOTIFY_NONE, int32_t AValue=0)              { }
        virtual void                do_widget_hint(SAT_Widget* AWidget, uint32_t AType, const char* AHint)                                      { }
        virtual void                do_widget_modal(SAT_Widget* AWidget)                                                                        { }
        virtual void                do_widget_cursor(SAT_Widget* AWidget, uint32_t ACursor)                                                     { }
        virtual void                do_widget_capture_mouse(SAT_Widget* AWidget)                                                                { }
        virtual void                do_widget_capture_keyboard(SAT_Widget* AWidget)                                                             { }

    public:

        SAT_Widget_Layout           WidgetLayout    = {};
        SAT_Widget_Options          WidgetOptions   = {};

    protected:

        SAT_Widget_State            WidgetState     = {};
        SAT_Widget_Recursive        WidgetRecursive = {};
        SAT_Widget_Update           WidgetUpdate    = {};

    protected:

        SAT_Widget_Base             WidgetBase      = {};
        SAT_Widget_Hierarchy        WidgetHierarchy = {};
        SAT_Widget_Visual           WidgetVisual    = {};
        SAT_Widget_Value            WidgetValue     = {};

};
