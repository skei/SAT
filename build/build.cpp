/*
    ../build/compile -i ../build/build.cpp -o ../bin/build -O linux -F exe -G native -d
    ../build/compile -i ../build/build.cpp -o ../bin/build.clap -O linux -F clap -G native -d
    nc -U -l -k /tmp/sat.socket
*/

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

// ALWAYS include this as the first thing!
// so, maybe we should put it here, so we never forget it!
// #include "base/sat.h"

//----------------------------------------------------------------------
//
// build / test
//
//----------------------------------------------------------------------

//#include "test/test_debug.h"
//#include "test/test_gfx.h"
//#include "test/test_plugin.h"
#include "test/test_widget.h"
//#include "test/test_window.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------
