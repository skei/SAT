#pragma once

#include <stdlib.h>

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

typedef std::atomic<bool>   sat_atomic_bool_t;
typedef float               sat_color_t;
typedef double              sat_coord_t;
typedef double              sat_param_t;
typedef float               sat_sample_t;

#include "base/type/sat_array.h"
#include "base/type/sat_color.h"
#include "base/type/sat_dictionary.h"
#include "base/type/sat_point.h"
#include "base/type/sat_queue.h"
#include "base/type/sat_rect.h"
