#pragma once

// included in sat_debug_memtrace
// sat_print not defined yet..

//----------------------------------------------------------------------

//#include <vector>
//#define SAT_Array std::vector

#include "base/sat_base.h"
#include "base/util/sat_intmath.h" // SAT_NextPowerOfTwo
//#include "base/sat_stdlib.h"

//----------------------------------------------------------------------

template<class _T>
class SAT_Array
{
    public:
        SAT_Array();
        SAT_Array(const SAT_Array& AArray);
        ~SAT_Array();
    public:
        uint32_t        size(void);
        void*           buffer(void);
        _T&             item(const uint32_t AIndex);
        uint32_t        bufferSize(void);
        void            resize(const uint32_t ASize);
        _T&             getItem(const uint32_t AIndex);
        _T&             operator [] (const uint32_t AIndex);
        SAT_Array<_T>&  operator = (const SAT_Array<_T> &AArray);
     // int32_t         findItem(_T& AItem);
        void            clear(bool AErase=false);
        void            insert(const _T& AItem, uint32_t APos);
        void            insert(SAT_Array<_T>& AArray, uint32_t APos);
        void            insertHead(const _T& AItem);
        void            insertTail(const _T& AItem);
        void            remove(const uint32_t APos);
        void            remove(const uint32_t APos, uint32_t ANum);
        void            remove(const _T& AItem);
        void            removeHead(void);
        void            removeTail(void);
        int32_t         find(const _T& AItem);
        bool            hasItem(const _T& AItem);
        void            append(_T& AItem);
        void            push_back(_T& AItem);
        _T&             head(void);
        _T&             tail(void);
        void            push(_T AItem);
        _T              pop(void);
    private:
        void            freeItems(void);
     // void            deleteItems(void);
        void            clearBuffer(bool AErase=false);
        void            resizeBuffer(const uint32_t ABufferSize);
        void            growBuffer(const uint32_t ANum);
        void            shrinkBuffer(const uint32_t ANum);
    private:
        _T*             MBuffer     = nullptr;
        uint32_t	    MBufferSize = 0;
        uint32_t	    MSize       = 0;
        const uint32_t  MTypeSize   = sizeof(_T);
};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

template<class _T>
SAT_Array<_T>::SAT_Array()
{
    // MBuffer     = nullptr;
    // MBufferSize = 0;
    // MSize       = 0;
}

template<class _T>
SAT_Array<_T>::SAT_Array(const SAT_Array& AArray)
{
    MBuffer = (_T*)malloc(MTypeSize*AArray.MBufferSize);
    MBufferSize = AArray.MBufferSize;
    MSize = AArray.MSize;
    memcpy(MBuffer, AArray.MBuffer, MTypeSize*AArray.MBufferSize);
}

template<class _T>
SAT_Array<_T>::~SAT_Array()
{
    if (MBuffer)
    {
        free(MBuffer);
    }
}

template<class _T>
uint32_t  SAT_Array<_T>::size(void)
{
    return MSize;
}

template<class _T>
void* SAT_Array<_T>::buffer(void)
{
    return MBuffer;
}

template<class _T>
_T& SAT_Array<_T>::item(const uint32_t AIndex)
{
    return MBuffer[AIndex];
}

template<class _T>
uint32_t  SAT_Array<_T>::bufferSize(void)
{
    return MBufferSize;
}

template<class _T>
void SAT_Array<_T>::resize(const uint32_t ASize)
{
    resizeBuffer(ASize);
}

template<class _T>
_T& SAT_Array<_T>::getItem(const uint32_t AIndex)
{
    return MBuffer[AIndex];
}

template<class _T>
_T& SAT_Array<_T>::operator [] (const uint32_t AIndex)
{
    return MBuffer[AIndex];
}

template<class _T>
SAT_Array<_T>& SAT_Array<_T>::operator = (const SAT_Array<_T> &AArray)
{
    if (this == &AArray) return *this;
    // if (AArray.MSize == 0) clear();
    // setSize(AArray.MSize);
    memcpy(MBuffer, AArray.MBuffer, MTypeSize*AArray.MSize);
    return *this;
}

template<class _T>
void SAT_Array<_T>::freeItems(void)
{
    for (uint32_t i=0; i<MSize; i++) free( MBuffer[i] );
}

// template<class _T>
// void SAT_Array<_T>::deleteItems(void)
// {
//     for (uint32_t i=0; i<MSize; i++) delete MBuffer[i];
// }

template<class _T>
void SAT_Array<_T>::clearBuffer(bool AErase)
{
    if (AErase)
    {
        if (MBuffer) free(MBuffer);
        MBuffer = nullptr;
        MBufferSize = 0;
    }
    MSize = 0;
}

template<class _T>
void SAT_Array<_T>::resizeBuffer(const uint32_t ABufferSize)
{
    uint32_t size = SAT_NextPowerOfTwo(ABufferSize);
    if (size != MBufferSize)
    {
        MBuffer = (_T*)realloc(MBuffer, MTypeSize*size);
        MBufferSize = size;
        //MSize = size;
        //if (MSize > MBufferSize) MSize = MBufferSize;
    }
}

//----------

template<class _T>
void SAT_Array<_T>::growBuffer(const uint32_t ANum)
{
    uint32_t newsize = MSize + ANum;
    resizeBuffer(newsize);
}

template<class _T>
void SAT_Array<_T>::shrinkBuffer(const uint32_t ANum)
{
    uint32_t newsize = MSize - ANum;
    resizeBuffer(newsize);
}

// template<class _T>
// int32_t SAT_Array<_T>::findItem(_T& AItem)
// {
//     for (uint32_t i=0; i<MSize; i++)
//     {
//         if (MBuffer[i] == AItem) return i;
//     }
//     return -1;
// }

template<class _T>
void SAT_Array<_T>::clear(bool AErase)
{
    clearBuffer(AErase);
}

template<class _T>
void SAT_Array<_T>::insert(const _T& AItem, uint32_t APos)
{
    growBuffer(1);
    memmove( &MBuffer[APos+1], &MBuffer[APos], (MSize-APos) * MTypeSize);
    MBuffer[APos] = AItem;
    MSize++;
}

template<class _T>
void SAT_Array<_T>::insert(SAT_Array<_T>& AArray, uint32_t APos)
{
    uint32_t num = AArray.size();
    growBuffer(num);
    memmove( &MBuffer[APos+num], &MBuffer[APos], (MSize-APos) * MTypeSize);
    memcpy( &MBuffer[APos], AArray.buffer(), num * MTypeSize );
    MSize += num;
}

template<class _T>
void SAT_Array<_T>::insertHead(const _T& AItem)
{
    insert(AItem,0);
}

template<class _T>
void SAT_Array<_T>::insertTail(const _T& AItem)
{
    growBuffer(1);
    MBuffer[MSize] = AItem;
    MSize++;
}

template<class _T>
void SAT_Array<_T>::remove(const uint32_t APos)
{
    memmove( &MBuffer[APos], &MBuffer[APos+1], (MSize-APos-1) * MTypeSize);
    shrinkBuffer(1);
    MSize--;
}

template<class _T>
void SAT_Array<_T>::remove(const uint32_t APos, uint32_t ANum)
{
    //moveBufferItems(APos+ANum,APos,ANum);
    memmove( &MBuffer[APos], &MBuffer[APos+ANum], (MSize-APos-ANum) * MTypeSize);
    shrinkBuffer(ANum);
    MSize -= ANum;
}

template<class _T>
void SAT_Array<_T>::remove(const _T& AItem)
{
    int32_t index = find(AItem);
    if (index >= 0) remove(index);
}

template<class _T>
void SAT_Array<_T>::removeHead(void)
{
    remove(0);
}

template<class _T>
void SAT_Array<_T>::removeTail(void)
{
    MSize--;
    shrinkBuffer(1);
}

template<class _T>
int32_t SAT_Array<_T>::find(const _T& AItem)
{
    for (uint32_t i=0; i<MSize; i++)
    {
        if (MBuffer[i] == AItem) return i;
    }
    return -1;
}

template<class _T>
bool SAT_Array<_T>::hasItem(const _T& AItem)
{
    if (find(AItem) >= 0) return true;
    return false;
}

template<class _T>
void SAT_Array<_T>::append(_T& AItem)
{
    insertTail(AItem);
}

template<class _T>
void SAT_Array<_T>::push_back(_T& AItem)
{
    insertTail(AItem);
}

template<class _T>
_T& SAT_Array<_T>::head(void)
{
    return MBuffer[0];
}

template<class _T>
_T& SAT_Array<_T>::tail(void)
{
    return MBuffer[MSize-1];
}

template<class _T>
void SAT_Array<_T>::push(_T AItem)
{
    insertTail(AItem);
}

template<class _T>
_T SAT_Array<_T>::pop(void)
{
    removeTail();
    return MBuffer[MSize];
}

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

typedef SAT_Array<char>         SAT_CharArray;
typedef SAT_Array<char*>        SAT_CharPtrArray;
typedef SAT_Array<const char>   SAT_ConstCharArray;
typedef SAT_Array<const char*>  SAT_ConstCharPtrArray;
typedef SAT_Array<void*>        SAT_PtrArray;
typedef SAT_Array<void**>       SAT_PtrPtrArray;
typedef SAT_Array<float*>       SAT_FloatPtrArray;
typedef SAT_Array<float>        SAT_FloatArray;
typedef SAT_Array<bool>         SAT_BoolArray;
typedef SAT_Array<int32_t>      SAT_Int32Array;
typedef SAT_Array<uint32_t>     SAT_Uint32Array;

// typedef SAT_Array<SAT_String>   SAT_StringArray;
// typedef SAT_Array<SAT_Sample>   SAT_SampleArray;
// typedef SAT_Array<SAT_Sample*>  SAT_SamplePtrArray;
