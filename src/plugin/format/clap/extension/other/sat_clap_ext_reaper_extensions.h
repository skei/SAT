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

//----------

/*
    reaper v7.43+dev0821 - August 21 2025:
    https://github.com/justinfrankel/reaper-sdk/blob/main/sdk/reaper_plugin_fx_embed.h    
    
    CLAP: support embedded ui
    host requests "cockos.reaper_embedui", plugin returns

    struct clap_plugin_reaper_embedui
    {
        INT_PTR *(*inline_editor)(const clap_plugin_t *plugin, int msg, void *param1, void *param2);
    };
*/

//----------

#include "base/sat_base.h"
#include "extern/plugin/sat_clap.h"
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
