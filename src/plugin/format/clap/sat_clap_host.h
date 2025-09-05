#pragma once

#include "base/sat_base.h"
#include "extern/plugin/sat_clap.h"
#include "plugin/format/clap/sat_clap_extension.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_ClapHost
{
    public:

        SAT_ClapHost();
        virtual ~SAT_ClapHost();

    public: // plugin

        const clap_host_t* getClapHost();

    public: // host

        virtual const void* get_extension(const char *extension_id) { return nullptr; }
        virtual void        request_restart() {}
        virtual void        request_process() {}
        virtual void        request_callback() {}

    public: // extensions

        virtual void        ambisonic_changed() {}
        virtual bool        audio_ports_is_rescan_flag_supported(uint32_t flag) { return false; }
        virtual void        audio_ports_rescan(uint32_t flags) {}
        virtual void        audio_ports_config_rescan() {}
        virtual bool        context_menu_populate(const clap_context_menu_target_t *target, const clap_context_menu_builder_t *builder) { return false; }
        virtual bool        context_menu_perform(const clap_context_menu_target_t *target, clap_id action_id) { return false; }
        virtual bool        context_menu_can_popup() { return false; }
        virtual bool        context_menu_popup(const clap_context_menu_target_t *target, int32_t screen_index, int32_t x, int32_t y) { return false; }
        virtual bool        event_registry_query(const char *space_name, uint16_t *space_id) { return false; }
        virtual void        gui_resize_hints_changed() {}
        virtual bool        gui_request_resize(uint32_t width, uint32_t height) { return false; }
        virtual bool        gui_request_show() { return false; }
        virtual bool        gui_request_hide() { return false; }
        virtual void        gui_closed(bool was_destroyed) {}
        virtual void        latency_changed() {}
        virtual void        log_log(clap_log_severity severity, const char *msg) {}
        virtual void        note_name_changed() {}
        virtual uint32_t    note_ports_supported_dialects() { return 0; }
        virtual void        note_ports_rescan(uint32_t flags) {}
        virtual void        params_rescan(clap_param_rescan_flags flags) {}
        virtual void        params_clear(clap_id param_id, clap_param_clear_flags flags) {}
        virtual void        params_request_flush() {}
        virtual bool        posix_fd_support_register_fd(int fd, clap_posix_fd_flags_t flags) { return false; }
        virtual bool        posix_fd_support_modify_fd(int fd, clap_posix_fd_flags_t flags) { return false; }
        virtual bool        posix_fd_support_unregister_fd(int fd) { return false; }
        virtual void        preset_load_on_error(uint32_t location_kind, const char *location, const char *load_key,int32_t os_error, const char *msg) {}
        virtual void        preset_load_loaded(uint32_t location_kind, const char *location, const char *load_key) {}
        virtual void        remote_controls_changed() {}
        virtual void        remote_controls_suggest_page(clap_id page_id) {}
        virtual void        state_mark_dirty() {}
        virtual void        surround_changed() {}
        virtual void        tail_changed() {}
        virtual bool        thread_check_is_main_thread() { return false; }
        virtual bool        thread_check_is_audio_thread() { return false; }
        virtual bool        thread_pool_request_exec(uint32_t num_tasks) { return false; }
        virtual bool        timer_support_register_timer(uint32_t period_ms, clap_id *timer_id) { return false; }
        virtual bool        timer_support_unregister_timer(clap_id timer_id) { return false; }
        virtual bool        track_info_get(clap_track_info_t *info) { return false; }
        virtual void        voice_info_changed() {}

    public: // draft extensions

        virtual bool        resource_directory_request_directory(bool is_shared) { return false; }
        virtual void        resource_directory_release_directory(bool is_shared) {}
        virtual bool        scratch_memory_reserve(uint32_t scratch_size_bytes, uint32_t max_concurrency_hint) { return false; }
        virtual void*       scratch_memory_access() { return nullptr; }
        virtual void        transport_control_request_start() {}
        virtual void        transport_control_request_stop() {}
        virtual void        transport_control_request_continue() {}
        virtual void        transport_control_request_pause() {}
        virtual void        transport_control_request_toggle_play() {}
        virtual void        transport_control_request_jump(clap_beattime position) {}
        virtual void        transport_control_request_loop_region(clap_beattime start, clap_beattime duration) {}
        virtual void        transport_control_request_toggle_loop() {}
        virtual void        transport_control_request_enable_loop(bool is_enabled) {}
        virtual void        transport_control_request_record(bool is_recording) {}
        virtual void        transport_control_request_toggle_record() {}
        virtual void        triggers_rescan(clap_trigger_rescan_flags flags) {}
        virtual void        triggers_clear(clap_id trigger_id, clap_trigger_clear_flags flags) {}
        virtual double      tuning_get_relative(clap_id tuning_id, int32_t channel, int32_t key, uint32_t sample_offset) { return 0.0; }
        virtual bool        tuning_should_play(clap_id tuning_id, int32_t channel, int32_t key) { return false; }
        virtual uint32_t    tuning_get_tuning_count() { return 0; }
        virtual bool        tuning_get_info(uint32_t tuning_index, clap_tuning_info_t *info) { return false; }
        virtual void        undo_begin_change() {}
        virtual void        undo_cancel_change() {}
        virtual void        undo_change_made(const char* name, const void* delta, size_t delta_size, bool delta_can_undo) {}
        virtual void        undo_request_undo() {}
        virtual void        undo_request_redo() {}
        virtual void        undo_set_wants_context_updates(bool is_subscribed) {}


    protected:

        clap_host_t MClapHost
        {
            .clap_version       = CLAP_VERSION,
            .host_data          = this,
            .name               = "",
            .vendor             = "",
            .url                = "",
            .version            = "",
            .get_extension      = get_extension_callback,
            .request_restart    = request_restart_callback,
            .request_process    = request_process_callback,
            .request_callback   = request_callback_callback
        };            

    private:

        static const void*  get_extension_callback(const struct clap_host *host, const char *extension_id);
        static void         request_restart_callback(const struct clap_host *host);
        static void         request_process_callback(const struct clap_host *host);
        static void         request_callback_callback(const struct clap_host *host);

};

//----------------------------------------------------------------------
//
// host
//
//----------------------------------------------------------------------

SAT_ClapHost::SAT_ClapHost()
{
}

SAT_ClapHost::~SAT_ClapHost()
{
}

//------------------------------
//
//------------------------------

const clap_host_t* SAT_ClapHost::getClapHost()
{
    return &MClapHost;
}

//------------------------------
// clap callbacks
//------------------------------


const void* SAT_ClapHost::get_extension_callback(const struct clap_host *host, const char *extension_id)
{
    SAT_ClapHost* h = (SAT_ClapHost*)host->host_data;
    return h->get_extension(extension_id);
}

void SAT_ClapHost::request_restart_callback(const struct clap_host *host)
{
    SAT_ClapHost* h = (SAT_ClapHost*)host->host_data;
    return h->request_restart();
}

void SAT_ClapHost::request_process_callback(const struct clap_host *host)
{
    SAT_ClapHost* h = (SAT_ClapHost*)host->host_data;
    return h->request_process();
}

void SAT_ClapHost::request_callback_callback(const struct clap_host *host)
{
    SAT_ClapHost* h = (SAT_ClapHost*)host->host_data;
    return h->request_callback();
}


