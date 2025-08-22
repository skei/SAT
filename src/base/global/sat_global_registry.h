#pragma once

#include "base/sat_base.h"
#include "base/global/sat_global_base.h"
#include "base/util/sat_strutils.h"

#include "extern/plugin/clap/clap.h"
#include "plugin/format/clap/sat_clap_factory.h"

#ifdef SAT_INCLUDE_REGISTRY
    class SAT_GlobalRegistry;
    class SAT_ClapPlugin;
    extern void SAT_Register(SAT_GlobalRegistry* ARegistry) __SAT_WEAK;
    extern SAT_ClapPlugin* SAT_CreatePlugin(int32_t AIndex, const clap_plugin_descriptor_t* ADescriptor, const clap_host_t* AHost) __SAT_WEAK;
#endif

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_GlobalRegistry
{

    typedef SAT_Array<const clap_plugin_descriptor_t*> SAT_ClapDescriptorArray;
    typedef SAT_Array<SAT_ClapFactory*> SAT_ClapFactoryArray;

    public:

        SAT_GlobalRegistry();
        ~SAT_GlobalRegistry();

        void activate(SAT_GlobalBase* AGlobal);
        void deactivate(SAT_GlobalBase* AGlobal);
        void setBinaryPath(const char* APath);

    public: // descriptors

        #ifdef SAT_INCLUDE_REGISTRY
            void                            registerDescriptor(const clap_plugin_descriptor_t* ADescriptor);
            void                            deleteDescriptors();
            void                            setStaticDescriptors(bool AState=true);
            uint32_t                        getNumDescriptors();
            const clap_plugin_descriptor_t* getDescriptor(uint32_t AIndex);
            int32_t                         findDescriptor(const char* AId);
        #endif

    public: // factories

        #ifdef SAT_INCLUDE_REGISTRY
            void                            registerFactory(SAT_ClapFactory* AFactory);
            void                            deleteFactories();
            void                            setStaticFactories(bool AState=true);
            uint32_t                        getNumFactories();
            const void*                     getFactory(uint32_t AIndex);
            int32_t                         findFactory(const char* AId);
        #endif

    private:

        bool                    MIsActivated                        = false;
        SAT_GlobalBase*         MGlobal                             = nullptr;
        char                    MBinaryPath[SAT_MAX_PATH_LENGTH]    = {0};

        #ifdef SAT_INCLUDE_REGISTRY
            bool MStaticDescriptors                                 = true;     // default is static descriptors
            bool MStaticFactories                                   = false;    // default is allocated factories
            SAT_ClapDescriptorArray MDescriptors                    = {};
            SAT_ClapFactoryArray    MFactories                      = {};
        #endif
};

//----------------------------------------------------------------------
//
// implementation
//
//----------------------------------------------------------------------

SAT_GlobalRegistry::SAT_GlobalRegistry()
{
}

SAT_GlobalRegistry::~SAT_GlobalRegistry()
{
}

void SAT_GlobalRegistry::activate(SAT_GlobalBase* AGlobal)
{
    if (!MIsActivated)
    {
        MGlobal = AGlobal;
        #ifdef SAT_INCLUDE_REGISTRY
            if (SAT_Register) SAT_Register(this);
        #endif
        MIsActivated = true;
    }
}

void SAT_GlobalRegistry::deactivate(SAT_GlobalBase* AGlobal)
{
    if (MIsActivated)
    {
        #ifdef SAT_INCLUDE_REGISTRY
            if (!MStaticDescriptors) deleteDescriptors();
            if (!MStaticFactories) deleteFactories();
        #endif
        MGlobal = nullptr;
        MIsActivated = false;
    }
}

void SAT_GlobalRegistry::setBinaryPath(const char* APath)
{
    SAT_Strlcpy(MBinaryPath,APath,SAT_MAX_PATH_LENGTH);
}

//------------------------------
// descriptors
//------------------------------

#ifdef SAT_INCLUDE_REGISTRY    

    void SAT_GlobalRegistry::registerDescriptor(const clap_plugin_descriptor_t* ADescriptor)
    {
        // SAT_GLOBAL_PRINT("registerDescriptor: \"%s\"\n",ADescriptor->id);
        MDescriptors.append(ADescriptor);
    }

    void SAT_GlobalRegistry::deleteDescriptors()
    {
        // SAT_GLOBAL_PRINT("deleteDescriptors\n");
        uint32_t num = MDescriptors.size();
        for (uint32_t i=0; i<num; i++)
        {
            delete MDescriptors[i];
        }
    }

    void SAT_GlobalRegistry::setStaticDescriptors(bool AStatic)
    {
        MStaticDescriptors = AStatic;
    }

    uint32_t SAT_GlobalRegistry::getNumDescriptors()
    {
        return MDescriptors.size();
    }

    const clap_plugin_descriptor_t* SAT_GlobalRegistry::getDescriptor(uint32_t AIndex)
    {
        return MDescriptors[AIndex];
    }

    int32_t SAT_GlobalRegistry::findDescriptor(const char* AId)
    {
        uint32_t num = MDescriptors.size();
        for (uint32_t i=0; i<num; i++)
        {
            //if (strcmp(AId,MDescriptors[i]->id) == 0) return i;
            if (SAT_IsEqual(AId,MDescriptors[i]->id)) return i;
        }
        return -1;
    }

#endif // SAT_INCLUDE_REGISTRY    

//------------------------------
// factories
//------------------------------

#ifdef SAT_INCLUDE_REGISTRY    

    void SAT_GlobalRegistry::registerFactory(SAT_ClapFactory* AFactory)
    {
        // SAT_GLOBAL_PRINT("registerFactory: \"%s\"\n",AFactory->getId());
        MFactories.append(AFactory);
    }

    void SAT_GlobalRegistry::deleteFactories()
    {
        // SAT_GLOBAL_PRINT("deleteFactories\n");
        uint32_t num = MFactories.size();
        for (uint32_t i=0; i<num; i++)
        {
            delete MFactories[i];
        }
    }

    void SAT_GlobalRegistry::setStaticFactories(bool AStatic)
    {
        MStaticFactories = AStatic;
    }

    uint32_t SAT_GlobalRegistry::getNumFactories()
    {
        return MFactories.size();
    }

    const void* SAT_GlobalRegistry::getFactory(uint32_t AIndex)
    {
        return MFactories[AIndex]->getPtr();
    }

    int32_t SAT_GlobalRegistry::findFactory(const char* AId)
    {
        uint32_t num = MFactories.size();
        for (uint32_t i=0; i<num; i++)
        {
            const char* factory_id = MFactories[i]->getId();
            //if (strcmp(AId,factory_id) == 0)
            if (SAT_IsEqual(AId,factory_id))
            {
                return i;
            }
        }
        return -1;
    }

#endif

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

#if 0

#ifdef SAT_INCLUDE_REGISTRY

    #include "plugin/sat_entry.h"                                                                                               \
                                                                                                                                \
    #define SAT_SIMPLE_PLUGIN_ENTRY(DESC,PLUG)                                                                                  \
                                                                                                                                \
        void SAT_Register(SAT_GlobalRegistry* ARegistry)                                                                        \
        {                                                                                                                       \
            ARegistry->registerDescriptor(&DESC);                                                                               \
        }                                                                                                                       \
                                                                                                                                \
        SAT_ClapPlugin* SAT_CreatePlugin(int32_t AIndex, const clap_plugin_descriptor_t* ADescriptor, const clap_host_t* AHost) \
        {                                                                                                                       \
            if (AIndex == 0) {                                                                                                  \
                SAT_Plugin* plugin = new PLUG(ADescriptor,AHost);                                                               \
                return plugin;                                                                                                  \
            }                                                                                                                   \
            return nullptr;                                                                                                     \
        }

#endif

#endif // 0