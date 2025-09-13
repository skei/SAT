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
        uint32_t on_widget_mouse_event(uint32_t AEvent, SAT_MouseState* AState) override;
        uint32_t on_widget_keyboard_event(uint32_t AEvent, SAT_KeyboardState* AState) override;
        // uint32_t on_widget_mouse_gesture(uint32_t AGesture, SAT_MouseState* AState) override;
        // uint32_t on_widget_keyboard_gesture(uint32_t AGesture, SAT_KeyboardState* AState) override;
    protected:
        // bool                MIsSelected     = false;
        // bool                MClicked        = false;
        // bool                MDragging       = false;
        // uint32_t            MDragButton     = SAT_MOUSE_BUTTON_NONE;

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

uint32_t SAT_TestWidget::on_widget_mouse_event(uint32_t AEvent, SAT_MouseState* AState)
{
    //const char* name = getName();
    //SAT_PRINT("%s : event: %i state: %i\n",name,AEvent,AState->id());
    return SAT_MOUSE_EVENT_RESPONSE_NONE;
}

uint32_t SAT_TestWidget::on_widget_keyboard_event(uint32_t AEvent, SAT_KeyboardState* AState)
{
    //const char* name = getName();
    //SAT_PRINT("%s : event: %i state: %i\n",name,AEvent,AState->id());
    return SAT_KEYBOARD_EVENT_RESPONSE_NONE;
}

// uint32_t SAT_TestWidget::on_widget_mouse_gesture(uint32_t AGesture, SAT_MouseState* AState)
// {
//     // const char* name = getName();
//     // SAT_PRINT("%s : gesture: %i state: %i\n",name,AGesture,AState->id());
//     return SAT_MOUSE_GESTURE_RESPONSE_NONE;
// }

// uint32_t SAT_TestWidget::on_widget_keyboard_gesture(uint32_t AGesture, SAT_KeyboardState* AState)
// {
//     // const char* name = getName();
//     // SAT_PRINT("%s : gesture: %i state: %i\n",name,AGesture,AState->id());
//     return SAT_KEYBOARD_GESTURE_RESPONSE_NONE;
// }


#if 0

void SAT_TestWidget::on_widget_mouse_click(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATime)
{
    SAT_PRINT("%s : x %i y %i b %i\n",getName(),AXpos,AYpos,AButton);
    if (AButton == SAT_BUTTON_LEFT)
    {
        MIsSelected = !MIsSelected;
        State.highlighted = MIsSelected;
        do_widget_redraw(this);
        //MClicked = true;
    }
}

void SAT_TestWidget::on_widget_mouse_double_click(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATime)
{
    SAT_PRINT("%s : x %i y %i b %i\n",getName(),AXpos,AYpos,AButton);
}

void SAT_TestWidget::on_widget_mouse_longpress(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATime)
{
    SAT_PRINT("%s : x %i y %i b %i\n",getName(),AXpos,AYpos,AButton);
}

void SAT_TestWidget::on_widget_mouse_start_drag(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATime)
{
    //SAT_PRINT("%s : x %i y %i\n",getName(),AXpos,AYpos);
    if (!MDragging)
    {
        do_widget_cursor(this,SAT_CURSOR_LOCK);
        do_widget_cursor(this,SAT_CURSOR_HIDE);
        MDragging = true;
        MDragButton = AButton;
    }
}

void SAT_TestWidget::on_widget_mouse_release(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATime)
{
    //SAT_PRINT("%s : x %i y %i b %i\n",getName(),AXpos,AYpos,AButton);
    if (MDragging && (AButton == MDragButton))
    {
        do_widget_cursor(this,SAT_CURSOR_UNLOCK);
        do_widget_cursor(this,SAT_CURSOR_SHOW);
        MDragging = false;
    }
};

void SAT_TestWidget::on_widget_mouse_move(int32_t AXpos, int32_t AYpos, uint32_t AState, uint32_t ATime)
{
    SAT_PRINT("%s : x %i y %i\n",getName(),AXpos,AYpos);
}

void SAT_TestWidget::on_widget_mouse_enter(SAT_Widget* AFrom, int32_t AXpos, int32_t AYpos, uint32_t ATime)
{
    SAT_TextWidget::on_widget_mouse_enter(AFrom,AXpos,AYpos,ATime);
    if (AFrom)
    {
        //SAT_PRINT("%s : x %i y %i from %s\n",getName(),AXpos,AYpos,AFrom->getName());
    }
    else
    {
        //SAT_PRINT("%s : x %i y %i from NULL\n",getName(),AXpos,AYpos);
    }
}

void SAT_TestWidget::on_widget_mouse_leave(SAT_Widget* ATo, int32_t AXpos, int32_t AYpos, uint32_t ATime)
{
    SAT_TextWidget::on_widget_mouse_leave(ATo,AXpos,AYpos,ATime);
    if (ATo)
    {
        //SAT_PRINT("%s : x %i y %i to %s\n",getName(),AXpos,AYpos,ATo->getName());
    }
    else
    {
        //SAT_PRINT("%s : x %i y %i to NULL\n",getName(),AXpos,AYpos);
    }
}

#endif

