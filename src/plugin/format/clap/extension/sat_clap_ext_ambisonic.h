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

class SAT_ClapAmbisonic
: public SAT_ClapExtension
{
    public:

        const char* getId() final       { return CLAP_EXT_AMBISONIC; }
        const char* getCompatId() final { return CLAP_EXT_AMBISONIC_COMPAT; }
        const void* getPtr() final      { return &MPlugExtAmbisonic; }
        const void* getHostPtr() final  { return &MHostExtAmbisonic; }
     
    private: // plugin

        static bool ambisonic_is_config_supported_callback(const clap_plugin_t *plugin, const clap_ambisonic_config_t *config);
        static bool ambisonic_get_config_callback(const clap_plugin_t *plugin, bool is_input, uint32_t port_index, clap_ambisonic_config_t *config);

        const clap_plugin_ambisonic_t MPlugExtAmbisonic
        {
            .is_config_supported  = ambisonic_is_config_supported_callback,
            .get_config           = ambisonic_get_config_callback
        };        

    private: // host

        static void ambisonic_changed_callback(const clap_host_t *host);

        const clap_host_ambisonic_t MHostExtAmbisonic
        {
            .changed = ambisonic_changed_callback
        };        

};

//----------------------------------------------------------------------
//
// plugin
//
//----------------------------------------------------------------------

bool SAT_ClapAmbisonic::ambisonic_is_config_supported_callback(const clap_plugin_t *plugin, const clap_ambisonic_config_t *config)
{
    SAT_ClapPlugin* p = (SAT_ClapPlugin*)plugin->plugin_data;
    return p->ambisonic_is_config_supported(config);
}

bool SAT_ClapAmbisonic::ambisonic_get_config_callback(const clap_plugin_t *plugin, bool is_input, uint32_t port_index, clap_ambisonic_config_t *config)
{
    SAT_ClapPlugin* p = (SAT_ClapPlugin*)plugin->plugin_data;
    return p->ambisonic_get_config(is_input,port_index,config);
}

//----------------------------------------------------------------------
//
// host
//
//----------------------------------------------------------------------

void SAT_ClapAmbisonic::ambisonic_changed_callback(const clap_host_t *host)
{
    SAT_ClapHost*h = (SAT_ClapHost*)host->host_data;
    h->ambisonic_changed();
}
