#pragma once

#include "base/sat_base.h"
#include "plugin/format/clap/sat_clap.h"
#include "plugin/format/clap/sat_clap_plugin.h"
#include "plugin/format/clap/sat_clap_host.h"
#include "plugin/format/clap/sat_clap_extension.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_ClapUndoDelta
: public SAT_ClapExtension
{
    public:

        const char* getId() final       { return CLAP_EXT_UNDO_DELTA; }
        const void* getPtr() final      { return &MPlugExtUndoDelta; }

    private: // plugin

        static void undo_delta_get_delta_properties_callback(const clap_plugin_t *plugin, clap_undo_delta_properties_t *properties);
        static bool undo_delta_can_use_delta_format_version_callback(const clap_plugin_t *plugin, clap_id format_version);
        static bool undo_delta_undo_callback(const clap_plugin_t *plugin, clap_id format_version, const void *delta, size_t delta_size);
        static bool undo_delta_redo_callback(const clap_plugin_t *plugin, clap_id format_version, const void *delta, size_t delta_size);

        const clap_plugin_undo_delta_t MPlugExtUndoDelta
        {
            .get_delta_properties         = undo_delta_get_delta_properties_callback,
            .can_use_delta_format_version = undo_delta_can_use_delta_format_version_callback,
            .undo                         = undo_delta_undo_callback,
            .redo                         = undo_delta_redo_callback
        };

};

//----------------------------------------------------------------------
//
// plugin
//
//----------------------------------------------------------------------

void SAT_ClapUndoDelta::undo_delta_get_delta_properties_callback(const clap_plugin_t *plugin, clap_undo_delta_properties_t *properties)
{
    SAT_ClapPlugin* p = (SAT_ClapPlugin*)plugin->plugin_data;
    p->undo_delta_get_delta_properties(properties);
}

bool SAT_ClapUndoDelta::undo_delta_can_use_delta_format_version_callback(const clap_plugin_t *plugin, clap_id format_version)
{
    SAT_ClapPlugin* p = (SAT_ClapPlugin*)plugin->plugin_data;
    return p->undo_delta_can_use_delta_format_version(format_version);
}

bool SAT_ClapUndoDelta::undo_delta_undo_callback(const clap_plugin_t *plugin, clap_id format_version, const void *delta, size_t delta_size)
{
    SAT_ClapPlugin* p = (SAT_ClapPlugin*)plugin->plugin_data;
    return p->undo_delta_undo(format_version,delta,delta_size);
}

bool SAT_ClapUndoDelta::undo_delta_redo_callback(const clap_plugin_t *plugin, clap_id format_version, const void *delta, size_t delta_size)
{
    SAT_ClapPlugin* p = (SAT_ClapPlugin*)plugin->plugin_data;
    return p->undo_delta_redo(format_version,delta,delta_size);
}
