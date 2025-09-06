#pragma once

#error NOT IMPLEMENTED YET

#include "base/sat_base.h"
#include "base/util/sat_strutils.h"
#include "extern/plugin/sat_clap.h"
#include "plugin/editor/sat_base_editor.h"
#include "plugin/editor/sat_editor_listener.h"
#include "plugin/editor/sat_editor_owner.h"

// #include "extern/plugin/clap/ext/gui.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_RemoteEditor
: public SAT_BaseEditor
{
    public:

        SAT_RemoteEditor(SAT_EditorOwner* AOwner, SAT_EditorListener* AListener);
        virtual ~SAT_RemoteEditor();

        // void setInitialSzie(uint32_t AWidth, uint32_t AHeight, double AScale, bool AProportional) override;

    public:

        // bool is_api_supported(const char *api, bool is_floating) override;
        // bool get_preferred_api(const char **api, bool *is_floating) override;
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
        const clap_window_t*    MParent         = nullptr;
        const clap_window_t*    MTransient      = nullptr;

        uint32_t                MInitialWidth   = 0;
        uint32_t                MInitialHeight  = 0;
        double                  MInitialScale   = 1.0;
        bool                    MProportional   = true;

        bool                    MIsCreated      = false;
        bool                    MIsOpen         = false;

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

SAT_RemoteEditor::SAT_RemoteEditor(SAT_EditorOwner* AOwner, SAT_EditorListener* AListener)
: SAT_BaseEditor()
{
    MOwner = AOwner;
    MListener = AListener;
}

SAT_RemoteEditor::~SAT_RemoteEditor()
{
}

//------------------------------
//
//------------------------------

void SAT_RemoteEditor::setInitialSzie(uint32_t AWidth, uint32_t AHeight, double AScale, bool AProportional)
{
    MInitialWidth = AWidth;
    MInitialHeight = AHeight;
    MInitialScale = AScale;
    MProportional = AProportional;
}

//------------------------------
//
//------------------------------

// bool SAT_RemoteEditor::is_api_supported(const char *api, bool is_floating)
// {
//     if (SAT_IsEqual(api,CLAP_WINDOW_API_X11) && !is_floating) return true;
//     return false;
// }

// bool SAT_RemoteEditor::get_preferred_api(const char **api, bool *is_floating)
// {
//     *api = CLAP_WINDOW_API_X11;
//     *is_floating = false;
//     return true;
// }

bool SAT_RemoteEditor::create(const char *api, bool is_floating)
{
    SAT_Assert(!MIsCreated);
    // if (SAT_IsEqual(api,CLAP_WINDOW_API_X11) && !is_floating) return true;
    MIsCreated = true;
    return true;
}

void SAT_RemoteEditor::destroy()
{
    SAT_Assert(MIsCreated);
    MIsCreated = false;
}

bool SAT_RemoteEditor::set_scale(double scale)
{
    MScale = scale;
    return true;
}

bool SAT_RemoteEditor::get_size(uint32_t *width, uint32_t *height)
{
    *width = MWidth;
    *height = MHeight;
    return true;
}

bool SAT_RemoteEditor::can_resize()
{
    return true;
}

bool SAT_RemoteEditor::get_resize_hints(clap_gui_resize_hints_t *hints)
{
    hints->can_resize_horizontally  = true;
    hints->can_resize_vertically    = true;
    hints->preserve_aspect_ratio    = MProportional;
    hints->aspect_ratio_width       = MInitialWidth;
    hints->aspect_ratio_height      = MInitialHeight;
    return true;
}

bool SAT_RemoteEditor::adjust_size(uint32_t *width, uint32_t *height)
{
    // uint32_t width = *width;
    // uint32_t height = *height;
    return true;
}

bool SAT_RemoteEditor::set_size(uint32_t width, uint32_t height)
{
    MWidth = width;
    MHeight = height;
    return true;
}

bool SAT_RemoteEditor::set_parent(const clap_window_t *window)
{
    MParent = window;
    return true;
}

bool SAT_RemoteEditor::set_transient(const clap_window_t *window)
{
    MTransient = window;
    return true;
}

void SAT_RemoteEditor::suggest_title(const char *title)
{
    MTitle = title;
}

bool SAT_RemoteEditor::show()
{
    SAT_Assert(!MIsOpen);
    MIsOpen = true;
    return true;
}

bool SAT_RemoteEditor::hide()
{
    SAT_Assert(MIsOpen);
    MIsOpen = false;
    return true;
}

