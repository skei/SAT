#pragma once

#include "base/sat.h"
#include "gui/input/sat_input_state.h"
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

        uint32_t    on_widget_input_event(SAT_InputEvent* AEvent) override;
        void        on_widget_input_gesture(SAT_InputGesture* AGesture) override;

        // void        on_widget_pre_paint(SAT_PaintContext* AContext) override;
        // void        on_widget_post_paint(SAT_PaintContext* AContext) override;

};

//------------------------------
//
//------------------------------

SAT_TestWidget::SAT_TestWidget(SAT_Rect ARect)
: SAT_TextWidget(ARect)
{
    MTypeName = "SAT_TestWidget";
    MSkin = SAT.GUI->SKINS.find("Default Text");
    Options.wantInputEvents = SAT_INPUT_EVENT_ALL;
    Options.wantInputGestures = SAT_INPUT_GESTURE_ALL;
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

uint32_t SAT_TestWidget::on_widget_input_event(SAT_InputEvent* AEvent)
{
    // uint32_t event_type = AEvent->type;
    // const char* event_name = AEvent->handler->eventName(event_type);
    // SAT_PRINT("%s : %s\n",getName(),event_name);
    return SAT_INPUT_EVENT_RESPONSE_NONE;
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

void SAT_TestWidget::on_widget_input_gesture(SAT_InputGesture* AGesture)
{
    uint32_t gesture_type = AGesture->type;
    const char* event_name = AGesture->handler->gestureName(gesture_type);
    SAT_PRINT("%s : %s - hovering: %s\n",getName(),event_name,AGesture->stateInfo->hoverWidget->getName());
}

//------------------------------
// testing pre/post paint
//------------------------------

// void SAT_TestWidget::on_widget_pre_paint(SAT_PaintContext* AContext)
// {
//     SAT_Rect rect = MRect;
//     rect.grow(5);
//     SAT_Painter* painter = AContext->painter;
//     painter->setFillColor(SAT_Red);
//     painter->fillRect(rect);
// }

// void SAT_TestWidget::on_widget_post_paint(SAT_PaintContext* AContext)
// {
//     SAT_Rect rect = MRect;
//     rect.shrink(5);
//     SAT_Painter* painter = AContext->painter;
//     painter->setDrawColor(SAT_Green);
//     painter->drawRect(rect);
// }
