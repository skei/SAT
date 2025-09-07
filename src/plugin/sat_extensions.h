#pragma once

#include "base/sat_base.h"
#include "plugin/clap/sat_clap_extensions.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_Extensions
{
    public:
        SAT_Extensions();
        ~SAT_Extensions();
    public:
        void        append(SAT_ClapExtension* AExtension, bool AReplace=true);
        //void        remove(uint32_t AIndex, bool ARemove=true);
        void        remove(uint32_t AIndex, bool ADelete=true);
        void        deleteAll();
        const void* find(const char* AName);
        int32_t     findIndex(const char* AName);
    private:
        SAT_ExtensionArray  MExtensions = {};


};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

SAT_Extensions::SAT_Extensions()
{
}

SAT_Extensions::~SAT_Extensions()
{
    #ifndef SAT_NO_AUTODELETE
        deleteAll();
    #endif
}

//------------------------------
//
//------------------------------

void SAT_Extensions::append(SAT_ClapExtension* AExtension, bool AReplace)
{
    SAT_Assert(AExtension);
    // AExtension->setStatic(false);
    int32_t index = findIndex(AExtension->getId());
    if ((index >= 0) && AReplace)
    {
        remove(index,false);
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

// void SAT_Extensions::appendStatic(SAT_ClapExtension* AExtension, bool AReplace)
// {
//     SAT_Assert(AExtension);
//     append(AExtension,AReplace);
//     AExtension->setStatic(true); // override static
// }

/*
    if specified extension exisis (not null), and not registered
    as static, it will be deleted.
    if ARemove is true, the MExtension array will shrink,
    otherwise the pointer will be set to NULL
*/

// void SAT_Extensions::remove(uint32_t AIndex, bool ARemove)
// {
//     SAT_ClapExtension* ext = MExtensions[AIndex];
//     if (ext) delete ext;
//     if (ARemove) MExtensions.remove(AIndex);
// }

void SAT_Extensions::remove(uint32_t AIndex, bool ADelete)
{
    SAT_ClapExtension* ext = MExtensions[AIndex];
    if (ext)
    {
        MExtensions.remove(AIndex);        
        if (ADelete) delete ext;
    }
}

/*
    delete all registered and existing (not null) extensions
    (unless the extension is registered as static)
*/

void SAT_Extensions::deleteAll()
{
    uint32_t num = MExtensions.size();
    for (uint32_t i=0; i<num; i++)
    {
        SAT_ClapExtension* ext = MExtensions[i];
        if (ext) delete ext;
    }
    MExtensions.clear();
}

/*
    returns pointer to extension struct if it is registered,
    else return null
    looks at both the regular extension id, and the _compat version
*/

const void* SAT_Extensions::find(const char* AName)
{
    int32_t index = findIndex(AName);
    if (index >= 0) return  MExtensions[index]->getPtr();
    else return nullptr;
}

/*
    returns extension index (into MExtensions) if it is registered,
    else return -1
    looks at both the regular extension id, and the _compat version
*/

int32_t SAT_Extensions::findIndex(const char* AName)
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
