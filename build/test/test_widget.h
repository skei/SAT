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

/*
    todo:
    
    keep visible if dragging:
        visibleIfHovering - captureMouse, captureHover

    look into this:
        hardcoded "one step up" redrawing".
        SAT_Widget.on_widget_mouse_leave:
        if autoHoverRedraw -> do_widget_redraw(REDRAW_PARENT)

*/

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

            SAT_PanelWidget* panel = new SAT_PanelWidget(SAT_Rect(10,10,500,400));
            background->appendChild(panel);
            panel->setName("panel");
            //panel->Layout.stretch = SAT_WIDGET_LAYOUT_STRETCH_ALL;
            //panel->Options.auto_redraw_hover = true;
            panel->setScale(1.0);

                SAT_TestWidget* widget1 = new SAT_TestWidget(SAT_Rect(50,10,200,100));
                panel->appendChild(widget1);
                widget1->setName("widget1");
                widget1->setTooltip("widget1 tooltip");
                // widget1->Layout.anchor = SAT_WIDGET_LAYOUT_ANCHOR_CENTER;
                // widget1->Layout.relative = SAT_WIDGET_LAYOUT_RELATIVE_PARENT;

                widget1->Options.wantMouseEvents = SAT_MOUSE_EVENT_ALL;

                //----------

                SAT_TestWidget* widget2 = new SAT_TestWidget(SAT_Rect(50,120,200,100));
                panel->appendChild(widget2);
                widget2->setName("widget2");
                widget2->setTooltip("widget2 tooltip");
                // widget2->Layout.anchor = SAT_WIDGET_LAYOUT_ANCHOR_CENTER;
                // widget2->Layout.relative = SAT_WIDGET_LAYOUT_RELATIVE_PARENT;

                widget2->Options.wantMouseEvents = SAT_MOUSE_EVENT_ALL;

                //----------

                SAT_TestWidget* widget3 = new SAT_TestWidget(SAT_Rect(10,60,100,100));
                panel->appendChild(widget3);
                widget3->setName("widget3");
                widget3->setTooltip("widget3 tooltip");

                widget3->State.active = false;
                widget3->State.visible = false;
                widget3->Options.wantMouseEvents = SAT_MOUSE_EVENT_ALL;


    window->show();
    window->eventLoop();
    window->hide();
    delete window;

    return 0;
}

