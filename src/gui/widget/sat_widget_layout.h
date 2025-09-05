#pragma once

#include "base/sat_base.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

struct SAT_WidgetLayout
{
    uint32_t        anchor                  = SAT_WIDGET_LAYOUT_ANCHOR_TOP_LEFT;    // snap widget pos to parent
    uint32_t        stretch                 = SAT_WIDGET_LAYOUT_STRETCH_NONE;       // stretch widget sides (after snapping)
    uint32_t        crop                    = SAT_WIDGET_LAYOUT_CROP_NONE;          // crop widget rect out of 'available' layout rect (for following widgets)
    uint32_t        relative                = SAT_WIDGET_LAYOUT_RELATIVE_NONE;      // pos/size relative to parent, layout (percentages)
    uint32_t        stack                   = SAT_WIDGET_LAYOUT_STACK_NONE;         // horiz/vert stacked (icon view)
    SAT_Rect        inner_border            = {0,0,0,0};                            // border around child widgets
    SAT_Rect        outer_border            = {0,0,0,0};                            // border around widget itself (in parent widget)
    SAT_Point       spacing                 = {0,0};                                // space between widgets
    SAT_Point       minSize                 = {-1,-1};                              // minimum widget size (-1 for none)
    SAT_Point       maxSize                 = {-1,-1};                              // maximum widget size (-1 for none)
};
