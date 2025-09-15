#pragma once

#include "base/sat_base.h"
#include "gui/mouse/sat_base_mouse_handler.h"
#include "gui/mouse/sat_mouse_states.h"
#include "gui/mouse/sat_mouse_state.h"
#include "gui/window/sat_widget_window.h"
#include "gui/sat_widget.h"

#define SAT_MOUSE_CURSOR_STACK_SIZE 256
typedef SAT_Stack<int32_t,SAT_MOUSE_CURSOR_STACK_SIZE> SAT_CursorStack;

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_MouseHandler
: public SAT_BaseMouseHandler
{

    //friend class SAT_Window;

    public:

        SAT_MouseHandler(SAT_WidgetWindow* AWindow);
        virtual ~SAT_MouseHandler();

    public:

        SAT_WidgetWindow*   getWindow()         override    { return nullptr; }
        SAT_MouseState*     getCurrentState()   override    { return MCurrentState; }
        SAT_MouseEvent*     getEvent()          override    { return &MEvent; }
        double              getCurrentTime()    override    { return MCurrentTime; }
        SAT_Widget*         getHoverWidget()    override    { return MHoverWidget; }
        SAT_Widget*         getActiveWidget()   override    { return MActiveWidget; }
        SAT_Widget*         getCapturedWidget() override    { return MCapturedWidget; }

    public:

        void                captureWidget(SAT_Widget* AWidget) override;
        void                setCursor(int32_t ACursor) override;
        void                resetCursor() override;
        void                showCursor() override;
        void                hideCursor() override;
        void                lockCursor(SAT_Widget* AWidget) override;
        void                unlockCursor() override;
        void                pushCursor(int32_t ACursor) override;
        void                popCursor() override;

        const char*         eventName(uint32_t AEvent) override;
        const char*         gestureName(uint32_t AGesture) override;
        const char*         stateName(int32_t AState) override;

    public:

        void                timer(double ADelta) override;
        void                click(SAT_MouseCoords APos, uint32_t AButton, uint32_t AState, uint32_t ATime) override;
        void                release(SAT_MouseCoords APos, uint32_t AButton, uint32_t AState, uint32_t ATime) override;
        void                move(SAT_MouseCoords APos, uint32_t AState, uint32_t ATime) override;
        void                enter(SAT_MouseCoords APos, uint32_t ATime) override;
        void                leave(SAT_MouseCoords APos, uint32_t ATime) override;

    public:

        void                reset();

    private:

        void                setupStates();
        bool                sendEvent(SAT_Widget* AWidget, SAT_MouseEvent* AEvent);
        void                updateState(int32_t AState);
        void                updateHover(SAT_MouseEvent* AEvent);
        SAT_MouseCoords     adjustPos(SAT_MouseCoords APos);

    private:

        SAT_WidgetWindow*   MWindow                             = nullptr;
        SAT_MouseState*     MCurrentState                       = nullptr;
        SAT_MouseState*     MMouseStates[SAT_MOUSE_STATE_COUNT] = {};
        SAT_MouseEvent      MEvent                              = {};
        double              MCurrentTime                        = 0.0;
        SAT_CursorStack     MCursorStack                        = {};
        int32_t             MCurrentCursor                      = SAT_MOUSE_CURSOR_DEFAULT;
        bool                MLockedCursor                       = false;
        SAT_MouseCoords     MLockedCursorPos                    = {0,0};
        SAT_MouseCoords     MLockedCursorVirtualPos             = {0,0};
        SAT_Widget*         MLockedCursorWidget                 = nullptr;
        SAT_Widget*         MHoverWidget                        = nullptr;
        SAT_Widget*         MActiveWidget                       = nullptr;
        SAT_Widget*         MCapturedWidget                     = nullptr;
        SAT_MouseCoords     MCurrentPos                         = {0,0};
};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

SAT_MouseHandler::SAT_MouseHandler(SAT_WidgetWindow* AWindow)
: SAT_BaseMouseHandler()
{
    MWindow = AWindow;
    setupStates();
    reset();
}

SAT_MouseHandler::~SAT_MouseHandler()
{
    #ifndef SAT_NO_AUTODELETE
        for (uint32_t i=0; i<SAT_MOUSE_STATE_COUNT; i++) delete MMouseStates[i];
    #endif
    // SAT_Assert(MCursorStack.isEmpty());
}

//------------------------------
//
//------------------------------

void SAT_MouseHandler::captureWidget(SAT_Widget* AWidget)
{
    MCapturedWidget = AWidget;
    if (MCapturedWidget) MActiveWidget = AWidget;
    else MActiveWidget = MHoverWidget;
}

void SAT_MouseHandler::setCursor(int32_t ACursor)
{
    // SAT_PRINT("%i\n",ACursor);
    if (ACursor != MCurrentCursor)
    {
        if (MWindow) MWindow->setMouseCursorShape(ACursor);
        MCurrentCursor = ACursor;
    }
}

void SAT_MouseHandler::resetCursor()
{
    // SAT_TRACE;
    if (MCurrentCursor != SAT_MOUSE_CURSOR_DEFAULT)
    {
        if (MWindow) MWindow->setMouseCursorShape(SAT_MOUSE_CURSOR_DEFAULT);
        MCurrentCursor = SAT_MOUSE_CURSOR_DEFAULT;
    }
}

void SAT_MouseHandler::showCursor()
{
    // SAT_TRACE;
    if (MWindow)
    {
        MWindow->showMouseCursor();
        MWindow->setMouseCursorShape(MCurrentCursor);
    }
}

void SAT_MouseHandler::hideCursor()
{
    // SAT_TRACE;
    if (MWindow) MWindow->hideMouseCursor();
}

void SAT_MouseHandler::lockCursor(SAT_Widget* AWidget)
{
    // if (AWidget) { SAT_PRINT("%s\n",AWidget->getName()); }
    // else { SAT_TRACE; }
    MLockedCursor = true;
    MLockedCursorPos = MCurrentPos;
    MLockedCursorVirtualPos = MCurrentPos;
    MLockedCursorWidget = AWidget;
}

void SAT_MouseHandler::unlockCursor()
{
    // SAT_TRACE;
    MLockedCursor = false;
    MLockedCursorWidget = nullptr;
}

void SAT_MouseHandler::pushCursor(int32_t ACursor)
{
    // SAT_PRINT("%i\n",ACursor);
    MCursorStack.push(MCurrentCursor);
    setCursor(ACursor);
}

void SAT_MouseHandler::popCursor()
{
    // SAT_TRACE;
    int32_t cursor = MCursorStack.pop();
    setCursor(cursor);
}

const char* SAT_MouseHandler::eventName(uint32_t AEvent)
{
    switch (AEvent)
    {
        case SAT_MOUSE_EVENT_NONE:      return "NONE";
        case SAT_MOUSE_EVENT_CLICK:     return "CLICK";
        case SAT_MOUSE_EVENT_RELEASE:   return "RELEASE";
        case SAT_MOUSE_EVENT_MOVE:      return "MOVE";
        case SAT_MOUSE_EVENT_ENTER:     return "ENTER";
        case SAT_MOUSE_EVENT_LEAVE:     return "LEAVE";
        default:                        return "UNKNOWN";
    }
    return "?";
}

const char* SAT_MouseHandler::gestureName(uint32_t AGesture)
{
    switch (AGesture)
    {
        case SAT_MOUSE_GESTURE_NONE:            return "NONE";
        case SAT_MOUSE_GESTURE_CLICK:           return "CLICK";
        case SAT_MOUSE_GESTURE_RELEASE:         return "RELEASE";
        case SAT_MOUSE_GESTURE_DRAG:            return "DRAG";
        case SAT_MOUSE_GESTURE_DOUBLE_CLICK:    return "DOUBLE CLICK";
        case SAT_MOUSE_GESTURE_DOUBLE_RELEASE:  return "DOUBLE_RELEASE";
        case SAT_MOUSE_GESTURE_DOUBLE_DRAG:     return "DOUBLE DRAG";
        case SAT_MOUSE_GESTURE_LONG_CLICK:      return "LONG CLICK";
        case SAT_MOUSE_GESTURE_LONG_RELEASE:    return "LONG RELEASE";
        case SAT_MOUSE_GESTURE_LONG_DRAG:       return "LONG DRAG";
        default:                                return "UNKNOWN";
    }
    return "?";
}

const char* SAT_MouseHandler::stateName(int32_t AState)
{
    switch (AState)
    {
        case SAT_MOUSE_STATE_NONE:              return "NONE";
        case SAT_MOUSE_STATE_IDLE:              return "IDLE";
        case SAT_MOUSE_STATE_CLICKED:           return "CLICKED";
        case SAT_MOUSE_STATE_DRAGGING:          return "DRAGGING";
        case SAT_MOUSE_STATE_RELEASED:          return "RELEASED";
        case SAT_MOUSE_STATE_DOUBLE_CLICKED:    return "DOUBLE CLICKED";
        case SAT_MOUSE_STATE_DOUBLE_DRAGGING:   return "DOUBLE DRAGGING";
        case SAT_MOUSE_STATE_DOUBLE_RELEASED:   return "DOUBLE RELEASED";
        case SAT_MOUSE_STATE_LONG_CLICKED:      return "CLICKED";
        case SAT_MOUSE_STATE_LONG_DRAGGING:     return "LONG CLICKED";
        case SAT_MOUSE_STATE_LONG_RELEASED:     return "LONG DRAGGING";
        default:                                return "UNKNOWN";
    }
    return "?";
}

//------------------------------
//
//------------------------------

void SAT_MouseHandler::timer(double ADelta)
{
    int32_t state = MCurrentState->timer(ADelta);
    updateState(state);
    MCurrentTime += ADelta;
}

void SAT_MouseHandler::click(SAT_MouseCoords APos, uint32_t AButton, uint32_t AState, uint32_t ATime)
{
    MEvent.type     = SAT_MOUSE_EVENT_CLICK;
    MEvent.pos      = APos;
    MEvent.button   = AButton;
    MEvent.modkeys  = AState;
    MEvent.time     = MCurrentTime;
    if (sendEvent(MActiveWidget,&MEvent))
    {
        int32_t state = MCurrentState->click(&MEvent);
        updateState(state);
    }
}

void SAT_MouseHandler::release(SAT_MouseCoords APos, uint32_t AButton, uint32_t AState, uint32_t ATime)
{
    MEvent.type     = SAT_MOUSE_EVENT_RELEASE;
    MEvent.pos      = APos;
    MEvent.button   = AButton;
    MEvent.modkeys  = AState;
    MEvent.time     = MCurrentTime;
    if (sendEvent(MActiveWidget,&MEvent))
    {
        int32_t state = MCurrentState->release(&MEvent);
        updateState(state);
    }
}

void SAT_MouseHandler::move(SAT_MouseCoords APos, uint32_t AState, uint32_t ATime)
{
    MEvent.type     = SAT_MOUSE_EVENT_MOVE;
    MEvent.pos      = APos;
    MEvent.button   = SAT_MOUSE_BUTTON_NONE;
    MEvent.modkeys  = AState;
    MEvent.time     = MCurrentTime;
    APos = adjustPos(APos);
    updateHover(&MEvent);
    MEvent.type = SAT_MOUSE_EVENT_MOVE;
    if (sendEvent(MActiveWidget,&MEvent))
    {
        int32_t state = MCurrentState->move(&MEvent);
        updateState(state);
    }
}

void SAT_MouseHandler::enter(SAT_MouseCoords APos, uint32_t ATime)
{
    // MEvent.type     = SAT_MOUSE_EVENT_ENTER;
    // MEvent.pos      = APos;
    // MEvent.button   = SAT_MOUSE_BUTTON_NONE;
    // MEvent.modkeys  = SAT_STATE_KEY_NONE;
    // MEvent.time     = MCurrentTime;
    updateHover(&MEvent);
}

void SAT_MouseHandler::leave(SAT_MouseCoords APos, uint32_t ATime)
{
    // MEvent.type     = SAT_MOUSE_EVENT_LEAVE;
    // MEvent.pos      = APos;
    // MEvent.button   = SAT_MOUSE_BUTTON_NONE;
    // MEvent.modkeys  = SAT_STATE_KEY_NONE;
    // MEvent.time     = MCurrentTime;
    MHoverWidget = nullptr;
}

//------------------------------
//
//------------------------------

void SAT_MouseHandler::reset()
{
    MCursorStack.reset();
    MEvent.handler = this;
    MCurrentTime = 0.0;
    MHoverWidget = nullptr;
    MActiveWidget = nullptr;
    MCapturedWidget = nullptr;
    MCurrentState = nullptr;
    updateState(SAT_MOUSE_STATE_IDLE);
}

//------------------------------
//
//------------------------------

void SAT_MouseHandler::setupStates()
{
    MMouseStates[SAT_MOUSE_STATE_IDLE]              = new SAT_IdleMouseState(this);
    MMouseStates[SAT_MOUSE_STATE_CLICKED]           = new SAT_ClickedMouseState(this);
    MMouseStates[SAT_MOUSE_STATE_DRAGGING]          = new SAT_DraggingMouseState(this);
    MMouseStates[SAT_MOUSE_STATE_RELEASED]          = new SAT_ReleasedMouseState(this);
    MMouseStates[SAT_MOUSE_STATE_DOUBLE_CLICKED]    = new SAT_DoubleClickedMouseState(this);
    MMouseStates[SAT_MOUSE_STATE_DOUBLE_DRAGGING]   = new SAT_DoubleDraggingMouseState(this);
    MMouseStates[SAT_MOUSE_STATE_DOUBLE_RELEASED]   = new SAT_DoubleReleasedMouseState(this);
    MMouseStates[SAT_MOUSE_STATE_LONG_CLICKED]      = new SAT_LongClickedMouseState(this);
    MMouseStates[SAT_MOUSE_STATE_LONG_DRAGGING]     = new SAT_LongDraggingMouseState(this);
    MMouseStates[SAT_MOUSE_STATE_LONG_RELEASED]     = new SAT_LongReleasedMouseState(this);
}

// return false if event shopuld be ignored..

bool SAT_MouseHandler::sendEvent(SAT_Widget* AWidget, SAT_MouseEvent* AEvent)
{
    uint32_t response = SAT_MOUSE_EVENT_RESPONSE_NONE;
    if (AWidget && AWidget->Options.wantMouseEvents & MEvent.type)
    {
        response = AWidget->on_widget_mouse_event(&MEvent);
    }
    switch (response)
    {
        case SAT_MOUSE_EVENT_RESPONSE_NONE:
            return true;
        case SAT_MOUSE_EVENT_RESPONSE_IGNORE:
            return false;
        case SAT_MOUSE_EVENT_RESPONSE_CAPTURE:
            captureWidget(AWidget);
            return true;
        case SAT_MOUSE_EVENT_RESPONSE_RELEASE:
            captureWidget(nullptr);
            return true;
    }
    return true;
}

void SAT_MouseHandler::updateState(int32_t AState)
{
    SAT_Assert(AState < SAT_MOUSE_STATE_COUNT);
    if (AState == SAT_MOUSE_STATE_NONE) return;
    int32_t from_state = SAT_MOUSE_STATE_NONE;
    int32_t to_state = AState;
    if (MCurrentState)
    {
        from_state = MCurrentState->type;
        if (from_state == to_state) return;
        MCurrentState->leave(to_state);
    }
    MCurrentState = MMouseStates[to_state];
    MCurrentState->enter(from_state);
}

void SAT_MouseHandler::updateHover(SAT_MouseEvent* AEvent)
{
    SAT_Widget* widget = MWindow->findChildAt(AEvent->pos.x,AEvent->pos.y);
    if (widget != MHoverWidget)
    {
        AEvent->type = SAT_MOUSE_EVENT_LEAVE;
        if (sendEvent(MHoverWidget,&MEvent))
        {
            //MHoverWidget = nullptr;
        }
        AEvent->type = SAT_MOUSE_EVENT_ENTER;
        if (sendEvent(widget,&MEvent))
        {
            //MHoverWidget = widget;
        }
    }
    MHoverWidget = widget;
    if (MCapturedWidget) MActiveWidget = MCapturedWidget;
    else MActiveWidget = MHoverWidget;
}

SAT_MouseCoords SAT_MouseHandler::adjustPos(SAT_MouseCoords APos)
{
    if (MLockedCursor)
    {
        if ((APos.x != MLockedCursorPos.x) || (APos.y != MLockedCursorPos.y))
        {
            int32_t xdiff = APos.x - MLockedCursorPos.x;
            int32_t ydiff = APos.y - MLockedCursorPos.y;
            MLockedCursorVirtualPos.x += xdiff;
            MLockedCursorVirtualPos.y += ydiff;
            MWindow->setMouseCursorPos(MLockedCursorPos.x,MLockedCursorPos.y);
            return MLockedCursorVirtualPos;
        }
    }
    return APos;
}
















//------------------------------
//
//------------------------------

#if 0

//------------------------------
//
//------------------------------

void SAT_MouseHandler::captureWidget(SAT_Widget* AWidget)
{
    if (AWidget) {
        //SAT_PRINT("capturing %s\n",AWidget->getName());
        if (capturedWidget)
        {
            if (capturedWidget->State.captured)
            {
                SAT_PRINT("%s is already captured!\n",capturedWidget->getName());
            }
            else
            {
                SAT_PRINT("%s is already captured! but its state is NOT captured!\n",capturedWidget->getName());
            }
        }
        else
        {
            capturedWidget = AWidget;
            AWidget->State.captured = true;
            activeWidget = AWidget;
        }
    }
    else
    {
        if (capturedWidget)
        {
            //SAT_PRINT("releasing %s\n",MCapturedWidget->getName());
            capturedWidget->State.captured = false;
            capturedWidget = nullptr;
            activeWidget = currentWidget;
        }
        else
        {
            SAT_PRINT("no widget is captured!\n");
        }
    }
}


//------------------------------
//
//------------------------------

void SAT_MouseHandler::timer(double ADelta)
{
    currentTime += ADelta;
    // SAT_PRINT("MCurrentTime %.3f MPrevTimeMoved %.3f\n",MCurrentTime,MPrevTimeMoved);
    if (!MCurrentState) return;
    int32_t state = MCurrentState->timer(ADelta);
    changeState(state);
}

void SAT_MouseHandler::click(SAT_MouseCoords APos, uint32_t AButton, uint32_t AState, uint32_t ATime)
{

    prevClickedPos = clickedPos;
    prevClickedButton = clickedButton;
    prevClickedTime = clickedTime;
    prevClickedWidget = clickedWidget;

    clickedPos = APos;
    clickedButton = AButton;
    clickedModKeys = AState;
    clickedTime = currentTime;
    clickedWidget = currentWidget;
    currentButtons |= (uint32_t)(1 << (AButton - 1));
    if (!MCurrentState) return;

    //debugPrintState("click: ");

    //int32_t event_response = sendEvent(MCurrentWidget,SAT_MOUSE_EVENT_CLICK);
    //if (handleResponse(MCurrentWidget,event_response))
    int32_t event_response = sendEvent(activeWidget,SAT_MOUSE_EVENT_CLICK);
    if (handleResponse(activeWidget,event_response))
    {
        int32_t state = MCurrentState->click(APos,AButton,AState,ATime);
        changeState(state);
    }
}

void SAT_MouseHandler::release(SAT_MouseCoords APos, uint32_t AButton, uint32_t AState, uint32_t ATime)
{
    releasedPos = APos;
    releasedButton = AButton;
    releasedModKeys = AState;
    releasedTime = currentTime;
    releasedWidget = currentWidget;
    currentButtons &= ~(uint32_t)(1 << (AButton - 1));
    if (!MCurrentState) return;

    //debugPrintState("release: ");

    //int32_t event_response = sendEvent(MCurrentWidget,SAT_MOUSE_EVENT_RELEASE);
    //if (handleResponse(MCurrentWidget,event_response))
    int32_t event_response = sendEvent(activeWidget,SAT_MOUSE_EVENT_RELEASE);

    /*
        ouch.. if we release widget from capture (in handleResponse),
        MActiveWidget & MCurrentWidget is set to currently hovering widget :-/
        and it will receive the release..
    */

    if (handleResponse(activeWidget,event_response))
    {
        int32_t state = MCurrentState->release(APos,AButton,AState,ATime);
        changeState(state);
    }
}

void SAT_MouseHandler::move(SAT_MouseCoords APos, uint32_t AState, uint32_t ATime)
{
    APos = adjustPos(APos);
    prevPos = currentPos;
    prevTimeMoved = currentTime;
    currentPos = APos;
    currentModKeys = AState;
    prevWidget = currentWidget;
    currentWidget = MWindow->findChildAt(APos.x,APos.y);
    if (!MCurrentState) return;

    //debugPrintState("move (pre): ");

    if (currentWidget != prevWidget)
    {
        int32_t leave_response = sendEvent(prevWidget,SAT_MOUSE_EVENT_LEAVE);
        handleResponse(prevWidget,leave_response);
        int32_t enter_response = sendEvent(currentWidget,SAT_MOUSE_EVENT_ENTER);
        handleResponse(currentWidget,enter_response);
    }

    if (capturedWidget) activeWidget = capturedWidget;
    else activeWidget = currentWidget;

    //debugPrintState("move (post): ");

    //int32_t event_response = sendEvent(MCurrentWidget,SAT_MOUSE_EVENT_MOVE);
    //if (handleResponse(MCurrentWidget,event_response))
    int32_t event_response = sendEvent(activeWidget,SAT_MOUSE_EVENT_MOVE);
    if (handleResponse(activeWidget,event_response))
    {
        int32_t state = MCurrentState->move(APos,AState,ATime);
        changeState(state);
    }
}

void SAT_MouseHandler::enter(SAT_MouseCoords APos, uint32_t ATime)
{
    prevWidget = MWindow; // nullptr;
    currentPos = APos;
    currentWidget = MWindow->findChildAt(APos.x,APos.y);
    if (!MCurrentState) return;

    //debugPrintState("enter (pre): ");

    if (capturedWidget) activeWidget = capturedWidget;
    else activeWidget = currentWidget;

    //debugPrintState("enter (post): ");

    // int32_t event_response = sendEvent(MCurrentWidget,SAT_MOUSE_EVENT_ENTER);
    // if (handleResponse(MCurrentWidget,event_response))
    int32_t event_response = sendEvent(activeWidget,SAT_MOUSE_EVENT_ENTER);
    if (handleResponse(activeWidget,event_response))
    {
    }
}

void SAT_MouseHandler::leave(SAT_MouseCoords APos, uint32_t ATime)
{
    prevWidget = currentWidget;
    currentWidget = MWindow; // nullptr;
    if (!MCurrentState) return;
    
    // int32_t event_response = sendEvent(MPrevWidget,SAT_MOUSE_EVENT_LEAVE);
    // if (handleResponse(MPrevWidget,event_response))
    int32_t event_response = sendEvent(activeWidget,SAT_MOUSE_EVENT_LEAVE);
    if (handleResponse(activeWidget,event_response))
    {
    }
}

//------------------------------
//
//------------------------------

void SAT_MouseHandler::changeState(int32_t AState)
{
    SAT_Assert(AState < SAT_MOUSE_STATE_COUNT);
    if (AState >= 0)
    {
        if (MCurrentState)
        {
            int32_t prev_state = MCurrentState->id();
            if (AState != prev_state)
            {
                MCurrentState->leaveState(AState);
                MCurrentState = MMouseStates[AState];
                MCurrentState->enterState(prev_state);
                MWindow->changeMouseState(MCurrentState);
            }
        }
        else
        {
            MCurrentState = MMouseStates[AState];
            MCurrentState->enterState(SAT_MOUSE_STATE_NONE);
            MWindow->changeMouseState(MCurrentState);
        }
    }
}


uint32_t SAT_MouseHandler::sendEvent(SAT_Widget* AWidget, uint32_t AEvent)
{
    uint32_t retval = SAT_MOUSE_EVENT_RESPONSE_NONE;
    if (AWidget && (AWidget->Options.wantMouseEvents & AEvent))
    {
        SAT_MouseEvent event = 
        {
            // .type    = AEvent;
            // .pos     = currentPos;
            // .button  = 
            // .modkeys = 
            // .time    = 
        };
        retval = AWidget->on_widget_mouse_event(&event,this);
    }
    return retval;
}

bool SAT_MouseHandler::handleResponse(SAT_Widget* AWidget, uint32_t AResponse)
{
    switch (AResponse)
    {
        case SAT_MOUSE_EVENT_RESPONSE_NONE:
            return true;
        case SAT_MOUSE_EVENT_RESPONSE_IGNORE:
            return false;
        case SAT_MOUSE_EVENT_RESPONSE_CAPTURE:
            SAT_PRINT("capturing %s\n",AWidget->getName());
            captureWidget(AWidget);
            return true;
        case SAT_MOUSE_EVENT_RESPONSE_RELEASE:
            SAT_PRINT("releasing %s\n",capturedWidget->getName());
            captureWidget(nullptr);
            return true;
        default:
            return true;
    }
    return true;
}

void SAT_MouseHandler::debugPrintState(const char* prefix)
{
    const char* current = "(null)";
    const char* captured = "(null)";
    const char* active = "(null)";
    if (currentWidget) current = currentWidget->getName();
    if (capturedWidget) captured = capturedWidget->getName();
    if (activeWidget) active = activeWidget->getName();
    SAT_DPRINT("%s current '%s' captured '%s' active '%s' \n",prefix,current,captured,active);
}

#endif // 0