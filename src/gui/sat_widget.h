#pragma once

#include "base/sat_base.h"
#include "gui/painter/sat_paint_context.h"
#include "gui/widget/sat_widget_owner.h"
#include "gui/sat_painter.h"
#include "gui/sat_skin.h"

class SAT_AnimChain;
class SAT_KeyboardEvent;
class SAT_KeyboardGesture;
class SAT_MouseEvent;
class SAT_MouseGesture;
class SAT_Parameter;

class SAT_Widget;
typedef SAT_Array<SAT_Widget*> SAT_WidgetArray;

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

struct SAT_WidgetLayout
{
    uint32_t    anchor                  = SAT_WIDGET_LAYOUT_ANCHOR_CURRENT | SAT_WIDGET_LAYOUT_ANCHOR_TOP_LEFT;
    uint32_t    stretch                 = SAT_WIDGET_LAYOUT_STRETCH_CURRENT | SAT_WIDGET_LAYOUT_STRETCH_NONE;
    uint32_t    crop                    = SAT_WIDGET_LAYOUT_CROP_NONE;
    uint32_t    relative                = SAT_WIDGET_LAYOUT_RELATIVE_NONE;
    uint32_t    stack                   = SAT_WIDGET_LAYOUT_STACK_CURRENT | SAT_WIDGET_LAYOUT_STACK_NONE;
    SAT_Rect    innerBorder             = {};
    SAT_Rect    outerBorder             = {};
    SAT_Point   spacing                 = {};
    uint32_t    limit                   = SAT_WIDGET_LAYOUT_LIMIT_NONE;
    SAT_Rect    minimum                 = {-1,-1,-1,-1};
    SAT_Rect    maximum                 = {-1,-1,-1,-1};
 // SAT_Point   scrollOffset            = {0,0};        // scrollbox..
 // SAT_Rect    animRect                = {0,0,1,1};    // x,y = offset, w/h = scale.. temp, while animating
 // SAT_Rect    postRect                = {};           // x,y = offset, w/h = addition.. movable, sizable widgets
    //----------
    SAT_Rect    rect                    = {};
    sat_coord_t scale                   = 1.0;
    //----------
    SAT_Rect    baseRect                = {};
    SAT_Rect    initialRect             = {};
    SAT_Rect    contentRect             = {};
    sat_coord_t recursiveScale          = 1.0;
    SAT_Rect    recursiveClipRect       = {};
    SAT_Widget* recursiveOpaqueParent   = nullptr;
};

struct SAT_WidgetOptions
{
    bool        clip                    = true;
    bool        realignIfInvisible      = false;
    uint32_t    wantMouseEvents         = SAT_MOUSE_EVENT_NONE;
    uint32_t    wantKeyboardEvents      = SAT_KEYBOARD_EVENT_NONE;
    uint32_t    wantMouseGestures       = SAT_MOUSE_GESTURE_NONE;
    uint32_t    wantKeyboardGestures    = SAT_KEYBOARD_GESTURE_NONE;
};

struct SAT_WidgetState
{
    bool        active                  = true;
    bool        visible                 = true;
    bool        opaque                  = true;
    bool        captured                = false;
    // bool     hovering                = false;
    // bool     enabled                 = true;
    // bool     interact                = false;
    // bool     highlighted             = false;
};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_Widget
{

    friend class SAT_WidgetWindow;
    
    public:

        SAT_Widget(SAT_Rect ARect);
        virtual ~SAT_Widget();

    public: // base

        virtual void                setName(const char* AName);
        virtual void                setHint(const char* AHint);
        virtual void                setTooltip(const char* ATooltip);
        virtual const char*         getName();
        virtual const char*         getHint();
        virtual const char*         getTooltip();
        virtual const char*         getTypeName();

    public: // hierarchy

        virtual void                setParent(SAT_Widget* AParent);
        virtual void                setIndex(uint32_t AIndex);
        virtual SAT_WidgetOwner*    getOwner();
        virtual SAT_Widget*         getParent();
        virtual uint32_t            getIndex();
        virtual SAT_Widget*         appendChild(SAT_Widget* AWidget);
        virtual void                deleteChildren();
        virtual void                removeChild(SAT_Widget* AWidget, bool ADelete=true);
        virtual uint32_t            getNumChildren();
        virtual SAT_Widget*         getChild(uint32_t AIndex);
        virtual SAT_Widget*         findChild(const char* AName);
        virtual void                showOwner(SAT_WidgetOwner* AOwner);
        virtual void                hideOwner(SAT_WidgetOwner* AOwner);

    public: // visual

        virtual void                setOpaque(bool AState=true);
        virtual void                setVisible(bool AState=true);
        virtual void                setChildrenVisible(bool AState=true);
        virtual void                setScale(sat_coord_t AScale);
        virtual void                setSkin(SAT_Skin* ASkin, bool AReplace=true);
        virtual void                setChildrenSkin(SAT_Skin* ASkin, bool AReplace=true);
        virtual void                setRect(SAT_Rect ARect);
      //virtual void                setBaseRect(SAT_Rect ARect);
        virtual bool                isOpaque();
        virtual bool                isVisible();
        virtual sat_coord_t         getScale();
        virtual SAT_Skin*           getSkin();
        virtual SAT_Rect            getRect();
        virtual SAT_Rect            getClipRect();
        virtual SAT_Rect            getContentRect();
        virtual SAT_Widget*         getOpaqueParent();
        virtual SAT_Widget*         findChildAt(int32_t AXpos, int32_t AYpos);
        virtual void                pushClip(SAT_PaintContext* AContext);
        virtual void                pushRecursiveClip(SAT_PaintContext* AContext);
        virtual void                popClip(SAT_PaintContext* AContext);
        virtual sat_coord_t         getPaintScale();
        virtual uint32_t            getPaintState();
        virtual void                paintChildren(SAT_PaintContext* AContext);
        virtual void                paintWidget(SAT_PaintContext* AContext, SAT_Widget* AWidget);

    public: // layout

        virtual void                realignChildren();

    public: // interactive

        virtual void                setActive(bool AState=true);
        virtual void                setChildrenActive(bool AState=true);
        virtual bool                isActive();
     // virtual void                setEnabled(bool AState=true);
     // virtual void                setChildrenEnabled(bool AState=true);
     // virtual bool                isEnabled();

    public: // value

        virtual uint32_t            getValueIndex();
        virtual sat_param_t         getValue();
        virtual sat_param_t         getValue(uint32_t AIndex);
        virtual SAT_Parameter*      getParameter();
        virtual SAT_Parameter*      getParameter(uint32_t AIndex);
        virtual void                setValueIndex(uint32_t AIndex);
        virtual void                setValue(sat_param_t AValue);
        virtual void                setValue(sat_param_t AValue, uint32_t AIndex);
        virtual void                setParameter(SAT_Parameter* AParameter);
        virtual void                setParameter(SAT_Parameter* AParameter, uint32_t AIndex);

    public: // on_

        virtual void                on_widget_show(SAT_WidgetOwner* AOwner);
        virtual void                on_widget_hide(SAT_WidgetOwner* AOwner);
        virtual void                on_widget_paint(SAT_PaintContext* AContext);
        virtual void                on_widget_pre_paint(SAT_PaintContext* AContext);
        virtual void                on_widget_post_paint(SAT_PaintContext* AContext);
        virtual void                on_widget_realign();
        virtual SAT_Rect            on_widget_pre_align(SAT_Rect ARect);
        virtual SAT_Rect            on_widget_post_align(SAT_Rect ARect);
        virtual void                on_widget_timer(uint32_t ATimerId, double ADelta);
        virtual void                on_widget_anim(uint32_t AId, uint32_t AType, uint32_t ANumValues, double* AValues);
        virtual void                on_widget_notify(SAT_Widget* AWidget, uint32_t AType=SAT_WIDGET_NOTIFY_NONE, intptr_t AValue=0);
        virtual uint32_t            on_widget_mouse_event(SAT_MouseEvent* AEvent);
        virtual void                on_widget_mouse_gesture(SAT_MouseGesture* AGesture);
        virtual uint32_t            on_widget_keyboard_event(SAT_KeyboardEvent* AEvent);
        virtual void                on_widget_keyboard_gesture(SAT_KeyboardGesture* AGesture);

    public: // do_

        virtual void                do_widget_update(SAT_Widget* AWidget, uint32_t AIndex=0);
        virtual void                do_widget_realign(SAT_Widget* AWidget, uint32_t AMode=SAT_WIDGET_REALIGN_PARENT);
        virtual void                do_widget_redraw(SAT_Widget* AWidget, uint32_t AMode=SAT_WIDGET_REDRAW_SELF);
        virtual void                do_widget_anim(SAT_Widget* AWidget, SAT_AnimChain* AChain);
        virtual void                do_widget_notify(SAT_Widget* AWidget, uint32_t AType=SAT_WIDGET_NOTIFY_NONE, int32_t AValue=0);
        virtual void                do_widget_hint(SAT_Widget* AWidget, uint32_t AType, const char* AHint);
        virtual void                do_widget_modal(SAT_Widget* AWidget);
        virtual void                do_widget_cursor(SAT_Widget* AWidget, int32_t ACursor);
        virtual void                do_widget_capture_mouse(SAT_Widget* AWidget);
        virtual void                do_widget_capture_keyboard(SAT_Widget* AWidget);

    public: 

        SAT_WidgetLayout    Layout                              = {};
        SAT_WidgetOptions   Options                             = {};
        SAT_WidgetState     State                               = {};

    protected:

        const char*         MTypeName                           = "SAT_Widget";
        const char*         MName                               = "";
        const char*         MHint                               = "";
        const char*         MTooltip                            = "";
        uint32_t            MCursor                             = SAT_MOUSE_CURSOR_DEFAULT;
        SAT_Skin*           MSkin                               = nullptr;

        SAT_WidgetOwner*    MOwner                              = nullptr;
        SAT_Widget*         MParent                             = nullptr;
        uint32_t            MIndex                              = 0;
        SAT_WidgetArray     MChildren                           = {};

        uint32_t            MValueIndex                         = 0;
        sat_param_t         MValues[SAT_WIDGET_NUM_VALUES]      = {};
        SAT_Parameter*      MParameters[SAT_WIDGET_NUM_VALUES]  = {};

        uint32_t            MPrevPainted                        = SAT_UINT32_MAX;
        // uint32_t         MPrevRedrawn                        = SAT_UINT32_MAX;
        // uint32_t         MPrevRealigned                      = SAT_UINT32_MAX;
        // uint32_t         MPrevUpdated                        = SAT_UINT32_MAX;

};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

SAT_Widget::SAT_Widget(SAT_Rect ARect)
{
    MTypeName = "SAT_Widget";
    Layout.baseRect = ARect;
    Layout.initialRect = ARect;
    MSkin = SAT.GUI->SKINS.find("Default");
    Layout.rect = ARect;
    Layout.contentRect = ARect;
    Layout.recursiveClipRect = ARect;
    Layout.recursiveOpaqueParent = this;
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
    MName = AName;
}

void SAT_Widget::setHint(const char* AHint)
{
    MHint = AHint;
}

void SAT_Widget::setTooltip(const char* ATooltip)
{
    MTooltip = ATooltip;
}

const char* SAT_Widget::getName()
{
    return MName;
}

const char* SAT_Widget::getHint()
{
    return MHint;
}

const char* SAT_Widget::getTooltip()
{
    return MTooltip;
}

const char* SAT_Widget::getTypeName()
{
    return MTypeName;
}

//------------------------------
//
// hierarchy
//
//------------------------------

void SAT_Widget::setParent(SAT_Widget* AParent)
{
    MParent = AParent;
}

void SAT_Widget::setIndex(uint32_t AIndex)
{
    MIndex = AIndex;
}

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

SAT_Widget* SAT_Widget::appendChild(SAT_Widget* AWidget)
{
    //AWidget->MParent = this;
    AWidget->setParent(this);
    uint32_t index = MChildren.size();
    //AWidget->MIndex = index;
    AWidget->setIndex(index);
    if (!AWidget->getSkin()) AWidget->setSkin(MSkin);
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

void SAT_Widget::removeChild(SAT_Widget* AWidget, bool ADelete)
{
    AWidget->setParent(nullptr);
    MChildren.remove(AWidget);
    if (ADelete) delete AWidget;
}

uint32_t SAT_Widget::getNumChildren()
{
    return MChildren.size();
}

SAT_Widget* SAT_Widget::getChild(uint32_t AIndex)
{
    return MChildren[AIndex];
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

void SAT_Widget::showOwner(SAT_WidgetOwner* AOwner)
{
    on_widget_show(AOwner);
    MOwner = AOwner;
    uint32_t num = getNumChildren();
    for (uint32_t i=0; i<num; i++)
    {
        SAT_Widget* widget = getChild(i);
        widget->showOwner(AOwner);
    }
}

void SAT_Widget::hideOwner(SAT_WidgetOwner* AOwner)
{
    on_widget_hide(AOwner);
    MOwner = nullptr;
    uint32_t num = getNumChildren();
    for (uint32_t i=0; i<num; i++)
    {
        SAT_Widget* widget = getChild(i);
        widget->hideOwner(AOwner);
    }
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
    Layout.scale = AScale;
}

// if AReplace is true, it will just replace the existing skin 
// else it will only set skin if it doesn't already have one

void SAT_Widget::setSkin(SAT_Skin* ASkin, bool AReplace)
{
    if (!MSkin || AReplace)
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

// ARect = screen-space
// todo: convert back to widget-space & set base_rect

void SAT_Widget::setRect(SAT_Rect ARect)
{
    Layout.rect = ARect;
}

// ARect = widget-space..
// unaffected by alignment/layout

// void SAT_Widget::setBaseRect(SAT_Rect ARect)
// {
//     MBaseRect = ARect;
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
    return Layout.scale;
}

SAT_Skin* SAT_Widget::getSkin()
{
    return MSkin;
}

//----------

SAT_Rect SAT_Widget::getRect()
{
    return Layout.rect;
}

SAT_Rect SAT_Widget::getClipRect()
{
    return Layout.recursiveClipRect;
}

SAT_Rect SAT_Widget::getContentRect()
{
    return Layout.contentRect;
}

SAT_Widget* SAT_Widget::getOpaqueParent()
{
    return Layout.recursiveOpaqueParent;
}

// returns this if no child widgets at x,y
// for a window, no widgets means the window itself
// (also when outside of the window)

// todo:
// findVisibleChildAt?
// findActiveChildAt
// arg uint32_t AMask.. switch, check Options, etc..

SAT_Widget* SAT_Widget::findChildAt(int32_t AXpos, int32_t AYpos)
{
    uint32_t num = getNumChildren();
    if (num > 0)
    {
        for (int32_t i=num-1; i>=0; i--)
        {
            SAT_Widget* widget = getChild(i);
            SAT_Rect widget_rect = widget->getRect();
            if (widget_rect.contains(AXpos,AYpos))
            {
                // TODO: argument: uint32_t AMask?
                bool widget_is_visible = widget->State.visible;
                // widget_is_visible |= widget->Options.visibleIfHovering;
                if (widget_is_visible)
                {
                    return widget->findChildAt(AXpos,AYpos);
                }
            }
        }
    }
    return this;
}

void SAT_Widget::pushClip(SAT_PaintContext* AContext)
{
    if (Options.clip)
    {
        SAT_Painter* painter= AContext->painter;
        SAT_Rect rect = getRect();
        painter->pushOverlappingClipRect(rect);
    }
}

void SAT_Widget::pushRecursiveClip(SAT_PaintContext* AContext)
{
    if (Options.clip)
    {
        SAT_Painter* painter= AContext->painter;
        SAT_Rect rect = Layout.recursiveClipRect;
        painter->pushOverlappingClipRect(rect);
    }
}

void SAT_Widget::popClip(SAT_PaintContext* AContext)
{
    if (Options.clip)
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
    scale *= Layout.recursiveScale;
    scale *= getScale();
    return scale;
}

uint32_t SAT_Widget::getPaintState()
{
    uint32_t state = SAT_SKIN_STATE_NORMAL;
    // if (State.hovering) state |= SAT_SKIN_STATE_HOVERING;
    // if (!State.enabled) state |= SAT_SKIN_STATE_DISABLED;
    // if (State.highlighted) state |= SAT_SKIN_STATE_HIGHLIGHTED;
    // if (State.interact) state |= SAT_SKIN_STATE_INTERACT;
    return state;
}

// assumes widget is visible, and clipping is set up
// see: State.visible, pushRecursiveClip/popClip

void SAT_Widget::paintChildren(SAT_PaintContext* AContext)
{
    uint32_t numchildren = MChildren.size();
    if (numchildren > 0)
    {
        for(uint32_t i=0; i<numchildren; i++)
        {
            SAT_Widget* child = (SAT_Widget*)MChildren[i];
            // skip child if it's outside current widget (its parent) rect.. scroll boxes, etc..
            SAT_Rect child_rect = child->getRect();
            if (child->Layout.rect.intersects(Layout.rect))
            {
                paintWidget(AContext,child);
            }
        }
    }
}

void SAT_Widget::paintWidget(SAT_PaintContext* AContext, SAT_Widget* AWidget)
{
    // skip if widget doesn't intersect update_rect..
    if (!AWidget->Layout.rect.intersects(AContext->update_rect)) return;
    if (AWidget->State.visible)
    {
        AWidget->pushRecursiveClip(AContext);
        AWidget->on_widget_paint(AContext);
        AWidget->popClip(AContext);
        AWidget->MPrevPainted = AContext->current_frame;
    }
}

//------------------------------
//
// layout
//
//------------------------------

// realign all child widgets (recursively)

void SAT_Widget::realignChildren()
{
    SAT_Assert(MOwner);

    sat_coord_t scale = MOwner->do_widget_owner_get_scale(this);
    sat_coord_t recursive_scale = Layout.recursiveScale * getScale();
    scale *= recursive_scale;

    sat_coord_t w = MOwner->do_widget_owner_get_width(this);
    sat_coord_t h = MOwner->do_widget_owner_get_height(this);
    SAT_Rect root_rect = SAT_Rect(w,h);

    //SAT_Rect widget_rect = Layout.rect;
    SAT_Rect widget_rect = Layout.baseRect;

    SAT_Rect inner_border = Layout.innerBorder;
    inner_border.scale(scale);

    SAT_Point spacing = Layout.spacing;
    spacing.scale(scale);

    SAT_Rect parent_rect = widget_rect;
    parent_rect.shrink(inner_border);

    SAT_Rect current_rect = widget_rect;
    current_rect.shrink(inner_border);

    Layout.contentRect = SAT_Rect( widget_rect.x,widget_rect.y, 0,0 );

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

        bool need_realign = (child->State.visible || child->Options.realignIfInvisible);
        if (need_realign)
        {

            // --- relative pos/size ---
            // (percentages)

            switch(child->Layout.relative)
            {
                case SAT_WIDGET_LAYOUT_RELATIVE_NONE:
                    child_rect = child->Layout.baseRect;
                    child_rect.scale(scale);
                    break;
                case SAT_WIDGET_LAYOUT_RELATIVE_PARENT:
                    child_rect = SAT_Rect(parent_rect.w,parent_rect.h,parent_rect.w,parent_rect.h);
                    child_rect.scale(child->Layout.initialRect);
                    child_rect.scale(0.01);
                case SAT_WIDGET_LAYOUT_RELATIVE_CURRENT:
                    child_rect = SAT_Rect(current_rect.w,current_rect.h,current_rect.w,current_rect.h);
                    child_rect.scale(child->Layout.initialRect);
                    child_rect.scale(0.01);
                case SAT_WIDGET_LAYOUT_RELATIVE_ROOT:
                    child_rect = SAT_Rect(root_rect.w,root_rect.h,root_rect.w,root_rect.h);
                    child_rect.scale(child->Layout.initialRect);
                    child_rect.scale(0.01);
                default:
                    SAT_PRINT("Error! unknown layout relative mode: %i\n",child->Layout.relative);
                    break;
            };

            // --- TODO: anim / manual movement ---
            
            // SAT_Rect manual = child->MManualAnim;
            // manual.scale(scale);
            // child_rect.add(manual);
            // //child_rect.add(child->MManuallyMoved);

            // --- pre-align ---

            child_rect = child->on_widget_pre_align(child_rect);

            // child_rect.add(child->MManuallyMoved);

            // --- anchor ---

            SAT_Rect anchor_rect;
            switch (child->Layout.anchor & 0xff000000)
            {
                case SAT_WIDGET_LAYOUT_ANCHOR_CURRENT:
                    anchor_rect = current_rect;
                    break;
                case SAT_WIDGET_LAYOUT_ANCHOR_PARENT:
                    anchor_rect = parent_rect;
                    break;
                default:
                    SAT_PRINT("Error: unknown layout anchor mode: %i\n",child->Layout.anchor & 0xff000000);
                    break;
            };

            bool xanchored = false;
            bool yanchored = false;
            double anchor_xcenter = anchor_rect.x + (anchor_rect.w * 0.5);
            double anchor_ycenter = anchor_rect.y + (anchor_rect.h * 0.5);
            if (child->Layout.anchor & SAT_WIDGET_LAYOUT_ANCHOR_LEFT)               { xanchored = true; child_rect.x += anchor_rect.x; }
            if (child->Layout.anchor & SAT_WIDGET_LAYOUT_ANCHOR_TOP)                { yanchored = true; child_rect.y += anchor_rect.y; }
            if (child->Layout.anchor & SAT_WIDGET_LAYOUT_ANCHOR_RIGHT)              { xanchored = true; child_rect.x += (anchor_rect.x2()  - child_rect.w); }
            if (child->Layout.anchor & SAT_WIDGET_LAYOUT_ANCHOR_BOTTOM)             { yanchored = true; child_rect.y += (anchor_rect.y2()  - child_rect.h); }
            if (child->Layout.anchor & SAT_WIDGET_LAYOUT_ANCHOR_CENTER_HORIZONTAL)  { xanchored = true; child_rect.x += (anchor_xcenter - (child_rect.w * 0.5)); }
            if (child->Layout.anchor & SAT_WIDGET_LAYOUT_ANCHOR_CENTER_VERTICAL)    { yanchored = true; child_rect.y += (anchor_ycenter - (child_rect.h * 0.5)); }

            // --- stack ---

            SAT_Rect stack_rect;
            switch (child->Layout.stack & 0xff000000)
            {
                case SAT_WIDGET_LAYOUT_STACK_CURRENT:
                    stack_rect = current_rect;
                    break;
                case SAT_WIDGET_LAYOUT_STACK_PARENT:
                    stack_rect = parent_rect;
                    break;
                default:
                    SAT_PRINT("Error! unknown layout stack mode: %i\n",child->Layout.stack & 0xff000000);
                    break;
            }

            if (child->Layout.stack & SAT_WIDGET_LAYOUT_STACK_HORIZONTAL)
            {
                if ((stackx + child_rect.w) >= stack_rect.w)
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
                child_rect.x += (stack_rect.x + stackx);
                child_rect.y += (stack_rect.y + stacky);
                stackx += child_rect.w + spacing.x;
                if (child_rect.h > stack_highest) stack_highest = child_rect.h;
            }

            if (child->Layout.stack & SAT_WIDGET_LAYOUT_STACK_VERTICAL)
            {
                if ((stacky + child_rect.h) >= stack_rect.h)
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
                child_rect.x += (stack_rect.x + stackx);
                child_rect.y += (stack_rect.y + stacky);
                stacky += child_rect.h + spacing.y;
                if (child_rect.w > stack_widest) stack_widest = child_rect.w;
            }

            if (!xanchored) child_rect.x += widget_rect.x;
            if (!yanchored) child_rect.y += widget_rect.y;

            // --- stretch ---

            SAT_Rect stretch_rect;
            switch (child->Layout.stretch & 0xff000000)
            {
                case SAT_WIDGET_LAYOUT_STRETCH_CURRENT:
                    stretch_rect = current_rect;
                    break;
                case SAT_WIDGET_LAYOUT_STRETCH_PARENT:
                    stretch_rect = parent_rect;
                    break;
                //case SAT_WIDGET_LAYOUT_STRETCH_ROOT:
                //    stretch_rect = root_rect;
                //    break;
                default:
                    SAT_PRINT("Error: unknown layout stretch mode: %i\n",child->Layout.stretch & 0xff000000);
                    break;
            };
            if (child->Layout.stretch & SAT_WIDGET_LAYOUT_STRETCH_LEFT)     { child_rect.setX1( stretch_rect.x   ); }
            if (child->Layout.stretch & SAT_WIDGET_LAYOUT_STRETCH_TOP)      { child_rect.setY1( stretch_rect.y   ); }
            if (child->Layout.stretch & SAT_WIDGET_LAYOUT_STRETCH_RIGHT)    { child_rect.setX2( stretch_rect.x2()); }
            if (child->Layout.stretch & SAT_WIDGET_LAYOUT_STRETCH_BOTTOM)   { child_rect.setY2( stretch_rect.y2()); }

            // --- crop ---

            if (child->Layout.crop & SAT_WIDGET_LAYOUT_CROP_LEFT)           { current_rect.setX1( child_rect.x2()); current_rect.x += spacing.x; current_rect.w -= spacing.x; }
            if (child->Layout.crop & SAT_WIDGET_LAYOUT_CROP_TOP)            { current_rect.setY1( child_rect.y2()); current_rect.y += spacing.y; current_rect.h -= spacing.y; }
            if (child->Layout.crop & SAT_WIDGET_LAYOUT_CROP_RIGHT)          { current_rect.setX2( child_rect.x   ); current_rect.w -= spacing.x; }
            if (child->Layout.crop & SAT_WIDGET_LAYOUT_CROP_BOTTOM)         { current_rect.setY2( child_rect.y   ); current_rect.h -= spacing.y; }

            // --- stack end ---

            if (child->Layout.stack & SAT_WIDGET_LAYOUT_STACK_END)
            {
                if (child->Layout.stack & SAT_WIDGET_LAYOUT_STACK_VERTICAL)
                {
                    float w = (stackx + stack_widest + spacing.x);
                    current_rect.x += w;
                    current_rect.w -= w;
                }
                if (child->Layout.stack & SAT_WIDGET_LAYOUT_STACK_HORIZONTAL)
                {
                    float h = (stacky + stack_highest + spacing.y);
                    current_rect.y += h;
                    current_rect.h -= h;
                }
            }

            // --- pos/size limit ---
            // (percentages, unless _pixels)


            SAT_Rect limit_scale;
            switch (child->Layout.limit)
            {
                case SAT_WIDGET_LAYOUT_LIMIT_NONE:
                    limit_scale.set(1.0);
                    break;
                case SAT_WIDGET_LAYOUT_LIMIT_PIXELS:
                    limit_scale.set(scale);
                    break;
                case SAT_WIDGET_LAYOUT_LIMIT_BASE:
                    limit_scale = Layout.baseRect;
                    limit_scale.scale(scale * 0.01);
                    break;
                case SAT_WIDGET_LAYOUT_LIMIT_PARENT:
                    limit_scale = parent_rect;
                    limit_scale.scale(scale * 0.01);
                    break;
                case SAT_WIDGET_LAYOUT_LIMIT_CURRENT:
                    limit_scale = current_rect;
                    limit_scale.scale(scale * 0.01);
                    break;
                case SAT_WIDGET_LAYOUT_LIMIT_ROOT:
                    limit_scale = root_rect;
                    limit_scale.scale(scale * 0.01);
                    break;
                default:
                    SAT_PRINT("Error: unknown layout limit mode: %i\n",child->Layout.limit);
                    break;
            }
            SAT_Rect limit_min = child->Layout.minimum;
            SAT_Rect limit_max = child->Layout.maximum;
            limit_min.scale(limit_scale);
            limit_max.scale(limit_scale);
            if ((limit_min.x >= 0) && (child_rect.x < limit_min.x)) child_rect.x = limit_min.x;
            if ((limit_min.y >= 0) && (child_rect.y < limit_min.y)) child_rect.y = limit_min.y;
            if ((limit_min.w >= 0) && (child_rect.w < limit_min.w)) child_rect.w = limit_min.w;
            if ((limit_min.h >= 0) && (child_rect.h < limit_min.h)) child_rect.h = limit_min.h;
            if ((limit_max.x >= 0) && (child_rect.x > limit_max.x)) child_rect.x = limit_max.x;
            if ((limit_max.y >= 0) && (child_rect.y > limit_max.y)) child_rect.y = limit_max.y;
            if ((limit_max.w >= 0) && (child_rect.w > limit_max.w)) child_rect.w = limit_max.w;
            if ((limit_max.h >= 0) && (child_rect.h > limit_max.h)) child_rect.h = limit_max.h;
            
            // --- content rect ---

            Layout.contentRect.combine(child_rect);

            // --- outer border ---

            SAT_Rect outer_border = child->Layout.outerBorder;
            outer_border.scale(scale);
            child_rect.shrink(outer_border);

            // --- post-align ---

            child_rect = child->on_widget_post_align(child_rect);

            // --- set child properties ---

            //SAT_PRINT("%s : %.f,%.f, %.f,%.f\n",child->getName(),child_rect.x,child_rect.y,child_rect.w,child_rect.h);

            child->Layout.rect = child_rect;
            child->Layout.recursiveScale = recursive_scale;

            child->Layout.recursiveClipRect = child_rect;
            child->Layout.recursiveClipRect.overlap(Layout.recursiveClipRect);  // overlap(widget_rect);

            if (child->State.opaque) child->Layout.recursiveOpaqueParent = child;
            else child->Layout.recursiveOpaqueParent = Layout.recursiveOpaqueParent;

            if (!child->MSkin) child->MSkin = MSkin;

            // --- recursive ---

            child->on_widget_realign();

            /*
                // scale the widget depending on its content...
                if (child_layout & SAT_WIDGET_LAYOUT_CONTENT_SIZE)
                {
                    SAT_Rect child_content = child->getContentRect();
                    child->Layout.rect = child_content;
                }
            */

        } // need_realign

        else
        {

            // set all children invisible, in case we try to draw some sub-widgets
            // (modulated parameters, etc)..

            //SAT_PRINT("%s not visible, setting all childrens invisible too\n",child->getName());
            child->setChildrenVisible(false);

            // we can't click an invisible widdget.. but we won't receive hover events either..
            // child->setChildrenActive(false);
        }

    } // for

    Layout.contentRect.w += inner_border.w;
    Layout.contentRect.h += inner_border.h;

}

//------------------------------
//
// interactive
//
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

bool SAT_Widget::isActive()
{
    return State.active;
}

// void SAT_Widget::setEnabled(bool AState)
// {
//     State.enabled = AState;
//     setChildrenEnabled(AState);
// }

// void SAT_Widget::setChildrenEnabled(bool AState)
// {
//     uint32_t num = getNumChildren();
//     for (uint32_t i=0; i<num; i++)
//     {
//         SAT_Widget* widget = getChild(i);
//         widget->setEnabled(AState);
//     }
// }

// bool SAT_Widget::isEnabled()
// {
//     return State.enabled;
// }

//------------------------------
//
// value
//
//------------------------------

uint32_t SAT_Widget::getValueIndex()
{
    return MValueIndex;
}

sat_param_t SAT_Widget::getValue()
{
    return MValues[MValueIndex];
}

sat_param_t SAT_Widget::getValue(uint32_t AIndex)
{
    return MValues[AIndex];
}

SAT_Parameter* SAT_Widget::getParameter()
{
    return MParameters[MValueIndex];
}

SAT_Parameter* SAT_Widget::getParameter(uint32_t AIndex)
{
    return MParameters[AIndex];
}

//----------

void SAT_Widget::setValueIndex(uint32_t AIndex)
{
    MValueIndex = AIndex;
}

void SAT_Widget::setValue(sat_param_t AValue)
{
    MValues[MValueIndex] = AValue;
}

void SAT_Widget::setValue(sat_param_t AValue, uint32_t AIndex)
{
    MValues[AIndex] = AValue;
}

void SAT_Widget::setParameter(SAT_Parameter* AParameter)
{
    MParameters[MValueIndex] = AParameter;
}

void SAT_Widget::setParameter(SAT_Parameter* AParameter, uint32_t AIndex)
{
    MParameters[AIndex] = AParameter;
}

//------------------------------
//
// on_
//
//------------------------------

// see showOwner
void SAT_Widget::on_widget_show(SAT_WidgetOwner* AOwner)
{
}

// see hideOwner
void SAT_Widget::on_widget_hide(SAT_WidgetOwner* AOwner)
{
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

// called before calculating new rect
// here we can remember the starting rect, prepare things..

SAT_Rect SAT_Widget::on_widget_pre_align(SAT_Rect ARect)
{
    return ARect;
}

// called after new rect has been calculated
// we can do some final adjustments, or undo things..

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

void SAT_Widget::on_widget_notify(SAT_Widget* AWidget, uint32_t AType, intptr_t AValue)
{
}

uint32_t SAT_Widget::on_widget_mouse_event(SAT_MouseEvent* AEvent)
{
    return SAT_MOUSE_EVENT_RESPONSE_NONE;
}

void SAT_Widget::on_widget_mouse_gesture(SAT_MouseGesture* AGesture)
{
}

uint32_t SAT_Widget::on_widget_keyboard_event(SAT_KeyboardEvent* AEvent)
{
    return SAT_KEYBOARD_EVENT_RESPONSE_NONE;
}

void SAT_Widget::on_widget_keyboard_gesture(SAT_KeyboardGesture* AGesture)
{
}

//------------------------------
//
// do_
//
//------------------------------

void SAT_Widget::do_widget_update(SAT_Widget* AWidget, uint32_t AIndex)
{
    SAT_Widget* parent = (SAT_Widget*)getParent();
    if (parent) parent->do_widget_update(AWidget,AIndex);
}

void SAT_Widget::do_widget_realign(SAT_Widget* AWidget, uint32_t AMode)
{
    SAT_Widget* parent = (SAT_Widget*)getParent();
    if (parent) parent->do_widget_realign(AWidget,AMode);
}

void SAT_Widget::do_widget_redraw(SAT_Widget* AWidget, uint32_t AMode)
{
    SAT_Widget* parent = (SAT_Widget*)getParent();
    if (parent) parent->do_widget_redraw(AWidget,AMode);
}

void SAT_Widget::do_widget_anim(SAT_Widget* AWidget, SAT_AnimChain* AChain)
{
    SAT_Widget* parent = (SAT_Widget*)getParent();
    if (parent) parent->do_widget_anim(AWidget,AChain);
}

void SAT_Widget::do_widget_notify(SAT_Widget* AWidget, uint32_t AType, int32_t AValue)
{
    SAT_Widget* parent = (SAT_Widget*)getParent();
    if (parent) parent->do_widget_notify(AWidget,AType,AValue);
}

void SAT_Widget::do_widget_hint(SAT_Widget* AWidget, uint32_t AType, const char* AHint)
{
    SAT_Widget* parent = (SAT_Widget*)getParent();
    if (parent) parent->do_widget_hint(AWidget,AType,AHint);
}

void SAT_Widget::do_widget_modal(SAT_Widget* AWidget)
{
    SAT_Widget* parent = (SAT_Widget*)getParent();
    if (parent) parent->do_widget_modal(AWidget);
}

void SAT_Widget::do_widget_cursor(SAT_Widget* AWidget, int32_t ACursor)
{
    SAT_Widget* parent = (SAT_Widget*)getParent();
    if (parent) parent->do_widget_cursor(AWidget,ACursor);
}

void SAT_Widget::do_widget_capture_mouse(SAT_Widget* AWidget)
{
    SAT_Widget* parent = (SAT_Widget*)getParent();
    if (parent) parent->do_widget_capture_mouse(AWidget);
}

void SAT_Widget::do_widget_capture_keyboard(SAT_Widget* AWidget)
{
    SAT_Widget* parent = (SAT_Widget*)getParent();
    if (parent) parent->do_widget_capture_keyboard(AWidget);
}
