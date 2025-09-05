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

class SAT_ClapUndoContext
: public SAT_ClapExtension
{
    public:

        const char* getId() final       { return CLAP_EXT_UNDO_CONTEXT; }
        const void* getPtr() final      { return &MPlugExtUndoContext; }

    private: // plugin

        static void undo_context_set_can_undo_callback(const clap_plugin_t *plugin, bool can_undo);
        static void undo_context_set_can_redo_callback(const clap_plugin_t *plugin, bool can_redo);
        static void undo_context_set_undo_name_callback(const clap_plugin_t *plugin, const char *name);
        static void undo_context_set_redo_name_callback(const clap_plugin_t *plugin, const char *name);

        const clap_plugin_undo_context_t MPlugExtUndoContext
        {
            .set_can_undo   = undo_context_set_can_undo_callback,
            .set_can_redo   = undo_context_set_can_redo_callback,
            .set_undo_name  = undo_context_set_undo_name_callback,
            .set_redo_name  = undo_context_set_redo_name_callback
        };        

};

//----------------------------------------------------------------------
//
// plugin
//
//----------------------------------------------------------------------

void SAT_ClapUndoContext::undo_context_set_can_undo_callback(const clap_plugin_t *plugin, bool can_undo)
{
  SAT_ClapPlugin* p = (SAT_ClapPlugin*)plugin->plugin_data;
  p->undo_context_set_can_undo(can_undo);
}

void SAT_ClapUndoContext::undo_context_set_can_redo_callback(const clap_plugin_t *plugin, bool can_redo)
{
  SAT_ClapPlugin* p = (SAT_ClapPlugin*)plugin->plugin_data;
  p->undo_context_set_can_redo(can_redo);
}

void SAT_ClapUndoContext::undo_context_set_undo_name_callback(const clap_plugin_t *plugin, const char *name)
{
  SAT_ClapPlugin* p = (SAT_ClapPlugin*)plugin->plugin_data;
  p->undo_context_set_undo_name(name);
}

void SAT_ClapUndoContext::undo_context_set_redo_name_callback(const clap_plugin_t *plugin, const char *name)
{
  SAT_ClapPlugin* p = (SAT_ClapPlugin*)plugin->plugin_data;
  p->undo_context_set_redo_name(name);
}
