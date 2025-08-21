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

class SAT_ClapAudioPortsActivation
: public SAT_ClapExtension
{
    public:

        const char* getId() final       { return CLAP_EXT_AUDIO_PORTS_ACTIVATION; }
        const char* getCompatId() final { return CLAP_EXT_AUDIO_PORTS_ACTIVATION_COMPAT; }
        const void* getPtr() final      { return &MPlugExtAudioPortsActivation; }

    private: // plugin

        static bool audio_ports_activation_can_activate_while_processing_callback(const clap_plugin_t *plugin);
        static bool audio_ports_activation_set_active_callback(const clap_plugin_t *plugin, bool is_input, uint32_t port_index, bool is_active, uint32_t sample_size);

        const clap_plugin_audio_ports_activation_t MPlugExtAudioPortsActivation
        {
            .can_activate_while_processing  = audio_ports_activation_can_activate_while_processing_callback,
            .set_active                     = audio_ports_activation_set_active_callback
  };        

};

//----------------------------------------------------------------------
//
// plugin
//
//----------------------------------------------------------------------

  bool SAT_ClapAudioPortsActivation::audio_ports_activation_can_activate_while_processing_callback(const clap_plugin_t *plugin)
  {
    SAT_ClapPlugin* p = (SAT_ClapPlugin*)plugin->plugin_data;
    return p->audio_ports_activation_can_activate_while_processing();
  }

  bool SAT_ClapAudioPortsActivation::audio_ports_activation_set_active_callback(const clap_plugin_t *plugin, bool is_input, uint32_t port_index, bool is_active, uint32_t sample_size)
  {
    SAT_ClapPlugin* p = (SAT_ClapPlugin*)plugin->plugin_data;
    return p->audio_ports_activation_set_active(is_input,port_index,is_active,sample_size);
  }
