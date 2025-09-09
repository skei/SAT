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
        background->Layout.stretch = SAT_WIDGET_LAYOUT_STRETCH_ALL;
        //background->setScale(1.0);

            SAT_PanelWidget* panel = new SAT_PanelWidget(SAT_Rect(10,10,100,100));
            background->appendChild(panel);
            panel->setName("panel");
            //panel->Layout.stretch = SAT_WIDGET_LAYOUT_STRETCH_ALL;
            //panel->Options.auto_redraw_hover = true;
            panel->setScale(1.0);


                SAT_TestWidget* widget1 = new SAT_TestWidget(SAT_Rect(10,10,80,20));
                panel->appendChild(widget1);
                widget1->setName("widget1");
                widget1->setTooltip("widget1 tooltip");
                // widget1->Layout.anchor = SAT_WIDGET_LAYOUT_ANCHOR_CENTER;
                // widget1->Layout.relative = SAT_WIDGET_LAYOUT_RELATIVE_PARENT;

                widget1->Options.wantUncapturedHover = true;
                widget1->Options.captureHover = true;
                widget1->Options.redrawIfHovering = true;

                // widget1->Options.hasTooltip = true;

                // widget1->Options.wantDoubleClick = true;
                // widget1->Options.wantLongPress = true;
                // widget1->Options.wantStartDrag = true;

                SAT_TestWidget* widget2 = new SAT_TestWidget(SAT_Rect(10,40,80,20));
                panel->appendChild(widget2);
                widget2->setName("widget2");
                widget2->setTooltip("widget2 tooltip");
                // widget2->Layout.anchor = SAT_WIDGET_LAYOUT_ANCHOR_CENTER;
                // widget2->Layout.relative = SAT_WIDGET_LAYOUT_RELATIVE_PARENT;

                // widget2->Options.wantHoverMove = true;
                // widget2->Options.captureHoverMove = true;
                // widget2->Options.redrawIfHovering = true;

                // widget2->Options.hasTooltip = true;

                // widget2->Options.wantDoubleClick = true;
                // widget2->Options.wantLongPress = true;
                // widget2->Options.wantStartDrag = true;
                


    window->show();
    window->eventLoop();
    window->hide();
    delete window;

    return 0;
}

