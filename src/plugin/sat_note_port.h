#pragma once

/*
    note dialects
        CLAP_NOTE_DIALECT_CLAP
        CLAP_NOTE_DIALECT_MIDI
        CLAP_NOTE_DIALECT_MIDI_MPE
        CLAP_NOTE_DIALECT_MIDI2
*/

#include "base/sat_base.h"
#include "extern/plugin/sat_clap.h"


//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_NotePort
{
    public:
        SAT_NotePort();
        virtual ~SAT_NotePort();
    public: // info
        void                    setId(uint32_t AId);
        void                    setName(const char* AName);
        void                    setSupportedDialects(uint32_t ADialects);
        void                    setPreferredDialect(uint32_t ADialect);
    public: // info
        uint32_t                getId();
        const char*             getName();
        uint32_t                getSupportedDialects();
        uint32_t                getPreferredDialect();
    public:
        clap_note_port_info_t*  getInfo();
        void                    setInfo(clap_note_port_info_t* AInfo);
        void                    setIndex(uint32_t AIndex);
        uint32_t                getIndex();
    private:
        clap_note_port_info_t  MInfo = 
        {
            .id                 = 0,        // clap_id
            .supported_dialects = 0,
            .preferred_dialect  = 0,
            .name               = "audio"  // char[CLAP_NAME_SIZE]
        };
    private:
        uint32_t                MIndex = 0;
};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

SAT_NotePort::SAT_NotePort()
{
}

SAT_NotePort::~SAT_NotePort()
{
}

//------------------------------
// info
//------------------------------

void        SAT_NotePort::setId(uint32_t AId)                       { MInfo.id = AId; }
void        SAT_NotePort::setName(const char* AName)                { SAT_Strlcpy(MInfo.name,AName,CLAP_NAME_SIZE); }
void        SAT_NotePort::setSupportedDialects(uint32_t ADialects)  { MInfo.supported_dialects = ADialects; }
void        SAT_NotePort::setPreferredDialect(uint32_t ADialect)    { MInfo.preferred_dialect = ADialect; }

uint32_t    SAT_NotePort::getId()                                   { return MInfo.id; }
const char* SAT_NotePort::getName()                                 { return MInfo.name; }
uint32_t    SAT_NotePort::getSupportedDialects()                    { return MInfo.supported_dialects; }
uint32_t    SAT_NotePort::getPreferredDialect()                     { return MInfo.preferred_dialect; }


//------------------------------
//
//------------------------------

clap_note_port_info_t* SAT_NotePort::getInfo()
{
    return &MInfo;
}

void SAT_NotePort::setInfo(clap_note_port_info_t* AInfo)
{
    SAT_Assert(AInfo);
    memcpy(&MInfo,AInfo,sizeof(clap_note_port_info_t));
}

uint32_t SAT_NotePort::getIndex()
{
    return MIndex;
}

void SAT_NotePort::setIndex(uint32_t AIndex)
{
    MIndex = AIndex;
}


