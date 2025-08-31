#pragma once

/*
    interact with the widget
*/

//----------------------------------------------------------------------

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

        bool            isActive() override;
        bool            isInteractive() override;
        bool            isEnabled() override;
        void            setActive(bool AState=true, bool ARecursive=true) override;
        void            setInteractive(bool AState=true, bool ARecursive=true) override;
        void            setEnabled(bool AState=true, bool ARecursive=true) override;
        bool            isRecursivelyActive() override;
        bool            isRecursivelyEnabled() override;

    public:
    
        // void            on_widget_mouse_click(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATime) override;
        // void            on_widget_mouse_dbl_click(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATime) override;
        // void            on_widget_mouse_release(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATime) override;
        // void            on_widget_mouse_move(int32_t AXpos, int32_t AYpos, uint32_t AState, uint32_t ATime) override;
        // void            on_widget_key_press(uint32_t AKey, uint32_t AChar, uint32_t AState, uint32_t ATime) override;
        // void            on_widget_key_release(uint32_t AKey, uint32_t AChar, uint32_t AState, uint32_t ATime) override;
        // void            on_widget_mouse_enter(SAT_BaseWidget* AFrom, int32_t AXpos, int32_t AYpos, uint32_t ATime) override;
        // void            on_widget_mouse_leave(SAT_BaseWidget* ATo, int32_t AXpos, int32_t AYpos, uint32_t ATime) override;
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

bool SAT_InteractiveWidget::isActive()
{
    return State.active;
}

bool SAT_InteractiveWidget::isInteractive()
{
    return State.interactive;
}

bool SAT_InteractiveWidget::isEnabled()
{
    return State.enabled;
}

//----------

void SAT_InteractiveWidget::setActive(bool AState, bool ARecursive)
{
    State.active = AState;
    if (ARecursive)
    {
        uint32_t num = getNumChildren();
        for (uint32_t i=0; i<num; i++)
        {
            SAT_BaseWidget* widget = getChild(i);
            widget->setActive(AState,ARecursive);
        }
    }
}

void SAT_InteractiveWidget::setInteractive(bool AState, bool ARecursive)
{
    State.interactive = AState;
}

void SAT_InteractiveWidget::setEnabled(bool AState, bool ARecursive)
{
    State.enabled = AState;
    if (ARecursive)
    {
        uint32_t num = getNumChildren();
        for (uint32_t i=0; i<num; i++)
        {
            SAT_BaseWidget* widget = getChild(i);
            widget->setEnabled(AState,ARecursive);
        }
    }
}

/*
    traverse up the hierarchy to see if there are inactive widgets
    above us, meaning this widget is also inactive
    (meaning it should not receive any interaction events, mouse, keys, etc)
*/

bool SAT_InteractiveWidget::isRecursivelyActive()
{
    if (!State.active) return false;
    SAT_BaseWidget* parent = getParent();
    if (!parent) return true;
    return parent->isRecursivelyActive();
}

/*
    same as active, but for the 'disabled' state..
    usually drawn a bit 'faded out'..
*/

bool SAT_InteractiveWidget::isRecursivelyEnabled()
{
    if (!State.enabled) return false;
    SAT_BaseWidget* parent = getParent();
    if (!parent) return true;
    return parent->isRecursivelyEnabled();
}


//------------------------------
//
//------------------------------

// void SAT_InteractiveWidget::on_widget_mouse_click(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATime)
// {
// }

// void SAT_InteractiveWidget::on_widget_mouse_dbl_click(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATime)
// {
// }

// void SAT_InteractiveWidget::on_widget_mouse_release(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATime)
// {
// }

// void SAT_InteractiveWidget::on_widget_mouse_move(int32_t AXpos, int32_t AYpos, uint32_t AState, uint32_t ATime)
// {
// }

// void SAT_InteractiveWidget::on_widget_key_press(uint32_t AKey, uint32_t AChar, uint32_t AState, uint32_t ATime)
// {
// }

// void SAT_InteractiveWidget::on_widget_key_release(uint32_t AKey, uint32_t AChar, uint32_t AState, uint32_t ATime)
// {
// }

// void SAT_InteractiveWidget::on_widget_mouse_enter(SAT_BaseWidget* AFrom, int32_t AXpos, int32_t AYpos, uint32_t ATime)
// {
// }

// void SAT_InteractiveWidget::on_widget_mouse_leave(SAT_BaseWidget* ATo, int32_t AXpos, int32_t AYpos, uint32_t ATime)
// {
// }
