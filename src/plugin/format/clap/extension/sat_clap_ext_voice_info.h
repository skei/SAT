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

class SAT_ClapVoiceInfo
: public SAT_ClapExtension
{
    public:

        const char* getId() final       { return CLAP_EXT_VOICE_INFO; }
        const void* getPtr() final      { return &MPlugExtVoiceInfo; }
        const void* getHostPtr() final  { return &MHostExtVoiceInfo; }

    private: // plugin

        static bool voice_info_get_callback(const clap_plugin_t *plugin, clap_voice_info_t *info);

        const clap_plugin_voice_info_t MPlugExtVoiceInfo
        {
            .get = voice_info_get_callback
        };        

    private: // host

        static void voice_info_changed_callback(const clap_host_t *host);

        clap_host_voice_info_t MHostExtVoiceInfo
        {
            .changed  = voice_info_changed_callback
        };

};

//----------------------------------------------------------------------
//
// plugin
//
//----------------------------------------------------------------------

bool SAT_ClapVoiceInfo::voice_info_get_callback(const clap_plugin_t *plugin, clap_voice_info_t *info)
{
    SAT_ClapPlugin* p = (SAT_ClapPlugin*)plugin->plugin_data;
    return p->voice_info_get(info);
}

//----------------------------------------------------------------------
//
// host
//
//----------------------------------------------------------------------

void SAT_ClapVoiceInfo::voice_info_changed_callback(const clap_host_t *host)
{
    SAT_ClapHost* h = (SAT_ClapHost*)host->host_data;
    h->voice_info_changed();
}
