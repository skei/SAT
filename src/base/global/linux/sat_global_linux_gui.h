#pragma once

/*
    #define SAT_USE_X11
    #define SAT_USE_X11_XRENDER
*/

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

#include "base/sat_base.h"
#include "base/global/sat_global_base.h"

// #ifdef SAT_GUI_NONE ...

#if defined SAT_USE_X11
    #include "extern/gui/sat_x11.h"
#endif

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_LinuxGlobalGui
{
    public:

        SAT_LinuxGlobalGui();
        ~SAT_LinuxGlobalGui();
        void activate(SAT_GlobalBase* AGlobal);
        void deactivate(SAT_GlobalBase* AGlobal);

        #if defined SAT_USE_X11
            xcb_screen_t*   getScreen();
            uint32_t        getScreenWidth();
            uint32_t        getScreenHeight();
            uint32_t        getScreenDepth();
            xcb_visualid_t  getScreenVisual();
            xcb_window_t    getScreenRoot();
            xcb_colormap_t  getScreenColorMap();
            uint32_t        getScreenWhitePixel();
            uint32_t        getScreenBlackPixel();
        #endif

    private:

        #if defined SAT_USE_X11
            bool            setup_x11();
            bool            cleanup_x11();
        #endif

    private:

        bool                MIsActivated    = false;
        SAT_GlobalBase*     MGlobal         = nullptr;

    private:

        #if defined SAT_USE_X11
            xcb_screen_t    MScreen             = {};
        #endif

};

//----------------------------------------------------------------------
//
// implementation
//
//----------------------------------------------------------------------

SAT_LinuxGlobalGui::SAT_LinuxGlobalGui()
{
}

SAT_LinuxGlobalGui::~SAT_LinuxGlobalGui()
{
}

void SAT_LinuxGlobalGui::activate(SAT_GlobalBase* AGlobal)
{
    if (!MIsActivated)
    {
        MGlobal = AGlobal;
        #if defined SAT_USE_X11
            setup_x11();
        #endif
        MIsActivated = true;
    }
}

void SAT_LinuxGlobalGui::deactivate(SAT_GlobalBase* AGlobal)
{
    if (MIsActivated)
    {
        #if defined SAT_USE_X11
            cleanup_x11();
        #endif
        MGlobal = nullptr;
        MIsActivated = false;
    }
}

//------------------------------
// skins
//------------------------------

// void SAT_GlobalGui::appendSkin(SAT_Skin* ASkin);
// void SAT_GlobalGui::removeSkin(SAT_Skin* ASkin);
// void SAT_GlobalGui::deleteSkins();
// SAT_Skin* SAT_GlobalGui::findSkin(const char* AName);


//------------------------------
// x11
//------------------------------

#if defined SAT_USE_X11

    /*
        // screen gc
        MScreenGC = xcb_generate_id(MConnection);
        xcb_drawable_t draw = MScreen->root;
        uint32_t mask = XCB_GC_FOREGROUND | XCB_GC_BACKGROUND;
        uint32_t values[2];
        values[0] = MScreen->black_pixel;
        values[1] = MScreen->white_pixel;
        xcb_create_gc(MConnection, MScreenGC, draw, mask, values);    
    */

    /*
        XCloseDisplay:
        destroys all windows, resource IDs (Window, Font, Pixmap, Colormap, Cursor, and GContext),
        or other resources that the client has created on this display
    */

    bool SAT_LinuxGlobalGui::setup_x11()
    {
        XInitThreads(); // is this actually needed?
        // MConnection = xcb_connect(ADisplayName,&MDefaultScreen);
        Display* display = XOpenDisplay(nullptr);
        xcb_connection_t* connection = XGetXCBConnection(display);
        // XSetEventQueueOwner(display,XCBOwnsEventQueue);
        int32_t screen_num = DefaultScreen(display);    
        xcb_screen_t* screen = nullptr;
        xcb_screen_iterator_t iter;
        iter = xcb_setup_roots_iterator(xcb_get_setup(connection));
        for (; iter.rem; --screen_num, xcb_screen_next(&iter))
        {
            if (screen_num == 0)
            {
                screen = iter.data;
                break;
            }
        }
        if (screen) {
            memcpy(&MScreen,screen,sizeof(xcb_screen_t));
            // MScreenWidth        = screen->width_in_pixels;
            // MScreenHeight       = screen->height_in_pixels;
            // MScreenDepth        = screen->root_depth;
            // MScreenWhitePixel   = screen->white_pixel;
            // MScreenBlackPixel   = screen->black_pixel;
            // // are the following valid after closing the Display connection?        
            // MScreenVisual       = screen->root_visual;   
            // MScreenRoot         = screen->root;
            // MScreenColorMap     = screen->default_colormap;
        }
        // XSetEventQueueOwner(display,XlibOwnsEventQueue);
        XCloseDisplay(display);
        return true;
    }

    bool SAT_LinuxGlobalGui::cleanup_x11()
    {
        return true;
    }

    //----------

    xcb_screen_t*   SAT_LinuxGlobalGui::getScreen()              { return &MScreen; }
    uint32_t        SAT_LinuxGlobalGui::getScreenWidth()         { return MScreen.width_in_pixels; }
    uint32_t        SAT_LinuxGlobalGui::getScreenHeight()        { return MScreen.height_in_pixels; }
    uint32_t        SAT_LinuxGlobalGui::getScreenDepth()         { return MScreen.root_depth; }
    uint32_t        SAT_LinuxGlobalGui::getScreenWhitePixel()    { return MScreen.white_pixel; }
    uint32_t        SAT_LinuxGlobalGui::getScreenBlackPixel()    { return MScreen.black_pixel; }
    xcb_visualid_t  SAT_LinuxGlobalGui::getScreenVisual()        { return MScreen.root_visual; }
    xcb_window_t    SAT_LinuxGlobalGui::getScreenRoot()          { return MScreen.root; }
    xcb_colormap_t  SAT_LinuxGlobalGui::getScreenColorMap()      { return MScreen.default_colormap; }

#elif defined SAT_USE_WAYLAND

    // ...

#else

    #error NO GUI DEFINED

#endif
