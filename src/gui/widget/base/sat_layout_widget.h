#pragma once

#include "base/sat_base.h"
//#include "gui/sat_gui_base.h"
#include "gui/widget/base/sat_visual_widget.h"

// struct SAT_WidgetLayout
// {
//     uint32_t    anchor          = SAT_WIDGET_LAYOUT_ANCHOR_TOP_LEFT;
//     uint32_t    stretch         = SAT_WIDGET_LAYOUT_STRETCH_NONE;
//     uint32_t    fill            = SAT_WIDGET_LAYOUT_FILL_NONE;
//     uint32_t    relative        = SAT_WIDGET_LAYOUT_RELATIVE_NONE;
//     uint32_t    stack           = SAT_WIDGET_LAYOUT_STACK_NONE;
//     SAT_Rect    inner_border    = {0,0,0,0};
//     SAT_Rect    outer_border    = {0,0,0,0};
//     SAT_Point   spacing         = {0,0};
//     SAT_Point   minSize         = {-1,-1};
//     SAT_Point   maxSize         = {-1,-1};
//     double      scale           = 1.0;
// };

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

        SAT_Rect        getBaseRect() override;
        SAT_Rect        getInitialRect() override;
        SAT_Rect        getContentRect() override;

    public:

        virtual void    realignChildren(uint32_t AMode=SAT_WIDGET_REALIGN_CHILDREN, uint32_t AIndex=0, bool ARecursive=true);

    public:

        void            on_widget_realign(uint32_t AMode=SAT_WIDGET_REALIGN_CHILDREN, uint32_t AIndex=0) override;
        SAT_Rect        on_widget_pre_align(SAT_Rect ARect, uint32_t AMode=SAT_WIDGET_REALIGN_CHILDREN, uint32_t AIndex=0) override;
        SAT_Rect        on_widget_post_align(SAT_Rect ARect, uint32_t AMode=SAT_WIDGET_REALIGN_CHILDREN, uint32_t AIndex=0) override;

    protected:

        SAT_Rect        MBaseRect       = {};
        SAT_Rect        MInitialRect    = {};
        SAT_Rect        MContentRect    = {};

};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

SAT_LayoutWidget::SAT_LayoutWidget(SAT_Rect ARect)
: SAT_VisualWidget(ARect)
{
    MWidgetType     = 0;
    MWidgetTypeName = "SAT_LayoutWidget";
    MInitialRect    = ARect;
    MBaseRect       = ARect;
}

SAT_LayoutWidget::~SAT_LayoutWidget()
{
}

//------------------------------
//
//------------------------------

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

//------------------------------
//
//------------------------------

/*
    realign all child widgets (recursively)
*/

void SAT_LayoutWidget::realignChildren(uint32_t AMode, uint32_t AIndex, bool ARecursive)
{
    sat_coord_t scale = 1.0;
    SAT_Rect root_rect = getRect();//{0};

    // hmmm... we want to realign before window is initially shown.. :-/
    //SAT_Assert(MOwner);
    
    if (MOwner)
    {
        scale = MOwner->do_widget_owner_get_scale(this);
        sat_coord_t w = MOwner->do_widget_owner_get_width(this);
        sat_coord_t h = MOwner->do_widget_owner_get_height(this);
        root_rect = SAT_Rect(w,h);
    }

    SAT_Rect inner_border = Layout.inner_border;
    inner_border.scale(scale);

    SAT_Point spacing = Layout.spacing;
    spacing.scale(scale);

    SAT_Rect mrect = getRect();

    SAT_Rect parent_rect = mrect;
    parent_rect.shrink(inner_border);

    SAT_Rect layout_rect = mrect;
    layout_rect.shrink(inner_border);

    MContentRect = SAT_Rect( mrect.x,mrect.y, 0,0 );

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
        SAT_Rect child_rect;

        bool need_realign = (child->State.visible || child->Options.realign_if_invisible);
        if (need_realign)
        {

            // --- relative ---

            if (child->Layout.relative & SAT_WIDGET_LAYOUT_RELATIVE_PERCENT)
            {
                if (child->Layout.relative & SAT_WIDGET_LAYOUT_RELATIVE_ROOT)
                {
                    child_rect = SAT_Rect(root_rect.w,root_rect.h,root_rect.w,root_rect.h);
                    child_rect.scale(child->getInitialRect());
                    child_rect.scale(0.01);
                }
                else if (child->Layout.relative & SAT_WIDGET_LAYOUT_RELATIVE_PARENT)
                {
                    child_rect = SAT_Rect(parent_rect.w,parent_rect.h,parent_rect.w,parent_rect.h);
                    child_rect.scale(child->getInitialRect());
                    child_rect.scale(0.01);
                }
                else if (child->Layout.relative & SAT_WIDGET_LAYOUT_RELATIVE_LAYOUT)
                {
                    child_rect = SAT_Rect(layout_rect.w,layout_rect.h,layout_rect.w,layout_rect.h);
                    child_rect.scale(child->getInitialRect());
                    child_rect.scale(0.01);
                }
                else
                {
                    child_rect = SAT_Rect(mrect.w,mrect.h,mrect.w,mrect.h);
                    child_rect.scale(child->getInitialRect());
                    child_rect.scale(0.01);
                }
            }
            else
            {
                child_rect = child->getBaseRect();
                child_rect.scale(scale);
            }

            /*
                SAT_Rect manual = child->MManualTween;
                manual.scale(scale);
                child_rect.add(manual);
                //child_rect.add(child->MManuallyMoved);
            */

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
                if ((stackx + child_rect.w /*+ border.w - spacing.x*/) >= layout_rect.w)
                {
                    if (stackx != 0) // first widget..
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

            if (child->Layout.stack & SAT_WIDGET_LAYOUT_STACK_HORIZONTAL)
            {
                // xanchored = true;
                // yanchored = true;
                if ((stacky + child_rect.h /*+ border.h - spacing.y*/) >= layout_rect.h)
                {
                    if (stacky != 0) // first widget..
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

            if (!xanchored) child_rect.x += mrect.x;
            if (!yanchored) child_rect.y += mrect.y;

            // --- stretch ---

            if (child->Layout.stretch & SAT_WIDGET_LAYOUT_STRETCH_LEFT)        { child_rect.setX1( layout_rect.x   ); }
            if (child->Layout.stretch & SAT_WIDGET_LAYOUT_STRETCH_TOP)         { child_rect.setY1( layout_rect.y   ); }
            if (child->Layout.stretch & SAT_WIDGET_LAYOUT_STRETCH_RIGHT)       { child_rect.setX2( layout_rect.x2()); }
            if (child->Layout.stretch & SAT_WIDGET_LAYOUT_STRETCH_BOTTOM)      { child_rect.setY2( layout_rect.y2()); }

            // --- fill (crop) ---

            if (child->Layout.fill & SAT_WIDGET_LAYOUT_FILL_LEFT)           { layout_rect.setX1( child_rect.x2()); layout_rect.x += spacing.x; layout_rect.w -= spacing.x; }
            if (child->Layout.fill & SAT_WIDGET_LAYOUT_FILL_TOP)            { layout_rect.setY1( child_rect.y2()); layout_rect.y += spacing.y; layout_rect.h -= spacing.y; }
            if (child->Layout.fill & SAT_WIDGET_LAYOUT_FILL_RIGHT)          { layout_rect.setX2( child_rect.x   ); layout_rect.w -= spacing.x; }
            if (child->Layout.fill & SAT_WIDGET_LAYOUT_FILL_BOTTOM)         { layout_rect.setY2( child_rect.y   ); layout_rect.h -= spacing.y; }

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

            child_rect = child->on_widget_post_align(child_rect);

            child->setRect(child_rect);

            // --- recursive ---

            if (ARecursive) child->on_widget_realign(AMode,AIndex);

            // child->realignChildren(ARecursive);
            // if (child_layout & SAT_WIDGET_LAYOUT_CONTENT_SIZE) {
            //   SAT_Rect child_content = child->getContentRect();
            //   child->setRect(child_content);
            // }

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

SAT_Rect SAT_LayoutWidget::on_widget_pre_align(SAT_Rect ARect, uint32_t AMode, uint32_t AIndex)
{
    return ARect;
}

SAT_Rect SAT_LayoutWidget::on_widget_post_align(SAT_Rect ARect, uint32_t AMode, uint32_t AIndex)
{
    return ARect;
}

//------------------------------
//
//------------------------------

