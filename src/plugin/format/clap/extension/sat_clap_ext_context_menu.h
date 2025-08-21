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

class SAT_ClapContextMenu
: public SAT_ClapExtension
{
    public:

        const char* getId() final       { return CLAP_EXT_CONTEXT_MENU; }
        const char* getCompatId() final { return CLAP_EXT_CONTEXT_MENU_COMPAT; }
        const void* getPtr() final      { return &MPlugExtContextMenu; }
        const void* getHostPtr() final  { return &MHostExtContextMenu; }

    private: // plugin

        static bool context_menu_populate_callback(const clap_plugin_t *plugin, const clap_context_menu_target_t  *target, const clap_context_menu_builder_t *builder);
        static bool context_menu_perform_callback(const clap_plugin_t *plugin, const clap_context_menu_target_t *target, clap_id action_id);

        const clap_plugin_context_menu_t MPlugExtContextMenu
        {
            .populate = context_menu_populate_callback,
            .perform  = context_menu_perform_callback
        };

    private: // host

        static bool context_menu_populate_callback(const clap_host_t *host, const clap_context_menu_target_t *target, const clap_context_menu_builder_t *builder);
        static bool context_menu_perform_callback(const clap_host_t *host, const clap_context_menu_target_t *target, clap_id action_id);
        static bool context_menu_can_popup_callback(const clap_host_t *host);
        static bool context_menu_popup_callback(const clap_host_t *host, const clap_context_menu_target_t *target, int32_t screen_index, int32_t x, int32_t y);

        clap_host_context_menu_t MHostExtContextMenu
        {
            .populate   = context_menu_populate_callback,
            .perform    = context_menu_perform_callback,
            .can_popup  = context_menu_can_popup_callback,
            .popup      = context_menu_popup_callback
        };

};

//----------------------------------------------------------------------
//
// plugin
//
//----------------------------------------------------------------------

bool SAT_ClapContextMenu::context_menu_populate_callback(const clap_plugin_t *plugin, const clap_context_menu_target_t  *target, const clap_context_menu_builder_t *builder) {
    SAT_ClapPlugin* p = (SAT_ClapPlugin*)plugin->plugin_data;
    return p->context_menu_populate(target,builder);
}

bool SAT_ClapContextMenu::context_menu_perform_callback(const clap_plugin_t *plugin, const clap_context_menu_target_t *target, clap_id action_id) {
    SAT_ClapPlugin* p = (SAT_ClapPlugin*)plugin->plugin_data;
    return p->context_menu_perform(target,action_id);
}

//----------------------------------------------------------------------
//
// host
//
//----------------------------------------------------------------------

bool SAT_ClapContextMenu::context_menu_populate_callback(const clap_host_t *host, const clap_context_menu_target_t *target, const clap_context_menu_builder_t *builder)
{
    SAT_ClapHost* h = (SAT_ClapHost*)host->host_data;
    return h->context_menu_populate(target,builder);
}

bool SAT_ClapContextMenu::context_menu_perform_callback(const clap_host_t *host, const clap_context_menu_target_t *target, clap_id action_id)
{
    SAT_ClapHost* h = (SAT_ClapHost*)host->host_data;
    return h->context_menu_perform(target,action_id);
}

bool SAT_ClapContextMenu::context_menu_can_popup_callback(const clap_host_t *host)
{
    SAT_ClapHost* h = (SAT_ClapHost*)host->host_data;
    return h->context_menu_can_popup();
}

bool SAT_ClapContextMenu::context_menu_popup_callback(const clap_host_t *host, const clap_context_menu_target_t *target, int32_t screen_index, int32_t x, int32_t y)
{
    SAT_ClapHost* h = (SAT_ClapHost*)host->host_data;
    return h->context_menu_popup(target,screen_index,x,y);
}

