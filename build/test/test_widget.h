#pragma once

#include "base/sat.h"
#include "gui/sat_widget_window.h"
#include "gui/sat_widgets.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

int main(void)
{
    SAT_WidgetWindow* window = new SAT_WidgetWindow(640,480);

        SAT_PanelWidget* panel = new SAT_PanelWidget(0);
        window->appendChild(panel);
        panel->Layout.stretch = SAT_WIDGET_LAYOUT_STRETCH_ALL;

            SAT_TextWidget* text = new SAT_TextWidget(SAT_Rect(50,20));
            panel->appendChild(text);
            text->Layout.anchor = SAT_WIDGET_LAYOUT_ANCHOR_CENTER;
            text->Layout.relative = SAT_WIDGET_LAYOUT_RELATIVE_PARENT;
            text->setBackgroundColor(SAT_DarkRed);
            text->setBorderWidth(1);
            text->setTextColor(SAT_LightYellow);

    window->show();
    window->eventLoop();
    window->hide();
    delete window;
    return 0;
}

