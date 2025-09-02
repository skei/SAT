#pragma once

#include "base/sat_base.h"
//#include "gui/sat_gui_base.h"
#include "gui/widget/base/sat_layout_widget.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_InteractiveWidget
: public SAT_LayoutWidget
{
    public:

        SAT_InteractiveWidget(SAT_Rect ARect);
        virtual ~SAT_InteractiveWidget();

    public:

        void            setActive(bool AState=true) override;
        void            setChildrenActive(bool AState=true) override;
        void            setEnabled(bool AState=true) override;
        void            setChildrenEnabled(bool AState=true) override;

        bool            isActive() override;
        bool            isEnabled() override;

     // void            activateVisibleChildren() override;
     // void            deactivateInvisibleChildren() override;

};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

SAT_InteractiveWidget::SAT_InteractiveWidget(SAT_Rect ARect)
: SAT_LayoutWidget(ARect)
{
    MWidgetTypeName = "SAT_InteractiveWidget";
}

SAT_InteractiveWidget::~SAT_InteractiveWidget()
{
}

//------------------------------
//
//------------------------------

void SAT_InteractiveWidget::setActive(bool AState)
{
    State.active = AState;
    setChildrenActive(AState);
}

void SAT_InteractiveWidget::setChildrenActive(bool AState)
{
    uint32_t num = getNumChildren();
    for (uint32_t i=0; i<num; i++)
    {
        SAT_BaseWidget* widget = getChild(i);
        widget->setActive(AState);
    }
}

void SAT_InteractiveWidget::setEnabled(bool AState)
{
    State.enabled = AState;
    setChildrenEnabled(AState);
}

void SAT_InteractiveWidget::setChildrenEnabled(bool AState)
{
    uint32_t num = getNumChildren();
    for (uint32_t i=0; i<num; i++)
    {
        SAT_BaseWidget* widget = getChild(i);
        widget->setEnabled(AState);
    }
}

//----------

bool SAT_InteractiveWidget::isActive()
{
    return State.active;
}

bool SAT_InteractiveWidget::isEnabled()
{
    return State.enabled;
}

//------------------------------
//
//------------------------------
