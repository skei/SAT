#pragma once

/*
    CLAP plugins can access the REAPER API via:
        const void* clap_host.get_extension(const clap_host* host,"cockos.reaper_extension");
    which returns a pointer to a reaper_plugin_info_t struct

    struct reaper_plugin_info_t
    {
        int     caller_version;
        HWND    hwnd_main;
        int     (*Register)(const char* name, void* infostruct);
        void*   (*GetFunc)(const char* name);
    };
*/

#include "base/sat_base.h"
#include "plugin/format/clap/sat_clap.h"
// #include "plugin/format/clap/sat_clap_plugin.h"
// #include "plugin/format/clap/sat_clap_host.h"
// #include "plugin/format/clap/sat_clap_extension.h"

// #include "extern/plugin/reaper/reaper_plugin.h"
// #include "extern/plugin/reaper/reaper_plugin_functions.h"


//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

#ifndef SAT_WIN32
    typedef void* HWND;
#endif

typedef struct reaper_plugin_info_t
{
    int     caller_version;
    HWND    hwnd_main;
    int     (*Register)(const char* name, void* infostruct);
    void*   (*GetFunc)(const char* name);
} reaper_plugin_info_t;

const reaper_plugin_info_t* SAT_GetReaperExtension(const clap_host_t* AHost);

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

const reaper_plugin_info_t* SAT_GetReaperExtension(const clap_host_t* AHost)
{
    return (const reaper_plugin_info_t*)AHost->get_extension(AHost,"cockos.reaper_extension");
}
