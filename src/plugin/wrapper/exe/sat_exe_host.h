#pragma once

#include "base/sat_base.h"
#include "plugin/sat_host.h"
#include "plugin/wrapper/exe/sat_exe_window.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_ExeHost
: public SAT_Host
{
    public:
        SAT_ExeHost();
        virtual ~SAT_ExeHost();
    public:
      //uint32_t entry(const char* APath);
    protected:
      //SAT_ExeWindow*  MWindow = nullptr;
};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

SAT_ExeHost::SAT_ExeHost()
: SAT_Host()
{
}

SAT_ExeHost::~SAT_ExeHost()
{
}

//------------------------------
//
//------------------------------

// uint32_t SAT_ExeHost::entry(const char* APath)
// {
//     return 1;
// }

