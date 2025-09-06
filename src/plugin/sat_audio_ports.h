#pragma once

#include "base/sat_base.h"
#include "plugin/sat_audio_port.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_AudioPorts
{
    public:
        SAT_AudioPorts();
        ~SAT_AudioPorts();
    public:
        void                append(SAT_AudioPort* APort);
        void                deleteAll();
        uint32_t            getCount();
        SAT_AudioPort*      get(uint32_t AIndex);
    private:
        SAT_AudioPortArray  MAudioPorts = {};
};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

SAT_AudioPorts::SAT_AudioPorts()
{
}

SAT_AudioPorts::~SAT_AudioPorts()
{
    #ifndef SAT_NO_AUTODELETE
        deleteAll();
    #endif
}

//------------------------------
//
//------------------------------

void SAT_AudioPorts::append(SAT_AudioPort* APort)
{
    uint32_t index = MAudioPorts.size();
    MAudioPorts.append(APort);
    APort->setIndex(index);
}

void SAT_AudioPorts::deleteAll()
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

uint32_t SAT_AudioPorts::getCount()
{
    return MAudioPorts.size();
}

SAT_AudioPort* SAT_AudioPorts::get(uint32_t AIndex)
{
    return MAudioPorts[AIndex];
}
