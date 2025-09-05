#pragma once

#include "base/sat_base.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_BaseWindow
{
    public:
        SAT_BaseWindow(uint32_t AWidth, uint32_t AHeight, intptr_t AParent=0) {}
        virtual ~SAT_BaseWindow() {}
    public:
        virtual uint32_t    getWidth() = 0;
        virtual uint32_t    getHeight() = 0;
    public:
        virtual void        show() = 0;
        virtual void        hide() = 0;
        virtual void        setPos(int32_t AXpos, int32_t AYpos) = 0;
        virtual void        setSize(uint32_t AWidth, uint32_t AHeight) = 0;
        virtual void        setTitle(const char* ATitle) = 0;
        virtual void        showMouseCursor() = 0;
        virtual void        hideMouseCursor() = 0;
        virtual void        grabMouseCursor() = 0;
        virtual void        releaseMouseCursor() = 0;
        virtual void        setMouseCursorPos(int32_t AXpos, int32_t AYpos) = 0;
        virtual void        setMouseCursorShape(int32_t ACursor) = 0;
        virtual void        reparent(intptr_t AParent) = 0;
        virtual void        invalidate(int32_t AXpos, int32_t AYpos, uint32_t AWidth, uint32_t AHeight) = 0;
        virtual void        sendClientMessage(uint32_t AData, uint32_t AType) = 0;
        virtual void        eventLoop() = 0;
        virtual void        startEventThread() = 0;
        virtual void        stopEventThread() = 0;
    public:
        virtual void        on_window_show() {}
        virtual void        on_window_hide() {}
        virtual void        on_window_move(int32_t AXpos, int32_t AYpos) {}
        virtual void        on_window_resize(uint32_t AWidth, uint32_t AHeight) {}
        virtual void        on_window_paint(int32_t AXpos, int32_t AYpos, uint32_t AWidth, uint32_t AHeight) {}
        virtual void        on_window_mouse_click(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATime) {}
        virtual void        on_window_mouse_release(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATime) {}
        virtual void        on_window_mouse_move(int32_t AXpos, int32_t AYpos, uint32_t AState, uint32_t ATime) {}
        virtual void        on_window_key_press(uint32_t AKey, uint32_t AChar, uint32_t AState, uint32_t ATime) {}
        virtual void        on_window_key_release(uint32_t AKey, uint32_t AChar, uint32_t AState, uint32_t ATime) {}
        virtual void        on_window_mouse_enter(int32_t AXpos, int32_t AYpos, uint32_t ATime) {}
        virtual void        on_window_mouse_leave(int32_t AXpos, int32_t AYpos, uint32_t ATime) {}
        virtual void        on_window_client_message(uint32_t AData) {}  
        virtual void        on_window_timer(uint32_t ATimerId, double ADelta) {}
};
