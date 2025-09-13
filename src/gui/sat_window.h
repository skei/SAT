#pragma once

#include "base/sat_base.h"
#include "gui/keyboard/sat_keyboard_handler.h"
#include "gui/mouse/sat_mouse_handler.h"
#include "gui/window/sat_widget_window.h"
#include "gui/sat_animator.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_Window
: public SAT_WidgetWindow
{
    public:
        SAT_Window(uint32_t AWidth, uint32_t AHeight, intptr_t AParent=0);
        virtual ~SAT_Window();
     public:
        void    handleTimer(uint32_t ATimerId, double ADelta, bool AInTimerThread=false) override;
        void    changeMouseState(SAT_MouseState* AState) override;
        void    changeKeyboardState(SAT_KeyboardState* AState) override;
        SAT_MouseHandler*       getMouseHandler() override;
        SAT_KeyboardHandler*    getKeyboardHandler() override;

    public:
        void    on_window_show() override;
        // void    on_window_hide() override;
        // void    on_window_move(int32_t AXpos, int32_t AYpos) override;
        // void    on_window_resize(uint32_t AWidth, uint32_t AHeight) override;
        void    on_window_mouse_click(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATime) override;
        void    on_window_mouse_release(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATime) override;
        void    on_window_mouse_move(int32_t AXpos, int32_t AYpos, uint32_t AState, uint32_t ATime) override;
        void    on_window_mouse_enter(int32_t AXpos, int32_t AYpos, uint32_t ATime) override;
        void    on_window_mouse_leave(int32_t AXpos, int32_t AYpos, uint32_t ATime) override;
        void    on_window_key_press(uint32_t AKey, uint32_t AChar, uint32_t AState, uint32_t ATime) override;
        void    on_window_key_release(uint32_t AKey, uint32_t AChar, uint32_t AState, uint32_t ATime) override;
        // void    on_window_client_message(uint32_t AData) override;  
        // void    on_window_timer(uint32_t ATimerId, double ADelta) override;

    public:

        // SAT_MouseHandler*   do_widget_owner_get_mouse_handler(SAT_Widget* AWidget) override;
        // SAT_MouseState*     do_widget_owner_get_mouse_state(SAT_Widget* AWidget) override;

    public:
        void    do_widget_update(SAT_Widget* AWidget, uint32_t AIndex=0) override;
        void    do_widget_realign(SAT_Widget* AWidget, uint32_t AMode=SAT_WIDGET_REALIGN_PARENT) override;
        void    do_widget_redraw(SAT_Widget* AWidget, uint32_t AMode=SAT_WIDGET_REDRAW_SELF) override;
        void    do_widget_anim(SAT_Widget* AWidget, SAT_AnimChain* AChain) override;
        void    do_widget_notify(SAT_Widget* AWidget, uint32_t AType, int32_t AValue) override;
        void    do_widget_hint(SAT_Widget* AWidget, uint32_t AType, const char* AHint) override;
        void    do_widget_modal(SAT_Widget* AWidget) override;
        void    do_widget_cursor(SAT_Widget* AWidget, int32_t ACursor) override;
        void    do_widget_capture_mouse(SAT_Widget* AWidget) override;
        void    do_widget_capture_keyboard(SAT_Widget* AWidget) override;
    private:
        SAT_Animator        MAnimator               = {};
        SAT_KeyboardHandler MKeyboard               = SAT_KeyboardHandler(this);
        SAT_MouseHandler    MMouse                  = SAT_MouseHandler(this);
     // SAT_Widget*         MKeyCapturedWidget      = nullptr;
        int32_t             MCurrentMouseCursor     = SAT_CURSOR_DEFAULT;

};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

SAT_Window::SAT_Window(uint32_t AWidth, uint32_t AHeight, intptr_t AParent)
: SAT_WidgetWindow(AWidth,AHeight,AParent)
{
    MTypeName = "SAT_Window";
}

SAT_Window::~SAT_Window()
{
}

//------------------------------
//
//------------------------------

void SAT_Window::handleTimer(uint32_t ATimerId, double ADelta, bool AInTimerThread)
{
    // handleMouseTimer(ADelta);
    MKeyboard.timer(ADelta);
    MMouse.timer(ADelta);
    MAnimator.process(ADelta);
    SAT_WidgetWindow::handleTimer(ATimerId,ADelta,AInTimerThread);
}

void SAT_Window::changeMouseState(SAT_MouseState* AState)
{
    //SAT_PRINT("state change %i\n",AState->id());
}

void SAT_Window::changeKeyboardState(SAT_KeyboardState* AState)
{
    //SAT_PRINT("state change %i\n",AState->id());
}

SAT_MouseHandler* SAT_Window::getMouseHandler()
{
    return &MMouse;
}

SAT_KeyboardHandler* SAT_Window::getKeyboardHandler()
{
    return &MKeyboard;
}

//------------------------------
// base window
//------------------------------

void SAT_Window::on_window_show()
{
    // MMouse.currentTime = 0.0;
    // MMouse.tooltipAllowed = true;
    SAT_WidgetWindow::on_window_show();
}

// void SAT_Window::on_window_hide()
// {
//     SAT_WidgetWindow::on_window_hide();
// }

// void SAT_Window::on_window_move(int32_t AXpos, int32_t AYpos)
// {
//     SAT_WidgetWindow::on_window_move(AXpos,AYpos);
// }

// void SAT_Window::on_window_resize(uint32_t AWidth, uint32_t AHeight)
// {
//     SAT_WidgetWindow::on_window_resize(AWidth,AHeight);
// }

void SAT_Window::on_window_mouse_click(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATime)
{
    SAT_MouseCoords pos = {AXpos,AYpos};
    MMouse.click(pos,AButton,AState,ATime);
    SAT_WidgetWindow::on_window_mouse_click(AXpos,AYpos,AButton,AState,ATime);
}

void SAT_Window::on_window_mouse_release(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATime)
{
    SAT_MouseCoords pos = {AXpos,AYpos};
    MMouse.release(pos,AButton,AState,ATime);
    SAT_WidgetWindow::on_window_mouse_release(AXpos,AYpos,AButton,AState,ATime);
}

void SAT_Window::on_window_mouse_move(int32_t AXpos, int32_t AYpos, uint32_t AState, uint32_t ATime)
{
    SAT_MouseCoords pos = {AXpos,AYpos};
    MMouse.move(pos,AState,ATime);
    SAT_WidgetWindow::on_window_mouse_move(AXpos,AYpos,AState,ATime);
}

void SAT_Window::on_window_mouse_enter(int32_t AXpos, int32_t AYpos, uint32_t ATime)
{
    SAT_MouseCoords pos = {AXpos,AYpos};
    MMouse.enter(pos,ATime);
    SAT_WidgetWindow::on_window_mouse_enter(AXpos,AYpos,ATime);
}

void SAT_Window::on_window_mouse_leave(int32_t AXpos, int32_t AYpos, uint32_t ATime)
{
    SAT_MouseCoords pos = {AXpos,AYpos};
    MMouse.leave(pos,ATime);
    SAT_WidgetWindow::on_window_mouse_leave(AXpos,AYpos,ATime);
}

void SAT_Window::on_window_key_press(uint32_t AKey, uint32_t AChar, uint32_t AState, uint32_t ATime)
{
    MKeyboard.press(AKey,AState,ATime);
    SAT_WidgetWindow::on_window_key_press(AKey,AChar,AState,ATime);
}

void SAT_Window::on_window_key_release(uint32_t AKey, uint32_t AChar, uint32_t AState, uint32_t ATime)
{
    MKeyboard.release(AKey,AState,ATime);
    SAT_WidgetWindow::on_window_key_release(AKey,AChar,AState,ATime);
}

// void SAT_Window::on_window_client_message(uint32_t AData)  
// {
//     SAT_WidgetWindow::on_window_client_message(AData);
// }

// // [GUI THREAD]
// void SAT_Window::on_window_timer(uint32_t ATimerId, double ADelta)
// {
//     //MMouse.timer(ADelta); // see handleTimer..
//     SAT_WidgetWindow::on_window_timer(ATimerId,ADelta);
// }

//------------------------------
// widget owner
//------------------------------

// SAT_MouseHandler* SAT_Window::do_widget_owner_get_mouse_handler(SAT_Widget* AWidget)
// {
//     return &MMouse;
// }

// SAT_MouseState* SAT_Window::do_widget_owner_get_mouse_state(SAT_Widget* AWidget)
// {
//     return MMouse.getCurrentState();
// }

//------------------------------
// do_widget
//------------------------------

void SAT_Window::do_widget_update(SAT_Widget* AWidget, uint32_t AIndex)
{
    SAT_WidgetWindow::do_widget_update(AWidget,AIndex);
}

void SAT_Window::do_widget_realign(SAT_Widget* AWidget, uint32_t AMode)
{
    SAT_WidgetWindow::do_widget_realign(AWidget,AMode);
}

void SAT_Window::do_widget_redraw(SAT_Widget* AWidget, uint32_t AMode)
{
    SAT_WidgetWindow::do_widget_redraw(AWidget,AMode);
}

void SAT_Window::do_widget_anim(SAT_Widget* AWidget, SAT_AnimChain* AChain)
{
    //SAT_PRINT("widget '%s'\n",AWidget->getName());
    MAnimator.appendChain(AChain);
    //SAT_WidgetWindow::do_widget_anim(AWidget,AChain);
}

void SAT_Window::do_widget_notify(SAT_Widget* AWidget, uint32_t AType, int32_t AValue)
{
    SAT_WidgetWindow::do_widget_notify(AWidget,AType,AValue);
}

void SAT_Window::do_widget_hint(SAT_Widget* AWidget, uint32_t AType, const char* AHint)
{
    SAT_WidgetWindow::do_widget_hint(AWidget,AType,AHint);
}

void SAT_Window::do_widget_modal(SAT_Widget* AWidget)
{
    //SAT_PRINT("widget '%s'\n",AWidget->getName());
    // MMouse.modalWidget = AWidget;
    //SAT_WidgetWindow::do_widget_modal(AWidget);
}

void SAT_Window::do_widget_cursor(SAT_Widget* AWidget, int32_t ACursor)
{
    SAT_WidgetWindow::do_widget_cursor(AWidget,ACursor);
    switch(ACursor)
    {
        case SAT_CURSOR_SHOW:  
            MMouse.showCursor();
            break;
        case SAT_CURSOR_HIDE:
            MMouse.hideCursor();
            break;
        case SAT_CURSOR_LOCK:
            MMouse.lockCursor(AWidget);
            break;
        case SAT_CURSOR_UNLOCK:
            MMouse.unlockCursor();
            break;
        case SAT_CURSOR_RESET:
            //MMouse.popCursor();
            MMouse.resetCursor();
            break;
        default:
            //MMouse.pushCursor(ACursor);
            MMouse.setCursor(ACursor);
            break;
    }

}

void SAT_Window::do_widget_capture_mouse(SAT_Widget* AWidget)
{
    MMouse.captureWidget(AWidget);
    SAT_WidgetWindow::do_widget_capture_mouse(AWidget);
    //SAT_PRINT("widget '%s'\n",AWidget->getName());
}

void SAT_Window::do_widget_capture_keyboard(SAT_Widget* AWidget)
{
    //SAT_PRINT("widget '%s'\n",AWidget->getName());
    MKeyboard.captureWidget(AWidget);
    //MKeyCapturedWidget = AWidget;
    //MKeys.captureWidget(AWidget);
    SAT_WidgetWindow::do_widget_capture_keyboard(AWidget);
}
