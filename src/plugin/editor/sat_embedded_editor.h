#pragma once

#include "base/sat_base.h"
#include "extern/plugin/sat_clap.h"
#include "plugin/editor/sat_base_editor.h"
#include "plugin/editor/sat_editor_listener.h"
#include "plugin/editor/sat_editor_owner.h"
#include "gui/sat_window.h"
#include "gui/window/sat_window_listener.h"

// #include "extern/plugin/clap/ext/gui.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_EmbeddedEditor
: public SAT_BaseEditor
, public SAT_WindowListener
{
    public:

        SAT_EmbeddedEditor(SAT_EditorOwner* AOwner, SAT_EditorListener* AListener);
        virtual ~SAT_EmbeddedEditor();

        void setInitialSize(uint32_t AWidth, uint32_t AHeight, double AScale, bool AProportional) override;

    public:

        bool create() override;
        void destroy() override;
        bool set_scale(double scale) override;
        bool get_size(uint32_t *width, uint32_t *height) override;
        bool can_resize() override;
        bool get_resize_hints(clap_gui_resize_hints_t *hints) override;
        bool adjust_size(uint32_t *width, uint32_t *height) override;
        bool set_size(uint32_t width, uint32_t height) override;
        bool set_parent(intptr_t window) override;
        bool set_transient(intptr_t window) override;
        void suggest_title(const char *title) override;
        bool show() override;
        bool hide() override;

    protected:

        SAT_EditorOwner*        MOwner          = nullptr;
        SAT_EditorListener*     MListener       = nullptr;
        intptr_t                MParent         = 0;
        intptr_t                MTransient      = 0;

        uint32_t                MInitialWidth   = 0;
        uint32_t                MInitialHeight  = 0;
        double                  MInitialScale   = 1.0;
        bool                    MProportional   = true;

        bool                    MIsCreated      = false;
        bool                    MIsOpen         = false;

        SAT_Window*             MWindow         = nullptr;

        uint32_t                MWidth          = 0;
        uint32_t                MHeight         = 0;
        double                  MScale          = 1.0;
        const char*             MTitle          = "Plugin window";


};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

SAT_EmbeddedEditor::SAT_EmbeddedEditor(SAT_EditorOwner* AOwner, SAT_EditorListener* AListener)
: SAT_BaseEditor()
{
    MOwner = AOwner;
    MListener = AListener;
}

SAT_EmbeddedEditor::~SAT_EmbeddedEditor()
{
    if (MIsCreated)
    {
        if (MIsOpen) hide();
        destroy();
    }
}

//------------------------------
//
//------------------------------

void SAT_EmbeddedEditor::setInitialSize(uint32_t AWidth, uint32_t AHeight, double AScale, bool AProportional)
{
    MInitialWidth = AWidth;
    MInitialHeight = AHeight;
    MInitialScale = AScale;
    MProportional = AProportional;
}

//------------------------------
//
//------------------------------

// bool SAT_EmbeddedEditor::is_api_supported(const char *api, bool is_floating)
// {
//     if (SAT_IsEqual(api,CLAP_WINDOW_API_X11) && !is_floating) return true;
//     return false;
// }

// bool SAT_EmbeddedEditor::get_preferred_api(const char **api, bool *is_floating)
// {
//     *api = CLAP_WINDOW_API_X11;
//     *is_floating = false;
//     return true;
// }

bool SAT_EmbeddedEditor::create()
{
    SAT_Assert(!MIsCreated);
    MWidth = MInitialWidth;
    MHeight = MInitialHeight;
    MScale = MInitialScale;
    MIsCreated = true;
    return true;
}

void SAT_EmbeddedEditor::destroy()
{
    SAT_Assert(MIsCreated);
    if (MWindow)
    {
        if (MIsOpen) MWindow->hide();
        delete MWindow;
        MWindow = nullptr;
    }
    MIsCreated = false;
}

bool SAT_EmbeddedEditor::set_scale(double scale)
{
    MScale = scale;
    if (MWindow) MWindow->setScale(scale);
    return true;
}

bool SAT_EmbeddedEditor::get_size(uint32_t *width, uint32_t *height)
{
    *width = MWidth;
    *height = MHeight;
    return true;
}

bool SAT_EmbeddedEditor::can_resize()
{
    return true;
}

bool SAT_EmbeddedEditor::get_resize_hints(clap_gui_resize_hints_t *hints)
{
    hints->can_resize_horizontally  = true;
    hints->can_resize_vertically    = true;
    hints->preserve_aspect_ratio    = MProportional;
    hints->aspect_ratio_width       = MInitialWidth;
    hints->aspect_ratio_height      = MInitialHeight;
    return true;
}

bool SAT_EmbeddedEditor::adjust_size(uint32_t *width, uint32_t *height)
{
    // uint32_t width = *width;
    // uint32_t height = *height;
    return true;
}

bool SAT_EmbeddedEditor::set_size(uint32_t width, uint32_t height)
{
    MWidth = width;
    MHeight = height;
    if (MWindow) MWindow->setSize(MWidth,MHeight);
    return true;
}

bool SAT_EmbeddedEditor::set_parent(intptr_t window)
{
    MParent = window;
    if (MWindow) MWindow->reparent(MParent);
    return true;
}

bool SAT_EmbeddedEditor::set_transient(intptr_t window)
{
    MTransient = window;
    return true;
}

void SAT_EmbeddedEditor::suggest_title(const char *title)
{
    MTitle = title;
    if (MWindow) MWindow->setTitle(title);
}

bool SAT_EmbeddedEditor::show()
{
    SAT_Assert(!MIsOpen);
    MWindow = new SAT_Window(MWidth,MHeight,MParent);
    SAT_Assert(MWindow);
    //MWindow->setScale(MScale);
    //MWindow->setTitle(MTitle);
    MWindow->show();
    MIsOpen = true;
    return true;
}

bool SAT_EmbeddedEditor::hide()
{
    SAT_Assert(MIsOpen);
    if (MWindow)
    {
        MWindow->hide();
        MWindow = nullptr;
    }
    MIsOpen = false;
    return true;
}

