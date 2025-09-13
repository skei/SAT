#pragma once

#include "base/sat_base.h"
#include "gui/mouse/sat_base_mouse_handler.h"
#include "gui/window/sat_base_window.h"
#include "gui/sat_widget.h"

//------------------------------
//
//------------------------------


//------------------------------
//
//------------------------------

#define SAT_DEFAULT_MOUSE_STATE(State)          \
    public:                                     \
        State(SAT_BaseMouseHandler* AHandler)   \
        : SAT_MouseState(AHandler) {}           \
        virtual ~State() {}

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_MouseState
{
    public:
        SAT_MouseState(SAT_BaseMouseHandler* AHandler);
        virtual ~SAT_MouseState();

    public:

        virtual uint32_t        id();
        virtual void            enterState(int32_t AFromState);
        virtual void            leaveState(int32_t AToState);

        virtual int32_t         timer(double ADelta);
        virtual int32_t         click(SAT_MouseCoords APos, uint32_t AButton, uint32_t AState, uint32_t ATime);
        virtual int32_t         release(SAT_MouseCoords APos, uint32_t AButton, uint32_t AState, uint32_t ATime);
        virtual int32_t         move(SAT_MouseCoords APos, uint32_t AState, uint32_t ATime);

    public:

        void                    activeButton(uint32_t AButton)  { MHandler->MActiveButton = AButton; };
        uint32_t                activeButton()                  { return MHandler->MActiveButton; };

        void                    activePos(SAT_MouseCoords APos) { MHandler->MActivePos = APos; };
        SAT_MouseCoords         activePos()                     { return MHandler->MActivePos; };

        void                    activeTime(double ATime)        { MHandler->MActiveTime = ATime; };
        double                  activeTime()                    { return MHandler->MActiveTime; };

        double                  currentTime()       { return MHandler->MCurrentTime; }
        SAT_MouseCoords         currentPos()        { return MHandler->MCurrentPos; }
        uint32_t                currentButtons()    { return MHandler->MCurrentButtons; }
        uint32_t                currentModKeys()    { return MHandler->MCurrentModKeys; }
        SAT_Widget*             currentWidget()     { return MHandler->MCurrentWidget; }
        int32_t                 currentCursor()     { return MHandler->MCurrentCursor; }

        SAT_MouseCoords         prevClickedPos()    { return MHandler->MPrevClickedPos; }
        uint32_t                prevClickedButton() { return MHandler->MPrevClickedButton; }
        double                  prevClickedTime()   { return MHandler->MPrevClickedTime; }
        SAT_Widget*             prevClickedWidget() { return MHandler->MPrevClickedWidget; }

        SAT_MouseCoords         prevPos()           { return MHandler->MPrevPos; }
        double                  prevTimeMoved()     { return MHandler->MPrevTimeMoved; }
        SAT_Widget*             prevWidget()        { return MHandler->MPrevWidget; }
        int32_t                 prevCursor()        { return MHandler->MPrevCursor; }

        SAT_MouseCoords         clickedPos()        { return MHandler->MClickedPos; }
        uint32_t                clickedButton()     { return MHandler->MClickedButton; }
        uint32_t                clickedModKeys()    { return MHandler->MClickedModKeys; }
        double                  clickedTime()       { return MHandler->MClickedTime; }
        SAT_Widget*             clickedWidget()     { return MHandler->MClickedWidget; }

        SAT_MouseCoords         releasedPos()       { return MHandler->MReleasedPos; }
        uint32_t                releasedButton()    { return MHandler->MReleasedButton; }
        uint32_t                releasedModKeys()   { return MHandler->MReleasedModKeys; }
        double                  releasedTime()      { return MHandler->MReleasedTime; }
        SAT_Widget*             releasedWidget()    { return MHandler->MReleasedWidget; }

        bool                    locked()            { return MHandler->MLocked; }
        SAT_MouseCoords         lockedPos()         { return MHandler->MLockedPos; }
        SAT_MouseCoords         lockedVirtualPos()  { return MHandler->MLockedVirtualPos; }
        SAT_Widget*             lockedWidget()      { return MHandler->MLockedWidget; }

        SAT_Widget*             capturedWidget()    { return MHandler->MCapturedWidget; }

    protected:

        uint32_t                sendEvent(SAT_Widget* AWidget, uint32_t AEvent);

    protected:

        SAT_BaseMouseHandler*   MHandler    = nullptr;
        SAT_WidgetWindow*       MWindow     = nullptr;
};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

SAT_MouseState::SAT_MouseState(SAT_BaseMouseHandler* AHandler)
{
    MHandler = AHandler;
    MWindow = AHandler->getWindow();
}

SAT_MouseState::~SAT_MouseState()
{
}

//------------------------------
//
//------------------------------

uint32_t SAT_MouseState::id()
{
    return SAT_MOUSE_STATE_IDLE;
}

void SAT_MouseState::enterState(int32_t AFromState)
{
    // SAT_PRINT("enterState from %i -> return %i\n",AFromState,id());
}

void SAT_MouseState::leaveState(int32_t AToState)
{
    // SAT_PRINT("leaveState to %i -> return %i\n",AToState,AToState);
}

//------------------------------
//
//------------------------------

int32_t SAT_MouseState::timer(double ADelta)
{
    return SAT_MOUSE_STATE_NONE;
}

int32_t SAT_MouseState::click(SAT_MouseCoords APos, uint32_t AButton, uint32_t AState, uint32_t ATime)
{
    return SAT_MOUSE_STATE_NONE;
}

int32_t SAT_MouseState::release(SAT_MouseCoords APos, uint32_t AButton, uint32_t AState, uint32_t ATime)
{
    return SAT_MOUSE_STATE_NONE;
}

int32_t SAT_MouseState::move(SAT_MouseCoords APos, uint32_t AState, uint32_t ATime)
{
    return SAT_MOUSE_STATE_NONE;
}

//------------------------------
//
//------------------------------

uint32_t SAT_MouseState::sendEvent(SAT_Widget* AWidget, uint32_t AEvent)
{
    if (AWidget && (AWidget->Options.wantMouseEvents & AEvent))
    {
        uint32_t retval = AWidget->on_widget_mouse_event(AEvent,this);
        return retval;
    }
    return SAT_MOUSE_EVENT_RESPONSE_NONE;
}
