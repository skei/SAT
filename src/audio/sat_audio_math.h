#pragma once

/*
    "I just looked it up - the centre-point of that spectrum-display is 1500Hz.  I use the mapping functions:"
        hzToLinear(hz) = hz/(1500 + hz)
        linearToHz(x) = 1500*x/(1 - x)
    "Then depending on the actual limits, I do a linear scale to convert x into a 0-1 value "
*/

/*
    https://github.com/DISTRHO/DPF/blob/main/distrho/extra/ScopedDenormalDisable.hpp#L35
    
    #ifdef __SSE2_MATH__
        #include <xmmintrin.h>
    #endif

    #if defined(__SSE2_MATH__)
        typedef uint cpuflags_t;
    #elif defined(__aarch64__)
        typedef uint64_t cpuflags_t;
    #elif defined(__arm__) && !defined(__SOFTFP__)
        typedef uint32_t cpuflags_t;
    #else
        typedef char cpuflags_t;
    #endif    

    cpuflags_t oldflags = 0;

    void disable()
    {
        #if defined(__SSE2_MATH__)
            oldflags = _mm_getcsr();
            setFlags(oldflags | 0x8040);
        #elif defined(__aarch64__)
            __asm__ __volatile__("mrs %0, fpcr" : "=r" (oldflags));
            setFlags(oldflags | 0x1000000);
            __asm__ __volatile__("isb");
        #elif defined(__arm__) && !defined(__SOFTFP__)
            __asm__ __volatile__("vmrs %0, fpscr" : "=r" (oldflags));
            setFlags(oldflags | 0x1000000);
        #endif
    }    

    void setFlags(const cpuflags_t flags)
    {
        #if defined(__SSE2_MATH__)
            _mm_setcsr(flags);
        #elif defined(__aarch64__)
            __asm__ __volatile__("msr fpcr, %0" :: "r" (flags));
        #elif defined(__arm__) && !defined(__SOFTFP__)
            __asm__ __volatile__("vmsr fpscr, %0" :: "r" (flags));
        #else
            // unused
            (void)flags;
        #endif
    }    

*/

