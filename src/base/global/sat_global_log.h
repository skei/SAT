#pragma once

/*
    TODO:
    - log file name prefix: binary/plugin name
    - header: system (cpu, kernel, glibc version, gpu, opengl version, paths (desktop, home, binary)
*/

#include "base/sat_base.h"
#include "base/global/sat_global_base.h"


// #include "sat.h"
// #include "base/sat_print.h"
// #include "base/system/sat_cpu.h"
#include "base/system/sat_file.h"
#include "base/system/sat_paths.h"
#include "base/system/sat_time.h"
#include "plugin/format/clap/sat_clap.h"

#ifdef SAT_LOG_THREAD
    #ifdef SAT_LINUX
        #include <sys/syscall.h>
        #include <sys/unistd.h>
        #define gettid() syscall(SYS_gettid)
    #endif
    #ifdef SAT_WIN32
        #include <processthreadsapi.h>
    #endif
#endif

#ifdef SAT_LOG_TIME
    #include <sys/time.h> // gettimeofday
#endif

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_GlobalLog
{
    public:
        SAT_GlobalLog();
        ~SAT_GlobalLog();
        void activate(SAT_GlobalBase* AGlobal);
        void deactivate(SAT_GlobalBase* AGlobal);
    public:
        #ifdef SAT_LOG_TIME
            void time_start();
            double time_elapsed();
        #endif // log time
        void print_header();
        void print_string(char* str, bool prefix=true);
        void print(const char* format, ...);
        //  void print_if(bool cond, const char* format, ...);
        void dprint(const char* format, ...);
    private:
        bool            MIsActivated    = false;
        SAT_GlobalBase* MGlobal         = nullptr;
        SAT_File        MFile                               = {};
        char            MLogfileName[SAT_MAX_PATH_LENGTH]   = {0};
        char            MLogfilePath[SAT_MAX_PATH_LENGTH]   = {0};
        bool            MEnabled                            = false;
        char            MFilename[SAT_MAX_PATH_LENGTH*2]    = {0};
        char            MTempBuffer[SAT_MAX_PATH_LENGTH]    = {0};
     // char            MHomePath[SAT_MAX_PATH_LENGTH]      = {0};
        #ifdef SAT_LOG_TIME
            double      MStartTime                          = 0.0;
        #endif

};

//----------------------------------------------------------------------
//
// implementation
//
//----------------------------------------------------------------------

SAT_GlobalLog::SAT_GlobalLog()
{
}

SAT_GlobalLog::~SAT_GlobalLog()
{
}

void SAT_GlobalLog::activate(SAT_GlobalBase* AGlobal)
{
    if (!MIsActivated)
    {
        MGlobal = AGlobal;
        //APrint->print("SAT_Log.initialize\n");
        //MPrint = APrint;
        #ifdef SAT_INCLUDE_LOG
            #ifdef SAT_LOG_TIME
                time_start();
            #endif
            MEnabled = false;
            //MLogfileName = AName;
            SAT_File file = {};
            //SAT_GetDesktopPath(MDesktopPath);
            SAT_GetHomePath(MLogfilePath);
            strcat(MLogfilePath,SAT_LOG_DIRECTORY);
            if (file.direxists(MLogfilePath))
            {
                SAT_CurrentTime time = {0};
                SAT_GetLocalTime(&time);
                sprintf(MLogfileName,"%02i-%s-%04i_%02i-%02i-%02i",time.day, SAT_MONTH_NAMES[time.month - 1], time.year, time.hour, time.minutes, time.seconds);
                #ifdef SAT_LINUX
                    sprintf(MFilename,"%s/%s",MLogfilePath,MLogfileName);
                #else
                    sprintf(MFilename,"%s\\%s",MLogfilePath,MLogfileName);
                #endif
                // APrint->print("logfile: %s path: %s\n",MLogfileName,MFilename);
                MFile.open(MFilename,SAT_FILE_WRITE_TEXT);
                if (!MFile.isOpen())
                {
                    // APrint->print("Log: couldn't open logfile '%s'\n",MFilename);
                }
                else
                {
                    MEnabled = true;
                    dprint("\n----------------------------------------------------------------------\n\n");
                    print_header();
                    dprint("\n----------\n\n");
                }
            }
            else
            {
                //APrint->print("Log: directory '%s' doesn't exist\n",MLogfilePath);
            }
        #else // nSAT_INCLUDE_LOG
        #endif
        MIsActivated = true;
    }
}

void SAT_GlobalLog::deactivate(SAT_GlobalBase* AGlobal)
{
    if (MIsActivated)
    {
        #ifdef SAT_INCLUDE_LOG
            if (MEnabled) {
                dprint("\n\n");
                MFile.close();
            }
        #else
        #endif
        MGlobal = nullptr;
        MIsActivated = false;
    }
}

//------------------------------
// time
//------------------------------

#ifdef SAT_LOG_TIME

    void SAT_GlobalLog::time_start()
    {
        struct timeval time;
        gettimeofday(&time,NULL);
        MStartTime = (double)time.tv_sec + (double)time.tv_usec * .000001;
    }

    double SAT_GlobalLog::time_elapsed()
    {
        struct timeval time;
        gettimeofday(&time,NULL);
        double currenttime = (double)time.tv_sec + (double)time.tv_usec * .000001;
        double elapsed = currenttime - MStartTime;
        return elapsed;
    }

#endif // SAT_LOG_TIME time

//------------------------------
//
//------------------------------

void SAT_GlobalLog::print_header()
{
    if (MEnabled)
    {
        SAT_CurrentTime time = {0};
        SAT_GetLocalTime(&time);
        const char* gui = "";
//        const char* painter = "";
        // SAT_GUI_NNE
        // SAT_GUI_SOFTWARE
        // SAT_GUI_WAYLAND
        // SAT_GUI_WIN32
        // SAT_GUI_X11
        #ifdef SAT_GUI_NONE
            gui = "NONE";
        #endif
        #ifdef SAT_GUI_SOFTWARE
            gui = "SOFTWARE";
        #endif
        #ifdef SAT_GUI_WAYLAND
            gui = "WAYLAND";
        #endif
        #ifdef SAT_GUI_WIN32
            gui = "WIN32";
        #endif
        #ifdef SAT_GUI_X11
            gui = "X11";
        #endif
        dprint("Time: %02i.%02i.%04i (%02i.%02i.%02i)\n",time.day,time.month,time.year,time.hour,time.minutes,time.seconds);
        #ifdef SAT_DEBUG
            dprint("Build: Debug\n");
        #else
            dprint("Build: Release\n");
        #endif
        #ifdef SAT_LINUX
            dprint("OS: Linux\n");
        #endif
        #ifdef SAT_WIN32
            dprint("OS: Windows\n");
        #endif
        dprint("GUI: %s\n",gui);
        char buffer[SAT_MAX_PATH_LENGTH];
        dprint("Home path: %s\n",SAT_GetHomePath(buffer));
        dprint("Desktop path: %s\n",SAT_GetDesktopPath(buffer));
        dprint("Base filename: %s\n",SAT_GetBaseFilename(buffer));
        dprint("Base path: %s\n",SAT_GetBasePath(buffer));
        dprint("CLAP Version: %i.%i.%i\n",CLAP_VERSION_MAJOR,CLAP_VERSION_MINOR,CLAP_VERSION_REVISION);
        //dprint("Host name: %s\n",SAT_GetHostName(buffer));
        #ifdef SAT_PLUGIN_DSSI
            dprint("Wrapper: DSSI\n");
        #endif
        #ifdef SAT_PLUGIN_EXE
            dprint("Wrapper: EXE\n");
        #endif
        #ifdef SAT_PLUGIN_LADSPA
            dprint("Wrapper: LADSPA\n");
        #endif
        #ifdef SAT_PLUGIN_LV2
            dprint("Wrapper: LV2\n");
        #endif
        #ifdef SAT_PLUGIN_VST2
            dprint("Wrapper: VST2\n");
        #endif
        #ifdef SAT_PLUGIN_VST3
            dprint("Wrapper: VST3\n");
        #endif
    } // enabled
}

//------------------------------
//
//------------------------------

//TODO: prefix, time..

//void operator () (const char* format, ...) {
//}

void SAT_GlobalLog::print_string(char* str, bool prefix)
{
    if (MEnabled)
    {
        if (prefix)
        {
            #if defined(SAT_LOG_TIME) || defined (SAT_LOG_THREAD)
                char temp[1024];
                temp[0] = 0;
                #ifdef SAT_LINUX
                    uint32_t thread_id = gettid();
                #endif
                #ifdef SAT_WIN32
                    uint32_t thread_id = GetCurrentThreadId();
                #endif
                #ifdef SAT_LOG_TIME
                    double time = time_elapsed();
                    #ifdef SAT_LOG_THREAD // time & thread_id
                        sprintf(temp,"[%.6f,%08x] %s",time,thread_id,str);
                    #else // time 
                        sprintf(temp,"[%.6f] %s",time,str);
                    #endif
                #else // thread_id
                    sprintf(temp,"[%08x] %s",thread_id,str);
                #endif
                uint32_t len = strlen(temp);
                MFile.write(temp,len);
            #else // none
                //sprintf(temp,"%s",str);
                uint32_t len = strlen(str);
                MFile.write(str,len);
            #endif
        }
        else
        { //!prefix
            uint32_t len = strlen(str);
            MFile.write(str,len);
        }
        MFile.flush();
    }
}

void SAT_GlobalLog::print(const char* format, ...)
{
    if (MEnabled)
    {
        if (MFile.isOpen())
        {
            va_list args;
            va_start(args,format);
            vsprintf(MTempBuffer,format,args);
            va_end(args);
            print_string(MTempBuffer);
        }
    }
}

/*
    void print_if(bool cond, const char* format, ...)
    {
        if (MEnabled)
        {
            if (cond && MFile.isOpen())
            {
                va_list args;
                va_start(args,format);
                vsprintf(MTempBuffer,format,args);
                va_end(args);
                print_string(MTempBuffer);
            }
        }
    }
*/

void SAT_GlobalLog::dprint(const char* format, ...)
{
    if (MEnabled)
    {
        if (MFile.isOpen())
        {
            va_list args;
            va_start(args,format);
            vsprintf(MTempBuffer,format,args);
            va_end(args);
            print_string(MTempBuffer,false);
        }
    }
}
