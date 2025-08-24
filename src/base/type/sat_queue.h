#pragma once

#include "base/sat_base.h"
#include "base/type/sat_queue.h"

/*
    argh..
    my mem-tracer reports what i believe is false positives
    when including both the moodycamel and rigtorp queues..
    not sure how to be certain...
*/

#define SAT_QUEUE_USE_MOODYCAMEL
//#define SAT_QUEUE_USE_RIGTORP

//----------------------------------------------------------------------
//
// moodycamel
//
//----------------------------------------------------------------------

#ifdef SAT_QUEUE_USE_MOODYCAMEL

    #include "extern/base/cameron314/concurrentqueue.h"
    #include "extern/base/cameron314/readerwriterqueue.h"

    // #define SAT_SPSCQueue   moodycamel::ReaderWriterQueue
    // #define SAT_MPMCQueue   moodycamel::ConcurrentQueue

    template<class T, int SIZE>
    class SAT_SPSCQueue
    {
        public:
            bool write(T AItem);
            bool read(T* AItem);
        private:
            moodycamel::ReaderWriterQueue<T> MQueue = moodycamel::ReaderWriterQueue<T>(SIZE);
    };

    template<class T, int SIZE>
    class SAT_MPMCQueue
    {
        public:
            bool write(T AItem);
            bool read(T* AItem);
        private:
            moodycamel::ConcurrentQueue<T> MQueue = moodycamel::ConcurrentQueue<T>(SIZE);
    };

    //------------------------------
    //
    //------------------------------

    template<class T, int SIZE>
    bool SAT_SPSCQueue<T,SIZE>::write(T AItem)
    {
        return MQueue.try_enqueue(AItem);
    }

    template<class T, int SIZE>
    bool SAT_SPSCQueue<T,SIZE>::read(T* AItem)
    {
        return MQueue.try_dequeue(*AItem);
    }

    //------------------------------
    //
    //------------------------------

    template<class T, int SIZE>
    bool SAT_MPMCQueue<T,SIZE>::write(T AItem)
    {
        return MQueue.try_enqueue(AItem);
    }

    template<class T, int SIZE>
    bool SAT_MPMCQueue<T,SIZE>::read(T* AItem)
    {
        return MQueue.try_dequeue(*AItem);
    }

#endif // SAT_QUEUE_USE_MOODYCAMEL

//----------------------------------------------------------------------
//
// rigtorp
//
//----------------------------------------------------------------------

#ifdef SAT_QUEUE_USE_RIGTORP

    #include "extern/base/rigtorp/SPSCQueue.h"
    #include "extern/base/rigtorp/MPMCQueue.h"

    template<class T, int SIZE>
    class SAT_SPSCQueue
    {
        public:
            bool write(T AItem);
            bool read(T* AItem);
        private:
            rigtorp::SPSCQueue<T> MQueue = rigtorp::SPSCQueue<T>(SIZE);
    };

    template<class T, int SIZE>
    class SAT_MPMCQueue
    {
        public:
            bool write(T AItem);
            bool read(T* AItem);
        private:
            rigtorp::MPMCQueue<T> MQueue = rigtorp::MPMCQueue<T>(SIZE);
    };

    //------------------------------
    //
    //------------------------------

    /*

        SPSCQueue<T>(size_t capacity);
            Create a SPSCqueue holding items of type T with capacity capacity.
            Capacity needs to be at least 1.
        void emplace(Args &&... args);
            Enqueue an item using inplace construction.
            Blocks if queue is full.
        bool try_emplace(Args &&... args);
            Try to enqueue an item using inplace construction.
            Returns true on success and false if queue is full.
        void push(const T &v);
            Enqueue an item using copy construction.
            Blocks if queue is full.
        template <typename P> void push(P &&v);
            Enqueue an item using move construction.
            Participates in overload resolution only if std::is_constructible<T, P&&>::value == true.
            Blocks if queue is full.
        bool try_push(const T &v);
            Try to enqueue an item using copy construction.
            Returns true on success and false if queue is full.
        template <typename P> bool try_push(P &&v);
            Try to enqueue an item using move construction.
            Returns true on success and false if queue is full.
            Participates in overload resolution only if std::is_constructible<T, P&&>::value == true.
        T *front();
            Return pointer to front of queue.
            Returns nullptr if queue is empty.
        void pop();
            Dequeue first item of queue.
            You must ensure that the queue is non-empty before calling pop.
            This means that front() must have returned a non-nullptr before each call to pop().
            Requires std::is_nothrow_destructible<T>::value == true.
        size_t size();
            Return the number of items available in the queue.
        bool empty();
            Return true if queue is currently empty.

        Only a single writer thread can perform enqueue operations and only a single reader thread
        can perform dequeue operations. Any other usage is invalid.

    */

    template<class T, int SIZE>
    bool SAT_SPSCQueue<T,SIZE>::write(T AItem)
    {
        return MQueue.try_push(AItem);
    }

    template<class T, int SIZE>
    bool SAT_SPSCQueue<T,SIZE>::read(T* AItem)
    {
        //return MQueue.try_pop(AItem);
        if (MQueue.front())
        {
            *AItem = *MQueue.front();
            MQueue.pop();
            return true;
        }
        return false;
    }

    //------------------------------
    //
    //------------------------------

    /*
        MPMCQueue<T>(size_t capacity);
            Constructs a new MPMCQueue holding items of type T with capacity capacity.
        void emplace(Args &&... args);
            Enqueue an item using inplace construction.
            Blocks if queue is full.
        bool try_emplace(Args &&... args);
            Try to enqueue an item using inplace construction.
            Returns true on success and false if queue is full.
        void push(const T &v);
            Enqueue an item using copy construction.
            Blocks if queue is full.
        template <typename P> void push(P &&v);
            Enqueue an item using move construction.
            Participates in overload resolution only if std::is_nothrow_constructible<T, P&&>::value == true.
            Blocks if queue is full.
        bool try_push(const T &v);
            Try to enqueue an item using copy construction.
            Returns true on success and false if queue is full.
        template <typename P> bool try_push(P &&v);
            Try to enqueue an item using move construction.
            Participates in overload resolution only if std::is_nothrow_constructible<T, P&&>::value == true.
            Returns true on success and false if queue is full.
        void pop(T &v);
            Dequeue an item by copying or moving the item into v.
            Blocks if queue is empty.
        bool try_pop(T &v);
            Try to dequeue an item by copying or moving the item into v.
            Return true on sucess and false if the queue is empty.
        ssize_t size();
            Returns the number of elements in the queue.
            The size can be negative when the queue is empty and there is at least one reader waiting.
            Since this is a concurrent queue the size is only a best effort guess until all reader and writer threads have been joined.
        bool empty();
            Returns true if the queue is empty.
            Since this is a concurrent queue this is only a best effort guess until all reader and writer threads have been joined.

        All operations except construction and destruction are thread safe.
    */

    template<class T, int SIZE>
    bool SAT_MPMCQueue<T,SIZE>::write(T AItem)
    {
        return MQueue.try_push(AItem);
    }

    template<class T, int SIZE>
    bool SAT_MPMCQueue<T,SIZE>::read(T* AItem)
    {
        return MQueue.try_pop(AItem);
        // if (MQueue.front())
        // {
        //     *AItem = *MQueue.front();
        //     MQueue.pop();
        //     return true;
        // }
        // return false;
    }

#endif // SAT_QUEUE_USE_RIGTORP


















#if 0

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

/*
    "..nothing will read the value until the size of the container is
    incremented, so you don't care if the orders of writes of the value itself
    happen in a random order, you only care that the value must be fully written
    before the count is increased.."
*/

/*
    (should we add volatile to read/write-pos?
    Volatile is a qualifier that is applied to a variable when it is declared.
    It tells the compiler that the value of the variable may change at any time -
    without any action being taken by the code the compiler finds nearby.
*/

/*
    volatile informs the compiler that the object (variable) is side effects prone.
    It means that it can be changed by something which is not visible for the compiler
    in a normal program execution path. For example by the hardware (DMA, hardware
    register) or signal (exception) handler which is not called by the program.
*/

// https://blog.regehr.org/archives/28

template<class T, int SIZE>
class SAT_Queue
{

    private:

        T*          MBuffer;
        uint32_t    MBufferSize;
        uint32_t    MBufferMask;
        uint32_t    MReadPos;
        uint32_t    MWritePos;

    public:

        SAT_Queue()
        {
            MBuffer     = (T*)malloc(SIZE*sizeof(T));
            MBufferSize = SIZE;
            MBufferMask = SIZE - 1;
            MReadPos    = 0;
            MWritePos   = 0;
        }

        ~SAT_Queue()
        {
            free(MBuffer);
        }

    public:

        bool write(T AItem)
        {
            uint32_t rp = MReadPos;
            uint32_t wp = MWritePos;
            if (((wp - rp) & MBufferMask) < (MBufferSize - 1))
            {
                MBuffer[wp] = AItem;
                uint32_t next = (wp + 1) & MBufferMask;
                MWritePos = next;
                return true;
            }
            return false;
        }

        bool read(T* AItem)
        {
            uint32_t wp = MWritePos;
            uint32_t rp = MReadPos;
            if (((wp - rp) & MBufferMask) > 0)
            {
                *AItem = MBuffer[rp];
                uint32_t next = (rp + 1) & MBufferMask;
                MReadPos = next;
                return true;
            }
            return false;
        }

        int32_t size()
        {
            uint32_t rp = MReadPos;
            uint32_t wp = MWritePos;
            return (wp - rp) & MBufferMask;
        }

};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

/*
    spsc
    http://linux-audio.4202.n7.nabble.com/Realtime-inter-thread-communication-td99157.html
    write single, read buffer (all)
*/

template<class T, int SIZE>
class SAT_QueueBuffer
{

    private:

        T   MData[SIZE];
        int MWritePos;
        int MReadPos;

    public:

        SAT_QueueBuffer()
        {
            memset(MData,0,SIZE*(sizeof(T)));
            MWritePos = 0;
            MReadPos = 0;
        }

        void write(T AData)
        {
            MData[MWritePos] = AData;
            MWritePos = (MWritePos + 1) % SIZE; // & SIZE if ^2
        }

        int read(T* ABuffer)
        {
            int count = 0;
            int writepos = MWritePos;
            if (MReadPos > writepos)
            {
                memcpy(
                    (char*)&ABuffer[count],
                    (char*)&MData[MReadPos],
                    (SIZE - MReadPos) * sizeof(T)
                );
                count = SIZE - MReadPos;
                MReadPos = 0;
            }
            memcpy(
                (char*)&ABuffer[count],
                (char*)&MData[MReadPos],
                (writepos - MReadPos) * sizeof(T)
            );
            count += writepos - MReadPos;
            MReadPos = writepos;
            return count;
        }

};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

// https://www.linkedin.com/pulse/lock-free-single-producer-consumer-queue-c11-sander-jobing

/*
    File:   SpScLockFreeQueue.h
    Author: Sander Jobing
    Created on July 29, 2017, 5:17 PM
    This class implements a Single Producer - Single Consumer lock-free and
    wait-free queue. Only 1 thread can fill the queue, another thread can read
    from the queue, but no more threads are allowed. This lock-free queue
    is a fifo queue, the first element inserted is the first element which
    comes out.
    Thanks to Timur Doumler, Juce
    https://www.youtube.com/watch?v=qdrp6k4rcP4
*/

#include <array>
#include <atomic>
#include <cassert>

template <typename T, size_t SIZE>
class SAT_AtomicQueue
{

    private:

        static constexpr size_t     MBufferSize  = SIZE + 1;
        std::array<T, MBufferSize>  MBuffer;
        std::atomic<size_t>         MReadPos    = {0};
        std::atomic<size_t>         MWritePos   = {0};

    public:

        // Asserts when the underlying type is not lock free

        SAT_AtomicQueue()
        {
            std::atomic<size_t> test;
            assert(test.is_lock_free());
        }

        //SAT_AtomicQueue(const SAT_AtomicQueue& src) = delete;

        virtual ~SAT_AtomicQueue()
        {
        }

    public:

        // Pushes an element to the queue
        // element  The element to add
        // True when the element was added, false when the queue is full

        //bool write(const T& element) {
        bool write(const T element)
        {
            const size_t oldWritePosition = MWritePos.load();
            const size_t newWritePosition = getPositionAfter(oldWritePosition);
            const size_t readPosition = MReadPos.load();
            if (newWritePosition == readPosition)
            {
                // The queue is full
                return false;
            }
            MBuffer[oldWritePosition] = element;
            MWritePos.store(newWritePosition);
            return true;
        }

        // Pops an element from the queue
        // element The returned element
        // True when succeeded, false when the queue is empty

        //bool read(T& element)
        bool read(T* element)
        {
            if (empty())
            {
                // The queue is empty
                return false;
            }
            const size_t readPosition = MReadPos.load();
            //element = std::move(MBuffer[readPosition]);
            *element = std::move(MBuffer[readPosition]);
            MReadPos.store(getPositionAfter(readPosition));
            return true;
        }

        // return True when empty

        bool empty() const noexcept
        {
            bool isEmpty = false;
            const size_t readPosition = MReadPos.load();
            const size_t writePosition = MWritePos.load();
            if (readPosition == writePosition)
            {
                isEmpty = true;
            }
            return isEmpty;
        }

        // Clears the content from the queue

        void clear() noexcept
        {
            const size_t readPosition = MReadPos.load();
            const size_t writePosition = MWritePos.load();
            if (readPosition != writePosition)
            {
                MReadPos.store(writePosition);
            }
        }

        // Returns the maximum size of the queue
        // The maximum number of elements the queue can hold

        constexpr size_t max_size() const noexcept
        {
            return MBufferSize - 1;
        }

        // Returns the actual number of elements in the queue
        // The actual size or 0 when empty

        size_t size() const noexcept
        {
            const size_t readPosition = MReadPos.load();
            const size_t writePosition = MWritePos.load();
            if (readPosition == writePosition)
            {
                return 0;
            }
            size_t size = 0;
            if (writePosition < readPosition)
            {
                size = MBufferSize - readPosition + writePosition;
            }
            else
            {
                size = writePosition - readPosition;
            }
            return size;
        }

        static constexpr size_t getPositionAfter(size_t pos) noexcept
        {
            return ((pos + 1 == MBufferSize) ? 0 : pos + 1);
        }

};

#endif // 0
