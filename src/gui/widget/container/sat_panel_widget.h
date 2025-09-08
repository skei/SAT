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

        virtual void setCanSelect(bool ACanSelect=true);
        virtual void fillBackground(SAT_PaintContext* AContext);
        virtual void drawBorder(SAT_PaintContext* AContext);

    public:

        void on_widget_paint(SAT_PaintContext* AContext) override;
        void on_widget_mouse_click(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATime) override;
        void on_widget_mouse_release(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATime) override;
        void on_widget_mouse_move(int32_t AXpos, int32_t AYpos, uint32_t AState, uint32_t ATime) override;
        void on_widget_mouse_start_drag(int32_t AXpos, int32_t AYpos, uint32_t AState, uint32_t ATime) override;

    protected:

        bool        MCanSelect  = false;
        bool        MIsSelected = false;

};

//------------------------------
//
//------------------------------

SAT_PanelWidget::SAT_PanelWidget(SAT_Rect ARect)
: SAT_Widget(ARect)
{
    WidgetBase.widgetTypeName   = "SAT_PanelWidget";
    WidgetVisual.skin           = SAT.GUI->SKINS.find("DefaultPanel");
}

SAT_PanelWidget::~SAT_PanelWidget()
{
}

//------------------------------
//
//------------------------------

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
    SAT_Rect rect = getRect();
    uint32_t state = getPaintState();
    uint32_t mode = WidgetVisual.skin->getBackgroundMode(state);
    switch (mode)
    {
        case SAT_SKIN_BACKGROUND_COLOR:
        {
            SAT_Color color = WidgetVisual.skin->getBackgroundColor(state);
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
    uint32_t mode = WidgetVisual.skin->getBorderMode(state);
    switch (mode)
    {
        case SAT_SKIN_BORDER_RECT:
        {
            SAT_Color color = WidgetVisual.skin->getBorderColor(state);
            sat_coord_t width = WidgetVisual.skin->getBorderWidth(state);
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
    #ifdef SAT_WINDOW_DEBUG_PAINTING
        SAT_PRINT("%s, frame %i (last frame %i)\n",getName(),AContext->current_frame,WidgetUpdate.last_painted);
    #endif
    fillBackground(AContext);
    paintChildren(AContext);    
    drawBorder(AContext);
}

void SAT_PanelWidget::on_widget_mouse_click(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATime)
{
    if (MCanSelect)
    {
        if (AButton == SAT_BUTTON_LEFT)
        {
            MIsSelected = !MIsSelected;
            WidgetState.highlighted = MIsSelected;
            do_widget_redraw(this);
        }
    }
    do_widget_cursor(this,SAT_CURSOR_LOCK);
}

void SAT_PanelWidget::on_widget_mouse_release(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATime)
{
    do_widget_cursor(this,SAT_CURSOR_SHOW);
    do_widget_cursor(this,SAT_CURSOR_UNLOCK);
};

void SAT_PanelWidget::on_widget_mouse_move(int32_t AXpos, int32_t AYpos, uint32_t AState, uint32_t ATime)
{
    SAT_PRINT("x %i y %i\n",AXpos,AYpos);
}

void SAT_PanelWidget::on_widget_mouse_start_drag(int32_t AXpos, int32_t AYpos, uint32_t AState, uint32_t ATime)
{
    SAT_PRINT("x %i y %i\n",AXpos,AYpos);
    do_widget_cursor(this,SAT_CURSOR_HIDE);
}
