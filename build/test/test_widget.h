#pragma once

#include "base/sat.h"
#include "gui/sat_widget_window.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class myWidget
: public SAT_Widget
{
    public:

        myWidget(SAT_Rect ARect);
        virtual ~myWidget();

        void on_widget_paint(SAT_PaintContext* AContext, uint32_t AMode=SAT_WIDGET_REDRAW_SELF, uint32_t AIndex=0) override;
};

//------------------------------
//
//------------------------------

myWidget::myWidget(SAT_Rect ARect)
: SAT_Widget(ARect)
{
}

myWidget::~myWidget()
{
}

void myWidget::on_widget_paint(SAT_PaintContext* AContext, uint32_t AMode, uint32_t AIndex)
{
    // if (AResized) { SAT_PRINT("resized\n"); }
    SAT_Painter* painter = AContext->painter;
    SAT_Rect rect = AContext->update_rect;
    painter->setFillColor(SAT_DarkRed);
    painter->fillRect(MRect);
    painter->setTextColor(SAT_White);
    painter->drawText(MRect,"Hello world",SAT_TEXT_ALIGN_CENTER);
    // handle widgets..
    // SAT_Widget::on_widget_paint(AContext,AMode,AIndex);
    paintChildren(AContext);    
}

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

int main(void)
{
    SAT_WidgetWindow* window = new SAT_WidgetWindow(640,480);
    myWidget* widget = new myWidget(SAT_Rect(10,10,300,200));
    window->appendChild(widget);
    window->show();
    window->eventLoop();
    window->hide();
    delete window;
    return 0;
}

