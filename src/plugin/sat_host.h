#pragma once

#include "base/sat_base.h"
#include "plugin/clap/sat_clap_extensions.h"
#include "plugin/clap/sat_clap_host.h"

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

    public: // extensions

        void                registerExtension(SAT_ClapExtension* AExtension, bool AReplace=true);
        void                registerStaticExtension(SAT_ClapExtension* AExtension, bool AReplace=true);
        void                deleteExtension(uint32_t AIndex, bool ARemove=true);
        void                deleteAllExtensions();
        const void*         findExtension(const char* AName);
        int32_t             findExtensionIndex(const char* AName);

    private:

        SAT_ExtensionArray  MExtensions     = {};

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
}

//------------------------------
//
//------------------------------

const void* SAT_Host::get_extension(const char *extension_id)
{
    return nullptr;
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
// extensions
//------------------------------

/*
    register an extension
    if it already exists, and AReplace is true, it will be replaced
    (the previous one will be deleted, unless it's static)
    if it foesn't exist, it will be appended
    it will be deleted automatically in the SAT_Plugin destructor
*/

void SAT_Host::registerExtension(SAT_ClapExtension* AExtension, bool AReplace)
{
    SAT_Assert(AExtension);
    AExtension->setStatic(false);
    int32_t index = findExtensionIndex(AExtension->getId());
    if ((index >= 0) && AReplace)
    {
        deleteExtension(index,false);
        MExtensions[index] = AExtension;
    }
    else MExtensions.append(AExtension);
}

/*
    register an extension
    if it already exists, and APreplace is true, it will be replaced
    (the previous one will be deleted, unless it's static)
    if it doesn't exist, it will be appended
    it will NOT be deleted automatically in the SAT_Plugin destructor
*/

void SAT_Host::registerStaticExtension(SAT_ClapExtension* AExtension, bool AReplace)
{
    SAT_Assert(AExtension);
    registerExtension(AExtension,AReplace);
    AExtension->setStatic(true); // override static
}

/*
    if specified extension exisis (not null), and not registered
    as static, it will be deleted.
    if ARemove is true, the MExtension array will shrink,
    otherwise the pointer will be set to NULL
*/

void SAT_Host::deleteExtension(uint32_t AIndex, bool ARemove)
{
    SAT_ClapExtension* ext = MExtensions[AIndex];
    if ((ext && !ext->isStatic())) delete ext;
    if (ARemove) MExtensions.remove(AIndex);
}

/*
    delete all registered and existing (not null) extensions
    (unless the extension is registered as static)
*/

void SAT_Host::deleteAllExtensions()
{
    uint32_t num = MExtensions.size();
    for (uint32_t i=0; i<num; i++)
    {
        SAT_ClapExtension* ext = MExtensions[i];
        if ((ext) && (!ext->isStatic()))
        {
            delete ext;
        }
    }
    MExtensions.clear();
}

/*
    returns pointer to extension struct if it is registered,
    else return null
    looks at both the regular extension id, and the _compat version
*/

const void* SAT_Host::findExtension(const char* AName)
{
    int32_t index = findExtensionIndex(AName);
    if (index >= 0) return  MExtensions[index]->getPtr();
    else return nullptr;
}

/*
    returns extension index (into MExtensions) if it is registered,
    else return -1
    looks at both the regular extension id, and the _compat version
*/

int32_t SAT_Host::findExtensionIndex(const char* AName)
{
    uint32_t num = MExtensions.size();
    for (uint32_t i=0; i<num; i++)
    {
        SAT_ClapExtension* ext = MExtensions[i];
        if (ext)
        {
            const char* id = ext->getId();
            if (id && SAT_IsEqual(AName,id)) return i;
            else
            {
                id = MExtensions[i]->getCompatId();
                if (id && SAT_IsEqual(AName,id)) return i;
            }
        }
    }
    return -1;
}
