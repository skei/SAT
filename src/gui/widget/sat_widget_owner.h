#pragma once

#include "base/sat_base.h"

class SAT_Painter;
class SAT_Widget;
class SAT_MouseHandler;
class SAT_MouseState;

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_WidgetOwner
{
    public:
        virtual SAT_Painter*        do_widget_owner_get_painter(SAT_Widget* AWidget)        { return nullptr; }
        virtual uint32_t            do_widget_owner_get_width(SAT_Widget* AWidget)          { return 0; }
        virtual uint32_t            do_widget_owner_get_height(SAT_Widget* AWidget)         { return 0; }
        virtual sat_coord_t         do_widget_owner_get_scale(SAT_Widget* AWidget)          { return 1.0; }
        virtual bool                do_widget_owner_register_timer(SAT_Widget* AWidget)     { return false; }
        virtual bool                do_widget_owner_unregister_timer(SAT_Widget* AWidget)   { return false; }
};
