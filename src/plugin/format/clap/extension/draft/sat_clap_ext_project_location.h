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

class SAT_ClapProjectLocation
: public SAT_ClapExtension
{
    public:

        const char* getId() final       { return CLAP_EXT_PROJECT_LOCATION; }
        const void* getPtr() final      { return &MPlugExtProjectLocation; }

    private: // plugin

        static void project_location_set_callback(const clap_plugin_t *plugin, const clap_project_location_element_t *path, uint32_t num_elements);

        const clap_plugin_project_location_t MPlugExtProjectLocation
        {
            .set = project_location_set_callback
        };

};

//----------------------------------------------------------------------
//
// plugin
//
//----------------------------------------------------------------------

void SAT_ClapProjectLocation::project_location_set_callback(const clap_plugin_t *plugin, const clap_project_location_element_t *path, uint32_t num_elements)
{
    SAT_ClapPlugin* p = (SAT_ClapPlugin*)plugin->plugin_data;
    p->project_location_set(path,num_elements);
}

