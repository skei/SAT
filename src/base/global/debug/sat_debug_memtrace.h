#pragma once

#include "base/sat_base.h"
#include "base/global/sat_global_base.h"
#include "base/global/sat_global_print.h"

struct SAT_MemTraceNode
{
    char      file[SAT_MAX_NAME_LENGTH] = {0};
    uint32_t  line                      = 0;
    uint32_t  flag                      = 0;
    void*     ptr                       = nullptr;
    uint32_t  size                      = 0;
};

typedef SAT_Array<SAT_MemTraceNode> SAT_MemTraceNodes;

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_MemTrace
{
    public:

        SAT_MemTrace();
        ~SAT_MemTrace();
        void activate(SAT_GlobalBase* AGlobal);
        void deactivate(SAT_GlobalBase* AGlobal);

    public:

        void*   malloc(unsigned int size, const char* file, const unsigned int line, const unsigned int flag = 0);
        void*   calloc(const unsigned int n, unsigned int size, const char* file, const unsigned int line);
        void*   realloc(void* ptr, const unsigned int size, const char* file, const unsigned int line);
        void    free(void* ptr, const char* file, const unsigned int line, const unsigned int flag = 0);
        void    print_memtrace();

    private:

        const char* strip_path(const char* buffer);

    private:

        bool                MIsActivated    = false;
        SAT_GlobalBase*     MGlobal         = nullptr;

        #ifdef SAT_DEBUG_MEMTRACE
            SAT_MemTraceNodes   MMemTraceNodes  = {};
        #endif

};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

SAT_MemTrace::SAT_MemTrace()
{
}

SAT_MemTrace::~SAT_MemTrace()
{
}

void SAT_MemTrace::activate(SAT_GlobalBase* AGlobal)
{
    if (!MIsActivated)
    {
        MGlobal = AGlobal;
        MIsActivated = true;
    }
}

void SAT_MemTrace::deactivate(SAT_GlobalBase* AGlobal)
{
    if (MIsActivated)
    {
        print_memtrace();
        MGlobal = nullptr;
        MIsActivated = false;
    }
}

//------------------------------
// memtrace
//------------------------------



void* SAT_MemTrace::malloc(unsigned int size, const char* file, const unsigned int line, const unsigned int flag)
{
    #ifdef SAT_DEBUG_MEMTRACE
        //print("malloc size %i file %s line %i\n",size,strip_path(file),line);
        void* p = ::malloc(size);
        SAT_MemTraceNode node;
        strcpy(node.file,strip_path(file));
        node.line = line;
        node.flag = flag;
        node.ptr  = p;
        node.size = size;
        MMemTraceNodes.append(node);
        return p;
    #else
        return ::malloc(size);
    #endif

}

void* SAT_MemTrace::calloc(const unsigned int n, unsigned int size, const char* file, const unsigned int line)
{
    #ifdef SAT_DEBUG_MEMTRACE
        //print("calloc\n");
        void* p = ::calloc(n,size);
        return p;
    #else
        return ::calloc(n,size);
    #endif
}

void* SAT_MemTrace::realloc(void* ptr, const unsigned int size, const char* file, const unsigned int line)
{
    #ifdef SAT_DEBUG_MEMTRACE
        //print("realloc\n");
        void* p = ::realloc(ptr,size);
        bool found = false;
        for (uint32_t i=0; i<MMemTraceNodes.size(); i++)
        {
            if (MMemTraceNodes[i].ptr == ptr)
            {
                found = true;
                MMemTraceNodes[i].ptr = p;
                MMemTraceNodes[i].size = size;
            }
        }
        if (!found)
        {
            //SAT_DPrint("Error! allocation %p not found (%s/%i)\n",ptr,strip_path(file),line);
        }
        return p;
    #else
        return ::realloc(ptr,size);
    #endif
}

//----------

// todo: error if not found

void SAT_MemTrace::free(void* ptr, const char* file, const unsigned int line, const unsigned int flag)
{
    #ifdef SAT_DEBUG_MEMTRACE
        //print("free ptr %p file %s line %i\n",ptr,strip_path(file),line);
        //bool found = false;
        // find node
        for (uint32_t i=0; i<MMemTraceNodes.size(); i++)
        {
            if (MMemTraceNodes[i].ptr == ptr) {
                // found = true;
                // check for malloc/fre mismatch
                if (MMemTraceNodes[i].flag != flag)
                {
                    if (MMemTraceNodes[i].flag == 0)
                    {
                        SAT_GLOBAL_DPRINT("  MemTrace - mismatch! malloc (%s:%i) delete (%s:%i)\n",MMemTraceNodes[i].file,MMemTraceNodes[i].line,strip_path(file),line);
                    }
                    else
                    {
                        SAT_GLOBAL_DPRINT("  MemTrace - mismatch! new (%s:%i) free (%s:%i)\n",MMemTraceNodes[i].file,MMemTraceNodes[i].line,strip_path(file),line);
                    }
                    // SAT_PrintCallStack();
                }
                // remove node
                MMemTraceNodes.remove(i);
            }
        }
        // not found
        // x11, nanovg prints a lot of these.. :-/
        // if (!found)
        // {
        //     SAT_GLOBAL_DPRINT("Error! allocation %p not found (%s/%i)\n",ptr,strip_path(file),line);
        //  }
        // delete memory
    #endif
    ::free(ptr);
}

// print() doesn't work?

void SAT_MemTrace::print_memtrace()
{
    #ifdef SAT_DEBUG_MEMTRACE
        if (MMemTraceNodes.size() > 0)
        {
            SAT_GLOBAL_DPRINT("Leaked memory:\n");
            for (uint32_t i=0; i<MMemTraceNodes.size(); i++)
            {
                char*     file  = MMemTraceNodes[i].file;
                uint32_t  line  = MMemTraceNodes[i].line;
                uint32_t  flag  = MMemTraceNodes[i].flag;
                void*     ptr   = MMemTraceNodes[i].ptr;
                uint32_t  size  = MMemTraceNodes[i].size;
                SAT_GLOBAL_DPRINT("  %i. %s:%i [%s]: %i bytes at %p\n",i,file,line,(flag==1)?"new":"malloc",size,ptr);
            }
        }
    #endif
}
    
const char* SAT_MemTrace::strip_path(const char* buffer)
{
    #ifdef SAT_DEBUG_MEMTRACE
        const char *slash;
        slash = strrchr(buffer,'/');
        if (slash) {
            return slash + 1;
        }
    #endif
    return buffer;
}
 

