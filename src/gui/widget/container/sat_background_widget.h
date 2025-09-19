#pragma once

#include "base/sat.h"
#include "gui/sat_widget.h"
#include "gui/widget/container/sat_panel_widget.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_BackgroundWidget
: public SAT_PanelWidget
{
    public:
        SAT_BackgroundWidget(SAT_Rect ARect);
        virtual ~SAT_BackgroundWidget();
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

SAT_BackgroundWidget::SAT_BackgroundWidget(SAT_Rect ARect)
: SAT_PanelWidget(ARect)
{
    MTypeName           = "SAT_BackgroundWidget";
    Layout.anchor       = SAT_WIDGET_LAYOUT_ANCHOR_ROOT | SAT_WIDGET_LAYOUT_ANCHOR_TOP_LEFT;
    Layout.stretch      = SAT_WIDGET_LAYOUT_STRETCH_ROOT | SAT_WIDGET_LAYOUT_STRETCH_ALL;
    Options.alignable   = true;
    Options.active      = true;
    Options.visible     = true;
    Options.opaque      = true;
    Options.skinStates  = SAT_SKIN_STATE_NORMAL;
    MSkin = SAT.GUI->SKINS.find("Default Background");
}

SAT_BackgroundWidget::~SAT_BackgroundWidget()
{
}

//------------------------------
//
//------------------------------

// void SAT_BackgroundWidget::on_widget_paint(SAT_PaintContext* AContext)
// {
// }

// void SAT_BackgroundWidget::on_widget_pre_paint(SAT_PaintContext* AContext)
// {
// }

// void SAT_BackgroundWidget::on_widget_post_paint(SAT_PaintContext* AContext)
// {
// }
