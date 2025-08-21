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

class SAT_ClapTemplate
: public SAT_ClapExtension
{
    public:

        // const char* getId() final       { return CLAP_EXT_TEMPLATE; }
        // const char* getCompatId() final { return CLAP_EXT_TEMPLATE_COMPAT; }
        // const void* getPtr() final      { return &MPlugExtTemplate; }
        // const void* getHostPtr() final  { return &MHostExtTemplate; }

    private: // plugin

        // static bool template_pfunc_callback();

        // const clap_plugin_template_t MPlugExtTemplate
        // {
        //     .func = template_pfunc_callback
        // };

    private: // host

        // static bool template_hfunc_callback();

        // const clap_host_template_t MHostExtTemplate
        // {
        //     .func = template_hfunc_callback
        // };

};

//----------------------------------------------------------------------
//
// plugin
//
//----------------------------------------------------------------------

// uint32_t SAT_ClapTemplate::template_pfunc_callback(const clap_plugin_t *plugin)
// {
//     SAT_ClapPlugin* p = (SAT_ClapPlugin*)p->plugin_data;
//     return p->pfunc();
// }

//----------------------------------------------------------------------
//
// host
//
//----------------------------------------------------------------------

// void SAT_ClapTemplate::template_hfunc_callback(const clap_host_t *host)
// {
//     SAT_ClapHost* h = (SAT_ClapHost*)host->host_data;
//     h->hfunc();
// }
