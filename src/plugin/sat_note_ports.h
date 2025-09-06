#pragma once

#include "base/sat_base.h"
#include "plugin/sat_note_port.h"


//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_NotePorts
{
    public:
        SAT_NotePorts();
        ~SAT_NotePorts();
    public:
        void                append(SAT_NotePort* APort);
        void                deleteAll();
        uint32_t            getCount();
        SAT_NotePort*       get(uint32_t AIndex);
    private:
        SAT_NotePortArray   MNotePorts = {};

};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

SAT_NotePorts::SAT_NotePorts()
{
}

SAT_NotePorts::~SAT_NotePorts()
{
    #ifndef SAT_NO_AUTODELETE
        deleteAll();
    #endif
}

//------------------------------
//
//------------------------------

void SAT_NotePorts::append(SAT_NotePort* APort)
{
    uint32_t index = MNotePorts.size();
    MNotePorts.append(APort);
    APort->setIndex(index);
}

void SAT_NotePorts::deleteAll()
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

uint32_t SAT_NotePorts::getCount()
{
    return MNotePorts.size();
}

SAT_NotePort* SAT_NotePorts::get(uint32_t AIndex)
{
    return MNotePorts[AIndex];
}
