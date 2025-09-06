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

class SAT_ClapLog
: public SAT_ClapExtension
{
    public:

        const char* getId() final       { return CLAP_EXT_LOG; }
        const void* getHostPtr() final  { return &MHostExtLog; }

    private: // host

        static void log_log_callback(const clap_host_t *host, clap_log_severity severity, const char *msg);

        clap_host_log_t MHostExtLog
        {
            .log  = log_log_callback
        };        

};

//----------------------------------------------------------------------
//
// host
//
//----------------------------------------------------------------------

void SAT_ClapLog::log_log_callback(const clap_host_t *host, clap_log_severity severity, const char *msg)
{
    SAT_ClapHost* h = (SAT_ClapHost*)host->host_data;
    h->log_log(severity,msg);
}
