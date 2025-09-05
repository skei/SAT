#pragma once

#include "base/sat_base.h"

#if defined SAT_USE_WAYLAND
    #include "extern/gui/sat_egl.h"
    #define NANOVG_GLES3_IMPLEMENTATION
#elif defined SAT_USE_WIN32
    #include "extern/gui/sat_wgl.h"
    #define NANOVG_GL3_IMPLEMENTATION
#elif defined SAT_USE_X11
    #include "extern/gui/sat_glx.h"
    #define NANOVG_GL3_IMPLEMENTATION
    //#include "gui/egl/sat_egl.h"
    //#define NANOVG_GLES3_IMPLEMENTATION
#endif

#include "extern/gui/nanovg/nanovg.h"
#include "extern/gui/nanovg/nanovg_gl.h"
#include "extern/gui/nanovg/nanovg_gl_utils.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmisleading-indentation"
    #include "extern/gui/nanovg/nanovg.c.h"
#pragma GCC diagnostic pop

#define NANOSVG_IMPLEMENTATION
#include "extern/gui/nanosvg/nanosvgrast.h"

//----------

//typedef NVGpaint sat_paint_t;

NVGcolor nvg_color(SAT_Color AColor) {
  NVGcolor color;
  color.r = AColor.r;
  color.g = AColor.g;
  color.b = AColor.b;
  color.a = AColor.a;
  return color;
}
