// host, as seen from a plugin

#include "base/sat_base.h"
#include "extern/plugin/sat_clap.h"
#include "plugin/clap/sat_clap_host_proxy.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_HostProxy
: public SAT_ClapHostProxy
{
    public:
        SAT_HostProxy(const clap_host_t* AHost);
        virtual ~SAT_HostProxy();
};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

SAT_HostProxy::SAT_HostProxy(const clap_host_t* AHost)
: SAT_ClapHostProxy(AHost)
{
    setupExtensions();
}

SAT_HostProxy::~SAT_HostProxy()
{
}

//------------------------------
//
//------------------------------
