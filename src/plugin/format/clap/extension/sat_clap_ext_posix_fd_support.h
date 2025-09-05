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

class SAT_ClapPosixFdSupport
: public SAT_ClapExtension
{
    public:

        const char* getId() final       { return CLAP_EXT_POSIX_FD_SUPPORT; }
        const void* getPtr() final      { return &MPlugExtPosixFdSupport; }
        const void* getHostPtr() final  { return &MHostExtPosixFdSupport; }

    private: // plugin

        static void posix_fd_support_on_fd_callback(const clap_plugin_t *plugin, int fd, clap_posix_fd_flags_t flags);

        const clap_plugin_posix_fd_support_t MPlugExtPosixFdSupport
        {
            .on_fd = posix_fd_support_on_fd_callback
        };        

    private: // host

        static bool posix_fd_support_register_fd_callback(const clap_host_t *host, int fd, clap_posix_fd_flags_t flags);
        static bool posix_fd_support_modify_fd_callback(const clap_host_t *host, int fd, clap_posix_fd_flags_t flags);
        static bool posix_fd_support_unregister_fd_callback(const clap_host_t *host, int fd);

        clap_host_posix_fd_support_t MHostExtPosixFdSupport
        {
            .register_fd    = posix_fd_support_register_fd_callback,
            .modify_fd      = posix_fd_support_modify_fd_callback,
            .unregister_fd  = posix_fd_support_unregister_fd_callback
        };        

};

//----------------------------------------------------------------------
//
// plugin
//
//----------------------------------------------------------------------

void SAT_ClapPosixFdSupport::posix_fd_support_on_fd_callback(const clap_plugin_t *plugin, int fd, clap_posix_fd_flags_t flags)
{
    SAT_ClapPlugin* p = (SAT_ClapPlugin*)plugin->plugin_data;
    p->posix_fd_support_on_fd(fd,flags);
}

//----------------------------------------------------------------------
//
// host
//
//----------------------------------------------------------------------

bool SAT_ClapPosixFdSupport::posix_fd_support_register_fd_callback(const clap_host_t *host, int fd, clap_posix_fd_flags_t flags)
{
    SAT_ClapHost* h = (SAT_ClapHost*)host->host_data;
    return h->posix_fd_support_register_fd(fd,flags);
}

bool SAT_ClapPosixFdSupport::posix_fd_support_modify_fd_callback(const clap_host_t *host, int fd, clap_posix_fd_flags_t flags)
{
    SAT_ClapHost* h = (SAT_ClapHost*)host->host_data;
    return h->posix_fd_support_modify_fd(fd,flags);
}

bool SAT_ClapPosixFdSupport::posix_fd_support_unregister_fd_callback(const clap_host_t *host, int fd)
{
    SAT_ClapHost* h = (SAT_ClapHost*)host->host_data;
    return h->posix_fd_support_unregister_fd(fd);
}
