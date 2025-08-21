#pragma once

#include "base/sat_base.h"
#include "plugin/sat_entry.h"
#include "plugin/format/clap/sat_clap.h"
#include "plugin/format/clap/sat_clap_plugin.h"
#include "plugin/format/clap/sat_clap_extensions.h"

typedef SAT_Array<SAT_ClapExtension*> SAT_ClapExtensionArray;

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_Plugin
: public SAT_ClapPlugin
{
    public:

        SAT_Plugin(const clap_plugin_descriptor_t* ADescriptor, const clap_host_t* AHost);
        virtual ~SAT_Plugin();

    public: // clap plugin

        bool                init() override;
        void                destroy() override;
        bool                activate(double sample_rate, uint32_t min_frames_count, uint32_t max_frames_count) override;
        void                deactivate() override;
        bool                start_processing() override;
        void                stop_processing() override;
        void                reset() override;
        clap_process_status process(const clap_process_t *process) override;
        const void*         get_extension(const char *id) override;
        void                on_main_thread() override;

    public: // extensions

        void                registerExtension(SAT_ClapExtension* AExtension, bool AReplace=true);
        void                registerStaticExtension(SAT_ClapExtension* AExtension, bool AReplace=true);
        void                deleteExtension(uint32_t AIndex, bool ARemove=true);
        void                deleteAllExtensions();
        const void*         findExtension(const char* AName);
        int32_t             findExtensionIndex(const char* AName);

    private:

        // bool                    MStaticExtensions   = false;
        SAT_ClapExtensionArray  MExtensions         = {};

};

//----------------------------------------------------------------------
//
// implementation
//
//----------------------------------------------------------------------

SAT_Plugin::SAT_Plugin(const clap_plugin_descriptor_t* ADescriptor, const clap_host_t* AHost)
: SAT_ClapPlugin(ADescriptor,AHost)
{
}

SAT_Plugin::~SAT_Plugin()
{
    #ifndef SAT_NO_AUTODELETE
        deleteAllExtensions();
    #endif
}

//------------------------------
// clap plugin
//------------------------------

bool SAT_Plugin::init()
{
    return true;
}

void SAT_Plugin::destroy()
{
}

bool SAT_Plugin::activate(double sample_rate, uint32_t min_frames_count, uint32_t max_frames_count)
{
    return true;
}

void SAT_Plugin::deactivate()
{
}

bool SAT_Plugin::start_processing()
{
    return true;
}

void SAT_Plugin::stop_processing()
{
}

void SAT_Plugin::reset()
{
}

clap_process_status SAT_Plugin::process(const clap_process_t *process)
{
    return CLAP_PROCESS_CONTINUE;
}

const void* SAT_Plugin::get_extension(const char *id)
{
    return findExtension(id);
}

void SAT_Plugin::on_main_thread()
{
}

//------------------------------
// clap extensions
//------------------------------

//..

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

void SAT_Plugin::registerExtension(SAT_ClapExtension* AExtension, bool AReplace)
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

void SAT_Plugin::registerStaticExtension(SAT_ClapExtension* AExtension, bool AReplace)
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

void SAT_Plugin::deleteExtension(uint32_t AIndex, bool ARemove)
{
    SAT_ClapExtension* ext = MExtensions[AIndex];
    if ((ext && !ext->isStatic())) delete ext;
    if (ARemove) MExtensions.remove(AIndex);
}

/*
    delete all registered and existing (not null) extensions
    (unless the extension is registered as static)
*/

void SAT_Plugin::deleteAllExtensions()
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

const void* SAT_Plugin::findExtension(const char* AName)
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

int32_t SAT_Plugin::findExtensionIndex(const char* AName)
{
    uint32_t num = MExtensions.size();
    for (uint32_t i=0; i<num; i++)
    {
        SAT_ClapExtension* ext = MExtensions[i];
        if (ext)
        {
            const char* id = ext->getId();
            if (id && (strcmp(AName,id) == 0)) return i;
            else
            {
                id = MExtensions[i]->getCompatId();
                if (id && (strcmp(AName,id) == 0)) return i;
            }
        }
    }
    return -1;
}


