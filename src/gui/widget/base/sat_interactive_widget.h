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

    public:

        void            on_widget_mouse_enter(SAT_BaseWidget* AFrom, int32_t AXpos, int32_t AYpos, uint32_t ATime) override;
        void            on_widget_mouse_leave(SAT_BaseWidget* ATo, int32_t AXpos, int32_t AYpos, uint32_t ATime) override;

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

void SAT_InteractiveWidget::on_widget_mouse_enter(SAT_BaseWidget* AFrom, int32_t AXpos, int32_t AYpos, uint32_t ATime)
{
    if (Options.auto_redraw_hover) do_widget_redraw(this);
    SAT_LayoutWidget::on_widget_mouse_enter(AFrom,AXpos,AYpos,ATime);
}

void SAT_InteractiveWidget::on_widget_mouse_leave(SAT_BaseWidget* ATo, int32_t AXpos, int32_t AYpos, uint32_t ATime)
{
    if (Options.auto_redraw_hover) do_widget_redraw(this);
    SAT_LayoutWidget::on_widget_mouse_leave(ATo,AXpos,AYpos,ATime);
}
