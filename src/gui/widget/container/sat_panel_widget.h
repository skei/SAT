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
    public:
        void on_widget_paint(SAT_PaintContext* AContext) override;
    protected:
        virtual void fillBackground(SAT_PaintContext* AContext);
        virtual void drawBorder(SAT_PaintContext* AContext);
        virtual void drawInnerDropShadow(SAT_PaintContext* AContext);
        virtual void drawOuterDropShadow(SAT_PaintContext* AContext);
        virtual void drawGradient(SAT_PaintContext* AContext);
        virtual void drawRoundedCorners(SAT_PaintContext* AContext);


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

void SAT_PanelWidget::on_widget_paint(SAT_PaintContext* AContext)
{
    fillBackground(AContext);
    paintChildren(AContext);    
    drawBorder(AContext);
}

//------------------------------
//
//------------------------------

void SAT_PanelWidget::fillBackground(SAT_PaintContext* AContext)
{
    SAT_Painter* painter = AContext->painter;
    SAT_Rect rect = MRect;
    uint32_t state = getPaintState();
    uint32_t mode = MSkin->getBackgroundMode(state);
    switch (mode)
    {
        case SAT_SKIN_BACKGROUND_NONE:
            break;
        case SAT_SKIN_BACKGROUND_COLOR:
        {
            SAT_Color color = MSkin->getBackgroundColor(state);
            painter->setFillColor(color);
            painter->fillRect(rect);
            break;
        }
        case SAT_SKIN_BACKGROUND_GRADIENT:
            break;
        case SAT_SKIN_BACKGROUND_IMAGE:
            break;
        default:
            SAT_PRINT("Error! unknown skin background mode: %i\n",mode);
            break;
    }
}

void SAT_PanelWidget::drawBorder(SAT_PaintContext* AContext)
{
    SAT_Painter* painter = AContext->painter;
    SAT_Rect rect = MRect;
    uint32_t state = getPaintState();
    uint32_t mode = MSkin->getBorderMode(state);
    switch (mode)
    {
        case SAT_SKIN_BORDER_NONE:
            break;
        case SAT_SKIN_BORDER_RECT:
        {
            SAT_Color color = MSkin->getBorderColor(state);
            sat_coord_t width = MSkin->getBorderWidth(state);
            // if antialising:
            // rect.shrink(width * 0.5);
            painter->setDrawColor(color);
            painter->setLineWidth(width);
            painter->drawRect(rect);
            painter->setLineWidth(0);
            break;
        }
        case SAT_SKIN_BORDER_ROUNDED:
            break;
        default:
            SAT_PRINT("Error! unknown skin border mode: %i\n",mode);
            break;
    }
}

void SAT_PanelWidget::drawInnerDropShadow(SAT_PaintContext* AContext)
{
}

void SAT_PanelWidget::drawOuterDropShadow(SAT_PaintContext* AContext)
{
}

void SAT_PanelWidget::drawGradient(SAT_PaintContext* AContext)
{
}

void SAT_PanelWidget::drawRoundedCorners(SAT_PaintContext* AContext)
{
}

