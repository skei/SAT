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

class SAT_ClapTail
: public SAT_ClapExtension
{
    public:

        const char* getId() final       { return CLAP_EXT_TAIL; }
        const void* getPtr() final      { return &MPlugExtTail; }
        const void* getHostPtr() final  { return &MHostExtTail; }

    private: // plugin

        static uint32_t tail_get_callback(const clap_plugin_t *plugin);

        const clap_plugin_tail_t MPlugExtTail
        {
            .get = tail_get_callback
        };        

    private: // host

        static void tail_changed_callback(const clap_host_t *host);

        clap_host_tail_t MHostExtTail
        {
            .changed  = tail_changed_callback
        };        

};

//----------------------------------------------------------------------
//
// plugin
//
//----------------------------------------------------------------------

uint32_t SAT_ClapTail::tail_get_callback(const clap_plugin_t *plugin)
{
    SAT_ClapPlugin* p = (SAT_ClapPlugin*)plugin->plugin_data;
    return p->tail_get();
}

//----------------------------------------------------------------------
//
// host
//
//----------------------------------------------------------------------

void SAT_ClapTail::tail_changed_callback(const clap_host_t *host)
{
    SAT_ClapHost* h = (SAT_ClapHost*)host->host_data;
    h->tail_changed();
}
