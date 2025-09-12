#pragma once

#include "base/sat.h"

#include "gui/window/sat_base_window.h"
#include "gui/painter/sat_painter_owner.h"
#include "gui/painter/sat_paint_context.h"
#include "gui/painter/sat_paint_source.h"
#include "gui/painter/sat_paint_target.h"
#include "gui/renderer/sat_renderer_owner.h"
#include "gui/renderer/sat_render_context.h"
#include "gui/renderer/sat_render_source.h"
#include "gui/renderer/sat_render_target.h"
#include "gui/surface/sat_surface_owner.h"
#include "extern/gui/sat_x11.h"

#include <sys/time.h>   // gettimeofday

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_X11Window
: public SAT_BaseWindow
, public SAT_SurfaceOwner
, public SAT_PainterOwner
, public SAT_PaintSource
, public SAT_PaintTarget
, public SAT_RendererOwner
, public SAT_RenderTarget
{
    public:

        SAT_X11Window(uint32_t AWidth, uint32_t AHeight, intptr_t AParent=0);
        virtual ~SAT_X11Window();

    public:

        bool                        isWindow() final;
        uint32_t                    getWidth() final;
        uint32_t                    getHeight() final;
        uint32_t                    getDepth() final;
        xcb_connection_t*           getXcbConnection() final;
        xcb_drawable_t              getXcbDrawable() final;
        Display*                    getX11Display() final;

    public: // BaseWindow

        void                        show() override;
        void                        hide() override;
        void                        setPos(int32_t AXpos, int32_t AYpos) override;
        void                        setSize(uint32_t AWidth, uint32_t AHeight) override;
        void                        setTitle(const char* ATitle) override;
        void                        showMouseCursor() override;
        void                        hideMouseCursor() override;
        void                        grabMouseCursor() override;
        void                        releaseMouseCursor() override;
        void                        setMouseCursorPos(int32_t AXpos, int32_t AYpos) override;
        void                        setMouseCursorShape(int32_t ACursor) override;
        void                        reparent(intptr_t AParent) override;
        void                        invalidate(int32_t AXpos, int32_t AYpos, uint32_t AWidth, uint32_t AHeight) override;
        void                        sendClientMessage(uint32_t AData, uint32_t AType) override;
        void                        eventLoop() override;
        void                        startEventThread() override;
        void                        stopEventThread() override;

    private: // X11

        void                        removeDecorations();
        void                        wantQuitEvents();
        void                        waitForMapNotify();
        void                        setXcbCursor(xcb_cursor_t ACursor);
        void                        freeXcbCursor(void);
        void                        setWMCursor(uint32_t ACursor);
        double                      getTime(void);
        uint32_t                    remapKey(uint32_t AKey, uint32_t AState);
        uint32_t                    remapButton(uint32_t AButton, uint32_t AState);
        uint32_t                    remapState(uint32_t AState);
        xcb_generic_event_t*        getEvent(bool ABlock=false);
        bool                        processEvent(xcb_generic_event_t* AEvent);
        static void*                event_thread_callback(void* AWindow);

    private: // X11

        Display*                    MDisplay                        = nullptr;
        xcb_connection_t*           MConnection                     = nullptr;
        xcb_window_t                MParent                         = XCB_NONE;
        xcb_window_t                MWindow                         = XCB_NONE;
        xcb_pixmap_t                MEmptyPixmap                    = XCB_NONE;
        xcb_cursor_t                MHiddenCursor                   = XCB_NONE;
        xcb_cursor_t                MCurrentCursor                  = XCB_NONE;
        xcb_key_symbols_t*          MKeySyms                        = nullptr;
        pthread_t                   MEventThread                    = 0;
        xcb_atom_t                  MWMProtocolsAtom                = XCB_NONE;
        xcb_atom_t                  MWMDeleteWindowAtom             = XCB_NONE;
        xcb_expose_event_t*         MExposeEvent                    = (xcb_expose_event_t*)MExposeEventBuffer;
        xcb_client_message_event_t* MClientMessageEvent             = (xcb_client_message_event_t*)MClientMessageEventBuffer;
        char*                       MExposeEventBuffer[32]          = {0};
        char*                       MClientMessageEventBuffer[32]   = {0};

    private: // state

        int32_t                     MXpos                           = 0;
        int32_t                     MYpos                           = 0;
        uint32_t                    MWidth                          = 0;
        uint32_t                    MHeight                         = 0;
        double                      MPrevTime                       = 0.0;
        bool                        MIsCursorHidden                 = false;
        bool                        MIsEmbedded                     = false;
        bool                        MIsMapped                       = false;
        bool                        MIsExposed                      = false;
        sat_atomic_bool_t           MIsEventThreadActive            = false;
     // sat_atomic_bool_t           MWindowIsClosing                = false;

};

//----------------------------------------------------------------------
//
// implementation
//
//----------------------------------------------------------------------

SAT_X11Window::SAT_X11Window(uint32_t AWidth, uint32_t AHeight, intptr_t AParent)
: SAT_BaseWindow(AWidth,AHeight,AParent)
{
    MXpos = 0;
    MYpos = 0;
    MWidth = AWidth;
    MHeight = AHeight;
    MParent = (xcb_window_t)AParent;
    // --- connection ---
    MDisplay = XOpenDisplay(nullptr);
    // MConnection = xcb_connect(ADisplayName,&MDefaultScreen);
    MConnection = XGetXCBConnection(MDisplay);
    XSetEventQueueOwner(MDisplay,XCBOwnsEventQueue);
    // --- screen ---
    // see /base/global/linux/sat_global_linux_gui.h
    // --- window ---
    uint32_t event_mask =
        XCB_EVENT_MASK_KEY_PRESS                |
        XCB_EVENT_MASK_KEY_RELEASE              |
        XCB_EVENT_MASK_BUTTON_PRESS             |
        XCB_EVENT_MASK_BUTTON_RELEASE           |
        XCB_EVENT_MASK_ENTER_WINDOW             |
        XCB_EVENT_MASK_LEAVE_WINDOW             |
        XCB_EVENT_MASK_POINTER_MOTION           |
        XCB_EVENT_MASK_EXPOSURE                 |
        // XCB_EVENT_MASK_RESIZE_REDIRECT       |
        // XCB_EVENT_MASK_SUBSTRUCTURE_NOTIFY   |
        XCB_EVENT_MASK_STRUCTURE_NOTIFY;
    uint32_t window_mask =
        XCB_CW_BACK_PIXMAP      |
        XCB_CW_BORDER_PIXEL     |
        XCB_CW_EVENT_MASK       |
        XCB_CW_COLORMAP;
    uint32_t window_mask_values[4] =
    {
        XCB_NONE, // XCB_BACK_PIXMAP_NONE ?
        0,
        event_mask,
        SAT.GUI->getScreenColorMap()
    };
    MWindow = xcb_generate_id(MConnection);
    xcb_create_window(
        MConnection,                                    // connection
        XCB_COPY_FROM_PARENT,                           // depth (same as root)
        MWindow,                                        // window Id
        MParent ? MParent : SAT.GUI->getScreenRoot(),   // parent window
        0, 0,                                           // x, y
        MWidth, MHeight,                                // width, height
        0,                                              // border_width
        XCB_WINDOW_CLASS_INPUT_OUTPUT,                  // class
        SAT.GUI->getScreenVisual(),                     // visual
        window_mask,
        window_mask_values
    );
    // --- cursor ---
    MEmptyPixmap = xcb_generate_id(MConnection);
    MHiddenCursor = xcb_generate_id(MConnection);
    xcb_create_pixmap(
        MConnection,
        1,
        MEmptyPixmap,
        MWindow,
        1,
        1
    );
    xcb_create_cursor(
        MConnection,
        MHiddenCursor,
        MEmptyPixmap,
        MEmptyPixmap,
        0, 0, 0,        // fore color
        0, 0, 0,        // back color
        0, 0            // x,y
    );    
    // --- keymap ---
    MKeySyms = xcb_key_symbols_alloc(MConnection);    
    // --- decorations, quit events ---
    if (AParent)
    {
        MIsEmbedded = true;
        removeDecorations();
    }
    else
    {
        MIsEmbedded = false;
        wantQuitEvents();
    }
    // --- time ---
    MPrevTime = getTime();
}

/*
    XCloseDisplay:
    destroys all windows, resource IDs (Window, Font, Pixmap, Colormap, Cursor, and GContext),
    or other resources that the client has created on this display
*/

SAT_X11Window::~SAT_X11Window()
{
    xcb_key_symbols_free(MKeySyms);
    xcb_free_pixmap(MConnection,MEmptyPixmap);
    xcb_free_cursor(MConnection,MHiddenCursor);
    if (MCurrentCursor != XCB_NONE) xcb_free_cursor(MConnection,MCurrentCursor);    
    xcb_destroy_window(MConnection,MWindow);
    XSetEventQueueOwner(MDisplay,XlibOwnsEventQueue);
    XCloseDisplay(MDisplay);
}

//------------------------------
// surface owner, paint source/target, renderer owner, render target
//------------------------------

bool                SAT_X11Window::isWindow()           { return true; }
uint32_t            SAT_X11Window::getWidth()           { return MWidth; }
uint32_t            SAT_X11Window::getHeight()          { return MHeight; }
uint32_t            SAT_X11Window::getDepth()           { return SAT.GUI->getScreenDepth(); }
xcb_connection_t*   SAT_X11Window::getXcbConnection()   { return MConnection; }
xcb_drawable_t      SAT_X11Window::getXcbDrawable()     { return MWindow; }
Display*            SAT_X11Window::getX11Display()      { return MDisplay; }

//------------------------------
// base window
//------------------------------

/*
    // TODO: if (!MIsOpen) ..
*/

void SAT_X11Window::show()
{
    xcb_map_window(MConnection,MWindow);
    xcb_flush(MConnection);
    #ifdef SAT_X11_WAIT_FOR_MAPNOTIFY
        waitForMapNotify();
        //MIsMapped = true; // set in waitForMapNotify()
        on_window_show();
    #endif
    if (MIsEmbedded) startEventThread();
}

/*
    TODO: if (MIsOpen) ..
    make sure we don't call on_window_hide() multiple times
*/

void SAT_X11Window::hide()
{
    on_window_hide();
    if (MIsEmbedded) stopEventThread();
    xcb_unmap_window(MConnection,MWindow);
    xcb_flush(MConnection);
    MIsMapped = false;
    MIsExposed = false;    
}

void SAT_X11Window::setPos(int32_t AXpos, int32_t AYpos)
{
    MXpos = AXpos;
    MYpos = AYpos;
    uint32_t values[] = { (uint32_t)AXpos, (uint32_t)AYpos };
    xcb_configure_window(MConnection,MWindow,XCB_CONFIG_WINDOW_X | XCB_CONFIG_WINDOW_Y,values);
    xcb_flush(MConnection);
}

void SAT_X11Window::setSize(uint32_t AWidth, uint32_t AHeight)
{
    MWidth = AWidth;
    MHeight = AHeight;
    uint32_t values[] = { AWidth, AHeight };
    xcb_configure_window(MConnection,MWindow,XCB_CONFIG_WINDOW_WIDTH | XCB_CONFIG_WINDOW_HEIGHT,values);
    xcb_flush(MConnection);
}

void SAT_X11Window::setTitle(const char* ATitle)
{
    xcb_change_property(
        MConnection,
        XCB_PROP_MODE_REPLACE,
        MWindow,
        XCB_ATOM_WM_NAME,
        XCB_ATOM_STRING,
        8,
        strlen(ATitle),
        ATitle
    );
    xcb_flush(MConnection);
}

void SAT_X11Window::showMouseCursor()
{
    if (MIsCursorHidden)
    {
        setXcbCursor(MCurrentCursor);
        MIsCursorHidden = false;
    }
}
  
void SAT_X11Window::hideMouseCursor()
{
    if (!MIsCursorHidden)
    {
        setXcbCursor(MHiddenCursor);
        MIsCursorHidden = true;
    }
}

void SAT_X11Window::grabMouseCursor()
{
    int32_t event_mask =
        XCB_EVENT_MASK_BUTTON_PRESS   |
        XCB_EVENT_MASK_BUTTON_RELEASE |
        XCB_EVENT_MASK_POINTER_MOTION |
        XCB_EVENT_MASK_FOCUS_CHANGE   |
        XCB_EVENT_MASK_ENTER_WINDOW   |
        XCB_EVENT_MASK_LEAVE_WINDOW;
    xcb_grab_pointer(
        MConnection,
        0,                                      // owner_events
        MWindow, /*rootWindow,*/                // grab_window
        event_mask,                             // event_mask
        XCB_GRAB_MODE_ASYNC,                    // pointer_mode
        XCB_GRAB_MODE_ASYNC,                    // keyboard_mode
        XCB_NONE, /*rootWindow,*/               // confine_to
        XCB_NONE,                               // cursor
        XCB_CURRENT_TIME                        // timestamp
    );
    xcb_flush(MConnection);
}

void SAT_X11Window::releaseMouseCursor()
{
    xcb_ungrab_pointer(MConnection,XCB_CURRENT_TIME);
    xcb_flush(MConnection);
}
  
void SAT_X11Window::setMouseCursorPos(int32_t AXpos, int32_t AYpos)
{
    xcb_warp_pointer(MConnection,XCB_NONE,MWindow,0,0,0,0,AXpos,AYpos);
    xcb_flush(MConnection);
}
  
void SAT_X11Window::setMouseCursorShape(int32_t ACursor)
{
    setWMCursor(ACursor);
}

void SAT_X11Window::reparent(intptr_t AParent)
{
    if (AParent != 0)
    {
        MIsEmbedded = true;
        xcb_reparent_window(MConnection,MWindow,AParent,0,0);
        xcb_flush(MConnection);
    }    
}

void SAT_X11Window::invalidate(int32_t AXpos, int32_t AYpos, uint32_t AWidth, uint32_t AHeight)
{
    // x11 doesn't like negative coords? (uint16_t)
    // AXpos = SAT_ClampI(AXpos,0,MWindowWidth);
    // AYpos = SAT_ClampI(AYpos,0,MWindowHeight);
    if (AXpos < 0) AXpos = 0;
    if (AYpos < 0) AYpos = 0;
    if (AXpos > (int)MWidth)  AXpos = MWidth;
    if (AYpos > (int)MHeight) AYpos = MHeight;
    memset(MExposeEventBuffer,0,sizeof(MExposeEventBuffer));
    MExposeEvent->window        = MWindow;
    MExposeEvent->response_type = XCB_EXPOSE;
    MExposeEvent->x             = AXpos;
    MExposeEvent->y             = AYpos;
    MExposeEvent->width         = AWidth;
    MExposeEvent->height        = AHeight;
    xcb_send_event(
        MConnection,
        false,
        MWindow,
        XCB_EVENT_MASK_EXPOSURE,
        (char*)MExposeEvent
    );
    xcb_flush(MConnection);    
}

/*
    this will (probably) be called form a separate timer thread,
    to redirect the timer tick to the gui thread..
    and is _also_ called from stopEventThread() in gui thread,
    to kill the event loop.. see SAT_X11Window::hide()..
*/

void SAT_X11Window::sendClientMessage(uint32_t AData, uint32_t AType)
{
    memset(MClientMessageEventBuffer,0,sizeof(MClientMessageEventBuffer));
    MClientMessageEvent->window         = MWindow;
    MClientMessageEvent->response_type  = XCB_CLIENT_MESSAGE;
    MClientMessageEvent->format         = 32; // didn't work without this
    MClientMessageEvent->type           = AType;
    MClientMessageEvent->data.data32[0] = AData;
    xcb_send_event(
        MConnection,
        false,
        MWindow,
        XCB_EVENT_MASK_NO_EVENT,
        (char*)MClientMessageEvent
    );
    xcb_flush(MConnection);
}

void SAT_X11Window::eventLoop()
{
    xcb_generic_event_t* event = getEvent(true);
    // while (event)
    do
    {
        bool result = processEvent(event);
        if (result == false)
        {
            // free(event); // not malloc'ed
            // break;
            return;// 1;
        }
        /*
            uint32_t e = event->response_type & ~0x80;
            if (e == XCB_CLIENT_MESSAGE)
            {
                xcb_client_message_event_t* client_message = (xcb_client_message_event_t*)event;
                xcb_atom_t type = client_message->type;
                uint32_t data = client_message->data.data32[0];
                // if (type == MWMProtocolsAtom) {
                if (data == MWMDeleteWindowAtom)
                {
                    //free(event); // not malloc'ed
                    //MQuitEventLoop = true;
                    break;
                    return 2;
                }
                // }
            }
        */
        event = getEvent(true);
    } while (event);
    // }
    // return 0;
}

void SAT_X11Window::startEventThread()
{
    MIsEventThreadActive = true;
    pthread_create(&MEventThread,nullptr,event_thread_callback,this);
}

/*
    the event thread is blocking when waiting for new events to arrive.
    to wake it up, we send a 'client message'.. when the thread receives this event,
    it will (should) kill itself..
*/

/*
    had an editor close crash.. (couldn't reproduce it, needs investigation)
    had the templates audio_plugin + instrument + note_effect templates open at the same time.
    closed bitwig

    crashed in SAT_X11Window::stopEventThread(), called from from SAT_X11Window::close()
    called after/from two SAT_Editor::~SAT_Editor() calls in a row..
    threads closing, vs atomic bools?
    if the window is closing, will the SAT_WINDOW_THREAD_KILL client message reach it?
*/  

void SAT_X11Window::stopEventThread()
{
    void* ret;
    MIsEventThreadActive = false;
    sendClientMessage(SAT_WINDOW_USER_MESSAGE_KILL,0);
    // xcb_flush(MConnection);
    pthread_join(MEventThread,&ret);
}

//------------------------------
// X11
//------------------------------

const unsigned long SAT_WM_HINTS_FUNCTIONS   = 1 << 0;
const unsigned long SAT_WM_HINTS_DECORATIONS = 1 << 1;
//c onst unsigned long SAT_WM_DECOR_ALL      = 1 << 0;
const unsigned long SAT_WM_DECOR_BORDER      = 1 << 1;
const unsigned long SAT_WM_DECOR_RESIZEH     = 1 << 2;
const unsigned long SAT_WM_DECOR_TITLE       = 1 << 3;
const unsigned long SAT_WM_DECOR_MENU        = 1 << 4;
const unsigned long SAT_WM_DECOR_MINIMIZE    = 1 << 5;
const unsigned long SAT_WM_DECOR_MAXIMIZE    = 1 << 6;
// const unsigned long SAT_WM_FUNC_ALL       = 1 << 0;
const unsigned long SAT_WM_FUNC_RESIZE       = 1 << 1;
const unsigned long SAT_WM_FUNC_MOVE         = 1 << 2;
const unsigned long SAT_WM_FUNC_MINIMIZE     = 1 << 3;
const unsigned long SAT_WM_FUNC_MAXIMIZE     = 1 << 4;
const unsigned long SAT_WM_FUNC_CLOSE        = 1 << 5;

struct SAT_WMHints
{
    uint32_t flags;
    uint32_t functions;
    uint32_t decorations;
    int32_t  inputMode;
    uint32_t state;
};

void SAT_X11Window::removeDecorations()
{
    xcb_atom_t prop = SAT_XcbGetInternAtom(MConnection,"_MOTIF_WM_HINTS");
    if (prop)
    {
        SAT_WMHints hints;
        hints.flags = SAT_WM_HINTS_DECORATIONS;
        hints.decorations = 0;
        const unsigned char* ptr = (const unsigned char*)(&hints);
        xcb_change_property(
            MConnection,
            XCB_PROP_MODE_REPLACE,
            MWindow,
            prop,     // hintsAtomReply->atom,
            prop,     // XCB_ATOM_WM_HINTS,
            32,
            5,        // PROP_MOTIF_WM_HINTS_ELEMENTS
            ptr
        );
    }
}

void SAT_X11Window::wantQuitEvents()
{
    xcb_intern_atom_cookie_t  protocol_cookie = xcb_intern_atom_unchecked(MConnection, 1, 12, "WM_PROTOCOLS");
    xcb_intern_atom_cookie_t  close_cookie    = xcb_intern_atom_unchecked(MConnection, 0, 16, "WM_DELETE_WINDOW");
    xcb_intern_atom_reply_t*  protocol_reply  = xcb_intern_atom_reply(MConnection, protocol_cookie, 0);
    xcb_intern_atom_reply_t*  close_reply     = xcb_intern_atom_reply(MConnection, close_cookie, 0);
    MWMProtocolsAtom    = protocol_reply->atom;
    MWMDeleteWindowAtom = close_reply->atom;
    xcb_change_property(MConnection, XCB_PROP_MODE_REPLACE, MWindow, MWMProtocolsAtom, 4, 32, 1, &MWMDeleteWindowAtom);
    //xcb_flush(MConnection);
    free(protocol_reply); // note malloc'ed ??
    free(close_reply);    
}

/*
    hmmm...
    we get a REPARENT_NOTIFY, and three CONFIGURE_NOTIFY events, before the
    first MAP_NOTIFY event.. maybe we should save the window info,
    and call on_window_move, on_window_size as soon as we get the map_notify?
*/

void SAT_X11Window::waitForMapNotify()
{
    /*
        int16_t x = 0;
        int16_t y = 0;
        uint16_t w = 0;
        uint16_t h = 0;
        bool configure = false;
    */
    xcb_flush(MConnection);
    while (1)
    {
        xcb_generic_event_t* event;
        event = xcb_wait_for_event(MConnection);
        uint8_t e = event->response_type & ~0x80;
        /*
            switch(e)
            {
                // case XCB_REPARENT_NOTIFY:
                // {
                //     xcb_reparent_notify_event_t* reparent_notify = (xcb_reparent_notify_event_t*)event;
                //     xcb_window_t parent = reparent_notify->parent;
                //     int16_t x = reparent_notify->x;
                //     int16_t y = reparent_notify->y;
                //     break;
                // }
                case XCB_CONFIGURE_NOTIFY:
                {
                    xcb_configure_notify_event_t* configure_notify = (xcb_configure_notify_event_t*)event;
                    x  = configure_notify->x;
                    y  = configure_notify->y;
                    w = configure_notify->width;
                    h = configure_notify->height;
                    configure = true;
                    break;
                }
                case XCB_MAP_NOTIFY:
                {
                    MIsMapped = true;
                    break;
                }
            }
            free(event);
            if (MIsMapped) break;
        */
        free(event); // allocated by xserver...
        if (e == XCB_MAP_NOTIFY) break;
    }
    MIsMapped = true;
    /*
        if (configure)
        {
            on_window_move(x,y);
            on_window_resize(w,h);
        }
    */
}

void SAT_X11Window::setXcbCursor(xcb_cursor_t ACursor)
{
    uint32_t mask;
    uint32_t values;
    mask   = XCB_CW_CURSOR;
    values = ACursor;
    xcb_change_window_attributes(MConnection,MWindow,mask,&values);
    // without xcb_flush, the mouse cursor wasn't updating properly (standalone)..
    xcb_flush(MConnection);
}

void SAT_X11Window::freeXcbCursor(void)
{
    if (MCurrentCursor != XCB_NONE)
    {
        xcb_free_cursor(MConnection,MCurrentCursor);
        MCurrentCursor = XCB_NONE;
        // xcb_flush(MConnection);
    }
}

void SAT_X11Window::setWMCursor(uint32_t ACursor)
{
    xcb_cursor_context_t *ctx;
    if (xcb_cursor_context_new(MConnection, SAT.GUI->getScreen(), &ctx) >= 0)
    {
        const char* name = SAT_X11_WM_CURSORS[ACursor];
        xcb_cursor_t cursor = xcb_cursor_load_cursor(ctx, name);
        if (cursor != XCB_CURSOR_NONE)
        {
            xcb_change_window_attributes(MConnection, MWindow, XCB_CW_CURSOR, &cursor);
        }
    }
    xcb_cursor_context_free(ctx);
    xcb_flush(MConnection);
}

/*
    TODO:
    move to sat_time.h?
*/

double SAT_X11Window::getTime()
{
    struct timeval time;
    gettimeofday(&time,NULL);
    double t = (double)time.tv_sec + (double)time.tv_usec * .000001;
    return t;
}

uint32_t SAT_X11Window::remapKey(uint32_t AKey, uint32_t AState)
{
    int col = 0;
    xcb_keysym_t keysym = xcb_key_symbols_get_keysym(MKeySyms,AKey,col);
    /*    
        xcb_keycode_t* keycode  = xcb_key_symbols_get_keycode(MKeySyms,keysym);
        free(keycode);
        char buffer[256] = {0};
        int32_t num = xkb_keysym_to_utf8(keysym,buffer,255);
        char c = buffer[0];
    */
    /*
        // "Alt_L, Return, etc"
        num = xkb_keysym_get_name(keysym,buffer,255);
        if (num > 0)
        {
            //for (int32_t i=0; i<num; i++) {  }
        }
    */
    uint32_t ks = keysym;
    switch (keysym)
    {
        case XKB_KEY_Return:      ks = SAT_KEY_ENTER;     break;
        case XKB_KEY_KP_Space:    ks = SAT_KEY_SPACE;     break;
        case XKB_KEY_Home:        ks = SAT_KEY_HOME;      break;
        case XKB_KEY_End:         ks = SAT_KEY_END;       break;
        case XKB_KEY_Left:        ks = SAT_KEY_LEFT;      break;
        case XKB_KEY_Right:       ks = SAT_KEY_RIGHT;     break;
        case XKB_KEY_Delete:      ks = SAT_KEY_DELETE;    break;
        case XKB_KEY_BackSpace:   ks = SAT_KEY_BACKSPACE; break;
        case XKB_KEY_Escape:      ks = SAT_KEY_ESC;       break;
    }
    return ks;
}

uint32_t SAT_X11Window::remapButton(uint32_t AButton, uint32_t AState)
{
    uint32_t b = AButton;
    // TODO
    return b;
}

uint32_t SAT_X11Window::remapState(uint32_t AState)
{
    uint32_t s = AState; //0; //SAT_KEY_STATE_NONE;
    if (AState & XCB_MOD_MASK_SHIFT)    s += SAT_STATE_KEY_SHIFT;
    if (AState & XCB_MOD_MASK_LOCK)     s += SAT_STATE_KEY_CAPS;
    if (AState & XCB_MOD_MASK_CONTROL)  s += SAT_STATE_KEY_CTRL;
    if (AState & XCB_MOD_MASK_1)        s += SAT_STATE_KEY_ALT;
    if (AState & XCB_MOD_MASK_5)        s += SAT_STATE_KEY_ALTGR;
    // if (AState & XCB_MOD_MASK_1) SAT_PRINT("1\n");
    // if (AState & XCB_MOD_MASK_2) SAT_PRINT("2\n");
    // if (AState & XCB_MOD_MASK_3) SAT_PRINT("3\n");
    // if (AState & XCB_MOD_MASK_4) SAT_PRINT("4\n");
    // if (AState & XCB_MOD_MASK_5) SAT_PRINT("5\n");
    return s;
}

// returns null if no events
// caller must free(event) !!!!

xcb_generic_event_t* SAT_X11Window::getEvent(bool ABlock)
{
    // xcb_flush(MConnection);
    xcb_generic_event_t* event = nullptr;
    if (ABlock) event = xcb_wait_for_event(MConnection);
    else event = xcb_poll_for_event(MConnection);
    // if (event)
    // {
    //     eventHandler(event);
    //     free(event); // not MALLOC'ed
    // }
    return event;
}

// returns false if we received MWMDeleteWindowAtom
// -> we are done (quit)
// frees AEvent
// (we didn't allocate AEvent (it's coming from the event handler - xcb_wait_for_event)
// so we call the 'non-intercepted' free, to avoid pestering our memleak detector)

bool SAT_X11Window::processEvent(xcb_generic_event_t* AEvent)
{
    // if (MWindowIsClosing) return false;
    switch (AEvent->response_type & ~0x80)
    {

        /*
            if SAT_X11_WAIT_FOR_MAPNOTIFY is defined, we wait for the first MAP_NOTIFY
            in waitForMapNotify(), and set MIsMapped = true, and call on_window_show()
            todo: check if we still get this event.. and, btw, do we get other x11
            events before that first MAP_NOTIFY, that we are ignoring?
            (a SAT_TRACE both here and in waitForMapNotify, only prints this one..)
        */

        case XCB_MAP_NOTIFY:
        {
            MIsMapped = true;
            on_window_show();
            break;
        }
        case XCB_UNMAP_NOTIFY:
        {
            MIsMapped = false;
            on_window_hide();
            break;
        }
        // case XCB_REPARENT_NOTIFY:
        // {
        //     xcb_reparent_notify_event_t* reparent_notify = (xcb_reparent_notify_event_t*)AEvent;
        //     xcb_window_t parent = reparent_notify->parent;
        //     int16_t x = reparent_notify->x;
        //     int16_t y = reparent_notify->y;
        //     break;
        // }
        /*
            (where is this from?)
            "Well... personally, I never needed these fancy functions.
            The most complicated that I needed was "only handle the last
            MotionNotify event in the queue and ignore earlier ones". For that,
            I had a variable xcb_generic_event_t *motion = NULL; before my loop.
            Each new motion notify event was not handled, but saved in this
            function. Other events were handled immediately. After the loop,
            if there was a motion notify event, it was handled."
        */
        case XCB_CONFIGURE_NOTIFY:
        {
            xcb_configure_notify_event_t* configure_notify = (xcb_configure_notify_event_t*)AEvent;
            int16_t x  = configure_notify->x;
            int16_t y  = configure_notify->y;
            uint16_t w = configure_notify->width;
            uint16_t h = configure_notify->height;
            //SAT_PRINT("configure: x %i y %i w %i h %i\n",x,y,w,h);
            if ((x != MXpos) || (y != MYpos))
            {
                MXpos = x;
                MYpos = y;
                on_window_move(x,y);
            }
            if ((w != MWidth) || (h != MHeight))
            {
                MWidth  = w;
                MHeight = h;
                on_window_resize(w,h);
            }
            break;
        }
        case XCB_EXPOSE:
        {
            xcb_expose_event_t* expose = (xcb_expose_event_t *)AEvent;
            uint16_t x = expose->x;
            uint16_t y = expose->y;
            uint16_t w = expose->width;
            uint16_t h = expose->height;
            /*
                // https://cairographics.org/cookbook/xcbsurface.c/
                // Avoid extra redraws by checking if this is the last expose event in the sequence
                while(expose->count != 0)
                {
                    xcb_generic_event_t* e2 = xcb_wait_for_event(MConnection);
                    xcb_expose_event_t* ex2 = (xcb_expose_event_t *)e2;
                    RECT.combine( SAT_Rect( ex2->x, ex2->y, ex2->width, ex2->height ) );
                }
                MIsPainting = true;
            */
            on_window_paint(x,y,w,h);
            xcb_flush(MConnection);
            // MIsPainting = false;
            MIsExposed = true;
            break;
        }
        case XCB_KEY_PRESS:
        {
            // if (!MWindowMapped) break;
            xcb_key_press_event_t* key_press = (xcb_key_press_event_t*)AEvent;
            uint8_t  k  = key_press->detail;
            uint16_t s  = key_press->state;
            uint32_t ts = key_press->time;
            //char c = 0;
            uint32_t ks = remapKey(k,s);
            s = remapState(s);
            on_window_key_press(ks,0,s,ts);
            break;
        }
        case XCB_KEY_RELEASE:
        {
            // if (!MWindowMapped) break;
            xcb_key_release_event_t* key_release = (xcb_key_release_event_t*)AEvent;
            uint8_t  k  = key_release->detail;
            uint16_t s  = key_release->state;
            uint32_t ts = key_release->time;
            // char c = 0;
            uint32_t ks = remapKey(k,s);
            s = remapState(s);
            on_window_key_release(ks,0,s,ts);
            break;
        }

        case XCB_BUTTON_PRESS:
        {
            // if (!MWindowMapped) break;
            xcb_button_press_event_t* button_press = (xcb_button_press_event_t*)AEvent;
            uint8_t  b  = button_press->detail;
            uint32_t s  = button_press->state;
            int32_t  x  = button_press->event_x;
            int32_t  y  = button_press->event_y;
            uint32_t ts = button_press->time;
            b = remapButton(b,s);
            s = remapState(s);
            on_window_mouse_click(x,y,b,s,ts);
            break;
        }
        case XCB_BUTTON_RELEASE:
        {
            // if (!MWindowMapped) break;
            xcb_button_release_event_t* button_release = (xcb_button_release_event_t*)AEvent;
            uint32_t b  = button_release->detail;
            uint32_t s  = button_release->state;
            int32_t  x  = button_release->event_x;
            int32_t  y  = button_release->event_y;
            uint32_t ts = button_release->time;
            b = remapButton(b,s);
            s = remapState(s);
            on_window_mouse_release(x,y,b,s,ts);
            break;
        }
        case XCB_MOTION_NOTIFY:
        {
            // if (!MWindowMapped) break;
            xcb_motion_notify_event_t* motion_notify = (xcb_motion_notify_event_t*)AEvent;
            // uint32_t  b = motion_notify->detail;
            uint32_t  s = motion_notify->state;
            int32_t   x = motion_notify->event_x;
            int32_t   y = motion_notify->event_y;
            uint32_t ts = motion_notify->time;
            s = remapState(s);
            on_window_mouse_move(x,y,s,ts);
            break;
        }
        case XCB_ENTER_NOTIFY:
        {
            if (!MIsMapped) break;
            xcb_enter_notify_event_t* enter_notify = (xcb_enter_notify_event_t*)AEvent;
            // uint32_t  m = enter_notify->mode;
            // uint32_t  s = enter_notify->state;
            int32_t   x = enter_notify->event_x;
            int32_t   y = enter_notify->event_y;
            uint32_t ts = enter_notify->time;
            on_window_mouse_enter(x,y,ts);
            break;
        }
        case XCB_LEAVE_NOTIFY:
        {
            if (!MIsMapped) break;
            xcb_leave_notify_event_t* leave_notify = (xcb_leave_notify_event_t*)AEvent;
            // uint32_t  m = leave_notify->mode;
            // uint32_t  s = leave_notify->state;
            int32_t   x = leave_notify->event_x;
            int32_t   y = leave_notify->event_y;
            uint32_t ts = leave_notify->time;
            on_window_mouse_leave(x,y,ts);
            break;
        }
        case XCB_CLIENT_MESSAGE:
        {
            xcb_client_message_event_t* client_message = (xcb_client_message_event_t*)AEvent;
            xcb_atom_t type = client_message->type;
            uint32_t data = client_message->data.data32[0];
            if (data == SAT_WINDOW_USER_MESSAGE_KILL)
            {
                free(AEvent);
                return false;
            }
            else if (data == SAT_WINDOW_USER_MESSAGE_TIMER)
            {
                double time = getTime();
                double delta = time - MPrevTime;
                MPrevTime = time;
                on_window_timer(SAT_WINDOW_USER_MESSAGE_TIMER,delta);
                free(AEvent);
                return true;
            }
            if (type == MWMProtocolsAtom) // why was this commented out?
            {
                if (data == MWMDeleteWindowAtom)
                {
                    free(AEvent);
                    return false;
                }
            }
            on_window_client_message(data);
            break;
        } // client message
    } // switch
    free(AEvent);
    return true; // still alive
}

//----------------------------------------------------------------------
//
// event thread callback
//
//----------------------------------------------------------------------

void* SAT_X11Window::event_thread_callback(void* AWindow)
{
    // sat_xcb_event_thread_pid = getpid();
    SAT_X11Window* window = (SAT_X11Window*)AWindow;
    if (window)
    {
        // window->xcb_event_thread_start_callback(window);
        xcb_connection_t* connection = window->MConnection;
        xcb_flush(connection);
        while (window->MIsEventThreadActive)
        {
            // Returns the next event or error from the server, or returns null in the event of an I/O error.
            // Blocks until either an event or error arrive, or an I/O error occurs.
            xcb_generic_event_t* event = xcb_wait_for_event(connection);
            if (event)
            {
                // when you get an event with response_type == 0, cast the pointer to xcb_generic_error_t*.
                if (event->response_type == 0)
                {
                    xcb_generic_error_t* error __attribute__((unused)) = (xcb_generic_error_t*)event;
                    free(event);
                    continue;
                }
                /*
                    if ((event->response_type & ~0x80) == XCB_CLIENT_MESSAGE)
                    {
                        xcb_client_message_event_t* client_message = (xcb_client_message_event_t*)event;
                        xcb_atom_t type = client_message->type;
                        uint32_t data = client_message->data.data32[0];
                        // if (data == SAT_WINDOW_THREAD_KILL)
                        // {
                        //     return nullptr;
                        // }
                    }
                */
                /*
                    if ((event->response_type & ~0x80) == XCB_CLIENT_MESSAGE)
                    {
                        xcb_client_message_event_t* client_message = (xcb_client_message_event_t*)event;
                        xcb_atom_t type = client_message->type;
                        uint32_t data = client_message->data.data32[0];
                        if (data == SAT_WINDOW_THREAD_TIMER)
                        {
                            // return nullptr;
                        }
                    }
                */
                // double-check (in case we have closed the window before processing all events in queue?
                // ??? is this needed, or did i put it here for some debugging purposes?
                // ugh..
                if (window->MIsEventThreadActive)
                {
                    if (!window->processEvent(event))
                    {
                        // window->xcb_event_thread_stop_callback(window);
                        return nullptr;
                    }
                } // active #2
            } // event
        } // while active #1
        // window->xcb_event_thread_stop_callback(window);
        return nullptr;
    } // window
    return nullptr;
}
