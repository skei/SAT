#pragma once

#include "base/sat_base.h"
#include "base/util/sat_intmath.h"
#include "gui/sat_gui_base.h"
#include "gui/sat_surface.h"

typedef SAT_SPSCQueue<uint64_t,SAT_WINDOW_RESIZE_QUEUE_SIZE> SAT_ResizeQueue;

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_WindowBuffer
{
    public:
        // SAT_WindowBuffer();
        SAT_WindowBuffer(SAT_SurfaceOwner* ASurfaceOwner, SAT_PainterOwner* APainterOwner, uint32_t AWidth, uint32_t AHeight);
        ~SAT_WindowBuffer();
    public:
        uint32_t            getWidth();
        uint32_t            getHeight();
        SAT_Surface*        getSurface();
        SAT_Painter*        getPainter();
    public:
     // bool                initialize(SAT_SurfaceOwner* ASurfaceOwner, SAT_PainterOwner* APainterOwner, uint32_t AWidth, uint32_t AHeight);
     // void                cleanup();
        void                createBuffer(uint32_t AWidth, uint32_t AHeight);
        void                deleteBuffer();
        bool                resizeBuffer(uint32_t AWidth, uint32_t AHeight);
    private:
        SAT_SurfaceOwner*   MSurfaceOwner   = nullptr;
        SAT_Surface*        MSurface        = nullptr;
        SAT_PainterOwner*   MPainterOwner   = nullptr;
        SAT_Painter*        MPainter        = nullptr;
        uint32_t            MWidth          = 0;
        uint32_t            MHeight         = 0;
};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

SAT_WindowBuffer::SAT_WindowBuffer(SAT_SurfaceOwner* ASurfaceOwner, SAT_PainterOwner* APainterOwner, uint32_t AWidth, uint32_t AHeight)
{
    SAT_Assert(ASurfaceOwner);
    MSurfaceOwner = ASurfaceOwner;
    SAT_Assert(APainterOwner);
    MPainterOwner = APainterOwner;
    uint32_t width = SAT_NextPowerOfTwo(AWidth);
    if (width < SAT_WINDOW_BUFFER_MIN_SIZE) width = SAT_WINDOW_BUFFER_MIN_SIZE;
    uint32_t height = SAT_NextPowerOfTwo(AHeight);
    if (height < SAT_WINDOW_BUFFER_MIN_SIZE) height = SAT_WINDOW_BUFFER_MIN_SIZE;
    createBuffer(width,height);
}

SAT_WindowBuffer::~SAT_WindowBuffer()
{
    deleteBuffer();
}

//------------------------------
//
//------------------------------

uint32_t SAT_WindowBuffer::getWidth()
{
    return MWidth;
}

uint32_t SAT_WindowBuffer::getHeight()
{
    return MHeight;
}

SAT_Surface* SAT_WindowBuffer::getSurface()
{
    return MSurface;
}

SAT_Painter* SAT_WindowBuffer::getPainter()
{
    return MPainter;
}

//------------------------------
//
//------------------------------

void SAT_WindowBuffer::createBuffer(uint32_t AWidth, uint32_t AHeight)
{
    //SAT_PRINT("%i,%i\n",AWidth,AHeight);
    MWidth = AWidth;
    MHeight = AHeight;
    SAT_Assert(!MSurface);
    MSurface = new SAT_Surface(MSurfaceOwner,MWidth,MHeight);
    SAT_Assert(MSurface);
    SAT_Assert(!MPainter);
    MPainter = new SAT_Painter(MPainterOwner,MSurface);
    SAT_Assert(MPainter);
}

void SAT_WindowBuffer::deleteBuffer()
{
    //SAT_PRINT("\n");
    if (MPainter) delete MPainter;
    MPainter = nullptr;
    if (MSurface) delete MSurface;
    MSurface = nullptr;
    MWidth = 0;
    MHeight = 0;
}

/*
    returns true if we actually resized the buffer
    (so we have to redraw the new buffer)
*/

bool SAT_WindowBuffer::resizeBuffer(uint32_t AWidth, uint32_t AHeight)
{
    uint32_t width = SAT_NextPowerOfTwo(AWidth);
    width = SAT_MaxI(SAT_WINDOW_BUFFER_MIN_SIZE,width);
    uint32_t height = SAT_NextPowerOfTwo(AHeight);
    height = SAT_MaxI(SAT_WINDOW_BUFFER_MIN_SIZE,height);
    if ((width != MWidth) || (height != MHeight))
    {
        deleteBuffer();
        createBuffer(width,height);
        return true;
    }
    return false;
}
