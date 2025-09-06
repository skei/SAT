#pragma once

#include "base/sat_base.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

#if defined SAT_EDITOR_NONE
    #include "plugin/editor/sat_base_editor.h"
    typedef SAT_BaseEditor SAT_ImplementedEditor
#elif defined SAT_EDITOR_EMBEDDED
    #include "plugin/editor/sat_embedded_editor.h"
    typedef SAT_EmbeddedEditor SAT_ImplementedEditor;
#elif defined SAT_EDITOR_REMOTE
    #include "plugin/editor/sat_remote_editor.h"
    typedef SAT_RemoteEditor SAT_ImplementedEditor;
#else
    #error NO EDTIOR DEFINED
#endif

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_Editor
: public SAT_ImplementedEditor
{
    public:
        SAT_Editor(SAT_EditorOwner* AOwner, SAT_EditorListener* AListener);
        virtual ~SAT_Editor();
};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

SAT_Editor::SAT_Editor(SAT_EditorOwner* AOwner, SAT_EditorListener* AListener)
: SAT_ImplementedEditor(AOwner,AListener)
{
}

SAT_Editor::~SAT_Editor()
{
}

