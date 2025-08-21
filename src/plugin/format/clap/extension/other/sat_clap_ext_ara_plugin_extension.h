#pragma once

#include "base/sat_base.h"
#include "plugin/format/clap/sat_clap.h"
#include "plugin/format/clap/sat_clap_plugin.h"
#include "plugin/format/clap/sat_clap_host.h"
#include "plugin/format/clap/sat_clap_extension.h"

#include "extern/plugin/ara/arasdk/ARACLAP.h"
using namespace ARA;

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_ClapAraPluginExtension
: public SAT_ClapExtension
{
    public:

        const char* getId() final       { return CLAP_EXT_ARA_PLUGINEXTENSION; }
        const void* getPtr() final      { return &MPlugExtAraPluginExtension; }

    private: // plugin

        static const ARAFactory*                    ara_get_factory_callback(const clap_plugin_t* plugin);
        static const ARAPlugInExtensionInstance*    ara_bind_to_document_controller_callback(const clap_plugin_t* plugin, ARADocumentControllerRef documentControllerRef, ARAPlugInInstanceRoleFlags knownRoles, ARAPlugInInstanceRoleFlags assignedRoles);

        const clap_ara_plugin_extension_t MPlugExtAraPluginExtension
        {
            .get_factory                    = ara_get_factory_callback,
            .bind_to_document_controller    = ara_bind_to_document_controller_callback
        };

};

//----------------------------------------------------------------------
//
// plugin
//
//----------------------------------------------------------------------

const ARAFactory* SAT_ClapAraPluginExtension::ara_get_factory_callback(const clap_plugin_t* plugin)
{
    SAT_ClapPlugin* p = (SAT_ClapPlugin*)plugin->plugin_data;
    return p->ara_get_factory();
}

const ARAPlugInExtensionInstance* SAT_ClapAraPluginExtension::ara_bind_to_document_controller_callback(const clap_plugin_t* plugin, ARADocumentControllerRef documentControllerRef, ARAPlugInInstanceRoleFlags knownRoles, ARAPlugInInstanceRoleFlags assignedRoles)
{
    SAT_ClapPlugin* p = (SAT_ClapPlugin*)plugin->plugin_data;
    return p->ara_bind_to_document_controller(documentControllerRef,knownRoles,assignedRoles);
}
