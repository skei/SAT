#pragma once

#undef  _WIN32_WINNT
#define _WIN32_WINNT 0x0501
// #ifndef SAT_WIN32_GDIPLUS
#ifndef WIN32_LEAN_AND_MEAN
    #define WIN32_LEAN_AND_MEAN
#endif
// #endif
#include <windows.h>
// #include <strsafe.h>


#include "base/sat_base.h"
#include "base/global/sat_global_base.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_GlobalSystem
{
    public:
        SAT_GlobalSystem();
        ~SAT_GlobalSystem();
        void activate(SAT_GlobalBase* AGlobal);
        void deactivate(SAT_GlobalBase* AGlobal);
    public:
        uint32_t        getOs();
        const char*     getOSString();
        void            setInstance(HINSTANCE AInstance);
        HINSTANCE       getInstance();
    private:
        bool            MIsActivated    = false;
        SAT_GlobalBase* MGlobal         = nullptr;
    private:
        HINSTANCE       MInstance       = nullptr;
};

__SAT_EXTERNC BOOL APIENTRY DllMain(HINSTANCE hModule, DWORD reason, LPVOID lpReserved);
void SAT_Win32PrintError(const char* txt)

//----------------------------------------------------------------------
//
// implementation
//
//----------------------------------------------------------------------

SAT_GlobalSystem::SAT_GlobalSystem()
{
}

SAT_GlobalSystem::~SAT_GlobalSystem()
{
}

void SAT_GlobalSystem::activate(SAT_GlobalBase* AGlobal)
{
    if (!MIsActivated)
    {
        MGlobal = AGlobal;
        MIsActivated = true;
    }
}

void SAT_GlobalSystem::deactivate(SAT_GlobalBase* AGlobal)
{
    if (MIsActivated)
    {
        MGlobal = nullptr;
        MIsActivated = false;
    }
}

//------------------------------
//
//------------------------------

uint32_t SAT_GlobalSystem::getOs()
{
    return SAT_OS_WIN32;
}

const char* SAT_GlobalSystem::getOSString()
{
    return "Win32";
}

void SAT_GlobalSystem::setInstance(HINSTANCE AInstance)
{
    MInstance = AInstance;
}

HINSTANCE SAT_GlobalSystem::getInstance()
{
    MInstance = AInstance;
}

//------------------------------
//
//------------------------------

/*
    http://msdn.microsoft.com/en-us/library/ms682583%28v=vs.85%29.aspx
    http://stackoverflow.com/questions/4496233/which-is-called-first-dllmain-or-global-static-object-constructor
    Which is called first, DllMain() or global static object constructor?
    MSDN's DllMain documentation says:
    If your DLL is linked with the C run-time library (CRT), the entry point
    provided by the CRT calls the constructors and destructors for global and
    static C++ objects. Therefore, these restrictions for DllMain also apply to
    constructors and destructors and any code that is called from them.
    Since the code within DllMain may use the static objects, the static objects
    must be constructed before DllMain is run for DLL_PROCESS_ATTACH, and
    destroyed after it is run for DLL_PROCESS_DETACH.
*/

#ifdef SAT_LIBRARY
    __SAT_EXTERNC
    BOOL APIENTRY
    DllMain(HINSTANCE hModule, DWORD reason, LPVOID lpReserved)
    {
        switch(reason)
        {
            case DLL_PROCESS_ATTACH:
                SAT->SYSTEM->setHInstance(hModule);
                //SAT_RegisterWindowClass(&s3_global_WinInstance);
                break;
            // case DLL_PROCESS_DETACH:
            //     //SAT_UnregisterWindowClass();
            //     break;
            // case DLL_THREAD_ATTACH:
            //     break;
            // case DLL_THREAD_DETACH:
            //     break;
            // default:
            //     break;
        }
        return TRUE;
    }
#endif // SAT_LIBRARY

//void SAT_Win32Error(LPTSTR lpszFunction)
void SAT_Win32PrintError(const char* txt)
{
    // Retrieve the system error message for the last-error code
    DWORD dw = GetLastError();
    LPVOID lpMsgBuf;
    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER      |
            FORMAT_MESSAGE_FROM_SYSTEM      |
            FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        dw,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR) &lpMsgBuf,
        0, NULL
    );
    // Display the error message and exit the process
    /*
        LPVOID lpDisplayBuf;
        lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT, (lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR));
        StringCchPrintf((LPTSTR)lpDisplayBuf, LocalSize(lpDisplayBuf) / sizeof(TCHAR), TEXT("%s failed with error %d: %s"), lpszFunction, dw, lpMsgBuf);
        MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK);
    */
    // SAT_PRINT("%s: %s\n",txt,lpMsgBuf);
    LocalFree(lpMsgBuf);
    // LocalFree(lpDisplayBuf);
    // ExitProcess(dw);
}


