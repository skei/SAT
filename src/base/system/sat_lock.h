#pragma once

#include "base/sat_base.h"

#if defined SAT_LINUX
    #include "base/system/linux/sat_linux_lock.h"
#elif defined SAT_WIN32
    #include "base/system/win32/sat_win32_lock.h"
#else
    #error NOT IMPLEMENTED YET
#endif
