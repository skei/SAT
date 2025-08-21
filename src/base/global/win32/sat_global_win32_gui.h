#pragma once

#undef  _WIN32_WINNT
#define _WIN32_WINNT 0x0501
// #ifndef SAT_WIN32_GDIPLUS
#ifndef WIN32_LEAN_AND_MEAN
    #define WIN32_LEAN_AND_MEAN
#endif
// #endif
#include <windows.h>

// see also:
// https://msdn.microsoft.com/en-us/library/windows/desktop/dd145130%28v=vs.85%29.aspx

// missing raster ops
#define DSTCOPY   0x00AA0029
#define DSTERASE  0x00220326 // dest = dest & (~ src) :  DSna
// #define FORE_ROP3(ROP4) (0x00FFFFFF & (ROP4))
// #define BACK_ROP3(ROP4) (ROP3FromIndex (SwapROP3_SrcDst (BYTE ((ROP4) >> 24))))

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

#include "base/sat_base.h"
#include "base/global/sat_global_base.h"
#include "base/util/sat_strutils.h"         // SAT_CreateUniqueString

// #if defined SAT_USE_WIN32
//     #include "gui/system/win32/sat_win32.h"
// #endif

//----------

/*
    CS_OWNDC    Allocates a unique device context for each window in the class
    CS_HREDRAW  Redraws the entire window if a movement or size adjustment
                changes the width of the client area.
    CS_VREDRAW  Redraws the entire window if a movement or size adjustment
                changes the height of the client area.
*/

// #define SAT_WIN32_CLASS_STYLE          ( CS_OWNDC )
#define SAT_WIN32_CLASS_STYLE           ( CS_OWNDC | CS_HREDRAW | CS_VREDRAW )

#define SAT_WIN32_STANDALONE_STYLE      ( WS_OVERLAPPEDWINDOW )
#define SAT_WIN32_EMBEDDED_STYLE        ( WS_CHILD )

#define SAT_WIN32_EX_STANDALONE_STYLE   ( 0 /*WS_EX_OVERLAPPEDWINDOW*/ )
#define SAT_WIN32_EX_EMBEDDED_STYLE     ( 0 /* WS_EX_TOOLWINDOW */ )

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_GlobalGui
{
    public:

        SAT_GlobalGui();
        ~SAT_GlobalGui();
        void activate(SAT_GlobalBase* AGlobal);
        void deactivate(SAT_GlobalBase* AGlobal);

    public:

        uint32_t        getScreenWidth();
        uint32_t        getScreenHeight();
        uint32_t        getScreenDepth();
        char*           getWindowClassName();

    private:

        void            registerWindowClass(WNDPROC AWndProc, const char* AClassName);
        void            unregisterWindowClass();

    private:

        bool            MIsActivated    = false;
        SAT_GlobalBase* MGlobal         = nullptr;

    private:

        // bool         MRegistered     = false;
        // WNDCLASS     MWndClass       = {};
        // ATOM         MAtom           = 0;
        // char         MName[SAT_MAX_STRING_LENGTH] = "sat_window_0";
        uint32_t        MNumRegisteredClasses = 0;

};

//----------------------------------------------------------------------
//
// implementation
//
//----------------------------------------------------------------------

SAT_GlobalGui::SAT_GlobalGui()
{
}

SAT_GlobalGui::~SAT_GlobalGui()
{
}

void SAT_GlobalGui::activate(SAT_GlobalBase* AGlobal)
{
    if (!MIsActivated)
    {
        MGlobal = AGlobal;
        // registerWindowClass();
        MIsActivated = true;
    }
}

void SAT_GlobalGui::deactivate(SAT_GlobalBase* AGlobal)
{
    if (MIsActivated)
    {
        // unregisterWindowClass();
        if (MNumRegisteredClasses > 0) {
            SAT_GLOBAL_DPRINT("  Warning: not all window classes are unregistered!\n");
        }
        MGlobal = nullptr;
        MIsActivated = false;
    }
}

//------------------------------
// win32
//------------------------------

uint32_t SAT_GlobalGui::getScreenWidth()
{
    return 0;
}

uint32_t SAT_GlobalGui::getScreenHeight()
{
    return 0;
}

uint32_t SAT_GlobalGui::getScreenDepth()
{
    return 0;
}

// static
// LRESULT CALLBACK sat_win32_eventproc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
// {
//     SAT_Win32Window* window = (SAT_Win32Window*)GetWindowLongPtr(hWnd,GWLP_USERDATA);
// 	if (!window) return DefWindowProc(hWnd,message,wParam,lParam);
//     return window->eventHandler(hWnd, message, wParam, lParam);
// }

void SAT_GlobalGui::registerWindowClass(WNDPROC AWndProc, const char* AClassName)
{
    // if (!MRegistered)
    // {
        HINSTANCE instance = MGlobal->SYSTEM->getInstance()
        // SAT_CreateUniqueString(MName,(char*)"sat_win32_window_",&instance);
        memset(&MClass,0,sizeof(MClass));
        MClass.style          = SAT_WIN32_CLASS_STYLE;
        MClass.lpfnWndProc    = AWndProc; // &sat_win32_eventproc;
        MClass.hInstance      = instance;
        MClass.lpszClassName  = AName;
        // #ifdef SAT_MOUSE_DOUBLECLICK
        //     MClass.style |= CS_DBLCLKS;
        // #endif
        WNDCLASS wndclass;
        ATOM atom = RegisterClass(&wndclass);
        MRegistered = true;
    // }
    // return MName;
    MNumRegisteredClasses += 1;
}

void SAT_GlobalGui::unregisterWindowClass(const char* AClassName)
{
    // if (MRegistered)
    // {
        HINSTANCE instance = MGlobal->SYSTEM->getInstance()
        UnregisterClass(AClassName,instance);
    // }
    MNumRegisteredClasses -= 1;
}
