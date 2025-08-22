#pragma once

//----------------------------------------------------------------------
//
// callstack
//
//----------------------------------------------------------------------

#ifdef SAT_DEBUG_CALLSTACK
    #define SAT_PrintCallStack \
        SAT.PRINT->setPrefix( __FILE__, __PRETTY_FUNCTION__, __LINE__ ); SAT.PRINT->print(""); \
        SAT.DEBUG->CALLSTACK->print(1);
#else
    #define SAT_PrintCallStack {}
#endif

//----------------------------------------------------------------------
//
// crash handler
//
//----------------------------------------------------------------------

#ifdef SAT_DEBUG_CRASH_HANDLER

    void sat_crash_handler_callback(int sig) {
        SAT.DEBUG->CRASH_HANDLER->crashHandler(sig);
    }

#endif

//----------------------------------------------------------------------
//
// log
//
//----------------------------------------------------------------------

#ifdef SAT_INCLUDE_LOG
    #define SAT_LOG SAT.LOG->print
#else
    #define SAT_LOG SAT_PrintNothing
#endif

//----------------------------------------------------------------------
//
// memtrace
//
//----------------------------------------------------------------------

#ifdef SAT_DEBUG_MEMTRACE

    static __thread char*         sat_memtrace_prefix_file;
    static __thread unsigned int  sat_memtrace_prefix_line;

    // NOT safe!
    // a hack, but it works.. kind of..
    
    unsigned int sat_memtrace_prefix(const char* file, const unsigned int line) {
        sat_memtrace_prefix_file = (char*)file;
        sat_memtrace_prefix_line = line;
        return 1;
    }

    // see:
    // https://en.cppreference.com/w/cpp/memory/new/operator_new.html    
    // https://en.cppreference.com/w/cpp/memory/new/operator_delete.html

    // void operator delete (void* ptr) /*throw()*/ {}
    // void operator delete (void* ptr) _GLIBCXX_USE_NOEXCEPT {}
    // void operator delete[] (void* ptr) /*throw()*/ {0
    // void operator delete [] (void* ptr) _GLIBCXX_USE_NOEXCEPT {0

    void* operator  new         (const size_t size, const char* file, unsigned int line)    { return SAT.DEBUG->MEMTRACE->malloc(size, file, line, 1); }
    void* operator  new[]       (const size_t size, const char* file, unsigned int line)    { return SAT.DEBUG->MEMTRACE->malloc(size, file, line, 1); }

    // void* operator new  (std::size_t count, const std::nothrow_t& tag)  { SAT.PRINT->print("new nothrow not implemented\n"); return (void*)666; }
    // void* operator new[](std::size_t count, const std::nothrow_t& tag)  { SAT.PRINT->print("new[] nothrow not implemented\n"); return (void*)666; }

    void  operator  delete      (void* ptr)                                                 { return SAT.DEBUG->MEMTRACE->free(ptr, sat_memtrace_prefix_file, sat_memtrace_prefix_line, 1); }
    void  operator  delete[]    (void* ptr)                                                 { return SAT.DEBUG->MEMTRACE->free(ptr, sat_memtrace_prefix_file, sat_memtrace_prefix_line, 1); }

    // void operator delete  (void* ptr, const std::nothrow_t& tag)    { SAT.PRINT->print("delete nothrow not implemented (%p)\n",ptr); }
    // void operator delete[](void* ptr, const std::nothrow_t& tag)    { SAT.PRINT->print("delete[] nothrow not implemented (%p)\n",ptr); }
    // void operator delete  (void* ptr, std::size_t sz)               { SAT.PRINT->print("delete size (%i) not implemented (%p)\n",sz,ptr); }
    // void operator delete[](void* ptr, std::size_t sz)               { SAT.PRINT->print("delete[] size (%i) not implemented (%p)\n",sz,ptr); }

    // -----

    #define new     new(__FILE__, __LINE__)
    #define delete  if (sat_memtrace_prefix(__FILE__, __LINE__)) delete

    #define malloc(s)       SAT.DEBUG->MEMTRACE->malloc(  s,    __FILE__, __LINE__ )
    #define calloc(n,s)     SAT.DEBUG->MEMTRACE->calloc(  n, s, __FILE__, __LINE__ )
    #define realloc(p,s)    SAT.DEBUG->MEMTRACE->realloc( p, s, __FILE__, __LINE__ )
    #define free(p)         SAT.DEBUG->MEMTRACE->free(    p,    __FILE__, __LINE__ )

#endif // SAT_DEBUG_MEMTRACE

//----------------------------------------------------------------------
//
// observers
//
//----------------------------------------------------------------------

#ifdef SAT_DEBUG_OBSERVER
    #define SAT_Observe(type,ptr,txt) SAT.DEBUG->OBSERVER->observe(type,ptr,txt)
    #define SAT_Unobserve(ptr) SAT.DEBUG->OBSERVER->unobserve(ptr)
    #define SAT_PrintObservers \
        SAT.PRINT->setPrefix( __FILE__, __FUNCTION__, __LINE__ ); SAT.PRINT->print(""); \
        SAT.DEBUG->OBSERVER->print_observers()
#else
    #define SAT_Observe(type,ptr,txt) {}
    #define SAT_Unobserve(ptr) {}
    #define SAT_PrintObservers {}
#endif

//----------------------------------------------------------------------
//
// print
//
//----------------------------------------------------------------------

//#define SAT_PRINT SAT.PRINT.print

//void SAT_NoPrint(const char*,...) {}

#ifdef SAT_PRINT_PRETTY_FUNCTION

    #define SAT_PRINT \
        SAT.PRINT->setPrefix( __FILE__, __PRETTY_FUNCTION__, __LINE__ ); \
        SAT.PRINT->print

    #define SAT_DPRINT \
        SAT.PRINT->clearPrefix(); \
        SAT.PRINT->print

    #define SAT_TRACE \
        SAT.PRINT->setPrefix( __FILE__, __PRETTY_FUNCTION__, __LINE__ ); \
        SAT.PRINT->print("\n")

#else // !SAT_PRINT_PRETTY_FUNCTION

    #define SAT_PRINT \
        SAT.PRINT->setPrefix( __FILE__, __FUNCTION__, __LINE__ ); \
        SAT.PRINT->print

    #define SAT_DPRINT \
        SAT.PRINT->clearPrefix(); \
        SAT.PRINT->print

    #define SAT_TRACE \
        SAT.PRINT->setPrefix( __FILE__, __FUNCTION__, __LINE__ ); \
        SAT.PRINT->print("\n")
    
#endif // SAT_PRINT_PRETTY_FUNCTION
  
//----------

#ifndef SAT_DEBUG
    #ifndef SAT_PRINT_ALWAYS
        #undef SAT_PRINT
        #undef SAT_DPRINT
        #undef SAT_TRACE
        #define SAT_PRINT   SAT_PrintNothing
        #define SAT_DPRINT  SAT_PrintNothing
        #define SAT_TRACE   {}

    #endif // SAT_PRINT_ALWAYS
#endif // SAT_DEBUG

//----------------------------------------------------------------------
//
// tests
//
//----------------------------------------------------------------------

// see SAT_Global.h

#ifdef SAT_INCLUDE_TESTS

    #define SAT_TEST(name,func)                                             \
                                                                            \
        bool sat__test_register_ ##func() {                                 \
            SAT.TEST->addTest(name,func);                                   \
            return true;                                                    \
        }                                                                   \
                                                                            \
        bool sat__test_registered_ ##func = sat__test_register_ ##func();

    #define SAT_RUN_TESTS SAT.TEST->runAllTests()

#else // !SAT_INCLUDE_TESTS

    #define SAT_TEST(name,func)
        //#define SAT_RUN_TESTS SAT.TEST->runAllTests();
    #define SAT_RUN_TESTS {}

#endif // SAT_INCLUDE_TESTS
