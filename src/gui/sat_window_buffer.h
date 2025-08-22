#pragma once

#include "base/sat_base.h"
#include "base/util/sat_intmath.h"
#include "gui/sat_gui_base.h"

typedef SAT_SPSCQueue<uint64_t,SAT_WINDOW_RESIZE_QUEUE_SIZE> SAT_ResizeQueue;

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_WindowBuffer
{
    public:
        SAT_WindowBuffer();
        ~SAT_WindowBuffer();
    public:
        uint32_t getWidth();
        uint32_t getHeight();

    public:
        void createBuffer(uint32_t AWidth, uint32_t AHeight);
        void deleteBuffer();
        bool initBuffer(uint32_t AWidth, uint32_t AHeight);
        void requestResize(uint32_t AWidth, uint32_t AHeight);
        bool checkSize(uint32_t AWidth, uint32_t AHeight);

    private: // buffer
        // SAT_Surface*        MBuffer         = nullptr;
        SAT_ResizeQueue     MResizeQueue    = {};
        uint32_t            MWidth          = 0;
        uint32_t            MHeight         = 0;
   
};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

SAT_WindowBuffer::SAT_WindowBuffer()
{
}

SAT_WindowBuffer::~SAT_WindowBuffer()
{
}

//------------------------------
//
//------------------------------

uint32_t SAT_WindowBuffer::getWidth()   { return MWidth; }
uint32_t SAT_WindowBuffer::getHeight()  { return MHeight; }

//------------------------------
//
//------------------------------

void SAT_WindowBuffer::createBuffer(uint32_t AWidth, uint32_t AHeight)
{
    //SAT_PRINT("%i,%i\n",AWidth,AHeight);
}

void SAT_WindowBuffer::deleteBuffer()
{
    //SAT_PRINT("\n");
}

bool SAT_WindowBuffer::initBuffer(uint32_t AWidth, uint32_t AHeight)
{
    uint32_t width  = SAT_NextPowerOfTwo(AWidth);
    if (width < SAT_WINDOW_BUFFER_MIN_SIZE) width = SAT_WINDOW_BUFFER_MIN_SIZE;
    uint32_t height = SAT_NextPowerOfTwo(AHeight);
    if (height < SAT_WINDOW_BUFFER_MIN_SIZE) height = SAT_WINDOW_BUFFER_MIN_SIZE;
    MWidth = width;
    MHeight = height;
    createBuffer(width,height);
    return true;
}

void SAT_WindowBuffer::requestResize(uint32_t AWidth, uint32_t AHeight)
{
    uint64_t size = AWidth;
    size = (size << 32) + AHeight;
    if (!MResizeQueue.write(size))
    {
        SAT_PRINT("couldn't write to resize queue\n");
    }
}

bool SAT_WindowBuffer::checkSize(uint32_t AWidth, uint32_t AHeight)
{
    // bool resized = false;
    uint32_t width  = AWidth;
    uint32_t height = AHeight;
    uint64_t size = 0;
    uint32_t resize_count = 0;
    // flush the queue, and keep the last entry only..
    while (MResizeQueue.read(&size)) resize_count += 1;
    if (resize_count > 0)
    {
        // SAT.STATISTICS->report_resize_queue_count(count);
        width  = (size & 0xffffffff00000000) >> 32;
        height = (size & 0x00000000ffffffff);
        width = SAT_NextPowerOfTwo(width);
        width = SAT_MaxI(SAT_WINDOW_BUFFER_MIN_SIZE,width);
        height = SAT_NextPowerOfTwo(height);
        height = SAT_MaxI(SAT_WINDOW_BUFFER_MIN_SIZE,height);
        if ((width != MWidth) || (height != MHeight))
        {
            //SAT_PRINT("window resized: %i,%i\n",width,height);
            MWidth = width;
            MHeight = height;
            deleteBuffer();
            createBuffer(MWidth,MHeight);
            // resize buffer
            return true;
        }
    }
    return false;
}
