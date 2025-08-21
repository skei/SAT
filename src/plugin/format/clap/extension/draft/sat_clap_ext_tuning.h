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

class SAT_ClapTuning
: public SAT_ClapExtension
{
    public:

        const char* getId() final       { return CLAP_EXT_TUNING; }
        const void* getPtr() final      { return &MPlugExtTuning; }
        const void* getHostPtr() final  { return &MHostExtTuning; }

    private: // plugin

        static void tuning_changed_callback(const clap_plugin_t *plugin);

        const clap_plugin_tuning_t MPlugExtTuning
        {
            .changed = tuning_changed_callback
        };        

  private: // host

        static double      tuning_get_relative_callback(const clap_host_t *host, clap_id tuning_id, int32_t channel, int32_t key, uint32_t sample_offset);
        static bool        tuning_should_play_callback(const clap_host_t *host, clap_id tuning_id, int32_t channel, int32_t key);
        static uint32_t    tuning_get_tuning_count_callback(const clap_host_t *host);
        static bool        tuning_get_info_callback(const clap_host_t *host, uint32_t tuning_index, clap_tuning_info_t *info);

        clap_host_tuning_t MHostExtTuning
        {
            .get_relative     = tuning_get_relative_callback,
            .should_play      = tuning_should_play_callback,
            .get_tuning_count = tuning_get_tuning_count_callback,
            .get_info         = tuning_get_info_callback
        };        

};

//----------------------------------------------------------------------
//
// plugin
//
//----------------------------------------------------------------------

void SAT_ClapTuning::tuning_changed_callback(const clap_plugin_t *plugin)
{
    SAT_ClapPlugin* p = (SAT_ClapPlugin*)plugin->plugin_data;
    p->tuning_changed();
}

//----------------------------------------------------------------------
//
// host
//
//----------------------------------------------------------------------

double SAT_ClapTuning::tuning_get_relative_callback(const clap_host_t *host, clap_id tuning_id, int32_t channel, int32_t key, uint32_t sample_offset)
{
    SAT_ClapHost* h = (SAT_ClapHost*)host->host_data;
    return h->tuning_get_relative(tuning_id,channel,key,sample_offset);
}

bool SAT_ClapTuning::tuning_should_play_callback(const clap_host_t *host, clap_id tuning_id, int32_t channel, int32_t key)
{
    SAT_ClapHost* h = (SAT_ClapHost*)host->host_data;
    return h->tuning_should_play(tuning_id,channel,key);
}

uint32_t SAT_ClapTuning::tuning_get_tuning_count_callback(const clap_host_t *host)
{
    SAT_ClapHost* h = (SAT_ClapHost*)host->host_data;
    return h->tuning_get_tuning_count();
}

bool SAT_ClapTuning::tuning_get_info_callback(const clap_host_t *host, uint32_t tuning_index, clap_tuning_info_t *info)
{
    SAT_ClapHost* h = (SAT_ClapHost*)host->host_data;
    return h->tuning_get_info(tuning_index,info);
}

