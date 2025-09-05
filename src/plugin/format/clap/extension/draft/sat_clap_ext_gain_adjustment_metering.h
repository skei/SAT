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

class SAT_ClapGainAdjustmentMetering
: public SAT_ClapExtension
{
    public:

        const char* getId() final       { return CLAP_EXT_GAIN_ADJUSTMENT_METERING; }
        const void* getPtr() final      { return &MPlugExtGainAdjustmentMetering; }

    private: // plugin

        static double gain_adjustment_metering_callback(const clap_plugin_t *plugin);

        const clap_plugin_gain_adjustment_metering_t MPlugExtGainAdjustmentMetering
        {
            .get  = gain_adjustment_metering_callback
        };

};

//----------------------------------------------------------------------
//
// plugin
//
//----------------------------------------------------------------------

double SAT_ClapGainAdjustmentMetering::gain_adjustment_metering_callback(const clap_plugin_t *plugin)
{
    SAT_ClapPlugin* p = (SAT_ClapPlugin*)plugin->plugin_data;
    return p->gain_adjustment_metering_get();
}
