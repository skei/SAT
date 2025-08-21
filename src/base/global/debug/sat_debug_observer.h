#pragma once

#include "base/sat_base.h"
#include "base/global/sat_global_base.h"
#include "base/global/sat_global_print.h"

// #ifdef SAT_DEBUG_OBSERVER
//     #include "base/debug/sat_debug_observer.h"
// #endif
// #include <signal.h>

struct SAT_Observable
{
    uint32_t    type;
    const void* ptr;
    const char* desc;
};

typedef SAT_Array<SAT_Observable> SAT_Observables;


//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_Observer
{
    public:

        SAT_Observer();
        ~SAT_Observer();
        void activate(SAT_GlobalBase* AGlobal);
        void deactivate(SAT_GlobalBase* AGlobal);

    public:

        void            observe(uint32_t AType, const void* APtr, const char* ADesc);
        void            unobserve(void* APtr);
        void            print_observers();
        uint32_t        getNumObservers();
        SAT_Observable* getObserver(uint32_t AIndex);

    private:

        bool                MIsActivated    = false;
        SAT_GlobalBase*     MGlobal         = nullptr;

    private:

        #ifdef SAT_DEBUG_OBSERVER
            SAT_Observables MObservables = {};
        #endif

};

//----------------------------------------------------------------------
//
// implementation
//
//----------------------------------------------------------------------

SAT_Observer::SAT_Observer()
{
}

SAT_Observer::~SAT_Observer()
{
}

void SAT_Observer::activate(SAT_GlobalBase* AGlobal)
{
    if (!MIsActivated)
    {
        MGlobal = AGlobal;
        MIsActivated = true;
    }
}

void SAT_Observer::deactivate(SAT_GlobalBase* AGlobal)
{
    if (MIsActivated)
    {
        MGlobal = nullptr;
        MIsActivated = false;
    }
}

//------------------------------
// observer
//------------------------------

/*
    type = SAT_OBSERVE_* (for correct printing)
    ptr  = pointer to variable being observed
    desc = name of variable (for printing)

    TODO: check if observed variable already exist before adding
*/

void SAT_Observer::observe(uint32_t AType, const void* APtr, const char* ADesc)
{
    #ifdef SAT_DEBUG_OBSERVER
        //MObservables[MNumObservables].type = AType;
        //MObservables[MNumObservables].ptr  = APtr;
        //MObservables[MNumObservables].desc = ADesc;
        SAT_Observable obs;
        obs.type = AType;
        obs.ptr  = APtr;
        obs.desc = ADesc;
        MObservables.append(obs);
    #endif
}

/*
    ptr = ptr to variable being observer
*/
  
void SAT_Observer::unobserve(void* APtr)
{
    #ifdef SAT_DEBUG_OBSERVER
        for (uint32_t i=0; i<MObservables.size(); i++)
        {
            if (MObservables[i].ptr == APtr)
            {
                MObservables.remove(i);
                return;
            }
        }
    #endif
}
  
void SAT_Observer::print_observers()
{
    #ifdef SAT_DEBUG_OBSERVER
        if (MObservables.size() > 0)
        {
            SAT_GLOBAL_DPRINT("Observed:\n");
            for (uint32_t i=0; i<MObservables.size(); i++)
            {
                // const void* ptr = nullptr;
                // intptr_t iptr = 0;
                switch (MObservables[i].type)
                {
                    case SAT_OBSERVE_FLOAT:
                    {
                        SAT_GLOBAL_DPRINT("  %i. %s = %.3f\n",i,MObservables[i].desc,*(float*)MObservables[i].ptr);
                        break;
                    }
                    case SAT_OBSERVE_DOUBLE:
                    {
                        SAT_GLOBAL_DPRINT("  %i. %s = %.3f\n",i,MObservables[i].desc,*(double*)MObservables[i].ptr);
                        break;
                    }
                    case SAT_OBSERVE_INT32:
                    {
                        SAT_GLOBAL_DPRINT("  %i. %s = %i\n",i,MObservables[i].desc,*(int32_t*)MObservables[i].ptr);
                        break;
                    }
                    case SAT_OBSERVE_UINT32:
                    {
                        SAT_GLOBAL_DPRINT("  %i. %s = %i\n",i,MObservables[i].desc,*(uint32_t*)MObservables[i].ptr);
                        break;
                    }
                    case SAT_OBSERVE_CHAR:
                    {
                        SAT_GLOBAL_DPRINT("  %i. %s = %c\n",i,MObservables[i].desc,*(char*)MObservables[i].ptr);
                        break;
                    }
                    case SAT_OBSERVE_PTR:
                    {
                        SAT_GLOBAL_DPRINT("  %i. %s = %p\n",i,MObservables[i].desc,*(void**)MObservables[i].ptr);
                        break;
                    }
                    case SAT_OBSERVE_STR:
                    {
                        SAT_GLOBAL_DPRINT("  %i. %s = %s\n",i,MObservables[i].desc,*(const char**)MObservables[i].ptr);
                        break;
                    }
                    default:
                    {
                        SAT_GLOBAL_DPRINT("  %i. %s = [unknown type]\n",i,MObservables[i].desc);
                        break;
                    }

                }
            }
            // print("\n");
        }
    #endif
}
  
uint32_t SAT_Observer::getNumObservers()
{
    #ifdef SAT_DEBUG_OBSERVER
        return MObservables.size();
    #else
        return 0;
    #endif
}
  
SAT_Observable* SAT_Observer::getObserver(uint32_t AIndex)
{
    #ifdef SAT_DEBUG_OBSERVER
        return &MObservables[AIndex];
    #else
        return nullptr;
    #endif
}
