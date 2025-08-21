#pragma once

#include "base/sat_base.h"
#include "base/global/sat_global_base.h"

typedef bool (*SAT_TestFunc)();

struct SAT_TestItem {
    const char*   name;
    SAT_TestFunc  func;
};

typedef SAT_Array<SAT_TestItem> SAT_TestItems;

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_GlobalTest
{
    public:
        SAT_GlobalTest();
        ~SAT_GlobalTest();
        void    activate(SAT_GlobalBase* AGlobal);
        void    deactivate(SAT_GlobalBase* AGlobal);
    public:
        void    addTest(const char* AName, SAT_TestFunc AFunc);
        bool    runAllTests();
    private:
        bool                    MIsActivated    = false;
        SAT_GlobalBase*         MGlobal         = nullptr;
    private:
        #ifdef SAT_INCLUDE_TESTS
            SAT_TestItems       MTestItems      = {};
         // SAT_TestSections    MTestSections   = {};
        #endif
};

//----------------------------------------------------------------------
//
// implementation
//
//----------------------------------------------------------------------

SAT_GlobalTest::SAT_GlobalTest()
{
}

SAT_GlobalTest::~SAT_GlobalTest()
{
}

void SAT_GlobalTest::activate(SAT_GlobalBase* AGlobal)
{
    if (!MIsActivated)
    {
        MGlobal = AGlobal;
        // APrint->print("SAT_UnitTest.initialize\n");
        // #ifdef SAT_INCLUDE_TESTS
        //     runAllTests();
        // #endif
        MIsActivated = true;
    }
}

void SAT_GlobalTest::deactivate(SAT_GlobalBase* AGlobal)
{
    if (MIsActivated)
    {
        MGlobal = nullptr;
        MIsActivated = false;
    }
}

//------------------------------
//
//------------------------------

void SAT_GlobalTest::addTest(const char* AName, SAT_TestFunc AFunc)
{
    #if defined SAT_INCLUDE_TESTS
        SAT_TestItem test = { AName, AFunc };
        MTestItems.push_back(test);
    #endif
}

bool SAT_GlobalTest::runAllTests()
{
    #if defined SAT_INCLUDE_TESTS
        uint32_t num = MTestItems.size();
        SAT_GLOBAL_DPRINT("\n>> Running %i tests.\n",num);
        for (uint32_t i=0; i<num; i++) {
            const char*   test_name = MTestItems[i].name;
            SAT_TestFunc  test_func = MTestItems[i].func;
            SAT_GLOBAL_DPRINT(" - %i/%i : %s\n",i+1,num,test_name);
            bool success = test_func();
            if (!success)
            {
                SAT_GLOBAL_DPRINT(">> ERROR! Test %i (%s) failed.\n",i+1,test_name);
                #if defined(SAT_TESTS_EXIT_ON_FAILURE)
                exit(127);
                #endif
                return false;
            }
        }
        SAT_GLOBAL_DPRINT(">> All tests succeeded.\n\n");
    #endif
    return true;
}
