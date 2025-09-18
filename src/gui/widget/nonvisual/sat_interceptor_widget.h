#pragma once

/*
    a widget you can use to intercept messages, and redirect them..
    if either Chilr or Parent proxy is null, it calls the original methods..
    if Multiplex is true, it calls both.. first the proxy, then the original
    (using return value from proxy)
*/

#include "base/sat.h"
#include "gui/mouse/sat_mouse_state.h"
#include "gui/sat_widget.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_InterceptorWidget
: public SAT_Widget
{
    public:
        SAT_InterceptorWidget(SAT_Rect ARect, SAT_Widget* AChild=nullptr, SAT_Widget* AParent=nullptr, bool AMultiplex=false, bool AOverrideReturn=false);
        virtual ~SAT_InterceptorWidget();
    public:
        virtual void    setChildProxy(SAT_Widget* AWidget);
        virtual void    setParentProxy(SAT_Widget* AWidget);
        virtual void    setMultiplex(bool AMultiplex=true);
        virtual void    setOverrideReturn(bool AOverride=true);
    public: // on_
        void            on_widget_show(SAT_WidgetOwner* AOwner) override;
        void            on_widget_hide(SAT_WidgetOwner* AOwner) override;
        void            on_widget_paint(SAT_PaintContext* AContext) override;
        void            on_widget_pre_paint(SAT_PaintContext* AContext) override;
        void            on_widget_post_paint(SAT_PaintContext* AContext) override;
        void            on_widget_realign() override;
        SAT_Rect        on_widget_pre_align(SAT_Rect ARect) override;
        SAT_Rect        on_widget_post_align(SAT_Rect ARect) override;
        void            on_widget_timer(uint32_t ATimerId, double ADelta) override;
        void            on_widget_anim(uint32_t AId, uint32_t AType, uint32_t ANumValues, double* AValues) override;
        void            on_widget_notify(SAT_Widget* AWidget, uint32_t AType=SAT_WIDGET_NOTIFY_NONE, intptr_t AValue=0) override;
        uint32_t        on_widget_mouse_event(SAT_MouseEvent* AEvent) override;
        void            on_widget_mouse_gesture(SAT_MouseGesture* AGesture) override;
        uint32_t        on_widget_keyboard_event(SAT_KeyboardEvent* AEvent) override;
        void            on_widget_keyboard_gesture(SAT_KeyboardGesture* AGesture) override;
    public: // do_
        void            do_widget_update(SAT_Widget* AWidget, uint32_t AIndex=0) override;
        void            do_widget_realign(SAT_Widget* AWidget, uint32_t AMode=SAT_WIDGET_REALIGN_PARENT) override;
        void            do_widget_redraw(SAT_Widget* AWidget, uint32_t AMode=SAT_WIDGET_REDRAW_SELF) override;
        void            do_widget_anim(SAT_Widget* AWidget, SAT_AnimChain* AChain) override;
        void            do_widget_notify(SAT_Widget* AWidget, uint32_t AType=SAT_WIDGET_NOTIFY_NONE, intptr_t AValue=0) override;
        void            do_widget_capture_mouse(SAT_Widget* AWidget) override;
        void            do_widget_capture_keyboard(SAT_Widget* AWidget) override;
        void            do_widget_cursor(SAT_Widget* AWidget, int32_t ACursor) override;
        void            do_widget_modal(SAT_Widget* AWidget) override;
        void            do_widget_hint(SAT_Widget* AWidget, uint32_t AType, const char* AHint=nullptr) override;
    protected:
        SAT_Widget*     MChildProxy     = nullptr;
        SAT_Widget*     MParentProxy    = nullptr;
        bool            MMultiplex      = false;
        bool            MOverrideReturn = false;

};

//------------------------------
//
//------------------------------

SAT_InterceptorWidget::SAT_InterceptorWidget(SAT_Rect ARect, SAT_Widget* AChild, SAT_Widget* AParent, bool AMultiplex, bool AOverrideReturn)
: SAT_Widget(ARect)
{
    MTypeName       = "SAT_InterceptorWidget";
    MChildProxy     = AChild;
    MParentProxy    = AParent;
    MMultiplex      = AMultiplex;
    MOverrideReturn = AOverrideReturn;
}

SAT_InterceptorWidget::~SAT_InterceptorWidget()
{
}

//------------------------------
//
//------------------------------

void SAT_InterceptorWidget::setChildProxy(SAT_Widget* AWidget)
{
    MChildProxy = AWidget;
}

void SAT_InterceptorWidget::setParentProxy(SAT_Widget* AWidget)
{
    MParentProxy = AWidget;
}

void SAT_InterceptorWidget::setMultiplex(bool AMultiplex)
{
    MMultiplex = AMultiplex;
}

void SAT_InterceptorWidget::setOverrideReturn(bool AOverride)
{
    MOverrideReturn = AOverride;
}

//------------------------------
//
//------------------------------

void SAT_InterceptorWidget::on_widget_show(SAT_WidgetOwner* AOwner)
{
    if (MChildProxy)
    {
        MChildProxy->on_widget_show(AOwner);
        if (MMultiplex) SAT_Widget::on_widget_show(AOwner);
    }
    else SAT_Widget::on_widget_show(AOwner);
}

void SAT_InterceptorWidget::on_widget_hide(SAT_WidgetOwner* AOwner)
{
    if (MChildProxy)
    {
        MChildProxy->on_widget_hide(AOwner);
        if (MMultiplex) SAT_Widget::on_widget_hide(AOwner);
    }
    else SAT_Widget::on_widget_hide(AOwner);
}

void SAT_InterceptorWidget::on_widget_paint(SAT_PaintContext* AContext)
{
    if (MChildProxy)
    {
        MChildProxy->on_widget_paint(AContext);
        if (MMultiplex) SAT_Widget::on_widget_paint(AContext);
    }
    else SAT_Widget::on_widget_paint(AContext);
}

void SAT_InterceptorWidget::on_widget_pre_paint(SAT_PaintContext* AContext)
{
    if (MChildProxy)
    {
        MChildProxy->on_widget_pre_paint(AContext);
        if (MMultiplex) SAT_Widget::on_widget_pre_paint(AContext);
    }
    else SAT_Widget::on_widget_pre_paint(AContext);
}

void SAT_InterceptorWidget::on_widget_post_paint(SAT_PaintContext* AContext)
{
    if (MChildProxy)
    {
        MChildProxy->on_widget_post_paint(AContext);
        if (MMultiplex) SAT_Widget::on_widget_post_paint(AContext);
    }
    else SAT_Widget::on_widget_post_paint(AContext);
}

void SAT_InterceptorWidget::on_widget_realign()
{
    if (MChildProxy)
    {
        MChildProxy->on_widget_realign();
        if (MMultiplex) SAT_Widget::on_widget_realign();
    }
    else SAT_Widget::on_widget_realign();
}

SAT_Rect SAT_InterceptorWidget::on_widget_pre_align(SAT_Rect ARect)
{
    if (MChildProxy)
    {
        SAT_Rect rect = MChildProxy->on_widget_pre_align(ARect);
        if (MMultiplex)
        {
            SAT_Rect retval = SAT_Widget::on_widget_pre_align(ARect);
            if (MOverrideReturn) rect = retval;
        }
        return rect;
    }
    else return SAT_Widget::on_widget_pre_align(ARect);
}

SAT_Rect SAT_InterceptorWidget::on_widget_post_align(SAT_Rect ARect)
{
    if (MChildProxy)
    {
        SAT_Rect rect = MChildProxy->on_widget_post_align(ARect);
        if (MMultiplex)
        {
            SAT_Rect retval = SAT_Widget::on_widget_post_align(rect);
            if (MOverrideReturn) rect = retval;
        }
        return rect;
    }
    else return SAT_Widget::on_widget_post_align(ARect);
}

void SAT_InterceptorWidget::on_widget_timer(uint32_t ATimerId, double ADelta)
{
    if (MChildProxy)
    {
        MChildProxy->on_widget_timer(ATimerId,ADelta);
        if (MMultiplex) SAT_Widget::on_widget_timer(ATimerId,ADelta);
    }
    else SAT_Widget::on_widget_timer(ATimerId,ADelta);
}

void SAT_InterceptorWidget::on_widget_anim(uint32_t AId, uint32_t AType, uint32_t ANumValues, double* AValues)
{
    if (MChildProxy)
    {
        MChildProxy->on_widget_anim(AId,AType,ANumValues,AValues);
        if (MMultiplex) SAT_Widget::on_widget_anim(AId,AType,ANumValues,AValues);
    }
    else SAT_Widget::on_widget_anim(AId,AType,ANumValues,AValues);
}

void SAT_InterceptorWidget::on_widget_notify(SAT_Widget* AWidget, uint32_t AType, intptr_t AValue)
{
    if (MChildProxy)
    {
        MChildProxy->on_widget_notify(AWidget,AType,AValue);
        if (MMultiplex) SAT_Widget::on_widget_notify(AWidget,AType,AValue);
    }
    else SAT_Widget::on_widget_notify(AWidget,AType,AValue);
}

uint32_t SAT_InterceptorWidget::on_widget_mouse_event(SAT_MouseEvent* AEvent)
{
    if (MChildProxy)
    {
        uint32_t response = MChildProxy->on_widget_mouse_event(AEvent);
        if (MMultiplex)
        {
            uint32_t retval = SAT_Widget::on_widget_mouse_event(AEvent);
            if (MOverrideReturn) response = retval;

        }
        return response;
    }
    else return SAT_Widget::on_widget_mouse_event(AEvent);
}

void SAT_InterceptorWidget::on_widget_mouse_gesture(SAT_MouseGesture* AGesture)
{
    if (MChildProxy)
    {
        MChildProxy->on_widget_mouse_gesture(AGesture);
        if (MMultiplex) SAT_Widget::on_widget_mouse_gesture(AGesture);
    }
    else return SAT_Widget::on_widget_mouse_gesture(AGesture);
}

uint32_t SAT_InterceptorWidget::on_widget_keyboard_event(SAT_KeyboardEvent* AEvent)
{
    if (MChildProxy)
    {
        uint32_t response = MChildProxy->on_widget_keyboard_event(AEvent);
        if (MMultiplex)
        {
            uint32_t retval = SAT_Widget::on_widget_keyboard_event(AEvent);
            if (MOverrideReturn) response = retval;
        }
        return response;
    }
    else return SAT_Widget::on_widget_keyboard_event(AEvent);
}

void SAT_InterceptorWidget::on_widget_keyboard_gesture(SAT_KeyboardGesture* AGesture)
{
    if (MChildProxy)
    {
        MChildProxy->on_widget_keyboard_gesture(AGesture);
        if (MMultiplex) SAT_Widget::on_widget_keyboard_gesture(AGesture);
    }
    else SAT_Widget::on_widget_keyboard_gesture(AGesture);
}

//------------------------------
//
//------------------------------

void SAT_InterceptorWidget::do_widget_update(SAT_Widget* AWidget, uint32_t AIndex)
{
    if (MParentProxy)
    {
        MParentProxy->do_widget_update(AWidget,AIndex);
        if (MMultiplex) SAT_Widget::do_widget_update(AWidget,AIndex);
    }
    else SAT_Widget::do_widget_update(AWidget,AIndex);
}

void SAT_InterceptorWidget::do_widget_realign(SAT_Widget* AWidget, uint32_t AMode)
{
    if (MParentProxy)
    {
        MParentProxy->do_widget_realign(AWidget,AMode);
        if (MMultiplex) SAT_Widget::do_widget_realign(AWidget,AMode);
    }
    else SAT_Widget::do_widget_realign(AWidget,AMode);
}

void SAT_InterceptorWidget::do_widget_redraw(SAT_Widget* AWidget, uint32_t AMode)
{
    if (MParentProxy)
    {
        MParentProxy->do_widget_redraw(AWidget,AMode);
        if (MMultiplex) SAT_Widget::do_widget_redraw(AWidget,AMode);
    }
    else SAT_Widget::do_widget_redraw(AWidget,AMode);
}

void SAT_InterceptorWidget::do_widget_anim(SAT_Widget* AWidget, SAT_AnimChain* AChain)
{
    if (MParentProxy)
    {
        MParentProxy->do_widget_anim(AWidget,AChain);
        if (MMultiplex) SAT_Widget::do_widget_anim(AWidget,AChain);
    }
    else SAT_Widget::do_widget_anim(AWidget,AChain);
}

void SAT_InterceptorWidget::do_widget_notify(SAT_Widget* AWidget, uint32_t AType, intptr_t AValue)
{
    if (MParentProxy)
    {
        MParentProxy->do_widget_notify(AWidget,AType,AValue);
        if (MMultiplex) SAT_Widget::do_widget_notify(AWidget,AType,AValue);
    }
    else SAT_Widget::do_widget_notify(AWidget,AType,AValue);
}

void SAT_InterceptorWidget::do_widget_capture_mouse(SAT_Widget* AWidget)
{
    if (MParentProxy)
    {
        MParentProxy->do_widget_capture_mouse(AWidget);
        if (MMultiplex) SAT_Widget::do_widget_capture_mouse(AWidget);
    }
    else SAT_Widget::do_widget_capture_mouse(AWidget);
}

void SAT_InterceptorWidget::do_widget_capture_keyboard(SAT_Widget* AWidget)
{
    if (MParentProxy)
    {
        MParentProxy->do_widget_capture_keyboard(AWidget);
        if (MMultiplex) SAT_Widget::do_widget_capture_keyboard(AWidget);
    }
    else SAT_Widget::do_widget_capture_keyboard(AWidget);
}

void SAT_InterceptorWidget::do_widget_cursor(SAT_Widget* AWidget, int32_t ACursor)
{
    if (MParentProxy)
    {
        MParentProxy->do_widget_cursor(AWidget,ACursor);
        if (MMultiplex) SAT_Widget::do_widget_cursor(AWidget,ACursor);
    }
    else SAT_Widget::do_widget_cursor(AWidget,ACursor);
}

void SAT_InterceptorWidget::do_widget_modal(SAT_Widget* AWidget)
{
    if (MParentProxy)
    {
        MParentProxy->do_widget_modal(AWidget);
        if (MMultiplex) SAT_Widget::do_widget_modal(AWidget);
    }
    else SAT_Widget::do_widget_modal(AWidget);
}

void SAT_InterceptorWidget::do_widget_hint(SAT_Widget* AWidget, uint32_t AType, const char* AHint)
{
    if (MParentProxy)
    {
        MParentProxy->do_widget_hint(AWidget,AType,AHint);
        if (MMultiplex) SAT_Widget::do_widget_hint(AWidget,AType,AHint);
    }
    else SAT_Widget::do_widget_hint(AWidget,AType,AHint);
}
