#pragma once

/*
    info.flags:
        CLAP_PORT_MONO
        CLAP_PORT_STEREO
        CLAP_PORT_SURROUND
        CLAP_PORT_AMBISONIC
        null or empty = unspecified (arbitrary audio)
    
    info.port_type:
        CLAP_AUDIO_PORT_IS_MAIN
        CLAP_AUDIO_PORT_SUPPORTS_64BITS
        CLAP_AUDIO_PORT_PREFERS_64BITS
        CLAP_AUDIO_PORT_REQUIRES_COMMON_SAMPLE_SIZE
*/

#include "base/sat_base.h"
#include "extern/plugin/sat_clap.h"

class SAT_AudioPort;
typedef SAT_Array<SAT_AudioPort*> SAT_AudioPortArray;

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_AudioPort
{
    public:
        SAT_AudioPort();
        virtual ~SAT_AudioPort();
    public: // info
        void                    setId(uint32_t AId);
        void                    setName(const char* AName);
        void                    setFlags(uint32_t AFlags);
        void                    setChannelCount(uint32_t ACount);
        void                    setPortType(const char* AType);
        void                    setInPlacePair(uint32_t APair);
    public: // info
        uint32_t                getId();
        const char*             getName();
        uint32_t                getFlags();
        uint32_t                getChannelCount();
        const char*             getPortType();
        uint32_t                getInPlacePair();
    public:
        clap_audio_port_info_t* getInfo();
        void                    setInfo(clap_audio_port_info_t* AInfo);
        void                    setIndex(uint32_t AIndex);
        uint32_t                getIndex();
    private:
        clap_audio_port_info_t  MInfo = 
        {
            .id                 = 0,        // clap_id
            .name               = "audio",  // char[CLAP_NAME_SIZE]
            .flags              = 0,        // uint32_t
            .channel_count      = 0,        // uint32_t;
            .port_type          = nullptr,  // const char*
            .in_place_pair      = 0         // clap_id 
        };
    private:
        uint32_t                MIndex = 0;
};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

SAT_AudioPort::SAT_AudioPort()
{
}

SAT_AudioPort::~SAT_AudioPort()
{
}

//------------------------------
// info
//------------------------------

void        SAT_AudioPort::setId(uint32_t AId)              { MInfo.id = AId; }
void        SAT_AudioPort::setName(const char* AName)       { SAT_Strlcpy(MInfo.name,AName,CLAP_NAME_SIZE); }
void        SAT_AudioPort::setFlags(uint32_t AFlags)        { MInfo.flags = AFlags; }
void        SAT_AudioPort::setChannelCount(uint32_t ACount) { MInfo.channel_count = ACount; }
void        SAT_AudioPort::setPortType(const char* AType)   { MInfo.port_type = AType; }
void        SAT_AudioPort::setInPlacePair(uint32_t APair)   { MInfo.in_place_pair = APair; }

uint32_t    SAT_AudioPort::getId()                          { return MInfo.id; }
const char* SAT_AudioPort::getName()                        { return MInfo.name; }
uint32_t    SAT_AudioPort::getFlags()                       { return MInfo.flags; }
uint32_t    SAT_AudioPort::getChannelCount()                { return MInfo.channel_count; }
const char* SAT_AudioPort::getPortType()                    { return MInfo.port_type; }
uint32_t    SAT_AudioPort::getInPlacePair()                 { return MInfo.in_place_pair; }

//------------------------------
//
//------------------------------

clap_audio_port_info_t* SAT_AudioPort::getInfo()
{
    return &MInfo;
}

void SAT_AudioPort::setInfo(clap_audio_port_info_t* AInfo)
{
    SAT_Assert(AInfo);
    memcpy(&MInfo,AInfo,sizeof(clap_audio_port_info_t));
}

uint32_t SAT_AudioPort::getIndex()
{
    return MIndex;
}

void SAT_AudioPort::setIndex(uint32_t AIndex)
{
    MIndex = AIndex;
}


