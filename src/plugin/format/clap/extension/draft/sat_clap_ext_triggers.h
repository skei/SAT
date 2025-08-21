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

class SAT_ClapTriggers
: public SAT_ClapExtension
{
    public:

        const char* getId() final       { return CLAP_EXT_TRIGGERS; }
        const void* getPtr() final      { return &MPlugExtTriggers; }
        const void* getHostPtr() final  { return &MHostExtTriggers; }

    private: // plugin

        static uint32_t triggers_count_callback(const clap_plugin_t *plugin);
        static bool     triggers_get_info_callback(const clap_plugin_t *plugin, uint32_t index, clap_trigger_info_t *trigger_info);

        const clap_plugin_triggers_t MPlugExtTriggers
        {
            .count    = triggers_count_callback,
            .get_info = triggers_get_info_callback
        };        

    private: // host

        static void triggers_rescan_callback(const clap_host_t *host, clap_trigger_rescan_flags flags);
        static void triggers_clear_callback(const clap_host_t *host, clap_id trigger_id, clap_trigger_clear_flags flags);

        clap_host_triggers_t MHostExtTriggers
        {
            .rescan = triggers_rescan_callback,
            .clear  = triggers_clear_callback
        };        

};

//----------------------------------------------------------------------
//
// plugin
//
//----------------------------------------------------------------------

uint32_t SAT_ClapTriggers::triggers_count_callback(const clap_plugin_t *plugin)
{
    SAT_ClapPlugin* p = (SAT_ClapPlugin*)plugin->plugin_data;
    return p->triggers_count();
}

bool SAT_ClapTriggers::triggers_get_info_callback(const clap_plugin_t *plugin, uint32_t index, clap_trigger_info_t *trigger_info)
{
    SAT_ClapPlugin* p = (SAT_ClapPlugin*)plugin->plugin_data;
    return p->triggers_get_info(index,trigger_info);
}

//----------------------------------------------------------------------
//
// host
//
//----------------------------------------------------------------------

void SAT_ClapTriggers::triggers_rescan_callback(const clap_host_t *host, clap_trigger_rescan_flags flags)
{
    SAT_ClapHost* h = (SAT_ClapHost*)host->host_data;
    h->triggers_rescan(flags);
}

void SAT_ClapTriggers::triggers_clear_callback(const clap_host_t *host, clap_id trigger_id, clap_trigger_clear_flags flags)
{
    SAT_ClapHost* h = (SAT_ClapHost*)host->host_data;
    h->triggers_clear(trigger_id,flags);
}
