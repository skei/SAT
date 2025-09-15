#pragma once

#include "base/sat.h"
#include "gui/mouse/sat_mouse_state.h"
#include "gui/widget/visual/sat_text_widget.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_TestWidget
: public SAT_TextWidget
{
    public:
        SAT_TestWidget(SAT_Rect ARect);
        virtual ~SAT_TestWidget();
    public:

        uint32_t    on_widget_mouse_event(SAT_MouseEvent* AEvent) override;
        void        on_widget_mouse_gesture(SAT_MouseGesture* AGesture) override;

    protected:

};

//------------------------------
//
//------------------------------

SAT_TestWidget::SAT_TestWidget(SAT_Rect ARect)
: SAT_TextWidget(ARect)
{
    MTypeName = "SAT_TestWidget";
    MSkin = SAT.GUI->SKINS.find("DefaultText");
}

SAT_TestWidget::~SAT_TestWidget()
{
}

//------------------------------
//
//------------------------------

/*
struct SAT_MouseEvent
{
    uint32_t            type    = SAT_MOUSE_EVENT_NONE;
    SAT_MouseHandler*   handler = nullptr;
    SAT_MouseCoords     pos     = {0,0};
    uint32_t            button  = SAT_MOUSE_BUTTON_NONE;
    uint32_t            modkeys = SAT_STATE_KEY_NONE;
    double              time    = 0.0;
};
*/

uint32_t SAT_TestWidget::on_widget_mouse_event(SAT_MouseEvent* AEvent)
{
    uint32_t event_type = AEvent->type;
    const char* event_name = AEvent->handler->eventName(event_type);
    SAT_PRINT("%s : %s\n",getName(),event_name);
    return SAT_MOUSE_EVENT_RESPONSE_NONE;
}

/*
struct SAT_MouseGesture
{
    uint32_t            type    = SAT_MOUSE_GESTURE_NONE;
    SAT_MouseHandler*   handler = nullptr;
    // SAT_MouseCoords     pos     = {0,0};
    // uint32_t            button  = SAT_MOUSE_BUTTON_NONE;
    // uint32_t            modkeys = SAT_STATE_KEY_NONE;
    // double              time    = 0.0;
};
*/

void SAT_TestWidget::on_widget_mouse_gesture(SAT_MouseGesture* AGesture)
{
}
