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

class SAT_ClapExtensibleAudioPorts
: public SAT_ClapExtension
{
    public:

        const char* getId() final       { return CLAP_EXT_EXTENSIBLE_AUDIO_PORTS; }
        const void* getPtr() final      { return &MPlugExtExtensibleAudioPorts; }

    private: // plugin

        static bool extensible_audio_ports_add_port_callback(const clap_plugin_t *plugin, bool is_input, uint32_t channel_count, const char *port_type, const void *port_details);
        static bool extensible_audio_ports_remove_port_callback(const clap_plugin_t *plugin, bool is_input, uint32_t index);

        const clap_plugin_extensible_audio_ports_t MPlugExtExtensibleAudioPorts
        {
            .add_port     = extensible_audio_ports_add_port_callback,
            .remove_port  = extensible_audio_ports_remove_port_callback
        };        

};

//----------------------------------------------------------------------
//
// plugin
//
//----------------------------------------------------------------------

bool SAT_ClapExtensibleAudioPorts::extensible_audio_ports_add_port_callback(const clap_plugin_t *plugin, bool is_input, uint32_t channel_count, const char *port_type, const void *port_details)
{
    SAT_ClapPlugin* p = (SAT_ClapPlugin*)plugin->plugin_data;
    return p->extensible_audio_ports_add_port(is_input,channel_count,port_type,port_details);
}

bool SAT_ClapExtensibleAudioPorts::extensible_audio_ports_remove_port_callback(const clap_plugin_t *plugin, bool is_input, uint32_t index)
{
    SAT_ClapPlugin* p = (SAT_ClapPlugin*)plugin->plugin_data;
    return p->extensible_audio_ports_remove_port(is_input,index);
}
