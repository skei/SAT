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

class SAT_ClapTimerSupport
: public SAT_ClapExtension
{
    public:

        const char* getId() final       { return CLAP_EXT_TIMER_SUPPORT; }
        const void* getPtr() final      { return &MPlugExtTimerSupport; }
        const void* getHostPtr() final  { return &MHostExtTimerSupport; }

    private: // plugin

        static void timer_support_on_timer_callback(const clap_plugin_t *plugin, clap_id timer_id);

        const clap_plugin_timer_support_t MPlugExtTimerSupport
        {
            .on_timer = timer_support_on_timer_callback
        };

    private: // host

        static bool timer_support_register_timer_callback(const clap_host_t *host, uint32_t period_ms, clap_id *timer_id);
        static bool timer_support_unregister_timer_callback(const clap_host_t *host, clap_id timer_id);

        clap_host_timer_support_t MHostExtTimerSupport
        {
            .register_timer   = timer_support_register_timer_callback,
            .unregister_timer = timer_support_unregister_timer_callback
        };        

};

//----------------------------------------------------------------------
//
// plugin
//
//----------------------------------------------------------------------

void SAT_ClapTimerSupport::timer_support_on_timer_callback(const clap_plugin_t *plugin, clap_id timer_id)
{
    SAT_ClapPlugin* p = (SAT_ClapPlugin*)plugin->plugin_data;
    p->timer_support_on_timer(timer_id);
}

//----------------------------------------------------------------------
//
// host
//
//----------------------------------------------------------------------

bool SAT_ClapTimerSupport::timer_support_register_timer_callback(const clap_host_t *host, uint32_t period_ms, clap_id *timer_id)
{
    SAT_ClapHost* h = (SAT_ClapHost*)host->host_data;
    return h->timer_support_register_timer(period_ms,timer_id);
}

bool SAT_ClapTimerSupport::timer_support_unregister_timer_callback(const clap_host_t *host, clap_id timer_id)
{
    SAT_ClapHost* h = (SAT_ClapHost*)host->host_data;
    return h->timer_support_unregister_timer(timer_id);
}
