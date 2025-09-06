#pragma once

#include "base/sat_base.h"
#include "base/util/sat_strutils.h"
#include "extern/plugin/sat_clap.h"
#include "plugin/clap/sat_clap_extensions.h"
#include "plugin/clap/sat_clap_plugin.h"
#include "plugin/editor/sat_editor_listener.h"
#include "plugin/editor/sat_editor_owner.h"
#include "plugin/processor/sat_process_context.h"
#include "plugin/processor/sat_processor_listener.h"
#include "plugin/processor/sat_processor_owner.h"
#include "plugin/sat_audio_ports.h"
#include "plugin/sat_editor.h"
#include "plugin/sat_extensions.h"
#include "plugin/sat_host_proxy.h"
#include "plugin/sat_note_ports.h"
#include "plugin/sat_parameters.h"
#include "plugin/sat_processor.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_Plugin
: public SAT_ClapPlugin
, public SAT_EditorOwner
, public SAT_EditorListener
, public SAT_ProcessorOwner
, public SAT_ProcessorListener
{
    public:

        SAT_Plugin(const clap_plugin_descriptor_t* ADescriptor, const clap_host_t* AHost);
        virtual ~SAT_Plugin();

    public: // clap plugin

        bool                init() override;
        void                destroy() override;
        bool                activate(double sample_rate, uint32_t min_frames_count, uint32_t max_frames_count) override;
        void                deactivate() override;
        bool                start_processing() override;
        void                stop_processing() override;
        void                reset() override;
        clap_process_status process(const clap_process_t *process) override;
        const void*         get_extension(const char *id) override;
        void                on_main_thread() override;

    public: // clap plugin extensions

        // bool                ambisonic_is_config_supported(const clap_ambisonic_config_t *config) override;
        // bool                ambisonic_get_config(bool is_input, uint32_t port_index, clap_ambisonic_config_t *config) override;
        // uint32_t            audio_ports_count(bool is_input) override;
        // bool                audio_ports_get(uint32_t index, bool is_input, clap_audio_port_info_t *info) override;
        // bool                audio_ports_activation_can_activate_while_processing() override;
        // bool                audio_ports_activation_set_active(bool is_input, uint32_t port_index, bool is_active, uint32_t sample_size) override;
        // uint32_t            audio_ports_config_count() override;
        // bool                audio_ports_config_get(uint32_t index, clap_audio_ports_config_t *config) override;
        // bool                audio_ports_config_select(clap_id config_id) override;
        // clap_id             audio_ports_config_info_current_config() override;
        // bool                audio_ports_config_info_get(clap_id config_id, uint32_t port_index, bool is_input, clap_audio_port_info_t* info) override;
        // bool                configurable_audio_ports_can_apply_configuration(const struct clap_audio_port_configuration_request *requests, uint32_t request_count) override;
        // bool                configurable_audio_ports_apply_configuration(const struct clap_audio_port_configuration_request *requests, uint32_t request_count) override;
        // bool                context_menu_populate(const clap_context_menu_target_t  *target, const clap_context_menu_builder_t *builder) override;
        // bool                context_menu_perform(const clap_context_menu_target_t *target, clap_id action_id) override;

        bool                gui_is_api_supported(const char *api, bool is_floating) override;
        bool                gui_get_preferred_api(const char **api, bool *is_floating) override;
        bool                gui_create(const char *api, bool is_floating) override;
        void                gui_destroy() override;
        bool                gui_set_scale(double scale) override;
        bool                gui_get_size(uint32_t *width, uint32_t *height) override;
        bool                gui_can_resize() override;
        bool                gui_get_resize_hints(clap_gui_resize_hints_t *hints) override;
        bool                gui_adjust_size(uint32_t *width, uint32_t *height) override;
        bool                gui_set_size(uint32_t width, uint32_t height) override;
        bool                gui_set_parent(const clap_window_t *window) override;
        bool                gui_set_transient(const clap_window_t *window) override;
        void                gui_suggest_title(const char *title) override;
        bool                gui_show() override;
        bool                gui_hide() override;

        // uint32_t            latency_get() override;
        // uint32_t            note_name_count() override;
        // bool                note_name_get(uint32_t index, clap_note_name_t *note_name) override;
        // uint32_t            note_ports_count(bool is_input) override;
        // bool                note_ports_get(uint32_t index, bool is_input, clap_note_port_info_t *info) override;
        // void                param_indication_set_mapping(clap_id param_id, bool has_mapping, const clap_color_t *color, const char *label, const char *description) override;
        // void                param_indication_set_automation(clap_id param_id, uint32_t automation_state, const clap_color_t *color) override;
        // uint32_t            params_count() override;
        // bool                params_get_info(uint32_t param_index, clap_param_info_t *param_info) override;
        // bool                params_get_value(clap_id param_id, double *out_value) override;
        // bool                params_value_to_text(clap_id param_id, double value, char *out_buffer, uint32_t out_buffer_capacity) override;
        // bool                params_text_to_value(clap_id param_id, const char *param_value_text, double *out_value) override;
        // void                params_flush(const clap_input_events_t *in, const clap_output_events_t *out) override;
        // void                posix_fd_support_on_fd(int fd, clap_posix_fd_flags_t flags) override;
        // bool                preset_load_from_location(uint32_t location_kind, const char *location, const char *load_key) override;
        // uint32_t            remote_controls_count() override;
        // bool                remote_controls_get(uint32_t page_index, clap_remote_controls_page_t *page) override;
        // bool                render_has_hard_realtime_requirement() override;
        // bool                render_set(clap_plugin_render_mode mode) override;
        // bool                state_save(const clap_ostream_t *stream) override;
        // bool                state_load(const clap_istream_t *stream) override;
        // bool                state_context_save(const clap_ostream_t *stream, uint32_t context_type) override;
        // bool                state_context_load(const clap_istream_t *stream, uint32_t context_type) override;
        // bool                surround_is_channel_mask_supported(uint64_t channel_mask) override;
        // uint32_t            surround_get_channel_map(bool is_input, uint32_t port_index, uint8_t *channel_map, uint32_t channel_map_capacity) override;
        // uint32_t            tail_get() override;
        // void                thread_pool_exec(uint32_t task_index) override;
        // void                timer_support_on_timer(clap_id timer_id) override;
        // void                track_info_changed() override;
        // bool                voice_info_get(clap_voice_info_t *info) override;

    public: // draft extensions

        // bool                extensible_audio_ports_add_port(bool is_input, uint32_t channel_count, const char *port_type, const void *port_details) override;
        // bool                extensible_audio_ports_remove_port(bool is_input, uint32_t index) override;
        // double              gain_adjustment_metering_get()  override;
        // uint32_t            mini_curve_display_get_curve_count() override;
        // uint32_t            mini_curve_display_render(clap_mini_curve_display_curve_data_t *curves, uint32_t curves_size) override;
        // void                mini_curve_display_set_observed(bool is_observed) override;
        // bool                mini_curve_display_get_axis_name(uint32_t curve_index, char *x_name, char *y_name, uint32_t name_capacity) override;
        // void                project_location_set(const clap_project_location_element_t *path, uint32_t num_elements) override;
        // void                resource_directory_set_directory(const char *path, bool is_shared) override;
        // void                resource_directory_collect(bool all) override;
        // uint32_t            resource_directory_get_files_count() override;
        // int32_t             resource_directory_get_file_path(uint32_t index, char *path, uint32_t path_size) override;
        // uint32_t            triggers_count() override;
        // bool                triggers_get_info(uint32_t index, clap_trigger_info_t *trigger_info) override;
        // void                tuning_changed() override;
        // void                undo_context_set_can_undo(bool can_undo) override;
        // void                undo_context_set_can_redo(bool can_redo) override;
        // void                undo_context_set_undo_name(const char *name) override;
        // void                undo_context_set_redo_name(const char *name) override;
        // void                undo_delta_get_delta_properties(clap_undo_delta_properties_t *properties) override;
        // bool                undo_delta_can_use_delta_format_version(clap_id format_version) override;
        // bool                undo_delta_undo(clap_id format_version, const void *delta, size_t delta_size) override;
        // bool                undo_delta_redo(clap_id format_version, const void *delta, size_t delta_size) override;

    public: // other extensions

        // #ifdef SAT_INCLUDE_ARA_EXTENSIONS
        //     const ARAFactory*                   ara_get_factory() override;
        //     const ARAPlugInExtensionInstance*   ara_bind_to_document_controller(ARADocumentControllerRef documentControllerRef, ARAPlugInInstanceRoleFlags knownRoles, ARAPlugInInstanceRoleFlags assignedRoles) override;
        // #endif


    public: // processor

        void                setProcessor(SAT_Processor* AProcessor);

        void                do_processor_listener_update_parameter(uint32_t AId, sat_param_t AValue) override;

        // uint32_t            do_processor_owner_getMinBlockSize() override;
        // uint32_t            do_processor_owner_getMaxBlockSize() override;
        // double              do_processor_owner_getSampleRate() override;

    public: // editor

        void                setInitialEditorSize(uint32_t AWidth, uint32_t AHeight, double AScale, bool AProportional);

        void                do_editor_listener_update_parameter(SAT_Parameter* AParameter, sat_param_t AValue) override;

        // uint32_t            do_editor_owner_get_initial_width() override;
        // uint32_t            do_editor_owner_get_initial_height() override;
        // double              do_editor_owner_get_initial_scale() override;
        // bool                do_editor_owner_get_is_proportional() override;

    public:

        SAT_Extensions      Extensions              = {};
        SAT_Parameters      Parameters              = {};
        SAT_AudioPorts      AudioPorts              = {};
        SAT_NotePorts       NotePorts               = {};

    protected: // editor

        // uint32_t            MEditorInitialWidth     = 0;
        // uint32_t            MEditorInitialHeight    = 0;
        // double              MEditorInitialScale     = 1.0;
        // bool                MEditorIsProportional   = true;

    private:

        SAT_HostProxy*      MHost                   = nullptr;
        SAT_Editor*         MEditor                 = {};
        SAT_Processor*      MProcessor              = {};
        SAT_ProcessContext  MProcessContext         = {};

     // uint32_t            MState                  = SAT_PLUGIN_STATE_NONE;
        bool                MIsInitialized          = false;
        bool                MIsActivated            = false;
        bool                MIsProcessing           = false;
        


};

//----------------------------------------------------------------------
//
// implementation
//
//----------------------------------------------------------------------

SAT_Plugin::SAT_Plugin(const clap_plugin_descriptor_t* ADescriptor, const clap_host_t* AHost)
: SAT_ClapPlugin(ADescriptor,AHost)
{
    MHost = new SAT_HostProxy(AHost);
    SAT_Assert(MHost);
    MEditor = new SAT_Editor(this,this);
    SAT_Assert(MEditor);
}

SAT_Plugin::~SAT_Plugin()
{
    #ifndef SAT_NO_AUTODELETE
        Extensions.deleteAll();
        Parameters.deleteAll();
        AudioPorts.deleteAll();
        NotePorts.deleteAll();
    #endif
    if (MEditor) delete MEditor;
    if (MHost) delete MHost;
}

//------------------------------
// clap plugin
//------------------------------

/*
    Must be called after creating the plugin.
    If init returns false, the host must destroy the plugin instance.
    If init returns true, then the plugin is initialized and in the deactivated state.
    Unlike in `plugin-factory::create_plugin`, in init you have complete access to the host 
    and host extensions, so clap related setup activities should be done here rather than in
    create_plugin.
    [main-thread]
*/

bool SAT_Plugin::init()
{
    SAT_Assert(!MIsInitialized);
    MIsInitialized = true;
    return true;
}

/*
    Free the plugin and its resources.
    It is required to deactivate the plugin prior to this call.
    [main-thread & !active]  
*/

void SAT_Plugin::destroy()
{
    SAT_Assert(!MIsInitialized);
    SAT_Assert(!MIsActivated);
    MIsActivated = false;
    // delete this;
}

/*
    Activate and deactivate the plugin.
    In this call the plugin may allocate memory and prepare everything needed for the process
    call. The process's sample rate will be constant and process's frame count will included in
    the [min, max] range, which is bounded by [1, INT32_MAX].
    In this call the plugin may call host-provided methods marked [being-activated].
    Once activated the latency and port configuration must remain constant, until deactivation.
    Returns true on success.
    [main-thread & !active]  
*/


bool SAT_Plugin::activate(double sample_rate, uint32_t min_frames_count, uint32_t max_frames_count)
{
    SAT_Assert(MIsInitialized);
    SAT_Assert(!MIsActivated);
    MProcessContext.sample_rate = sample_rate;
    // MProcessContext.min_frames_count = min_frames_count;
    // MProcessContext.max_frames_count = max_frames_count;
    MIsActivated = true;
    return true;
}
  
/*
    [main-thread & active] 
*/

void SAT_Plugin::deactivate()
{
    SAT_Assert(MIsActivated);
    MIsActivated = false;
}

/*
    Call start processing before processing.
    Returns true on success.
    [audio-thread & active & !processing]
*/

bool SAT_Plugin::start_processing()
{
    SAT_Assert(MIsActivated);
    SAT_Assert(!MIsProcessing);
    MIsProcessing = true;
    return true;
}

/*
    Call stop processing before sending the plugin to sleep.
    [audio-thread & active & processing]
*/

void SAT_Plugin::stop_processing()
{
    SAT_Assert(MIsActivated);
    SAT_Assert(MIsProcessing);
    MIsProcessing = false;
}

/*
    - Clears all buffers, performs a full reset of the processing state (filters, oscillators,
        envelopes, lfo, ...) and kills all voices.
    - The parameter's value remain unchanged.
    - clap_process.steady_time may jump backward.
    
    [audio-thread & active]  
*/

void SAT_Plugin::reset()
{
    SAT_Assert(MIsActivated);
}

/*
    process audio, events, ...
    All the pointers coming from clap_process_t and its nested attributes,
    are valid until process() returns.
    [audio-thread & active & processing]
*/

clap_process_status SAT_Plugin::process(const clap_process_t *process)
{
    SAT_Assert(MIsActivated);
    SAT_Assert(MIsProcessing);
    return CLAP_PROCESS_CONTINUE;
}

/*
    Query an extension.
    The returned pointer is owned by the plugin.
    It is forbidden to call it before plugin->init().
    You can call it within plugin->init() call, and after.
    [thread-safe] 
*/

const void* SAT_Plugin::get_extension(const char *id)
{
    SAT_Assert(MIsInitialized);
    return Extensions.find(id);
}

/*
    Called by the host on the main thread in response to a previous call to:
        host->request_callback(host);
    [main-thread]
*/

void SAT_Plugin::on_main_thread()
{
    // SAT_Assert(MIsInitialized);
    // SAT_Assert(MIsActivated);
    // SAT_Assert(MIsProcessing);
    SAT_Assert(MState == SAT_PLUGIN_STATE_PROCESSING);
}

//------------------------------
// extensions
//------------------------------





// bool SAT_Plugin::ambisonic_is_config_supported(const clap_ambisonic_config_t *config)
// bool SAT_Plugin::ambisonic_get_config(bool is_input, uint32_t port_index, clap_ambisonic_config_t *config)

// uint32_t SAT_Plugin::audio_ports_count(bool is_input)
// bool SAT_Plugin::audio_ports_get(uint32_t index, bool is_input, clap_audio_port_info_t *info)

// bool SAT_Plugin::audio_ports_activation_can_activate_while_processing()
// bool SAT_Plugin::audio_ports_activation_set_active(bool is_input, uint32_t port_index, bool is_active, uint32_t sample_size)

// uint32_t SAT_Plugin::audio_ports_config_count()
// bool SAT_Plugin::audio_ports_config_get(uint32_t index, clap_audio_ports_config_t *config)
// bool SAT_Plugin::audio_ports_config_select(clap_id config_id)

// clap_id  SAT_Plugin::audio_ports_config_info_current_config()
// bool SAT_Plugin::audio_ports_config_info_get(clap_id config_id, uint32_t port_index, bool is_input, clap_audio_port_info_t* info)

// bool SAT_Plugin::configurable_audio_ports_can_apply_configuration(const struct clap_audio_port_configuration_request *requests, uint32_t request_count)
// bool SAT_Plugin::configurable_audio_ports_apply_configuration(const struct clap_audio_port_configuration_request *requests, uint32_t request_count)

// bool SAT_Plugin::context_menu_populate(const clap_context_menu_target_t  *target, const clap_context_menu_builder_t *builder)
// bool SAT_Plugin::context_menu_perform(const clap_context_menu_target_t *target, clap_id action_id)

// ----- gui -----

bool SAT_Plugin::gui_is_api_supported(const char *api, bool is_floating)
{
    SAT_Assert(MEditor);
    if (is_floating) return false;
    #if defined SAT_LINUX
        return SAT_IsEqual(api,CLAP_WINDOW_API_X11);
    #elif defined SAT_WIN32
        return SAT_IsEqual(api,CLAP_WINDOW_API_WIN32);
    #else
        #error NOT IMPLEMENTED YET
    #endif
    return false;
}

bool SAT_Plugin::gui_get_preferred_api(const char **api, bool *is_floating)
{
    SAT_Assert(MEditor);
    #if defined SAT_LINUX
        *api = CLAP_WINDOW_API_X11;
    #elif defined SAT_WIN32
        *api = CLAP_WINDOW_API_WIN32;
    #else
        #error NOT IMPLEMENTED YET
    #endif
    *is_floating = false;
    return true;
}

bool SAT_Plugin::gui_create(const char *api, bool is_floating)
{
    SAT_Assert(MEditor);
    if (is_floating) return false;
    #if defined SAT_LINUX
        if (!SAT_IsEqual(api,CLAP_WINDOW_API_X11)) return false;
    #elif defined SAT_WIN32
        if (!SAT_IsEqual(api,CLAP_WINDOW_API_WIN32)) return false;
    #else
        #error NOT IMPLEMENTED YET
    #endif
    MEditor->create();
    return true;
}

void SAT_Plugin::gui_destroy()
{
    SAT_Assert(MEditor);
    MEditor->destroy();
    // delete MEditor;
}

bool SAT_Plugin::gui_set_scale(double scale)
{
    SAT_Assert(MEditor);
    return MEditor->set_scale(scale);
}

bool SAT_Plugin::gui_get_size(uint32_t *width, uint32_t *height)
{
    SAT_Assert(MEditor);
    return MEditor->get_size(width,height);
}

bool SAT_Plugin::gui_can_resize()
{
    SAT_Assert(MEditor);
    return MEditor->can_resize();
}

bool SAT_Plugin::gui_get_resize_hints(clap_gui_resize_hints_t *hints)
{
    SAT_Assert(MEditor);
    return MEditor->get_resize_hints(hints);
}

bool SAT_Plugin::gui_adjust_size(uint32_t *width, uint32_t *height)
{
    SAT_Assert(MEditor);
    return MEditor->adjust_size(width,height);
}

bool SAT_Plugin::gui_set_size(uint32_t width, uint32_t height)
{
    SAT_Assert(MEditor);
    return MEditor->set_size(width,height);
}

bool SAT_Plugin::gui_set_parent(const clap_window_t *window)
{
    SAT_Assert(MEditor);
    #if defined SAT_LINUX
        SAT_Assert(SAT_IsEqual(window->api,CLAP_WINDOW_API_X11));
        return MEditor->set_parent(window->x11);
    #elif defined SAT_WIN32
        SAT_Assert(SAT_IsEqual(window->api,CLAP_WINDOW_API_WIN32));
        return MEditor->set_parent(window->win32);
    #else
        #error NOT IMPLEMENTED YET
    #endif
}

bool SAT_Plugin::gui_set_transient(const clap_window_t *window)
{
    SAT_Assert(MEditor);
    #if defined SAT_LINUX
        SAT_Assert(SAT_IsEqual(window->api,CLAP_WINDOW_API_X11));
        return MEditor->set_parent(window->x11);
    #elif defined SAT_WIN32
        SAT_Assert(SAT_IsEqual(window->api,CLAP_WINDOW_API_WIN32));
        return MEditor->set_parent(window->win32);
    #else
        #error NOT IMPLEMENTED YET
    #endif
}

void SAT_Plugin::gui_suggest_title(const char *title)
{
    SAT_Assert(MEditor);
    MEditor->suggest_title(title);
}

bool SAT_Plugin::gui_show()
{
    SAT_Assert(MEditor);
    return MEditor->show();
}

bool SAT_Plugin::gui_hide()
{
    SAT_Assert(MEditor);
    return MEditor->hide();
}

// ----- -----

// uint32_t SAT_Plugin::latency_get()

// uint32_t SAT_Plugin::note_name_count()
// bool SAT_Plugin::note_name_get(uint32_t index, clap_note_name_t *note_name)

// uint32_t SAT_Plugin::note_ports_count(bool is_input)
// bool SAT_Plugin::note_ports_get(uint32_t index, bool is_input, clap_note_port_info_t *info)

// void SAT_Plugin::param_indication_set_mapping(clap_id param_id, bool has_mapping, const clap_color_t *color, const char *label, const char *description)
// void SAT_Plugin::param_indication_set_automation(clap_id param_id, uint32_t automation_state, const clap_color_t *color)

// uint32_t SAT_Plugin::params_count()
// bool SAT_Plugin::params_get_info(uint32_t param_index, clap_param_info_t *param_info)
// bool SAT_Plugin::params_get_value(clap_id param_id, double *out_value)
// bool SAT_Plugin::params_value_to_text(clap_id param_id, double value, char *out_buffer, uint32_t out_buffer_capacity)
// bool SAT_Plugin::params_text_to_value(clap_id param_id, const char *param_value_text, double *out_value)
// void SAT_Plugin::params_flush(const clap_input_events_t *in, const clap_output_events_t *out)

// void SAT_Plugin::posix_fd_support_on_fd(int fd, clap_posix_fd_flags_t flags)

// bool SAT_Plugin::preset_load_from_location(uint32_t location_kind, const char *location, const char *load_key)

// uint32_t SAT_Plugin::remote_controls_count()
// bool SAT_Plugin::remote_controls_get(uint32_t page_index, clap_remote_controls_page_t *page)

// bool SAT_Plugin::render_has_hard_realtime_requirement()
// bool SAT_Plugin::render_set(clap_plugin_render_mode mode)

// bool SAT_Plugin::state_save(const clap_ostream_t *stream)
// bool SAT_Plugin::state_load(const clap_istream_t *stream)

// bool SAT_Plugin::state_context_save(const clap_ostream_t *stream, uint32_t context_type)
// bool SAT_Plugin::state_context_load(const clap_istream_t *stream, uint32_t context_type)

// bool SAT_Plugin::surround_is_channel_mask_supported(uint64_t channel_mask)
// uint32_t SAT_Plugin::surround_get_channel_map(bool is_input, uint32_t port_index, uint8_t *channel_map, uint32_t channel_map_capacity)

// uint32_t SAT_Plugin::tail_get()

// void SAT_Plugin::thread_pool_exec(uint32_t task_index)

// void SAT_Plugin::timer_support_on_timer(clap_id timer_id)

// void SAT_Plugin::track_info_changed()

// bool SAT_Plugin::voice_info_get(clap_voice_info_t *info)

//------------------------------
// draft extensions
//------------------------------

// bool SAT_Plugin::extensible_audio_ports_add_port(bool is_input, uint32_t channel_count, const char *port_type, const void *port_details)
// bool SAT_Plugin::extensible_audio_ports_remove_port(bool is_input, uint32_t index)

// double SAT_Plugin::gain_adjustment_metering_get()

// uint32_t SAT_Plugin::mini_curve_display_get_curve_count()
// uint32_t SAT_Plugin::mini_curve_display_render(clap_mini_curve_display_curve_data_t *curves, uint32_t curves_size)
// void SAT_Plugin::mini_curve_display_set_observed(bool is_observed)
// bool SAT_Plugin::mini_curve_display_get_axis_name(uint32_t curve_index, char *x_name, char *y_name, uint32_t name_capacity)

// void SAT_Plugin::project_location_set(const clap_project_location_element_t *path, uint32_t num_elements)

// void SAT_Plugin::resource_directory_set_directory(const char *path, bool is_shared)
// void SAT_Plugin::resource_directory_collect(bool all)
// uint32_t SAT_Plugin::resource_directory_get_files_count()
// int32_t SAT_Plugin::resource_directory_get_file_path(uint32_t index, char *path, uint32_t path_size)

// uint32_t SAT_Plugin::triggers_count()
// bool SAT_Plugin::triggers_get_info(uint32_t index, clap_trigger_info_t *trigger_info)

// void SAT_Plugin::tuning_changed()

// void SAT_Plugin::undo_context_set_can_undo(bool can_undo)
// void SAT_Plugin::undo_context_set_can_redo(bool can_redo)
// void SAT_Plugin::undo_context_set_undo_name(const char *name)
// void SAT_Plugin::undo_context_set_redo_name(const char *name)
// void SAT_Plugin::undo_delta_get_delta_properties(clap_undo_delta_properties_t *properties)

// bool SAT_Plugin::undo_delta_can_use_delta_format_version(clap_id format_version)
// bool SAT_Plugin::undo_delta_undo(clap_id format_version, const void *delta, size_t delta_size)
// bool SAT_Plugin::undo_delta_redo(clap_id format_version, const void *delta, size_t delta_size)

//------------------------------
// draft extensions
//------------------------------

// #ifdef SAT_INCLUDE_ARA_EXTENSIONS
//     const ARAFactory* SAT_Plugin::ara_get_factory()
//     const ARAPlugInExtensionInstance* SAT_Plugin::ara_bind_to_document_controller(ARADocumentControllerRef documentControllerRef, ARAPlugInInstanceRoleFlags knownRoles, ARAPlugInInstanceRoleFlags assignedRoles)
// #endif





//------------------------------
// editor
//------------------------------

void SAT_Plugin::setInitialEditorSize(uint32_t AWidth, uint32_t AHeight, double AScale, bool AProportional)
{
    // MEditorInitialWidth = AWidth;
    // MEditorInitialHeight = AHeight;
    // MEditorInitialScale = AScale;
    // MEditorIsProportional = AProportional;
    SAT_Assert(MEditor);
    MEditor->setInitialSize(AWidth,AHeight,AScale,AProportional);
}

void SAT_Plugin::do_editor_listener_update_parameter(SAT_Parameter* AParameter, sat_param_t AValue)
{
    // Parameters.updateParameter();
    // MHost->updateParameter();
}

// uint32_t    SAT_Plugin::do_editor_owner_get_initial_width()     { return MEditorInitialWidth; }
// uint32_t    SAT_Plugin::do_editor_owner_get_initial_height()    { return MEditorInitialHeight; }
// double      SAT_Plugin::do_editor_owner_get_initial_scale()     { return MEditorInitialScale; }
// bool        SAT_Plugin::do_editor_owner_get_is_proportional()   { return MEditorIsProportional; }

//------------------------------
// processor
//------------------------------

void SAT_Plugin::setProcessor(SAT_Processor* AProcessor)
{
    SAT_Assert(AProcessor);
    MProcessor = AProcessor;
}

void SAT_Plugin::do_processor_listener_update_parameter(uint32_t AId, sat_param_t AValue)
{
    // Parameters.updateParameter();
    // MEditor->updateParameter();
}

// uint32_t    SAT_Plugin::do_processor_owner_getMinBlockSize()   { return 0; }
// uint32_t    SAT_Plugin::do_processor_owner_getMaxBlockSize()   { return 0; }
// double      SAT_Plugin::do_processor_owner_getSampleRate()     { return 0.0; }
