#pragma once

/*
    outer drop shadow
    draw background (color, gradient, image, inner drop shadow)
    draw child widgets
    draw border (rounded)
    movable, resizable?
    (or SAT_EditablePanel?)

    examples:
    - reorder effects
    - resize heigh of combo-box (aka selector)..
    - horizontal scroll_box, with horizontally resizable panels to indicate proportional sizes, etc....
    (think gradients with mutiple 'stops')
*/

#include "base/sat.h"
#include "gui/sat_widget.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_PanelWidget
: public SAT_Widget
{
    public:

        SAT_PanelWidget(SAT_Rect ARect);
        virtual ~SAT_PanelWidget();

    protected:

        virtual void fillBackground(SAT_PaintContext* AContext);
        virtual void drawBorder(SAT_PaintContext* AContext);

    public:

        void on_widget_paint(SAT_PaintContext* AContext) override;

};

//------------------------------
//
//------------------------------

SAT_PanelWidget::SAT_PanelWidget(SAT_Rect ARect)
: SAT_Widget(ARect)
{
    MTypeName = "SAT_PanelWidget";
    MSkin = SAT.GUI->SKINS.find("DefaultPanel");
}

SAT_PanelWidget::~SAT_PanelWidget()
{
}

//------------------------------
//
//------------------------------

void SAT_PanelWidget::fillBackground(SAT_PaintContext* AContext)
{
    SAT_Painter* painter = AContext->painter;
    SAT_Rect rect = getRect();
    uint32_t state = getPaintState();
    uint32_t mode = MSkin->getBackgroundMode(state);
    switch (mode)
    {
        case SAT_SKIN_BACKGROUND_COLOR:
        {
            SAT_Color color = MSkin->getBackgroundColor(state);
            painter->setFillColor(color);
            painter->fillRect(rect);
            break;
        }
    }
}

void SAT_PanelWidget::drawBorder(SAT_PaintContext* AContext)
{
    SAT_Painter* painter = AContext->painter;
    SAT_Rect rect = getRect();
    uint32_t state = getPaintState();
    uint32_t mode = MSkin->getBorderMode(state);
    switch (mode)
    {
        case SAT_SKIN_BORDER_RECT:
        {
            SAT_Color color = MSkin->getBorderColor(state);
            sat_coord_t width = MSkin->getBorderWidth(state);
            painter->setDrawColor(color);
            painter->setLineWidth(width);
            painter->drawRect(rect);
            painter->setLineWidth(0);
        }
    }
}

//------------------------------
//
//------------------------------

void SAT_PanelWidget::on_widget_paint(SAT_PaintContext* AContext)
{
    fillBackground(AContext);
    paintChildren(AContext);    
    drawBorder(AContext);
}
