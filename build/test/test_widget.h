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
    //window->Layout.inner_border = SAT_Rect(10,10,10,10);

        SAT_PanelWidget* panel = new SAT_PanelWidget(0);
        window->appendChild(panel);
        panel->Layout.stretch = SAT_WIDGET_LAYOUT_STRETCH_ALL;
        panel->setContentScale(2.0);

            SAT_PanelWidget* panel2 = new SAT_PanelWidget(SAT_Rect(10,10,100,100));
            panel->appendChild(panel2);
            //panel2->Layout.stretch = SAT_WIDGET_LAYOUT_STRETCH_ALL;
            //panel2->setContentScale(2.0);

                SAT_TextWidget* text = new SAT_TextWidget(SAT_Rect(10,10,80,20));
                panel2->appendChild(text);
                //text->Layout.anchor = SAT_WIDGET_LAYOUT_ANCHOR_CENTER;
                //text->Layout.relative = SAT_WIDGET_LAYOUT_RELATIVE_PARENT;
                text->setBackgroundColor(SAT_DarkRed);
                text->setBorderWidth(1);
                text->setTextColor(SAT_LightYellow);

    window->show();
    window->eventLoop();
    window->hide();
    delete window;
    return 0;
}

