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

        virtual void setFillBackground(bool AFill=true);
        virtual void setBackgroundColor(SAT_Color AColor);
        virtual void setDrawBorder(bool ADraw=true);
        virtual void setBorderColor(SAT_Color AColor);
        virtual void setBorderWidth(sat_coord_t AWidth);

        virtual void fillBackground(SAT_PaintContext* AContext);
        virtual void drawBorder(SAT_PaintContext* AContext);

    public:

        void on_widget_paint(SAT_PaintContext* AContext, uint32_t AMode=SAT_WIDGET_PAINT_NORMAL, uint32_t AIndex=0) override;

    private:

        bool        MFillBackground     = true;
        SAT_Color   MBackgroundColor    = SAT_DarkGrey;
        bool        MDrawBorder         = true;
        SAT_Color   MBorderColor        = SAT_LighterGrey;
        sat_coord_t MBorderWidth        = 2.0;

};

//------------------------------
//
//------------------------------

SAT_PanelWidget::SAT_PanelWidget(SAT_Rect ARect)
: SAT_Widget(ARect)
{
    MWidgetTypeName = "SAT_PanelWidget";
}

SAT_PanelWidget::~SAT_PanelWidget()
{
}

//------------------------------
//
//------------------------------

void SAT_PanelWidget::setFillBackground(bool AFill)         { MFillBackground = AFill; }
void SAT_PanelWidget::setBackgroundColor(SAT_Color AColor)  { MBackgroundColor = AColor; }
void SAT_PanelWidget::setDrawBorder(bool ADraw)             { MDrawBorder = ADraw; }
void SAT_PanelWidget::setBorderColor(SAT_Color AColor)      { MBorderColor = AColor; }
void SAT_PanelWidget::setBorderWidth(sat_coord_t AWidth)    { MBorderWidth = AWidth; }

void SAT_PanelWidget::fillBackground(SAT_PaintContext* AContext)
{
    SAT_Painter* painter = AContext->painter;
    if (MFillBackground)
    {
        painter->setFillColor(MBackgroundColor);
        painter->fillRect(MRect);
    }
}

void SAT_PanelWidget::drawBorder(SAT_PaintContext* AContext)
{
    SAT_Painter* painter = AContext->painter;
    if (MDrawBorder)
    {
        painter->setDrawColor(MBorderColor);
        painter->setLineWidth(MBorderWidth);
        painter->drawRect(MRect);
        painter->setLineWidth(0);
    }
}

//------------------------------
//
//------------------------------

void SAT_PanelWidget::on_widget_paint(SAT_PaintContext* AContext, uint32_t AMode, uint32_t AIndex)
{
    fillBackground(AContext);
    paintChildren(AContext);    
    drawBorder(AContext);
}

