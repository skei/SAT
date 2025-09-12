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
    SAT_Painter* painter = AContext->painter;
    SAT_Rect rect = AContext->update_rect;
    painter->setFillColor(SAT_DarkGrey);
    painter->fillRect(rect);
    //----------

    SAT_Rect rect1 = { 100,100, 200, 200 };
    SAT_Rect rect2 = { 150,150, 200, 200 };

    SAT_Rect rect3 = rect1;
    rect3.combine(rect2);

    SAT_Rect rect4 = rect1;
    rect4.overlap(rect2);

    painter->setDrawColor(SAT_Red);
    painter->drawRect(rect1);

    painter->setDrawColor(SAT_Yellow);
    painter->drawRect(rect2);

    rect3.grow(3);
    painter->setDrawColor(SAT_LightGrey);
    painter->drawRect(rect3);

    rect4.shrink(3);
    painter->setDrawColor(SAT_DarkerGrey);
    painter->drawRect(rect4);

    //----------
    SAT_Window::on_window_paint(AContext);
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

