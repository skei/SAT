#pragma once

#include "base/sat_base.h"
#include "gui/sat_gui_base.h"

// something weird is happening if we use an array...
// crashes in popClipRect

//typedef SAT_Array<SAT_Rect> SAT_ClipRectStack;

// performance should anyway be better using a hardcoded buffer..
// no resizing and reallocationg the buffer for every push/pop..
// (but we're limited to a max sack size..)

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
        virtual void        pushOverlappingClipRect(SAT_Rect ARect);
        virtual void        popClipRect();
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
    SAT_Assert(MClipRectStack.isEmpty());
    resetClip();
    SAT_ImplementedPainter::endPainting();
}

//   virtual void pushClip(SAT_Rect ARect) {
//     MClipStack.push(MClipRect);
//     MClipRect = ARect;
//     resetClip();
//     setClip(MClipRect.x,MClipRect.y,MClipRect.w,MClipRect.h);
//   }


void SAT_Painter::pushClipRect(SAT_Rect ARect)
{
    // SAT_TRACE;
    MClipRectStack.push(MCurrentClipRect);
    MCurrentClipRect = ARect;
    resetClip();
    setClip(ARect);
}

//   virtual void pushOverlappingClip(SAT_Rect ARect) {
//     SAT_Rect r = ARect;
//     r.overlap(MClipRect);
//     pushClip(r);
//   }


void SAT_Painter::pushOverlappingClipRect(SAT_Rect ARect)
{
    SAT_Rect r = ARect;
    r.overlap(MCurrentClipRect);
    pushClipRect(r);
}

//   virtual void pushNoClip() {
//     MClipStack.push(MClipRect);
//     resetClip();
//   }

//   virtual SAT_Rect popClip() {
//     SAT_Rect popped_rect = MClipStack.pop();
//     MClipRect = popped_rect;
//     setClip(MClipRect.x,MClipRect.y,MClipRect.w,MClipRect.h);
//     return MClipRect;
//   }

void SAT_Painter::popClipRect()
{
    SAT_Rect rect = MClipRectStack.pop();       // ugh.. crash...
    MCurrentClipRect = rect;
    setClip(rect);
    //return rect;
}

//   virtual void resetClipStack() {
//     MClipStack.reset();
//   }


SAT_Rect SAT_Painter::getClipRect()
{
    return MCurrentClipRect;
}

void SAT_Painter::setClipRect(SAT_Rect ARect)
{
    MCurrentClipRect = ARect;
}





