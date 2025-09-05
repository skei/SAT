#pragma once

#include "base/sat_base.h"
#include "extern/plugin/sat_clap.h"
#include "plugin/format/clap/sat_clap_extension.h"

#ifdef SAT_INCLUDE_ARA_EXTENSIONS
    #include "extern/plugin/ara/arasdk/ARACLAP.h"
    using namespace ARA;
#endif

#ifdef SAT_INCLUDE_REAPER_EXTENSIONS
#endif

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_ClapPlugin
{
    public:

        SAT_ClapPlugin(const clap_plugin_descriptor_t* ADescriptor, const clap_host_t* AHost);
        virtual ~SAT_ClapPlugin();

    public: // plugin

        const clap_plugin_t*            getClapPlugin();
        const clap_plugin_descriptor_t* getClapDescriptor();
        const clap_host_t*              getClapHost();

    public: // plugin

        virtual bool                init() { return true; }
        virtual void                destroy() {}
        virtual bool                activate(double sample_rate, uint32_t min_frames_count, uint32_t max_frames_count) { return true; }
        virtual void                deactivate() {}
        virtual bool                start_processing() { return true; }
        virtual void                stop_processing() {}
        virtual void                reset() {}
        virtual clap_process_status process(const clap_process_t *process) { return CLAP_PROCESS_CONTINUE; }
        virtual const void*         get_extension(const char *id) { return nullptr; }
        virtual void                on_main_thread() {}

    public: // extensions

        virtual bool                ambisonic_is_config_supported(const clap_ambisonic_config_t *config) { return false; }
        virtual bool                ambisonic_get_config(bool is_input, uint32_t port_index, clap_ambisonic_config_t *config) { return false; }
        virtual uint32_t            audio_ports_count(bool is_input) { return 0; }
        virtual bool                audio_ports_get(uint32_t index, bool is_input, clap_audio_port_info_t *info) { return false; }
        virtual bool                audio_ports_activation_can_activate_while_processing() { return false; }
        virtual bool                audio_ports_activation_set_active(bool is_input, uint32_t port_index, bool is_active, uint32_t sample_size) { return false; }
        virtual uint32_t            audio_ports_config_count() { return 0; }
        virtual bool                audio_ports_config_get(uint32_t index, clap_audio_ports_config_t *config) { return true; }
        virtual bool                audio_ports_config_select(clap_id config_id) { return true;}
        virtual clap_id             audio_ports_config_info_current_config() { return 0; }
        virtual bool                audio_ports_config_info_get(clap_id config_id, uint32_t port_index, bool is_input, clap_audio_port_info_t* info) { return false; }
        virtual bool                configurable_audio_ports_can_apply_configuration(const struct clap_audio_port_configuration_request *requests, uint32_t request_count) { return false; }
        virtual bool                configurable_audio_ports_apply_configuration(const struct clap_audio_port_configuration_request *requests, uint32_t request_count) { return false; }
        virtual bool                context_menu_populate(const clap_context_menu_target_t  *target, const clap_context_menu_builder_t *builder) { return false; }
        virtual bool                context_menu_perform(const clap_context_menu_target_t *target, clap_id action_id) { return false; }
        virtual bool                gui_is_api_supported(const char *api, bool is_floating) { return false; }
        virtual bool                gui_get_preferred_api(const char **api, bool *is_floating) { return false; }
        virtual bool                gui_create(const char *api, bool is_floating) { return false; }
        virtual void                gui_destroy() {}
        virtual bool                gui_set_scale(double scale) { return false; }
        virtual bool                gui_get_size(uint32_t *width, uint32_t *height) { return false; }
        virtual bool                gui_can_resize() { return false; }
        virtual bool                gui_get_resize_hints(clap_gui_resize_hints_t *hints) { return false; }
        virtual bool                gui_adjust_size(uint32_t *width, uint32_t *height) { return false; }
        virtual bool                gui_set_size(uint32_t width, uint32_t height) { return false; }
        virtual bool                gui_set_parent(const clap_window_t *window) { return false; }
        virtual bool                gui_set_transient(const clap_window_t *window) { return false; }
        virtual void                gui_suggest_title(const char *title) {}
        virtual bool                gui_show() { return false; }
        virtual bool                gui_hide() { return false; }
        virtual uint32_t            latency_get() { return 0; }
        virtual uint32_t            note_name_count() { return 0; }
        virtual bool                note_name_get(uint32_t index, clap_note_name_t *note_name) { return false; }
        virtual uint32_t            note_ports_count(bool is_input) { return 0; }
        virtual bool                note_ports_get(uint32_t index, bool is_input, clap_note_port_info_t *info) { return false; }
        virtual void                param_indication_set_mapping(clap_id param_id, bool has_mapping, const clap_color_t *color, const char *label, const char *description) {}
        virtual void                param_indication_set_automation(clap_id param_id, uint32_t automation_state, const clap_color_t *color) {}
        virtual uint32_t            params_count() { return 0; }
        virtual bool                params_get_info(uint32_t param_index, clap_param_info_t *param_info) { return false; }
        virtual bool                params_get_value(clap_id param_id, double *out_value) { return false; }
        virtual bool                params_value_to_text(clap_id param_id, double value, char *out_buffer, uint32_t out_buffer_capacity) { return false; }
        virtual bool                params_text_to_value(clap_id param_id, const char *param_value_text, double *out_value) { return false; }
        virtual void                params_flush(const clap_input_events_t *in, const clap_output_events_t *out) {}
        virtual void                posix_fd_support_on_fd(int fd, clap_posix_fd_flags_t flags) {}
        virtual bool                preset_load_from_location(uint32_t location_kind, const char *location, const char *load_key) { return false; }
        virtual uint32_t            remote_controls_count() { return 0; }
        virtual bool                remote_controls_get(uint32_t page_index, clap_remote_controls_page_t *page) { return false; }
        virtual bool                render_has_hard_realtime_requirement() { return false; }
        virtual bool                render_set(clap_plugin_render_mode mode) { return false; }
        virtual bool                state_save(const clap_ostream_t *stream) { return false; }
        virtual bool                state_load(const clap_istream_t *stream) { return false; }
        virtual bool                state_context_save(const clap_ostream_t *stream, uint32_t context_type) { return false; }
        virtual bool                state_context_load(const clap_istream_t *stream, uint32_t context_type) { return false; }
        virtual bool                surround_is_channel_mask_supported(uint64_t channel_mask) { return false; }
        virtual uint32_t            surround_get_channel_map(bool is_input, uint32_t port_index, uint8_t *channel_map, uint32_t channel_map_capacity) { return 0; }
        virtual uint32_t            tail_get() { return 0; }
        virtual void                thread_pool_exec(uint32_t task_index) {}
        virtual void                timer_support_on_timer(clap_id timer_id) {}
        virtual void                track_info_changed() {}
        virtual bool                voice_info_get(clap_voice_info_t *info) { return false; }

    public: // draft extensions

        virtual bool                extensible_audio_ports_add_port(bool is_input, uint32_t channel_count, const char *port_type, const void *port_details) { return false; }
        virtual bool                extensible_audio_ports_remove_port(bool is_input, uint32_t index) { return false; }
        virtual double              gain_adjustment_metering_get() { return 0.0; }
        virtual uint32_t            mini_curve_display_get_curve_count() { return 0; }
        virtual uint32_t            mini_curve_display_render(clap_mini_curve_display_curve_data_t *curves, uint32_t curves_size) { return 0; }
        virtual void                mini_curve_display_set_observed(bool is_observed) {}
        virtual bool                mini_curve_display_get_axis_name(uint32_t curve_index, char *x_name, char *y_name, uint32_t name_capacity) { return false; }
        virtual void                project_location_set(const clap_project_location_element_t *path, uint32_t num_elements) {}
        virtual void                resource_directory_set_directory(const char *path, bool is_shared) {}
        virtual void                resource_directory_collect(bool all) {}
        virtual uint32_t            resource_directory_get_files_count() { return 0; }
        virtual int32_t             resource_directory_get_file_path(uint32_t index, char *path, uint32_t path_size) { return 0; }
        virtual uint32_t            triggers_count() { return 0; }
        virtual bool                triggers_get_info(uint32_t index, clap_trigger_info_t *trigger_info) { return false; }
        virtual void                tuning_changed() {}
        virtual void                undo_context_set_can_undo(bool can_undo) {}
        virtual void                undo_context_set_can_redo(bool can_redo) {}
        virtual void                undo_context_set_undo_name(const char *name) {}
        virtual void                undo_context_set_redo_name(const char *name) {}
        virtual void                undo_delta_get_delta_properties(clap_undo_delta_properties_t *properties) {}
        virtual bool                undo_delta_can_use_delta_format_version(clap_id format_version) { return false; }
        virtual bool                undo_delta_undo(clap_id format_version, const void *delta, size_t delta_size) { return false; }
        virtual bool                undo_delta_redo(clap_id format_version, const void *delta, size_t delta_size) { return false; }

    public: // other extensions

        #ifdef SAT_INCLUDE_ARA_EXTENSIONS
            virtual const ARAFactory*                   ara_get_factory() { return nullptr; }
            virtual const ARAPlugInExtensionInstance*   ara_bind_to_document_controller(ARADocumentControllerRef documentControllerRef, ARAPlugInInstanceRoleFlags knownRoles, ARAPlugInInstanceRoleFlags assignedRoles) { return nullptr; }
        #endif

    private:

        static bool                 init_callback(const struct clap_plugin *plugin);
        static void                 destroy_callback(const struct clap_plugin *plugin);
        static bool                 activate_callback(const struct clap_plugin *plugin, double sample_rate, uint32_t min_frames_count, uint32_t max_frames_count);
        static void                 deactivate_callback(const struct clap_plugin *plugin);
        static bool                 start_processing_callback(const struct clap_plugin *plugin);
        static void                 stop_processing_callback(const struct clap_plugin *plugin);
        static void                 reset_callback(const struct clap_plugin *plugin);
        static clap_process_status  process_callback(const struct clap_plugin *plugin, const clap_process_t *process);
        static const void*          get_extension_callback(const struct clap_plugin *plugin, const char *id);
        static void                 on_main_thread_callback(const struct clap_plugin *plugin);

    //protected:
    private:

        clap_plugin_t MClapPlugin
        {
            .desc               = nullptr,
            .plugin_data        = this,
            .init               = init_callback,
            .destroy            = destroy_callback,
            .activate           = activate_callback,
            .deactivate         = deactivate_callback,
            .start_processing   = start_processing_callback,
            .stop_processing    = stop_processing_callback,
            .reset              = reset_callback,
            .process            = process_callback,
            .get_extension      = get_extension_callback,
            .on_main_thread     = on_main_thread_callback
        };            

        const clap_plugin_descriptor_t* MClapDescriptor = nullptr;
        const clap_host_t*              MClapHost = nullptr;

};

//----------------------------------------------------------------------
//
// plugin
//
//----------------------------------------------------------------------

SAT_ClapPlugin::SAT_ClapPlugin(const clap_plugin_descriptor_t* ADescriptor, const clap_host_t* AHost)
{
    MClapPlugin.desc = ADescriptor;
    MClapDescriptor = ADescriptor;
    MClapHost = AHost;
}

SAT_ClapPlugin::~SAT_ClapPlugin()
{
}

//------------------------------
//
//------------------------------

const clap_plugin_t* SAT_ClapPlugin::getClapPlugin()
{
    return &MClapPlugin;
}

const clap_plugin_descriptor_t* SAT_ClapPlugin::getClapDescriptor()
{
    return MClapDescriptor;
}

const clap_host_t* SAT_ClapPlugin::getClapHost()
{
    return MClapHost;
}

//------------------------------
// clap callbacks
//------------------------------

bool SAT_ClapPlugin::init_callback(const struct clap_plugin *plugin)
{
    SAT_ClapPlugin* plug = (SAT_ClapPlugin*)plugin->plugin_data;
    return plug->init();
}

void SAT_ClapPlugin::destroy_callback(const struct clap_plugin *plugin)
{
    SAT_ClapPlugin* plug = (SAT_ClapPlugin*)plugin->plugin_data;
    plug->destroy();
    //delete this;
}

bool SAT_ClapPlugin::activate_callback(const struct clap_plugin *plugin, double sample_rate, uint32_t min_frames_count, uint32_t max_frames_count)
{
    SAT_ClapPlugin* plug = (SAT_ClapPlugin*)plugin->plugin_data;
    return plug->activate(sample_rate,min_frames_count,max_frames_count);
}

void SAT_ClapPlugin::deactivate_callback(const struct clap_plugin *plugin)
{
    SAT_ClapPlugin* plug = (SAT_ClapPlugin*)plugin->plugin_data;
    plug->deactivate();
}

bool SAT_ClapPlugin::start_processing_callback(const struct clap_plugin *plugin)
{
    SAT_ClapPlugin* plug = (SAT_ClapPlugin*)plugin->plugin_data;
    return plug->start_processing();
}

void SAT_ClapPlugin::stop_processing_callback(const struct clap_plugin *plugin)
{
    SAT_ClapPlugin* plug = (SAT_ClapPlugin*)plugin->plugin_data;
    plug->stop_processing();
}

void SAT_ClapPlugin::reset_callback(const struct clap_plugin *plugin)
{
    SAT_ClapPlugin* plug = (SAT_ClapPlugin*)plugin->plugin_data;
    plug->reset();
}

clap_process_status SAT_ClapPlugin::process_callback(const struct clap_plugin *plugin, const clap_process_t *process)
{
    SAT_ClapPlugin* plug = (SAT_ClapPlugin*)plugin->plugin_data;
    return plug->process(process);
}

const void* SAT_ClapPlugin::get_extension_callback(const struct clap_plugin *plugin, const char *id)
{
    SAT_ClapPlugin* plug = (SAT_ClapPlugin*)plugin->plugin_data;
    return plug->get_extension(id);
}

void SAT_ClapPlugin::on_main_thread_callback(const struct clap_plugin *plugin)
{
    SAT_ClapPlugin* plug = (SAT_ClapPlugin*)plugin->plugin_data;
    plug->on_main_thread();
}
