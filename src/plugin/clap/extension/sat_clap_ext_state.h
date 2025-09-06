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

class SAT_ClapState
: public SAT_ClapExtension
{
    public:

        const char* getId() final       { return CLAP_EXT_STATE; }
        const void* getPtr() final      { return &MPlugExtState; }
        const void* getHostPtr() final  { return &MHostExtState; }

    private: // plugin

        static bool state_save_callback(const clap_plugin_t *plugin, const clap_ostream_t *stream);
        static bool state_load_callback(const clap_plugin_t *plugin, const clap_istream_t *stream);

        const clap_plugin_state_t MPlugExtState
        {
            .save = state_save_callback,
            .load = state_load_callback
        };        

    private: // host

        static void state_mark_dirty_callback(const clap_host_t *host);

        clap_host_state_t MHostExtState
        {
            .mark_dirty  = state_mark_dirty_callback
        };

};

//----------------------------------------------------------------------
//
// plugin
//
//----------------------------------------------------------------------

bool SAT_ClapState::state_save_callback(const clap_plugin_t *plugin, const clap_ostream_t *stream)
{
    SAT_ClapPlugin* p = (SAT_ClapPlugin*)plugin->plugin_data;
    return p->state_save(stream);
}

bool SAT_ClapState::state_load_callback(const clap_plugin_t *plugin, const clap_istream_t *stream)
{
    SAT_ClapPlugin* p = (SAT_ClapPlugin*)plugin->plugin_data;
    return p->state_load(stream);
}

//----------------------------------------------------------------------
//
// host
//
//----------------------------------------------------------------------

void SAT_ClapState::state_mark_dirty_callback(const clap_host_t *host)
{
    SAT_ClapHost* h = (SAT_ClapHost*)host->host_data;
    h->state_mark_dirty();
}
