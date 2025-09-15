#pragma once

#if 0

#include "base/sat_base.h"
#include "gui/sat_skin.h"
#include "gui/painter/sat_paint_context.h"
#include "gui/widget/sat_widget_owner.h"

class SAT_AnimChain;
class SAT_KeyboardHandler;
class SAT_KeyboardState;
class SAT_MouseEvent;
class SAT_MouseGesture;
class SAT_MouseHandler;
class SAT_MouseState;
class SAT_Parameter;
class SAT_Widget;
class SAT_WidgetLayoutHandler;

class SAT_BaseWidget;
typedef SAT_Array<SAT_BaseWidget*> SAT_BaseWidgetArray;

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------



//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_BaseWidget
{

    public:

        SAT_BaseWidget()                                                                            { }
        virtual ~SAT_BaseWidget()                                                                   { }

    public: // base

        virtual void                setName(const char* AName)                                      { }
        virtual void                setHint(const char* AHint)                                      { }
        virtual void                setTooltip(const char* ATooltip)                                { }
        virtual const char*         getName()                                                       { return ""; }
        virtual const char*         getHint()                                                       { return ""; }
        virtual const char*         getTooltip()                                                    { return ""; }
        virtual const char*         getTypeName()                                                   { return ""; }

        virtual SAT_WidgetState*    getState() { return nullptr; }
        virtual SAT_WidgetOptions*  getOptions() { return nullptr; }

    public: // hierarchy

        virtual void                setParent(SAT_BaseWidget* AParent)                                  { }
        virtual void                setIndex(uint32_t AIndex)                                       { }
        virtual SAT_WidgetOwner*    getOwner()                                                      { return nullptr; }

        virtual SAT_Rect            getOwnerRect() { return SAT_Rect(); }
        virtual sat_coord_t         getOwnerScale() { return 1.0; }

        virtual SAT_BaseWidget*     getParent()                                                     { return nullptr; }
        virtual uint32_t            getIndex()                                                      { return 0; }
        virtual SAT_BaseWidget*     appendChild(SAT_BaseWidget* AWidget)                            { return AWidget; }
        virtual void                deleteChildren()                                                { }
        virtual void                removeChild(SAT_BaseWidget* AWidget, bool ADelete=true)         { }
        virtual uint32_t            getNumChildren()                                                { return 0; }
        virtual SAT_BaseWidget*     getChild(uint32_t AIndex)                                       { return nullptr; }
        virtual SAT_BaseWidget*     findChild(const char* AName)                                    { return nullptr; }
        virtual void                showOwner(SAT_WidgetOwner* AOwner)                              { }
        virtual void                hideOwner(SAT_WidgetOwner* AOwner)                              { }

    public: // visual

        virtual void                setOpaque(bool AState=true)                                     { }
        virtual void                setVisible(bool AState=true)                                    { }
        virtual void                setChildrenVisible(bool AState=true)                            { }
        virtual void                setScale(sat_coord_t AScale)                                    { }
        virtual void                setSkin(SAT_Skin* ASkin, bool AReplace=true)                    { }
        virtual void                setChildrenSkin(SAT_Skin* ASkin, bool AReplace=true)            { }
        virtual void                setRect(SAT_Rect ARect)                                         { }
      //virtual void                setBaseRect(SAT_Rect ARect)                                     { }
        virtual bool                isOpaque()                                                      { return false; }
        virtual bool                isVisible()                                                     { return false; }
        virtual sat_coord_t         getScale()                                                      { return 1.0; }
        virtual SAT_Skin*           getSkin()                                                       { return nullptr; }
        virtual SAT_Rect            getRect()                                                       { return SAT_Rect(); }
        virtual SAT_Rect            getClipRect()                                                   { return SAT_Rect(); }
        virtual SAT_Rect            getContentRect()                                                { return SAT_Rect(); }
        virtual SAT_BaseWidget*     getOpaqueParent()                                               { return nullptr; }
        virtual SAT_BaseWidget*     findChildAt(int32_t AXpos, int32_t AYpos)                       { return nullptr; }
        virtual void                pushClip(SAT_PaintContext* AContext)                            { }
        virtual void                pushRecursiveClip(SAT_PaintContext* AContext)                   { }
        virtual void                popClip(SAT_PaintContext* AContext)                             { }
        virtual sat_coord_t         getPaintScale()                                                 { return 1.0; }
        virtual uint32_t            getPaintState()                                                 { return 0; }
        virtual void                paintChildren(SAT_PaintContext* AContext)                       { }
        virtual void                paintWidget(SAT_PaintContext* AContext, SAT_Widget* AWidget)    { }

    public: // layout

        virtual SAT_WidgetLayout*           getLayout() { return nullptr; }
        virtual SAT_WidgetLayoutHandler*    getLayoutHandler() { return nullptr; }

        virtual void                        realignChildren()                                       { }

    public: // interactive

        virtual void                setActive(bool AState=true)                                     { }
        virtual void                setChildrenActive(bool AState=true)                             { }
//        virtual void                setEnabled(bool AState=true)                                    { }
//        virtual void                setChildrenEnabled(bool AState=true)                            { }
        virtual bool                isActive()                                                      { return false; }
//        virtual bool                isEnabled()                                                     { return false; }
        //virtual void              activateVisibleChildren()                                       { }
        //virtual void              deactivateInvisibleChildren()                                   { }

    public: // value

        virtual uint32_t            getValueIndex()                                                 { return 0; }
        virtual sat_param_t         getValue()                                                      { return 0.0; }
        virtual sat_param_t         getValue(uint32_t AIndex)                                       { return 0.0; }
        virtual SAT_Parameter*      getParameter()                                                  { return nullptr; }
        virtual SAT_Parameter*      getParameter(uint32_t AIndex)                                   { return nullptr; }
        virtual void                setValueIndex(uint32_t AIndex)                                  { }
        virtual void                setValue(sat_param_t AValue)                                    { }
        virtual void                setValue(sat_param_t AValue, uint32_t AIndex)                   { }
        virtual void                setParameter(SAT_Parameter* AParameter)                         { }
        virtual void                setParameter(SAT_Parameter* AParameter, uint32_t AIndex)        { }

    public: // on_

        virtual void                on_widget_show(SAT_WidgetOwner* AOwner)                                                         { }
        virtual void                on_widget_hide(SAT_WidgetOwner* AOwner)                                                         { }
        virtual void                on_widget_paint(SAT_PaintContext* AContext)                                                     { }
        virtual void                on_widget_pre_paint(SAT_PaintContext* AContext)                                                 { }
        virtual void                on_widget_post_paint(SAT_PaintContext* AContext)                                                { }
        virtual void                on_widget_realign()                                                                             { }
        virtual SAT_Rect            on_widget_pre_align(SAT_Rect ARect)                                                             { return SAT_Rect(); }
        virtual SAT_Rect            on_widget_post_align(SAT_Rect ARect)                                                            { return SAT_Rect(); }
        virtual void                on_widget_timer(uint32_t ATimerId, double ADelta)                                               { }
        virtual void                on_widget_anim(uint32_t AId, uint32_t AType, uint32_t ANumValues, double* AValues)              { }
        virtual void                on_widget_notify(SAT_Widget* AWidget, uint32_t AType=SAT_WIDGET_NOTIFY_NONE, intptr_t AValue=0) { }

        virtual uint32_t            on_widget_mouse_event(SAT_MouseEvent* AEvent)                                                   { return SAT_MOUSE_EVENT_RESPONSE_NONE;  }
        virtual void                on_widget_mouse_gesture(SAT_MouseGesture* AGesture)                                             { }

        virtual uint32_t            on_widget_keyboard_event(uint32_t AEvent, SAT_KeyboardState* AState)                            { return SAT_MOUSE_EVENT_RESPONSE_NONE; }
        virtual void                on_widget_keyboard_gesture(uint32_t AGesture, SAT_KeyboardState* AState)                        {}

    public: // do_

        virtual void                do_widget_update(SAT_Widget* AWidget, uint32_t AIndex=0)                                        { }
        virtual void                do_widget_realign(SAT_Widget* AWidget, uint32_t AMode=SAT_WIDGET_REALIGN_PARENT)                { }
        virtual void                do_widget_redraw(SAT_Widget* AWidget, uint32_t AMode=SAT_WIDGET_REDRAW_SELF)                    { }
        virtual void                do_widget_anim(SAT_Widget* AWidget, SAT_AnimChain* AChain)                                      { }
        virtual void                do_widget_notify(SAT_Widget* AWidget, uint32_t AType=SAT_WIDGET_NOTIFY_NONE, int32_t AValue=0)  { }
        virtual void                do_widget_hint(SAT_Widget* AWidget, uint32_t AType, const char* AHint)                          { }
        virtual void                do_widget_modal(SAT_Widget* AWidget)                                                            { }
        virtual void                do_widget_cursor(SAT_Widget* AWidget, int32_t ACursor)                                          { }
        virtual void                do_widget_capture_mouse(SAT_Widget* AWidget)                                                    { }
        virtual void                do_widget_capture_keyboard(SAT_Widget* AWidget)                                                 { }

    public:

        SAT_WidgetLayout        Layout                              = {};
        SAT_WidgetOptions       Options                             = {};
        SAT_WidgetState         State                              = {};


};

#endif // 0
