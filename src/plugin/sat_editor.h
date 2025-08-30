#pragma once

#include "base/sat_base.h"
#include "gui/sat_gui_base.h"
#include "plugin/sat_plugin_base.h"

class SAT_Editor
: public SAT_WindowListener
{
    public:
        SAT_Editor(SAT_EditorOwner* AOwner, SAT_EditorListener* AListener);
        virtual ~SAT_Editor();
    protected:
        SAT_EditorOwner* MOwner = nullptr;
        SAT_EditorListener* MListener = nullptr;
};

//----------------------------------------------------------------------
//
//
//

//----------------------------------------------------------------------

SAT_Editor::SAT_Editor(SAT_EditorOwner* AOwner, SAT_EditorListener* AListener)
{
    MOwner = AOwner;
    MListener = AListener;
}

SAT_Editor::~SAT_Editor()
{
}

