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

class SAT_ClapTrackInfo
: public SAT_ClapExtension
{
    public:

        const char* getId() final       { return CLAP_EXT_TRACK_INFO; }
        const char* getCompatId() final { return CLAP_EXT_TRACK_INFO_COMPAT; }
        const void* getPtr() final      { return &MPlugExtTrackInfo; }
        const void* getHostPtr() final  { return &MHostExtTrackInfo; }

    private: // plugin

        static void track_info_changed_callback(const clap_plugin_t *plugin);

        const clap_plugin_track_info_t MPlugExtTrackInfo
        {
            .changed = track_info_changed_callback
        };        

    private: // host

        static bool track_info_get_callback(const clap_host_t *host, clap_track_info_t *info);

        clap_host_track_info_t MHostExtTrackInfo
        {
            .get  = track_info_get_callback
        };

};

//----------------------------------------------------------------------
//
// plugin
//
//----------------------------------------------------------------------

void SAT_ClapTrackInfo::track_info_changed_callback(const clap_plugin_t *plugin)
{
    SAT_ClapPlugin* p = (SAT_ClapPlugin*)plugin->plugin_data;
    p->track_info_changed();
}

//----------------------------------------------------------------------
//
// host
//
//----------------------------------------------------------------------

bool SAT_ClapTrackInfo::track_info_get_callback(const clap_host_t *host, clap_track_info_t *info)
{
    SAT_ClapHost* h = (SAT_ClapHost*)host->host_data;
    return h->track_info_get(info);
}
