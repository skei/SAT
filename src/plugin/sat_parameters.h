#pragma once

#include "base/sat_base.h"

#include "plugin/sat_parameter.h"
#include "plugin/parameter/sat_curve_parameter.h"
#include "plugin/parameter/sat_db_parameter.h"
#include "plugin/parameter/sat_enum_parameter.h"
#include "plugin/parameter/sat_hz_parameter.h"
#include "plugin/parameter/sat_int_parameter.h"
#include "plugin/parameter/sat_pow_parameter.h"
#include "plugin/parameter/sat_text_parameter.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_Parameters
{
    public:

        SAT_Parameters();
        ~SAT_Parameters();

    public:

        SAT_Parameter*  append(SAT_Parameter* AParameter);
        void            remove(SAT_Parameter* AParameter);
        void            remove(uint32_t AIndex);
        void            deleteAll();
        uint32_t        getCount();
        SAT_Parameter*  get(uint32_t AIndex);
        SAT_Parameter*  find(uint32_t AId);
        SAT_Parameter*  find(const char* AName, const char* AModule);
        int32_t         findIndex(uint32_t AId);
        int32_t         findIndex(const char* AName, const char* AModule);

    private:

        SAT_ParameterArray          MParameters = {};
     
};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

SAT_Parameters::SAT_Parameters()
{
}

SAT_Parameters::~SAT_Parameters()
{
    #ifndef SAT_NO_AUTODELETE
        deleteAll();
    #endif
}

//------------------------------
//
//------------------------------

SAT_Parameter* SAT_Parameters::append(SAT_Parameter* AParameter)
{
    SAT_Assert(AParameter);
    uint32_t index = MParameters.size();
    MParameters.append(AParameter);
    AParameter->setIndex(index);
    AParameter->setId(index);
    return AParameter;
}

void SAT_Parameters::remove(SAT_Parameter* AParameter)
{
    MParameters.remove(AParameter);
}

void SAT_Parameters::remove(uint32_t AIndex)
{
    MParameters.remove(AIndex);
}

void SAT_Parameters::deleteAll()
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

uint32_t SAT_Parameters::getCount()
{
    return MParameters.size();
}

SAT_Parameter* SAT_Parameters::get(uint32_t AIndex)
{
    return MParameters[AIndex];
}

SAT_Parameter* SAT_Parameters::find(uint32_t AId)
{
    int32_t index = findIndex(AId);
    if (index >= 0) return MParameters[index];
    return nullptr;
}

SAT_Parameter* SAT_Parameters::find(const char* AName, const char* AModule)
{
    int32_t index = findIndex(AName,AModule);
    if (index >= 0) return MParameters[index];
    return nullptr;
}

int32_t SAT_Parameters::findIndex(uint32_t AId)
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

int32_t SAT_Parameters::findIndex(const char* AName, const char* AModule)
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
