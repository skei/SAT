#pragma once

#include "extern/plugin/sat_clap.h"


//------------------------------
// extension
//------------------------------

#include "plugin/format/clap/extension/sat_clap_ext_ambisonic.h"
#include "plugin/format/clap/extension/sat_clap_ext_audio_ports.h"
#include "plugin/format/clap/extension/sat_clap_ext_audio_ports_config.h"
#include "plugin/format/clap/extension/sat_clap_ext_audio_ports_config_info.h"
#include "plugin/format/clap/extension/sat_clap_ext_audio_ports_activation.h"
#include "plugin/format/clap/extension/sat_clap_ext_configurable_audio_ports.h"
#include "plugin/format/clap/extension/sat_clap_ext_context_menu.h"
#include "plugin/format/clap/extension/sat_clap_ext_event_registry.h"
#include "plugin/format/clap/extension/sat_clap_ext_gui.h"
#include "plugin/format/clap/extension/sat_clap_ext_latency.h"
#include "plugin/format/clap/extension/sat_clap_ext_log.h"
#include "plugin/format/clap/extension/sat_clap_ext_note_name.h"
#include "plugin/format/clap/extension/sat_clap_ext_note_ports.h"
#include "plugin/format/clap/extension/sat_clap_ext_param_indication.h"
#include "plugin/format/clap/extension/sat_clap_ext_params.h"
#include "plugin/format/clap/extension/sat_clap_ext_posix_fd_support.h"
#include "plugin/format/clap/extension/sat_clap_ext_preset_load.h"
#include "plugin/format/clap/extension/sat_clap_ext_remote_controls.h"
#include "plugin/format/clap/extension/sat_clap_ext_render.h"
#include "plugin/format/clap/extension/sat_clap_ext_state.h"
#include "plugin/format/clap/extension/sat_clap_ext_state_context.h"
#include "plugin/format/clap/extension/sat_clap_ext_surround.h"
#include "plugin/format/clap/extension/sat_clap_ext_tail.h"
#include "plugin/format/clap/extension/sat_clap_ext_thread_check.h"
#include "plugin/format/clap/extension/sat_clap_ext_thread_pool.h"
#include "plugin/format/clap/extension/sat_clap_ext_timer_support.h"
#include "plugin/format/clap/extension/sat_clap_ext_track_info.h"
#include "plugin/format/clap/extension/sat_clap_ext_voice_info.h"

//------------------------------
// draft
//------------------------------

#include "plugin/format/clap/extension/draft/sat_clap_ext_extensible_audio_ports.h"
#include "plugin/format/clap/extension/draft/sat_clap_ext_gain_adjustment_metering.h"
#include "plugin/format/clap/extension/draft/sat_clap_ext_mini_curve_display.h"
#include "plugin/format/clap/extension/draft/sat_clap_ext_project_location.h"
#include "plugin/format/clap/extension/draft/sat_clap_ext_resource_directory.h"
#include "plugin/format/clap/extension/draft/sat_clap_ext_scratch_memory.h"
#include "plugin/format/clap/extension/draft/sat_clap_ext_transport_control.h"
#include "plugin/format/clap/extension/draft/sat_clap_ext_triggers.h"
#include "plugin/format/clap/extension/draft/sat_clap_ext_tuning.h"
#include "plugin/format/clap/extension/draft/sat_clap_ext_undo.h"
#include "plugin/format/clap/extension/draft/sat_clap_ext_undo_context.h"
#include "plugin/format/clap/extension/draft/sat_clap_ext_undo_delta.h"

//------------------------------
// other
//------------------------------

#ifdef SAT_INCLUDE_ARA_EXTENSIONS
    #include "plugin/format/clap/extension/other/sat_clap_ext_ara_plugin_extension.h"
#endif

#ifdef SAT_INCLUDE_REAPER_EXTENSIONS
    #include "plugin/format/clap/extension/other/sat_clap_ext_reaper_extensions.h"
#endif
