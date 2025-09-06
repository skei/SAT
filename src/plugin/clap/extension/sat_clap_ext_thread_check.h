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

class SAT_ClapThreadCheck
: public SAT_ClapExtension
{
    public:

        const char* getId() final       { return CLAP_EXT_THREAD_CHECK; }
        const void* getHostPtr() final  { return &MHostExtThreadCheck; }

    private: // host

        static bool thread_check_is_main_thread_callback(const clap_host_t *host);
        static bool thread_check_is_audio_thread_callback(const clap_host_t *host);

        clap_host_thread_check_t MHostExtThreadCheck
        {
            .is_main_thread   = thread_check_is_main_thread_callback,
            .is_audio_thread  = thread_check_is_audio_thread_callback
        };

};

//----------------------------------------------------------------------
//
// host
//
//----------------------------------------------------------------------

bool SAT_ClapThreadCheck::thread_check_is_main_thread_callback(const clap_host_t *host)
{
    SAT_ClapHost* h = (SAT_ClapHost*)host->host_data;
    return h->thread_check_is_main_thread();
}

bool SAT_ClapThreadCheck::thread_check_is_audio_thread_callback(const clap_host_t *host)
{
    SAT_ClapHost* h = (SAT_ClapHost*)host->host_data;
    return h->thread_check_is_audio_thread();
}
