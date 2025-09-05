#pragma once

#include "base/sat_base.h"
#include "extern/plugin/sat_clap.h"
#include "plugin/format/clap/sat_clap_plugin.h"
#include "plugin/format/clap/sat_clap_host.h"
#include "plugin/format/clap/sat_clap_extension.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_ClapPresetLoad
: public SAT_ClapExtension
{
    public:

        const char* getId() final       { return CLAP_EXT_PRESET_LOAD; }
        const char* getCompatId() final { return CLAP_EXT_PRESET_LOAD_COMPAT; }
        const void* getPtr() final      { return &MPlugExtPresetLoad; }
        const void* getHostPtr() final  { return &MHostExtPresetLoad; }

    private: // plugin

        static bool preset_load_from_location_callback(const clap_plugin_t *plugin, uint32_t location_kind, const char *location, const char *load_key);

        const clap_plugin_preset_load_t MPlugExtPresetLoad
        {
            .from_location = preset_load_from_location_callback
        };        

    private: // host

        static void preset_load_on_error_callback(const clap_host_t *host, uint32_t location_kind, const char *location, const char *load_key,int32_t os_error, const char *msg);
        static void preset_load_loaded_callback(const clap_host_t *host, uint32_t location_kind, const char *location, const char *load_key);

        clap_host_preset_load_t MHostExtPresetLoad
        {
            .on_error = preset_load_on_error_callback,
            .loaded   = preset_load_loaded_callback
        };        

};

//----------------------------------------------------------------------
//
// plugin
//
//----------------------------------------------------------------------

bool SAT_ClapPresetLoad::preset_load_from_location_callback(const clap_plugin_t *plugin, uint32_t location_kind, const char *location, const char *load_key)
{
    SAT_ClapPlugin* p = (SAT_ClapPlugin*)plugin->plugin_data;
    return p->preset_load_from_location(location_kind,location,load_key);
}

//----------------------------------------------------------------------
//
// host
//
//----------------------------------------------------------------------

void SAT_ClapPresetLoad::preset_load_on_error_callback(const clap_host_t *host, uint32_t location_kind, const char *location, const char *load_key,int32_t os_error, const char *msg)
{
    SAT_ClapHost* h = (SAT_ClapHost*)host->host_data;
    h->preset_load_on_error(location_kind,location,load_key,os_error,msg);
}

void SAT_ClapPresetLoad::preset_load_loaded_callback(const clap_host_t *host, uint32_t location_kind, const char *location, const char *load_key)
{
    SAT_ClapHost* h = (SAT_ClapHost*)host->host_data;
    h->preset_load_loaded(location_kind,location,load_key);
}
