#pragma once

// #define SAT_DEBUG_MEMTRACE

#include "base/sat.h"
#include "gui/sat_window.h"
#include "gui/sat_widgets.h"
#include "gui/widget/sat_test_widget.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

int main(void)
{

    SAT_Window* window = new SAT_Window(640,480);
    window->setName("window");

        SAT_PanelWidget* background = new SAT_PanelWidget(SAT_Rect(640,480));
        window->appendChild(background);
        background->setName("background");
        background->WidgetLayout.stretch = SAT_WIDGET_LAYOUT_STRETCH_ALL;
        //background->setScale(1.0);

            SAT_PanelWidget* panel = new SAT_PanelWidget(SAT_Rect(10,10,100,100));
            background->appendChild(panel);
            panel->setName("panel");
            //panel->WidgetLayout.stretch = SAT_WIDGET_LAYOUT_STRETCH_ALL;
            //panel->WidgetOptions.auto_redraw_hover = true;
            panel->setScale(1.0);

                SAT_TestWidget* widget = new SAT_TestWidget(SAT_Rect(10,10,80,20));
                panel->appendChild(widget);
                widget->setName("text");
                //widget->WidgetLayout.anchor = SAT_WIDGET_LAYOUT_ANCHOR_CENTER;
                //widget->WidgetLayout.relative = SAT_WIDGET_LAYOUT_RELATIVE_PARENT;
                widget->WidgetOptions.redraw_if_hovering = true;
                widget->WidgetOptions.tooltip = true;
                widget->setTooltip("some nice tooltip text here...");

                SAT_TestWidget* widget2 = new SAT_TestWidget(SAT_Rect(10,40,80,20));
                panel->appendChild(widget2);
                widget2->setName("text2");
                //widget2->WidgetLayout.anchor = SAT_WIDGET_LAYOUT_ANCHOR_CENTER;
                //widget2->WidgetLayout.relative = SAT_WIDGET_LAYOUT_RELATIVE_PARENT;
                //widget2->WidgetOptions.redraw_if_hovering = true;
                widget2->WidgetOptions.tooltip = true;

    window->show();
    window->eventLoop();
    window->hide();
    delete window;

    return 0;
}

