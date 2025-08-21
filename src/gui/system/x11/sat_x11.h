#pragma once

//----------------------------------------------------------------------

#include <X11/Xlib.h>
#include <X11/Xlib-xcb.h>
//#include <X11/Xft/Xft.h>

#include <xcb/xcb.h>
#include <xcb/xcb_util.h>
//#include <xcb/xproto.h>
#include <xcb/xcb_cursor.h>
#include <xcb/xcb_image.h>
#include <xcb/xcb_keysyms.h>
#include <xkbcommon/xkbcommon.h>

// TODO: #ifdef explicit, save/restore prev?
#define explicit explicit_
    #include <xcb/xkb.h>
#undef explicit

#include "base/sat_base.h"

//----------------------------------------------------------------------

struct SAT_XcbPolyText8 {
    uint8_t*  data  = nullptr;
    size_t    used  = 0;
};

//----------------------------------------------------------------------

// https://tronche.com/gui/x/xlib/appendix/b/

const char* SAT_X11_WM_CURSORS[/*SAT_CURSOR_COUNT*/] =
{
    "left_ptr",             // SAT_CURSOR_DEFAULT
    "left_ptr",             // SAT_CURSOR_ARROW
    "sb_up_arrow",          // SAT_CURSOR_ARROW_UP
    "sb_down_arrow",        // SAT_CURSOR_ARROW_DOWN
    "sb_left_arrow",        // SAT_CURSOR_ARROW_LEFT
    "sb_right_arrow",       // SAT_CURSOR_ARROW_RIGHT
    "sb_v_double_arrow",    // SAT_CURSOR_ARROW_UP_DOWN
    "sb_h_double_arrow",    // SAT_CURSOR_ARROW_LEFT_RIGHT
    "top_left_corner",      // SAT_CURSOR_ARROW_TOP_LEFT
    "top_right_corner",     // SAT_CURSOR_ARROW_TOP_RIGHT
    "bottom_left_corner",   // SAT_CURSOR_ARROW_BOTTOM_LEFT
    "bottom_right_corner",  // SAT_CURSOR_ARROW_BOTTOM_RIGHT
    "left_side",            // SAT_CURSOR_ARROW_LEFT_SIDE
    "right_side",           // SAT_CURSOR_ARROW_RIGHT_SIDE
    "top_side",             // SAT_CURSOR_ARROW_TOP_SIDE
    "bottom_side",          // SAT_CURSOR_ARROW_BOTTOM_SIDE
    "fleur",                // SAT_CURSOR_MOVE
    "watch",                // SAT_CURSOR_WAIT
    "clock",                // SAT_CURSOR_ARROW_WAIT    !!!
    "hand1",                // SAT_CURSOR_HAND
    "hand2",                // SAT_CURSOR_FINGER
    "crosshair",            // SAT_CURSOR_CROSS
    "cross",                // SAT_CURSOR_CROSS2
    "pencil",               // SAT_CURSOR_PENCIL
    "plus",                 // SAT_CURSOR_PLUS
    "question_arrow",       // SAT_CURSOR_QUESTION
    "xterm",                // SAT_CURSOR_IBEAM
    "circle",               // SAT_CURSOR_ARROW_INVALID
    "crossed_circle",       // SAT_CURSOR_INVALID
    "pirate"                // SAT_CURSOR_X
};

//----------------------------------------------------------------------

// class SAT_X11Drawable
// {
//     public:
//         virtual xcb_drawable_t getDrawable() = 0;
// };

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

xcb_atom_t SAT_XcbGetInternAtom(xcb_connection_t *conn, const char *name)
{
    xcb_intern_atom_cookie_t cookie = xcb_intern_atom(conn ,0, strlen(name), name);
    xcb_intern_atom_reply_t *reply = xcb_intern_atom_reply(conn, cookie, NULL);
    //return !reply ? XCB_ATOM_STRING : reply->atom;
    return reply->atom;
}

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

