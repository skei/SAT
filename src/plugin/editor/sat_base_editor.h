#pragma once

#include "base/sat_base.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_BaseEditor
{
    public:
        SAT_BaseEditor()                                                    { }
        virtual ~SAT_BaseEditor()                                           { }

    public:

        virtual void setInitialSize(uint32_t AWidth, uint32_t AHeight, double AScale, bool AProportional) {}

    public: // clap gui

        virtual bool create()                                           { return true; }
        virtual void destroy()                                          { }
        virtual bool set_scale(double scale)                            { return true; }
        virtual bool get_size(uint32_t *width, uint32_t *height)        { return false; }
        virtual bool can_resize()                                       { return true; }
        virtual bool get_resize_hints(clap_gui_resize_hints_t *hints)   { return false; }
        virtual bool adjust_size(uint32_t *width, uint32_t *height)     { return true; }
        virtual bool set_size(uint32_t width, uint32_t height)          { return true; }
        virtual bool set_parent(intptr_t window)                        { return true; }
        virtual bool set_transient(intptr_t window)                     { return true; }
        virtual void suggest_title(const char *title)                   { }
        virtual bool show()                                             { return true; }
        virtual bool hide()                                             { return true; }

};
