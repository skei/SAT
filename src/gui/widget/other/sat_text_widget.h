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

        virtual void setText(const char* AText);
        virtual void setDrawText(bool ADraw=true);
        virtual void setTextColor(SAT_Color AColor);
        virtual void setTextSize(sat_coord_t ASize);

        virtual void drawText(SAT_PaintContext* AContext);

    public:

        void on_widget_paint(SAT_PaintContext* AContext, uint32_t AMode=SAT_WIDGET_PAINT_NORMAL, uint32_t AIndex=0) override;

    private:

        bool        MDrawText       = true;
        const char* MText           = "Text";
        uint32_t    MTextAlignment  = SAT_TEXT_ALIGN_CENTER;
        SAT_Color   MTextColor      = SAT_Black;
        sat_coord_t MTextSize       = 10.0;

};

//------------------------------
//
//------------------------------

SAT_TextWidget::SAT_TextWidget(SAT_Rect ARect)
: SAT_PanelWidget(ARect)
{
}

SAT_TextWidget::~SAT_TextWidget()
{
}

//------------------------------
//
//------------------------------

void SAT_TextWidget::setDrawText(bool ADraw)            { MDrawText = ADraw; }
void SAT_TextWidget::setText(const char* AText)         { MText = AText; }
void SAT_TextWidget::setTextColor(SAT_Color AColor)     { MTextColor = AColor; }
void SAT_TextWidget::setTextSize(sat_coord_t ASize)     { MTextSize = ASize; }


void SAT_TextWidget::drawText(SAT_PaintContext* AContext)
{
    SAT_Painter* painter = AContext->painter;
    if (MDrawText)
    {
        painter->setTextColor(MTextColor);
        // painter->setTextSize(MTextSize);
        painter->drawText(MRect,MText,MTextAlignment);
    }
}

//------------------------------
//
//------------------------------

void SAT_TextWidget::on_widget_paint(SAT_PaintContext* AContext, uint32_t AMode, uint32_t AIndex)
{
    fillBackground(AContext);
    paintChildren(AContext);    
    drawText(AContext);
    drawBorder(AContext);
}

