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

class SAT_ClapNoteName
: public SAT_ClapExtension
{
    public:

        const char* getId() final       { return CLAP_EXT_NOTE_NAME; }
        const void* getPtr() final      { return &MPlugExtNoteName; }
        const void* getHostPtr() final  { return &MHostExtNoteName; }

    private: // plugin

        static uint32_t note_name_count_callback(const clap_plugin_t *plugin);
        static bool note_name_get_callback(const clap_plugin_t *plugin, uint32_t index, clap_note_name_t *note_name);

        const clap_plugin_note_name_t MPlugExtNoteName
        {
            .count  = note_name_count_callback,
            .get    = note_name_get_callback
        };

    private: // host

        static void note_name_changed_callback(const clap_host_t *host);

        clap_host_note_name_t MHostExtNoteName
        {
            .changed  = note_name_changed_callback
        };

};

//----------------------------------------------------------------------
//
// plugin
//
//----------------------------------------------------------------------

uint32_t SAT_ClapNoteName::note_name_count_callback(const clap_plugin_t *plugin)
{
    SAT_ClapPlugin* p = (SAT_ClapPlugin*)plugin->plugin_data;
    return p->note_name_count();
}

bool SAT_ClapNoteName::note_name_get_callback(const clap_plugin_t *plugin, uint32_t index, clap_note_name_t *note_name)
{
    SAT_ClapPlugin* p = (SAT_ClapPlugin*)plugin->plugin_data;
    return p->note_name_get(index,note_name);
}

//----------------------------------------------------------------------
//
// host
//
//----------------------------------------------------------------------

void SAT_ClapNoteName::note_name_changed_callback(const clap_host_t *host)
{
    SAT_ClapHost* h = (SAT_ClapHost*)host->host_data;
    h->note_name_changed();
}

