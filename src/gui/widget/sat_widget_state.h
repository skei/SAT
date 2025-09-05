#pragma once

#include "base/sat_base.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

struct SAT_WidgetState
{
    bool            active                  = true;                                 // handles events
    bool            enabled                 = true;                                 // if false, draw 'disabled'state (greyed out)
    bool            opaque                  = true;                                 // set to true if widget fills it's entire rect
    bool            visible                 = true;                                 // drawing/alignment
    bool            hovering                = false;                                // mouse cursor is hovering over widget
    bool            interacting             = false;                                // interacting with widget
};
