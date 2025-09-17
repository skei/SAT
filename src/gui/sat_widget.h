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
    uint32_t        anchor                  = SAT_WIDGET_LAYOUT_ANCHOR_TOP_LEFT;    // | SAT_WIDGET_LAYOUT_ANCHOR_REMAINDER;
    uint32_t        stretch                 = SAT_WIDGET_LAYOUT_STRETCH_NONE;       // | SAT_WIDGET_LAYOUT_STRETCH_REMAINDER;
    uint32_t        crop                    = SAT_WIDGET_LAYOUT_CROP_NONE;
    uint32_t        relative                = SAT_WIDGET_LAYOUT_RELATIVE_NONE;
    uint32_t        stack                   = SAT_WIDGET_LAYOUT_STACK_NONE;         // |SAT_WIDGET_LAYOUT_STACK_REMAINDER
    SAT_Rect        innerBorder             = {};
    SAT_Rect        outerBorder             = {};
    SAT_Point       spacing                 = {};
    uint32_t        limits                  = SAT_WIDGET_LAYOUT_LIMIT_NONE;
    SAT_Rect        minimum                 = {-1,-1,-1,-1};
    SAT_Rect        maximum                 = {-1,-1,-1,-1};
};

struct SAT_WidgetOptions
{
    bool            active                  = true;                         // receive (mouse) events
    bool            visible                 = true;                         // visible (painted)
    bool            alignable               = true;                         // take into account while realigning
    bool            clip                    = true;                         // set clip before painting
    bool            opaque                  = true;                         // entirely fills its rect? (or does parent show through?
    sat_coord_t     scale                   = 1.0;                          // scale children (and painting)
    uint32_t        skinStates              = SAT_SKIN_STATE_NORMAL;        // which skin/paint states widget supports
    uint32_t        wantMouseEvents         = SAT_MOUSE_EVENT_NONE;         // which mouse events the widget wants
    uint32_t        wantMouseGestures       = SAT_MOUSE_GESTURE_NONE;       // which mouse gestures the widget wants
    uint32_t        wantKeyboardEvents      = SAT_KEYBOARD_EVENT_NONE;      // keyboard..
    uint32_t        wantKeyboardGestures    = SAT_KEYBOARD_GESTURE_NONE;    // keyboard..
};

// struct SAT_WidgetAppearance
// struct SAT_WidgetBehaviour

struct SAT_WidgetState
{
    bool            active                  = true;
    bool            visible                 = true;
    bool            disabled                = true;
    bool            hovering                = false;
    bool            interacting             = false;
    bool            highlighted             = false;
    // bool         selected                = false;
    // bool         focused                 = false;
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
    public:
        virtual void            setName(const char* AName);
        virtual void            setHint(const char* AHint);
        virtual void            setTooltip(const char* ATooltip);
        virtual const char*     getName();
        virtual const char*     getHint();
        virtual const char*     getTooltip();
        virtual const char*     getTypeName();
    public: // hierarchy
        virtual SAT_Widget*     appendChild(SAT_Widget* AWidget);
        virtual void            removeChild(SAT_Widget* AWidget, bool ADelete=true);
        virtual void            deleteChildren();
        virtual SAT_Widget*     findChild(const char* AName);
        virtual SAT_Widget*     findChildAt(int32_t AXpos, int32_t AYpos, bool AVisibleOnly=true, bool AActiveOnly=false);
        virtual void            showOwner(SAT_WidgetOwner* AOwner);
        virtual void            hideOwner(SAT_WidgetOwner* AOwner);
    public: // painting
        virtual void            pushClip(SAT_PaintContext* AContext);
        virtual void            popClip(SAT_PaintContext* AContext);
        virtual sat_coord_t     getPaintScale();
        virtual uint32_t        getPaintState();
        virtual void            paintWidget(SAT_PaintContext* AContext);
        virtual void            paintChildren(SAT_PaintContext* AContext);
    public: // alignment
        virtual void            setActive(bool AState=true);
        virtual void            setVisible(bool AState=true);
        virtual void            setSkin(SAT_Skin* ASkin, bool AReplace=true);
        // virtual void         setDisabled(bool AState=true);
        virtual void            setChildrenActive(bool AState=true);
        virtual void            setChildrenVisible(bool AState=true);
        virtual void            setChildrenSkin(SAT_Skin* ASkin, bool AReplace=true);
        // virtual void         setChildrenDisabled(bool AState=true);
        virtual void            realignChildren();
    public: // value
        virtual uint32_t        getValueIndex();
        virtual void            setValueIndex(uint32_t AIndex);
        virtual sat_param_t     getValue();
        virtual sat_param_t     getValue(uint32_t AIndex);
        virtual void            setValue(sat_param_t AValue);
        virtual void            setValue(sat_param_t AValue, uint32_t AIndex);
        virtual SAT_Parameter*  getParameter();
        virtual SAT_Parameter*  getParameter(uint32_t AIndex);
        virtual void            setParameter(SAT_Parameter* AParameter);
        virtual void            setParameter(SAT_Parameter* AParameter, uint32_t AIndex);
    public: // on_
        virtual void            on_widget_show(SAT_WidgetOwner* AOwner);
        virtual void            on_widget_hide(SAT_WidgetOwner* AOwner);
        virtual void            on_widget_paint(SAT_PaintContext* AContext);
        virtual void            on_widget_pre_paint(SAT_PaintContext* AContext);
        virtual void            on_widget_post_paint(SAT_PaintContext* AContext);
        virtual void            on_widget_realign();
        virtual SAT_Rect        on_widget_pre_align(SAT_Rect ARect);
        virtual SAT_Rect        on_widget_post_align(SAT_Rect ARect);
        virtual void            on_widget_timer(uint32_t ATimerId, double ADelta);
        virtual void            on_widget_anim(uint32_t AId, uint32_t AType, uint32_t ANumValues, double* AValues);
        virtual void            on_widget_notify(SAT_Widget* AWidget, uint32_t AType=SAT_WIDGET_NOTIFY_NONE, intptr_t AValue=0);
        virtual uint32_t        on_widget_mouse_event(SAT_MouseEvent* AEvent);
        virtual void            on_widget_mouse_gesture(SAT_MouseGesture* AGesture);
        virtual uint32_t        on_widget_keyboard_event(SAT_KeyboardEvent* AEvent);
        virtual void            on_widget_keyboard_gesture(SAT_KeyboardGesture* AGesture);
    public: // do_
        virtual void            do_widget_update(SAT_Widget* AWidget, uint32_t AIndex=0);
        virtual void            do_widget_realign(SAT_Widget* AWidget, uint32_t AMode=SAT_WIDGET_REALIGN_PARENT);
        virtual void            do_widget_redraw(SAT_Widget* AWidget, uint32_t AMode=SAT_WIDGET_REDRAW_SELF);
        virtual void            do_widget_anim(SAT_Widget* AWidget, SAT_AnimChain* AChain);
        virtual void            do_widget_notify(SAT_Widget* AWidget, uint32_t AType=SAT_WIDGET_NOTIFY_NONE, intptr_t AValue=0);
        virtual void            do_widget_capture_mouse(SAT_Widget* AWidget);
        virtual void            do_widget_capture_keyboard(SAT_Widget* AWidget);
        virtual void            do_widget_cursor(SAT_Widget* AWidget, int32_t ACursor);
        virtual void            do_widget_modal(SAT_Widget* AWidget);
        virtual void            do_widget_hint(SAT_Widget* AWidget, uint32_t AType, const char* AHint=nullptr);
    public: 
        SAT_WidgetLayout        Layout                              = {};
        SAT_WidgetOptions       Options                             = {};
    protected:
        const char*             MTypeName                           = "SAT_Widget";
        const char*             MName                               = "";
        const char*             MHint                               = "";
        const char*             MTooltip                            = "";
        SAT_WidgetState         MState                              = {};
    protected: // hierarchy
        SAT_WidgetOwner*        MOwner                              = nullptr;
        SAT_Widget*             MParent                             = nullptr;
        SAT_WidgetArray         MChildren                           = {};
        uint32_t                MIndex                              = 0;
    protected: // alignment
        SAT_Rect                MRect                               = {};               // (pixels) current rect
        SAT_Rect                MClipRect                           = {};               // (pixels) clip rect (recursive)
        SAT_Rect                MContentRect                        = {};               // (pixels) rect containing all child widgets (and borders, etc)
        SAT_Rect                MInitialRect                        = {};               // (base units) rect widget is created with (could be relative/percentages)
        SAT_Rect                MBaseRect                           = {};               // (base units) rect realignment starts from
        SAT_Rect                MBaseOffset                         = {};               // (base units) movable, sizable, anim
        SAT_Point               MScrollOffset                       = {};               // (base units) scrollbox
        SAT_Widget*             MOpaqueParent                       = nullptr;          // widget to sytart from during painting (self, if widget is opaque)
        sat_coord_t             MScale                              = 1.0;              // recursively (what's actually visible)
        // uint32_t             MPrevRealigned                      = SAT_UINT32_MAX;
    protected: // painting
        SAT_Skin*               MSkin                               = nullptr;
        uint32_t                MPrevPainted                        = SAT_UINT32_MAX;
        // uint32_t             MPrevRedrawn                        = SAT_UINT32_MAX;
    protected: // value
        uint32_t                MValueIndex                         = 0;
        sat_param_t             MValues[SAT_WIDGET_NUM_VALUES]      = {};
        SAT_Parameter*          MParameters[SAT_WIDGET_NUM_VALUES]  = {};
        // uint32_t             MPrevUpdated                        = SAT_UINT32_MAX;
};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

SAT_Widget::SAT_Widget(SAT_Rect ARect)
{
    MTypeName       = "SAT_Widget";
    MRect           = ARect;
    MInitialRect    = ARect;
    MBaseRect       = ARect;
    MContentRect    = ARect;
    MClipRect       = ARect;
    MOpaqueParent   = this;
    MSkin           = SAT.GUI->SKINS.find("Default");
}

SAT_Widget::~SAT_Widget()
{
    #ifndef SAT_NO_AUTODELETE
        deleteChildren();
    #endif
}

//------------------------------
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
// hierarchy
//------------------------------

// child automatically inherits skin, unless it already has one

SAT_Widget* SAT_Widget::appendChild(SAT_Widget* AWidget)
{
    AWidget->MParent = this;
    uint32_t index = MChildren.size();
    AWidget->MIndex = index;
    if (!AWidget->MSkin) AWidget->MSkin = MSkin;
    MChildren.append(AWidget);
    return AWidget;
}

void SAT_Widget::removeChild(SAT_Widget* AWidget, bool ADelete)
{
    AWidget->MParent = nullptr;
    MChildren.remove(AWidget);
    if (ADelete) delete AWidget;
}

void SAT_Widget::deleteChildren()
{
    for (uint32_t i=0; i<MChildren.size(); i++)
    {
        SAT_Widget* widget = MChildren[i];
        if (widget) delete widget;
    }
}

SAT_Widget* SAT_Widget::findChild(const char* AName)
{
    const char* name = getName();
    if (strcmp(AName,name) == 0)
    {
        return this;
    }
    for (uint32_t i=0; i<MChildren.size(); i++)
    {
        SAT_Widget* child = MChildren[i];
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

// returns this if no child widgets at x,y
// for a window, no widgets means the window itself
// (also when outside of the window)

SAT_Widget* SAT_Widget::findChildAt(int32_t AXpos, int32_t AYpos, bool AVisibleOnly, bool AActiveOnly)
{
    uint32_t num = MChildren.size();
    if (num > 0)
    {
        for (int32_t i=num-1; i>=0; i--)
        {
            SAT_Widget* widget = MChildren[i];
            SAT_Rect widget_rect = widget->MRect;
            if (widget_rect.contains(AXpos,AYpos))
            {
                bool match = true;
                if (AActiveOnly && (widget->MState.active == false)) match = false;
                if (AVisibleOnly && (widget->MState.visible == false)) match = false;
                if (match)
                {
                    return widget->findChildAt(AXpos,AYpos,AVisibleOnly,AActiveOnly);
                }
            }
        }
    }
    return this;
}

// called when the window is shown on the screen
// todo: check if it also called after a hide/show cycle too?)

void SAT_Widget::showOwner(SAT_WidgetOwner* AOwner)
{
    on_widget_show(AOwner);
    MOwner = AOwner;
    uint32_t num = MChildren.size();
    for (uint32_t i=0; i<num; i++)
    {
        SAT_Widget* widget = MChildren[i];
        widget->showOwner(AOwner);
    }
}

void SAT_Widget::hideOwner(SAT_WidgetOwner* AOwner)
{
    on_widget_hide(AOwner);
    MOwner = nullptr;
    uint32_t num = MChildren.size();
    for (uint32_t i=0; i<num; i++)
    {
        SAT_Widget* widget = MChildren[i];
        widget->hideOwner(AOwner);
    }
}

//------------------------------
// painting
//------------------------------

void SAT_Widget::pushClip(SAT_PaintContext* AContext)
{
    if (Options.clip)
    {
        SAT_Painter* painter= AContext->painter;
        painter->pushOverlappingClipRect(MClipRect); // MRect
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

sat_coord_t SAT_Widget::getPaintScale()
{
    SAT_Assert(MOwner);
    return Options.scale * MScale;
}

uint32_t SAT_Widget::getPaintState()
{
    uint32_t state = SAT_SKIN_STATE_NORMAL;
    if (MState.hovering     &&  (Options.skinStates & SAT_SKIN_STATE_HOVERING))     state |= SAT_SKIN_STATE_HOVERING;
    if (MState.disabled     &&  (Options.skinStates & SAT_SKIN_STATE_DISABLED))     state |= SAT_SKIN_STATE_DISABLED;
    if (MState.highlighted  &&  (Options.skinStates & SAT_SKIN_STATE_HIGHLIGHTED))  state |= SAT_SKIN_STATE_HIGHLIGHTED;
    if (MState.interacting  &&  (Options.skinStates & SAT_SKIN_STATE_INTERACTING))  state |= SAT_SKIN_STATE_INTERACTING;
    return state;
}

// assumes widget is visible, and checked for update_rect overlap

void SAT_Widget::paintWidget(SAT_PaintContext* AContext)
{
    pushClip(AContext);
    on_widget_paint(AContext);
    popClip(AContext);
    MPrevPainted = AContext->current_frame;
}

void SAT_Widget::paintChildren(SAT_PaintContext* AContext)
{
    for (uint32_t i=0; i<MChildren.size(); i++)
    {
        SAT_Widget* child = (SAT_Widget*)MChildren[i];
        if (child->MState.visible)
        {
            child->paintWidget(AContext);
        }
    }
}

//------------------------------
// alignment
//------------------------------

void SAT_Widget::setActive(bool AState)
{
    MState.active = AState;
    setChildrenActive(AState);
}

void SAT_Widget::setVisible(bool AState)
{
    MState.visible = AState;
    setChildrenVisible(AState);
}

// if AReplace is true, replace skin if is already has one,
// else set it unconditionally

void SAT_Widget::setSkin(SAT_Skin* ASkin, bool AReplace)
{
    if (MSkin && AReplace) MSkin = ASkin;
    else MSkin = ASkin;
    setChildrenSkin(ASkin,AReplace);
}

// void SAT_Widget::setDisabled(bool AState)
// {
//     MState.disabled = AState;
//     setChildrenDisabled(AState);
// }

void SAT_Widget::setChildrenActive(bool AState)
{
    for (uint32_t i=0; i<MChildren.size(); i++)
    {
        SAT_Widget* widget = MChildren[i];
        widget->MState.active = AState;
        widget->setChildrenActive(AState);
    }
}

void SAT_Widget::setChildrenVisible(bool AState)
{
    for (uint32_t i=0; i<MChildren.size(); i++)
    {
        SAT_Widget* child = MChildren[i];
        child->MState.visible = AState;
        child->setChildrenVisible(AState);
    }
}

void SAT_Widget::setChildrenSkin(SAT_Skin* ASkin, bool AReplace)
{
    for (uint32_t i=0; i<MChildren.size(); i++)
    {
        SAT_Widget* child = MChildren[i];
        if (child->MSkin && AReplace) child->MSkin = ASkin;
        else child->MSkin = ASkin;
        child->setChildrenSkin(ASkin,AReplace);
    }
}

// void SAT_Widget::setChildrenDisabled(bool AState)
// {
//     for (uint32_t i=0; i<MChildren.size(); i++)
//     {
//         SAT_Widget* widget = MChildren[i];
//         widget->MState.disabled = AState;
//         widget->setChildrenDisabled(AState);
//     }
// }

void SAT_Widget::realignChildren()
{

    sat_coord_t scale = Options.scale * MScale;

    SAT_Rect widget_rect = MBaseRect;

    SAT_Rect inner_border = Layout.innerBorder;
    inner_border.scale(scale);

    SAT_Point spacing = Layout.spacing;
    spacing.scale(scale);

    SAT_Rect parent_rect = widget_rect;
    parent_rect.shrink(inner_border);

    SAT_Rect remainder_rect = widget_rect;
    remainder_rect.shrink(inner_border);

    MContentRect = SAT_Rect( widget_rect.x,widget_rect.y, 0,0 );

    double stackx           = 0;
    double stacky           = 0;
    double stack_highest    = 0;
    double stack_widest     = 0;

    // ---

    for (uint32_t i=0; i<MChildren.size(); i++)
    {
        SAT_Widget* child = MChildren[i];
        SAT_Assert(child);

        SAT_Rect child_rect;

        if (child->Options.alignable)
        {

            // --- relative pos/size ---
            // (percentages)

            switch(child->Layout.relative)
            {
                case SAT_WIDGET_LAYOUT_RELATIVE_NONE:
                    child_rect = child->MBaseRect;
                    child_rect.scale(scale);
                    break;
                case SAT_WIDGET_LAYOUT_RELATIVE_PARENT:
                    child_rect = SAT_Rect(parent_rect.w,parent_rect.h,parent_rect.w,parent_rect.h);
                    child_rect.scale(child->MInitialRect);
                    child_rect.scale(0.01);
                    break;
                case SAT_WIDGET_LAYOUT_RELATIVE_REMAINDER:
                    child_rect = SAT_Rect(remainder_rect.w,remainder_rect.h,remainder_rect.w,remainder_rect.h);
                    child_rect.scale(child->MInitialRect);
                    child_rect.scale(0.01);
                    break;
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
                case SAT_WIDGET_LAYOUT_ANCHOR_REMAINDER:
                    anchor_rect = remainder_rect;
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
                case SAT_WIDGET_LAYOUT_STACK_REMAINDER:
                    stack_rect = remainder_rect;
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
                case SAT_WIDGET_LAYOUT_STRETCH_REMAINDER:
                    stretch_rect = remainder_rect;
                    break;
                case SAT_WIDGET_LAYOUT_STRETCH_PARENT:
                    stretch_rect = parent_rect;
                    break;
                default:
                    SAT_PRINT("Error: unknown layout stretch mode: %i\n",child->Layout.stretch & 0xff000000);
                    break;
            };
            if (child->Layout.stretch & SAT_WIDGET_LAYOUT_STRETCH_LEFT)     { child_rect.setX1( stretch_rect.x   ); }
            if (child->Layout.stretch & SAT_WIDGET_LAYOUT_STRETCH_TOP)      { child_rect.setY1( stretch_rect.y   ); }
            if (child->Layout.stretch & SAT_WIDGET_LAYOUT_STRETCH_RIGHT)    { child_rect.setX2( stretch_rect.x2()); }
            if (child->Layout.stretch & SAT_WIDGET_LAYOUT_STRETCH_BOTTOM)   { child_rect.setY2( stretch_rect.y2()); }

            // --- crop ---

            if (child->Layout.crop & SAT_WIDGET_LAYOUT_CROP_LEFT)           { remainder_rect.setX1( child_rect.x2()); remainder_rect.x += spacing.x; remainder_rect.w -= spacing.x; }
            if (child->Layout.crop & SAT_WIDGET_LAYOUT_CROP_TOP)            { remainder_rect.setY1( child_rect.y2()); remainder_rect.y += spacing.y; remainder_rect.h -= spacing.y; }
            if (child->Layout.crop & SAT_WIDGET_LAYOUT_CROP_RIGHT)          { remainder_rect.setX2( child_rect.x   ); remainder_rect.w -= spacing.x; }
            if (child->Layout.crop & SAT_WIDGET_LAYOUT_CROP_BOTTOM)         { remainder_rect.setY2( child_rect.y   ); remainder_rect.h -= spacing.y; }

            // --- stack end ---

            if (child->Layout.stack & SAT_WIDGET_LAYOUT_STACK_END)
            {
                if (child->Layout.stack & SAT_WIDGET_LAYOUT_STACK_VERTICAL)
                {
                    float w = (stackx + stack_widest + spacing.x);
                    remainder_rect.x += w;
                    remainder_rect.w -= w;
                }
                if (child->Layout.stack & SAT_WIDGET_LAYOUT_STACK_HORIZONTAL)
                {
                    float h = (stacky + stack_highest + spacing.y);
                    remainder_rect.y += h;
                    remainder_rect.h -= h;
                }
            }

            // --- pos/size limit ---
            // (percentages, unless _pixels)

            SAT_Rect limit_scale;
            switch (child->Layout.limits)
            {
                case SAT_WIDGET_LAYOUT_LIMIT_NONE:
                    limit_scale.set(1.0);
                    break;
                case SAT_WIDGET_LAYOUT_LIMIT_PIXELS:
                    limit_scale.set(scale);
                    break;
                case SAT_WIDGET_LAYOUT_LIMIT_BASE:
                    limit_scale = MBaseRect;
                    limit_scale.scale(scale * 0.01);
                    break;
                case SAT_WIDGET_LAYOUT_LIMIT_PARENT:
                    limit_scale = parent_rect;
                    limit_scale.scale(scale * 0.01);
                    break;
                case SAT_WIDGET_LAYOUT_LIMIT_REMAINDER:
                    limit_scale = remainder_rect;
                    limit_scale.scale(scale * 0.01);
                    break;
                default:
                    SAT_PRINT("Error: unknown layout limit mode: %i\n",child->Layout.limits);
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

            MContentRect.combine(child_rect);

            // --- outer border ---

            SAT_Rect outer_border = child->Layout.outerBorder;
            outer_border.scale(scale);
            child_rect.shrink(outer_border);

            // --- post-align ---

            child_rect = child->on_widget_post_align(child_rect);

            // --- set child properties ---

            child->MRect = child_rect;

            if (child_rect.isNotEmpty())
            {
                child->MScale = scale;
                child->MClipRect = child_rect;
                child->MClipRect.overlap(MClipRect);
                if (child->Options.opaque) child->MOpaqueParent = child;
                else child->MOpaqueParent = MOpaqueParent;
                if (!child->MSkin) child->MSkin = MSkin;
                child->MState.active = child->Options.active;
                child->MState.visible = child->Options.visible;
                // recursive
                child->on_widget_realign();
            }
            else
            {
                child->setVisible(false);
                child->setActive(false);
            }

        } // alignable

        else
        {
            // widget is not alignable, so it will not be drawn or accept events,
            // so we set it, and its children not visible/active..
            child->setVisible(false);
            child->setActive(false);
        }

    } // for

    MContentRect.w += inner_border.w;
    MContentRect.h += inner_border.h;

}

//------------------------------
// value
//------------------------------

uint32_t SAT_Widget::getValueIndex()
{
    return MValueIndex;
}

void SAT_Widget::setValueIndex(uint32_t AIndex)
{
    MValueIndex = AIndex;
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

void SAT_Widget::on_widget_show(SAT_WidgetOwner* AOwner)
{
}

void SAT_Widget::on_widget_hide(SAT_WidgetOwner* AOwner)
{
}

// assumes widget is visible, and checked for update_rect overlap
// and clipping has been set up (widget's cliprect)

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

SAT_Rect SAT_Widget::on_widget_pre_align(SAT_Rect ARect)
{
    return ARect;
}

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
    if (MParent) MParent->do_widget_update(AWidget,AIndex);
}

void SAT_Widget::do_widget_realign(SAT_Widget* AWidget, uint32_t AMode)
{
    if (MParent) MParent->do_widget_realign(AWidget,AMode);
}

void SAT_Widget::do_widget_redraw(SAT_Widget* AWidget, uint32_t AMode)
{
    if (MParent) MParent->do_widget_redraw(AWidget,AMode);
}

void SAT_Widget::do_widget_anim(SAT_Widget* AWidget, SAT_AnimChain* AChain)
{
    if (MParent) MParent->do_widget_anim(AWidget,AChain);
}

void SAT_Widget::do_widget_notify(SAT_Widget* AWidget, uint32_t AType, intptr_t AValue)
{
    if (MParent) MParent->do_widget_notify(AWidget,AType,AValue);
}

void SAT_Widget::do_widget_capture_mouse(SAT_Widget* AWidget)
{
    if (MParent) MParent->do_widget_capture_mouse(AWidget);
}

void SAT_Widget::do_widget_capture_keyboard(SAT_Widget* AWidget)
{
    if (MParent) MParent->do_widget_capture_keyboard(AWidget);
}

void SAT_Widget::do_widget_cursor(SAT_Widget* AWidget, int32_t ACursor)
{
    if (MParent) MParent->do_widget_cursor(AWidget,ACursor);
}

void SAT_Widget::do_widget_modal(SAT_Widget* AWidget)
{
    if (MParent) MParent->do_widget_modal(AWidget);
}

void SAT_Widget::do_widget_hint(SAT_Widget* AWidget, uint32_t AType, const char* AHint)
{
    if (MParent) MParent->do_widget_hint(AWidget,AType,AHint);
}
