#pragma once

/*
    options:
    autosize (scale font to fit)
    editable
    selectable (in text_box_widget)
    send notify if selected, etc..)
*/

#include "base/sat.h"
#include "gui/sat_widget.h"
#include "gui/widget/container/sat_panel_widget.h"

// #define SAT_TEXT_WIDGET_EDITABLE
// #define SAT_TEXT_WIDGET_AUTOSIZE

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_TextWidget
: public SAT_PanelWidget
{
    public:

        SAT_TextWidget(SAT_Rect ARect);
        virtual ~SAT_TextWidget();
    public:
        virtual void setText(const char* AText);
    protected:
        virtual void drawText(SAT_PaintContext* AContext);
    public:
        void on_widget_paint(SAT_PaintContext* AContext) override;
    protected:
        const char* MText = "Text";
};

//------------------------------
//
//------------------------------

SAT_TextWidget::SAT_TextWidget(SAT_Rect ARect)
: SAT_PanelWidget(ARect)
{
    MTypeName = "SAT_TextWidget";
    MSkin = SAT.GUI->SKINS.find("DefaultText");
}

SAT_TextWidget::~SAT_TextWidget()
{
}

//------------------------------
//
//------------------------------

void SAT_TextWidget::setText(const char* AText)
{
    MText = AText;
}

//------------------------------
//
//------------------------------

void SAT_TextWidget::drawText(SAT_PaintContext* AContext)
{
    SAT_Painter* painter = AContext->painter;
    SAT_Rect rect = MRect;
    uint32_t state = getPaintState();
    uint32_t mode = MSkin->getTextMode(state);
    switch (mode)
    {
        case SAT_SKIN_TEXT_NORMAL:
        {
            SAT_Color color = MSkin->getTextColor(state);
            uint32_t align = MSkin->getTextAlignment(state);
            // sat_coord_t size = Visual.skin->getTextSize(state);
            // intptr_t font = Visual.skin->getTextFont(state);
            painter->setTextColor(color);
            // painter->setTextSize(size);
            // painter->setTextFont(font);
            painter->drawText(rect,MText,align);
        }
    }
}

//------------------------------
//
//------------------------------

void SAT_TextWidget::on_widget_paint(SAT_PaintContext* AContext)
{
    fillBackground(AContext);
    paintChildren(AContext);    
    drawText(AContext);
    drawBorder(AContext);
}
