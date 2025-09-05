#pragma once

#include "base/sat.h"
#include "gui/sat_window.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class myWindow
: public SAT_Window
{
    public:
        myWindow(uint32_t AWidth, uint32_t AHeight, intptr_t AParent=0);
        virtual ~myWindow();
        void on_window_paint(SAT_PaintContext* AContext) override;
};

//------------------------------
//
//------------------------------

myWindow::myWindow(uint32_t AWidth, uint32_t AHeight, intptr_t AParent)
: SAT_Window(AWidth,AHeight,AParent)
{
}

myWindow::~myWindow()
{
}

void myWindow::on_window_paint(SAT_PaintContext* AContext)
{
    // if (AResized) { SAT_PRINT("resized\n"); }
    SAT_Painter* painter = AContext->painter;
    SAT_Rect rect = AContext->update_rect;
    painter->setFillColor(SAT_DarkRed);
    painter->fillRect(rect);
    painter->setTextColor(SAT_White);
    painter->drawText(SAT_Rect(getWidth(),getHeight()),"Hello world",SAT_TEXT_ALIGN_CENTER);
    // handle widgets..
    SAT_WidgetWindow::on_window_paint(AContext);
}

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

int main(void)
{
    myWindow* window = new myWindow(640,480);
    window->show();
    window->eventLoop();
    window->hide();
    delete window;
    return 0;
}

