#pragma once

/*
    ../build/compile -i ../build/build.cpp -o ../bin/build -S linux -F exe -G native -d
    ../build/compile -i ../build/build.cpp -o ../bin/build.clap -S linux -F clap -G native -d
    nc -U -l -k /tmp/sat.socket
*/

//----------------------------------------------------------------------

#include "base/sat.h"
#include "plugin/sat_plugin.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

const clap_plugin_descriptor_t myDescriptor =
{
    .clap_version   = CLAP_VERSION,
    .id             = "myPlugin",
    .name           = "plugin",
    .vendor         = SAT_VENDOR,
    .url            = SAT_URL,
    .manual_url     = "",
    .support_url    = "",
    .version        = SAT_VERSION,
    .description    = "my cool plugin",
    .features       = (const char*[]){ CLAP_PLUGIN_FEATURE_AUDIO_EFFECT, nullptr }
};

//------------------------------
//
//------------------------------

class myPlugin
: public SAT_Plugin 
{
    private:
        SAT_ClapParams  MParams;
    public:
        myPlugin(const clap_plugin_descriptor_t* ADescriptor, const clap_host_t* AHost);
        virtual ~myPlugin();
    public:
        uint32_t params_count() final;
};

//------------------------------
//
//------------------------------

myPlugin::myPlugin(const clap_plugin_descriptor_t* ADescriptor, const clap_host_t* AHost)
: SAT_Plugin(ADescriptor,AHost)
{
    registerStaticExtension(&MParams);
    registerExtension( new SAT_ClapGui() );
}

myPlugin::~myPlugin()
{
}

uint32_t myPlugin::params_count()
{
    return 0;
}

//------------------------------
//
//------------------------------

#ifndef SAT_NO_ENTRY
    #include "plugin/sat_entry.h"
    SAT_REGISTER_SINGLE_PLUGIN(myDescriptor,myPlugin)
#endif

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

int main(void)
{
    //clap_entry.init("./");
    // myPlugin* plugin = new myPlugin(nullptr,nullptr);
    // delete plugin;
    //clap_entry.deinit();
    return 0;
}

