#pragma once

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

#define SAT_MAGIC               0x5341545f  // 'SAT_'
#define SAT_MAGIC_USER          0x7361745f  // 'sat_'
#define SAT_MAGIC_PLUGIN        0x53415450  // 'SATP'
#define SAT_MAGIC_EDITOR        0x53415445  // 'SATE'

#define SAT_EVENT_SPACE_ID      SAT_MAGIC   // CLAP_CORE_EVENT_SPACE_ID

//----------

const char  SAT_NULL_STRING[]   = "";
const char  SAT_HEX_TABLE[]     = "0123456789ABCDEF";
const char  SAT_VALID_SYMBOLS[] = "________________________________"
                                  "________________0123456789______"
                                  "_ABCDEFGHIJKLMNOPQRSTUVWXYZ_____"
                                  "_abcdefghijklmnopqrstuvwxyz_____";
const char* SAT_MONTH_NAMES[13] = { "jan", "feb", "mar", "apr", "may", "jun", "jul", "aug", "sep", "oct", "nov", "dec", "errorember" };

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

#define SAT_PI              3.14159265358979323846
#define SAT_PI2             (SAT_PI * 2.0)
#define SAT_PI05            (SAT_PI * 0.5)
#define SAT_INVPI           (1.0 / SAT_PI)
#define SAT_INVPI2          (1.0 / SAT_PI2)
#define SAT_INVPI05         (1.0 / SAT_PI05)

#define SAT_TINY            0.001
#define SAT_VERY_TINY       0.00001

#define SAT_INV360          (1.0 / 360.0)
#define SAT_INV12           (1.0 / 12.0)
#define SAT_INV16           (1.0 / 16.0)
#define SAT_INV32           (1.0 / 32.0)
#define SAT_INV127          (1.0 / 127.0)
#define SAT_INV255          (1.0 / 255.0)
#define SAT_INV256          (1.0 / 256.0)
#define SAT_INV8192         (1.0 / 8192.0)

#define SAT_SQRT2           sqrt(2.0)

//----------

#define SAT_CHAR_BIT        8
#define SAT_CHAR_MAX        0x7f                      // 127
#define SAT_SHORT_MAX       0x7fff                    // 32767
#define SAT_INT32_MAX       0x7fffffff                // 2147483647
#define SAT_UINT32_MAX      0xffffffff                // 8589934591U
#define SAT_INT64_MAX       0x7fffffffffffffff        // 9223372036854775807LL
#define SAT_UINT64_MAX      0x7fffffffffffffff        // 18446744073709551615ULL
#define SAT_FLOAT_MAX       3.40282347e+38F
#define SAT_FLOAT_MIN       1.17549435E-38F
#define SAT_FLOAT_EPSILON   1.19209290E-7F
#define SAT_FLOAT_DENORM    1.40129846E-45F
#define SAT_DOUBLE_MAX      1.7976931348623157e+308
#define SAT_DOUBLE_MIN      2.2250738585072014E-308
#define SAT_DOUBLE_EPSILON  2.2204460492503131E-16
#define SAT_DOUBLE_DENORM   4.9406564584124654E-324

#if defined SAT_32BIT
    #define SAT_INT_MAX     SAT_INT32_MAX             // 2147483647L
    #define SAT_UINT_MAX    SAT_UINT32_MAX            // 8589934591UL
#elif defined SAT_64BIT
    #define SAT_INT_MAX     SAT_INT64_MAX             // 9223372036854775807L
    #define SAT_UINT_MAX    SAT_UINT64_MAX            // 18446744073709551615UL
#else
    #error UNKNOWN ARCHITECTURE (WORD SIZE)
#endif

#define SAT_RANDMAX         0x7fffffff
#define SAT_INVRANDMAX      (1.0 / (double)SAT_RANDMAX)

//----------------------------------------------------------------------
//
// 'enums'
//
//----------------------------------------------------------------------

#define SAT_BUTTON_NONE                             0
#define SAT_BUTTON_LEFT                             1
#define SAT_BUTTON_MIDDLE                           2
#define SAT_BUTTON_RIGHT                            3
#define SAT_BUTTON_SCROLL_UP                        4
#define SAT_BUTTON_SCROLL_DOWN                      5
#define SAT_BUTTON_SIDE_BACKWARD                    8
#define SAT_BUTTON_SIDE_FORWARD                     9

#define SAT_CORNER_NONE                             0
#define SAT_CORNER_UPPER_LEFT                       0x01
#define SAT_CORNER_UPPER_RIGHT                      0x02
#define SAT_CORNER_LOWER_RIGHT                      0x04
#define SAT_CORNER_LOWER_LEFT                       0x08
#define SAT_CORNER_UPPER                            (SAT_CORNER_UPPER_LEFT  | SAT_CORNER_UPPER_RIGHT)
#define SAT_CORNER_LOWER                            (SAT_CORNER_LOWER_LEFT  | SAT_CORNER_LOWER_RIGHT)
#define SAT_CORNER_LEFT                             (SAT_CORNER_UPPER_LEFT  | SAT_CORNER_LOWER_LEFT)
#define SAT_CORNER_RIGHT                            (SAT_CORNER_UPPER_RIGHT | SAT_CORNER_LOWER_RIGHT)
#define SAT_CORNER_ALL                              (SAT_CORNER_UPPER       | SAT_CORNER_LOWER)

#define SAT_CURSOR_RESET                            -5
#define SAT_CURSOR_LOCK                             -4
#define SAT_CURSOR_UNLOCK                           -3
#define SAT_CURSOR_SHOW                             -2
#define SAT_CURSOR_HIDE                             -1
#define SAT_CURSOR_DEFAULT                          0

#define SAT_EDGE_NONE                               0
#define SAT_EDGE_LEFT                               0x01
#define SAT_EDGE_RIGHT                              0x02
#define SAT_EDGE_TOP                                0x04
#define SAT_EDGE_BOTTOM                             0x08
#define SAT_EDGE_HORIZ                              (SAT_EDGE_LEFT | SAT_EDGE_RIGHT)
#define SAT_EDGE_VERT                               (SAT_EDGE_TOP | SAT_EDGE_BOTTOM)
#define SAT_EDGE_ALL                                (SAT_EDGE_HORIZ | SAT_EDGE_VERT)

#define SAT_FILE_READ_BINARY                        (char*)"rb"
#define SAT_FILE_READ_TEXT                          (char*)"r"
#define SAT_FILE_WRITE_BINARY                       (char*)"wb"
#define SAT_FILE_WRITE_TEXT                         (char*)"w"
#define SAT_FILE_APPEND_BINARY                      (char*)"ab"
#define SAT_FILE_APPEND_TEXT                        (char*)"a"

#define SAT_HINT_NORMAL                             0
#define SAT_HINT_CLEAR                              1
// #define SAT_HINT_SHOW                            2
// #define SAT_HINT_HIDE                            3

#define SAT_KEY_NONE                                0
#define SAT_KEY_BACKSPACE                           8
#define SAT_KEY_ENTER                               13
#define SAT_KEY_ESC                                 27
#define SAT_KEY_SPACE                               32
#define SAT_KEY_END                                 35
#define SAT_KEY_HOME                                36
#define SAT_KEY_LEFT                                37
#define SAT_KEY_RIGHT                               39
#define SAT_KEY_DELETE                              46

#define SAT_KEY_STATE_NONE                          0
#define SAT_KEY_STATE_SHIFT                         0x01
#define SAT_KEY_STATE_CAPS                          0x02
#define SAT_KEY_STATE_CTRL                          0x04
#define SAT_KEY_STATE_ALT                           0x08
#define SAT_KEY_STATE_ALTGR                         0x10

#define SAT_OBSERVE_NONE                            0
#define SAT_OBSERVE_FLOAT                           1
#define SAT_OBSERVE_DOUBLE                          2
#define SAT_OBSERVE_INT32                           3
#define SAT_OBSERVE_UINT32                          4
#define SAT_OBSERVE_CHAR                            5
#define SAT_OBSERVE_PTR                             6
#define SAT_OBSERVE_STR                             7

#define SAT_OS_UNKNOWN                              0
#define SAT_OS_LINUX                                1
#define SAT_OS_WIN32                                2
#define SAT_OS_MAC                                  3

#define SAT_SKIN_BACKGROUND_NONE                    0
#define SAT_SKIN_BACKGROUND_COLOR                   1
#define SAT_SKIN_BACKGROUND_GRADIENT                2
#define SAT_SKIN_BACKGROUND_IMAGE                   3

#define SAT_SKIN_BORDER_NONE                        0
#define SAT_SKIN_BORDER_RECT                        1
#define SAT_SKIN_BORDER_ROUNDED                     2

#define SAT_SKIN_DROP_SHADOW_NONE                   0
#define SAT_SKIN_DROP_SHADOW_INNER                  1
#define SAT_SKIN_DROP_SHADOW_OUTER                  2

#define SAT_SKIN_GRADIENT_NONE                      0
#define SAT_SKIN_GRADIENT_VERTICAL                  1

#define SAT_SKIN_MATCH_ALL                          0
#define SAT_SKIN_MATCH_SINGLE                       1
#define SAT_SKIN_MATCH_MATCH                        2
#define SAT_SKIN_MATCH_ANY                          3

#define SAT_SKIN_STATE_NORMAL                       0
#define SAT_SKIN_STATE_HOVERING                     0x01
#define SAT_SKIN_STATE_DISABLED                     0x02
#define SAT_SKIN_STATE_HIGHLIGHTED                  0x04
#define SAT_SKIN_STATE_INTERACT                     0x08
#define SAT_SKIN_STATE_ALL                          0x0F
#define SAT_SKIN_STATE_COUNT                        16

#define SAT_SKIN_TEXT_NONE                          0
#define SAT_SKIN_TEXT_NORMAL                        1

#define SAT_TEXT_ALIGN_CENTER                       0
#define SAT_TEXT_ALIGN_LEFT                         0x01
#define SAT_TEXT_ALIGN_RIGHT                        0x02
#define SAT_TEXT_ALIGN_TOP                          0x04
#define SAT_TEXT_ALIGN_BOTTOM                       0x08

#define SAT_ANIM_FINISHED                           0xffffffff

#define SAT_WIDGET_DRAG_AND_DROP                    0
#define SAT_WIDGET_DRAG_SELECTION                  -1
#define SAT_WIDGET_DRAG_VALUE                      -2

#define SAT_WIDGET_LAYOUT_ANCHOR_NONE               0
#define SAT_WIDGET_LAYOUT_ANCHOR_LEFT               0x01
#define SAT_WIDGET_LAYOUT_ANCHOR_TOP                0x02
#define SAT_WIDGET_LAYOUT_ANCHOR_RIGHT              0x04
#define SAT_WIDGET_LAYOUT_ANCHOR_BOTTOM             0x08
#define SAT_WIDGET_LAYOUT_ANCHOR_TOP_LEFT           (SAT_WIDGET_LAYOUT_ANCHOR_TOP | SAT_WIDGET_LAYOUT_ANCHOR_LEFT)
#define SAT_WIDGET_LAYOUT_ANCHOR_TOP_RIGHT          (SAT_WIDGET_LAYOUT_ANCHOR_TOP | SAT_WIDGET_LAYOUT_ANCHOR_RIGHT)
#define SAT_WIDGET_LAYOUT_ANCHOR_BOTTOM_LEFT        (SAT_WIDGET_LAYOUT_ANCHOR_BOTTOM | SAT_WIDGET_LAYOUT_ANCHOR_LEFT)
#define SAT_WIDGET_LAYOUT_ANCHOR_BOTTOM_RIGHT       (SAT_WIDGET_LAYOUT_ANCHOR_BOTTOM | SAT_WIDGET_LAYOUT_ANCHOR_RIGHT)
#define SAT_WIDGET_LAYOUT_ANCHOR_CENTER_HORIZONTAL  0x10
#define SAT_WIDGET_LAYOUT_ANCHOR_CENTER_VERTICAL    0x20
#define SAT_WIDGET_LAYOUT_ANCHOR_CENTER             (SAT_WIDGET_LAYOUT_ANCHOR_CENTER_HORIZONTAL | SAT_WIDGET_LAYOUT_ANCHOR_CENTER_VERTICAL)

#define SAT_WIDGET_LAYOUT_STRETCH_NONE              0
#define SAT_WIDGET_LAYOUT_STRETCH_LEFT              0x01
#define SAT_WIDGET_LAYOUT_STRETCH_TOP               0x02
#define SAT_WIDGET_LAYOUT_STRETCH_RIGHT             0x04
#define SAT_WIDGET_LAYOUT_STRETCH_BOTTOM            0x08
#define SAT_WIDGET_LAYOUT_STRETCH_HORIZONTAL        (SAT_WIDGET_LAYOUT_STRETCH_LEFT | SAT_WIDGET_LAYOUT_STRETCH_RIGHT)
#define SAT_WIDGET_LAYOUT_STRETCH_VERTICAL          (SAT_WIDGET_LAYOUT_STRETCH_TOP | SAT_WIDGET_LAYOUT_STRETCH_BOTTOM)
#define SAT_WIDGET_LAYOUT_STRETCH_ALL               (SAT_WIDGET_LAYOUT_STRETCH_HORIZONTAL | SAT_WIDGET_LAYOUT_STRETCH_VERTICAL)

#define SAT_WIDGET_LAYOUT_CROP_NONE                 0
#define SAT_WIDGET_LAYOUT_CROP_LEFT                 0x01
#define SAT_WIDGET_LAYOUT_CROP_TOP                  0x02
#define SAT_WIDGET_LAYOUT_CROP_RIGHT                0x04
#define SAT_WIDGET_LAYOUT_CROP_BOTTOM               0x08
#define SAT_WIDGET_LAYOUT_CROP_HORIZONTAL           (SAT_WIDGET_LAYOUT_CROP_LEFT | SAT_WIDGET_LAYOUT_CROP_RIGHT)
#define SAT_WIDGET_LAYOUT_CROP_VERTICAL             (SAT_WIDGET_LAYOUT_CROP_TOP | SAT_WIDGET_LAYOUT_CROP_BOTTOM)
#define SAT_WIDGET_LAYOUT_CROP_ALL                  (SAT_WIDGET_LAYOUT_CROP_HORIZONTAL | SAT_WIDGET_LAYOUT_CROP_VERTICAL)

#define SAT_WIDGET_LAYOUT_RELATIVE_NONE             0
// #define SAT_WIDGET_LAYOUT_RELATIVE_PERCENT       0x01
#define SAT_WIDGET_LAYOUT_RELATIVE_PARENT           1 // 0x01
#define SAT_WIDGET_LAYOUT_RELATIVE_LAYOUT           2 // 0x02
#define SAT_WIDGET_LAYOUT_RELATIVE_ROOT             3 // 0x04

#define SAT_WIDGET_LAYOUT_STACK_NONE                0
#define SAT_WIDGET_LAYOUT_STACK_HORIZONTAL          0x01
#define SAT_WIDGET_LAYOUT_STACK_VERTICAL            0x02
#define SAT_WIDGET_LAYOUT_STACK_END                 0x04

#define SAT_WIDGET_NOTIFY_NONE                      0
#define SAT_WIDGET_NOTIFY_SELECT                    1
#define SAT_WIDGET_NOTIFY_CANCEL                    2
#define SAT_WIDGET_NOTIFY_TOGGLE                    3
#define SAT_WIDGET_NOTIFY_OPEN                      4
#define SAT_WIDGET_NOTIFY_CLOSE                     5

#define SAT_WIDGET_PAINT_NORMAL                     0
#define SAT_WIDGET_PAINT_VALUE                      1
#define SAT_WIDGET_PAINT_MODULATION                 2

#define SAT_WIDGET_REALIGN_NORMAL                   0
#define SAT_WIDGET_REALIGN_CHILDREN                 0
#define SAT_WIDGET_REALIGN_PARENT                   0x01
#define SAT_WIDGET_REALIGN_ROOT                     0x02
#define SAT_WIDGET_REALIGN_SELF                     0x04
// #define SAT_WIDGET_REALIGN_POS                   0x02
// #define SAT_WIDGET_REALIGN_SIZE                  0x04
// #define SAT_WIDGET_REALIGN_RECT                  (SAT_WIDGET_REALIGN_POS | SAT_WIDGET_REALIGN_SIZE)

#define SAT_WIDGET_REDRAW_NORMAL                    0
#define SAT_WIDGET_REDRAW_SELF                      0x01
#define SAT_WIDGET_REDRAW_PARENT                    0x02
#define SAT_WIDGET_REDRAW_ROOT                      0x04
#define SAT_WIDGET_REDRAW_CHILDREN                  0x08

#define SAT_WIDGET_UPDATE_VALUE                     0

#define SAT_WINDOW_USER_MESSAGE_KILL                666
#define SAT_WINDOW_USER_MESSAGE_TIMER               667

//----------------------------------------------------------------------
//
// terminal colors
//
//----------------------------------------------------------------------

// https://gist.github.com/JBlond/2fea43a3049b38287e5e9cefc87b2124
// 0 Reset/Normal, 1 Bold, 2 Faint, 3 Italics, 4 Underlined
// "\e[1;97m" (bold white)

#if defined SAT_LINUX

    #define SAT_TERM_BG_BLACK                   "\e[40m"
    #define SAT_TERM_BG_RED                     "\e[41m"
    #define SAT_TERM_BG_GREEN                   "\e[42m"
    #define SAT_TERM_BG_YELLOW                  "\e[43m"
    #define SAT_TERM_BG_BLUE                    "\e[44m"
    #define SAT_TERM_BG_MAGENTA                 "\e[45m"
    #define SAT_TERM_BG_CYAN                    "\e[46m"
    #define SAT_TERM_BG_LIGHT_GREY              "\e[47m"

    #define SAT_TERM_BG_GREY                    "\e[100m"
    #define SAT_TERM_BG_LIGHT_RED               "\e[101m"
    #define SAT_TERM_BG_LIGHT_GREEN             "\e[102m"
    #define SAT_TERM_BG_LIGHT_YELLOW            "\e[103m"
    #define SAT_TERM_BG_LIGHT_BLUE              "\e[104m"
    #define SAT_TERM_BG_LIGHT_MAGENTA           "\e[105m"
    #define SAT_TERM_BG_LIGHT_CYAN              "\e[106m"
    #define SAT_TERM_BG_WHITE                   "\e[107m"

    #define SAT_TERM_FG_BLACK                   "\e[30m"
    #define SAT_TERM_FG_RED                     "\e[31m"
    #define SAT_TERM_FG_GREEN                   "\e[32m"
    #define SAT_TERM_FG_YELLOW                  "\e[33m"
    #define SAT_TERM_FG_BLUE                    "\e[34m"
    #define SAT_TERM_FG_MAGENTA                 "\e[35m"
    #define SAT_TERM_FG_CYAN                    "\e[36m"
    #define SAT_TERM_FG_LIGHT_GREY              "\e[37m"

    #define SAT_TERM_FG_GREY                    "\e[90m"
    #define SAT_TERM_FG_LIGHT_RED               "\e[91m"
    #define SAT_TERM_FG_LIGHT_GREEN             "\e[92m"
    #define SAT_TERM_FG_LIGHT_YELLOW            "\e[93m"
    #define SAT_TERM_FG_LIGHT_BLUE              "\e[94m"
    #define SAT_TERM_FG_LIGHT_MAGENTA           "\e[95m"
    #define SAT_TERM_FG_LIGHT_CYAN              "\e[96m"
    #define SAT_TERM_FG_WHITE                   "\e[97m"

    #define SAT_TERM_RESET                      "\e[0m"
    
    #define SAT_TERM_NORMAL                     "\e[0;97m"
    #define SAT_TERM_BOLD                       "\e[1;97m"
    #define SAT_TERM_FAINT                      "\e[2;97m"
    #define SAT_TERM_ITALICS                    "\e[3;97m"
    #define SAT_TERM_UNDERLINE                  "\e[4;97m"
  
#elif defined SAT_WIN32

    #define SAT_TERM_BG_BLACK                   ""
    #define SAT_TERM_BG_RED                     ""
    #define SAT_TERM_BG_GREEN                   ""
    #define SAT_TERM_BG_YELLOW                  ""
    #define SAT_TERM_BG_BLUE                    ""
    #define SAT_TERM_BG_MAGENTA                 ""
    #define SAT_TERM_BG_CYAN                    ""
    #define SAT_TERM_BG_LIGHT_GREY              ""

    #define SAT_TERM_BG_GREY                    ""
    #define SAT_TERM_BG_LIGHT_RED               ""
    #define SAT_TERM_BG_LIGHT_GREEN             ""
    #define SAT_TERM_BG_LIGHT_YELLOW            ""
    #define SAT_TERM_BG_LIGHT_BLUE              ""
    #define SAT_TERM_BG_LIGHT_MAGENTA           ""
    #define SAT_TERM_BG_LIGHT_CYAN              ""
    #define SAT_TERM_BG_WHITE                   ""

    #define SAT_TERM_FG_BLACK                   ""
    #define SAT_TERM_FG_RED                     ""
    #define SAT_TERM_FG_GREEN                   ""
    #define SAT_TERM_FG_YELLOW                  ""
    #define SAT_TERM_FG_BLUE                    ""
    #define SAT_TERM_FG_MAGENTA                 ""
    #define SAT_TERM_FG_CYAN                    ""
    #define SAT_TERM_FG_LIGHT_GREY              ""

    #define SAT_TERM_FG_GREY                    ""
    #define SAT_TERM_FG_LIGHT_RED               ""
    #define SAT_TERM_FG_LIGHT_GREEN             ""
    #define SAT_TERM_FG_LIGHT_YELLOW            ""
    #define SAT_TERM_FG_LIGHT_BLUE              ""
    #define SAT_TERM_FG_LIGHT_MAGENTA           ""
    #define SAT_TERM_FG_LIGHT_CYAN              ""
    #define SAT_TERM_FG_WHITE                   ""

    #define SAT_TERM_RESET                      ""

    #define SAT_TERM_NORMAL                     ""
    #define SAT_TERM_BOLD                       ""
    #define SAT_TERM_FAINT                      ""
    #define SAT_TERM_ITALICS                    ""
    #define SAT_TERM_UNDERLINE                  ""

#else

    #error NOT IMPLEMENTED YET

#endif
