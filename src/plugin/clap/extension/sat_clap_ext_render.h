#pragma once

#include "base/sat_base.h"
#include "extern/plugin/sat_clap.h"
#include "plugin/clap/sat_clap_plugin.h"
#include "plugin/clap/sat_clap_host.h"
#include "plugin/clap/sat_clap_extension.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_ClapRender
: public SAT_ClapExtension
{
    public:

        const char* getId() final       { return CLAP_EXT_RENDER; }
        const void* getPtr() final      { return &MPlugExtRender; }

    private: // plugin

        static bool render_has_hard_realtime_requirement_callback(const clap_plugin_t *plugin);
        static bool render_set_callback(const clap_plugin_t *plugin, clap_plugin_render_mode mode);

        const clap_plugin_render_t MPlugExtRender
        {
            .has_hard_realtime_requirement  = render_has_hard_realtime_requirement_callback,
            .set                            = render_set_callback
        };        

};

//----------------------------------------------------------------------
//
// plugin
//
//----------------------------------------------------------------------

bool SAT_ClapRender::render_has_hard_realtime_requirement_callback(const clap_plugin_t *plugin)
{
    SAT_ClapPlugin* p = (SAT_ClapPlugin*)plugin->plugin_data;
    return p->render_has_hard_realtime_requirement();
}

bool SAT_ClapRender::render_set_callback(const clap_plugin_t *plugin, clap_plugin_render_mode mode)
{
    SAT_ClapPlugin* p = (SAT_ClapPlugin*)plugin->plugin_data;
    return p->render_set(mode);
}
