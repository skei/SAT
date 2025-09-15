#pragma once

#include "base/sat_base.h"
#include "gui/keyboard/sat_base_keyboard_handler.h"
#include "gui/window/sat_base_window.h"
#include "gui/sat_widget.h"

//------------------------------
//
//------------------------------

// class SAT_KeyboardHandler;

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_KeyboardState
{
    public:
        SAT_KeyboardState(SAT_BaseKeyboardHandler* AHandler);
        virtual ~SAT_KeyboardState();
    public:
        virtual void                enter(int32_t AFromState)           { }
        virtual void                leave(int32_t AToState)             { }
    public:
        virtual int32_t             timer(double ADelta)                { return SAT_KEYBOARD_STATE_NONE; }
        virtual int32_t             press(SAT_KeyboardEvent* AEvent)    { return SAT_KEYBOARD_STATE_NONE; }
        virtual int32_t             release(SAT_KeyboardEvent* AEvent)  { return SAT_KEYBOARD_STATE_NONE; }
    public:
        SAT_BaseKeyboardHandler*    handler = nullptr;
        SAT_WidgetWindow*           window  = nullptr;
        int32_t                     type    = SAT_KEYBOARD_STATE_NONE;
        const char*                 name    ="";
    protected:
        void                        sendGesture(SAT_KeyboardGesture* AGesture);
};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

SAT_KeyboardState::SAT_KeyboardState(SAT_BaseKeyboardHandler* AHandler)
{
    handler = AHandler;
    window = AHandler->getWindow();
}

SAT_KeyboardState::~SAT_KeyboardState()
{
}

//------------------------------
//
//------------------------------

void SAT_KeyboardState::sendGesture(SAT_KeyboardGesture* AGesture)
{
    // SAT_KeyboardGesture gesture =
    // {
    //     .type = AGesture
    // };
    // SAT_Widget* widget = activeWidget();
    // if (widget && (widget->Options.wantKeyboardGestures & AGesture))
    // {
    //     widget->on_widget_keyboard_gesture(&gesture,this);
    // }
}
