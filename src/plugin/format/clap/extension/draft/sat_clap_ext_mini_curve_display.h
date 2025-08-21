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

class SAT_ClapMiniCurveDisplay
: public SAT_ClapExtension
{
    public:

        const char* getId() final       { return CLAP_EXT_MINI_CURVE_DISPLAY; }
        const void* getPtr() final      { return &MPlugExtMiniCurveDisplay; }

    private: // plugin

        static uint32_t mini_curve_display_get_curve_count_callback(const clap_plugin_t *plugin);
        static uint32_t mini_curve_display_render_callback(const clap_plugin_t *plugin, clap_mini_curve_display_curve_data_t *curves, uint32_t curves_size);
        static void     mini_curve_display_set_observed_callback(const clap_plugin_t *plugin, bool is_observed);
        static bool     mini_curve_display_get_axis_name_callback(const clap_plugin_t *plugin, uint32_t curve_index, char *x_name, char *y_name, uint32_t name_capacity);

        const clap_plugin_mini_curve_display_t MPlugExtMiniCurveDisplay
        {
            .get_curve_count  = mini_curve_display_get_curve_count_callback,
            .render           = mini_curve_display_render_callback,
            .set_observed     = mini_curve_display_set_observed_callback,
            .get_axis_name    = mini_curve_display_get_axis_name_callback
        };        

};

//----------------------------------------------------------------------
//
// plugin
//
//----------------------------------------------------------------------

uint32_t SAT_ClapMiniCurveDisplay::mini_curve_display_get_curve_count_callback(const clap_plugin_t *plugin)
{
    SAT_ClapPlugin* p = (SAT_ClapPlugin*)plugin->plugin_data;
    return p->mini_curve_display_get_curve_count();
}

uint32_t SAT_ClapMiniCurveDisplay::mini_curve_display_render_callback(const clap_plugin_t *plugin, clap_mini_curve_display_curve_data_t *curves, uint32_t curves_size)
{
    SAT_ClapPlugin* p = (SAT_ClapPlugin*)plugin->plugin_data;
    return p->mini_curve_display_render(curves,curves_size);
}

void SAT_ClapMiniCurveDisplay::mini_curve_display_set_observed_callback(const clap_plugin_t *plugin, bool is_observed)
{
    SAT_ClapPlugin* p = (SAT_ClapPlugin*)plugin->plugin_data;
    p->mini_curve_display_set_observed(is_observed);
}

bool SAT_ClapMiniCurveDisplay::mini_curve_display_get_axis_name_callback(const clap_plugin_t *plugin, uint32_t curve_index, char *x_name, char *y_name, uint32_t name_capacity)
{
    SAT_ClapPlugin* p = (SAT_ClapPlugin*)plugin->plugin_data;
    return p->mini_curve_display_get_axis_name(curve_index,x_name,y_name,name_capacity);
}
