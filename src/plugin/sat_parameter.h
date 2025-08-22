#pragma once

/*
    clap_param_info_flags
        CLAP_PARAM_IS_STEPPED
        CLAP_PARAM_IS_PERIODIC
        CLAP_PARAM_IS_HIDDEN
        CLAP_PARAM_IS_READONLY
        CLAP_PARAM_IS_BYPASS
        CLAP_PARAM_IS_AUTOMATABLE
        CLAP_PARAM_IS_AUTOMATABLE_PER_NOTE_ID
        CLAP_PARAM_IS_AUTOMATABLE_PER_KEY
        CLAP_PARAM_IS_AUTOMATABLE_PER_CHANNEL
        CLAP_PARAM_IS_AUTOMATABLE_PER_PORT
        CLAP_PARAM_IS_MODULATABLE
        CLAP_PARAM_IS_MODULATABLE_PER_NOTE_ID
        CLAP_PARAM_IS_MODULATABLE_PER_KEY
        CLAP_PARAM_IS_MODULATABLE_PER_CHANNEL
        CLAP_PARAM_IS_MODULATABLE_PER_PORT
        CLAP_PARAM_REQUIRES_PROCESS
        CLAP_PARAM_IS_ENUM

    automation state
        CLAP_PARAM_INDICATION_AUTOMATION_NONE
        CLAP_PARAM_INDICATION_AUTOMATION_PRESENT
        CLAP_PARAM_INDICATION_AUTOMATION_PLAYING
        CLAP_PARAM_INDICATION_AUTOMATION_RECORDING
        CLAP_PARAM_INDICATION_AUTOMATION_OVERRIDING
*/

#include "base/sat_base.h"
#include "plugin/format/clap/sat_clap.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_Parameter
{
    public:
        SAT_Parameter();
        virtual ~SAT_Parameter();
        public: // info
        void                        setId(uint32_t AId);
        void                        setFlags(uint32_t AFlags);
        void                        addFlags(uint32_t AFlags);
        void                        setName(const char* AName);
        void                        setModule(const char* AName);
        void                        setMinValue(sat_param_t AValue);
        void                        setMaxValue(sat_param_t AValue);
        void                        setDefaultValue(sat_param_t AValue);
    public: // info
        uint32_t                    getId();
        uint32_t                    getFlags();
        const char*                 getName();
        const char*                 getModule();
        sat_param_t                 getMinValue();
        sat_param_t                 getMaxValue();
        sat_param_t                 getDefaultValue();
    public:
        virtual sat_param_t         getValue();
        virtual void                setValue(sat_param_t AValue);
        virtual sat_param_t         getNormalizedValue();
        virtual void                setNormalizedValue(sat_param_t AValue);
        virtual const char*         valueToText(sat_param_t AValue);
        virtual sat_param_t         textToValue(const char* AValue);
        virtual void                setValue(const char* AValue);
    public:
        clap_param_info_t*          getInfo();
        void                        setInfo(clap_param_info_t* AInfo);
        int32_t                     getIndex();
        void                        setIndex(int32_t AIndex);
        virtual const char*         getValueText();
        virtual void                setValueFormat(const char* AFormat);
        void                        connect(void* AWidget);
        void*                       getConnectedWidget();
        void                        setPreviousUpdateFrame(uint32_t AFrame);
        uint32_t                    getPreviousUpdateFrame();
    public: // param indication
        void                        setParamIndication(bool AState, uint32_t AColor=0, const char* ALabel="", const char* ADescription="");
        void                        setParamAutomation(uint32_t AState, uint32_t AColor=0);
        bool                        getIndicationState();
        uint32_t                    getIndicationColor();
        const char*                 getIndicationLabel();
        const char*                 getIndicationDescription();
        uint32_t                    getAutomationState();
        uint32_t                    getAutomatiuonColor();
    public:
    private:
        clap_param_info_t   MInfo =
        {
            .id                     = 0,
            .flags                  = CLAP_PARAM_IS_AUTOMATABLE,
            .cookie                 = this,
            .name                   = "param",
            .module                 = "",
            .min_value              = 0.0,
            .max_value              = 1.0,
            .default_value          = 0.0
        };
    private:
        sat_param_t                 MValue                                  = 0.0;
        char                        MValueText[SAT_MAX_VALUE_TEXT_LENGTH]   = {0};
        const char*                 MValueFormat                            = "%.2f";
    private: // param indication
        bool                        MIndicationState                        = false;
        uint32_t                    MIndicationColor                        = 0.0;
        const char*                 MIndicationLabel                        = "";       // todo: buffer? is the char* we receive in setParamIndication() 'const'?
        const char*                 MIndicationDescription                  = "";       // --"--
        uint32_t                    MAutomationState                        = 0;
        uint32_t                    MAutomatiuonColor                       = 0;
    private:
        uint32_t                    MIndex                                  = -1;
        void*                       MConnectedWidget                        = nullptr;
        uint32_t                    MPreviousUpdateFrame                    = 0;

};

//------------------------------
//
//------------------------------

// aka 'Module'

class SAT_ParameterGroup
{
};

// presets, state

class SAT_ParameterManager
{
};

//----------------------------------------------------------------------
//
// implementation
//
//----------------------------------------------------------------------

SAT_Parameter::SAT_Parameter()
{
}

SAT_Parameter::~SAT_Parameter()
{
}

//------------------------------
// info
//------------------------------

void SAT_Parameter::setId(uint32_t AId)                 { MInfo.id = AId; }
void SAT_Parameter::setFlags(uint32_t AFlags)           { MInfo.flags = AFlags; }
void SAT_Parameter::addFlags(uint32_t AFlags)           { MInfo.flags |= AFlags; }
void SAT_Parameter::setName(const char* AName)          { SAT_Strlcpy(MInfo.name,AName,CLAP_NAME_SIZE); }
void SAT_Parameter::setModule(const char* AModule)      { SAT_Strlcpy(MInfo.name,AModule,CLAP_PATH_SIZE); }
void SAT_Parameter::setMinValue(sat_param_t AValue)     { MInfo.min_value = AValue; }
void SAT_Parameter::setMaxValue(sat_param_t AValue)     { MInfo.max_value = AValue; }
void SAT_Parameter::setDefaultValue(sat_param_t AValue) { MInfo.default_value = AValue; }

uint32_t    SAT_Parameter::getId()                      { return MInfo.id; }
uint32_t    SAT_Parameter::getFlags()                   { return MInfo.flags; }
const char* SAT_Parameter::getName()                    { return MInfo.name; }
const char* SAT_Parameter::getModule()                  { return MInfo.module; }
sat_param_t SAT_Parameter::getMinValue()                { return MInfo.min_value; }
sat_param_t SAT_Parameter::getMaxValue()                { return MInfo.max_value; }
sat_param_t SAT_Parameter::getDefaultValue()            { return MInfo.default_value; }

//------------------------------
//
//------------------------------

sat_param_t SAT_Parameter::getValue()
{
    return MValue;
}

void SAT_Parameter::setValue(sat_param_t AValue)
{
    SAT_Assert(AValue >= MInfo.min_value);
    SAT_Assert(AValue <= MInfo.min_value);
    MValue = AValue;
}

sat_param_t SAT_Parameter::getNormalizedValue()
{
    sat_param_t range = MInfo.max_value - MInfo.min_value;
    sat_param_t value = MInfo.min_value;
    if (range > 0.0) value /= range;
    SAT_Assert(value >= 0.0);
    SAT_Assert(value <= 1.0);
    return value;
}

void SAT_Parameter::setNormalizedValue(sat_param_t AValue)
{
    SAT_Assert(AValue >= 0.0);
    SAT_Assert(AValue <= 1.0);
    sat_param_t range = MInfo.max_value - MInfo.min_value;
    sat_param_t value = MInfo.min_value;
    if (range > 0.0) value *= range;
    MValue = AValue;
}

const char* SAT_Parameter::valueToText(sat_param_t AValue)
{
    SAT_Assert(AValue >= MInfo.min_value);
    SAT_Assert(AValue <= MInfo.min_value);
    sprintf(MValueText,MValueFormat,AValue);
    return MValueText;
}

sat_param_t SAT_Parameter::textToValue(const char* AValue)
{
    SAT_Assert(AValue);
    sat_param_t value = atof(AValue);
    return 0.0;
}

void SAT_Parameter::setValue(const char* AValue)
{
    MValue = textToValue(AValue);
}

//------------------------------
//
//------------------------------

clap_param_info_t* SAT_Parameter::getInfo()
{
    return &MInfo;
}

void SAT_Parameter::setInfo(clap_param_info_t* AInfo)
{
    SAT_Assert(AInfo);
    memcpy(&MInfo,AInfo,sizeof(clap_param_info_t));
}

int32_t SAT_Parameter::getIndex()
{
    return MIndex;
}

void SAT_Parameter::setIndex(int32_t AIndex)
{
    MIndex = AIndex;
    //MInfo.id = MIndex;
}

const char* SAT_Parameter::getValueText()
{
    return valueToText(MValue);
}

void SAT_Parameter::setValueFormat(const char* AFormat)
{
    MValueFormat = AFormat;
};

void SAT_Parameter::connect(void* AWidget)
{
    MConnectedWidget = AWidget;
}

void* SAT_Parameter::getConnectedWidget()
{
    return MConnectedWidget;
}

void SAT_Parameter::setPreviousUpdateFrame(uint32_t AFrame)
{
    MPreviousUpdateFrame = AFrame;
}

//------------------------------
// param indication
//------------------------------

void SAT_Parameter::setParamIndication(bool AState, uint32_t AColor, const char* ALabel, const char* ADescription)
{
    MIndicationState = AState;
    MIndicationColor = AColor;
    MIndicationLabel = ALabel;
    MIndicationDescription = ADescription;
}

void SAT_Parameter::setParamAutomation(uint32_t AState, uint32_t AColor)
{
    MAutomationState = AState;
    MAutomatiuonColor = AColor;
}

bool SAT_Parameter::getIndicationState()                { return MIndicationState; }
uint32_t SAT_Parameter::getIndicationColor()            { return  MIndicationColor; }
const char* SAT_Parameter::getIndicationLabel()         { return  MIndicationLabel; }
const char* SAT_Parameter::getIndicationDescription()   { return  MIndicationDescription; }

uint32_t SAT_Parameter::getAutomationState()            { return  MAutomationState; }
uint32_t SAT_Parameter::getAutomatiuonColor()           { return  MAutomatiuonColor; }
uint32_t SAT_Parameter::getPreviousUpdateFrame()        { return  MPreviousUpdateFrame; }

//------------------------------
//
//------------------------------



