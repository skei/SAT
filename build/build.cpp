/*
    ../build/compile -i ../build/build.cpp -o ../bin/build -S linux -F exe -G native -d
    ../build/compile -i ../build/build.cpp -o ../bin/build.clap -S linux -F clap -G native -d
    nc -U -l -k /tmp/sat.socket
*/

//----------------------------------------------------------------------

#include "base/sat.h"

#include "plugin/sat_entry.h"
#include "plugin/sat_plugin.h"
#include "plugin/sat_processor.h"

#include "plugin/format/clap/sat_clap_extensions.h"
#include "plugin/format/clap/sat_clap_host_proxy.h"
#include "plugin/format/clap/sat_clap_plugin_proxy.h"

#include "gui/sat_window.h"
#include "gui/sat_painter.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class myPlugin
: public SAT_Plugin
{
    private:
        SAT_ClapGui*    MGui;
        SAT_ClapParams  MParams;
    public:
        myPlugin(const clap_plugin_descriptor_t* ADescriptor, const clap_host_t* AHost);
        virtual ~myPlugin();
    public:
        uint32_t params_count() final;
};

//------------------------------
//
//------------------------------

myPlugin::myPlugin(const clap_plugin_descriptor_t* ADescriptor, const clap_host_t* AHost)
: SAT_Plugin(ADescriptor,AHost)
{
    registerExtension( new SAT_ClapGui() );
    registerStaticExtension(&MParams);
}

myPlugin::~myPlugin()
{
}

uint32_t myPlugin::params_count()
{
    return 0;
}


//----------

const clap_plugin_descriptor_t myDescriptor = 
{
    .clap_version   = CLAP_VERSION,
    .id             = "myPlugin",
    .name           = "plugin",
    .vendor         = SAT_VENDOR,
    .url            = SAT_URL,
    .manual_url     = "",
    .support_url    = "",
    .version        = SAT_VERSION,
    .description    = "my cool plugin",
    .features       = (const char*[]){ CLAP_PLUGIN_FEATURE_AUDIO_EFFECT, nullptr }
};

//----------

SAT_SIMPLE_PLUGIN_ENTRY(myDescriptor,myPlugin)

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class myWindow
: public SAT_Window
{
    public:
        myWindow(uint32_t AWidth, uint32_t AHeight, intptr_t AParent=0);
        virtual ~myWindow();
        void on_window_paint(int32_t AXpos, int32_t AYpos, uint32_t AWidth, uint32_t AHeight) final;
    private:
        SAT_Painter* MPainter = nullptr;
};

//------------------------------
//
//------------------------------

myWindow::myWindow(uint32_t AWidth, uint32_t AHeight, intptr_t AParent)
: SAT_Window(AWidth,AHeight,AParent)
{
    MPainter = new SAT_Painter(this,this);
}

myWindow::~myWindow()
{
    delete MPainter;
}

void myWindow::on_window_paint(int32_t AXpos, int32_t AYpos, uint32_t AWidth, uint32_t AHeight)
{
    MPainter->setFillColor(SAT_DarkRed);
    MPainter->fillRect(AXpos,AYpos,AWidth,AHeight);
    MPainter->setTextColor(SAT_White);
    MPainter->drawText(SAT_Rect(AXpos,AYpos,AWidth,AHeight),"Hello world",SAT_TEXT_ALIGN_CENTER);
}

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

void test_debug()
{

    // SAT_Assert(1==0);

    // SAT_PrintCallStack;

    // --- memtrace ---

    // uint8_t* test = (uint8_t*)malloc(1024);
    // uint8_t* test2 = new uint8_t[512];
    // SAT_PRINT("test %p test2 %p\n",test,test2);
    // free(test);
    // delete [] test2;
    // //delete test; // mismatch
    // //free(test2); // mismatch

    // --- observer ---

    // const char* teststr = "string 123\0";
    // double      testdbl = 3.14;
    // void*       testptr = 0; // &teststr;
    // // SAT_PRINT("teststr %s testdlb %.3f testptr %p\n",teststr,testdbl,testptr);
    // SAT_Observe(SAT_OBSERVE_DOUBLE, &testdbl,"test - dbl");
    // SAT_Observe(SAT_OBSERVE_STR,    &teststr,"test - str");
    // SAT_Observe(SAT_OBSERVE_PTR,    &testptr,"test - ptr");
    // SAT_PrintObservers;

    // --- crash handler ---

    // int* ptr = nullptr;
    // int a = *ptr;
    // SAT_PRINT("a = %i\n",a);

}

//----------

int main(void)
{
    //clap_entry.init("./");

    SAT_PRINT("OS: %s\n",SAT.SYSTEM->getOSString());
    // SAT_DPRINT("hello world!\n");
    // SAT_TRACE;

    // SAT_LOG("WARNING! no window available");
    // SAT_PRINT("width %i height %i depth %i\n",SAT.GUI->getScreenWidth(),SAT.GUI->getScreenHeight(),SAT.GUI->getScreenDepth());

    // test_debug();

    myPlugin* plugin = new myPlugin(nullptr,nullptr);
    delete plugin;

    myWindow* window = new myWindow(640,480);
    window->show();
    window->eventLoop();
    window->hide();
    delete window;

    //clap_entry.deinit();
    return 0;
}

