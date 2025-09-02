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
        virtual void setDrawBorder(bool ADraw=true);
        virtual void setCanSelect(bool ACanSelect=true);

        virtual void fillBackground(SAT_PaintContext* AContext);
        virtual void drawBorder(SAT_PaintContext* AContext);


    public:

        void on_widget_paint(SAT_PaintContext* AContext) override;
        void on_widget_mouse_click(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATime) override;

    protected:

        bool        MFillBackground     = true;
        bool        MDrawBorder         = true;

        bool        MCanSelect          = false;
        bool        MIsSelected         = false;

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

void SAT_PanelWidget::setFillBackground(bool AFill)
{
    MFillBackground = AFill;
}

void SAT_PanelWidget::setDrawBorder(bool ADraw)
{
    MDrawBorder = ADraw;
}

void SAT_PanelWidget::setCanSelect(bool ACanSelect)
{
    MCanSelect = ACanSelect;
}

//------------------------------
//
//------------------------------

void SAT_PanelWidget::fillBackground(SAT_PaintContext* AContext)
{
    SAT_Painter* painter = AContext->painter;
    if (MFillBackground)
    {
        uint32_t state = MIsSelected ? SAT_SKIN_SELECTED : SAT_SKIN_NORMAL;
        if (State.hovering) state |= SAT_SKIN_HOVER;
        SAT_Color color = MSkin->getBackgroundColor(state);
        painter->setFillColor(color);
        SAT_Rect rect = getRect();
        painter->fillRect(rect);
    }
}

void SAT_PanelWidget::drawBorder(SAT_PaintContext* AContext)
{
    if (MDrawBorder)
    {
        SAT_Painter* painter = AContext->painter;
        uint32_t state = MIsSelected ? SAT_SKIN_SELECTED : SAT_SKIN_NORMAL;
        if (State.hovering) state |= SAT_SKIN_HOVER;
        SAT_Color color = MSkin->getBorderColor(state);
        sat_coord_t width = MSkin->getBorderWidth(state);
        painter->setDrawColor(color);
        painter->setLineWidth(width);
        SAT_Rect rect = Recursive.rect;
        painter->drawRect(rect);
        painter->setLineWidth(0);
    }
}

//------------------------------
//
//------------------------------

void SAT_PanelWidget::on_widget_paint(SAT_PaintContext* AContext)
{
    //if (!State.visible) return;
    pushClip(AContext);
    //pushRecursiveClip(AContext);
    fillBackground(AContext);
    paintChildren(AContext);    
    drawBorder(AContext);
    popClip(AContext);
}

void SAT_PanelWidget::on_widget_mouse_click(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATime)
{
    if (MCanSelect)
    {
        if (AButton == SAT_BUTTON_LEFT)
        {
            if (MIsSelected) MIsSelected = false;
            else MIsSelected = true;
            do_widget_redraw(this);
        }
    }
}

