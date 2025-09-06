#pragma once

#include "base/sat.h"
#include "gui/sat_window.h"
#include "gui/sat_widgets.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

int main(void)
{
    SAT_Window* window = new SAT_Window(640,480);
    window->setName("window");
    //window->WidgetLayout.inner_border = SAT_Rect(20,20,20,20);
    //window->setScale(0.5);

        SAT_PanelWidget* background = new SAT_PanelWidget(SAT_Rect(640,480));
        background->setName("background");
        window->appendChild(background);
        //background->WidgetLayout.stretch = SAT_WIDGET_LAYOUT_STRETCH_ALL;
        //background->setScale(1.0);

            SAT_PanelWidget* panel = new SAT_PanelWidget(SAT_Rect(10,10,100,100));
            background->appendChild(panel);
            panel->setName("panel");
            //panel->WidgetLayout.stretch = SAT_WIDGET_LAYOUT_STRETCH_ALL;
            //panel->WidgetOptions.auto_redraw_hover = true;
            panel->setScale(1.5);

                SAT_TextWidget* text = new SAT_TextWidget(SAT_Rect(10,10,80,20));
                panel->appendChild(text);
                text->setName("text");
                //text->WidgetLayout.anchor = SAT_WIDGET_LAYOUT_ANCHOR_CENTER;
                //text->WidgetLayout.relative = SAT_WIDGET_LAYOUT_RELATIVE_PARENT;
                //text->setDrawBorder(false);
                text->setCanSelect(true);
                text->WidgetOptions.redraw_if_hovering = true;

                SAT_TextWidget* text2 = new SAT_TextWidget(SAT_Rect(10,40,80,20));
                panel->appendChild(text2);
                text2->setName("text2");
                //text2->WidgetLayout.anchor = SAT_WIDGET_LAYOUT_ANCHOR_CENTER;
                //text2->WidgetLayout.relative = SAT_WIDGET_LAYOUT_RELATIVE_PARENT;
                //text2->setFillBackground(false);
                //text2->WidgetState.opaque = false;
                text2->setDrawBorder(false);
                text2->setCanSelect(true);
                text2->WidgetOptions.redraw_if_hovering = true;

    window->show();
    window->eventLoop();
    window->hide();
    delete window;
    return 0;
}

