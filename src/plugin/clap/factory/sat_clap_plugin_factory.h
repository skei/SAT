#pragma once

#include "base/sat.h"
#include "extern/plugin/sat_clap.h"
#include "plugin/clap/sat_clap_plugin.h"
#include "plugin/clap/sat_clap_factory.h"
#include "plugin/clap/sat_clap_extension.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_ClapPluginFactory
: public SAT_ClapFactory
{
    public:

        const char* getId() final   { return CLAP_PLUGIN_FACTORY_ID; }
        const void* getPtr() final  { return &MFactory; }

    private:

        static uint32_t                         get_plugin_count_callback(const struct clap_plugin_factory *factory);
        static const clap_plugin_descriptor_t*  get_plugin_descriptor_callback(const struct clap_plugin_factory *factory, uint32_t index);
        static const clap_plugin_t*             create_plugin_callback(const struct clap_plugin_factory *factory, const clap_host_t *host, const char *plugin_id);

        const clap_plugin_factory_t MFactory
        {
            .get_plugin_count      = get_plugin_count_callback,
            .get_plugin_descriptor = get_plugin_descriptor_callback,
            .create_plugin         = create_plugin_callback
        };

};

//----------------------------------------------------------------------
//
// plugin
//
//----------------------------------------------------------------------

uint32_t SAT_ClapPluginFactory::get_plugin_count_callback(const struct clap_plugin_factory *factory)
{
    SAT_TRACE;
    int32_t num = SAT.REGISTRY->getNumDescriptors();
    //SAT_PRINT("num: %i\n",num);
    return num;
}

const clap_plugin_descriptor_t* SAT_ClapPluginFactory::get_plugin_descriptor_callback(const struct clap_plugin_factory *factory, uint32_t index)
{
  SAT_PRINT("index: %i\n",index);
  const clap_plugin_descriptor_t* descriptor = SAT.REGISTRY->getDescriptor(index);
  return descriptor;
}

const clap_plugin_t* SAT_ClapPluginFactory::create_plugin_callback(const struct clap_plugin_factory *factory, const clap_host_t *host, const char *plugin_id)
{
    SAT_PRINT("plugin_id: %s\n",plugin_id);
    if (SAT_CreatePlugin)
    {
        /*
            int32_t index = SAT.REGISTRY->findDescriptor(plugin_id);
            if (index >= 0)
            {
                const clap_plugin_descriptor_t* descriptor = SAT.REGISTRY->getDescriptor(index);
                SAT_ClapPlugin* plugin = SAT_CreatePlugin(index,descriptor,host);
                //plugin->setFormat("CLAP");
                return  plugin->getClapPlugin();
            }
        */
        int32_t index = SAT.REGISTRY->findDescriptor(plugin_id);
        if (index >= 0)
        {
            SAT_PRINT("index: %i\n",index);
            const clap_plugin_descriptor_t* descriptor = SAT.REGISTRY->getDescriptor(index);
            SAT_ClapPlugin* plugin = SAT_CreatePlugin(index,descriptor,host);
            return plugin->getClapPlugin();
        }
    }
    return nullptr;
}

