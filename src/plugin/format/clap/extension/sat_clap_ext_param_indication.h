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

class SAT_ClapParamIndication
: public SAT_ClapExtension
{
    public:

        const char* getId() final       { return CLAP_EXT_PARAM_INDICATION; }
        const char* getCompatId() final { return CLAP_EXT_PARAM_INDICATION_COMPAT; }
        const void* getPtr() final      { return &MPlugExtParamIndication; }

    private: // plugin

        static void param_indication_set_mapping_callback(const clap_plugin_t *plugin, clap_id param_id, bool has_mapping, const clap_color_t *color, const char *label, const char *description);
        static void param_indication_set_automation_callback(const clap_plugin_t *plugin, clap_id param_id, uint32_t automation_state, const clap_color_t *color);

        const clap_plugin_param_indication_t MPlugExtParamIndication
        {
            .set_mapping    = param_indication_set_mapping_callback,
            .set_automation = param_indication_set_automation_callback
        };        

};

//----------------------------------------------------------------------
//
// plugin
//
//----------------------------------------------------------------------

void SAT_ClapParamIndication::param_indication_set_mapping_callback(const clap_plugin_t *plugin, clap_id param_id, bool has_mapping, const clap_color_t *color, const char *label, const char *description)
{
    SAT_ClapPlugin* p = (SAT_ClapPlugin*)plugin->plugin_data;
    return p->param_indication_set_mapping(param_id,has_mapping,color,label,description);
}

void SAT_ClapParamIndication::param_indication_set_automation_callback(const clap_plugin_t *plugin, clap_id param_id, uint32_t automation_state, const clap_color_t *color)
{
    SAT_ClapPlugin* p = (SAT_ClapPlugin*)plugin->plugin_data;
    return p->param_indication_set_automation(param_id,automation_state,color);
}
