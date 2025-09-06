#pragma once

#include "base/sat_base.h"
//#include "plugin/clap/sat_clap_extensions.h"
#include "plugin/clap/sat_clap_host.h"
#include "plugin/sat_extensions.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_Host
: public SAT_ClapHost
{
    public:
        SAT_Host();
        virtual ~SAT_Host();

    public: // clap host

        const void*  get_extension(const char *extension_id) override;
        void         request_restart() override;
        void         request_process() override;
        void         request_callback() override;

    public: // clap host extensions

    public:

        SAT_Extensions  Extensions     = {};

};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

SAT_Host::SAT_Host()
: SAT_ClapHost()
{
    // MClapHost.name      = "SAT_Host";
    // MClapHost.vendor    = "skei.audio";
    // MClapHost.url       = "https://github.com/skei/SAT";
    // MClapHost.version   = "0.0.0";
}
SAT_Host::~SAT_Host()
{
    #ifndef SAT_NO_AUTODELETE
        Extensions.deleteAll();
    #endif
}

//------------------------------
// clap host
//------------------------------

const void* SAT_Host::get_extension(const char *extension_id)
{
    SAT_Assert(extension_id);
    return Extensions.find(extension_id);
}

void SAT_Host::request_restart()
{
}

void SAT_Host::request_process()
{
}

void SAT_Host::request_callback()
{
}

//------------------------------
// clap host extensions
//------------------------------

