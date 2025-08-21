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

class SAT_ClapResourceDirectory
: public SAT_ClapExtension
{
    public:

        const char* getId() final       { return CLAP_EXT_RESOURCE_DIRECTORY; }
        const void* getPtr() final      { return &MPlugExtResourceDirectory; }
        const void* getHostPtr() final  { return &MHostExtResourceDirectory; }

    private: // plugin

        static void     resource_directory_set_directory_callback(const clap_plugin_t *plugin, const char *path, bool is_shared);
        static void     resource_directory_collect_callback(const clap_plugin_t *plugin, bool all);
        static uint32_t resource_directory_get_files_count_callback(const clap_plugin_t *plugin);
        static int32_t  resource_directory_get_file_path_callback(const clap_plugin_t *plugin, uint32_t index, char *path, uint32_t path_size);

        const clap_plugin_resource_directory_t MPlugExtResourceDirectory
        {
            .set_directory    = resource_directory_set_directory_callback,
            .collect          = resource_directory_collect_callback,
            .get_files_count  = resource_directory_get_files_count_callback,
            .get_file_path    = resource_directory_get_file_path_callback
        };
  
      private: // host

        static bool resource_directory_request_directory_callback(const clap_host_t *host, bool is_shared);
        static void resource_directory_release_directory_callback(const clap_host_t *host, bool is_shared);

        clap_host_resource_directory_t MHostExtResourceDirectory
        {
            .request_directory  = resource_directory_request_directory_callback,
            .release_directory  = resource_directory_release_directory_callback
        };        

};

//----------------------------------------------------------------------
//
// plugin
//
//----------------------------------------------------------------------

void SAT_ClapResourceDirectory::resource_directory_set_directory_callback(const clap_plugin_t *plugin, const char *path, bool is_shared)
{
    SAT_ClapPlugin* p = (SAT_ClapPlugin*)plugin->plugin_data;
    p->resource_directory_set_directory(path,is_shared);
}

void SAT_ClapResourceDirectory::resource_directory_collect_callback(const clap_plugin_t *plugin, bool all)
{
    SAT_ClapPlugin* p = (SAT_ClapPlugin*)plugin->plugin_data;
    p->resource_directory_collect(all);
}

uint32_t SAT_ClapResourceDirectory::resource_directory_get_files_count_callback(const clap_plugin_t *plugin)
{
    SAT_ClapPlugin* p = (SAT_ClapPlugin*)plugin->plugin_data;
    return p->resource_directory_get_files_count();
}

int32_t SAT_ClapResourceDirectory::resource_directory_get_file_path_callback(const clap_plugin_t *plugin, uint32_t index, char *path, uint32_t path_size)
{
    SAT_ClapPlugin* p = (SAT_ClapPlugin*)plugin->plugin_data;
    return p->resource_directory_get_file_path(index,path,path_size);
}

//----------------------------------------------------------------------
//
// host
//
//----------------------------------------------------------------------

bool SAT_ClapResourceDirectory::resource_directory_request_directory_callback(const clap_host_t *host, bool is_shared)
{
    SAT_ClapHost* h = (SAT_ClapHost*)host->host_data;
    return h->resource_directory_request_directory(is_shared);
}

void SAT_ClapResourceDirectory::resource_directory_release_directory_callback(const clap_host_t *host, bool is_shared)
{
    SAT_ClapHost* h = (SAT_ClapHost*)host->host_data;
    h->resource_directory_release_directory(is_shared);
}
