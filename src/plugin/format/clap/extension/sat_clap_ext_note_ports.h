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

class SAT_ClapNotePorts
: public SAT_ClapExtension
{
    public:

        const char* getId() final       { return CLAP_EXT_NOTE_PORTS; }
        const void* getPtr() final      { return &MPlugExtNotePorts; }
        const void* getHostPtr() final  { return &MHostExtNotePorts; }

    private: // plugin

        static uint32_t note_ports_count_callback(const clap_plugin_t *plugin, bool is_input);
        static bool     note_ports_get_callback(const clap_plugin_t *plugin, uint32_t index, bool is_input, clap_note_port_info_t *info);

        const clap_plugin_note_ports_t MPlugExtNotePorts
        {
            .count  = note_ports_count_callback,
            .get    = note_ports_get_callback
        };


    private: // host

        static uint32_t note_ports_supported_dialects_callback(const clap_host_t *host);
        static void     note_ports_rescan_callback(const clap_host_t *host, uint32_t flags);

        clap_host_note_ports_t MHostExtNotePorts = {
            .supported_dialects  = note_ports_supported_dialects_callback,
            .rescan              = note_ports_rescan_callback
        };        

};

//----------------------------------------------------------------------
//
// plugin
//
//----------------------------------------------------------------------

uint32_t SAT_ClapNotePorts::note_ports_count_callback(const clap_plugin_t *plugin, bool is_input)
{
    SAT_ClapPlugin* p = (SAT_ClapPlugin*)plugin->plugin_data;
    return p->note_ports_count(is_input);
}

bool SAT_ClapNotePorts::note_ports_get_callback(const clap_plugin_t *plugin, uint32_t index, bool is_input, clap_note_port_info_t *info)
{
    SAT_ClapPlugin* p = (SAT_ClapPlugin*)plugin->plugin_data;
    return p->note_ports_get(index,is_input,info);
}

//----------------------------------------------------------------------
//
// host
//
//----------------------------------------------------------------------

uint32_t SAT_ClapNotePorts::note_ports_supported_dialects_callback(const clap_host_t *host)
{
    SAT_ClapHost* h = (SAT_ClapHost*)host->host_data;
    return h->note_ports_supported_dialects();
  }

void SAT_ClapNotePorts::note_ports_rescan_callback(const clap_host_t *host, uint32_t flags)
{
    SAT_ClapHost* h = (SAT_ClapHost*)host->host_data;
    h->note_ports_rescan(flags);
  }
