#pragma once

#include "base/sat_base.h"
//#include "gui/sat_gui_base.h"
#include "gui/widget/base/sat_interactive_widget.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_ValueWidget
: public SAT_InteractiveWidget
{
    public:

        SAT_ValueWidget(SAT_Rect ARect);
        virtual ~SAT_ValueWidget();

    public:

        sat_param_t         getValue(uint32_t AIndex=0) override;
        SAT_Parameter*      getParameter(uint32_t AIndex=0) override;
        void                setValue(sat_param_t AValue, uint32_t AIndex=0) override;
        void                setParameter(SAT_Parameter* AParameter, uint32_t AIndex=0) override;

    protected:

        sat_param_t         MValue      = 0.0;
        SAT_Parameter*      MParameter  = nullptr;
};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

SAT_ValueWidget::SAT_ValueWidget(SAT_Rect ARect)
: SAT_InteractiveWidget(ARect)
{
    MWidgetType     = 0;
    MWidgetTypeName = "SAT_ValueWidget";
}

SAT_ValueWidget::~SAT_ValueWidget()
{
}

//------------------------------
//
//------------------------------

sat_param_t SAT_ValueWidget::getValue(uint32_t AIndex)
{
    return MValue;
}

SAT_Parameter* SAT_ValueWidget::getParameter(uint32_t AIndex)
{
    return MParameter;
}

//----------

void SAT_ValueWidget::setValue(sat_param_t AValue, uint32_t AIndex)
{
    MValue = AValue;
}

void SAT_ValueWidget::setParameter(SAT_Parameter* AParameter, uint32_t AIndex)
{
    MParameter = AParameter;
}
