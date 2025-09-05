#pragma once

#include "base/sat_base.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

struct SAT_WidgetOptions
{
    bool            auto_capture            = true;                                 // auto capture mouse when clicking
    bool            auto_clip               = true;                                 // clip child widgets
    bool            auto_cursor_shape       = true;                                 // set cursor shape when hovering over widget
    bool            auto_cursor_lock        = true;                                 // lock cursor in place (when dragging)
    bool            auto_cursor_hide        = true;                                 // auto hide cursor when dragging
    bool            auto_hint               = false;                                // auto send hint when hovering
    bool            auto_size               = false;                                // scale/zoom widget (content) relative to rect/size (f.ex. font size)
    bool            want_hover_events       = false;                                // want hover, move, etc mouse events even when not captured
    bool            realign_if_invisible    = false;                                // realign (child) widgets, even if not visible (menus, etc)
    bool            auto_redraw_hover       = false;                                // realign (child) widgets, even if not visible (menus, etc)
};