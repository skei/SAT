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

class SAT_ClapLatency
: public SAT_ClapExtension
{
    public:

        const char* getId() final       { return CLAP_EXT_LATENCY; }
        const void* getPtr() final      { return &MPlugExtLatency; }
        const void* getHostPtr() final  { return &MHostExtLatency; }

    private:

        static uint32_t latency_get_callback(const clap_plugin_t *plugin);

        const clap_plugin_latency_t MPlugExtLatency
        {
            .get = latency_get_callback
        };

    private:

        static void latency_changed_callback(const clap_host_t *host);

        const clap_host_latency_t MHostExtLatency {
            .changed = latency_changed_callback
        };
};

//----------------------------------------------------------------------
//
// plugin
//
//----------------------------------------------------------------------

uint32_t SAT_ClapLatency::latency_get_callback(const clap_plugin_t *plugin)
{
    SAT_ClapPlugin* p = (SAT_ClapPlugin*)plugin->plugin_data;
    return p->latency_get();
}

//----------------------------------------------------------------------
//
// host
//
//----------------------------------------------------------------------

void SAT_ClapLatency::latency_changed_callback(const clap_host_t *host)
{
    SAT_ClapHost* h = (SAT_ClapHost*)host->host_data;
    h->latency_changed();
}

