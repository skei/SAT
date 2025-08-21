#pragma once

#include "base/sat_base.h"
#include "gui/sat_gui_base.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

#if defined SAT_PAINTER_X11
    #include "gui/system/x11/sat_x11_painter.h"
    typedef SAT_X11Painter SAT_ImplementedPainter;
#elif defined SAT_PAINTER_WIN32
    #error NOT IMPLEMENTED YET
#else
    #error NO PAINTER DEFINED
#endif

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_Painter
: public SAT_ImplementedPainter
{
    public:
        SAT_Painter(SAT_PainterOwner* AOwner, SAT_PaintTarget* ATarget);
        virtual ~SAT_Painter();
};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

SAT_Painter::SAT_Painter(SAT_PainterOwner* AOwner, SAT_PaintTarget* ATarget)
: SAT_ImplementedPainter(AOwner,ATarget)
{
}

SAT_Painter::~SAT_Painter()
{
}
