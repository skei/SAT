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

#define SAT_TEXT_WIDGET_EDITABLE
#define SAT_TEXT_WIDGET_AUTOSIZE

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

        virtual void setDrawText(bool ADraw=true);
        virtual void setText(const char* AText);
        virtual void setTextAlignment(uint32_t AAlignment);

        virtual void drawText(SAT_PaintContext* AContext);

    public:

        void on_widget_paint(SAT_PaintContext* AContext) override;

    protected:

        bool        MDrawText           = true;
        const char* MText               = "Text";
        uint32_t    MTextAlignment      = SAT_TEXT_ALIGN_CENTER;

};

//------------------------------
//
//------------------------------

SAT_TextWidget::SAT_TextWidget(SAT_Rect ARect)
: SAT_PanelWidget(ARect)
{
    //MFillBackground = false;
    //MDrawBorder = false;
}

SAT_TextWidget::~SAT_TextWidget()
{
}

//------------------------------
//
//------------------------------

void SAT_TextWidget::setDrawText(bool ADraw)
{
    MDrawText = ADraw;
}

void SAT_TextWidget::setText(const char* AText)
{
    MText = AText;
}

void SAT_TextWidget::setTextAlignment(uint32_t AAlignment)
{
    MTextAlignment = AAlignment;
}

//----------

void SAT_TextWidget::drawText(SAT_PaintContext* AContext)
{
    if (MDrawText)
    {
        SAT_Painter* painter = AContext->painter;
        uint32_t state = MIsSelected ? SAT_SKIN_SELECTED : SAT_SKIN_NORMAL;
        if (State.hovering) state |= SAT_SKIN_HOVER;
        SAT_Color color = MSkin->getTextColor(state);
        painter->setTextColor(color);
        // sat_coord_t size = MSkin->getTextSize(state);
        // painter->setTextSize(size);
        SAT_Rect rect = Recursive.rect;
        painter->drawText(rect,MText,MTextAlignment);
    }
}

//------------------------------
//
//------------------------------

void SAT_TextWidget::on_widget_paint(SAT_PaintContext* AContext)
{
    if (!State.visible) return;
    pushClip(AContext);
    //pushRecursiveClip(AContext);
    fillBackground(AContext);
    paintChildren(AContext);    
    drawText(AContext);
    drawBorder(AContext);
    popClip(AContext);
}
