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

class SAT_ClapAudioPortsConfigInfo
: public SAT_ClapExtension
{
    public:

        // see also: CLAP_EXT_AUDIO_PORTS_CONFIG

        const char* getId() final       { return CLAP_EXT_AUDIO_PORTS_CONFIG_INFO; }
        const char* getCompatId() final { return CLAP_EXT_AUDIO_PORTS_CONFIG_INFO_COMPAT; }
        const void* getPtr() final      { return &MPlugExtAudioPortsConfigInfo; }

    private: // plugin

        static clap_id  audio_ports_config_info_current_config_callback(const clap_plugin_t *plugin);
        static bool     audio_ports_config_info_get_callback(const clap_plugin_t* plugin, clap_id config_id, uint32_t port_index, bool is_input, clap_audio_port_info_t* info);

        const clap_plugin_audio_ports_config_info_t MPlugExtAudioPortsConfigInfo
        {
            .current_config = audio_ports_config_info_current_config_callback,
            .get            = audio_ports_config_info_get_callback
        };      

};

//----------------------------------------------------------------------
//
// plugin
//
//----------------------------------------------------------------------

  uint32_t SAT_ClapAudioPortsConfigInfo::audio_ports_config_info_current_config_callback(const clap_plugin_t *plugin)
  {
        SAT_ClapPlugin* p = (SAT_ClapPlugin*)plugin->plugin_data;
        return p->audio_ports_config_info_current_config();
  }

  bool SAT_ClapAudioPortsConfigInfo::audio_ports_config_info_get_callback(const clap_plugin_t* plugin, clap_id config_id, uint32_t port_index, bool is_input, clap_audio_port_info_t* info)
  {
        SAT_ClapPlugin* p = (SAT_ClapPlugin*)plugin->plugin_data;
        return p->audio_ports_config_info_get(config_id,port_index,is_input,info);
  }

