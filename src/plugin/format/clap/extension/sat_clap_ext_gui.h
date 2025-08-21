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

class SAT_ClapGui
: public SAT_ClapExtension
{
    public:

        const char* getId() final       { return CLAP_EXT_GUI; }
        const void* getPtr() final      { return &MPlugExtGui; }
        const void* getHostPtr() final  { return &MHostExtGui; }

    private: // plugin

        static  bool gui_is_api_supported_callback(const clap_plugin_t *plugin, const char *api, bool is_floating);
        static  bool gui_get_preferred_api_callback(const clap_plugin_t *plugin, const char **api, bool *is_floating);
        static  bool gui_create_callback(const clap_plugin_t *plugin, const char *api, bool is_floating);
        static  void gui_destroy_callback(const clap_plugin_t *plugin);
        static  bool gui_set_scale_callback(const clap_plugin_t *plugin, double scale);
        static  bool gui_get_size_callback(const clap_plugin_t *plugin, uint32_t *width, uint32_t *height);
        static  bool gui_can_resize_callback(const clap_plugin_t *plugin);
        static  bool gui_get_resize_hints_callback(const clap_plugin_t *plugin, clap_gui_resize_hints_t *hints);
        static  bool gui_adjust_size_callback(const clap_plugin_t *plugin, uint32_t *width, uint32_t *height);
        static  bool gui_set_size_callback(const clap_plugin_t *plugin, uint32_t width, uint32_t height);
        static  bool gui_set_parent_callback(const clap_plugin_t *plugin, const clap_window_t *window);
        static  bool gui_set_transient_callback(const clap_plugin_t *plugin, const clap_window_t *window);
        static  void gui_suggest_title_callback(const clap_plugin_t *plugin, const char *title);
        static  bool gui_show_callback(const clap_plugin_t *plugin);
        static  bool gui_hide_callback(const clap_plugin_t *plugin);
         
        const clap_plugin_gui_t MPlugExtGui
        {
            .is_api_supported   = gui_is_api_supported_callback,
            .get_preferred_api  = gui_get_preferred_api_callback,
            .create             = gui_create_callback,
            .destroy            = gui_destroy_callback,
            .set_scale          = gui_set_scale_callback,
            .get_size           = gui_get_size_callback,
            .can_resize         = gui_can_resize_callback,
            .get_resize_hints   = gui_get_resize_hints_callback,
            .adjust_size        = gui_adjust_size_callback,
            .set_size           = gui_set_size_callback,
            .set_parent         = gui_set_parent_callback,
            .set_transient      = gui_set_transient_callback,
            .suggest_title      = gui_suggest_title_callback,
            .show               = gui_show_callback,
            .hide               = gui_hide_callback
        };

    private: // host

        static  void gui_resize_hints_changed_callback(const clap_host_t *host);
        static  bool gui_request_resize_callback(const clap_host_t *host, uint32_t width, uint32_t height);
        static  bool gui_request_show_callback(const clap_host_t *host);
        static  bool gui_request_hide_callback(const clap_host_t *host);
        static  void gui_closed_callback(const clap_host_t *host, bool was_closed);

        const clap_host_gui_t MHostExtGui
        {
            .resize_hints_changed = gui_resize_hints_changed_callback,
            .request_resize       = gui_request_resize_callback,
            .request_show         = gui_request_show_callback,
            .request_hide         = gui_request_hide_callback,
            .closed               = gui_closed_callback
        };

};

//----------------------------------------------------------------------
//
// plugin
//
//----------------------------------------------------------------------

bool SAT_ClapGui::gui_is_api_supported_callback(const clap_plugin_t *plugin, const char *api, bool is_floating)
{
    SAT_ClapPlugin* p = (SAT_ClapPlugin*)plugin->plugin_data;
    return p->gui_is_api_supported(api,is_floating);
}

bool SAT_ClapGui::gui_get_preferred_api_callback(const clap_plugin_t *plugin, const char **api, bool *is_floating)
{
    SAT_ClapPlugin* p = (SAT_ClapPlugin*)plugin->plugin_data;
    return p->gui_get_preferred_api(api,is_floating);
}

bool SAT_ClapGui::gui_create_callback(const clap_plugin_t *plugin, const char *api, bool is_floating)
{
    SAT_ClapPlugin* p = (SAT_ClapPlugin*)plugin->plugin_data;
    return p->gui_create(api,is_floating);
}

void SAT_ClapGui::gui_destroy_callback(const clap_plugin_t *plugin)
{
    SAT_ClapPlugin* p = (SAT_ClapPlugin*)plugin->plugin_data;
    p->gui_destroy();
}

bool SAT_ClapGui::gui_set_scale_callback(const clap_plugin_t *plugin, double scale)
{
    SAT_ClapPlugin* p = (SAT_ClapPlugin*)plugin->plugin_data;
    return p->gui_set_scale(scale);
}

bool SAT_ClapGui::gui_get_size_callback(const clap_plugin_t *plugin, uint32_t *width, uint32_t *height)
{
    SAT_ClapPlugin* p = (SAT_ClapPlugin*)plugin->plugin_data;
    return p->gui_get_size(width,height);
}

bool SAT_ClapGui::gui_can_resize_callback(const clap_plugin_t *plugin)
{
    SAT_ClapPlugin* p = (SAT_ClapPlugin*)plugin->plugin_data;
    return p->gui_can_resize();
}

bool SAT_ClapGui::gui_get_resize_hints_callback(const clap_plugin_t *plugin, clap_gui_resize_hints_t *hints)
{
    SAT_ClapPlugin* p = (SAT_ClapPlugin*)plugin->plugin_data;
    return p->gui_get_resize_hints(hints);
}

bool SAT_ClapGui::gui_adjust_size_callback(const clap_plugin_t *plugin, uint32_t *width, uint32_t *height)
{
    SAT_ClapPlugin* p = (SAT_ClapPlugin*)plugin->plugin_data;
    return p->gui_adjust_size(width,height);
}

bool SAT_ClapGui::gui_set_size_callback(const clap_plugin_t *plugin, uint32_t width, uint32_t height)
{
    SAT_ClapPlugin* p = (SAT_ClapPlugin*)plugin->plugin_data;
    return p->gui_set_size(width,height);
}

bool SAT_ClapGui::gui_set_parent_callback(const clap_plugin_t *plugin, const clap_window_t *window)
{
    SAT_ClapPlugin* p = (SAT_ClapPlugin*)plugin->plugin_data;
    return p->gui_set_parent(window);
}

bool SAT_ClapGui::gui_set_transient_callback(const clap_plugin_t *plugin, const clap_window_t *window)
{
    SAT_ClapPlugin* p = (SAT_ClapPlugin*)plugin->plugin_data;
    return p->gui_set_transient(window);
}

void SAT_ClapGui::gui_suggest_title_callback(const clap_plugin_t *plugin, const char *title)
{
    SAT_ClapPlugin* p = (SAT_ClapPlugin*)plugin->plugin_data;
    p->gui_suggest_title(title);
}

bool SAT_ClapGui::gui_show_callback(const clap_plugin_t *plugin)
{
    SAT_ClapPlugin* p = (SAT_ClapPlugin*)plugin->plugin_data;
    return p->gui_show();
}

bool SAT_ClapGui::gui_hide_callback(const clap_plugin_t *plugin)
{
    SAT_ClapPlugin* p = (SAT_ClapPlugin*)plugin->plugin_data;
    return p->gui_hide();
}

//----------------------------------------------------------------------
//
// host
//
//----------------------------------------------------------------------

void SAT_ClapGui::gui_resize_hints_changed_callback(const clap_host_t *host)
{
    SAT_ClapHost* h = (SAT_ClapHost*)host->host_data;
    h->gui_resize_hints_changed();
}

bool SAT_ClapGui::gui_request_resize_callback(const clap_host_t *host, uint32_t width, uint32_t height)
{
    SAT_ClapHost* h = (SAT_ClapHost*)host->host_data;
    return h->gui_request_resize(width,height);
}

bool SAT_ClapGui::gui_request_show_callback(const clap_host_t *host)
{
    SAT_ClapHost* h = (SAT_ClapHost*)host->host_data;
    return h->gui_request_show();
}

bool SAT_ClapGui::gui_request_hide_callback(const clap_host_t *host)
{
    SAT_ClapHost* h = (SAT_ClapHost*)host->host_data;
    return h->gui_request_hide();
}

void SAT_ClapGui::gui_closed_callback(const clap_host_t *host, bool was_closed)
{
    SAT_ClapHost* h = (SAT_ClapHost*)host->host_data;
    h->gui_closed(was_closed);
}
