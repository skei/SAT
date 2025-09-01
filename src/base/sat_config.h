#pragma once

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

#define SAT_VENDOR                  "skei.audio"
#define SAT_URL                     "https://github.com/skei/SA_Toolkit"
#define SAT_VERSION                 "0.0.0"
#define SAT_LOG_DIRECTORY           "Desktop/skei.audio"
#define SAT_USER_CONFIG_FILE        "user_config.h"

//----------------------------------------------------------------------
//
// 'magic' constants
//
//----------------------------------------------------------------------

//----------------------------------------
// base
//----------------------------------------

#define SAT_MAX_NAME_LENGTH                         64
#define SAT_MAX_PATH_LENGTH                         1024
#define SAT_MAX_STRING_LENGTH                       256
#define SAT_MAX_VALUE_TEXT_LENGTH                   32

//----------------------------------------
// plugin
//----------------------------------------

// #define SAT_PARAMETER_NUM_VALUES                    16
// #define SAT_PLUGIN_MAX_BLOCK_SIZE                   4096

//----------------------------------------
// gui
//----------------------------------------

#define SAT_PAINTER_CLIP_RECT_STACK_SIZE                 256
#define SAT_QUEUE_SIZE_PAINT                        256
#define SAT_QUEUE_SIZE_REALIGN                      256
#define SAT_QUEUE_SIZE_REDRAW                       256
#define SAT_QUEUE_SIZE_RESIZE                       256
#define SAT_QUEUE_SIZE_TWEEN                        256
#define SAT_QUEUE_SIZE_UPDATE                       256
#define SAT_RENDERER_MAJOR_VERSION                  3
#define SAT_RENDERER_MINOR_VERSION                  2
#define SAT_TWEEN_MAX_VALUES                        4
#define SAT_TWEEN_FINISHED                          0xffffffff
// #define SAT_WIDGET_NUM_VALUES                       16
#define SAT_WINDOW_BUFFER_MIN_SIZE                  256
#define SAT_WINDOW_MOUSE_DBL_CLICK_MS               200
#define SAT_WINDOW_TIMER_MS                         20

//----------------------------------------
// other
//----------------------------------------

// #define SAT_AUDIO_QUANTIZED_SIZE                    32
// #define SAT_MODMATRIX_MAX_SRC_COUNT                 32
// #define SAT_MODMATRIX_MAX_DST_COUNT                 32
// #define SAT_MODMATRIX_MAX_MOD_COUNT                 32

//----------------------------------------
// not used?
//----------------------------------------

// #define SAT_PLUGIN_MAX_PARAM_EVENTS_PER_BLOCK       1024
// #define SAT_PLUGIN_MAX_MOD_EVENTS_PER_BLOCK         1024
// #define SAT_PLUGIN_MAX_GUI_EVENTS_PER_BLOCK         32
// #define SAT_PLUGIN_MAX_NOTE_ENDS_PER_BLOCK          1024
// #define SAT_THREAD_POOL_MAX_THREADS                 256
// #define SAT_THREAD_POOL_MAX_VOICES                  96
// #define SAT_TWEEN_CHAIN_QUEUE_SIZE                  32
// #define SAT_VOICE_MAX_EVENTS_PER_BLOCK              1024
// #define SAT_VOICE_PROCESSOR_MAX_EVENTS_PER_BLOCK    1024
// #define SAT_VOICE_PROCESSOR_NUM_THREADS             12
// #define SAT_WINDOW_DIRTY_QUEUE_SIZE                 1024

//----------------------------------------------------------------------
//
// options
//
//----------------------------------------------------------------------

//----------------------------------------
// base
//----------------------------------------

#define SAT_DEBUG_ASSERT
#define SAT_DEBUG_BREAKPOINT
#define SAT_DEBUG_CRASH_HANDLER
#define SAT_DEBUG_CALLSTACK
// #define SAT_DEBUG_MEMTRACE
#define SAT_DEBUG_OBSERVER
// #define SAT_DEBUG_WINDOW
#define SAT_INCLUDE_LOG
#define SAT_INCLUDE_REGISTRY
#define SAT_INCLUDE_STATISTICS
#define SAT_LOG_TIME
#define SAT_LOG_THREAD
// #define SAT_NO_AUTODELETE
// #define SAT_NO_GLOBAL
// #define SAT_PRINT_ALWAYS
// #define SAT_PRINT_PRETTY_FUNCTION
// #define SAT_PRINT_SOCKET
#define SAT_PRINT_THREAD
#define SAT_PRINT_TIME

// ----- setup in compile script -----

// #define SAT_DEBUG
// #define SAT_INCLUDE_TESTS
// #define SAT_LIBRARY

//----------------------------------------
// plugin
//----------------------------------------

// #define SAT_INCLUDE_ARA_EXTENSIONS
// #define SAT_INCLUDE_REAPER_EXTENSIONS
// #define SAT_NO_ENTRY

// ----- setup in compile script -----

// #define SAT_PLUGIN_CLAP
// #define SAT_PLUGIN_DSSI
// #define SAT_PLUGIN_EXE
// #define SAT_PLUGIN_LADSPA
// #define SAT_PLUGIN_LV2
// #define SAT_PLUGIN_VST2
// #define SAT_PLUGIN_VST3

//----------------------------------------
// gui
//----------------------------------------

// #define SAT_NO_BITMAP_DECODE
// #define SAT_NO_BITMAP_DECODE_FILE
// #define SAT_NO_WINDOW_BUFFERING
#define SAT_WINDOW_REDIRECT_TIMER_TO_GUI_THREAD
#define SAT_X11_WAIT_FOR_MAPNOTIFY

// ----- setup in compile script -----

// #define SAT_GUI_NONE
// #define SAT_GUI_NATIVE
// #define SAT_GUI_CPU
// #define SAT_GUI_GPU
// #define SAT_PAINTER_BLEND2D
// #define SAT_PAINTER_CAIRO
// #define SAT_PAINTER_CANVAS_ITY
// #define SAT_PAINTER_NANOVG
// #define SAT_PAINTER_WIN32
// #define SAT_PAINTER_X11
// #define SAT_RENDERER_EGL
// #define SAT_RENDERER_GDI
// #define SAT_RENDERER_GLX
// #define SAT_RENDERER_WGL
// #define SAT_RENDERER_X11
// #define SAT_SURFACE_BITMAP
// #define SAT_SURFACE_NANOVG
// #define SAT_SURFACE_WIN32
// #define SAT_SURFACE_X11  
// #define SAT_USE_CAIRO
// #define SAT_USE_X11
// #define SAT_USE_X11_XRENDER
// #define SAT_WINDOW_WAYLAND
// #define SAT_WINDOW_WIN32
// #define SAT_WINDOW_X11

//----------------------------------------
// other
//----------------------------------------



//----------------------------------------------------------------------
//
// user config
//
//----------------------------------------------------------------------

#if defined __has_include
    #if __has_include (SAT_USER_CONFIG_FILE)
        #include SAT_USER_CONFIG_FILE
    #endif
#endif

//----------------------------------------------------------------------
//
// defaults, simplifications, 'cleanup', ..
//
//----------------------------------------------------------------------

//----------------------------------------
// debug
//----------------------------------------

#ifndef SAT_DEBUG
    #undef SAT_DEBUG_ASSERT
    #undef SAT_DEBUG_BREAKPOINT
    #undef SAT_DEBUG_CRASH_HANDLER
    #undef SAT_DEBUG_CALLSTACK
    #undef SAT_DEBUG_MEMTRACE
    #undef SAT_DEBUG_OBSERVER
    #undef SAT_DEBUG_WINDOW
#endif

//----------------------------------------
// plugin
//----------------------------------------

#undef SAT_LIBRARY
#undef SAT_PLUGIN_FORMAT_DEFINED

//-----

#ifdef SAT_PLUGIN_CLAP
    #define SAT_PLUGIN_FORMAT_DEFINED
    #define SAT_LIBRARY
#endif

#ifdef SAT_PLUGIN_DSSI
    #define SAT_PLUGIN_FORMAT_DEFINED
    #define SAT_LIBRARY
#endif

#ifdef SAT_PLUGIN_EXE
    #define SAT_PLUGIN_FORMAT_DEFINED
#endif

#ifdef SAT_PLUGIN_LADSPA
    #define SAT_PLUGIN_FORMAT_DEFINED
    #define SAT_LIBRARY
#endif

#ifdef SAT_PLUGIN_LV2
    #define SAT_PLUGIN_FORMAT_DEFINED
    #define SAT_LIBRARY
#endif

#ifdef SAT_PLUGIN_VST2
    #define SAT_PLUGIN_FORMAT_DEFINED
    #define SAT_LIBRARY
#endif

#ifdef SAT_PLUGIN_VST3
    #define SAT_PLUGIN_FORMAT_DEFINED
    #define SAT_LIBRARY
#endif

//-----

#ifndef SAT_PLUGIN_FORMAT_DEFINED
    #warning NO PLUGIN FORMAT DEFINED
#endif

#ifdef SAT_LIBRARY
    #define SAT_PRINT_SOCKET
    #undef SAT_DEBUG_MEMTRACE
#endif

//----------------------------------------
// gui
//----------------------------------------

#undef SAT_GUI_TYPE_DEFINED

//-----

#if defined SAT_NO_GUI

    // no gui

    #define SAT_GUI_TYPE_DEFINED

#elif defined SAT_GUI_NATIVE

    // simplified

    #define SAT_GUI_TYPE_DEFINED
    #if defined SAT_LINUX
        #define SAT_USE_X11
        // #define SAT_USE_X11_XRENDER
        #define SAT_PAINTER_X11  
        #define SAT_RENDERER_X11  
        #define SAT_SURFACE_X11  
        #define SAT_WINDOW_X11  
    #elif defined SAT_WIN32
        #error NOT IMPLEMENTED YET
    #else
        #error NO OS DEFINED
    #endif
#elif defined SAT_GUI_CPU
    #define SAT_GUI_TYPE_DEFINED
    // cairo, canvasify, blend2d, ..
#elif defined SAT_GUI_GPU
    #define SAT_GUI_TYPE_DEFINED
    // opengl, nanovg

#else

    // TODO: manually (window, surface, renderer, painter)

#endif

//-----

#ifndef SAT_GUI_TYPE_DEFINED
    #warning NO GUI TYPE DEFINED
#endif

//----------------------------------------
// other
//----------------------------------------


