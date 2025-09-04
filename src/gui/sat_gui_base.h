#pragma once

#include "base/sat_base.h"
#include "gui/sat_gui_system.h"

class SAT_Painter;
class SAT_Renderer;
class SAT_Surface;
class SAT_Window;

class SAT_BaseWidget;

//----------------------------------------------------------------------
//
// painter
//
//----------------------------------------------------------------------

struct SAT_PaintContext
{
    SAT_Painter*    painter         = nullptr;
    SAT_Rect        update_rect     = {};
    uint32_t        current_frame   = 0;
    double          current_time    = 0.0;
    double          previous_time   = 0.0;
};

//------------------------------

class SAT_BasePainter
{
    public:
        SAT_BasePainter(SAT_PainterOwner* AOwner, SAT_PaintTarget* ATarget) {}
        virtual ~SAT_BasePainter() {}
    public:
        virtual void        beginPainting(uint32_t AWidth, uint32_t AHeight) = 0;
        virtual void        endPainting() = 0;
        virtual void        setClip(SAT_Rect ARect) = 0;
        virtual void        resetClip() = 0;
    public: // state
        virtual void        setDrawColor(SAT_Color AColor) = 0;
        virtual void        setFillColor(SAT_Color AColor) = 0;
        virtual void        setTextColor(SAT_Color AColor) = 0;
        virtual void        setLineWidth(sat_coord_t AWidth) = 0;
    public: // raster
        virtual void        drawLine(SAT_Point AFrom, SAT_Point ATo) = 0;
        virtual void        drawRect(SAT_Rect ARect) = 0;
        virtual void        drawArc(SAT_Point APos, sat_coord_t ARadius, sat_coord_t AAngle1, sat_coord_t AAngle2) = 0;
        virtual void        fillRect(SAT_Rect ARect) = 0;
        virtual void        fillArc(SAT_Point APos, sat_coord_t ARadius, sat_coord_t AAngle1, sat_coord_t AAngle2) = 0;
        virtual void        drawText(SAT_Point APos, const char* AText) = 0;
        virtual void        drawText(SAT_Rect ARect, const char* AText, uint32_t AAlignment) = 0;
        virtual sat_coord_t getTextBounds(const char* AText, sat_coord_t* ABounds) = 0;
        virtual sat_coord_t getTextWidth(const char* AText) = 0;
        virtual sat_coord_t getTextHeight(const char* AText) = 0;
        virtual void        drawImage(SAT_Point APos, SAT_PaintSource* ASource) = 0;
        virtual void        drawImage(SAT_Point APos, SAT_PaintSource* ASource, SAT_Rect ASrc) = 0;
        virtual void        drawImage(SAT_Rect ADst, SAT_PaintSource* ASource, SAT_Rect ASrc) = 0;
    public: // vector
        // TODO
};

//----------------------------------------------------------------------
//
// renderer
//
//----------------------------------------------------------------------

struct SAT_RenderContext
{
    SAT_Renderer*   renderer    = nullptr;
};

//------------------------------

class SAT_BaseRenderer
{
    public:
        SAT_BaseRenderer(SAT_RendererOwner* AOwner, SAT_RenderTarget* ATarget) {}
        virtual ~SAT_BaseRenderer() {}
    public:
        virtual bool makeCurrent() = 0;
        virtual bool resetCurrent() = 0;
        virtual bool beginRendering() = 0;
        virtual bool beginRendering(int32_t AWidth, int32_t AHeight) = 0;
        virtual bool endRendering() = 0;
        virtual bool setViewport(int32_t AXpos, int32_t AYpos, int32_t AWidth, int32_t AHeight) = 0;
        virtual bool swapBuffers() = 0;
        virtual bool enableVSync() = 0;
        virtual bool disableVSync() = 0;
};

//----------------------------------------------------------------------
//
// surface
//
//----------------------------------------------------------------------

class SAT_BaseSurface
{
   public:
        SAT_BaseSurface(SAT_SurfaceOwner* AOwner, uint32_t AWidth, uint32_t AHeight, uint32_t ADepth=0) {}
        virtual ~SAT_BaseSurface() {}
    public:
     // virtual void fill(SAT_Color AColor) = 0;
     // virtual void uploadBitmap(SAT_Bitmap* ABitmap) = 0;
};

//----------------------------------------------------------------------
//
// widget
//
//----------------------------------------------------------------------

class SAT_WidgetOwner
{
    public:
        virtual SAT_Painter*    do_widget_owner_get_painter(SAT_BaseWidget* AWidget)        { return nullptr; }
        virtual uint32_t        do_widget_owner_get_width(SAT_BaseWidget* AWidget)          { return 0; }
        virtual uint32_t        do_widget_owner_get_height(SAT_BaseWidget* AWidget)         { return 0; }
        virtual sat_coord_t     do_widget_owner_get_scale(SAT_BaseWidget* AWidget)          { return 1.0; }
        virtual bool            do_widget_owner_register_timer(SAT_BaseWidget* AWidget)     { return false; }
        virtual bool            do_widget_owner_unregister_timer(SAT_BaseWidget* AWidget)   { return false; }
};

//----------------------------------------------------------------------
//
// window
//
//----------------------------------------------------------------------

class SAT_WindowListener
{
    public:
        virtual void do_widget_update(SAT_BaseWidget* AWidget, uint32_t AIndex=0);
};

//------------------------------

class SAT_BaseWindow
{
    public:
        SAT_BaseWindow(uint32_t AWidth, uint32_t AHeight, intptr_t AParent=0) {}
        virtual ~SAT_BaseWindow() {}
    public:
        virtual uint32_t    getWidth() = 0;
        virtual uint32_t    getHeight() = 0;
    public:
        virtual void        show() = 0;
        virtual void        hide() = 0;
        virtual void        setPos(int32_t AXpos, int32_t AYpos) = 0;
        virtual void        setSize(uint32_t AWidth, uint32_t AHeight) = 0;
        virtual void        setTitle(const char* ATitle) = 0;
        virtual void        showMouseCursor() = 0;
        virtual void        hideMouseCursor() = 0;
        virtual void        grabMouseCursor() = 0;
        virtual void        releaseMouseCursor() = 0;
        virtual void        setMouseCursorPos(int32_t AXpos, int32_t AYpos) = 0;
        virtual void        setMouseCursorShape(int32_t ACursor) = 0;
        virtual void        reparent(intptr_t AParent) = 0;
        virtual void        invalidate(int32_t AXpos, int32_t AYpos, uint32_t AWidth, uint32_t AHeight) = 0;
        virtual void        sendClientMessage(uint32_t AData, uint32_t AType) = 0;
        virtual void        eventLoop() = 0;
        virtual void        startEventThread() = 0;
        virtual void        stopEventThread() = 0;
    public:
        virtual void        on_window_show() {}
        virtual void        on_window_hide() {}
        virtual void        on_window_move(int32_t AXpos, int32_t AYpos) {}
        virtual void        on_window_resize(uint32_t AWidth, uint32_t AHeight) {}
        virtual void        on_window_paint(int32_t AXpos, int32_t AYpos, uint32_t AWidth, uint32_t AHeight) {}
        virtual void        on_window_mouse_click(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATime) {}
        virtual void        on_window_mouse_release(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATime) {}
        virtual void        on_window_mouse_move(int32_t AXpos, int32_t AYpos, uint32_t AState, uint32_t ATime) {}
        virtual void        on_window_key_press(uint32_t AKey, uint32_t AChar, uint32_t AState, uint32_t ATime) {}
        virtual void        on_window_key_release(uint32_t AKey, uint32_t AChar, uint32_t AState, uint32_t ATime) {}
        virtual void        on_window_mouse_enter(int32_t AXpos, int32_t AYpos, uint32_t ATime) {}
        virtual void        on_window_mouse_leave(int32_t AXpos, int32_t AYpos, uint32_t ATime) {}
        virtual void        on_window_client_message(uint32_t AData) {}  
        virtual void        on_window_timer(uint32_t ATimerId, double ADelta) {}
};

