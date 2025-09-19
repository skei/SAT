#pragma once

#include "base/sat_base.h"
#include "gui/input/sat_base_input_handler.h"
#include "gui/input/sat_input_states.h"
#include "gui/input/sat_input_state.h"
#include "gui/window/sat_widget_window.h"
#include "gui/sat_widget.h"

#define SAT_MOUSE_CURSOR_STACK_SIZE 256
typedef SAT_Stack<int32_t,SAT_MOUSE_CURSOR_STACK_SIZE> SAT_CursorStack;

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_InputHandler
: public SAT_BaseInputHandler
{

    public:

        SAT_InputHandler(SAT_WidgetWindow* AWindow);
        virtual ~SAT_InputHandler();

    public:

        SAT_WidgetWindow*   getWindow()                         override    { return MWindow; }
        SAT_InputState*     getCurrentState()                   override    { return MCurrentState; }
        SAT_StateInfo*      getStateInfo()                      override    { return &MStateInfo; }
        double              getCurrentTime()                    override    { return MCurrentTime; }

    public:

        void                reset();

    public:

        bool                wantEvent(SAT_Widget* AWidget, uint32_t AEvent) override;
        bool                sendEvent(SAT_Widget* AWidget, uint32_t AEvent) override;
        bool                wantGesture(SAT_Widget* AWidget, uint32_t AGesture) override;
        void                sendGesture(SAT_Widget* AWidget, uint32_t AGesture) override;
      //bool                wantState(SAT_Widget* AWidget, uint32_t AGState) override;

        void                keyCapture(SAT_Widget* AWidget) override;
        void                mouseCapture(SAT_Widget* AWidget) override;
        void                modal(SAT_Widget* AWidget) override;

        void                setMouseCursor(int32_t ACursor) override;
        void                resetMouseCursor() override;
        void                showMouseCursor() override;
        void                hideMouseCursor() override;
        void                lockMouseCursor(SAT_Widget* AWidget) override;
        void                unlockMouseCursor() override;
        void                pushMouseCursor(int32_t ACursor) override;
        void                popMouseCursor() override;

        const char*         eventName(uint32_t AEvent) override;
        const char*         gestureName(uint32_t AGesture) override;
        const char*         stateName(int32_t AState) override;

    public:

        void                timer(double ADelta) override;
        void                mouseClick(SAT_MouseCoords APos, uint32_t AButton, uint32_t AState, uint32_t ATime) override;
        void                mouseRelease(SAT_MouseCoords APos, uint32_t AButton, uint32_t AState, uint32_t ATime) override;
        void                mouseMove(SAT_MouseCoords APos, uint32_t AState, uint32_t ATime) override;
        void                mouseEnter(SAT_MouseCoords APos, uint32_t ATime) override;
        void                mouseLeave(SAT_MouseCoords APos, uint32_t ATime) override;
        void                keyPress(uint32_t AKey, uint32_t AState, uint32_t ATime) override;
        void                keyRelease(uint32_t AKey, uint32_t AState, uint32_t ATime) override;

    private:

        void                setupStates();
        void                updateState(int32_t AState);
        void                updateMouse(bool AVisibleOnly=true, bool AActiveOnly=false);
        SAT_MouseCoords     adjustMouseCoords(SAT_MouseCoords APos);

    private:

        SAT_WidgetWindow*   MWindow                                 = nullptr;
        SAT_InputState*     MInputStates[SAT_INPUT_STATE_COUNT]     = {};
        SAT_StateInfo       MStateInfo                              = {};
        SAT_InputEvent      MEvent                                  = {};
        SAT_InputGesture    MGesture                                = {};
        SAT_CursorStack     MCursorStack                            = {};
        SAT_InputState*     MCurrentState                           = nullptr;
        double              MCurrentTime                            = 0.0;
        int32_t             MCurrentCursor                          = SAT_MOUSE_CURSOR_DEFAULT;
        bool                MLockedCursor                           = false;
        SAT_MouseCoords     MLockedCursorPos                        = {0,0};
        SAT_MouseCoords     MLockedCursorVirtualPos                 = {0,0};
        SAT_Widget*         MLockedCursorWidget                     = nullptr;

        SAT_Widget*         MKeyCaptureWidget                       = nullptr;
        SAT_Widget*         MMouseCaptureWidget                     = nullptr;
        SAT_Widget*         MModalWidget                            = nullptr;

    private: // internal

        char    MGestureNameBuffer[SAT_MAX_NAME_LENGTH] = {0};
};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

SAT_InputHandler::SAT_InputHandler(SAT_WidgetWindow* AWindow)
: SAT_BaseInputHandler()
{
    MWindow             = AWindow;
    MEvent.stateInfo    = &MStateInfo;
    MEvent.handler      = this;
    MGesture.stateInfo  = &MStateInfo;
    MGesture.handler    = this;
    setupStates();
    //reset();
}

SAT_InputHandler::~SAT_InputHandler()
{
    #ifndef SAT_NO_AUTODELETE
        for (uint32_t i=0; i<SAT_INPUT_STATE_COUNT; i++) delete MInputStates[i];
    #endif
    // SAT_Assert(MCursorStack.isEmpty());
}

//------------------------------
//
//------------------------------

void SAT_InputHandler::reset()
{
    SAT_TRACE;
    MCursorStack.reset();
    // for (uint32_t i=0; i<SAT_MOUSE_BUTTON_COUNT; i++) MClickedWidgets[i] = nullptr;
    MCurrentCursor          = SAT_MOUSE_CURSOR_DEFAULT;
    MCurrentTime            = 0.0;
    MLockedCursor           = false;
  //MCapturedWidget         = nullptr;
  //MModalWidget            = nullptr;
    MStateInfo.hoverWidget  = nullptr;
    MStateInfo.activePos    = {0,0};
    MStateInfo.activeButton = SAT_MOUSE_BUTTON_NONE;
    MStateInfo.activeWidget = nullptr;
    MStateInfo.activeTime   = 0.0;
    MStateInfo.activeKey    = SAT_KEY_NONE;
    MCurrentState           = nullptr;
    updateState(SAT_INPUT_STATE_IDLE);
}

//------------------------------
//
//------------------------------

bool SAT_InputHandler::wantEvent(SAT_Widget* AWidget, uint32_t AEvent)
{
    return (AWidget->Options.wantInputEvents & AEvent);
}

bool SAT_InputHandler::wantGesture(SAT_Widget* AWidget, uint32_t AGesture)
{
    return (AWidget->Options.wantInputGestures & AGesture);
}

// return false if event should be ignored..

bool SAT_InputHandler::sendEvent(SAT_Widget* AWidget, uint32_t AEvent)
{
    MEvent.type = AEvent;
    uint32_t response = SAT_INPUT_EVENT_RESPONSE_NONE;
    if (AWidget && (AWidget->Options.wantInputEvents & AEvent))
    {
        response = AWidget->on_widget_input_event(&MEvent);
    }
    switch (response)
    {
        case SAT_INPUT_EVENT_RESPONSE_NONE:
            return true;
        case SAT_INPUT_EVENT_RESPONSE_IGNORE:
            return false;
        // case SAT_INPUT_EVENT_RESPONSE_CAPTURE:
        //     captureWidget(AWidget);
        //     return true;
        // case SAT_INPUT_EVENT_RESPONSE_RELEASE:
        //     captureWidget(nullptr);
        //     return true;
    }
    return true;
}

void SAT_InputHandler::sendGesture(SAT_Widget* AWidget, uint32_t AGesture)
{
    MGesture.type = AGesture;
    if (AWidget && (AWidget->Options.wantInputGestures & AGesture))
    {
        AWidget->on_widget_input_gesture(&MGesture);
    }
}

void SAT_InputHandler::keyCapture(SAT_Widget* AWidget)
{
    MKeyCaptureWidget = AWidget;
}

void SAT_InputHandler::mouseCapture(SAT_Widget* AWidget)
{
    MMouseCaptureWidget = AWidget;
}

void SAT_InputHandler::modal(SAT_Widget* AWidget)
{
    MModalWidget = AWidget;
}

//------------------------------
//
//------------------------------

void SAT_InputHandler::setMouseCursor(int32_t ACursor)
{
    // SAT_PRINT("%i\n",ACursor);
    if (ACursor != MCurrentCursor)
    {
        if (MWindow) MWindow->setMouseCursorShape(ACursor);
        MCurrentCursor = ACursor;
    }
}

void SAT_InputHandler::resetMouseCursor()
{
    // SAT_TRACE;
    if (MCurrentCursor != SAT_MOUSE_CURSOR_DEFAULT)
    {
        if (MWindow) MWindow->setMouseCursorShape(SAT_MOUSE_CURSOR_DEFAULT);
        MCurrentCursor = SAT_MOUSE_CURSOR_DEFAULT;
    }
}

void SAT_InputHandler::showMouseCursor()
{
    // SAT_TRACE;
    if (MWindow)
    {
        MWindow->showMouseCursor();
        MWindow->setMouseCursorShape(MCurrentCursor);
    }
}

void SAT_InputHandler::hideMouseCursor()
{
    // SAT_TRACE;
    if (MWindow) MWindow->hideMouseCursor();
}

void SAT_InputHandler::lockMouseCursor(SAT_Widget* AWidget)
{
    // if (AWidget) { SAT_PRINT("%s\n",AWidget->getName()); }
    // else { SAT_TRACE; }
    MLockedCursor           = true;
    MLockedCursorPos        = MStateInfo.mousePos;
    MLockedCursorVirtualPos = MStateInfo.mousePos;
    MLockedCursorWidget     = AWidget;
}

void SAT_InputHandler::unlockMouseCursor()
{
    // SAT_TRACE;
    MLockedCursor       = false;
    MLockedCursorWidget = nullptr;
}

void SAT_InputHandler::pushMouseCursor(int32_t ACursor)
{
    // SAT_PRINT("%i\n",ACursor);
    MCursorStack.push(MCurrentCursor);
    setMouseCursor(ACursor);
}

void SAT_InputHandler::popMouseCursor()
{
    // SAT_TRACE;
    int32_t cursor = MCursorStack.pop();
    setMouseCursor(cursor);
}

//------------------------------
//
//------------------------------

const char* SAT_InputHandler::eventName(uint32_t AEvent)
{
    switch (AEvent)
    {
        case SAT_INPUT_EVENT_NONE:          return "NONE";
        case SAT_INPUT_EVENT_MOUSE_CLICK:   return "MOUSE_CLICK";
        case SAT_INPUT_EVENT_MOUSE_RELEASE: return "MOUSE_RELEASE";
        case SAT_INPUT_EVENT_MOUSE_MOVE:    return "MOUSE_MOVE";
        case SAT_INPUT_EVENT_MOUSE_ENTER:   return "MOUSE_ENTER";
        case SAT_INPUT_EVENT_MOUSE_LEAVE:   return "MOUSE_LEAVE";
        case SAT_INPUT_EVENT_KEY_PRESS:     return "KEY_PRESS";
        case SAT_INPUT_EVENT_KEY_RELEASE:   return "KEY_RELEASE";
        default:                            return "UNKNOWN";
    }
    return "?";
}

const char* SAT_InputHandler::gestureName(uint32_t AGesture)
{
    if (AGesture == SAT_INPUT_GESTURE_NONE)     return "NONE";
    if (AGesture == SAT_INPUT_GESTURE_ALL)      return "ALL";
    MGestureNameBuffer[0] = 0;
    if (AGesture & SAT_INPUT_GESTURE_BEGIN)         strcat(MGestureNameBuffer,"BEGIN ");
    if (AGesture & SAT_INPUT_GESTURE_END)           strcat(MGestureNameBuffer,"END ");
    if (AGesture & SAT_INPUT_GESTURE_LONG)          strcat(MGestureNameBuffer,"LONG ");
    if (AGesture & SAT_INPUT_GESTURE_DOUBLE)        strcat(MGestureNameBuffer,"DOUBLE ");
    if (AGesture & SAT_INPUT_GESTURE_DUAL)          strcat(MGestureNameBuffer,"DUAL ");
    if (AGesture & SAT_INPUT_GESTURE_DRAG)          strcat(MGestureNameBuffer,"DRAG ");
    if (AGesture & SAT_INPUT_GESTURE_HOVER)         strcat(MGestureNameBuffer,"HOVER ");
    if (AGesture & SAT_INPUT_GESTURE_MOUSE_CLICK)   strcat(MGestureNameBuffer,"MOUSE CLICK");
    if (AGesture & SAT_INPUT_GESTURE_MOUSE_RELEASE) strcat(MGestureNameBuffer,"MOUSE RELEASE");
    if (AGesture & SAT_INPUT_GESTURE_MOUSE_DRAG)    strcat(MGestureNameBuffer,"MOUSE DRAG");
    if (AGesture & SAT_INPUT_GESTURE_MOUSE_HOVER)   strcat(MGestureNameBuffer,"MOUSE HOVER");
    if (AGesture & SAT_INPUT_GESTURE_KEY_PRESS)     strcat(MGestureNameBuffer,"KEY PRESS");
    if (AGesture & SAT_INPUT_GESTURE_KEY_RELEASE)   strcat(MGestureNameBuffer,"KEY RELEASE");
    return MGestureNameBuffer;
}

const char* SAT_InputHandler::stateName(int32_t AState)
{
    if (AState == SAT_INPUT_STATE_NONE) return "NONE";
    return MInputStates[AState]->name;
}

//------------------------------
//
//------------------------------

void SAT_InputHandler::timer(double ADelta)
{
    int32_t state = MCurrentState->timer(ADelta);
    updateState(state);
    MStateInfo.currentTime = MCurrentTime;
    MCurrentTime += ADelta;
}

void SAT_InputHandler::mouseClick(SAT_MouseCoords APos, uint32_t AButton, uint32_t AState, uint32_t ATime)
{
    MStateInfo.mousePos     = APos;
    MStateInfo.mouseButton  = AButton;
    MStateInfo.modKeys      = AState;
    MStateInfo.time         = MCurrentTime;
    //MClickedWidgets[AButton] = MStateInfo.hover_widget;
    if (sendEvent(MStateInfo.hoverWidget,SAT_INPUT_EVENT_MOUSE_CLICK))
    {
        int32_t state = MCurrentState->mouseClick(&MEvent);
        updateState(state);
    }
}

void SAT_InputHandler::mouseRelease(SAT_MouseCoords APos, uint32_t AButton, uint32_t AState, uint32_t ATime)
{
    MStateInfo.mousePos     = APos;
    MStateInfo.mouseButton  = AButton;
    MStateInfo.modKeys      = AState;
    MStateInfo.time         = MCurrentTime;
    if (sendEvent(MStateInfo.hoverWidget,SAT_INPUT_EVENT_MOUSE_RELEASE))
    {
        int32_t state = MCurrentState->mouseRelease(&MEvent);
        updateState(state);
    }
    //MClickedWidgets[AButton] = nullptr;
}

void SAT_InputHandler::mouseMove(SAT_MouseCoords APos, uint32_t AState, uint32_t ATime)
{
    MStateInfo.mousePos     = adjustMouseCoords(APos);
    MStateInfo.mouseButton  = SAT_MOUSE_BUTTON_NONE;
    MStateInfo.modKeys      = AState;
    MStateInfo.time         = MCurrentTime;
    updateMouse(false,true);
    if (sendEvent(MStateInfo.hoverWidget,SAT_INPUT_EVENT_MOUSE_MOVE))
    {
        int32_t state = MCurrentState->mouseMove(&MEvent);
        updateState(state);
    }
}

void SAT_InputHandler::mouseEnter(SAT_MouseCoords APos, uint32_t ATime)
{
    MStateInfo.mousePos     = APos;
    MStateInfo.mouseButton  = SAT_MOUSE_BUTTON_NONE;
    MStateInfo.modKeys      = SAT_MOD_KEY_NONE;
    MStateInfo.time         = MCurrentTime;
    updateMouse(false,true);
}

void SAT_InputHandler::mouseLeave(SAT_MouseCoords APos, uint32_t ATime)
{
    MStateInfo.mousePos     = APos;
    MStateInfo.mouseButton  = SAT_MOUSE_BUTTON_NONE;
    MStateInfo.modKeys      = SAT_MOD_KEY_NONE;
    MStateInfo.time         = MCurrentTime;
    MStateInfo.hoverWidget  = nullptr;
}

// send to activeWidget.. key-captured?

void SAT_InputHandler::keyPress(uint32_t AKey, uint32_t AState, uint32_t ATime)
{
    MStateInfo.key          = AKey;
    MStateInfo.modKeys      = AState;
    MStateInfo.time         = MCurrentTime;
    if (sendEvent(MKeyCaptureWidget,SAT_INPUT_EVENT_KEY_PRESS))
    {
        int32_t state = MCurrentState->keyPress(&MEvent);
        updateState(state);
    }
}

void SAT_InputHandler::keyRelease(uint32_t AKey, uint32_t AState, uint32_t ATime)
{
    MStateInfo.key          = AKey;
    MStateInfo.modKeys      = AState;
    MStateInfo.time         = MCurrentTime;
    if (sendEvent(MMouseCaptureWidget,SAT_INPUT_EVENT_KEY_RELEASE))
    {
        int32_t state = MCurrentState->keyRelease(&MEvent);
        updateState(state);
    }
}

//------------------------------
//
//------------------------------

void SAT_InputHandler::setupStates()
{
    MInputStates[SAT_INPUT_STATE_IDLE]              = new SAT_IdleInputState(this);
    MInputStates[SAT_INPUT_STATE_MOUSE_CLICKED]     = new SAT_MouseClickedInputState(this);
    MInputStates[SAT_INPUT_STATE_MOUSE_DRAGGING]    = new SAT_MouseDraggingInputState(this);
    MInputStates[SAT_INPUT_STATE_MOUSE_RELEASED]    = new SAT_MouseReleasedInputState(this);
    MInputStates[SAT_INPUT_STATE_MOUSE_HOVERING]    = new SAT_MouseHoveringInputState(this);
}

void SAT_InputHandler::updateState(int32_t AState)
{
    SAT_Assert(AState < SAT_INPUT_STATE_COUNT);
    if (AState == SAT_INPUT_STATE_NONE) return;
    int32_t from_state = SAT_INPUT_STATE_NONE;
    int32_t to_state = AState;

    // if (MStateInfo.active_widget->Options.wantStates & to_state)
    // {
    // }

    if (MCurrentState)
    {
        from_state = MCurrentState->type;
        if (from_state == to_state) return;
        MCurrentState->leave(to_state);
    }
    MCurrentState = MInputStates[to_state];
    //MEvent.state = MCurrentState;
    //MGesture.state = MCurrentState;
    MCurrentState->enter(from_state);
}

void SAT_InputHandler::updateMouse(bool AVisibleOnly, bool AActiveOnly)
{
    SAT_Widget* widget = MWindow->findChildAt(MStateInfo.mousePos.x,MStateInfo.mousePos.y,AVisibleOnly,AActiveOnly);
    if (widget != MStateInfo.hoverWidget)
    {
        if (sendEvent(MStateInfo.hoverWidget,SAT_INPUT_EVENT_MOUSE_LEAVE))
        {
            //MHoverWidget = nullptr;
        }
        if (sendEvent(widget,SAT_INPUT_EVENT_MOUSE_ENTER))
        {
            //MHoverWidget = widget;
        }
    }
    MStateInfo.hoverWidget = widget;
    //if (MCapturedWidget) MActiveWidget = MCapturedWidget;
    //else MActiveWidget = MHoverWidget;
}

SAT_MouseCoords SAT_InputHandler::adjustMouseCoords(SAT_MouseCoords APos)
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

