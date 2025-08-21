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

class SAT_ClapThreadPool
: public SAT_ClapExtension
{
    public:

        const char* getId() final       { return CLAP_EXT_THREAD_POOL; }
        const void* getPtr() final      { return &MPlugExtThreadPool; }
        const void* getHostPtr() final  { return &MHostExtThreadPool; }

    private: // plugin

        static void thread_pool_exec_callback(const clap_plugin_t *plugin, uint32_t task_index);

        const clap_plugin_thread_pool_t MPlugExtThreadPool
        {
            .exec = thread_pool_exec_callback
        };        

    private: // host

        static bool thread_pool_request_exec_callback(const clap_host_t *host, uint32_t num_tasks);

        clap_host_thread_pool_t MHostExtThreadPool
        {
            .request_exec  = thread_pool_request_exec_callback
        };        

};

//----------------------------------------------------------------------
//
// plugin
//
//----------------------------------------------------------------------

void SAT_ClapThreadPool::thread_pool_exec_callback(const clap_plugin_t *plugin, uint32_t task_index)
{
    SAT_ClapPlugin* p = (SAT_ClapPlugin*)plugin->plugin_data;
    p->thread_pool_exec(task_index);
}

//----------------------------------------------------------------------
//
// host
//
//----------------------------------------------------------------------

bool SAT_ClapThreadPool::thread_pool_request_exec_callback(const clap_host_t *host, uint32_t num_tasks)
{
    SAT_ClapHost* h = (SAT_ClapHost*)host->host_data;
    return h->thread_pool_request_exec(num_tasks);
}
