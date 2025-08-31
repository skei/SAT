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

        void on_widget_paint(SAT_PaintContext* AContext, uint32_t AMode=SAT_WIDGET_PAINT_NORMAL, uint32_t AIndex=0) override;
        void on_widget_mouse_click(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATime) override;

    private:

        SAT_Color   MColor1 = SAT_DarkRed;
        SAT_Color   MColor2 = SAT_Grey;

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
    painter->setFillColor(MColor1);
    painter->fillRect(MRect);
    painter->setTextColor(MColor2);
    painter->drawText(MRect,"Hello world",SAT_TEXT_ALIGN_CENTER);
    paintChildren(AContext);    
}

void myWidget::on_widget_mouse_click(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATime)
{
    SAT_Color temp = MColor1;
    MColor1 = MColor2;
    MColor2 = temp;
    do_widget_redraw(this);
};


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

