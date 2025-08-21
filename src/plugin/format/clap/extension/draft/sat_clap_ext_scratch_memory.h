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

class SAT_ClapScratchMemory
: public SAT_ClapExtension
{
    public:

        const char* getId() final       { return CLAP_EXT_SCRATCH_MEMORY; }
        const void* getHostPtr() final  { return &MHostExtScratchMemory; }

    private: // host

        static bool     scratch_memory_reserve_callback(const clap_host_t *host, uint32_t scratch_size_bytes, uint32_t max_concurrency_hint);
        static void*    scratch_memory_access_callback(const clap_host_t *host);

        const clap_host_scratch_memory_t MHostExtScratchMemory
        {
            .reserve    = scratch_memory_reserve_callback,
            .access     = scratch_memory_access_callback
        };

};

//----------------------------------------------------------------------
//
// host
//
//----------------------------------------------------------------------

bool SAT_ClapScratchMemory::scratch_memory_reserve_callback(const clap_host_t *host, uint32_t scratch_size_bytes, uint32_t max_concurrency_hint)
{
    SAT_ClapHost* h = (SAT_ClapHost*)host->host_data;
    return h->scratch_memory_reserve(scratch_size_bytes,max_concurrency_hint);
}

void* SAT_ClapScratchMemory::scratch_memory_access_callback(const clap_host_t *host)
{
    SAT_ClapHost* h = (SAT_ClapHost*)host->host_data;
    return h->scratch_memory_access();
}
