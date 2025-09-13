#pragma once

#include "base/sat_base.h"
#include "gui/window/sat_widget_window.h"
#include "gui/sat_widget.h"

class SAT_KeyboardState;

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_BaseKeyboardHandler
{

    friend class SAT_KeyboardState;

    public:

        SAT_BaseKeyboardHandler() {}
        ~SAT_BaseKeyboardHandler() {}

    public:

        virtual void                reset() {}
        virtual SAT_WidgetWindow*   getWindow() { return nullptr; }
        virtual SAT_KeyboardState*  getState() { return nullptr; }

    public:

        virtual void                captureWidget(SAT_Widget* AWidget) {}

    public:

        virtual void                timer(double ADelta) {}
        virtual void                press(uint32_t AKey, uint32_t AState, uint32_t ATime) {}
        virtual void                release(uint32_t AKey, uint32_t AState, uint32_t ATime) {}

    protected:
    
        SAT_Widget*                 MCapturedWidget         = nullptr;
        double                      MCurrentTime            = 0.0;
        uint32_t                    MCurrentKeys            = 0;
        uint32_t                    MCurrentModKeys         = SAT_STATE_KEY_NONE;
        SAT_Widget*                 MPrevWidget             = nullptr;
        uint32_t                    MPressedKey             = SAT_KEY_NONE;
        uint32_t                    MPressedModKeys         = SAT_STATE_KEY_NONE;
        double                      MPressedTime            = 0.0;
        uint32_t                    MReleasedKey            = SAT_KEY_NONE;
        uint32_t                    MReleasedModKeys        = SAT_STATE_KEY_NONE;
        double                      MReleasedTime           = 0.0;
     
};

