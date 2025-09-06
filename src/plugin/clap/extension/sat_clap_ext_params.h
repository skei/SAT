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

class SAT_ClapParams
: public SAT_ClapExtension
{

    public:

        const char* getId() final       { return CLAP_EXT_PARAMS; }
        const void* getPtr() final      { return &MPlugExtParams; }
        const void* getHostPtr() final  { return &MHostExtParams; }

    private: // plugin

        static uint32_t params_count_callback(const clap_plugin_t *plugin);
        static bool     params_get_info_callback(const clap_plugin_t *plugin, uint32_t param_index, clap_param_info_t *param_info);
        static bool     params_get_value_callback(const clap_plugin_t *plugin, clap_id param_id, double *out_value);
        static bool     params_value_to_text_callback(const clap_plugin_t *plugin, clap_id param_id, double value, char *out_buffer, uint32_t out_buffer_capacity);
        static bool     params_text_to_value_callback(const clap_plugin_t *plugin, clap_id param_id, const char *param_value_text, double *out_value);
        static void     params_flush_callback(const clap_plugin_t *plugin, const clap_input_events_t *in, const clap_output_events_t *out);

        const clap_plugin_params_t MPlugExtParams
        {
            .count          = params_count_callback,
            .get_info       = params_get_info_callback,
            .get_value      = params_get_value_callback,
            .value_to_text  = params_value_to_text_callback,
            .text_to_value  = params_text_to_value_callback,
            .flush          = params_flush_callback
        };

    private: // host

        static void     params_rescan_callback(const clap_host_t *host, clap_param_rescan_flags flags);
        static void     params_clear_callback(const clap_host_t *host, clap_id param_id, clap_param_clear_flags flags);
        static void     params_request_flush_callback(const clap_host_t *host);

        const clap_host_params_t MHostExtParams
        {
            .rescan         = params_rescan_callback,
            .clear          = params_clear_callback,
            .request_flush  = params_request_flush_callback
        };

};

//----------------------------------------------------------------------
//
// plugin
//
//----------------------------------------------------------------------

uint32_t SAT_ClapParams::params_count_callback(const clap_plugin_t *plugin)
{
    SAT_ClapPlugin* p = (SAT_ClapPlugin*)plugin->plugin_data;
    return p->params_count();
}

bool SAT_ClapParams::params_get_info_callback(const clap_plugin_t *plugin, uint32_t param_index, clap_param_info_t *param_info)
{
    SAT_ClapPlugin* p = (SAT_ClapPlugin*)plugin->plugin_data;
    return p->params_get_info(param_index,param_info);
}

bool SAT_ClapParams::params_get_value_callback(const clap_plugin_t *plugin, clap_id param_id, double *out_value)
{
    SAT_ClapPlugin* p = (SAT_ClapPlugin*)plugin->plugin_data;
    return p->params_get_value(param_id,out_value);
}

bool SAT_ClapParams::params_value_to_text_callback(const clap_plugin_t *plugin, clap_id param_id, double value, char *out_buffer, uint32_t out_buffer_capacity)
{
    SAT_ClapPlugin* p = (SAT_ClapPlugin*)plugin->plugin_data;
    return p->params_value_to_text(param_id,value,out_buffer,out_buffer_capacity);
}

bool SAT_ClapParams::params_text_to_value_callback(const clap_plugin_t *plugin, clap_id param_id, const char *param_value_text, double *out_value)
{
    SAT_ClapPlugin* p = (SAT_ClapPlugin*)plugin->plugin_data;
    return p->params_text_to_value(param_id,param_value_text,out_value);
}

void SAT_ClapParams::params_flush_callback(const clap_plugin_t *plugin, const clap_input_events_t *in, const clap_output_events_t *out)
{
    SAT_ClapPlugin* p = (SAT_ClapPlugin*)plugin->plugin_data;
    p->params_flush(in,out);
}

//----------------------------------------------------------------------
//
// host
//
//----------------------------------------------------------------------

void SAT_ClapParams::params_rescan_callback(const clap_host_t *host, clap_param_rescan_flags flags)
{
    SAT_ClapHost* h = (SAT_ClapHost*)host->host_data;
    h->params_rescan(flags);
}

void SAT_ClapParams::params_clear_callback(const clap_host_t *host, clap_id param_id, clap_param_clear_flags flags)
{
    SAT_ClapHost* h = (SAT_ClapHost*)host->host_data;
    h->params_clear(param_id,flags);
}

void SAT_ClapParams::params_request_flush_callback(const clap_host_t *host)
{
    SAT_ClapHost* h = (SAT_ClapHost*)host->host_data;
    h->params_request_flush();
}

