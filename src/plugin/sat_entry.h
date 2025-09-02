#pragma once

#include "base/sat_base.h"

#ifndef SAT_INCLUDE_REGISTRY
    #error PLUGINS REQUIRE REGISTRY
#endif

//------------------------------
//
//------------------------------

#ifdef SAT_PLUGIN_CLAP
    #include "plugin/format/clap/sat_clap_entry.h"
#endif

#ifdef SAT_PLUGIN_DSSI
    #include "plugin/format/dssi/sat_dssi_entry.h"
#endif

#ifdef SAT_PLUGIN_EXE
    #include "plugin/format/exe/sat_exe_entry.h"
#endif

#ifdef SAT_PLUGIN_LADSPA
    #include "plugin/format/ladspa/sat_ladspa_entry.h"
#endif

#ifdef SAT_PLUGIN_LV2
    #include "plugin/format/lv2/sat_lv2_entry.h"
#endif

#ifdef SAT_PLUGIN_VST2
    #include "plugin/format/vst2/sat_vst2_entry.h"
#endif

#ifdef SAT_PLUGIN_VST3
    #include "plugin/format/vst3/sat_vst3_entry.h"
#endif

//------------------------------
//
//------------------------------

#ifdef SAT_INCLUDE_REGISTRY

    #define SAT_REGISTER_SINGLE_PLUGIN(DESC,PLUG)                                                                               \
                                                                                                                                \
        void SAT_Register(SAT_GlobalRegistry* ARegistry)                                                                        \
        {                                                                                                                       \
            ARegistry->registerDescriptor(&DESC);                                                                               \
        }                                                                                                                       \
                                                                                                                                \
        SAT_ClapPlugin* SAT_CreatePlugin(int32_t AIndex, const clap_plugin_descriptor_t* ADescriptor, const clap_host_t* AHost) \
        {                                                                                                                       \
            if (AIndex == 0) {                                                                                                  \
                SAT_Plugin* plugin = new PLUG(ADescriptor,AHost);                                                               \
                return plugin;                                                                                                  \
            }                                                                                                                   \
            return nullptr;                                                                                                     \
        }

#else

    // empty func.. will be optimized away.. (hopefully)..
    #define SAT_REGISTER_SINGLE_PLUGIN(DESC,PLUG) void sat_no_entry() {}

#endif
