#pragma once

#include "base/sat_base.h"
#include "plugin/format/clap/sat_clap.h"
#include "plugin/format/clap/sat_clap_plugin.h"
#include "plugin/format/clap/sat_clap_host.h"
#include "plugin/format/clap/sat_clap_extension.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_ClapAudioPortsConfig
: public SAT_ClapExtension
{
    public:

        // see also: CLAP_EXT_AUDIO_PORTS_CONFIG_INFO

        const char* getId() final       { return CLAP_EXT_AUDIO_PORTS_CONFIG; }
        const void* getPtr() final      { return &MPlugExtAudioPortsConfig; }
        const void* getHostPtr() final  { return &MMostExtAudioPortsConfig; }

    private: // plugin

        static uint32_t audio_ports_config_count_callback(const clap_plugin_t *plugin);
        static bool     audio_ports_config_get_callback(const clap_plugin_t *plugin, uint32_t index, clap_audio_ports_config_t *config);
        static bool     audio_ports_config_select_callback(const clap_plugin_t *plugin, clap_id config_id);

        const clap_plugin_audio_ports_config_t MPlugExtAudioPortsConfig
        {
            .count  = audio_ports_config_count_callback,
            .get    = audio_ports_config_get_callback,
            .select = audio_ports_config_select_callback
        };      

    private: // host

        static void audio_ports_config_rescan_callback(const clap_host_t *host);

        const clap_host_audio_ports_config_t MMostExtAudioPortsConfig
        {
            .rescan = audio_ports_config_rescan_callback
        };    

};

//----------------------------------------------------------------------
//
// plugin
//
//----------------------------------------------------------------------

  uint32_t SAT_ClapAudioPortsConfig::audio_ports_config_count_callback(const clap_plugin_t *plugin) {
    SAT_ClapPlugin* p = (SAT_ClapPlugin*)plugin->plugin_data;
    return p->audio_ports_config_count();
  }

  bool SAT_ClapAudioPortsConfig::audio_ports_config_get_callback(const clap_plugin_t *plugin, uint32_t index, clap_audio_ports_config_t *config) {
    SAT_ClapPlugin* p = (SAT_ClapPlugin*)plugin->plugin_data;
    return p->audio_ports_config_get(index,config);
  }
 
  bool SAT_ClapAudioPortsConfig::audio_ports_config_select_callback(const clap_plugin_t *plugin, clap_id config_id) {
    SAT_ClapPlugin* p = (SAT_ClapPlugin*)plugin->plugin_data;
    return p->audio_ports_config_select(config_id);
  }  

//----------------------------------------------------------------------
//
// host
//
//----------------------------------------------------------------------

void SAT_ClapAudioPortsConfig::audio_ports_config_rescan_callback(const clap_host_t *host)
{
    SAT_ClapHost* h = (SAT_ClapHost*)host->host_data;
    h->audio_ports_config_rescan();
}
