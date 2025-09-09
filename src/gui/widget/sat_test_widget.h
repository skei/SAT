#pragma once

#include "base/sat.h"
#include "gui/widget/visual/sat_text_widget.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_TestWidget
: public SAT_TextWidget
{
    public:

        SAT_TestWidget(SAT_Rect ARect);
        virtual ~SAT_TestWidget();

    public:

        void on_widget_mouse_click(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATime) override;
        void on_widget_mouse_longpress(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATime) override;
        void on_widget_mouse_start_drag(int32_t AXpos, int32_t AYpos, uint32_t AState, uint32_t ATime) override;
        void on_widget_mouse_move(int32_t AXpos, int32_t AYpos, uint32_t AState, uint32_t ATime) override;
        void on_widget_mouse_release(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATime) override;

    protected:

        bool MIsSelected = false;
        bool MIsDragging = false;
        // uint32_t MButton = SAT_BUTTON_NONE;

};

//------------------------------
//
//------------------------------

SAT_TestWidget::SAT_TestWidget(SAT_Rect ARect)
: SAT_TextWidget(ARect)
{
    WidgetBase.widgetTypeName = "SAT_TestWidget";
    WidgetVisual.skin = SAT.GUI->SKINS.find("DefaultText");
}

SAT_TestWidget::~SAT_TestWidget()
{
}

//------------------------------
//
//------------------------------

void SAT_TestWidget::on_widget_mouse_click(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATime)
{
    SAT_PRINT("%s : x %i y %i b %i\n",getName(),AXpos,AYpos,AButton);
    if (AButton == SAT_BUTTON_LEFT)
    {
        do_widget_cursor(this,SAT_CURSOR_LOCK);
    //    MIsDragging = true;
    }
}

void SAT_TestWidget::on_widget_mouse_longpress(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATime)
{
    SAT_PRINT("%s : x %i y %i b %i\n",getName(),AXpos,AYpos,AButton);
}

void SAT_TestWidget::on_widget_mouse_start_drag(int32_t AXpos, int32_t AYpos, uint32_t AState, uint32_t ATime)
{
    SAT_PRINT("%s : x %i y %i\n",getName(),AXpos,AYpos);
    // if (MIsDragging)
    // {
    //     do_widget_cursor(this,SAT_CURSOR_HIDE);
    // }
}

void SAT_TestWidget::on_widget_mouse_release(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATime)
{
    SAT_PRINT("%s : x %i y %i b %i\n",getName(),AXpos,AYpos,AButton);
    if (AButton == SAT_BUTTON_LEFT)
    {
    //    if (MIsDragging)
    //    {
            do_widget_cursor(this,SAT_CURSOR_UNLOCK);
    //        do_widget_cursor(this,SAT_CURSOR_SHOW);
    //        MIsDragging = false;
    //    }
    }
};

void SAT_TestWidget::on_widget_mouse_move(int32_t AXpos, int32_t AYpos, uint32_t AState, uint32_t ATime)
{
    SAT_PRINT("%s : x %i y %i\n",getName(),AXpos,AYpos);
}



