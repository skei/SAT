
/*
    num x/y
    select none, single, column, row, area
    select single/multi per column/row
    resizable column/row
    cells = callbacks for init, drawing, mouse events
    can insert widget per cell in init..
    combine rows, colums, areas..
*/

/*
    combined.. per cell:
        bool        combined                            // true if part of combined area
        uint32_t    combined_x_start, combined_y_start  // first (upper left) cell
        uint32_t    combined_x_count, combined_y_count  // combined area width/height
        uint32_t    combined_x_index, combined_y_index  // current cell index

        00  01  02
        10  11  12
        20  21  22
*/

#define SAT_GRID_WIDGET_SELECT_NONE
#define SAT_GRID_WIDGET_SELECT_SINGLE
#define SAT_GRID_WIDGET_SELECT_SINGLE_PER_COLUMN
#define SAT_GRID_WIDGET_SELECT_SINGLE_PER_ROW
#define SAT_GRID_WIDGET_SELECT_AREA

#define SAT_GRID_WIDGET_RESIZE_COLUMNS
#define SAT_GRID_WIDGET_RESIZE_ROWS

#define SAT_GRID_WIDGET_CALLBACK_INIT
#define SAT_GRID_WIDGET_CALLBACK_MOUSE_CLICK
#define SAT_GRID_WIDGET_CALLBACK_MOUSE_DBL_CLICK
#define SAT_GRID_WIDGET_CALLBACK_MOUSE_MOVE
#define SAT_GRID_WIDGET_CALLBACK_MOUSE_RELEASE
