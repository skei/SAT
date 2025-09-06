#pragma once

#include "base/sat.h"
#include "extern/plugin/sat_clap.h"
#include "plugin/clap/sat_clap_factory.h"
#include "plugin/clap/sat_clap_factories.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

static bool         sat_clap_entry_init_callback(const char *plugin_path);
static void         sat_clap_entry_deinit_callback(void);
static const void*  sat_clap_entry_get_factory_callback(const char* factory_id);

CLAP_EXPORT extern const clap_plugin_entry_t clap_entry
{
    .clap_version = CLAP_VERSION,
    .init         = sat_clap_entry_init_callback,
    .deinit       = sat_clap_entry_deinit_callback,
    .get_factory  = sat_clap_entry_get_factory_callback
};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

bool sat_clap_entry_init_callback(const char *plugin_path)
{
    SAT.initialize();
    SAT.activate(&SAT);
    SAT_PRINT("plugin_path: %s\n",plugin_path);
    SAT.REGISTRY->setBinaryPath(plugin_path);
    SAT.REGISTRY->registerFactory( new SAT_ClapPluginFactory() );
    return true;
}

void sat_clap_entry_deinit_callback(void)
{
    SAT_TRACE;
    SAT.deactivate(&SAT);
    SAT.cleanup();
}

const void* sat_clap_entry_get_factory_callback(const char* factory_id)
{
    SAT_PRINT("factory_id: %s\n",factory_id);
    int32_t index = SAT.REGISTRY->findFactory(factory_id);
    if (index >= 0)
    {
        SAT_PRINT("... found at index %i\n",index);
        const clap_plugin_factory_t* factory = (const clap_plugin_factory_t*)SAT.REGISTRY->getFactory(index);
        return factory;
    }
    // none..
    return nullptr;
}

