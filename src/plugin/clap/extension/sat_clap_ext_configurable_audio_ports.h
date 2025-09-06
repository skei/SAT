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

class SAT_ClapConfigurableAudioPorts
: public SAT_ClapExtension
{
    public:

        const char* getId() final       { return CLAP_EXT_CONFIGURABLE_AUDIO_PORTS; }
        const char* getCompatId() final { return CLAP_EXT_CONFIGURABLE_AUDIO_PORTS_COMPAT; }
        const void* getPtr() final      { return &MPlugExtConfigurableAudioPorts; }

    private: // plugin

        static bool configurable_audio_ports_can_apply_configuration_callback(const clap_plugin_t *plugin, const struct clap_audio_port_configuration_request *requests, uint32_t request_count);
        static bool configurable_audio_ports_apply_configuration_callback(const clap_plugin_t *plugin, const struct clap_audio_port_configuration_request *requests, uint32_t request_count);

        const clap_plugin_configurable_audio_ports_t MPlugExtConfigurableAudioPorts
        {
            .can_apply_configuration  = configurable_audio_ports_can_apply_configuration_callback,
            .apply_configuration      = configurable_audio_ports_apply_configuration_callback
        };        

};

//----------------------------------------------------------------------
//
// plugin
//
//----------------------------------------------------------------------

bool SAT_ClapConfigurableAudioPorts::configurable_audio_ports_can_apply_configuration_callback(const clap_plugin_t *plugin, const struct clap_audio_port_configuration_request *requests, uint32_t request_count)
{
    SAT_ClapPlugin* p = (SAT_ClapPlugin*)plugin->plugin_data;
    return p->configurable_audio_ports_can_apply_configuration(requests,request_count);
}

bool SAT_ClapConfigurableAudioPorts::configurable_audio_ports_apply_configuration_callback(const clap_plugin_t *plugin, const struct clap_audio_port_configuration_request *requests, uint32_t request_count)
{
    SAT_ClapPlugin* p = (SAT_ClapPlugin*)plugin->plugin_data;
    return p->configurable_audio_ports_apply_configuration(requests,request_count);
}
