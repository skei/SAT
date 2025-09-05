#pragma once

#include "base/sat_base.h"
#include "gui/painter/sat_paint_context.h"
#include "gui/widget/sat_base_widget.h"
#include "gui/widget/sat_widget_owner.h"
#include "gui/widget/sat_widget_layout.h"
#include "gui/widget/sat_widget_options.h"
#include "gui/widget/sat_widget_state.h"
#include "gui/widget/sat_widget_recursive.h"
#include "gui/widget/sat_widget_update.h"
#include "gui/sat_painter.h"
#include "gui/sat_skin.h"

class SAT_AnimChain;
class SAT_Parameter;

class SAT_Widget;
typedef SAT_Array<SAT_Widget*> SAT_WidgetArray;

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

        sat_param_t         getValue(uint32_t AIndex=0) override;
        SAT_Parameter*      getParameter(uint32_t AIndex=0) override;
        void                setValue(sat_param_t AValue, uint32_t AIndex=0) override;
        void                setParameter(SAT_Parameter* AParameter, uint32_t AIndex=0) override;

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
        void                on_widget_key_press(uint32_t AKey, uint32_t AChar, uint32_t AState, uint32_t ATime) override;
        void                on_widget_key_release(uint32_t AKey, uint32_t AChar, uint32_t AState, uint32_t ATime) override;

        void                on_widget_mouse_enter(SAT_Widget* AFrom, int32_t AXpos, int32_t AYpos, uint32_t ATime) override;
        void                on_widget_mouse_leave(SAT_Widget* ATo, int32_t AXpos, int32_t AYpos, uint32_t ATime) override;

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

    public: // options

        SAT_WidgetLayout    Layout          = {};
        SAT_WidgetOptions   Options         = {};
        SAT_WidgetState     State           = {};
        SAT_WidgetRecursive Recursive       = {};
        SAT_WidgetUpdate    Update          = {};

    protected: // base
    
        const char*         MName           = "";
        const char*         MHint           = "";
        const char*         MWidgetTypeName = "SAT_Widget";

    protected: // hierarchy

        SAT_WidgetOwner*    MOwner          = nullptr;
        SAT_Widget*         MParent         = nullptr;
        SAT_WidgetArray     MChildren       = {};
        uint32_t            MIndex          = 0;

    protected: // visual

        SAT_Rect            MBaseRect       = {};
        SAT_Rect            MInitialRect    = {};
        sat_coord_t         MScale          = 1.0;
        SAT_Skin*           MSkin           = nullptr;        

    protected: // value

        sat_param_t         MValue          = 0.0;
        SAT_Parameter*      MParameter      = nullptr;

};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

SAT_Widget::SAT_Widget(SAT_Rect ARect)
: SAT_BaseWidget()
{
    MWidgetTypeName         = "SAT_Widget";
    MBaseRect               = ARect;
    MInitialRect            = ARect;
    Recursive.rect          = ARect;
    Recursive.clip_rect     = ARect;
    Recursive.content_rect  = ARect;
    Recursive.opaque_parent = this;

}

SAT_Widget::~SAT_Widget()
{
    #ifndef SAT_NO_AUTODELETE
        deleteChildren();
    #endif
}

//------------------------------
// base
//------------------------------

void SAT_Widget::setName(const char* AName)
{
    MName = AName;
}

void SAT_Widget::setHint(const char* AHint)
{
    MHint = AHint;
}

const char* SAT_Widget::getName()
{
    return MName;
}

const char* SAT_Widget::getHint()
{
    return MHint;
}

const char* SAT_Widget::getWidgetTypeName()
{
    return MWidgetTypeName;
}

//------------------------------
// hierarchy
//------------------------------

void SAT_Widget::setOwner(SAT_WidgetOwner* AOwner)
{
    MOwner = AOwner;
}

void SAT_Widget::setParent(SAT_Widget* AParent)
{
    MParent = AParent;
}

void SAT_Widget::setIndex(uint32_t AIndex)
{
    MIndex = AIndex;
}

//----------

SAT_WidgetOwner* SAT_Widget::getOwner()
{
    return MOwner;
}

SAT_Widget* SAT_Widget::getParent()
{
    return MParent;
}

uint32_t SAT_Widget::getIndex()
{
    return MIndex;
}

//----------

SAT_Widget* SAT_Widget::appendChild(SAT_Widget* AWidget)
{
    AWidget->MParent = this;
    uint32_t index = MChildren.size();
    AWidget->MIndex = index;
    if (!AWidget->MSkin) AWidget->MSkin = MSkin;
    MChildren.append(AWidget);
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
    MChildren.remove(AWidget);
}

uint32_t SAT_Widget::getNumChildren()
{
    return MChildren.size();
}

SAT_Widget* SAT_Widget::getChild(uint32_t AIndex)
{
    return MChildren[AIndex];
}

//----------

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

void SAT_Widget::setOpaque(bool AState)
{
    State.opaque = AState;
}

void SAT_Widget::setVisible(bool AState)
{
    State.visible = AState;
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
    MScale = AScale;
}

/*
    if AReplace is true, it will just replace the existing skin 
    else it will only set skin if it doesn't alreaduy have one
*/

void SAT_Widget::setSkin(SAT_Skin* ASkin, bool AReplace)
{
    if ((!MSkin) || AReplace)
    {
        MSkin = ASkin;
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
    return State.opaque;
}

bool SAT_Widget::isVisible()
{
    return State.visible;
}

sat_coord_t SAT_Widget::getScale()
{
    return MScale;
}

SAT_Skin* SAT_Widget::getSkin()
{
    return MSkin;
}



//----------

SAT_Rect SAT_Widget::getRect()
{
    return Recursive.rect;
}

SAT_Rect SAT_Widget::getClipRect()
{
    return Recursive.clip_rect;
}

SAT_Rect SAT_Widget::getContentRect()
{
    return Recursive.content_rect;
}

SAT_Widget* SAT_Widget::getOpaqueParent()
{
    return Recursive.opaque_parent;
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
            SAT_Rect widget_rect = widget->Recursive.rect;
            if (widget->State.active)
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

//------------------------------

void SAT_Widget::pushClip(SAT_PaintContext* AContext)
{
    if (Options.auto_clip)
    {
        SAT_Painter* painter= AContext->painter;
        SAT_Rect rect = getRect();
        painter->pushOverlappingClipRect(rect);
    }
}

void SAT_Widget::pushRecursiveClip(SAT_PaintContext* AContext)
{
    if (Options.auto_clip)
    {
        SAT_Painter* painter= AContext->painter;
        SAT_Rect rect = Recursive.clip_rect;
        painter->pushOverlappingClipRect(rect);
    }
}

void SAT_Widget::popClip(SAT_PaintContext* AContext)
{
    if (Options.auto_clip)
    {
        SAT_Painter* painter= AContext->painter;
        painter->popClipRect();

    }
}

//----------

sat_coord_t SAT_Widget::getPaintScale()
{
    SAT_Assert(MOwner);
    sat_coord_t scale = MOwner->do_widget_owner_get_scale(this);
    scale *= Recursive.scale;
    scale *= getScale();
    return scale;
}

void SAT_Widget::paintChildren(SAT_PaintContext* AContext)
{
    // if this widget is not visible, don't do anything..
    //if (!State.visible) return;
    
    uint32_t numchildren = MChildren.size();
    if (numchildren > 0)
    {
        for(uint32_t i=0; i<numchildren; i++)
        {
            SAT_Widget* widget = MChildren[i];
            //if (widget->Update.last_painted != AContext->current_frame)
            //{
                SAT_Rect widgetrect = widget->Recursive.rect;
                widgetrect.overlap(Recursive.rect);
                if (widgetrect.isNotEmpty())
                {
                    widget->on_widget_paint(AContext);
                    widget->Update.last_painted = AContext->current_frame;
                }
            //}
        }
    }
}

//------------------------------
// layout
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
    SAT_Assert(MOwner);

    sat_coord_t scale = MOwner->do_widget_owner_get_scale(this);
    sat_coord_t recursive_scale = Recursive.scale * getScale();
    scale *= recursive_scale;

    sat_coord_t w = MOwner->do_widget_owner_get_width(this);
    sat_coord_t h = MOwner->do_widget_owner_get_height(this);
    SAT_Rect root_rect = SAT_Rect(w,h);

    SAT_Rect rect = Recursive.rect;

    SAT_Rect inner_border = Layout.inner_border;
    inner_border.scale(scale);

    SAT_Point spacing = Layout.spacing;
    spacing.scale(scale);

    SAT_Rect parent_rect = rect;
    parent_rect.shrink(inner_border);

    SAT_Rect layout_rect = rect;
    layout_rect.shrink(inner_border);

    Recursive.content_rect = SAT_Rect( rect.x,rect.y, 0,0 );

    double layout_xcenter   = layout_rect.x + (layout_rect.w * 0.5);
    double layout_ycenter   = layout_rect.y + (layout_rect.h * 0.5);
    double stackx           = 0;
    double stacky           = 0;
    double stack_highest    = 0;
    double stack_widest     = 0;

    // ---

    for (uint32_t i=0; i<MChildren.size(); i++)
    {
        SAT_Widget* child = (SAT_Widget*)MChildren[i];
        SAT_Assert(child);

        SAT_Rect child_rect;

        bool need_realign = (child->State.visible || child->Options.realign_if_invisible);
        if (need_realign)
        {

            // --- relative ---

            if (child->Layout.relative)
            {
                if (child->Layout.relative == SAT_WIDGET_LAYOUT_RELATIVE_ROOT)
                {
                    child_rect = SAT_Rect(root_rect.w,root_rect.h,root_rect.w,root_rect.h);
                    child_rect.scale(child->MInitialRect);
                    child_rect.scale(0.01);
                }
                else if (child->Layout.relative == SAT_WIDGET_LAYOUT_RELATIVE_PARENT)
                {
                    child_rect = SAT_Rect(parent_rect.w,parent_rect.h,parent_rect.w,parent_rect.h);
                    child_rect.scale(child->MInitialRect);
                    child_rect.scale(0.01);
                }
                else if (child->Layout.relative == SAT_WIDGET_LAYOUT_RELATIVE_LAYOUT)
                {
                    child_rect = SAT_Rect(layout_rect.w,layout_rect.h,layout_rect.w,layout_rect.h);
                    child_rect.scale(child->MInitialRect);
                    child_rect.scale(0.01);
                }
                else // relative to current/self ??
                {
                    child_rect = SAT_Rect(rect.w,rect.h,rect.w,rect.h);
                    child_rect.scale(child->MInitialRect);
                    child_rect.scale(0.01);
                }
            }
            else
            {
                child_rect = child->MBaseRect;
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
            if (child->Layout.anchor & SAT_WIDGET_LAYOUT_ANCHOR_LEFT)               { xanchored = true; child_rect.x += layout_rect.x; }
            if (child->Layout.anchor & SAT_WIDGET_LAYOUT_ANCHOR_TOP)                { yanchored = true; child_rect.y += layout_rect.y; }
            if (child->Layout.anchor & SAT_WIDGET_LAYOUT_ANCHOR_RIGHT)              { xanchored = true; child_rect.x += (layout_rect.x2()  - child_rect.w); }
            if (child->Layout.anchor & SAT_WIDGET_LAYOUT_ANCHOR_BOTTOM)             { yanchored = true; child_rect.y += (layout_rect.y2()  - child_rect.h); }
            if (child->Layout.anchor & SAT_WIDGET_LAYOUT_ANCHOR_CENTER_HORIZONTAL)  { xanchored = true; child_rect.x += (layout_xcenter - (child_rect.w * 0.5)); }
            if (child->Layout.anchor & SAT_WIDGET_LAYOUT_ANCHOR_CENTER_VERTICAL)    { yanchored = true; child_rect.y += (layout_ycenter - (child_rect.h * 0.5)); }

            // --- stack ---

            if (child->Layout.stack & SAT_WIDGET_LAYOUT_STACK_HORIZONTAL)
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

            if (child->Layout.stack & SAT_WIDGET_LAYOUT_STACK_VERTICAL)
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

            if (child->Layout.stretch & SAT_WIDGET_LAYOUT_STRETCH_LEFT)        { child_rect.setX1( layout_rect.x   ); }
            if (child->Layout.stretch & SAT_WIDGET_LAYOUT_STRETCH_TOP)         { child_rect.setY1( layout_rect.y   ); }
            if (child->Layout.stretch & SAT_WIDGET_LAYOUT_STRETCH_RIGHT)       { child_rect.setX2( layout_rect.x2()); }
            if (child->Layout.stretch & SAT_WIDGET_LAYOUT_STRETCH_BOTTOM)      { child_rect.setY2( layout_rect.y2()); }

            // --- crop ---

            if (child->Layout.crop & SAT_WIDGET_LAYOUT_CROP_LEFT)           { layout_rect.setX1( child_rect.x2()); layout_rect.x += spacing.x; layout_rect.w -= spacing.x; }
            if (child->Layout.crop & SAT_WIDGET_LAYOUT_CROP_TOP)            { layout_rect.setY1( child_rect.y2()); layout_rect.y += spacing.y; layout_rect.h -= spacing.y; }
            if (child->Layout.crop & SAT_WIDGET_LAYOUT_CROP_RIGHT)          { layout_rect.setX2( child_rect.x   ); layout_rect.w -= spacing.x; }
            if (child->Layout.crop & SAT_WIDGET_LAYOUT_CROP_BOTTOM)         { layout_rect.setY2( child_rect.y   ); layout_rect.h -= spacing.y; }

            // --- stack end ---

            if (child->Layout.stack & SAT_WIDGET_LAYOUT_STACK_END)
            {
                if (child->Layout.stack & SAT_WIDGET_LAYOUT_STACK_VERTICAL)
                {
                    float w = (stackx + stack_widest + spacing.x);
                    layout_rect.x += w;
                    layout_rect.w -= w;
                }
                if (child->Layout.stack & SAT_WIDGET_LAYOUT_STACK_HORIZONTAL)
                {
                    float h = (stacky + stack_highest + spacing.y);
                    layout_rect.y += h;
                    layout_rect.h -= h;
                }
            }

            // --- min/max size ---

            double min_width  = child->Layout.minSize.w * scale;
            double min_height = child->Layout.minSize.h * scale;
            double max_width  = child->Layout.maxSize.w * scale;
            double max_height = child->Layout.maxSize.h * scale;

            if ((min_width  >= 0) && (child_rect.w < min_width )) child_rect.w = min_width;
            if ((min_height >= 0) && (child_rect.h < min_height)) child_rect.h = min_height;
            if ((max_width  >= 0) && (child_rect.w > max_width )) child_rect.w = max_width;
            if ((max_height >= 0) && (child_rect.h > max_height)) child_rect.h = max_height;

            // --- content rect ---

            Recursive.content_rect.combine(child_rect);

            // --- outer border ---

            SAT_Rect outer_border = child->Layout.outer_border;
            outer_border.scale(scale);
            child_rect.shrink(outer_border);

            // --- post-align ---

            child_rect = child->on_widget_post_align(child_rect);

            // --- set child properties ---

            child->Recursive.rect       = child_rect;
            child->Recursive.scale      = recursive_scale;

            child->Recursive.clip_rect  = child_rect;
            child->Recursive.clip_rect.overlap(Recursive.rect);

            if (child->State.opaque)
            {
                SAT_PRINT("child %s = opaque\n",child->getName());
                child->Recursive.opaque_parent = child;
            }
            else
            {
                child->Recursive.opaque_parent = Recursive.opaque_parent;
                SAT_PRINT("child %s = not opaque (opaque_parent %s\n",child->getName(),Recursive.opaque_parent->getName());
            }

            if (!child->MSkin) child->MSkin = MSkin;

            // --- recursive ---

            child->on_widget_realign();

            /*
                // scale the widget depending on its content...
                if (child_layout & SAT_WIDGET_LAYOUT_CONTENT_SIZE)
                {
                    SAT_Rect child_content = child->getContentRect();
                    child->Recursive.rect = child_content;
                }
            */

        } // need_realign

        else
        {
            // child->State.visible and child->Options.realign_if_invisible is false
            child->setChildrenVisible(false);
        }

    } // for

    Recursive.content_rect.w += inner_border.w;
    Recursive.content_rect.h += inner_border.h;
}

//------------------------------
// interactive
//------------------------------

void SAT_Widget::setActive(bool AState)
{
    State.active = AState;
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
    State.enabled = AState;
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
    return State.active;
}

bool SAT_Widget::isEnabled()
{
    return State.enabled;
}

//------------------------------
// value
//------------------------------

sat_param_t SAT_Widget::getValue(uint32_t AIndex)
{
    return MValue;
}

SAT_Parameter* SAT_Widget::getParameter(uint32_t AIndex)
{
    return MParameter;
}

//----------

void SAT_Widget::setValue(sat_param_t AValue, uint32_t AIndex)
{
    MValue = AValue;
}

void SAT_Widget::setParameter(SAT_Parameter* AParameter, uint32_t AIndex)
{
    MParameter = AParameter;
}

//------------------------------
// on_
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
    if (!State.visible) return;
    pushClip(AContext);
    //pushRecursiveClip(AContext);
    paintChildren(AContext);
    popClip(AContext);
}

void SAT_Widget::on_widget_pre_paint(SAT_PaintContext* AContext)
{
}

void SAT_Widget::on_widget_post_paint(SAT_PaintContext* AContext)
{
}

//------------------------------
//
//------------------------------

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

//------------------------------
//
//------------------------------

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

void SAT_Widget::on_widget_key_press(uint32_t AKey, uint32_t AChar, uint32_t AState, uint32_t ATime)
{
}

void SAT_Widget::on_widget_key_release(uint32_t AKey, uint32_t AChar, uint32_t AState, uint32_t ATime)
{
}

//------------------------------
//
//------------------------------

void SAT_Widget::on_widget_mouse_enter(SAT_Widget* AFrom, int32_t AXpos, int32_t AYpos, uint32_t ATime)
{
    if (Options.auto_redraw_hover) do_widget_redraw(this);
}

void SAT_Widget::on_widget_mouse_leave(SAT_Widget* ATo, int32_t AXpos, int32_t AYpos, uint32_t ATime)
{
    if (Options.auto_redraw_hover) do_widget_redraw(this);
}


//------------------------------
// do_
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
