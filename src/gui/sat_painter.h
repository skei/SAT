#pragma once

#include "base/sat_base.h"
#include "gui/sat_gui_base.h"

typedef SAT_Array<SAT_Rect> SAT_ClipRectStack;

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
    public:
        void                beginPainting(uint32_t AWidth, uint32_t AHeight) override;
        void                endPainting() override;
    public:
        virtual void        pushClipRect(SAT_Rect ARect);
        virtual void        popClipRect();
        virtual SAT_Rect    getClipRect();
    public:
    public:
        SAT_ClipRectStack   MClipRectStack      = {};     
        SAT_Rect            MCurrentClipRect    = {};     

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

void SAT_Painter::beginPainting(uint32_t AWidth, uint32_t AHeight)
{
    SAT_ImplementedPainter::beginPainting(AWidth,AHeight);
    SAT_Rect rect = {0,0,AWidth,AHeight};
    setClip(rect);
    MCurrentClipRect = SAT_Rect(0,0,AWidth,AHeight);
}

void SAT_Painter::endPainting()
{
    resetClip();
    SAT_ImplementedPainter::endPainting();
}

void SAT_Painter::pushClipRect(SAT_Rect ARect)
{
    MClipRectStack.push(MCurrentClipRect);
    setClip(ARect);
    MCurrentClipRect = ARect;
}

void SAT_Painter::popClipRect()
{
    SAT_Rect rect = MClipRectStack.pop();
    setClip(rect);
    MCurrentClipRect = rect;
}

SAT_Rect SAT_Painter::getClipRect()
{
    return MCurrentClipRect;
}




