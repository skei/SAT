#pragma once

/*
    todo/consider
        - last drawn frame to avoid excess drawing..
        - layered widgets (transrency, opacity, redrawing parent widgets..)

        - show/hide widget when not hovering over it, fade in/out when moving over
          widgets on top of other widgets (f.ex scrollbars)
*/

//----------------------------------------------------------------------

#include "base/sat_base.h"
//#include "gui/sat_gui_base.h"
#include "gui/sat_painter.h"
#include "gui/widget/base/sat_hierarchy_widget.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_VisualWidget
: public SAT_HierarchyWidget
{
    public:

        SAT_VisualWidget(SAT_Rect ARect);
        virtual ~SAT_VisualWidget();

    public:

        void                setOpaque(bool AState=true) override;
        void                setVisible(bool AState=true) override;
        void                setChildrenVisible(bool AState=true) override;
        void                setScale(sat_coord_t AScale) override;
        void                setSkin(SAT_Skin* ASkin) override;
        void                setChildrenSkin(SAT_Skin* ASkin) override;

     // void                setRect(SAT_Rect ARect) override;
     // void                setBaseRect(SAT_Rect ARect) override;

        bool                isOpaque() override;
        bool                isVisible() override;
        sat_coord_t         getScale() override;
        SAT_Skin*           getSkin() override;

        SAT_Rect            getRect() override;
        SAT_Rect            getClipRect() override;
        SAT_Rect            getContentRect() override;
        SAT_BaseWidget*     getOpaqueParent() override;

        SAT_BaseWidget*     findChildAt(int32_t AXpos, int32_t AYpos) override;

    public:

        void                pushClip(SAT_PaintContext* AContext) override;
        void                pushRecursiveClip(SAT_PaintContext* AContext) override;
        void                popClip(SAT_PaintContext* AContext) override;

        sat_coord_t         getPaintScale() override;
        void                paintChildren(SAT_PaintContext* AContext) override;

    public:

        void                on_widget_show(SAT_WidgetOwner* AOwner) override;
        void                on_widget_hide(SAT_WidgetOwner* AOwner) override;
        void                on_widget_paint(SAT_PaintContext* AContext) override;
        void                on_widget_pre_paint(SAT_PaintContext* AContext) override;
        void                on_widget_post_paint(SAT_PaintContext* AContext) override;

    protected:

        SAT_Rect            MBaseRect       = {};
        SAT_Rect            MInitialRect    = {};   // pos/size when created (may be percentages)
        sat_coord_t         MScale          = 1.0;
        SAT_Skin*           MSkin           = nullptr;

};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

SAT_VisualWidget::SAT_VisualWidget(SAT_Rect ARect)
: SAT_HierarchyWidget()
{
    MWidgetTypeName         = "SAT_VisualWidget";
    MBaseRect               = ARect;
    MInitialRect            = ARect;
    Recursive.rect          = ARect;
    Recursive.clip_rect     = ARect;
    Recursive.content_rect  = ARect;
    Recursive.opaque_parent = this;
}

SAT_VisualWidget::~SAT_VisualWidget()
{
}

//------------------------------
//
//------------------------------

void SAT_VisualWidget::setOpaque(bool AState)
{
    State.opaque = AState;
}

void SAT_VisualWidget::setVisible(bool AState)
{
    State.visible = AState;
    setChildrenVisible(AState);
}

void SAT_VisualWidget::setChildrenVisible(bool AState)
{
    for (uint32_t i=0; i<getNumChildren(); i++)
    {
        SAT_BaseWidget* child = getChild(i);
        child->State.visible = false;
        child->setChildrenVisible(AState);
    }
}

void SAT_VisualWidget::setScale(sat_coord_t AScale)
{
    MScale = AScale;
}

void SAT_VisualWidget::setSkin(SAT_Skin* ASkin)
{
    MSkin = ASkin;
}

void SAT_VisualWidget::setChildrenSkin(SAT_Skin* ASkin)
{
    for (uint32_t i=0; i<getNumChildren(); i++)
    {
        SAT_BaseWidget* child = getChild(i);
        child->setSkin(ASkin);
        child->setChildrenSkin(ASkin);
    }
}

/*
    ARect = screen-space
    todo: convert back to widget-space & set base_rect
*/

// void SAT_VisualWidget::setRect(SAT_Rect ARect)
// {
// }

/*
    ARect = widget-space..
    unaffected by alignment/layout
*/

// void SAT_VisualWidget::setBaseRect(SAT_Rect ARect)
// {
// }

//----------

bool SAT_VisualWidget::isOpaque()
{
    return State.opaque;
}

bool SAT_VisualWidget::isVisible()
{
    return State.visible;
}

sat_coord_t SAT_VisualWidget::getScale()
{
    return MScale;
}

SAT_Skin* SAT_VisualWidget::getSkin()
{
    return MSkin;
}



//----------

SAT_Rect SAT_VisualWidget::getRect()
{
    return Recursive.rect;
}

SAT_Rect SAT_VisualWidget::getClipRect()
{
    return Recursive.clip_rect;
}

SAT_Rect SAT_VisualWidget::getContentRect()
{
    return Recursive.content_rect;
}

SAT_BaseWidget* SAT_VisualWidget::getOpaqueParent()
{
    return Recursive.opaque_parent;
}

//----------

/*
    returns null if no child widgets at x,y
*/

SAT_BaseWidget* SAT_VisualWidget::findChildAt(int32_t AXpos, int32_t AYpos)
{
    uint32_t num = getNumChildren();
    if (num > 0)
    {
        for (int32_t i=num-1; i>=0; i--)
        {
            SAT_BaseWidget* widget = getChild(i);
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
//
//------------------------------

void SAT_VisualWidget::pushClip(SAT_PaintContext* AContext)
{
    if (Options.auto_clip)
    {
        SAT_Painter* painter= AContext->painter;
        painter->pushOverlappingClipRect(Recursive.rect);
    }
}

void SAT_VisualWidget::pushRecursiveClip(SAT_PaintContext* AContext)
{
    if (Options.auto_clip)
    {
        SAT_Painter* painter= AContext->painter;
        //SAT_Rect rect = getRecursiveClipRect();
        SAT_Rect rect = Recursive.clip_rect;
        painter->pushOverlappingClipRect(rect);
    }
}

void SAT_VisualWidget::popClip(SAT_PaintContext* AContext)
{
    if (Options.auto_clip)
    {
        SAT_Painter* painter= AContext->painter;
        painter->popClipRect();

    }
}

//----------

sat_coord_t SAT_VisualWidget::getPaintScale()
{
    SAT_Assert(MOwner);
    sat_coord_t scale = MOwner->do_widget_owner_get_scale(this);
    scale *= Recursive.scale;
    scale *= getScale();
    return scale;
}

/*
    draw all the child-widgets, recursively
    (but not the widet itself)
    clipping is already set up
    (see on_widget_paint(), and inherited ones)..

    hmmm.. no point in calling isRecursivelyVisible for each child widget?
    if current widget is visible, it will not call child-widgets

    ouch.. we need it if we call straight into a hierarchy (dirty widgets),
    and haven't checked the visibility..
    but we only need to do it once (fur current widget, don't we?)
    and don't call child widgets if not this one is not visible..
    (but #2, visibility is checked in child.paintChildren..)
*/

void SAT_VisualWidget::paintChildren(SAT_PaintContext* AContext)
{
    // if this widget is not visible, don't do anything..
    //if (!State.visible) return;
    uint32_t numchildren = MChildren.size();
    if (numchildren > 0)
    {
        for(uint32_t i=0; i<numchildren; i++)
        {
            SAT_BaseWidget* widget = MChildren[i];
            //if (widget->isRecursivelyVisible())
            //if (widget->State.visible)
            //{
                SAT_Rect widgetrect = widget->Recursive.rect;
                widgetrect.overlap(Recursive.rect);
                if (widgetrect.isNotEmpty())
                {
                    widget->on_widget_paint(AContext);
                }
            //}
        }
    }
}

//------------------------------
//
//------------------------------

void SAT_VisualWidget::on_widget_show(SAT_WidgetOwner* AOwner)
{
    setOwner(AOwner);
    uint32_t num = getNumChildren();
    for (uint32_t i=0; i<num; i++)
    {
        SAT_BaseWidget* widget = getChild(i);
        widget->on_widget_show(AOwner);
    }
}

void SAT_VisualWidget::on_widget_hide(SAT_WidgetOwner* AOwner)
{
    setOwner(nullptr);
    uint32_t num = getNumChildren();
    for (uint32_t i=0; i<num; i++)
    {
        SAT_BaseWidget* widget = getChild(i);
        widget->on_widget_hide(AOwner);
    }
}


void SAT_VisualWidget::on_widget_paint(SAT_PaintContext* AContext)
{
    if (!State.visible) return;
    pushClip(AContext);
    //pushRecursiveClip(AContext);
    paintChildren(AContext);
    popClip(AContext);
}

void SAT_VisualWidget::on_widget_pre_paint(SAT_PaintContext* AContext)
{
}

void SAT_VisualWidget::on_widget_post_paint(SAT_PaintContext* AContext)
{
}













