#pragma once

#include "base/sat_base.h"
#include "gui/sat_gui_base.h"

typedef SAT_Stack<SAT_Rect,SAT_PAINTER_CLIP_RECT_STACK_SIZE> SAT_ClipRectStack;

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
        virtual void        pushClipRectAndReset();
        virtual void        pushOverlappingClipRect(SAT_Rect ARect);
        virtual void        popClipRect();
        virtual void        resetClipRectStack();
        virtual SAT_Rect    getClipRect();
        virtual void        setClipRect(SAT_Rect ARect);

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
    SAT_Assert(MClipRectStack.isEmpty());
}

/*
    start painting..
    - call implemented painters
        (win32 needs the negin/endPaint thing to get the PaintDC, iirc)
    - set clipping
*/

void SAT_Painter::beginPainting(uint32_t AWidth, uint32_t AHeight)
{
    SAT_ImplementedPainter::beginPainting(AWidth,AHeight);
    //MClipRectStack.reset();
    SAT_Assert(MClipRectStack.isEmpty());
    SAT_Rect rect = {0,0,AWidth,AHeight};
    setClip(rect);
    MCurrentClipRect = SAT_Rect(0,0,AWidth,AHeight);
}

/*
    end painting..
    - reset clipping
    - flush? blit to screen? finalize?
*/

void SAT_Painter::endPainting()
{
    SAT_Assert(MClipRectStack.isEmpty());
    resetClip();
    SAT_ImplementedPainter::endPainting();
}

/*
    push the current clip rect on the stack (to remember it)
    and set new clip rect
    some backends only shrinks the clipping rect, so we reset it first..
    (cairo comes to mind, been a while...)
*/

void SAT_Painter::pushClipRect(SAT_Rect ARect)
{
    // SAT_TRACE;
    MClipRectStack.push(MCurrentClipRect);
    MCurrentClipRect = ARect;
    resetClip();
    setClip(ARect);
}

/*
    find overlap betwen current c.ip react and argument
    push the current clip rect, and clip to new (overlap)
    (rect within rect)
*/

void SAT_Painter::pushOverlappingClipRect(SAT_Rect ARect)
{
    SAT_Rect r = ARect;
    r.overlap(MCurrentClipRect);
    pushClipRect(r);
}

/*
    push the current clip rect onto the stack,
    and reset clipping
*/

void SAT_Painter::pushClipRectAndReset()
{
    MClipRectStack.push(MCurrentClipRect);
    resetClip();
    // MCurrentClipRect = SAT_Rect(0);
}

/*
    pop rect off the stack, and set cliping to it
*/

void SAT_Painter::popClipRect()
{
    SAT_Rect rect = MClipRectStack.pop();
    MCurrentClipRect = rect;
    setClip(rect);
}

void SAT_Painter::resetClipRectStack()
{
    MClipRectStack.reset();
}

SAT_Rect SAT_Painter::getClipRect()
{
    return MCurrentClipRect;
}

void SAT_Painter::setClipRect(SAT_Rect ARect)
{
    MCurrentClipRect = ARect;
}
