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

class SAT_ClapEventRegistry
: public SAT_ClapExtension
{
    public:

        const char* getId() final       { return CLAP_EXT_EVENT_REGISTRY; }
        const void* getHostPtr() final  { return &MHostExtEventRegistry; }

    private: // host

        static bool event_registry_query_callback(const clap_host_t *host, const char *space_name, uint16_t *space_id);

        clap_host_event_registry_t MHostExtEventRegistry
        {
            .query  = event_registry_query_callback
        };


};

//----------------------------------------------------------------------
//
// host
//
//----------------------------------------------------------------------

bool SAT_ClapEventRegistry::event_registry_query_callback(const clap_host_t *host, const char *space_name, uint16_t *space_id) {
    SAT_ClapHost* h = (SAT_ClapHost*)host->host_data;
    return h->event_registry_query(space_name,space_id);
}
