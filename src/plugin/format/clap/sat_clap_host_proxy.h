#pragma once

#include "base/sat_base.h"
#include "plugin/format/clap/sat_clap.h"
#include "plugin/format/clap/extension/other/sat_clap_ext_reaper_extensions.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_ClapHostProxy
{
    public:
        SAT_ClapHostProxy(const clap_host_t* AHost);
        ~SAT_ClapHostProxy();
    public:
        void setupExtensions();
    public: // extensions
        const clap_host_ambisonic_t*            ambisonic           = nullptr;
        const clap_host_audio_ports_config_t*   audio_ports_config  = nullptr;
        const clap_host_audio_ports_t*          audio_ports         = nullptr;
        const clap_host_context_menu_t*         context_menu        = nullptr;
        const clap_host_event_registry_t*       event_registry      = nullptr;
        const clap_host_gui_t*                  gui                 = nullptr;
        const clap_host_latency_t*              latency             = nullptr;
        const clap_host_log_t*                  log                 = nullptr;
        const clap_host_note_name_t*            note_name           = nullptr;
        const clap_host_note_ports_t*           note_ports          = nullptr;
        const clap_host_params_t*               params              = nullptr;
        const clap_host_posix_fd_support_t*     posix_fd_support    = nullptr;
        const clap_host_preset_load_t*          preset_load         = nullptr;
        const clap_host_remote_controls_t*      remote_controls     = nullptr;
        const clap_host_state_t*                state               = nullptr;
        const clap_host_surround_t*             surround            = nullptr;
        const clap_host_tail_t*                 tail                = nullptr;
        const clap_host_thread_check_t*         thread_check        = nullptr;
        const clap_host_thread_pool_t*          thread_pool         = nullptr;
        const clap_host_timer_support_t*        timer_support       = nullptr;
        const clap_host_track_info_t*           track_info          = nullptr;
        const clap_host_voice_info_t*           voice_info          = nullptr;
        // draft
        const clap_host_mini_curve_display_t*   mini_curve_display  = nullptr;
        const clap_host_resource_directory_t*   resource_directory  = nullptr;
        const clap_host_scratch_memory_t*       scratch_memory      = nullptr;
        const clap_host_transport_control_t*    transport_control   = nullptr;
        const clap_host_triggers_t*             triggers            = nullptr;
        const clap_host_tuning_t*               tuning              = nullptr;
        const clap_host_undo_t*                 undo                = nullptr;
        // other
        const reaper_plugin_info_t*             reaper_extension    = nullptr;
    private:
        const clap_host_t*                      MClapHost           = nullptr;
};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

SAT_ClapHostProxy::SAT_ClapHostProxy(const clap_host_t* AHost)
{
    MClapHost = AHost;
    //setupExtensions();
}

SAT_ClapHostProxy::~SAT_ClapHostProxy()
{
}

//------------------------------
//
//------------------------------

void SAT_ClapHostProxy::setupExtensions()
{
    if (MClapHost)
    {
        ambisonic           = (const clap_host_ambisonic_t*)MClapHost->get_extension(MClapHost,CLAP_EXT_AMBISONIC);
        audio_ports         = (const clap_host_audio_ports_t*)MClapHost->get_extension(MClapHost,CLAP_EXT_AUDIO_PORTS);
        audio_ports_config  = (const clap_host_audio_ports_config_t*)MClapHost->get_extension(MClapHost,CLAP_EXT_AUDIO_PORTS_CONFIG);
        context_menu        = (const clap_host_context_menu_t*)MClapHost->get_extension(MClapHost,CLAP_EXT_CONTEXT_MENU);
        event_registry      = (const clap_host_event_registry_t*)MClapHost->get_extension(MClapHost,CLAP_EXT_EVENT_REGISTRY);
        gui                 = (const clap_host_gui_t*)MClapHost->get_extension(MClapHost,CLAP_EXT_GUI);
        latency             = (const clap_host_latency_t*)MClapHost->get_extension(MClapHost,CLAP_EXT_LATENCY);
        log                 = (const clap_host_log_t*)MClapHost->get_extension(MClapHost,CLAP_EXT_LOG);
        note_name           = (const clap_host_note_name_t*)MClapHost->get_extension(MClapHost,CLAP_EXT_NOTE_NAME);
        note_ports          = (const clap_host_note_ports_t*)MClapHost->get_extension(MClapHost,CLAP_EXT_NOTE_PORTS);
        params              = (const clap_host_params_t*)MClapHost->get_extension(MClapHost,CLAP_EXT_PARAMS);
        posix_fd_support    = (const clap_host_posix_fd_support_t*)MClapHost->get_extension(MClapHost,CLAP_EXT_POSIX_FD_SUPPORT);
        preset_load         = (const clap_host_preset_load_t*)MClapHost->get_extension(MClapHost,CLAP_EXT_PRESET_LOAD);
        remote_controls     = (const clap_host_remote_controls_t*)MClapHost->get_extension(MClapHost,CLAP_EXT_REMOTE_CONTROLS);
        state               = (const clap_host_state_t*)MClapHost->get_extension(MClapHost,CLAP_EXT_STATE);
        surround            = (const clap_host_surround_t*)MClapHost->get_extension(MClapHost,CLAP_EXT_SURROUND);
        tail                = (const clap_host_tail_t*)MClapHost->get_extension(MClapHost,CLAP_EXT_TAIL);
        thread_check        = (const clap_host_thread_check_t*)MClapHost->get_extension(MClapHost,CLAP_EXT_THREAD_CHECK);
        thread_pool         = (const clap_host_thread_pool_t*)MClapHost->get_extension(MClapHost,CLAP_EXT_THREAD_POOL);
        timer_support       = (const clap_host_timer_support_t*)MClapHost->get_extension(MClapHost,CLAP_EXT_TIMER_SUPPORT);
        track_info          = (const clap_host_track_info_t*)MClapHost->get_extension(MClapHost,CLAP_EXT_TRACK_INFO);
        voice_info          = (const clap_host_voice_info_t*)MClapHost->get_extension(MClapHost,CLAP_EXT_VOICE_INFO);
        // draft
        mini_curve_display  = (const clap_host_mini_curve_display_t*)MClapHost->get_extension(MClapHost,CLAP_EXT_MINI_CURVE_DISPLAY);
        resource_directory  = (const clap_host_resource_directory_t*)MClapHost->get_extension(MClapHost,CLAP_EXT_RESOURCE_DIRECTORY);
        scratch_memory      = (const clap_host_scratch_memory_t*)MClapHost->get_extension(MClapHost,CLAP_EXT_SCRATCH_MEMORY);
        transport_control   = (const clap_host_transport_control_t*)MClapHost->get_extension(MClapHost,CLAP_EXT_TRANSPORT_CONTROL);
        triggers            = (const clap_host_triggers_t*)MClapHost->get_extension(MClapHost,CLAP_EXT_TRIGGERS);
        tuning              = (const clap_host_tuning_t*)MClapHost->get_extension(MClapHost,CLAP_EXT_TUNING);
        undo                = (const clap_host_undo_t*)MClapHost->get_extension(MClapHost,CLAP_EXT_UNDO);
        // other
        reaper_extension    = (const reaper_plugin_info_t*)MClapHost->get_extension(MClapHost,"cockos.reaper_extension");

        // _COMPAT

        if (!ambisonic)         ambisonic       = (const clap_host_ambisonic_t*)MClapHost->get_extension(MClapHost,CLAP_EXT_AMBISONIC_COMPAT);
        if (!context_menu)      context_menu    = (const clap_host_context_menu_t*)MClapHost->get_extension(MClapHost,CLAP_EXT_CONTEXT_MENU_COMPAT);
        if (!preset_load)       preset_load     = (const clap_host_preset_load_t*)MClapHost->get_extension(MClapHost,CLAP_EXT_PRESET_LOAD_COMPAT);
        if (!remote_controls)   remote_controls = (const clap_host_remote_controls_t*)MClapHost->get_extension(MClapHost,CLAP_EXT_REMOTE_CONTROLS_COMPAT);
        if (!surround)          surround        = (const clap_host_surround_t*)MClapHost->get_extension(MClapHost,CLAP_EXT_SURROUND_COMPAT);
        if (!track_info)        track_info      = (const clap_host_track_info_t*)MClapHost->get_extension(MClapHost,CLAP_EXT_TRACK_INFO_COMPAT);
        // draft
    }
}
