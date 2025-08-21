#pragma once

/*
    crash handler:
    compile with: -g -rdynamic
    // https://lasr.cs.ucla.edu/vahab/resources/signals.html
    // The only two signals for which a handler cannot be defined are SIGKILL and SIGSTOP.
*/

#include "base/sat_base.h"
#include "base/global/sat_global_base.h"
#include "base/global/sat_global_print.h"
#include "base/global/debug/sat_debug_callstack.h"
#include "base/global/debug/sat_debug_observer.h"

#ifdef SAT_DEBUG_CRASH_HANDLER    
    extern void sat_crash_handler_callback(int sig);
#endif

#include <signal.h>

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_CrashHandler
{
    public:

        SAT_CrashHandler();
        ~SAT_CrashHandler();
        void activate(SAT_GlobalBase* AGlobal, SAT_CallStack* ACallStack=nullptr, SAT_Observer* AObserver=nullptr);
        void deactivate(SAT_GlobalBase* AGlobal);

    public:

        void setupCrashHandler(int sig);
        void setupCrashHandlers();
        void cleanupCrashHandlers();
        void crashHandler(int sig);

    private:

        bool                MIsActivated    = false;
        SAT_GlobalBase*     MGlobal         = nullptr;
        SAT_CallStack*      MCallStack      = nullptr;
        SAT_Observer*       MObserver       = nullptr;

    private:

        // #ifdef SAT_DEBUG_OBSERVER
        //     SAT_Observer* MObserver = nullptr;
        // #endif

};

//----------------------------------------------------------------------
//
// implementation
//
//----------------------------------------------------------------------

SAT_CrashHandler::SAT_CrashHandler()
{
}

SAT_CrashHandler::~SAT_CrashHandler()
{
}

void SAT_CrashHandler::activate(SAT_GlobalBase* AGlobal, SAT_CallStack* ACallStack, SAT_Observer* AObserver)
{
    if (!MIsActivated)
    {
        MGlobal = AGlobal;
        MCallStack = ACallStack;
        MObserver = AObserver;
        setupCrashHandlers();
        MIsActivated = true;
    }
}

void SAT_CrashHandler::deactivate(SAT_GlobalBase* AGlobal)
{
    if (MIsActivated)
    {
        cleanupCrashHandlers();
        MGlobal = nullptr;
        MIsActivated = false;
    }
}

//------------------------------
// crash handler
//------------------------------

#ifdef SAT_DEBUG_CRASH_HANDLER
    const char* SAT_SignalNames[32] = {
        "(kill(pid,0))",
        "SIGHUP (Hangup)",
        "SIGINT (Interactive attention signal)",
        "SIGQUIT (Quit)",
        "SIGILL (Illegal instruction)",
        "SIGTRAP (Trace/breakpoint trap)",
        "SIGABRT (Abnormal termination)",
        "(-)",
        "SIGFPE (Erroneous arithmetic operation)",
        "SIGKILL (Killed)",
        "SIGBUS (Bus error)",
        "SIGSEGV (Invalid access to storage)",
        "SIGSYS (Bad system call)",
        "SIGPIPE (Broken pipe)",
        "SIGALRM (Alarm clock)",
        "SIGTERM (Termination request)",
        "SIGURG (Urgent data is available at a socket)",
        "SIGSTOP (Stop, unblockable)",
        "SIGTSTP (Keyboard stop)",
        "SIGCONT (Continue)",
        "SIGCHLD (Child terminated or stopped)",
        "SIGTTIN (Background read from control terminal)",
        "SIGTTOU (Background write to control terminal)",
        "SIGPOLL (Pollable event occurred)",
        "SIGXCPU (CPU time limit exceeded)",
        "SIGXFSZ (File size limit exceeded)",
        "SIGVTALRM (Virtual timer expired)",
        "SIGPROF (Profiling timer expired)",
        "SIGWINCH (Window size change)",
        "(-)",
        "SIGUSR1 (User-defined signal 1)",
        "SIGUSR2 (User-defined signal 2)"
    };
#endif

void SAT_CrashHandler::setupCrashHandler(int sig)
{
    #ifdef SAT_DEBUG_CRASH_HANDLER    
        #ifdef SAT_LINUX
            signal(sig,sat_crash_handler_callback);
        #endif
    #endif
}

void SAT_CrashHandler::setupCrashHandlers()
{
    #ifdef SAT_DEBUG_CRASH_HANDLER    
        #ifdef SAT_LINUX
            //for (int i=0; i<32; i++) SAT_InitSignalHandler(i);
            setupCrashHandler(SIGILL);
            setupCrashHandler(SIGABRT);
            setupCrashHandler(SIGFPE);
            setupCrashHandler(SIGSEGV);
        #endif
    #endif
}

void SAT_CrashHandler::cleanupCrashHandlers()
{
    #ifdef SAT_DEBUG_CRASH_HANDLER    
    #endif
}
  
void SAT_CrashHandler::crashHandler(int sig)
{
    #ifdef SAT_DEBUG_CRASH_HANDLER    
        #ifdef SAT_LINUX
            SAT_GLOBAL_DPRINT("CRASH!\n");
            SAT_GLOBAL_DPRINT("  %i : %s\n",sig,SAT_SignalNames[sig]);
            // SAT_GLOBAL_WATCHES.printWatches("watched:");
            // if (MCallStack) MCallStack->print();
            #if defined SAT_DEBUG_CALLSTACK
                MCallStack->print();
            #endif
            #ifdef SAT_DEBUG_OBSERVER
                if (MObserver) MObserver->print_observers();
            #endif
            exit(1); //_exit(1);
        #endif
    #endif
}  
