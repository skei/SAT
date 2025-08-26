#pragma once

#ifndef SAT_NO_STDLIB
    #include <cassert>
    #include <malloc.h>
    #include <math.h>
    #include <memory>
    #include <pthread.h>
    #include <stdarg.h>
    #include <stdint.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <time.h>
    #include <unistd.h>
    #include <array>
    #include <atomic>
    //#include <condition_variable>
    #include <thread>
    #include <vector>
    // #include <sys/time.h>   // gettimeofday
#else
    #error NOT IMPLEMENTED YET
#endif
