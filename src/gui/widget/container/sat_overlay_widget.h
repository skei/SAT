#pragma once

/*
    fills the entire root/parent, ignoring its borders, etc..
    initially not active and not visible..
    set to visible and active to 'turn it on'..
    if backgroiund color is set transparent, can also be used to dim
    everything below it (for example, when a popup menu is shown)
    also set to not opaque so that 'regular' widgets below it will
    always be painted..
*/

#include "base/sat.h"
#include "gui/sat_widget.h"
#include "gui/widget/container/sat_panel_widget.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_OverlayWidget
: public SAT_PanelWidget
{
    public:
        SAT_OverlayWidget(SAT_Rect ARect);
        virtual ~SAT_OverlayWidget();
    public:
        // void    on_widget_paint(SAT_PaintContext* AContext) override;
        // void    on_widget_pre_paint(SAT_PaintContext* AContext) override;
        // void    on_widget_post_paint(SAT_PaintContext* AContext) override;
};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

SAT_OverlayWidget::SAT_OverlayWidget(SAT_Rect ARect)
: SAT_PanelWidget(ARect)
{
    MTypeName           = "SAT_OverlayWidget";
    Layout.anchor       = SAT_WIDGET_LAYOUT_ANCHOR_ROOT  | SAT_WIDGET_LAYOUT_ANCHOR_TOP_LEFT;
    Layout.stretch      = SAT_WIDGET_LAYOUT_STRETCH_ROOT | SAT_WIDGET_LAYOUT_STRETCH_ALL;
    Options.alignable   = true;
    Options.active      = false;
    Options.visible     = false;
    Options.opaque      = false;
    MSkin = SAT.GUI->SKINS.find("Default Overlay");
}

SAT_OverlayWidget::~SAT_OverlayWidget()
{
}

//------------------------------
//
//------------------------------

// void SAT_OverlayWidget::on_widget_paint(SAT_PaintContext* AContext)
// {
// }

// void SAT_OverlayWidget::on_widget_pre_paint(SAT_PaintContext* AContext)
// {
// }

// void SAT_OverlayWidget::on_widget_post_paint(SAT_PaintContext* AContext)
// {
// }
