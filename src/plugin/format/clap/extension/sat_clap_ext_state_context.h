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

class SAT_ClapStateContext
: public SAT_ClapExtension
{
    public:

        const char* getId() final       { return CLAP_EXT_STATE_CONTEXT; }
        const void* getPtr() final      { return &MPlugExtStateContext; }

    private: // plugin

        static bool state_context_save_callback(const clap_plugin_t *plugin, const clap_ostream_t *stream, uint32_t context_type);
        static bool state_context_load_callback(const clap_plugin_t *plugin, const clap_istream_t *stream, uint32_t context_type);

        const clap_plugin_state_context_t MPlugExtStateContext
        {
            .save = state_context_save_callback,
            .load = state_context_load_callback
        };        

};

//----------------------------------------------------------------------
//
// plugin
//
//----------------------------------------------------------------------

bool SAT_ClapStateContext::state_context_save_callback(const clap_plugin_t *plugin, const clap_ostream_t *stream, uint32_t context_type)
{
    SAT_ClapPlugin* p = (SAT_ClapPlugin*)plugin->plugin_data;
    return p->state_context_save(stream,context_type);
}

bool SAT_ClapStateContext::state_context_load_callback(const clap_plugin_t *plugin, const clap_istream_t *stream, uint32_t context_type)
{
    SAT_ClapPlugin* p = (SAT_ClapPlugin*)plugin->plugin_data;
    return p->state_context_load(stream,context_type);
}  
