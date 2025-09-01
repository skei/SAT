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

        SAT_Rect            getRect() override;
        bool                isVisible() override;
        bool                isOpaque() override;
        void                setRect(SAT_Rect ARect) override;
        void                setVisible(bool AState=true, bool ARecursive=true) override;
        void                setOpaque(bool AState=true, bool ARecursive=true) override;
        SAT_BaseWidget*     findWidgetAt(int32_t AXpos, int32_t AYpos, bool ARecursive=true) override;
        SAT_Rect            getRecursiveClipRect(SAT_Rect ARect) override;
        SAT_Rect            getRecursiveClipRect() override;
        SAT_BaseWidget*     findOpaqueParent(SAT_Rect ARect) override;
        bool                isRecursivelyVisible() override;
        bool                isRecursivelyOpaque() override;

    public:

        virtual sat_coord_t getPaintScale();
        virtual void        pushClip(SAT_PaintContext* AContext);
        virtual void        pushRecursiveClip(SAT_PaintContext* AContext);
        virtual void        popClip(SAT_PaintContext* AContext);
        virtual void        paintChildren(SAT_PaintContext* AContext);

    public:

        void                on_widget_paint(SAT_PaintContext* AContext, uint32_t AMode=SAT_WIDGET_PAINT_NORMAL, uint32_t AIndex=0) override;
        void                on_widget_pre_paint(SAT_PaintContext* AContext, uint32_t AMode=SAT_WIDGET_PAINT_NORMAL, uint32_t AIndex=0) override;
        void                on_widget_post_paint(SAT_PaintContext* AContext, uint32_t AMode=SAT_WIDGET_PAINT_NORMAL, uint32_t AIndex=0) override;

    protected:

        SAT_Rect            MRect   = {};
};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

SAT_VisualWidget::SAT_VisualWidget(SAT_Rect ARect)
: SAT_HierarchyWidget()
{
    MWidgetTypeName = "SAT_VisualWidget";
    MRect           = ARect;
}

SAT_VisualWidget::~SAT_VisualWidget()
{
}

//------------------------------
//
//------------------------------

SAT_Rect SAT_VisualWidget::getRect()
{
    return MRect;
}

bool SAT_VisualWidget::isVisible()
{
    return State.visible;
}
bool SAT_VisualWidget::isOpaque()
{
    return State.opaque;
}

//----------

void SAT_VisualWidget::setRect(SAT_Rect ARect)
{
    MRect = ARect;
}

void SAT_VisualWidget::setVisible(bool AState, bool ARecursive)
{
    State.visible = AState;
    if (ARecursive)
    {
        for (uint32_t i=0; i<getNumChildren(); i++)
        {
            SAT_BaseWidget* widget = getChild(i);
            widget->setVisible(AState,ARecursive);
        }
    }
}

void SAT_VisualWidget::setOpaque(bool AState, bool ARecursive)
{
    State.opaque = AState;
    if (ARecursive)
    {
        for (uint32_t i=0; i<getNumChildren(); i++)
        {
            SAT_BaseWidget* widget = getChild(i);
            widget->setOpaque(AState,ARecursive);
        }
    }
}

/*
    returns null if no child widgets at x,y
*/

SAT_BaseWidget* SAT_VisualWidget::findWidgetAt(int32_t AXpos, int32_t AYpos, bool ARecursive)
{
    uint32_t num = getNumChildren();
    if (num > 0)
    {
        for (int32_t i=num-1; i>=0; i--)
        {
            SAT_BaseWidget* widget = getChild(i);
            SAT_Rect widget_rect = widget->getRect();
            if (widget->State.active)
            {
                if (widget_rect.contains(AXpos,AYpos))
                {
                    if (ARecursive) return widget->findWidgetAt(AXpos,AYpos);
                }
            }
        }
    }
    return this;
}

/*
    find clipping rectangle by traversing the hierarchy upwards,
    intersecting the current rect with each widget that has the autoClipChilren flag set
*/

SAT_Rect SAT_VisualWidget::getRecursiveClipRect(SAT_Rect ARect)
{
    //SAT_TRACE;
    SAT_Rect rect = ARect;
    SAT_BaseWidget* parent = getParent();
    if (parent)
    {
        if (parent->Options.auto_clip)
        {
            SAT_Rect parent_rect = parent->getRect();
            rect.overlap(parent_rect);
            rect = parent->getRecursiveClipRect(rect);
        }
    }
    return rect;
}

SAT_Rect SAT_VisualWidget::getRecursiveClipRect()
{
    return getRecursiveClipRect(MRect);
}


/*
    returns topmost opaque parent
    or null if no opaque parent found (or widget doesn't have a parent)
    consider ARect, the area of the initial widget..
    check backards until we're sure no other widgets behind it will be visible,
    so we can start painting from there..
*/

SAT_BaseWidget* SAT_VisualWidget::findOpaqueParent(SAT_Rect ARect)
{
    // SAT_TRACE;
    // if (State.opaque == true) return this;
    // else
    // {
        SAT_BaseWidget* parent = getParent();
        if (parent)
        {
            if (parent->State.opaque == true) return parent;
            else return parent->findOpaqueParent(ARect);
        }
        else return nullptr;
    // }
}

/*
    same as active, etc..
    if any widget is set to invisible, all its child widgets are
    also invisible (not drawn, or considered when realigning, etc)
*/

bool SAT_VisualWidget::isRecursivelyVisible()
{
    if (!State.visible) return false;
    SAT_BaseWidget* parent = getParent();
    if (!parent) return true;
    return parent->isRecursivelyVisible();
}

/*
    find 'topmost' widget that conpletely fills the provided rect/area
    (fully obscures everything below it)
*/

bool SAT_VisualWidget::isRecursivelyOpaque()
{
    if (!State.opaque) return false;
    SAT_BaseWidget* parent = getParent();
    if (!parent) return true;
    return parent->isRecursivelyOpaque();
}

//------------------------------
//
//------------------------------

sat_coord_t SAT_VisualWidget::getPaintScale()
{
    SAT_Assert(MOwner);
    sat_coord_t scale = MOwner->do_widget_owner_get_scale(this);
    scale *= getRecursiveScale();
    scale *= getContentScale();
    return scale;
}

void SAT_VisualWidget::pushClip(SAT_PaintContext* AContext)
{
    if (Options.auto_clip)
    {
        SAT_Painter* painter= AContext->painter;
        painter->pushOverlappingClipRect(MRect);
    }
}

void SAT_VisualWidget::pushRecursiveClip(SAT_PaintContext* AContext)
{
    if (Options.auto_clip)
    {
        SAT_Painter* painter= AContext->painter;
        SAT_Rect rect = getRecursiveClipRect();
        painter->pushOverlappingClipRect(rect);//MRect);
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
                SAT_Rect widgetrect = widget->getRect();
                widgetrect.overlap(MRect);
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

void SAT_VisualWidget::on_widget_paint(SAT_PaintContext* AContext, uint32_t AMode, uint32_t AIndex)
{
    if (!State.visible) return;
    pushClip(AContext);
    //pushRecursiveClip(AContext);
    paintChildren(AContext);
    popClip(AContext);
}

void SAT_VisualWidget::on_widget_pre_paint(SAT_PaintContext* AContext, uint32_t AMode, uint32_t AIndex)
{
}

void SAT_VisualWidget::on_widget_post_paint(SAT_PaintContext* AContext, uint32_t AMode, uint32_t AIndex)
{
}













