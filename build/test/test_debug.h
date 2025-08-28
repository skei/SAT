#pragma once 

// #define SAT_DEBUG_MEMTRACE
// #define SAT_PRINT_SOCKET

#include "base/sat.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

void test_debug()
{
    // SAT_Assert(1==0);
    // SAT_PrintCallStack;

    // --- memtrace ---
    // uint8_t* test = (uint8_t*)malloc(1024);
    // uint8_t* test2 = new uint8_t[512];
    // SAT_PRINT("test %p test2 %p\n",test,test2);
    // free(test);
    // delete [] test2;
    // //delete test; // mismatch
    // //free(test2); // mismatch

    // --- observer ---
    // const char* test_str = "string 123\0";
    // double      test_dbl = 3.14;
    // void*       test_ptr = 0; // &teststr;
    // // SAT_PRINT("teststr %s testdlb %.3f testptr %p\n",teststr,testdbl,testptr);
    // SAT_Observe(SAT_OBSERVE_DOUBLE, &test_dbl,"test_dbl");
    // SAT_Observe(SAT_OBSERVE_STR,    &test_str,"test_str");
    // SAT_Observe(SAT_OBSERVE_PTR,    &test_ptr,"test_ptr");
    // SAT_PrintObservers;

    // --- crash handler ---
    // int* ptr = nullptr;
    // int a = *ptr;
    // SAT_PRINT("a = %i\n",a);
}

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

int main(void)
{
    test_debug();

    SAT_PRINT("OS: %s\n",SAT.SYSTEM->getOSString());
    SAT_DPRINT("hello world!\n");
    SAT_TRACE;
    SAT_PRINT("width %i height %i depth %i\n",SAT.GUI->getScreenWidth(),SAT.GUI->getScreenHeight(),SAT.GUI->getScreenDepth());

    // SAT_LOG("WARNING! no window available");

    return 0;
}

