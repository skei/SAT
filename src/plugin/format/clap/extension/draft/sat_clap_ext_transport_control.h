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

class SAT_ClapTransportControls
: public SAT_ClapExtension
{
    public:

        const char* getId() final       { return CLAP_EXT_TRANSPORT_CONTROL; }
        const void* getHostPtr() final  { return &MHostExtTransportControl; }

    private: // host

        static void transport_control_request_start_callback(const clap_host_t *host);
        static void transport_control_request_stop_callback(const clap_host_t *host);
        static void transport_control_request_continue_callback(const clap_host_t *host);
        static void transport_control_request_pause_callback(const clap_host_t *host);
        static void transport_control_request_toggle_play_callback(const clap_host_t *host);
        static void transport_control_request_jump_callback(const clap_host_t *host, clap_beattime position);
        static void transport_control_request_loop_region_callback(const clap_host_t *host, clap_beattime start, clap_beattime duration);
        static void transport_control_request_toggle_loop_callback(const clap_host_t *host);
        static void transport_control_request_enable_loop_callback(const clap_host_t *host, bool is_enabled);
        static void transport_control_request_record_callback(const clap_host_t *host, bool is_recording);
        static void transport_control_request_toggle_record_callback(const clap_host_t *host);

        clap_host_transport_control_t MHostExtTransportControl
        {
            .request_start          = transport_control_request_start_callback,
            .request_stop           = transport_control_request_stop_callback,
            .request_continue       = transport_control_request_continue_callback,
            .request_pause          = transport_control_request_pause_callback,
            .request_toggle_play    = transport_control_request_toggle_play_callback,
            .request_jump           = transport_control_request_jump_callback,
            .request_loop_region    = transport_control_request_loop_region_callback,
            .request_toggle_loop    = transport_control_request_toggle_loop_callback,
            .request_enable_loop    = transport_control_request_enable_loop_callback,
            .request_record         = transport_control_request_record_callback,
            .request_toggle_record  = transport_control_request_toggle_record_callback
        };

};

//----------------------------------------------------------------------
//
// host
//
//----------------------------------------------------------------------

void SAT_ClapTransportControls::transport_control_request_start_callback(const clap_host_t *host)
{
    SAT_ClapHost* h = (SAT_ClapHost*)host->host_data;
    h->transport_control_request_start();
}

void SAT_ClapTransportControls::transport_control_request_stop_callback(const clap_host_t *host)
{
    SAT_ClapHost* h = (SAT_ClapHost*)host->host_data;
    h->transport_control_request_stop();
}

void SAT_ClapTransportControls::transport_control_request_continue_callback(const clap_host_t *host)
{
    SAT_ClapHost* h = (SAT_ClapHost*)host->host_data;
    h->transport_control_request_continue();
}

void SAT_ClapTransportControls::transport_control_request_pause_callback(const clap_host_t *host)
{
    SAT_ClapHost* h = (SAT_ClapHost*)host->host_data;
    h->transport_control_request_pause();
}

void SAT_ClapTransportControls::transport_control_request_toggle_play_callback(const clap_host_t *host)
{
    SAT_ClapHost* h = (SAT_ClapHost*)host->host_data;
    h->transport_control_request_toggle_play();
}

void SAT_ClapTransportControls::transport_control_request_jump_callback(const clap_host_t *host, clap_beattime position)
{
    SAT_ClapHost* h = (SAT_ClapHost*)host->host_data;
    h->transport_control_request_jump(position);
}

void SAT_ClapTransportControls::transport_control_request_loop_region_callback(const clap_host_t *host, clap_beattime start, clap_beattime duration)
{
    SAT_ClapHost* h = (SAT_ClapHost*)host->host_data;
    h->transport_control_request_loop_region(start,duration);
}

void SAT_ClapTransportControls::transport_control_request_toggle_loop_callback(const clap_host_t *host)
{
    SAT_ClapHost* h = (SAT_ClapHost*)host->host_data;
    h->transport_control_request_toggle_loop();
}

void SAT_ClapTransportControls::transport_control_request_enable_loop_callback(const clap_host_t *host, bool is_enabled)
{
    SAT_ClapHost* h = (SAT_ClapHost*)host->host_data;
    h->transport_control_request_enable_loop(is_enabled);
}

void SAT_ClapTransportControls::transport_control_request_record_callback(const clap_host_t *host, bool is_recording)
{
    SAT_ClapHost* h = (SAT_ClapHost*)host->host_data;
    h->transport_control_request_record(is_recording);
}

void SAT_ClapTransportControls::transport_control_request_toggle_record_callback(const clap_host_t *host)
{
    SAT_ClapHost* h = (SAT_ClapHost*)host->host_data;
    h->transport_control_request_toggle_record();
}
