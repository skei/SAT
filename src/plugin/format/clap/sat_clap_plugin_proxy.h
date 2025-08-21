#pragma once

#include "base/sat_base.h"
#include "plugin/format/clap/sat_clap.h"

#include "extern/plugin/ara/arasdk/ARACLAP.h"
//using namespace ARA;


//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_ClapPluginProxy
{
    public:
        SAT_ClapPluginProxy(const clap_plugin_t* APlugin);
        ~SAT_ClapPluginProxy();
    public:
        void setupExtensions();
    public: // extensions
        const clap_plugin_ambisonic_t*                  ambisonic                   = nullptr;
        const clap_plugin_audio_ports_t*                audio_ports                 = nullptr;
        const clap_plugin_audio_ports_activation_t*     audio_ports_activation      = nullptr;
        const clap_plugin_audio_ports_config_t*         audio_ports_config          = nullptr;
        const clap_plugin_audio_ports_config_info_t*    audio_ports_config_info     = nullptr;
        const clap_plugin_configurable_audio_ports_t*   configurable_audio_ports    = nullptr;
        const clap_plugin_context_menu_t*               context_menu                = nullptr;
        const clap_plugin_gui_t*                        gui                         = nullptr;
        const clap_plugin_latency_t*                    latency                     = nullptr;
        const clap_plugin_note_name_t*                  note_name                   = nullptr;
        const clap_plugin_note_ports_t*                 note_ports                  = nullptr;
        const clap_plugin_param_indication_t*           param_indication            = nullptr;
        const clap_plugin_params_t*                     params                      = nullptr;
        const clap_plugin_posix_fd_support_t*           posix_fd_support            = nullptr;
        const clap_plugin_preset_load_t*                preset_load                 = nullptr;
        const clap_plugin_remote_controls_t*            remote_controls             = nullptr;
        const clap_plugin_render_t*                     render                      = nullptr;
        const clap_plugin_state_t*                      state                       = nullptr;
        const clap_plugin_state_context_t*              state_context               = nullptr;
        const clap_plugin_surround_t*                   surround                    = nullptr;
        const clap_plugin_tail_t*                       tail                        = nullptr;
        const clap_plugin_thread_pool_t*                thread_pool                 = nullptr;
        const clap_plugin_timer_support_t*              timer_support               = nullptr;
        const clap_plugin_track_info_t*                 track_info                  = nullptr;
        const clap_plugin_voice_info_t*                 voice_info                  = nullptr;
        // draft
        const clap_plugin_extensible_audio_ports_t*     extensible_audio_ports      = nullptr;
        const clap_plugin_gain_adjustment_metering_t*   gain_adjustment_metering    = nullptr;
        const clap_plugin_mini_curve_display_t*         mini_curve_display          = nullptr;
        const clap_plugin_project_location_t*           project_location            = nullptr;
        const clap_plugin_resource_directory_t*         resource_directory          = nullptr;
        const clap_plugin_triggers_t*                   triggers                    = nullptr;
        const clap_plugin_tuning_t*                     tuning                      = nullptr;
        const clap_plugin_undo_context_t*               undo_context                = nullptr;
        const clap_plugin_undo_delta_t*                 undo_delta                  = nullptr;
        // other
        const clap_ara_plugin_extension_t*              ara_plugin_extension        = nullptr;
    private:
        const clap_host_t*                              MClapHost                   = nullptr;

    private:
        const clap_plugin_t* MClapPlugin = nullptr;
};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

SAT_ClapPluginProxy::SAT_ClapPluginProxy(const clap_plugin_t* APlugin)
{
    MClapPlugin = APlugin;
}

SAT_ClapPluginProxy::~SAT_ClapPluginProxy()
{
}

//------------------------------
//
//------------------------------

void SAT_ClapPluginProxy::setupExtensions()
{
}
