#pragma once

#include "base/sat_base.h"
#include "base/system/sat_paths.h"
#include "plugin/sat_plugin.h"
#include "plugin/wrapper/exe/sat_exe_host.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

char            MPath[SAT_MAX_PATH_LENGTH]  = {0};
SAT_ExeHost*    MHost                       = nullptr;
SAT_Plugin*     MPlugin;
uint32_t        MPluginIndex                = 0;
SAT_ExeWindow*  MEditorWindow               = nullptr;
uint32_t        MEditorWidth                = 0;
uint32_t        MEditorHeight               = 0;

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

void parse_args(int argc, char** argv)
{
    MPluginIndex = 0;
}

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

int main(int argc, char** argv)
{
    // setup
    parse_args(argc,argv);
    const char* path = SAT_GetExePath(MPath);
    SAT_PRINT("path: %s\n",path);
    MHost = new SAT_ExeHost();
    // start audio/midi
    // load plugin
    // open editor
    // mainloop
    // close editor
    // unload plugin
    // stop audio/midi
    delete MHost;
    // cleanup
}
