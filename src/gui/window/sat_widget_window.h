#pragma once

#include "base/sat_base.h"
#include "base/system/sat_timer.h"
#include "gui/window/sat_paint_window.h"
#include "gui/window/sat_window_listener.h"
#include "gui/widget/sat_widget_owner.h"
#include "gui/sat_widget.h"

class SAT_Animator;
class SAT_KeyboardHandler;
class SAT_MouseHandler;

//------------------------------
// queues
//------------------------------

// typedef SAT_SPSCQueue<SAT_Widget*,SAT_UPDATE_QUEUE_SIZE>    SAT_WidgetUpdateQueue;
typedef SAT_SPSCQueue<SAT_Widget*,SAT_REALIGN_QUEUE_SIZE>   SAT_WidgetRealignQueue;
typedef SAT_SPSCQueue<SAT_Widget*,SAT_REDRAW_QUEUE_SIZE>    SAT_WidgetRedrawQueue;
typedef SAT_SPSCQueue<SAT_Widget*,SAT_PAINT_QUEUE_SIZE>     SAT_WidgetPaintQueue;

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_WidgetWindow
: public SAT_PaintWindow
, public SAT_Widget
, public SAT_WidgetOwner
, public SAT_TimerListener
{
    public:

        SAT_WidgetWindow(uint32_t AWidth, uint32_t AHeight, intptr_t AParent=0);
        virtual ~SAT_WidgetWindow();

    public:

        virtual SAT_Animator*           getAnimator()           { return nullptr; }
        virtual SAT_KeyboardHandler*    getKeyboardHandler()    { return nullptr; }
        virtual SAT_MouseHandler*       getMouseHandler()       { return nullptr; }

    public: // window

        virtual void        setListener(SAT_WindowListener* AListener);
        virtual sat_coord_t calcScale(uint32_t ANewWidth, uint32_t ANewHeight);
        virtual void        setHintWidget(SAT_Widget* AWidget);
        virtual void        showTooltip(SAT_Widget* AWidget, int32_t AXpos, int32_t AYpos);
        virtual void        hideTooltip();
        virtual SAT_Widget* findWidget(int32_t AXpos, int32_t AYpos);

    public: // timer

        virtual void        appendTimerWidget(SAT_Widget* AWidget);
        virtual void        removeTimerWidget(SAT_Widget* AWidget);
        virtual void        handleTimer(uint32_t ATimerId, double ADelta, bool AInTimerThread=false);

    public: // painting

        virtual void        paintWidgets(SAT_PaintContext* AContext);
        virtual void        paintBackground(SAT_PaintContext* AContext);
        virtual void        paintOverlay(SAT_PaintContext* AContext);

     private:

        void                on_timer_listener_update(SAT_Timer* ATimer, double ADelta) override;
        void                on_window_paint(SAT_PaintContext* AContext) override;

    public:

        void                on_window_show() override;
        void                on_window_hide() override;
     // void                on_window_move(int32_t AXpos, int32_t AYpos) override;
        void                on_window_resize(uint32_t AWidth, uint32_t AHeight) override;
     // void                on_window_mouse_click(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATime) override;
     // void                on_window_mouse_release(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATime) override;
     // void                on_window_mouse_move(int32_t AXpos, int32_t AYpos, uint32_t AState, uint32_t ATime) override;
     // void                on_window_mouse_enter(int32_t AXpos, int32_t AYpos, uint32_t ATime) override;
     // void                on_window_mouse_leave(int32_t AXpos, int32_t AYpos, uint32_t ATime) override;
     // void                on_window_key_press(uint32_t AKey, uint32_t AChar, uint32_t AState, uint32_t ATime) override;
     // void                on_window_key_release(uint32_t AKey, uint32_t AChar, uint32_t AState, uint32_t ATime) override;
     // void                on_window_client_message(uint32_t AData) override;  
        void                on_window_timer(uint32_t ATimerId, double ADelta) override;

    public:

        SAT_Painter*        do_widget_owner_get_painter(SAT_Widget* AWidget) override;
        uint32_t            do_widget_owner_get_width(SAT_Widget* AWidget) override;
        uint32_t            do_widget_owner_get_height(SAT_Widget* AWidget) override;
        sat_coord_t         do_widget_owner_get_scale(SAT_Widget* AWidget) override;
        bool                do_widget_owner_register_timer(SAT_Widget* AWidget) override;
        bool                do_widget_owner_unregister_timer(SAT_Widget* AWidget) override;

    public:

        void                do_widget_update(SAT_Widget* AWidget, uint32_t AIndex=0) override;
        void                do_widget_realign(SAT_Widget* AWidget, uint32_t AMode=SAT_WIDGET_REALIGN_PARENT) override;
        void                do_widget_redraw(SAT_Widget* AWidget, uint32_t AMode=SAT_WIDGET_REDRAW_SELF) override;
     // void                do_widget_anim(SAT_Widget* AWidget, SAT_AnimChain* AChain) override;
     // void                do_widget_notify(SAT_Widget* AWidget, uint32_t AType, int32_t AValue) override;
        void                do_widget_hint(SAT_Widget* AWidget, uint32_t AType, const char* AHint) override;
     // void                do_widget_modal(SAT_Widget* AWidget) override;
     // void                do_widget_cursor(SAT_Widget* AWidget, int32_t ACursor) override;
     // void                do_widget_capture_mouse(SAT_Widget* AWidget) override;
     // void                do_widget_capture_keyboard(SAT_Widget* AWidget) override;

    private:

        SAT_WindowListener*     MListener           = nullptr;

        SAT_WidgetRealignQueue  MRealignQueue       = {};
        SAT_WidgetRedrawQueue   MRedrawQueue        = {};
        SAT_WidgetPaintQueue    MPaintQueue         = {};
      //SAT_WidgetUpdateQueue   MUpdateQueue        = {};

        SAT_Timer               MTimer              = SAT_Timer(this);
        uint32_t                MCurrentTimerTick   = 0;
        SAT_WidgetArray         MTimerWidgets       = {};
        sat_atomic_bool_t       MTimerBlocked       {false};

        SAT_WidgetArray         MBackgroundWidgets  = {};
        SAT_WidgetArray         MOverlayWidgets     = {};
        SAT_Widget*             MHintReceiver       = nullptr;

        sat_atomic_bool_t       MIsClosing          {false};
        bool                    MNeedFullRepaint    = false;

        uint32_t                MInitialWidth       = 0;
        uint32_t                MInitialHeight      = 0;
        bool                    MProportional       = false;
        sat_coord_t             MWindowScale        = 1.0;

};

//----------------------------------------------------------------------
//
// implementation
//
//----------------------------------------------------------------------

SAT_WidgetWindow::SAT_WidgetWindow(uint32_t AWidth, uint32_t AHeight, intptr_t AParent)
: SAT_PaintWindow(AWidth, AHeight, AParent)
, SAT_Widget(SAT_Rect(AWidth,AHeight))
{
    MTypeName       = "SAT_WidgetWindow";
    MInitialWidth   = AWidth;
    MInitialHeight  = AHeight;
    MProportional   = false;
    MOpaqueParent   = this;
    MSkin           = SAT.GUI->SKINS.find("Default");
};

SAT_WidgetWindow::~SAT_WidgetWindow()
{
}

//------------------------------
// window
//------------------------------

void SAT_WidgetWindow::setListener(SAT_WindowListener* AListener)
{
    MListener = AListener;
}

// calculate scale
// how much we can scale the window proportionally from the initial/original size,
// and still fit within the new window size..

sat_coord_t SAT_WidgetWindow::calcScale(uint32_t ANewWidth, uint32_t ANewHeight)
{
    sat_coord_t scale = 1.0;
    if ((MInitialWidth > 0) && (MInitialHeight > 0))
    {
        sat_coord_t xscale = (sat_coord_t)ANewWidth  / (sat_coord_t)MInitialWidth;
        sat_coord_t yscale = (sat_coord_t)ANewHeight / (sat_coord_t)MInitialHeight;
        if (xscale < yscale) scale = xscale;
        else scale =  yscale;
    }
    return scale;
}

void SAT_WidgetWindow::setHintWidget(SAT_Widget* AWidget)
{
    MHintReceiver = AWidget;
}

void SAT_WidgetWindow::showTooltip(SAT_Widget* AWidget, int32_t AXpos, int32_t AYpos)
{
    SAT_PRINT("Show tooltip: pos %i,%i widget %s\n",AXpos,AYpos,AWidget->getTooltip());
}

// void SAT_WidgetWindow::updateTooltip(int32_t AXpos, int32_t AYpos, SAT_Widget* AWidget)
// {
// }

void SAT_WidgetWindow::hideTooltip()
{
    SAT_PRINT("Hide tooltip\n");
}

SAT_Widget* SAT_WidgetWindow::findWidget(int32_t AXpos, int32_t AYpos)
{
    return findChildAt(AXpos,AYpos);
}

//------------------------------
// timer
//------------------------------

void SAT_WidgetWindow::appendTimerWidget(SAT_Widget* AWidget)
{
    SAT_Assert(AWidget);
    MTimerWidgets.append(AWidget);
}

void SAT_WidgetWindow::removeTimerWidget(SAT_Widget* AWidget)
{
    SAT_Assert(AWidget);
    MTimerWidgets.remove(AWidget);
}

// TODO: widget redrawing originating from audio automation & modulation (MWidgetUpdateQueue?)
// AInTimerThread is true if we're called from a timer,
// or false if we have redirected it to the gui thread..

void SAT_WidgetWindow::handleTimer(uint32_t ATimerId, double ADelta, bool AInTimerThread)
{
    // ----- widget timers -----
    for (uint32_t i=0; i<MTimerWidgets.size(); i++)
    {
        MTimerWidgets[i]->on_widget_timer(ATimerId,ADelta);
    }
    // ----- realign queue -----
    uint32_t count = 0;
    SAT_Widget* widget;
    while (MRealignQueue.read(&widget))
    {
        widget->on_widget_realign();
        MRedrawQueue.write(widget);
        count += 1;
    }
    // SAT.STATISTICS.report_WindwRealignQueue(count);
    // ----- redraw queue -----
    count = 0;
    SAT_Rect update_rect;
    while (MRedrawQueue.read(&widget))
    {
        // .. possibly do some more checking and culling here..
        if (count == 0) update_rect = widget->MClipRect;
        else update_rect.combine(widget->MClipRect);

        MPaintQueue.write(widget);
        count += 1;
    }
    // SAT.STATISTICS.report_WindwRedrawQueue(count,rect);
    // ----- invalidate -----
    if (update_rect.isNotEmpty())
    {
        invalidate(update_rect.x,update_rect.y,update_rect.w,update_rect.h);
    }
    MCurrentTimerTick += 1;
    MTimerBlocked = false;
}

//------------------------------
// painting
//------------------------------

// paint widgets, after background have been drawn
// MNeedFullRepaint set in on_window_show and on_window_resize
// todo: lots of messy stuff here left from testing and debugging..
// needs to be cleaned up.. find out what's actually needed, etc..

void SAT_WidgetWindow::paintWidgets(SAT_PaintContext* AContext)
{
    uint32_t paint_count = 0;
    SAT_Widget* widget = nullptr;
    if (MNeedFullRepaint)
    {
        //SAT_PRINT("full repaint\n");
        while (MPaintQueue.read(&widget))
        {
            paint_count += 1;
        }
        // TODO: just pain self? (which means also the children..
        SAT_PRINT("painting all widgets\n");
        // for (uint32_t i=0; i<getNumChildren(); i++)
        // {
        //     widget = getChild(i);
        //     paintWidget(AContext,widget);
        // }

        paintWidget(AContext,this);
        //paintChildren(AContext);

        // SAT.STATISTICS.report_WindowPaintAll();
        MNeedFullRepaint = false;
    }
    else
    {
        while (MPaintQueue.read(&widget))
        {
            if (widget->MPrevPainted != AContext->current_frame)
            {
                SAT_Widget* opaque_parent = widget->MOpaqueParent;
                SAT_PRINT("painting: %s (opaque_parent: %s)\n",widget->getName(),opaque_parent->getName());
                // TODO: set clipping around this widget, even if we redraw parent?
                if (opaque_parent != widget) paintWidget(AContext,opaque_parent);
                else paintWidget(AContext,widget);
            }
            paint_count += 1;
        }
        // SAT.STATISTICS.report_WindowPaintQueue(paint_count);
    }
}

// draw any background widgets that intersect the update_rect

void SAT_WidgetWindow::paintBackground(SAT_PaintContext* AContext)
{
    for (uint32_t i=0; i<MBackgroundWidgets.size(); i++)
    {
        SAT_Widget* widget = MBackgroundWidgets[i];
        SAT_Rect rect = widget->MRect;
        if (rect.intersects(AContext->update_rect))
        {
            paintWidget(AContext,widget);
        }
    }
}

// draw any overlay widgets that intersect the update_rect

void SAT_WidgetWindow::paintOverlay(SAT_PaintContext* AContext)
{
    for (uint32_t i=0; i<MOverlayWidgets.size(); i++)
    {
        SAT_Widget* widget = MOverlayWidgets[i];
        SAT_Rect rect = widget->MRect;
        if (rect.intersects(AContext->update_rect))
        {
            paintWidget(AContext,widget);
        }
    }
}

//------------------------------
// private
//------------------------------

// [TIMER THREAD]
void SAT_WidgetWindow::on_timer_listener_update(SAT_Timer* ATimer, double ADelta)
{
    if (MTimerBlocked) return;
    if (MIsClosing) return;
    MTimerBlocked = true;
    #ifdef SAT_WINDOW_REDIRECT_TIMER_TO_GUI_THREAD
        sendClientMessage(SAT_WINDOW_USER_MESSAGE_TIMER,0);
        // see on_window_timer(), which will call handleTimer()...
    #else
        // don't do this! this is dagerous! handleTimer reads from the
        // MTimerWidgets array, calls MAnimator, writes to MRedrawQueue..
        handleTimer(ATimerId,ADelta,true);
    #endif
};

// clipping is set up (by SAT_PaintWindow)
// around the update_rect

void SAT_WidgetWindow::on_window_paint(SAT_PaintContext* AContext)
{
    paintBackground(AContext);
    paintWidgets(AContext);
    paintOverlay(AContext);
}

//------------------------------
// base window
//------------------------------

void SAT_WidgetWindow::on_window_show()
{
    MIsClosing = false;
    MTimerBlocked = false;
    MNeedFullRepaint = true;
    showOwner(this);
    realignChildren();
    MTimer.start(SAT_WINDOW_TIMER_MS);
}

void SAT_WidgetWindow::on_window_hide()
{
    MIsClosing = true;
    if (MTimer.isRunning()) MTimer.stop();
    hideOwner(this);
}

// void SAT_WidgetWindow::on_window_move(int32_t AXpos, int32_t AYpos)
// {
// }

void SAT_WidgetWindow::on_window_resize(uint32_t AWidth, uint32_t AHeight)
{
    MWindowScale = calcScale(AWidth,AHeight);
    Options.scale = MWindowScale;
    SAT_Rect rect = SAT_Rect(AWidth,AHeight);
    MRect = rect;
    MBaseRect = rect;
    MClipRect = rect;
    realignChildren();
    SAT_PaintWindow::windowResize(AWidth,AHeight);
    MNeedFullRepaint = true;
}

// void SAT_WidgetWindow::on_window_mouse_click(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATime)
// {
// }

// void SAT_WidgetWindow::on_window_mouse_release(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATime)
// {
// }

// void SAT_WidgetWindow::on_window_mouse_move(int32_t AXpos, int32_t AYpos, uint32_t AState, uint32_t ATime)
// {
// }

// void SAT_WidgetWindow::on_window_mouse_enter(int32_t AXpos, int32_t AYpos, uint32_t ATime)
// {
// }

// void SAT_WidgetWindow::on_window_mouse_leave(int32_t AXpos, int32_t AYpos, uint32_t ATime)
// {
// }

// void SAT_WidgetWindow::on_window_key_press(uint32_t AKey, uint32_t AChar, uint32_t AState, uint32_t ATime)
// {
// }

// void SAT_WidgetWindow::on_window_key_release(uint32_t AKey, uint32_t AChar, uint32_t AState, uint32_t ATime)
// {
// }

// void SAT_WidgetWindow::on_window_client_message(uint32_t AData)  
// {
// }

// [GUI THREAD]
void SAT_WidgetWindow::on_window_timer(uint32_t ATimerId, double ADelta)
{
    handleTimer(ATimerId,ADelta,false);
}

//------------------------------
// widget owner
//------------------------------

SAT_Painter* SAT_WidgetWindow::do_widget_owner_get_painter(SAT_Widget* AWidget)
{
    return getPainter();
}

uint32_t SAT_WidgetWindow::do_widget_owner_get_width(SAT_Widget* AWidget)
{
    return getWidth();
}

uint32_t SAT_WidgetWindow::do_widget_owner_get_height(SAT_Widget* AWidget)
{
    return getWidth();
}

sat_coord_t SAT_WidgetWindow::do_widget_owner_get_scale(SAT_Widget* AWidget)
{
    //return Options.scale;
    return MWindowScale;
}

bool SAT_WidgetWindow::do_widget_owner_register_timer(SAT_Widget* AWidget)
{
    MTimerWidgets.append(AWidget);
    return true;
}

bool SAT_WidgetWindow::do_widget_owner_unregister_timer(SAT_Widget* AWidget)
{
    MTimerWidgets.remove(AWidget);
    return true;
}

//------------------------------
// do_widget
//------------------------------

void SAT_WidgetWindow::do_widget_update(SAT_Widget* AWidget, uint32_t AIndex)
{
    void* parameter = AWidget->getParameter();
    if (MListener && parameter)
    {
        MListener->do_widget_update(AWidget,AIndex);
    }
}

void SAT_WidgetWindow::do_widget_realign(SAT_Widget* AWidget, uint32_t AMode)
{
    /*
        #ifdef SAT_NO_WINDOW_BUFFERING
            AWidget->realignChildren();
            AWidget->do_Widget_redraw(AWidget);
        #else
            MRealignQueue.write(AWidget);
        #endif
    */
    SAT_Widget* parent;
    switch (AMode)
    {
        case SAT_WIDGET_REALIGN_SELF:
            MRealignQueue.write(AWidget);
            break;
        case SAT_WIDGET_REALIGN_PARENT:
            parent = AWidget->MParent; // getParent();
            if (parent) MRealignQueue.write(parent);
            break;
        default:
            SAT_PRINT("Error! unhandled realign mode: %i\n",AMode);
            break;
    }
}

// we handle opaque_parent != widget in paintWidgets()

void SAT_WidgetWindow::do_widget_redraw(SAT_Widget* AWidget, uint32_t AMode)
{
    /*
        #ifdef SAT_NO_WINDOW_BUFFERING
            // if not buffered, we draw directly..
            SAT_Rect rect = AWidget->getRect();
            invalidate(rect.x,rect.y,rect.w,rect.h);
        #else
            MRedrawQueue.write(AWidget);
        #endif
    */
    SAT_Widget* parent;
    switch (AMode)
    {
        case SAT_WIDGET_REDRAW_SELF:
            MRedrawQueue.write(AWidget);
            break;
        case SAT_WIDGET_REDRAW_PARENT:
            parent = AWidget->MParent; // getParent();
            if (parent) MRedrawQueue.write(parent);
            break;
        //case SAT_WIDGET_REDRAW_OPAQUE_PARENT:
        //    parent = AWidget->getOpaqueParent();
        //    if (parent) MRedrawQueue.write(parent);
        //    break;
        default:
            SAT_PRINT("Error! unhandled redraw mode: %i\n",AMode);
            break;
    }
}

// void SAT_WidgetWindow::do_widget_anim(SAT_Widget* AWidget, SAT_AnimChain* AChain)
// {
// }

// void SAT_WidgetWindow::do_widget_notify(SAT_Widget* AWidget, uint32_t AType, int32_t AValue)
// {
// }

void SAT_WidgetWindow::do_widget_hint(SAT_Widget* AWidget, uint32_t AType, const char* AHint)
{
    if (!AHint) AHint = AWidget->getHint();
    if (MHintReceiver)
    {
        switch (AType)
        {
            case SAT_WIDGET_HINT_NORMAL:
                MHintReceiver->on_widget_notify(AWidget,SAT_WIDGET_NOTIFY_HINT,(intptr_t)AHint);
                break;
            case SAT_WIDGET_HINT_CLEAR:
                MHintReceiver->on_widget_notify(AWidget,SAT_WIDGET_NOTIFY_HINT,(intptr_t)AHint);
                break;
            default:
                SAT_PRINT("Error! unknown hint type: %i\n",AType);
        }
    }
}

// void SAT_WidgetWindow::do_widget_modal(SAT_Widget* AWidget)
// {
// }

// void SAT_WidgetWindow::do_widget_cursor(SAT_Widget* AWidget, int32_t ACursor)
// {
// }

// void SAT_WidgetWindow::do_widget_capture_mouse(SAT_Widget* AWidget)
// {
// }

// void SAT_WidgetWindow::do_widget_capture_keyboard(SAT_Widget* AWidget)
// {
// }
