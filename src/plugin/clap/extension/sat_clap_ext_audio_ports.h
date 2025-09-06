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

class SAT_ClapAudioPorts
: public SAT_ClapExtension
{
    public:

        const char* getId() final       { return CLAP_EXT_AUDIO_PORTS; }
        const void* getPtr() final      { return &MPlugExtAudioPorts; }
        const void* getHostPtr() final  { return &MHostExtAudioPorts; }

    private: // plugin

        static uint32_t audio_ports_count_callback(const clap_plugin_t *plugin, bool is_input);
        static bool audio_ports_get_callback(const clap_plugin_t *plugin, uint32_t index, bool is_input, clap_audio_port_info_t *info);

        const clap_plugin_audio_ports_t MPlugExtAudioPorts
        {
            .count  = audio_ports_count_callback,
            .get    = audio_ports_get_callback
        };        

    private: // host

        static bool audio_ports_is_rescan_flag_supported_callback(const clap_host_t *host, uint32_t flag);
        static void audio_ports_rescan_callback(const clap_host_t *host, uint32_t flags);

        clap_host_audio_ports_t MHostExtAudioPorts
        {
            .is_rescan_flag_supported = audio_ports_is_rescan_flag_supported_callback,
            .rescan                   = audio_ports_rescan_callback
        };        

};

//----------------------------------------------------------------------
//
// plugin
//
//----------------------------------------------------------------------

uint32_t SAT_ClapAudioPorts::audio_ports_count_callback(const clap_plugin_t *plugin, bool is_input)
{
    SAT_ClapPlugin* p = (SAT_ClapPlugin*)plugin->plugin_data;
    return p->audio_ports_count(is_input);
}

bool SAT_ClapAudioPorts::audio_ports_get_callback(const clap_plugin_t *plugin, uint32_t index, bool is_input, clap_audio_port_info_t *info)
{
    SAT_ClapPlugin* p = (SAT_ClapPlugin*)plugin->plugin_data;
    return p->audio_ports_get(index,is_input,info);
}

//----------------------------------------------------------------------
//
// host
//
//----------------------------------------------------------------------

bool SAT_ClapAudioPorts::audio_ports_is_rescan_flag_supported_callback(const clap_host_t *host, uint32_t flag)
{
    SAT_ClapHost* h = (SAT_ClapHost*)host->host_data;
    return h->audio_ports_is_rescan_flag_supported(flag);
}

void SAT_ClapAudioPorts::audio_ports_rescan_callback(const clap_host_t *host, uint32_t flags)
{
    SAT_ClapHost* h = (SAT_ClapHost*)host->host_data;
    h->audio_ports_rescan(flags);
}
