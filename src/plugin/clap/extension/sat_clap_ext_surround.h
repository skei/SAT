#pragma once

#include "base/sat_base.h"
#include "extern/plugin/sat_clap.h"
#include "plugin/clap/sat_clap_plugin.h"
#include "plugin/clap/sat_clap_host.h"
#include "plugin/clap/sat_clap_extension.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_ClapSurround
: public SAT_ClapExtension
{
    public:

        const char* getId() final       { return CLAP_EXT_SURROUND; }
        const char* getCompatId() final { return CLAP_EXT_SURROUND_COMPAT; }
        const void* getPtr() final      { return &MPlugExtSurround; }
        const void* getHostPtr() final  { return &MHostExtSurround; }

    private: // plugin

        static bool     surround_is_channel_mask_supported_callback(const clap_plugin_t *plugin, uint64_t channel_mask);
        static uint32_t surround_get_channel_map_callback(const clap_plugin_t *plugin, bool is_input, uint32_t port_index, uint8_t *channel_map, uint32_t channel_map_capacity);

        const clap_plugin_surround_t MPlugExtSurround
        {
            .is_channel_mask_supported  =  surround_is_channel_mask_supported_callback,
            .get_channel_map            =  surround_get_channel_map_callback
        };        

    private: // host

        static void surround_changed_callback(const clap_host_t *host);

        clap_host_surround_t MHostExtSurround
        {
            .changed = surround_changed_callback
        };        

};

//----------------------------------------------------------------------
//
// plugin
//
//----------------------------------------------------------------------

bool SAT_ClapSurround::surround_is_channel_mask_supported_callback(const clap_plugin_t *plugin, uint64_t channel_mask)
{
    SAT_ClapPlugin* p = (SAT_ClapPlugin*)plugin->plugin_data;
    return p->surround_is_channel_mask_supported(channel_mask);
}

uint32_t SAT_ClapSurround::surround_get_channel_map_callback(const clap_plugin_t *plugin, bool is_input, uint32_t port_index, uint8_t *channel_map, uint32_t channel_map_capacity)
{
    SAT_ClapPlugin* p = (SAT_ClapPlugin*)plugin->plugin_data;
    return p->surround_get_channel_map(is_input,port_index,channel_map,channel_map_capacity);
}

//----------------------------------------------------------------------
//
// host
//
//----------------------------------------------------------------------

void SAT_ClapSurround::surround_changed_callback(const clap_host_t *host)
{
    SAT_ClapHost* h = (SAT_ClapHost*)host->host_data;
    h->surround_changed();
}
