/*
    ../build/compile -i ../build/build.cpp -o ../bin/build -S linux -F exe -G native -d
    ../build/compile -i ../build/build.cpp -o ../bin/build.clap -S linux -F clap -G native -d
    nc -U -l -k /tmp/sat.socket
*/

//----------------------------------------------------------------------

#include "base/sat.h"
#include "plugin/sat_plugin.h"
#include "gui/sat_widget_window.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

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

class myPlugin
: public SAT_Plugin 
{
    private:
        SAT_ClapParams  MParams;
    public:
        myPlugin(const clap_plugin_descriptor_t* ADescriptor, const clap_host_t* AHost);
        virtual ~myPlugin();
    public:
        uint32_t params_count() final;
};

myPlugin::myPlugin(const clap_plugin_descriptor_t* ADescriptor, const clap_host_t* AHost)
: SAT_Plugin(ADescriptor,AHost)
{
    registerStaticExtension(&MParams);
    registerExtension( new SAT_ClapGui() );
}

myPlugin::~myPlugin()
{
}

uint32_t myPlugin::params_count()
{
    return 0;
}

#ifndef SAT_NO_ENTRY
    #include "plugin/sat_entry.h"
    SAT_REGISTER_SINGLE_PLUGIN(myDescriptor,myPlugin)
#endif

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class myWindow
: public SAT_WidgetWindow
{
    public:
        myWindow(uint32_t AWidth, uint32_t AHeight, intptr_t AParent=0);
        virtual ~myWindow();
        void on_window_paint(SAT_PaintContext* AContext, bool ABuffered=false) override;
};

myWindow::myWindow(uint32_t AWidth, uint32_t AHeight, intptr_t AParent)
: SAT_WidgetWindow(AWidth,AHeight,AParent)
{
}

myWindow::~myWindow()
{
}

void myWindow::on_window_paint(SAT_PaintContext* AContext, bool ABuffered)
{

    //if (AResized) { SAT_PRINT("resized\n"); }
    SAT_Painter* painter = AContext->painter;
    SAT_Rect rect = AContext->update_rect;
    painter->setFillColor(SAT_DarkRed);
    painter->fillRect(rect.x,rect.y,rect.w,rect.h);
    painter->setTextColor(SAT_White);
    painter->drawText(SAT_Rect(getWidth(),getHeight()),"Hello world",SAT_TEXT_ALIGN_CENTER);

    // handle widget system...
    SAT_WidgetWindow::on_window_paint(AContext);

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
    // const char* test_str = "string 123\0";
    // double      test_dbl = 3.14;
    // void*       test_ptr = 0; // &teststr;
    // // SAT_PRINT("teststr %s testdlb %.3f testptr %p\n",teststr,testdbl,testptr);
    // SAT_Observe(SAT_OBSERVE_DOUBLE, &test_dbl,"test_dbl");
    // SAT_Observe(SAT_OBSERVE_STR,    &test_str,"test_str");
    // SAT_Observe(SAT_OBSERVE_PTR,    &test_ptr,"test_ptr");
    // SAT_PrintObservers;

    // --- crash handler ---
    // int* ptr = nullptr;
    // int a = *ptr;
    // SAT_PRINT("a = %i\n",a);
}

int main(void)
{
    // test_debug();

    // SAT_PRINT("OS: %s\n",SAT.SYSTEM->getOSString());
    // SAT_DPRINT("hello world!\n");
    // SAT_TRACE;
    // SAT_LOG("WARNING! no window available");
    // SAT_PRINT("width %i height %i depth %i\n",SAT.GUI->getScreenWidth(),SAT.GUI->getScreenHeight(),SAT.GUI->getScreenDepth());

    //clap_entry.init("./");
    // myPlugin* plugin = new myPlugin(nullptr,nullptr);

    myWindow* window = new myWindow(640,480);
    window->show();
    window->eventLoop();
    window->hide();
    delete window;
    //clap_entry.deinit();
    // delete plugin;
    return 0;
}

