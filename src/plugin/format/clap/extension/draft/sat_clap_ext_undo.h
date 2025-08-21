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

class SAT_ClapUndo
: public SAT_ClapExtension
{
    public:

        const char* getId() final       { return CLAP_EXT_UNDO; }
        const void* getHostPtr() final  { return &MHostExtUndo; }

    private: // host

        static void undo_begin_change_callback(const clap_host_t *host);
        static void undo_cancel_change_callback(const clap_host_t *host);
        static void undo_change_made_callback(const clap_host_t *host, const char* name, const void* delta, size_t delta_size, bool delta_can_undo);
        static void undo_request_undo_callback(const clap_host_t *host);
        static void undo_request_redo_callback(const clap_host_t *host);
        static void undo_set_wants_context_updates_callback(const clap_host_t *host, bool is_subscribed);

        const clap_host_undo_t MHostExtUndo
        {
            .begin_change               = undo_begin_change_callback,
            .cancel_change              = undo_cancel_change_callback,
            .change_made                = undo_change_made_callback,
            .request_undo               = undo_request_undo_callback,
            .request_redo               = undo_request_redo_callback,
            .set_wants_context_updates  = undo_set_wants_context_updates_callback

        };

};

//----------------------------------------------------------------------
//
// host
//
//----------------------------------------------------------------------

void SAT_ClapUndo::undo_begin_change_callback(const clap_host_t *host)
{
    SAT_ClapHost* h = (SAT_ClapHost*)host->host_data;
    h->undo_begin_change();
}

void SAT_ClapUndo::undo_cancel_change_callback(const clap_host_t *host)
{
    SAT_ClapHost* h = (SAT_ClapHost*)host->host_data;
    h->undo_cancel_change();
}

void SAT_ClapUndo::undo_change_made_callback(const clap_host_t *host, const char* name, const void* delta, size_t delta_size, bool delta_can_undo)
{
    SAT_ClapHost* h = (SAT_ClapHost*)host->host_data;
    h->undo_change_made(name,delta,delta_size,delta_can_undo);
}

void SAT_ClapUndo::undo_request_undo_callback(const clap_host_t *host)
{
    SAT_ClapHost* h = (SAT_ClapHost*)host->host_data;
    h->undo_request_undo();
}

void SAT_ClapUndo::undo_request_redo_callback(const clap_host_t *host)
{
    SAT_ClapHost* h = (SAT_ClapHost*)host->host_data;
    h->undo_request_redo();
}

void SAT_ClapUndo::undo_set_wants_context_updates_callback(const clap_host_t *host, bool is_subscribed)
{
    SAT_ClapHost* h = (SAT_ClapHost*)host->host_data;
    h->undo_set_wants_context_updates(is_subscribed);
}
