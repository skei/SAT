#pragma once

#include "base/sat_base.h"

class SAT_Widget;

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

struct SAT_WidgetRecursive
{
    SAT_Rect        rect                    = {};
    SAT_Rect        clip_rect               = {};
    SAT_Rect        content_rect            = {};
    sat_coord_t     scale                   = 1.0;
    SAT_Widget*     opaque_parent           = nullptr;
 // bool            active                  = true;
 // bool            enabled                 = true;
 // bool            opaque                  = true;
 // bool            visible                 = true;
 // SAT_Skin        skin                    = {};
 // SAT_Color       background              = SAT_Grey;
};