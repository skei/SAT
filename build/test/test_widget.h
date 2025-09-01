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
    window->setName("window");
    //window->Layout.inner_border = SAT_Rect(20,20,20,20);
    window->setContentScale(0.5);

        SAT_PanelWidget* background = new SAT_PanelWidget(SAT_Rect(640,480));
        background->setName("background");
        window->appendChild(background);
        //background->Layout.stretch = SAT_WIDGET_LAYOUT_STRETCH_ALL;
        //background->setContentScale(2.0);

            SAT_PanelWidget* panel = new SAT_PanelWidget(SAT_Rect(10,10,100,100));
            background->appendChild(panel);
            panel->setName("panel");
            panel->setBackgroundColor(SAT_Green);
            //panel->Layout.stretch = SAT_WIDGET_LAYOUT_STRETCH_ALL;
            panel->setContentScale(2.0);

                SAT_TextWidget* text = new SAT_TextWidget(SAT_Rect(10,10,80,20));
                panel->appendChild(text);
                text->setName("text");
                //text->Layout.anchor = SAT_WIDGET_LAYOUT_ANCHOR_CENTER;
                //text->Layout.relative = SAT_WIDGET_LAYOUT_RELATIVE_PARENT;
                text->setBackgroundColor(SAT_DarkRed);
                text->setBorderWidth(1);
                text->setTextColor(SAT_LightYellow);
                text->setCanSelect(true);

    window->show();
    window->eventLoop();
    window->hide();
    delete window;
    return 0;
}

