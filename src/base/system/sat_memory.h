#pragma once

#include "base/sat_base.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

void*   SAT_Malloc_Aligned(uint32_t ASize, uint32_t AAlignment);
void    SAT_Free_Aligned(void *p);

#define SAT_ClearMem(x) memset(x,0,sizeof(x))

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

void* SAT_Malloc_Aligned(uint32_t ASize, uint32_t AAlignment)
{
    void* p1;   // original block
    void** p2;  // aligned block
    int offset = AAlignment - 1 + sizeof(void*);
    if ((p1 = (void*)malloc(ASize + offset)) == nullptr) return nullptr;
    p2 = (void**)(((size_t)(p1) + offset) & ~(AAlignment - 1));
    p2[-1] = p1;
    return p2;
}

void SAT_Free_Aligned(void *p)
{
    free(((void**)p)[-1];
}


