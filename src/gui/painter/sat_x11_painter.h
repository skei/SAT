#pragma once

#include "base/sat.h"
#include "base/util/sat_math.h"
#include "gui/painter/sat_base_painter.h"
#include "gui/painter/sat_painter_owner.h"
#include "gui/painter/sat_paint_source.h"
#include "gui/painter/sat_paint_target.h"
#include "extern/gui/sat_x11.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_X11Painter
: public SAT_BasePainter {

    public:

        SAT_X11Painter(SAT_PainterOwner* AOwner, SAT_PaintTarget* ATarget);
        virtual ~SAT_X11Painter();

    public: // BasePainter

        void        beginPainting(uint32_t AWidth, uint32_t AHeight) override;
        void        endPainting() override;
        void        setClip(SAT_Rect ARect) override;
        void        resetClip() override;

    public:        

        void        setDrawColor(SAT_Color AColor) override;
        void        setFillColor(SAT_Color AColor) override;
        void        setTextColor(SAT_Color AColor) override;
        void        setLineWidth(sat_coord_t AWidth) override;

    public:

        void        drawLine(SAT_Point AFrom, SAT_Point ATo) override;
        void        drawRect(SAT_Rect ARect) override;
        void        drawArc(SAT_Point APos, sat_coord_t ARadius, sat_coord_t AAngle1, sat_coord_t AAngle2) override;
        void        fillRect(SAT_Rect ARect) override;
        void        fillArc(SAT_Point APos, sat_coord_t ARadius, sat_coord_t AAngle1, sat_coord_t AAngle2) override;
        void        drawText(SAT_Point APos, const char* AText) override;
        void        drawText(SAT_Rect ARect, const char* AText, uint32_t AAlignment) override;
        sat_coord_t getTextBounds(const char* AText, sat_coord_t* ABounds) override;
        sat_coord_t getTextWidth(const char* AText) override;
        sat_coord_t getTextHeight(const char* AText) override;
        void        drawImage(SAT_Point APos, SAT_PaintSource* ASource) override;
        void        drawImage(SAT_Point APos, SAT_PaintSource* ASource, SAT_Rect ASrc) override;
        void        drawImage(SAT_Rect ADst, SAT_PaintSource* ASource, SAT_Rect ASrc) override;

    private: // X11

        void        set_color(SAT_Color AColor);
        void        set_background_color(SAT_Color AColor);
        void        set_line_width(uint32_t AWidth);
        void        open_font(const char* AName);
        void        close_font(void);
        void        select_font(const char* AName);
        void        measure_string(const char *string);
        void        addStringText8(SAT_XcbPolyText8* pt, char const* s);

    private: // X11

        xcb_connection_t*   MConnection     = nullptr;
        xcb_gcontext_t      MGC             = XCB_NONE;
        xcb_drawable_t      MDrawable       = XCB_NONE;
        xcb_colormap_t      MColorMap      = XCB_NONE;

        // #ifdef SAT_USE_X11_XRENDER
        //     xcb_render_picture_t  MTargetPicture  = 0;
        //     uint32_t              MTargetDepth    = 0;
        // #endif

    private: // state

        SAT_Color         MDrawColor    = SAT_White;    // {1.0, 1.0, 1.0, 1.0};
        SAT_Color         MFillColor    = SAT_Grey;     // {0.5, 0.5, 0.5, 1.5};
        SAT_Color         MTextColor    = SAT_Black;    // {0.0, 0.0, 0.0, 1.5};

        // sat_coord_t    MXpos         = 0.0;
        // sat_coord_t    MYpos         = 0.0;
        // uint32_t       MWidth        = 0;
        // uint32_t       MHeight       = 0;
        sat_coord_t       MLineWidth    = 1.0;

        xcb_font_t        MFont         = XCB_NONE;
        int32_t           MFontAscent   = 0;
        int32_t           MFontDescent  = 0;
        int32_t           MFontWidth    = 0;
        int32_t           MFontHeight   = 0;
        int32_t           MFontOrigin   = 0;
        int32_t           MFontLeft     = 0;
        int32_t           MFontRight    = 0;

};

//----------------------------------------------------------------------
//
// implementation
//
//----------------------------------------------------------------------

SAT_X11Painter::SAT_X11Painter(SAT_PainterOwner* AOwner, SAT_PaintTarget* ATarget)
: SAT_BasePainter(AOwner,ATarget)
{
    MConnection = AOwner->getXcbConnection();
    MDrawable = ATarget->getXcbDrawable();

    MColorMap = SAT.GUI->getScreenColorMap();

    MGC = xcb_generate_id(MConnection);
    uint32_t mask =
        //XCB_GC_FUNCTION
        //XCB_GC_PLANE_MASK
        //XCB_GC_FOREGROUND
        //XCB_GC_BACKGROUND
        //XCB_GC_LINE_WIDTH
        //XCB_GC_LINE_STYLE
        //XCB_GC_CAP_STYLE
        //XCB_GC_JOIN_STYLE
        //XCB_GC_FILL_STYLE
        //XCB_GC_FILL_RULE
        //XCB_GC_TILE
        //XCB_GC_STIPPLE
        //XCB_GC_TILE_STIPPLE_ORIGIN_X
        //XCB_GC_TILE_STIPPLE_ORIGIN_Y
        //XCB_GC_FONT |
        //XCB_GC_SUBWINDOW_MODE
        XCB_GC_GRAPHICS_EXPOSURES;
        //XCB_GC_CLIP_ORIGIN_X
        //XCB_GC_CLIP_ORIGIN_Y
        //XCB_GC_CLIP_MASK
        //XCB_GC_DASH_OFFSET
        //XCB_GC_DASH_LIST
        //XCB_GC_ARC_MODE
    uint32_t values[] = { 0 };
    xcb_create_gc(
        MConnection,
        MGC,
        MDrawable,
        mask,
        values
    );
    /*
        #ifdef SAT_USE_X11_XRENDER
            MTargetPicture = ATarget->getXcbPicture();
            MTargetDepth = ATarget->getDepth();
        #endif
    */
    xcb_flush(MConnection);
}

SAT_X11Painter::~SAT_X11Painter()
{
    //xcb_flush(MConnection);
    xcb_free_gc(MConnection,MGC);
}

//------------------------------
//
//------------------------------

void SAT_X11Painter::beginPainting(uint32_t AWidth, uint32_t AHeight)
{
}

void SAT_X11Painter::endPainting()
{
    // flush?
}

//------------------------------
// clipping
//------------------------------

/*
    from axonlib sources:
        xlib seems to cut off one pixel to the right & bottom... ?
*/


void SAT_X11Painter::setClip(SAT_Rect ARect)
{
    //resetClip();
    xcb_rectangle_t rectangles[] = {{
        (int16_t)SAT_Trunc(ARect.x),
        (int16_t)SAT_Trunc(ARect.y),
        (uint16_t)SAT_Trunc(ARect.w) + 1,
        (uint16_t)SAT_Trunc(ARect.h) + 1
    }};
    xcb_set_clip_rectangles(
        MConnection,
        XCB_CLIP_ORDERING_UNSORTED, // ordering,
        MGC,
        0, // clip_x_origin
        0, // clip_y_origin
        1, // rectangles_len
        rectangles
    );
    xcb_flush(MConnection);
}

void SAT_X11Painter::resetClip()
{
    uint32_t mask = XCB_GC_CLIP_MASK;
    uint32_t values[1];
    values[0] = XCB_NONE;
    xcb_change_gc(MConnection, MGC, mask, values);
    xcb_flush(MConnection);
}

//------------------------------
// state
//------------------------------

void SAT_X11Painter::setDrawColor(SAT_Color AColor)
{
    MDrawColor = AColor;
    set_color(AColor);
}
  
void SAT_X11Painter::setFillColor(SAT_Color AColor)
{
    MFillColor = AColor;
    set_color(AColor);
}

void SAT_X11Painter::setTextColor(SAT_Color AColor)
{
    MTextColor = AColor;
    set_color(AColor);
}

void SAT_X11Painter::setLineWidth(sat_coord_t AWidth)
{
    MLineWidth = AWidth;
    set_line_width(AWidth);
}

//------------------------------
// draw
//------------------------------

void SAT_X11Painter::drawLine(SAT_Point AFrom, SAT_Point ATo)
{
    xcb_point_t polyline[] = {
        (int16_t)SAT_Trunc(AFrom.x),
        (int16_t)SAT_Trunc(AFrom.y),
        (int16_t)SAT_Trunc(ATo.x),
        (int16_t)SAT_Trunc(ATo.y)
    };
    xcb_poly_line(MConnection,XCB_COORD_MODE_ORIGIN,MDrawable,MGC,2,polyline);
}

void SAT_X11Painter::drawRect(SAT_Rect ARect)
{
    //xcb_rectangle_t rectangles[] = {{ (int16_t)ARect.x, (int16_t)ARect.y, (uint16_t)ARect.w, (uint16_t)ARect.h }};
    xcb_rectangle_t rectangles[] = {{
        (int16_t)SAT_Trunc(ARect.x),
        (int16_t)SAT_Trunc(ARect.y),
        (uint16_t)SAT_Trunc(ARect.w) - 1,
        (uint16_t)SAT_Trunc(ARect.h) - 1
    }};
    xcb_poly_rectangle(MConnection,MDrawable,MGC,1,rectangles);
}
  
/*
    angle 1 = start angle, relative to 3 o'clock
    angle 2 = 'distance' 0..1, counter-clockwise
    a1 = -AAngle1 + 0.25    // start angle = 12 o'clock
    a2 = -AAngle2;          // 'distance' 0..1, counter-clockwise
                            // positive = clockwise, negative = counter-clockwise
*/

void SAT_X11Painter::drawArc(SAT_Point APos, sat_coord_t ARadius, sat_coord_t AAngle1, sat_coord_t AAngle2)
{
    sat_coord_t x = APos.x - ARadius;
    sat_coord_t y = APos.y - ARadius;
    sat_coord_t w = APos.x + ARadius;
    sat_coord_t h = APos.y + ARadius;
    sat_coord_t a1 = AAngle1 * 360.0f * 64.0f;
    sat_coord_t a2 = AAngle2 * 360.0f * 64.0f;
    xcb_arc_t arcs[] = {
        (int16_t)SAT_Trunc(x),
        (int16_t)SAT_Trunc(y),
        (uint16_t)SAT_Trunc(w),  // +1
        (uint16_t)SAT_Trunc(h),  // +1
        (int16_t)SAT_Trunc(a1),
        (int16_t)SAT_Trunc(a2)
    };
    xcb_poly_arc(MConnection, MDrawable, MGC, 1, arcs );
}
  
//------------------------------
// fill
//------------------------------

void SAT_X11Painter::fillRect(SAT_Rect ARect)
{
    xcb_rectangle_t rectangles[] = {{
        (int16_t)ARect.x,
        (int16_t)ARect.y,
        (uint16_t)ARect.w,
        (uint16_t)ARect.h
    }};
    xcb_poly_fill_rectangle(MConnection,MDrawable,MGC,1,rectangles);
}

void SAT_X11Painter::fillArc(SAT_Point APos, sat_coord_t ARadius, sat_coord_t AAngle1, sat_coord_t AAngle2)
{
    sat_coord_t x = APos.x - ARadius;
    sat_coord_t y = APos.y - ARadius;
    sat_coord_t w = APos.x + ARadius;
    sat_coord_t h = APos.y + ARadius;
    sat_coord_t a1 = AAngle1 * 360.0f * 64.0f;
    sat_coord_t a2 = AAngle2 * 360.0f * 64.0f;
    xcb_arc_t arcs[] = {
        (int16_t)SAT_Trunc(x),
        (int16_t)SAT_Trunc(y),
        (uint16_t)SAT_Trunc(w),  // +1
        (uint16_t)SAT_Trunc(h),  // +1
        (int16_t)SAT_Trunc(a1),
        (int16_t)SAT_Trunc(a2)
    };
    xcb_poly_fill_arc(MConnection, MDrawable, MGC, 1, arcs );
}
  
//------------------------------
// text
//------------------------------

void SAT_X11Painter::drawText(SAT_Point APos, const char* AText)
{
    uint8_t buffer[512];
    SAT_XcbPolyText8 pt;
    pt.data = buffer;
    pt.used = 0;
    addStringText8(&pt,AText);
    int16_t x = (int16_t)SAT_Trunc(APos.x);
    int16_t y = (int16_t)SAT_Trunc(APos.y);
    xcb_poly_text_8(MConnection,MDrawable,MGC,x,y,pt.used,pt.data);
}

void SAT_X11Painter::drawText(SAT_Rect ARect, const char* AText, uint32_t AAlignment)
{
    measure_string(AText);
    SAT_Point pos;
    sat_coord_t w;
    if (AAlignment & SAT_TEXT_ALIGN_TOP) pos.y = ARect.y    + MFontAscent;
    else if (AAlignment & SAT_TEXT_ALIGN_BOTTOM) pos.y = ARect.y2() - MFontDescent;
    else pos.y = ARect.y + (MFontAscent * 0.5f) + (ARect.h * 0.5f);
    w = MFontWidth;
    if (AAlignment & SAT_TEXT_ALIGN_LEFT) pos.x = ARect.x;
    else if (AAlignment & SAT_TEXT_ALIGN_RIGHT) pos.x = ARect.x2() - w;
    else pos.x = ARect.x + (ARect.w * 0.5f) - (w * 0.5f);
    drawText(pos,AText);
  }

sat_coord_t SAT_X11Painter::getTextBounds(const char* AText, sat_coord_t* ABounds)
{
    measure_string(AText);
    ABounds[0] = 0.0;
    ABounds[1] = - MFontAscent;
    ABounds[2] = MFontWidth;
    ABounds[3] = MFontHeight;
    // SAT_PRINT("ascent %i descent %i\n",MFontAscent,MFontDescent);
    return MFontWidth;//0.0;
}

sat_coord_t SAT_X11Painter::getTextWidth(const char* AText)
{
    measure_string(AText);
    return MFontWidth;
}

sat_coord_t SAT_X11Painter::getTextHeight(const char* AText)
{
    measure_string(AText);
    return MFontHeight;
}

//------------------------------
// image
//------------------------------

// draw entire image

void SAT_X11Painter::drawImage(SAT_Point APos, SAT_PaintSource* ASource)
{
    int16_t x = (int16_t)SAT_Trunc(APos.x);
    int16_t y = (int16_t)SAT_Trunc(APos.y);
    uint32_t w = ASource->getWidth();
    uint32_t h = ASource->getHeight();
    if (ASource->isBitmap()) {
        uint32_t* buffer    = ASource->getBuffer();
        uint32_t buffersize = ASource->getBufferSize();
        xcb_image_t* image = xcb_image_create(
            w,                              // width      width in pixels.
            h,                              // height     height in pixels.
            XCB_IMAGE_FORMAT_Z_PIXMAP,      // format
            32,                             // xpad       scanline pad (8,16,32)
            24, // MTargetDepth,            // depth      (1,4,8,16,24 zpixmap),    (1 xybitmap), (anything xypixmap)
            32,                             // bpp        (1,4,8,16,24,32 zpixmap,  (1 xybitmap), (anything xypixmap)
            32,                             // unit       unit of image representation, in bits (8,16,32)
            XCB_IMAGE_ORDER_LSB_FIRST,      // byte_order
            XCB_IMAGE_ORDER_LSB_FIRST,      // bit_order
            buffer,                         // base       The base address of malloced image data
            buffersize,                     // bytes      The size in bytes of the storage pointed to by base.
                                            //            If base == 0 and bytes == ~0 and data == 0, no storage will be auto-allocated.
            (uint8_t*)buffer                // data       The image data. If data is null and bytes != ~0, then an attempt will be made
                                            //            to fill in data; from base if it is non-null (and bytes is large enough), else
                                            //            by mallocing sufficient storage and filling in base.
        );
        xcb_image_put(
            MConnection,        // xcb_connection_t*  conn,
            MDrawable,          // xcb_drawable_t     draw,
            MGC,                // xcb_gcontext_t     gc,
            image,              // xcb_image_t*       image,
            x,                  // int16_t            x,
            y,                  // int16_t            y,
            0                   // uint8_t            left_pad
        );
        image->base = nullptr;
        xcb_image_destroy(image);
        xcb_flush(MConnection);
    }
    else if (ASource->isSurface())
    {
        #ifdef SAT_USE_X11_XRENDER
            xcb_render_picture_t src_picture = ASource->getXcbPicture();
            xcb_render_composite(
                MConnection,
                XCB_RENDER_PICT_OP_OVER,
                src_picture,
                None,
                MTargetPicture,
                0, // x
                0, // y
                0,
                0,
                x,
                y,
                w,
                h
            );
            xcb_flush(MConnection);
        #else
            xcb_copy_area(
                MConnection,                // Pointer to the xcb_connection_t structure
                ASource->getXcbDrawable(),  // The Drawable we want to paste
                MDrawable,                  // The Drawable on which we copy the previous Drawable
                MGC,                        // A Graphic Context
                0,                          // Top left x coordinate of the region we want to copy
                0,                          // Top left y coordinate of the region we want to copy
                x,                          // Top left x coordinate of the region where we want to copy
                y,                          // Top left y coordinate of the region where we want to copy
                w,                          // Width                 of the region we want to copy
                h                           // Height of the region we want to copy
            );
            xcb_flush(MConnection);
        #endif
    }
}

// draw part of image

void SAT_X11Painter::drawImage(SAT_Point APos, SAT_PaintSource* ASource, SAT_Rect ASrc)
{
    int16_t x = (int16_t)SAT_Trunc(APos.x);            // Top left x coordinate of the region where we want to copy
    int16_t y = (int16_t)SAT_Trunc(APos.y);            // Top left y coordinate of the region where we want to copy
    int16_t src_x = (int16_t)SAT_Trunc(ASrc.x);
    int16_t src_y = (int16_t)SAT_Trunc(ASrc.y);
    uint16_t src_w = (uint16_t)SAT_Trunc(ASrc.w);
    uint16_t src_h = (uint16_t)SAT_Trunc(ASrc.h);
    if (ASource->isBitmap())
    {
    }
    else if (ASource->isSurface())
    {
        xcb_copy_area(
            MConnection,                // Pointer to the xcb_connection_t structure
            ASource->getXcbDrawable(),  // The Drawable we want to paste
            MDrawable,                  // The Drawable on which we copy the previous Drawable
            MGC,                        // A Graphic Context
            src_x,                      // Top left x coordinate of the region we want to copy
            src_y,                      // Top left y coordinate of the region we want to copy
            x,                          // Top left x coordinate of the region where we want to copy
            y,                          // Top left y coordinate of the region where we want to copy
            src_w,                     // Width                 of the region we want to copy
            src_h                      // Height of the region we want to copy
        );
        xcb_flush(MConnection);
    }
}

// stretch image

void SAT_X11Painter::drawImage(SAT_Rect ADst, SAT_PaintSource* ASource, SAT_Rect ASrc)
{
    if (ASource->isBitmap())
    {
    }
    else if (ASource->isSurface())
    {
    }
}

//------------------------------
// X11
//------------------------------

// colormap = screen->default_colormap
// xcb_colormap_t colormapId = xcb_generate_id (connection);
// xcb_create_colormap (connection, XCB_COLORMAP_ALLOC_NONE, colormapId, window, screen->root_visual);

// xcb_alloc_color_reply_t* reply = xcb_alloc_color_reply(
//     connection,
//     xcb_alloc_color(
//         connection,
//         colormapId,
//         65535,
//         0,
//         0
//     ),
//     NULL
// );
// free(reply);




void SAT_X11Painter::set_color(SAT_Color AColor)
{
    uint8_t r = AColor.r * 255.0f;
    uint8_t g = AColor.g * 255.0f;
    uint8_t b = AColor.b * 255.0f;
    uint8_t a = AColor.a * 255.0f;
    uint32_t color = (a << 24) + (r << 16) + (g << 8) + b;
    // xcb_alloc_color(MConnection,MColorMap,r,g,b);
    uint32_t mask = XCB_GC_FOREGROUND;
    uint32_t values[1];
    values[0] = color;
    xcb_change_gc(MConnection, MGC, mask, values);
}

void SAT_X11Painter::set_background_color(SAT_Color AColor)
{
    uint8_t r = AColor.r * 255.0f;
    uint8_t g = AColor.g * 255.0f;
    uint8_t b = AColor.b * 255.0f;
    uint8_t a = 0;//AColor.a * 255.0f;
    uint32_t color = (a << 24) + (r << 16) + (g << 8) + b;
    uint32_t mask = XCB_GC_BACKGROUND;
    uint32_t values[1];
    values[0] = color;
    xcb_change_gc(MConnection, MGC, mask, values);
}

void SAT_X11Painter::set_line_width(uint32_t AWidth)
{
    uint32_t mask = XCB_GC_LINE_WIDTH;
    uint32_t values[1];
    values[0] = AWidth;
    xcb_change_gc(MConnection, MGC, mask, values);
}

void SAT_X11Painter::open_font(const char* AName)
{
    close_font();
    MFont = xcb_generate_id(MConnection);
    xcb_open_font(
        MConnection,
        MFont, //font,
        strlen(AName),
        AName
    );
}

void SAT_X11Painter::close_font(void)
{
    if (MFont)
    {
      xcb_close_font(MConnection,MFont);
    }
}

void SAT_X11Painter::select_font(const char* AName)
{
    open_font(AName);
    uint32_t mask = XCB_GC_FONT;
    uint32_t values[1];
    values[0] = MFont;
    xcb_change_gc(MConnection, MGC, mask, values);
}

void SAT_X11Painter::measure_string(const char *string)
{
    xcb_char2b_t xcb_str[256];
    for (uint32_t i = 0; i < strlen(string); i++)
    {
        xcb_str[i].byte1 = 0;
        xcb_str[i].byte2 = string[i];
    }
    xcb_query_text_extents_cookie_t cookie = xcb_query_text_extents(MConnection, MGC, strlen(string), xcb_str);
    xcb_query_text_extents_reply_t* reply = xcb_query_text_extents_reply(MConnection, cookie, NULL);
    MFontAscent   = reply->font_ascent;
    MFontDescent  = reply->font_descent;
    MFontWidth    = reply->overall_width;
    MFontHeight   = reply->font_ascent + reply->font_descent;
    // MFontHeight   = reply->overall_ascent + reply->overall_descent;
    MFontOrigin   = reply->font_ascent;
    MFontLeft     = reply->overall_left;
    MFontRight    = reply->overall_right;
    // MFontOverallAscent = reply->overall_ascent;
    // MFontOverallDescent = reply->overall_descent;
    // free(xcb_str);
    free(reply);
}

void SAT_X11Painter::addStringText8(SAT_XcbPolyText8* pt, char const* s)
{
    size_t len = strlen(s);
    // Each element can only contain up to 254 characters, so we have to
    // split the string.
    size_t chunks = (len + 253) / 254;
    // Each element starts with one byte length and one byte 'delta', followed
    // by the character payload, determine the according number of needed bytes.
    // size_t const required = chunks * 2 + len;
    // allocate storage
    // uint8_t* buffer = (uint8_t*)realloc(pt->data, pt->used + required);
    // if(!buffer) return;
    // pt->data = buffer;
    while(chunks)
    {
        size_t n = (len < 255) ? len : 254;
        pt->data[pt->used] = n;
        pt->data[pt->used + 1] = 0;
        memcpy( pt->data+2, s, n);
        pt->used += n+2;
        s += n;
        len -= n;
        --chunks;
    }
}

//----------------------------------------------------------------------
#if 0

virtual void drawBitmap(axBitmap* aBitmap, int aX, int aY, int aSrcX, int aSrcY, int aSrcW, int aSrcH)
{
    XPutImage(mDisplay,mDrawable,mGC,(XImage*)aBitmap->getHandle(),aSrcX,aSrcY,aX,aY,aSrcW,aSrcH);
}

virtual void drawSurface(axSurfaceBase* aSurface, int aX, int aY, int aSrcX, int aSrcY, int aSrcW, int aSrcH)
{
    XCopyArea(mDisplay,(Drawable)aSurface->getHandle(),mDrawable,mGC,aSrcX,aSrcY,aSrcW,aSrcH,aX,aY); // mWinHandle = dst
}

virtual void renderSurface(axSurfaceBase* aSurface, int aX, int aY, int aSrcX, int aSrcY, int aSrcW, int aSrcH)
{
    #ifdef AX_ALPHA
        int op = PictOpOver;
        XRenderComposite(mDisplay,op,(Picture)aSurface->getPicture(),None,mPicture,aSrcX,aSrcY,0,0,aX,aY,aSrcW,aSrcH);
    #endif
}

virtual void stretchSurface(axSurfaceBase* aSurface, int aX, int aY, int aW, int aH, int aSrcX, int aSrcY, int aSrcW, int aSrcH)
{
    #ifdef AX_ALPHA
        if (aW > 0)
        {
            if (aH > 0)
            {
                double xs = (float)aSrcW / (float)aW;
                double ys = (float)aSrcH / (float)aH;
                double zs = 1;
                XTransform xform =
                {{
                    { XDoubleToFixed(xs), XDoubleToFixed(0 ), XDoubleToFixed(0 ) },
                    { XDoubleToFixed(0 ), XDoubleToFixed(ys), XDoubleToFixed(0 ) },
                    { XDoubleToFixed(0 ), XDoubleToFixed(0 ), XDoubleToFixed(zs) }
                }};
                //Picture pic = aImage->getPicture();
                Picture pic = (Picture)aSurface->getPicture();
                XRenderSetPictureTransform(mDisplay, pic, &xform );
                int op = PictOpOver;
                // hmmm.. is srcx, srcy transformed by the matrix too?
                float x = axFloor( (float)aSrcX / xs );
                float y = axFloor( (float)aSrcY / ys );
                XRenderComposite(mDisplay,op,pic,None,mPicture,(int)x,(int)y,0,0,aX,aY,aW,aH);
                XRenderSetPictureTransform(mDisplay, pic, &mat_ident );
            } //h>0
        } //w>0
    #endif
}

#endif // 0
//----------------------------------------------------------------------
#if 0

void moveTo(sat_coord_t x, sat_coord_t y)
{
    MXpos = x;
    MYpos = y;
}

void lineTo(sat_coord_t x, sat_coord_t y)
{
    drawLine(MXpos,MYpos,x,y);
    MXpos = x;
    MYpos = y;
}

void drawRoundedRect(sat_coord_t x, sat_coord_t y, sat_coord_t w, sat_coord_t h, sat_coord_t r)
{
    // TODO: no color/size per call
    // void drawRoundedRectangle(KODE_FRect ARect, sat_coord_t ARadius, uint32_t ACorners, KODE_Color AColor, uint32_t AWidth=1)
    // {
    //   //set_color(AColor);
    //   //set_line_width(AWidth);
    //   sat_coord_t r  = ARadius;// - 1;
    //   sat_coord_t r2 = r*2;
    //   sat_coord_t AX1 = ARect.x;
    //   sat_coord_t AY1 = ARect.y;
    //   sat_coord_t AX2 = ARect.x2();
    //   sat_coord_t AY2 = ARect.y2();
    //   drawArc(  KODE_FRect(AX1,      AY1,      AX1+r2-2, AY1+r2-3), 0.75, 0.25, AColor, AWidth ); // upper left
    //   drawArc(  KODE_FRect(AX2-r2+1, AY1,      AX2-1,    AY1+r2-2), 0.00, 0.25, AColor, AWidth ); // upper right
    //   drawArc(  KODE_FRect(AX1,      AY2-r2+1, AX1+r2-2, AY2-1),    0.50, 0.25, AColor, AWidth ); // lower left
    //   drawArc(  KODE_FRect(AX2-r2+1, AY2-r2+2, AX2-1,    AY2-1),    0.25, 0.25, AColor, AWidth ); // lower right
    //   drawLine( AX1+r,    AY1,      AX2-r,    AY1,   AColor, AWidth );  // top
    //   drawLine( AX1+r,    AY2,      AX2-r,    AY2,   AColor, AWidth );  // bottom
    //   drawLine( AX1,      AY1+r,    AX1,      AY2-r, AColor, AWidth );  // left
    //   drawLine( AX2,      AY1+r,    AX2,      AY2-r, AColor, AWidth );  // right
    // }
}
  
void drawEllipse(sat_coord_t cx, sat_coord_t cy, sat_coord_t rx, sat_coord_t ry)
{
    // void drawEllipse(KODE_FRect ARect, KODE_Color AColor, uint32_t AWidth=1)
    // {
    //   set_color(AColor);
    //   set_line_width(AWidth);
    //   xcb_arc_t arcs[] = {
    //     (int16_t)ARect.x,
    //     (int16_t)ARect.y,
    //     (uint16_t)ARect.w, // +1
    //     (uint16_t)ARect.h, // +1
    //     0,
    //     360 * 64
    //   };
    //   xcb_poly_arc(MConnection, MDrawable, MGC, 1, arcs );
    // }
}
  
void fillRoundedRect(sat_coord_t x, sat_coord_t y, sat_coord_t w, sat_coord_t h, sat_coord_t r)
{
    // TODO: no color/size per call
    // void fillRoundedRectangle(KODE_FRect ARect, sat_coord_t ARadius, uint32_t ACorners, KODE_Color AColor)
    // {
    //   //set_color(AColor);
    //   //set_line_width(AWidth);
    //   sat_coord_t r  = ARadius;// - 1;
    //   sat_coord_t r2 = r*2;
    //   sat_coord_t AX1 = ARect.x;
    //   sat_coord_t AY1 = ARect.y;
    //   sat_coord_t AX2 = ARect.x2();
    //   sat_coord_t AY2 = ARect.y2();
    //   fillArc(       KODE_FRect(AX1-1,  AY1-1,   AX1+r2,   AY1+r2),   0.75, 0.25, AColor ); // upper left
    //   fillArc(       KODE_FRect(AX2-r2, AY1-1,   AX2,      AY1+r2-1), 0.00, 0.25, AColor ); // upper right
    //   fillArc(       KODE_FRect(AX1-1,  AY2-r2,  AX1+r2-1, AY2),      0.50, 0.25, AColor ); // lower left
    //   fillArc(       KODE_FRect(AX2-r2, AY2-r2,  AX2,      AY2),      0.25, 0.25, AColor ); // lower right
    //   fillRectangle( KODE_FRect(AX1+r,  AY1,     AX2-r,    AY1+r-1), AColor );  // top
    //   fillRectangle( KODE_FRect(AX1,    AY1+r,   AX2,      AY2-r),   AColor );  // mid
    //   fillRectangle( KODE_FRect(AX1+r,  AY2-r+1, AX2-r,    AY2),     AColor );  // bot
    // }
}
  
void fillEllipse(sat_coord_t cx, sat_coord_t cy, sat_coord_t rx, sat_coord_t ry)
{
    // void fillEllipse(KODE_FRect ARect, KODE_Color AColor)
    // {
    //   set_color(AColor);
    //   xcb_arc_t arcs[] = {
    //     (int16_t)ARect.x,
    //     (int16_t)ARect.y,
    //     (uint16_t)ARect.w, // +1,
    //     (uint16_t)ARect.h, // +1,
    //     (int16_t)(0),
    //     (int16_t)(360 * 64)
    //   };
    //   xcb_poly_fill_arc(MConnection, MDrawable, MGC, 1, arcs );
    // }
}

void fillTriangle(sat_coord_t AX1, sat_coord_t AY1, sat_coord_t AX2, sat_coord_t AY2, sat_coord_t AX3, sat_coord_t AY3, KODE_Color AColor)
{
    set_color(AColor);
    xcb_point_t polyline[] =  {
        (int16_t)AX1, (int16_t)AY1, (int16_t)AX2, (int16_t)AY2,
        (int16_t)AX2, (int16_t)AY2, (int16_t)AX3, (int16_t)AY3,
        (int16_t)AX3, (int16_t)AY3, (int16_t)AX1, (int16_t)AY1,
    };
    xcb_fill_poly(MConnection,MDrawable,MGC,XCB_POLY_SHAPE_CONVEX,XCB_COORD_MODE_ORIGIN,6,polyline);
}
  
#endif // 0
//----------------------------------------------------------------------
