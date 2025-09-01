#pragma once

/*
    widget pos/size, relative to parent and other widgets
*/

/*
    todo/consider:
        - movable/sizable (affects layout, pos/size)
        - tweening - offset (from layout/alignment)
        - scrolling (scroll_box) - offset (from layout/alignment)
*/

//----------------------------------------------------------------------

#include "base/sat_base.h"
//#include "gui/sat_gui_base.h"
#include "gui/widget/base/sat_visual_widget.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_LayoutWidget
: public SAT_VisualWidget
{
    public:

        SAT_LayoutWidget(SAT_Rect ARect);
        virtual ~SAT_LayoutWidget();

    public:

        void            setBaseRect(SAT_Rect ARect) override;
        void            setContentScale(sat_coord_t AScale) override;
        void            setAccumulatedScale(sat_coord_t AScale) override;

        SAT_Rect        getBaseRect() override;
        SAT_Rect        getInitialRect() override;
        SAT_Rect        getContentRect() override;
        sat_coord_t     getContentScale() override;
        sat_coord_t     getAccumulatedScale() override;

    public:

        virtual void    realignChildren(uint32_t AMode=SAT_WIDGET_REALIGN_CHILDREN, uint32_t AIndex=0, bool ARecursive=true);

    public:

        void            on_widget_realign(uint32_t AMode=SAT_WIDGET_REALIGN_CHILDREN, uint32_t AIndex=0) override;
        SAT_Rect        on_widget_pre_align(SAT_Rect ARect, uint32_t AMode=SAT_WIDGET_REALIGN_CHILDREN, uint32_t AIndex=0) override;
        SAT_Rect        on_widget_post_align(SAT_Rect ARect, uint32_t AMode=SAT_WIDGET_REALIGN_CHILDREN, uint32_t AIndex=0) override;

    protected:

        SAT_Rect        MBaseRect           = {};   // starting point for alignment
        SAT_Rect        MInitialRect        = {};   // pos/size when created (may be percentages)
        SAT_Rect        MContentRect        = {};

        sat_coord_t     MContentScale       = 1.0;
        sat_coord_t     MAccumulatedScale   = 1.0;

     // SAT_Point       MLayoutOffset       = {0,0};


};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

SAT_LayoutWidget::SAT_LayoutWidget(SAT_Rect ARect)
: SAT_VisualWidget(ARect)
{
    MWidgetTypeName = "SAT_LayoutWidget";
    MBaseRect       = ARect;
    MInitialRect    = ARect;
}

SAT_LayoutWidget::~SAT_LayoutWidget()
{
}

//------------------------------
//
//------------------------------

/*
    base rect is the 'starting point' during (re-) alignment
    coords in 'create-space', reliative to initial size of window
    when creating it.. (unscaled)..
*/

void SAT_LayoutWidget::setBaseRect(SAT_Rect ARect)
{
    MBaseRect = ARect;
}

void SAT_LayoutWidget::setContentScale(sat_coord_t AScale)
{
    MContentScale = AScale;
}

void SAT_LayoutWidget::setAccumulatedScale(sat_coord_t AScale)
{
    MAccumulatedScale = AScale;
}

SAT_Rect SAT_LayoutWidget::getBaseRect()
{
    return MBaseRect;
}

SAT_Rect SAT_LayoutWidget::getInitialRect()
{
    return MInitialRect;
}

SAT_Rect SAT_LayoutWidget::getContentRect()
{
    return MContentRect;
}

sat_coord_t SAT_LayoutWidget::getContentScale()
{
    return MContentScale;
}

sat_coord_t SAT_LayoutWidget::getAccumulatedScale()
{
    return MAccumulatedScale;
}

//------------------------------
//
//------------------------------

/*
    realign all child widgets (recursively)
    note: MOwner (SAT_WidgetOwner) needs to be set..
    (this func calls int it, to ask for window.scaling and root.size, etc)

    called directly from:
        SAT_WidgetWindow.on_window_show     // after on_widget_show() has been called to 'deliver' the WidgetOwner to the widgets)
        SAT_WidgetWindow.on_window_resize   // we are waiting for the initial MAP_NOTIFY events when opning the window,
                                            // (if SAT_X11_WAIT_FOR_MAPNOTIFY is defined, see SAT_X11Window.show())
                                            // so we shouldn't get any resize events, and thus, realignChildren() calls, before on_window_show()?
    via on_widget_realign:
        SAT_WidgetWindow.handleTimer        // via SAT_WidgetWindow.on_timer_listener_update() (in timer thread!) -> x11 gui thread -> handleTimer
*/

void SAT_LayoutWidget::realignChildren(uint32_t AMode, uint32_t AIndex, bool ARecursive)
{
    // on_window_show -> on_widget_show should have set this..
    SAT_Assert(MOwner);

    sat_coord_t scale = MOwner->do_widget_owner_get_scale(this);
    scale *= getAccumulatedScale();
    scale *= getContentScale();

    sat_coord_t w = MOwner->do_widget_owner_get_width(this);
    sat_coord_t h = MOwner->do_widget_owner_get_height(this);
    SAT_Rect root_rect = SAT_Rect(w,h);

    SAT_Rect rect = getRect();

    SAT_Rect inner_border = Layout.inner_border;
    inner_border.scale(scale);

    SAT_Point spacing = Layout.spacing;
    spacing.scale(scale);

    //SAT_Rect rect = getRect();

    SAT_Rect parent_rect = rect;
    parent_rect.shrink(inner_border);

    SAT_Rect layout_rect = rect;
    layout_rect.shrink(inner_border);

    MContentRect = SAT_Rect( rect.x,rect.y, 0,0 );

    double layout_xcenter   = layout_rect.x + (layout_rect.w * 0.5);
    double layout_ycenter   = layout_rect.y + (layout_rect.h * 0.5);
    double stackx           = 0;
    double stacky           = 0;
    double stack_highest    = 0;
    double stack_widest     = 0;

    // ---

    for (uint32_t i=0; i<MChildren.size(); i++)
    {
        SAT_BaseWidget* child = MChildren[i];
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
                    child_rect.scale(child->getInitialRect());
                    child_rect.scale(0.01);
                }
                else if (child->Layout.relative == SAT_WIDGET_LAYOUT_RELATIVE_PARENT)
                {
                    child_rect = SAT_Rect(parent_rect.w,parent_rect.h,parent_rect.w,parent_rect.h);
                    child_rect.scale(child->getInitialRect());
                    child_rect.scale(0.01);
                }
                else if (child->Layout.relative == SAT_WIDGET_LAYOUT_RELATIVE_LAYOUT)
                {
                    child_rect = SAT_Rect(layout_rect.w,layout_rect.h,layout_rect.w,layout_rect.h);
                    child_rect.scale(child->getInitialRect());
                    child_rect.scale(0.01);
                }
                else // relative to current/self ??
                {
                    child_rect = SAT_Rect(rect.w,rect.h,rect.w,rect.h);
                    child_rect.scale(child->getInitialRect());
                    child_rect.scale(0.01);
                }
            }
            else
            {
                child_rect = child->getBaseRect();
                child_rect.scale(scale);
            }

            // --- TODO: tweening / manual movement ---
            
            /*
                SAT_Rect manual = child->MManualTween;
                manual.scale(scale);
                child_rect.add(manual);
                //child_rect.add(child->MManuallyMoved);
            */

            // --- pre-align ---

            child_rect = child->on_widget_pre_align(child_rect);

            // --- scale ---
            
            sat_coord_t accum_scale = getAccumulatedScale();
            accum_scale *= getContentScale();
            child->setAccumulatedScale(accum_scale);

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

            MContentRect.combine(child_rect);

            // --- outer border ---

            SAT_Rect outer_border = child->Layout.outer_border;
            outer_border.scale(scale);
            child_rect.shrink(outer_border);

            // --- post-align ---

            child_rect = child->on_widget_post_align(child_rect);

            // --- set child rect ---

            child->setRect(child_rect);

            // --- recursive ---

            if (ARecursive) child->on_widget_realign(AMode,AIndex);

            /*
                child->realignChildren(ARecursive);
                if (child_layout & SAT_WIDGET_LAYOUT_CONTENT_SIZE)
                {
                    SAT_Rect child_content = child->getContentRect();
                    child->setRect(child_content);
                }
            */

        } // need_realign

    } // for

    MContentRect.w += inner_border.w;
    MContentRect.h += inner_border.h;
}

//------------------------------
//
//------------------------------

void SAT_LayoutWidget::on_widget_realign(uint32_t AMode, uint32_t AIndex)
{
    realignChildren(AMode,AIndex,true);
}

/*
    called before calculating new rect
    here we can remember the starting rect, prepare things..
*/

SAT_Rect SAT_LayoutWidget::on_widget_pre_align(SAT_Rect ARect, uint32_t AMode, uint32_t AIndex)
{
    return ARect;
}

/*
    called after new rect has been calculated
    cwe can do some final adjustments, or undo things..
*/

SAT_Rect SAT_LayoutWidget::on_widget_post_align(SAT_Rect ARect, uint32_t AMode, uint32_t AIndex)
{
    return ARect;
}

//------------------------------
//
//------------------------------

