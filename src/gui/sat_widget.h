#pragma once

#include "base/sat_base.h"
#include "gui/painter/sat_paint_context.h"
#include "gui/widget/sat_base_widget.h"
#include "gui/widget/sat_widget_owner.h"
#include "gui/sat_painter.h"
#include "gui/sat_skin.h"

class SAT_AnimChain;
class SAT_Parameter;

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_Widget
: public SAT_BaseWidget
{

    // friend class SAT_WidgetWindow;
    
    public:

        SAT_Widget(SAT_Rect ARect);
        virtual ~SAT_Widget();

    public: // base

        void                setName(const char* AName) override;
        void                setHint(const char* AHint) override;
        const char*         getName() override;
        const char*         getHint() override;
        const char*         getWidgetTypeName() override;

    public: // hierarchy

        void                setOwner(SAT_WidgetOwner* AOwner) override;
        void                setParent(SAT_Widget* AParent) override;
        void                setIndex(uint32_t AIndex) override;
        SAT_WidgetOwner*    getOwner() override;
        SAT_Widget*         getParent() override;
        uint32_t            getIndex() override;
        SAT_Widget*         appendChild(SAT_Widget* AWidget) override;
        void                deleteChildren() override;
        void                removeChild(SAT_Widget* AWidget) override;
        uint32_t            getNumChildren() override;
        SAT_Widget*         getChild(uint32_t AIndex) override;
        SAT_Widget*         findChild(const char* AName) override;

    public: // visual

        void                setOpaque(bool AState=true) override;
        void                setVisible(bool AState=true) override;
        void                setChildrenVisible(bool AState=true) override;
        void                setScale(sat_coord_t AScale) override;
        void                setSkin(SAT_Skin* ASkin, bool AReplace=true) override;
        void                setChildrenSkin(SAT_Skin* ASkin, bool AReplace=true) override;
     // void                setRect(SAT_Rect ARect) override;
     // void                setBaseRect(SAT_Rect ARect) override;
        bool                isOpaque() override;
        bool                isVisible() override;
        sat_coord_t         getScale() override;
        SAT_Skin*           getSkin() override;
        SAT_Rect            getRect() override;
        SAT_Rect            getClipRect() override;
        SAT_Rect            getContentRect() override;
        SAT_Widget*         getOpaqueParent() override;
        SAT_Widget*         findChildAt(int32_t AXpos, int32_t AYpos) override;
        void                pushClip(SAT_PaintContext* AContext) override;
        void                pushRecursiveClip(SAT_PaintContext* AContext) override;
        void                popClip(SAT_PaintContext* AContext) override;
        sat_coord_t         getPaintScale() override;
        uint32_t            getPaintState() override;
        void                paintChildren(SAT_PaintContext* AContext) override;

    public: // layout

        void                realignChildren() override;


    public: // interactive

        void                setActive(bool AState=true) override;
        void                setChildrenActive(bool AState=true) override;
        void                setEnabled(bool AState=true) override;
        void                setChildrenEnabled(bool AState=true) override;
        bool                isActive() override;
        bool                isEnabled() override;
     // void                activateVisibleChildren() override;
     // void                deactivateInvisibleChildren() override;

    public: // value

        uint32_t            getValueIndex() override;
        sat_param_t         getValue() override;
        sat_param_t         getValue(uint32_t AIndex) override;
        SAT_Parameter*      getParameter() override;
        SAT_Parameter*      getParameter(uint32_t AIndex) override;
        void                setValueIndex(uint32_t AIndex) override;
        void                setValue(sat_param_t AValue) override;
        void                setValue(sat_param_t AValue, uint32_t AIndex) override;
        void                setParameter(SAT_Parameter* AParameter) override;
        void                setParameter(SAT_Parameter* AParameter, uint32_t AIndex) override;

    public: // on_

        void                on_widget_show(SAT_WidgetOwner* AOwner) override;
        void                on_widget_hide(SAT_WidgetOwner* AOwner) override;
        void                on_widget_paint(SAT_PaintContext* AContext) override;
        void                on_widget_pre_paint(SAT_PaintContext* AContext) override;
        void                on_widget_post_paint(SAT_PaintContext* AContext) override;
        void                on_widget_realign() override;
        SAT_Rect            on_widget_pre_align(SAT_Rect ARect) override;
        SAT_Rect            on_widget_post_align(SAT_Rect ARect) override;
        void                on_widget_timer(uint32_t ATimerId, double ADelta) override;
        void                on_widget_anim(uint32_t AId, uint32_t AType, uint32_t ANumValues, double* AValues) override;
        void                on_widget_hint(uint32_t AType, const char* AHint) override;
        void                on_widget_mouse_click(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATime) override;
        void                on_widget_mouse_dbl_click(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATime) override;
        void                on_widget_mouse_release(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATime) override;
        void                on_widget_mouse_move(int32_t AXpos, int32_t AYpos, uint32_t AState, uint32_t ATime) override;
        void                on_widget_mouse_enter(SAT_Widget* AFrom, int32_t AXpos, int32_t AYpos, uint32_t ATime) override;
        void                on_widget_mouse_leave(SAT_Widget* ATo, int32_t AXpos, int32_t AYpos, uint32_t ATime) override;
        void                on_widget_key_press(uint32_t AKey, uint32_t AChar, uint32_t AState, uint32_t ATime) override;
        void                on_widget_key_release(uint32_t AKey, uint32_t AChar, uint32_t AState, uint32_t ATime) override;

    public: // do_

        void                do_widget_update(SAT_Widget* AWidget, uint32_t AIndex=0) override;
        void                do_widget_realign(SAT_Widget* AWidget) override;
        void                do_widget_redraw(SAT_Widget* AWidget) override;
        void                do_widget_anim(SAT_Widget* AWidget, SAT_AnimChain* AChain) override;
        void                do_widget_notify(SAT_Widget* AWidget, uint32_t AType=SAT_WIDGET_NOTIFY_NONE, int32_t AValue=0) override;
        void                do_widget_hint(SAT_Widget* AWidget, uint32_t AType, const char* AHint) override;
        void                do_widget_modal(SAT_Widget* AWidget) override;
        void                do_widget_cursor(SAT_Widget* AWidget, uint32_t ACursor) override;
        void                do_widget_capture_mouse(SAT_Widget* AWidget) override;
        void                do_widget_capture_keyboard(SAT_Widget* AWidget) override;

};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

SAT_Widget::SAT_Widget(SAT_Rect ARect)
: SAT_BaseWidget()
{
    WidgetBase.widgetTypeName     = "SAT_Widget";
    WidgetVisual.baseRect         = ARect;
    WidgetVisual.initialRect      = ARect;
    WidgetRecursive.rect          = ARect;
    WidgetRecursive.clip_rect     = ARect;
    WidgetRecursive.content_rect  = ARect;
    WidgetRecursive.opaque_parent = this;
}

SAT_Widget::~SAT_Widget()
{
    #ifndef SAT_NO_AUTODELETE
        deleteChildren();
    #endif
}

//------------------------------
//
// base
//
//------------------------------

void SAT_Widget::setName(const char* AName)
{
    WidgetBase.name = AName;
}

void SAT_Widget::setHint(const char* AHint)
{
    WidgetBase.hint = AHint;
}

const char* SAT_Widget::getName()
{
    return WidgetBase.name;
}

const char* SAT_Widget::getHint()
{
    return WidgetBase.hint;
}

const char* SAT_Widget::getWidgetTypeName()
{
    return WidgetBase.widgetTypeName;
}

//------------------------------
//
// hierarchy
//
//------------------------------

void SAT_Widget::setOwner(SAT_WidgetOwner* AOwner)
{
    WidgetHierarchy.owner = AOwner;
}

void SAT_Widget::setParent(SAT_Widget* AParent)
{
    WidgetHierarchy.parent = AParent;
}

void SAT_Widget::setIndex(uint32_t AIndex)
{
    WidgetHierarchy.index = AIndex;
}

//----------

SAT_WidgetOwner* SAT_Widget::getOwner()
{
    return WidgetHierarchy.owner;
}

SAT_Widget* SAT_Widget::getParent()
{
    return WidgetHierarchy.parent;
}

uint32_t SAT_Widget::getIndex()
{
    return WidgetHierarchy.index;
}

//----------

SAT_Widget* SAT_Widget::appendChild(SAT_Widget* AWidget)
{
    AWidget->WidgetHierarchy.parent = this;
    uint32_t index = WidgetHierarchy.children.size();
    AWidget->WidgetHierarchy.index = index;
    if (!AWidget->WidgetVisual.skin) AWidget->WidgetVisual.skin = WidgetVisual.skin;
    WidgetHierarchy.children.append(AWidget);
    return AWidget;
}

void SAT_Widget::deleteChildren()
{
    for (uint32_t i=0; i<getNumChildren(); i++)
    {
        SAT_Widget* widget = getChild(i);
        if (widget) delete widget;
    }
}

void SAT_Widget::removeChild(SAT_Widget* AWidget)
{
    AWidget->setParent(nullptr);
    WidgetHierarchy.children.remove(AWidget);
}

uint32_t SAT_Widget::getNumChildren()
{
    return WidgetHierarchy.children.size();
}

SAT_Widget* SAT_Widget::getChild(uint32_t AIndex)
{
    return WidgetHierarchy.children[AIndex];
}

SAT_Widget* SAT_Widget::findChild(const char* AName)
{
    const char* name = getName();
    if (strcmp(AName,name) == 0)
    {
        return this;
    }
    for (uint32_t i=0; i<getNumChildren(); i++)
    {
        SAT_Widget* child = getChild(i);
        name = child->getName();
        if (strcmp(AName,name) == 0) 
        {
            return child;
        }
        else
        {
            SAT_Widget* subchild = child->findChild(AName);
            if (subchild) return subchild;
        }
    }
    return nullptr;
}

//----------

// void SAT_Widget::setshowOwner(SAT_WidgetOwner* AOwner)
// {
//     setOwner(AOwner);
//     uint32_t num = getNumChildren();
//     for (uint32_t i=0; i<num; i++)
//     {
//         SAT_Widget* widget = getChild(i);
//         widget->showOwner(AOwner);
//     }
// }

// void SAT_Widget::hideOwner(SAT_WidgetOwner* AOwner)
// {
//     setOwner(nullptr);
//     uint32_t num = getNumChildren();
//     for (uint32_t i=0; i<num; i++)
//     {
//         SAT_Widget* widget = getChild(i);
//         widget->hideOwner(AOwner);
//     }
// }

void SAT_Widget::setOpaque(bool AState)
{
    WidgetState.opaque = AState;
}

void SAT_Widget::setVisible(bool AState)
{
    WidgetState.visible = AState;
    setChildrenVisible(AState);

}

void SAT_Widget::setChildrenVisible(bool AState)
{
    for (uint32_t i=0; i<getNumChildren(); i++)
    {
        SAT_Widget* child = getChild(i);
        child->setVisible(AState);
    }
}

void SAT_Widget::setScale(sat_coord_t AScale)
{
    WidgetVisual.scale = AScale;
}

/*
    if AReplace is true, it will just replace the existing skin 
    else it will only set skin if it doesn't alreaduy have one
*/

void SAT_Widget::setSkin(SAT_Skin* ASkin, bool AReplace)
{
    if ((!WidgetVisual.skin) || AReplace)
    {
        WidgetVisual.skin = ASkin;
    }
    setChildrenSkin(ASkin,AReplace);
}

void SAT_Widget::setChildrenSkin(SAT_Skin* ASkin, bool AReplace)
{
    for (uint32_t i=0; i<getNumChildren(); i++)
    {
        SAT_Widget* child = getChild(i);
        child->setSkin(ASkin,AReplace);
    }
}

/*
    ARect = screen-space
    todo: convert back to widget-space & set base_rect
*/

// void SAT_Widget::setRect(SAT_Rect ARect)
// {
// }

/*
    ARect = widget-space..
    unaffected by alignment/layout
*/

// void SAT_Widget::setBaseRect(SAT_Rect ARect)
// {
// }

//----------

bool SAT_Widget::isOpaque()
{
    return WidgetState.opaque;
}

bool SAT_Widget::isVisible()
{
    return WidgetState.visible;
}

sat_coord_t SAT_Widget::getScale()
{
    return WidgetVisual.scale;
}

SAT_Skin* SAT_Widget::getSkin()
{
    return WidgetVisual.skin;
}

//----------

SAT_Rect SAT_Widget::getRect()
{
    return WidgetRecursive.rect;
}

SAT_Rect SAT_Widget::getClipRect()
{
    return WidgetRecursive.clip_rect;
}

SAT_Rect SAT_Widget::getContentRect()
{
    return WidgetRecursive.content_rect;
}

SAT_Widget* SAT_Widget::getOpaqueParent()
{
    return WidgetRecursive.opaque_parent;
}

//----------

/*
    returns null if no child widgets at x,y
*/

SAT_Widget* SAT_Widget::findChildAt(int32_t AXpos, int32_t AYpos)
{
    uint32_t num = getNumChildren();
    if (num > 0)
    {
        for (int32_t i=num-1; i>=0; i--)
        {
            SAT_Widget* widget = getChild(i);
            SAT_Rect widget_rect = widget->WidgetRecursive.rect;
            if (widget->WidgetState.active)
            {
                if (widget_rect.contains(AXpos,AYpos))
                {
                    return widget->findChildAt(AXpos,AYpos);
                }
            }
        }
    }
    return this;
}

//----------

void SAT_Widget::pushClip(SAT_PaintContext* AContext)
{
    if (WidgetOptions.auto_clip)
    {
        SAT_Painter* painter= AContext->painter;
        SAT_Rect rect = getRect();
        painter->pushOverlappingClipRect(rect);
    }
}

void SAT_Widget::pushRecursiveClip(SAT_PaintContext* AContext)
{
    if (WidgetOptions.auto_clip)
    {
        SAT_Painter* painter= AContext->painter;
        SAT_Rect rect = WidgetRecursive.clip_rect;
        painter->pushOverlappingClipRect(rect);
    }
}

void SAT_Widget::popClip(SAT_PaintContext* AContext)
{
    if (WidgetOptions.auto_clip)
    {
        SAT_Painter* painter= AContext->painter;
        painter->popClipRect();

    }
}

//----------

sat_coord_t SAT_Widget::getPaintScale()
{
    SAT_Assert(WidgetHierarchy.owner);
    sat_coord_t scale = WidgetHierarchy.owner->do_widget_owner_get_scale(this);
    scale *= WidgetRecursive.scale;
    scale *= getScale();
    return scale;
}

uint32_t SAT_Widget::getPaintState()
{
    uint32_t state = SAT_SKIN_STATE_NORMAL;
    if (WidgetOptions.redraw_if_hovering)
    {
        if (WidgetState.hovering) state |= SAT_SKIN_STATE_HOVERING;
    }
    if (WidgetState.highlighted) state |= SAT_SKIN_STATE_HIGHLIGHTED;
    if (!WidgetState.enabled) state |= SAT_SKIN_STATE_DISABLED;
    if (WidgetState.interact) state |= SAT_SKIN_STATE_INTERACT;
    return state;
}

/*
    assumes widget is visible, and clipping is set up
    see: WidgetState.visible, pushRecursiveClip/popClip
*/

void SAT_Widget::paintChildren(SAT_PaintContext* AContext)
{
    uint32_t numchildren = WidgetHierarchy.children.size();
    if (numchildren > 0)
    {
        for(uint32_t i=0; i<numchildren; i++)
        {
            SAT_Widget* child = WidgetHierarchy.children[i];
            if (child->WidgetState.visible)
            {
                //SAT_Rect widgetrect = child->WidgetRecursive.rect;
                //widgetrect.overlap(WidgetRecursive.rect);
                //if (widgetrect.isNotEmpty())
                if (child->WidgetRecursive.rect.intersects(WidgetRecursive.rect))
                {
                    // widget->pushClip(AContext);
                    child->pushRecursiveClip(AContext);
                    child->on_widget_paint(AContext);
                    child->popClip(AContext);
                    child->WidgetUpdate.last_painted = AContext->current_frame;
                }
            }
        }
    }
}

//------------------------------
//
// layout
//
//------------------------------

/*
    realign all child widgets (recursively)
    note: MOwner (SAT_WidgetOwner) needs to be set..
    (we need it to ask for window.scaling and root.size, etc)

    called directly from:
        SAT_WidgetWindow.on_window_show     // after on_widget_show() has been called (and given the WidgetOwner to the widgets)
        SAT_WidgetWindow.on_window_resize   // we are waiting for the initial MAP_NOTIFY events when opning the window,
                                            // (if SAT_X11_WAIT_FOR_MAPNOTIFY is defined, see SAT_X11Window.show())
                                            // so we shouldn't get any resize events, and thus, realignChildren() calls, before on_window_show()?
    via on_widget_realign:
        SAT_WidgetWindow.handleTimer        // via SAT_WidgetWindow.on_timer_listener_update() (timer thread)
                                            // -> sendClientMessage -> on_window_timer() (gui thread) -> handleTimer
*/

void SAT_Widget::realignChildren()
{
    // on_window_show -> on_widget_show should have set this..
    SAT_Assert(WidgetHierarchy.owner);

    sat_coord_t scale = WidgetHierarchy.owner->do_widget_owner_get_scale(this);
    sat_coord_t recursive_scale = WidgetRecursive.scale * getScale();
    scale *= recursive_scale;

    sat_coord_t w = WidgetHierarchy.owner->do_widget_owner_get_width(this);
    sat_coord_t h = WidgetHierarchy.owner->do_widget_owner_get_height(this);
    SAT_Rect root_rect = SAT_Rect(w,h);

    SAT_Rect rect = WidgetRecursive.rect;
    //SAT_PRINT("rect %.1f,%.1f root %.1f,%.1f\n",rect.w,rect.h,w,h);

    SAT_Rect inner_border = WidgetLayout.inner_border;
    inner_border.scale(scale);

    SAT_Point spacing = WidgetLayout.spacing;
    spacing.scale(scale);

    SAT_Rect parent_rect = rect;
    parent_rect.shrink(inner_border);

    SAT_Rect layout_rect = rect;
    layout_rect.shrink(inner_border);

    WidgetRecursive.content_rect = SAT_Rect( rect.x,rect.y, 0,0 );

    double layout_xcenter   = layout_rect.x + (layout_rect.w * 0.5);
    double layout_ycenter   = layout_rect.y + (layout_rect.h * 0.5);
    double stackx           = 0;
    double stacky           = 0;
    double stack_highest    = 0;
    double stack_widest     = 0;

    // ---

    for (uint32_t i=0; i<WidgetHierarchy.children.size(); i++)
    {
        SAT_Widget* child = (SAT_Widget*)WidgetHierarchy.children[i];
        SAT_Assert(child);

        SAT_Rect child_rect;

        bool need_realign = (child->WidgetState.visible || child->WidgetOptions.realign_if_invisible);
        if (need_realign)
        {

            // --- relative ---

            if (child->WidgetLayout.relative)
            {
                if (child->WidgetLayout.relative == SAT_WIDGET_LAYOUT_RELATIVE_ROOT)
                {
                    child_rect = SAT_Rect(root_rect.w,root_rect.h,root_rect.w,root_rect.h);
                    child_rect.scale(child->WidgetVisual.initialRect);
                    child_rect.scale(0.01);
                }
                else if (child->WidgetLayout.relative == SAT_WIDGET_LAYOUT_RELATIVE_PARENT)
                {
                    child_rect = SAT_Rect(parent_rect.w,parent_rect.h,parent_rect.w,parent_rect.h);
                    child_rect.scale(child->WidgetVisual.initialRect);
                    child_rect.scale(0.01);
                }
                else if (child->WidgetLayout.relative == SAT_WIDGET_LAYOUT_RELATIVE_LAYOUT)
                {
                    child_rect = SAT_Rect(layout_rect.w,layout_rect.h,layout_rect.w,layout_rect.h);
                    child_rect.scale(child->WidgetVisual.initialRect);
                    child_rect.scale(0.01);
                }
                else // relative to current/self ??
                {
                    child_rect = SAT_Rect(rect.w,rect.h,rect.w,rect.h);
                    child_rect.scale(child->WidgetVisual.initialRect);
                    child_rect.scale(0.01);
                }
            }
            else
            {
                child_rect = child->WidgetVisual.baseRect;
                child_rect.scale(scale);
            }

            // --- TODO: anim / manual movement ---
            
            /*
                SAT_Rect manual = child->MManualAnim;
                manual.scale(scale);
                child_rect.add(manual);
                //child_rect.add(child->MManuallyMoved);
            */

            // --- pre-align ---

            child_rect = child->on_widget_pre_align(child_rect);

            /*
                child_rect.add(child->MManuallyMoved);
            */

            // --- anchor ---

            bool xanchored = false;
            bool yanchored = false;
            if (child->WidgetLayout.anchor & SAT_WIDGET_LAYOUT_ANCHOR_LEFT)               { xanchored = true; child_rect.x += layout_rect.x; }
            if (child->WidgetLayout.anchor & SAT_WIDGET_LAYOUT_ANCHOR_TOP)                { yanchored = true; child_rect.y += layout_rect.y; }
            if (child->WidgetLayout.anchor & SAT_WIDGET_LAYOUT_ANCHOR_RIGHT)              { xanchored = true; child_rect.x += (layout_rect.x2()  - child_rect.w); }
            if (child->WidgetLayout.anchor & SAT_WIDGET_LAYOUT_ANCHOR_BOTTOM)             { yanchored = true; child_rect.y += (layout_rect.y2()  - child_rect.h); }
            if (child->WidgetLayout.anchor & SAT_WIDGET_LAYOUT_ANCHOR_CENTER_HORIZONTAL)  { xanchored = true; child_rect.x += (layout_xcenter - (child_rect.w * 0.5)); }
            if (child->WidgetLayout.anchor & SAT_WIDGET_LAYOUT_ANCHOR_CENTER_VERTICAL)    { yanchored = true; child_rect.y += (layout_ycenter - (child_rect.h * 0.5)); }

            // --- stack ---

            if (child->WidgetLayout.stack & SAT_WIDGET_LAYOUT_STACK_HORIZONTAL)
            {
                if ((stackx + child_rect.w) >= layout_rect.w)
                {
                    if (stackx != 0)
                    {
                        stackx = 0;
                        stacky += stack_highest + spacing.y;
                        stack_highest = 0;
                    }
                }
                xanchored = true;
                yanchored = true;
                child_rect.x += (layout_rect.x + stackx);
                child_rect.y += (layout_rect.y + stacky);
                stackx += child_rect.w + spacing.x;
                if (child_rect.h > stack_highest) stack_highest = child_rect.h;
            }

            if (child->WidgetLayout.stack & SAT_WIDGET_LAYOUT_STACK_VERTICAL)
            {
                if ((stacky + child_rect.h) >= layout_rect.h)
                {
                    if (stacky != 0)
                    {
                        stacky = 0;
                        stackx += stack_widest + spacing.x;
                        stack_widest = 0;
                    }
                }
                xanchored = true;
                yanchored = true;
                child_rect.x += (layout_rect.x + stackx);
                child_rect.y += (layout_rect.y + stacky);
                stacky += child_rect.h + spacing.y;
                if (child_rect.w > stack_widest) stack_widest = child_rect.w;
            }

            if (!xanchored) child_rect.x += rect.x;
            if (!yanchored) child_rect.y += rect.y;

            // --- stretch ---

            if (child->WidgetLayout.stretch & SAT_WIDGET_LAYOUT_STRETCH_LEFT)        { child_rect.setX1( layout_rect.x   ); }
            if (child->WidgetLayout.stretch & SAT_WIDGET_LAYOUT_STRETCH_TOP)         { child_rect.setY1( layout_rect.y   ); }
            if (child->WidgetLayout.stretch & SAT_WIDGET_LAYOUT_STRETCH_RIGHT)       { child_rect.setX2( layout_rect.x2()); }
            if (child->WidgetLayout.stretch & SAT_WIDGET_LAYOUT_STRETCH_BOTTOM)      { child_rect.setY2( layout_rect.y2()); }

            // --- crop ---

            if (child->WidgetLayout.crop & SAT_WIDGET_LAYOUT_CROP_LEFT)           { layout_rect.setX1( child_rect.x2()); layout_rect.x += spacing.x; layout_rect.w -= spacing.x; }
            if (child->WidgetLayout.crop & SAT_WIDGET_LAYOUT_CROP_TOP)            { layout_rect.setY1( child_rect.y2()); layout_rect.y += spacing.y; layout_rect.h -= spacing.y; }
            if (child->WidgetLayout.crop & SAT_WIDGET_LAYOUT_CROP_RIGHT)          { layout_rect.setX2( child_rect.x   ); layout_rect.w -= spacing.x; }
            if (child->WidgetLayout.crop & SAT_WIDGET_LAYOUT_CROP_BOTTOM)         { layout_rect.setY2( child_rect.y   ); layout_rect.h -= spacing.y; }

            // --- stack end ---

            if (child->WidgetLayout.stack & SAT_WIDGET_LAYOUT_STACK_END)
            {
                if (child->WidgetLayout.stack & SAT_WIDGET_LAYOUT_STACK_VERTICAL)
                {
                    float w = (stackx + stack_widest + spacing.x);
                    layout_rect.x += w;
                    layout_rect.w -= w;
                }
                if (child->WidgetLayout.stack & SAT_WIDGET_LAYOUT_STACK_HORIZONTAL)
                {
                    float h = (stacky + stack_highest + spacing.y);
                    layout_rect.y += h;
                    layout_rect.h -= h;
                }
            }

            // --- min/max size ---

            double min_width  = child->WidgetLayout.minSize.w * scale;
            double min_height = child->WidgetLayout.minSize.h * scale;
            double max_width  = child->WidgetLayout.maxSize.w * scale;
            double max_height = child->WidgetLayout.maxSize.h * scale;

            if ((min_width  >= 0) && (child_rect.w < min_width )) child_rect.w = min_width;
            if ((min_height >= 0) && (child_rect.h < min_height)) child_rect.h = min_height;
            if ((max_width  >= 0) && (child_rect.w > max_width )) child_rect.w = max_width;
            if ((max_height >= 0) && (child_rect.h > max_height)) child_rect.h = max_height;

            // --- content rect ---

            WidgetRecursive.content_rect.combine(child_rect);

            // --- outer border ---

            SAT_Rect outer_border = child->WidgetLayout.outer_border;
            outer_border.scale(scale);
            child_rect.shrink(outer_border);

            // --- post-align ---

            child_rect = child->on_widget_post_align(child_rect);

            // --- set child properties ---

            child->WidgetRecursive.rect       = child_rect;
            child->WidgetRecursive.scale      = recursive_scale;

            child->WidgetRecursive.clip_rect  = child_rect;
            //child->WidgetRecursive.clip_rect.overlap(WidgetRecursive.rect);
            child->WidgetRecursive.clip_rect.overlap(WidgetRecursive.clip_rect);

            if (child->WidgetState.opaque)
            {
                //SAT_PRINT("child %s = opaque\n",child->getName());
                child->WidgetRecursive.opaque_parent = child;
            }
            else
            {
                //SAT_PRINT("child %s = not opaque (opaque_parent %s\n",child->getName(),WidgetRecursive.opaque_parent->getName());
                child->WidgetRecursive.opaque_parent = WidgetRecursive.opaque_parent;
            }

            if (!child->WidgetVisual.skin) child->WidgetVisual.skin = WidgetVisual.skin;

            // --- recursive ---

            child->on_widget_realign();

            /*
                // scale the widget depending on its content...
                if (child_layout & SAT_WIDGET_LAYOUT_CONTENT_SIZE)
                {
                    SAT_Rect child_content = child->getContentRect();
                    child->WidgetRecursive.rect = child_content;
                }
            */

        } // need_realign

        else
        {
            // child->WidgetState.visible and child->WidgetOptions.realign_if_invisible is false
            child->setChildrenVisible(false);
        }

    } // for

    WidgetRecursive.content_rect.w += inner_border.w;
    WidgetRecursive.content_rect.h += inner_border.h;
}

//------------------------------
//
// interactive
//
//------------------------------

void SAT_Widget::setActive(bool AState)
{
    WidgetState.active = AState;
    setChildrenActive(AState);
}

void SAT_Widget::setChildrenActive(bool AState)
{
    uint32_t num = getNumChildren();
    for (uint32_t i=0; i<num; i++)
    {
        SAT_Widget* widget = getChild(i);
        widget->setActive(AState);
    }
}

void SAT_Widget::setEnabled(bool AState)
{
    WidgetState.enabled = AState;
    setChildrenEnabled(AState);
}

void SAT_Widget::setChildrenEnabled(bool AState)
{
    uint32_t num = getNumChildren();
    for (uint32_t i=0; i<num; i++)
    {
        SAT_Widget* widget = getChild(i);
        widget->setEnabled(AState);
    }
}

//----------

bool SAT_Widget::isActive()
{
    return WidgetState.active;
}

bool SAT_Widget::isEnabled()
{
    return WidgetState.enabled;
}

//------------------------------
//
// value
//
//------------------------------

uint32_t SAT_Widget::getValueIndex()
{
    return WidgetValue.index;
}

sat_param_t SAT_Widget::getValue()
{
    return WidgetValue.values[WidgetValue.index];
}

sat_param_t SAT_Widget::getValue(uint32_t AIndex)
{
    return WidgetValue.values[AIndex];
}

SAT_Parameter* SAT_Widget::getParameter()
{
    return WidgetValue.parameters[WidgetValue.index];
}

SAT_Parameter* SAT_Widget::getParameter(uint32_t AIndex)
{
    return WidgetValue.parameters[AIndex];
}

//----------

void SAT_Widget::setValueIndex(uint32_t AIndex)
{
    WidgetValue.index = AIndex;
}

void SAT_Widget::setValue(sat_param_t AValue)
{
    WidgetValue.values[WidgetValue.index] = AValue;
}

void SAT_Widget::setValue(sat_param_t AValue, uint32_t AIndex)
{
    WidgetValue.values[AIndex] = AValue;
}

void SAT_Widget::setParameter(SAT_Parameter* AParameter)
{
    WidgetValue.parameters[WidgetValue.index] = AParameter;
}

void SAT_Widget::setParameter(SAT_Parameter* AParameter, uint32_t AIndex)
{
    WidgetValue.parameters[AIndex] = AParameter;
}

//------------------------------
//
// on_
//
//------------------------------

void SAT_Widget::on_widget_show(SAT_WidgetOwner* AOwner)
{
    setOwner(AOwner);
    uint32_t num = getNumChildren();
    for (uint32_t i=0; i<num; i++)
    {
        SAT_Widget* widget = getChild(i);
        widget->on_widget_show(AOwner);
    }
}

void SAT_Widget::on_widget_hide(SAT_WidgetOwner* AOwner)
{
    setOwner(nullptr);
    uint32_t num = getNumChildren();
    for (uint32_t i=0; i<num; i++)
    {
        SAT_Widget* widget = getChild(i);
        widget->on_widget_hide(AOwner);
    }
}

void SAT_Widget::on_widget_paint(SAT_PaintContext* AContext)
{
    paintChildren(AContext);
}

void SAT_Widget::on_widget_pre_paint(SAT_PaintContext* AContext)
{
}

void SAT_Widget::on_widget_post_paint(SAT_PaintContext* AContext)
{
}

void SAT_Widget::on_widget_realign()
{
    realignChildren();
}

/*
    called before calculating new rect
    here we can remember the starting rect, prepare things..
*/

SAT_Rect SAT_Widget::on_widget_pre_align(SAT_Rect ARect)
{
    return ARect;
}

/*
    called after new rect has been calculated
    cwe can do some final adjustments, or undo things..
*/

SAT_Rect SAT_Widget::on_widget_post_align(SAT_Rect ARect)
{
    return ARect;
}

void SAT_Widget::on_widget_timer(uint32_t ATimerId, double ADelta)
{
}

void SAT_Widget::on_widget_anim(uint32_t AId, uint32_t AType, uint32_t ANumValues, double* AValues)
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

void SAT_Widget::on_widget_mouse_enter(SAT_Widget* AFrom, int32_t AXpos, int32_t AYpos, uint32_t ATime)
{
}

void SAT_Widget::on_widget_mouse_leave(SAT_Widget* ATo, int32_t AXpos, int32_t AYpos, uint32_t ATime)
{
}

void SAT_Widget::on_widget_key_press(uint32_t AKey, uint32_t AChar, uint32_t AState, uint32_t ATime)
{
}

void SAT_Widget::on_widget_key_release(uint32_t AKey, uint32_t AChar, uint32_t AState, uint32_t ATime)
{
}

//------------------------------
//
// do_
//
//------------------------------

void SAT_Widget::do_widget_update(SAT_Widget* AWidget, uint32_t AIndex)
{
    SAT_Widget* parent = getParent();
    if (parent) parent->do_widget_update(AWidget,AIndex);
}

void SAT_Widget::do_widget_realign(SAT_Widget* AWidget)
{
    SAT_Widget* parent = getParent();
    if (parent) parent->do_widget_realign(AWidget);
}

void SAT_Widget::do_widget_redraw(SAT_Widget* AWidget)
{
    SAT_Widget* parent = getParent();
    if (parent) parent->do_widget_redraw(AWidget);
}

void SAT_Widget::do_widget_anim(SAT_Widget* AWidget, SAT_AnimChain* AChain)
{
    SAT_Widget* parent = getParent();
    if (parent) parent->do_widget_anim(AWidget,AChain);
}

void SAT_Widget::do_widget_notify(SAT_Widget* AWidget, uint32_t AType, int32_t AValue)
{
    SAT_Widget* parent = getParent();
    if (parent) parent->do_widget_notify(AWidget,AType,AValue);
}

void SAT_Widget::do_widget_hint(SAT_Widget* AWidget, uint32_t AType, const char* AHint)
{
    SAT_Widget* parent = getParent();
    if (parent) parent->do_widget_hint(AWidget,AType,AHint);
}

void SAT_Widget::do_widget_modal(SAT_Widget* AWidget)
{
    SAT_Widget* parent = getParent();
    if (parent) parent->do_widget_modal(AWidget);
}

void SAT_Widget::do_widget_cursor(SAT_Widget* AWidget, uint32_t ACursor)
{
    SAT_Widget* parent = getParent();
    if (parent) parent->do_widget_cursor(AWidget,ACursor);
}

void SAT_Widget::do_widget_capture_mouse(SAT_Widget* AWidget)
{
    SAT_Widget* parent = getParent();
    if (parent) parent->do_widget_capture_mouse(AWidget);
}

void SAT_Widget::do_widget_capture_keyboard(SAT_Widget* AWidget)
{
    SAT_Widget* parent = getParent();
    if (parent) parent->do_widget_capture_keyboard(AWidget);
}
