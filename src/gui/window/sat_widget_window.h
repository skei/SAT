#pragma once

/*
    - widget_window is-a widget, sitting at the top of the widget hierarchy
    - widget handling & managing, events up and down the hierarchy
    - realigning, redrawing..
    - scaling, timer, queueing
*/

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
    public: // window
        virtual void            setListener(SAT_WindowListener* AListener);
        virtual void            setProportional(bool AProportional=true);
        virtual sat_coord_t     calcScale(uint32_t ANewWidth, uint32_t ANewHeight);
        virtual void            setHintWidget(SAT_Widget* AWidget);
     // virtual void            showPopup(SAT_Widget* AWidget, int32_t AXpos, int32_t AYpos);
     // virtual void            updatePopup(SAT_Widget* AWidget, int32_t AXpos, int32_t AYpos);
     // virtual void            hidePopup();
     // virtual void            showTooltip(SAT_Widget* AWidget, int32_t AXpos, int32_t AYpos);
     // virtual void            updateTooltip(SAT_Widget* AWidget, int32_t AXpos, int32_t AYpos);
     // virtual void            hideTooltip();
    public: // timer
        virtual void            appendTimerWidget(SAT_Widget* AWidget);
        virtual void            removeTimerWidget(SAT_Widget* AWidget);
        virtual void            handleTimer(uint32_t ATimerId, double ADelta, bool AInTimerThread=false);
    public: // painting
        virtual void            paintWidget(SAT_PaintContext* AContext, SAT_Widget* AWidget);
        virtual void            paintWidgets(SAT_PaintContext* AContext);
        virtual void            paintBackground(SAT_PaintContext* AContext);
        virtual void            paintOverlay(SAT_PaintContext* AContext);
    private:
        void                    on_timer_listener_update(SAT_Timer* ATimer, double ADelta) override;
        void                    on_window_paint(SAT_PaintContext* AContext) override;
    public:
        void                    on_window_show() override;
        void                    on_window_hide() override;
     // void                    on_window_move(int32_t AXpos, int32_t AYpos) override;
        void                    on_window_resize(uint32_t AWidth, uint32_t AHeight) override;
     // void                    on_window_mouse_click(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATime) override;
     // void                    on_window_mouse_release(int32_t AXpos, int32_t AYpos, uint32_t AButton, uint32_t AState, uint32_t ATime) override;
     // void                    on_window_mouse_move(int32_t AXpos, int32_t AYpos, uint32_t AState, uint32_t ATime) override;
     // void                    on_window_mouse_enter(int32_t AXpos, int32_t AYpos, uint32_t ATime) override;
     // void                    on_window_mouse_leave(int32_t AXpos, int32_t AYpos, uint32_t ATime) override;
     // void                    on_window_key_press(uint32_t AKey, uint32_t AChar, uint32_t AState, uint32_t ATime) override;
     // void                    on_window_key_release(uint32_t AKey, uint32_t AChar, uint32_t AState, uint32_t ATime) override;
     // void                    on_window_client_message(uint32_t AData) override;  
        void                    on_window_timer(uint32_t ATimerId, double ADelta) override;
    public:
        SAT_Painter*            do_widget_owner_get_painter(SAT_Widget* AWidget) override;
        bool                    do_widget_owner_register_timer(SAT_Widget* AWidget) override;
        bool                    do_widget_owner_unregister_timer(SAT_Widget* AWidget) override;
     // uint32_t                do_widget_owner_get_width(SAT_Widget* AWidget) override;
     // uint32_t                do_widget_owner_get_height(SAT_Widget* AWidget) override;
     // sat_coord_t             do_widget_owner_get_scale(SAT_Widget* AWidget) override;
    public:
        void                    do_widget_update(SAT_Widget* AWidget, uint32_t AIndex=0) override;
        void                    do_widget_realign(SAT_Widget* AWidget, uint32_t AMode=SAT_WIDGET_REALIGN_PARENT) override;
        void                    do_widget_redraw(SAT_Widget* AWidget, uint32_t AMode=SAT_WIDGET_REDRAW_SELF) override;
        void                    do_widget_anim(SAT_Widget* AWidget, SAT_AnimChain* AChain) override;
        void                    do_widget_notify(SAT_Widget* AWidget, uint32_t AType, intptr_t AValue) override;
        void                    do_widget_capture_mouse(SAT_Widget* AWidget) override;
        void                    do_widget_capture_keyboard(SAT_Widget* AWidget) override;
        void                    do_widget_cursor(SAT_Widget* AWidget, int32_t ACursor) override;
        void                    do_widget_modal(SAT_Widget* AWidget) override;
        void                    do_widget_hint(SAT_Widget* AWidget, uint32_t AType, const char* AHint=nullptr) override;
    public:
        virtual SAT_Animator*           getAnimator()           { return nullptr; }
        virtual SAT_KeyboardHandler*    getKeyboardHandler()    { return nullptr; }
        virtual SAT_MouseHandler*       getMouseHandler()       { return nullptr; }
    private:
        SAT_WindowListener*     MListener           = nullptr;
        SAT_WidgetRealignQueue  MRealignQueue       = {};
        SAT_WidgetRedrawQueue   MRedrawQueue        = {};
        SAT_WidgetPaintQueue    MPaintQueue         = {};
      //SAT_WidgetUpdateQueue   MUpdateQueue        = {};
        SAT_WidgetArray         MBackgroundWidgets  = {};
        SAT_WidgetArray         MOverlayWidgets     = {};
        SAT_WidgetArray         MTimerWidgets       = {};
        SAT_Timer               MTimer              = SAT_Timer(this);
        uint32_t                MCurrentTimerTick   = 0;
        sat_atomic_bool_t       MTimerBlocked       {false};
        sat_atomic_bool_t       MIsClosing          {false};
        SAT_Widget*             MHintReceiver       = nullptr;
        bool                    MNeedFullRepaint    = false;
        uint32_t                MInitialWidth       = 0;
        uint32_t                MInitialHeight      = 0;
        bool                    MProportional       = false;
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

void SAT_WidgetWindow::setProportional(bool AProportional)
{
    MProportional = AProportional;
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

// void SAT_WidgetWindow::showPopup(SAT_Widget* AWidget, int32_t AXpos, int32_t AYpos)
// {
//     SAT_PRINT("Show popup: pos %i,%i widget %s\n",AXpos,AYpos,AWidget->getName());
// }

// void SAT_WidgetWindow::updatePopup(int32_t AXpos, int32_t AYpos, SAT_Widget* AWidget)
// {
// }

// void SAT_WidgetWindow::hidePopup()
// {
//     SAT_PRINT("Hide popup\n");
// }

// void SAT_WidgetWindow::showTooltip(SAT_Widget* AWidget, int32_t AXpos, int32_t AYpos)
// {
//     SAT_PRINT("Show tooltip: pos %i,%i widget %s\n",AXpos,AYpos,AWidget->getTooltip());
// }

// void SAT_WidgetWindow::updateTooltip(int32_t AXpos, int32_t AYpos, SAT_Widget* AWidget)
// {
// }

// void SAT_WidgetWindow::hideTooltip()
// {
//     SAT_PRINT("Hide tooltip\n");
// }

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

// AInTimerThread is true if we're called from a timer, or false if we have redirected it to the gui thread..
// TODO: widget redrawing originating from audio automation & modulation (MWidgetUpdateQueue?)
// keeps track of current timer tck (for checking widget lst painted tick, etc..
// sets blocked to false before returning (see on_timer_listener_update)
// handles:
// - timer widgets
// - realign queue (realigning the widget/children, and posh the widget onto the redraw queue
// - redraw queue (pushing each widget to the paint queue)
//   while keeping track of a update_rect sporrounding all (to be) painted widgets
// - and finally, calls invalidate

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

// paint a widget, or if needed, its opaque parent.. calling widget->on_widget_paint
// checks for: widget visible, prev painted frame, update_rect intersection
// clipping is set around the widget (cliprect), even if we paint the opaque_parent

void SAT_WidgetWindow::paintWidget(SAT_PaintContext* AContext, SAT_Widget* AWidget)
{
    if (AWidget->MState.visible)
    {
        if (AWidget->MPrevPainted != AContext->current_frame)
        {
            if (AWidget->MRect.intersects(AContext->update_rect))
            {
                AWidget->pushClip(AContext);
                SAT_Widget* opaque_parent = AWidget->MOpaqueParent;
                if (opaque_parent != AWidget)
                {
                    opaque_parent->on_widget_paint(AContext);
                    opaque_parent->MPrevPainted = AContext->current_frame;
                }
                else
                {
                    AWidget->on_widget_paint(AContext);
                    AWidget->MPrevPainted = AContext->current_frame;
                }
                AWidget->popClip(AContext);
            }
        }
    }
}

// flush the paint queue, and draw all the widgets, calling PaintWidget for each one
// or, if MNeedFullRepaint, just flush the queue, and paint everything, paintWidget(window)
// (usually when we just opened the window, or resized it)

void SAT_WidgetWindow::paintWidgets(SAT_PaintContext* AContext)
{
    uint32_t paint_count = 0;
    SAT_Widget* widget = nullptr;
    if (MNeedFullRepaint)
    {
        while (MPaintQueue.read(&widget)) { paint_count += 1; }
        paintWidget(AContext,this);
        MNeedFullRepaint = false;
    }
    else
    {
        while (MPaintQueue.read(&widget))
        {
            paintWidget(AContext,widget);
            paint_count += 1;
        }
    }
}

// before painting widgets in MPaintQueue..
// draw (visible) background widgets that intersect the update_rect
// no MOpaqueParent or MPrevPainted check?
// calls widget->paintWidget, which sets up clipping (widget cliprect),

void SAT_WidgetWindow::paintBackground(SAT_PaintContext* AContext)
{
    for (uint32_t i=0; i<MBackgroundWidgets.size(); i++)
    {
        SAT_Widget* widget = MBackgroundWidgets[i];
        if (widget->MState.visible)
        {
            // if (widget->MPrevPainted != AContext->current_frame)
            if (widget->MRect.intersects(AContext->update_rect))
            {
                // SAT_Widget* opaque_parent = widget->MOpaqueParent;
                widget->paintWidget(AContext); // calls push/popClip
            }
        }
    }
}

// after painting widgets in MPaintQueue..
// draw (visible) overlay widgets that intersect the update_rect
// no MOpaqueParent or MPrevPainted check?
// calls widget->paintWidget, which sets up clipping (widget's cliprect)

void SAT_WidgetWindow::paintOverlay(SAT_PaintContext* AContext)
{
    for (uint32_t i=0; i<MOverlayWidgets.size(); i++)
    {
        SAT_Widget* widget = MOverlayWidgets[i];
        if (widget->MState.visible)
        {
            // if (widget->MPrevPainted != AContext->current_frame)
            if (widget->MRect.intersects(AContext->update_rect))
            {
                // SAT_Widget* opaque_parent = widget->MOpaqueParent;
                widget->paintWidget(AContext); // calls push/popClip
            }
        }
    }
}

//------------------------------
// private
//------------------------------

// called from a separate thread (different/increasing thread_id for each call)
// to be safe, we don't do much here.. just 'forward' it to the x11/gui thread by
// posting a user-message to the x11 server, and handle the message when it arrives
// in the event thread (in gui/event thread)
// sets blocked to true (set back to false at the end of handleTimer).. 
// if this is still true in the next timer tick, we just return, and wait for the next tick..
// if the window has just been closed, we just return (no more timer related events wanted)

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

// clipping is set up around the update_rect
// (SAT_PaintWindow - paintToScreen/Buffer)

void SAT_WidgetWindow::on_window_paint(SAT_PaintContext* AContext)
{
    paintBackground(AContext);
    paintWidgets(AContext);
    paintOverlay(AContext);
}

//------------------------------
// base window
//------------------------------

// called after the window appears on the screen (x11/map_notify)
// (just before starting the event thread)

void SAT_WidgetWindow::on_window_show()
{
    MIsClosing = false;
    MTimerBlocked = false;
    MNeedFullRepaint = true;
    showOwner(this);
    realignChildren();
    MTimer.start(SAT_WINDOW_TIMER_MS);
}

// called before we start shutting down the window
// (just before stopping the event thread)

void SAT_WidgetWindow::on_window_hide()
{
    MIsClosing = true;
    if (MTimer.isRunning()) MTimer.stop();
    hideOwner(this);
}

// void SAT_WidgetWindow::on_window_move(int32_t AXpos, int32_t AYpos)
// {
// }

// will we automatically receive a repaint message after the resize?
// (plugin editor?)
// if not, we might need to 'force' a redraw after resize..

void SAT_WidgetWindow::on_window_resize(uint32_t AWidth, uint32_t AHeight)
{
    // MWindowScale = calcScale(AWidth,AHeight);
    // Options.scale = MWindowScale;
    Options.scale = calcScale(AWidth,AHeight);
    SAT_Rect rect = SAT_Rect(AWidth,AHeight);
    MRect = rect;
    MBaseRect = rect;
    MClipRect = rect;
    realignChildren();
    MNeedFullRepaint = true;
    SAT_PaintWindow::on_window_resize(AWidth,AHeight); // windowResize;
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

// caled in the gui/event thread, after the timer callback posted a user message
// to the (x11) event queue..

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

// uint32_t SAT_WidgetWindow::do_widget_owner_get_width(SAT_Widget* AWidget)
// {
//     return getWidth();
// }

// uint32_t SAT_WidgetWindow::do_widget_owner_get_height(SAT_Widget* AWidget)
// {
//     return getWidth();
// }

// sat_coord_t SAT_WidgetWindow::do_widget_owner_get_scale(SAT_Widget* AWidget)
// {
//     //return Options.scale;
//     return 1.0;//MWindowScale;
// }

//------------------------------
// do_widget
//------------------------------

// let widget listener sort out the potential parameter connection,
// so we don't need to do anything related to parameters here..
// also, we might use the listener for other than plugin-related things,
// to get notified when some widget value change..

void SAT_WidgetWindow::do_widget_update(SAT_Widget* AWidget, uint32_t AIndex)
{
    // void* parameter = AWidget->getParameter();
    // if (MListener && parameter)
    // {
    //     MListener->do_widget_update(AWidget,AIndex);
    // }
    if (MListener) MListener->do_widget_update(AWidget,AIndex);
}

void SAT_WidgetWindow::do_widget_realign(SAT_Widget* AWidget, uint32_t AMode)
{
    // #ifdef SAT_NO_WINDOW_EVENT_QUEUE
    //     AWidget->realignChildren();
    //     AWidget->do_Widget_redraw(AWidget);
    // #else
    //     MRealignQueue.write(AWidget);
    // #endif
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

void SAT_WidgetWindow::do_widget_redraw(SAT_Widget* AWidget, uint32_t AMode)
{
    // #ifdef SAT_NO_WINDOW_EVENT_QUEUE
    //     // if not buffered, we draw directly..
    //     SAT_Rect rect = AWidget->getRect();
    //     invalidate(rect.x,rect.y,rect.w,rect.h);
    // #else
    //     MRedrawQueue.write(AWidget);
    // #endif
    SAT_Widget* parent;
    switch (AMode)
    {
        case SAT_WIDGET_REDRAW_SELF:
            MRedrawQueue.write(AWidget);
            break;
        case SAT_WIDGET_REDRAW_PARENT:
            parent = AWidget->MParent;
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

void SAT_WidgetWindow::do_widget_anim(SAT_Widget* AWidget, SAT_AnimChain* AChain)
{
}

void SAT_WidgetWindow::do_widget_notify(SAT_Widget* AWidget, uint32_t AType, intptr_t AValue)
{
}

void SAT_WidgetWindow::do_widget_capture_mouse(SAT_Widget* AWidget)
{
}

void SAT_WidgetWindow::do_widget_capture_keyboard(SAT_Widget* AWidget)
{
}

void SAT_WidgetWindow::do_widget_cursor(SAT_Widget* AWidget, int32_t ACursor)
{
}

void SAT_WidgetWindow::do_widget_modal(SAT_Widget* AWidget)
{
}

void SAT_WidgetWindow::do_widget_hint(SAT_Widget* AWidget, uint32_t AType, const char* AHint)
{
    if (MHintReceiver)
    {
        switch (AType)
        {
            case SAT_WIDGET_HINT_NORMAL:
                if (!AHint) AHint = AWidget->getHint();
                MHintReceiver->on_widget_notify(AWidget,SAT_WIDGET_NOTIFY_HINT,(intptr_t)AHint);
                break;
            case SAT_WIDGET_HINT_CLEAR:
                MHintReceiver->on_widget_notify(AWidget,SAT_WIDGET_NOTIFY_HINT,(intptr_t)"");
                break;
            default:
                SAT_PRINT("Error! unknown hint type: %i\n",AType);
        }
    }
}



