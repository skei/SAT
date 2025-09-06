#pragma once

#include "base/sat_base.h"
#include "extern/plugin/sat_clap.h"

class SAT_ClapExtension;
typedef SAT_Array<SAT_ClapExtension*> SAT_ExtensionArray;

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_ClapExtension
{
    friend class SAT_Host;
    friend class SAT_Plugin;
    friend class SAT_Extensions;

    public:
        SAT_ClapExtension() {}
        virtual ~SAT_ClapExtension() {}
    public:
        virtual const char* getId()                         { return nullptr; }         // "CLAP_EXT_*"; }
        virtual const char* getCompatId()                   { return nullptr; }         // "CLAP_EXT_*_COPMPAT"; }
        virtual const void* getPtr()                        { return nullptr; }         // plugin side struct
        virtual const void* getHostPtr()                    { return nullptr; }         // host side struct
    // private:
    //     void                setStatic(bool AIsStatic=true)  { MIsStatic = AIsStatic; }
    //     bool                isStatic()                      { return MIsStatic; }       
    // private:
    //     bool                MIsStatic = false; // if false, extension will be deleted in plugin destructor?
};
