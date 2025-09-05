#pragma once

#include "base/sat_base.h"

class SAT_Painter;

//----------------------------------------------------------------------
//
//
//
//---------------------------------------------------------------------

struct SAT_PaintContext
{
    SAT_Painter*    painter         = nullptr;
    SAT_Rect        update_rect     = {};
    uint32_t        current_frame   = 0;
    double          current_time    = 0.0;
    double          previous_time   = 0.0;
};
