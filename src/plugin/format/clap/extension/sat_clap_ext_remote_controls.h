#pragma once

#include "base/sat_base.h"
#include "extern/plugin/sat_clap.h"
#include "plugin/format/clap/sat_clap_plugin.h"
#include "plugin/format/clap/sat_clap_host.h"
#include "plugin/format/clap/sat_clap_extension.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_ClapRemoteControls
: public SAT_ClapExtension
{
    public:

        const char* getId() final       { return CLAP_EXT_REMOTE_CONTROLS; }
        const char* getCompatId() final { return CLAP_EXT_REMOTE_CONTROLS_COMPAT; }
        const void* getPtr() final      { return &MPlugExtRemoteControls; }
        const void* getHostPtr() final  { return &MHostExtRemoteControls; }

    private: // plugin

        static uint32_t remote_controls_count_callback(const clap_plugin_t *plugin);
        static bool remote_controls_get_callback(const clap_plugin_t *plugin, uint32_t page_index, clap_remote_controls_page_t *page);

        const clap_plugin_remote_controls_t MPlugExtRemoteControls
        {
            .count  = remote_controls_count_callback,
            .get    = remote_controls_get_callback
        };        

    private: // host

        static void remote_controls_changed_callback(const clap_host_t *host);
        static void remote_controls_suggest_page_callback(const clap_host_t *host, clap_id page_id);

        clap_host_remote_controls_t MHostExtRemoteControls
        {
            .changed      = remote_controls_changed_callback,
            .suggest_page = remote_controls_suggest_page_callback
        };        

};

//----------------------------------------------------------------------
//
// plugin
//
//----------------------------------------------------------------------

uint32_t SAT_ClapRemoteControls::remote_controls_count_callback(const clap_plugin_t *plugin)
{
    SAT_ClapPlugin* p = (SAT_ClapPlugin*)plugin->plugin_data;
    return p->remote_controls_count();
}

bool SAT_ClapRemoteControls::remote_controls_get_callback(const clap_plugin_t *plugin, uint32_t page_index, clap_remote_controls_page_t *page)
{
    SAT_ClapPlugin* p = (SAT_ClapPlugin*)plugin->plugin_data;
    return p->remote_controls_get(page_index,page);
}

//----------------------------------------------------------------------
//
// host
//
//----------------------------------------------------------------------

void SAT_ClapRemoteControls::remote_controls_changed_callback(const clap_host_t *host)
{
    SAT_ClapHost* h = (SAT_ClapHost*)host->host_data;
    h->remote_controls_changed();
}

void SAT_ClapRemoteControls::remote_controls_suggest_page_callback(const clap_host_t *host, clap_id page_id)
{
    SAT_ClapHost* h = (SAT_ClapHost*)host->host_data;
    h->remote_controls_suggest_page(page_id);
}
