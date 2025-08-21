#pragma once

#include "base/sat_base.h"
#include "plugin/format/clap/sat_clap.h"

// #include "plugin/format/clap/sat_clap_plugin.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_ClapExtension
{
    friend class SAT_Plugin;

    public:
        SAT_ClapExtension() {}
        virtual ~SAT_ClapExtension() {}
    public:
        virtual const char* getId()                         { return nullptr; }         // "CLAP_EXT_*"; }
        virtual const char* getCompatId()                   { return nullptr; }         // "CLAP_EXT_*_COPMPAT"; }
        virtual const void* getPtr()                        { return nullptr; }         // plugin side struct
        virtual const void* getHostPtr()                    { return nullptr; }         // host side struct
    private:
        void                setStatic(bool AIsStatic=true)  { MIsStatic = AIsStatic; }
        bool                isStatic()                      { return MIsStatic; }       
    private:
        bool                MIsStatic = false; // if false, extension will be deleted in plugin destructor?
};
