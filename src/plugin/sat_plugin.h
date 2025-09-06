#pragma once

#include "base/sat_base.h"
#include "base/util/sat_strutils.h"
#include "extern/plugin/sat_clap.h"
#include "plugin/clap/sat_clap_extensions.h"
#include "plugin/clap/sat_clap_plugin.h"
#include "plugin/editor/sat_editor_listener.h"
#include "plugin/editor/sat_editor_owner.h"
#include "plugin/processor/sat_processor_listener.h"
#include "plugin/processor/sat_processor_owner.h"
#include "plugin/sat_audio_port.h"
#include "plugin/sat_editor.h"
#include "plugin/sat_host_proxy.h"
#include "plugin/sat_note_port.h"
#include "plugin/sat_parameter.h"
#include "plugin/sat_processor.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_Plugin
: public SAT_ClapPlugin
, public SAT_EditorOwner
, public SAT_EditorListener
, public SAT_ProcessorOwner
, public SAT_ProcessorListener
{
    public:

        SAT_Plugin(const clap_plugin_descriptor_t* ADescriptor, const clap_host_t* AHost);
        virtual ~SAT_Plugin();

    public:

        void                do_editor_listener_update_parameter(SAT_Parameter* AParameter, sat_param_t AValue) override;
        void                do_processor_listener_update_parameter(uint32_t AId, sat_param_t AValue) override;

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

    public: // clap plugin extensions

    public: // extensions

        void                registerExtension(SAT_ClapExtension* AExtension, bool AReplace=true);
        void                registerStaticExtension(SAT_ClapExtension* AExtension, bool AReplace=true);
        void                deleteExtension(uint32_t AIndex, bool ARemove=true);
        void                deleteAllExtensions();
        const void*         findExtension(const char* AName);
        int32_t             findExtensionIndex(const char* AName);

    public: // parameters

        void                appendParameter(SAT_Parameter* AParameter);
        void                deleteAllParameters();
        uint32_t            getNumParameters();
        SAT_Parameter*      getParameter(uint32_t AIndex);
        SAT_Parameter*      findParameter(uint32_t AId);
        SAT_Parameter*      findParameter(const char* AName, const char* AModule=nullptr);
        int32_t             findParameterIndex(uint32_t AId);
        int32_t             findParameterIndex(const char* AName, const char* AModule=nullptr);

    public: // presets
    
    public: // audio ports

        void                appendAudioPort(SAT_AudioPort* APort);
        void                deleteAllAudioPorts();
        uint32_t            getNumAudioPorts();
        SAT_AudioPort*      getAudioPort(uint32_t AIndex);

    public: // note ports

        void                appendNotePort(SAT_NotePort* APort);
        void                deleteAllNotePorts();
        uint32_t            getNumNotePorts();
        SAT_NotePort*       getNotePort(uint32_t AIndex);

    public: // editor

    public: // processor

        void                setProcessor(SAT_Processor* AProcessor);

    private:

        SAT_HostProxy*      MHost           = nullptr;
        uint32_t            MState          = SAT_PLUGIN_STATE_NONE;
        SAT_ExtensionArray  MExtensions     = {};
        SAT_ParameterArray  MParameters     = {};
      //SAT_PresetManager   MPresets        = {}
        SAT_AudioPortArray  MAudioPorts     = {};
        SAT_NotePortArray   MNotePorts      = {};
        SAT_Processor*      MProcessor      = {};
        SAT_Editor*         MEditor         = {};

};

//----------------------------------------------------------------------
//
// implementation
//
//----------------------------------------------------------------------

SAT_Plugin::SAT_Plugin(const clap_plugin_descriptor_t* ADescriptor, const clap_host_t* AHost)
: SAT_ClapPlugin(ADescriptor,AHost)
{
    MHost = new SAT_HostProxy(AHost);
}

SAT_Plugin::~SAT_Plugin()
{
    delete MHost;
    #ifndef SAT_NO_AUTODELETE
        deleteAllExtensions();
        deleteAllParameters();
    #endif
}

//------------------------------
//
//------------------------------

// editor owner

// editor listener
void SAT_Plugin::do_editor_listener_update_parameter(SAT_Parameter* AParameter, sat_param_t AValue)
{
}

// processor owner

// processor listener
void SAT_Plugin::do_processor_listener_update_parameter(uint32_t AId, sat_param_t AValue)
{
}

//------------------------------
// clap plugin
//------------------------------

bool SAT_Plugin::init()
{
    SAT_Assert(MState == SAT_PLUGIN_STATE_NONE);
    MState = SAT_PLUGIN_STATE_INITIALIZED;
    return true;
}

void SAT_Plugin::destroy()
{
    SAT_Assert(MState == SAT_PLUGIN_STATE_INITIALIZED);
    MState = SAT_PLUGIN_STATE_NONE;
}

bool SAT_Plugin::activate(double sample_rate, uint32_t min_frames_count, uint32_t max_frames_count)
{
    SAT_Assert(MState == SAT_PLUGIN_STATE_INITIALIZED);
    MState = SAT_PLUGIN_STATE_ACTIVATED;
    return true;
}

void SAT_Plugin::deactivate()
{
    SAT_Assert(MState == SAT_PLUGIN_STATE_ACTIVATED);
    MState = SAT_PLUGIN_STATE_INITIALIZED;
}

bool SAT_Plugin::start_processing()
{
    SAT_Assert(MState == SAT_PLUGIN_STATE_ACTIVATED);
    MState = SAT_PLUGIN_STATE_PROCESSING;
    return true;
}

void SAT_Plugin::stop_processing()
{
    SAT_Assert(MState == SAT_PLUGIN_STATE_PROCESSING);
    MState = SAT_PLUGIN_STATE_ACTIVATED;
}

void SAT_Plugin::reset()
{
}

clap_process_status SAT_Plugin::process(const clap_process_t *process)
{
    SAT_Assert(MState == SAT_PLUGIN_STATE_PROCESSING);
    return CLAP_PROCESS_CONTINUE;
}

const void* SAT_Plugin::get_extension(const char *id)
{
    SAT_Assert(MState == SAT_PLUGIN_STATE_INITIALIZED);
    return findExtension(id);
}

void SAT_Plugin::on_main_thread()
{
    //SAT_Assert(MState == SAT_PLUGIN_STATE_ACTIVATED);
    SAT_Assert(MState == SAT_PLUGIN_STATE_PROCESSING);
}

//------------------------------
// clap extensions
//------------------------------

// ...

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

//------------------------------
// parameters
//------------------------------

/*
    we are currently using index as id for performance reasons, so we don't have
    to search through all the parameters to find parameter with a certain id..
    parameter updates from clap uses id.. but we also get the cookie = ptr back
    to this class, so we could just look up the indedx from that!
    TODO: investigate.. does all hosts send the cookie? SAT_Assert(cookie)...
*/

void SAT_Plugin::appendParameter(SAT_Parameter* AParameter)
{
    SAT_Assert(AParameter);
    uint32_t index = MParameters.size();
    MParameters.append(AParameter);
    AParameter->setIndex(index);
    AParameter->setId(index);
}

void SAT_Plugin::deleteAllParameters()
{
    uint32_t num = MParameters.size();
    for (uint32_t i=0; i<num; i++)
    {
        if (MParameters[i])
        {
            delete MParameters[i];
            // MParameters[i] = nullptr;
        }
    }
    MParameters.clear();
}

uint32_t SAT_Plugin::getNumParameters()
{
    return MParameters.size();
}

SAT_Parameter* SAT_Plugin::getParameter(uint32_t AIndex)
{
    return MParameters[AIndex];
}

SAT_Parameter* SAT_Plugin::findParameter(uint32_t AId)
{
    int32_t index = findParameterIndex(AId);
    if (index >= 0) return MParameters[index];
    return nullptr;
}

SAT_Parameter* SAT_Plugin::findParameter(const char* AName, const char* AModule)
{
    int32_t index = findParameterIndex(AName,AModule);
    if (index >= 0) return MParameters[index];
    return nullptr;
}

int32_t SAT_Plugin::findParameterIndex(uint32_t AId)
{
    SAT_Assert(AId >= 0);
    SAT_Assert(AId < MParameters.size());
    //return MParameters[AId]->getIndex();
    uint32_t num = MParameters.size();
    for (uint32_t i=0; i<num; i++)
    {
        if (MParameters[i]->getId() == AId) return i;
    }
    return -1;
}

int32_t SAT_Plugin::findParameterIndex(const char* AName, const char* AModule)
{
    uint32_t num = MParameters.size();
    for (uint32_t i=0; i<num; i++)
    {
        const char* param_name = MParameters[i]->getName();
        if (param_name && SAT_IsEqual(param_name,AName))
        {
            if (AModule)
            {
                const char* param_module = MParameters[i]->getModule();
                if (param_module && SAT_IsEqual(param_module,AModule))
                {
                    return i;
                }
            }
            else return i;
        }
    }
    return -1;
}

//------------------------------
// presets
//------------------------------

//------------------------------
// audio ports
//------------------------------

void SAT_Plugin::appendAudioPort(SAT_AudioPort* APort)
{
    uint32_t index = MAudioPorts.size();
    MAudioPorts.append(APort);
    APort->setIndex(index);
}

void SAT_Plugin::deleteAllAudioPorts()
{
    uint32_t num = MAudioPorts.size();
    for (uint32_t i=0; i<num; i++)
    {
        if (MAudioPorts[i])
        {
            delete MAudioPorts[i];
            // MAudioPorts[i] = nullptr;
        }
    }
    MAudioPorts.clear();
}

uint32_t SAT_Plugin::getNumAudioPorts()
{
    return MAudioPorts.size();
}

SAT_AudioPort* SAT_Plugin::getAudioPort(uint32_t AIndex)
{
    return MAudioPorts[AIndex];
}

//------------------------------
// note ports
//------------------------------

void SAT_Plugin::appendNotePort(SAT_NotePort* APort)
{
    uint32_t index = MNotePorts.size();
    MNotePorts.append(APort);
    APort->setIndex(index);
}

void SAT_Plugin::deleteAllNotePorts()
{
    uint32_t num = MNotePorts.size();
    for (uint32_t i=0; i<num; i++)
    {
        if (MNotePorts[i])
        {
            delete MNotePorts[i];
            // MNotePorts[i] = nullptr;
        }
    }
    MNotePorts.clear();
}

uint32_t SAT_Plugin::getNumNotePorts()
{
    return MNotePorts.size();
}

SAT_NotePort* SAT_Plugin::getNotePort(uint32_t AIndex)
{
    return MNotePorts[AIndex];
}

//------------------------------
// editor
//------------------------------

// getDefaultSize
// getParameters

//------------------------------
// processor
//------------------------------

void SAT_Plugin::setProcessor(SAT_Processor* AProcessor)
{
    SAT_Assert(AProcessor);
    MProcessor = AProcessor;
}

