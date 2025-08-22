#pragma once

/*
    initially based on:
        http://www.codeproject.com/Articles/149879/Associative-Array-in-C
        by Arnav Mukhopadhyay
*/

#include "base/sat_base.h"
#include "base/type/sat_array.h"
#include "base/util/sat_strutils.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

template <class T>
class SAT_Dictionary
{
    public:

        // SAT_Dictionary()
        // ~SAT_Dictionary()

    public:

        uint32_t    size();
        bool        hasItem(const char* name);
        T           getItem(uint32_t index);
        T           getItem(const char* name);
        int32_t     getItemIndex(const char* name);
        const char* getItemName(uint32_t index);
        T&          operator [] (uint32_t index);
        T&          operator [] (const char* name);
        bool        addItem(const char* name, T value);
        bool        removeItem(uint32_t index);
        bool        removeItem(const char* name);

    private:

        struct SAT_DictionaryItem
        {
            const char* name;
            T           value;
        };

        SAT_Array<SAT_DictionaryItem> MItems;

};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

// template <class T>
// SAT_Dictionary<T>::SAT_Dictionary()
// {
// }

// template <class T>
// SAT_Dictionary<T>::~SAT_Dictionary()
// {
// }

template <class T>
uint32_t SAT_Dictionary<T>::size()
{
    return MItems.size();
}

template <class T>
bool SAT_Dictionary<T>::hasItem(const char* name)
{
    for (uint32_t i=0; i<size(); i++)
    {
        //if (strcmp(name,MItems[i].name) == 0) return true;
        if (SAT_IsEqual(name,MItems[i].name)) return true;
    }
    return false;
}

template <class T>
T SAT_Dictionary<T>::getItem(uint32_t index)
{
    return MItems[index].value;
}

template <class T>
T SAT_Dictionary<T>::getItem(const char* name)
{
    for (uint32_t i=0; i<size(); i++)
    {
        //if (strcmp(name,MItems[i].name) == 0) return MItems[i].value;
        if (SAT_IsEqual(name,MItems[i].name)) return MItems[i].value;
    }
    return nullptr;
}

template <class T>
int32_t SAT_Dictionary<T>::getItemIndex(const char* name)
{
    for (uint32_t i=0; i<size(); i++)
    {
        //if (strcmp(name,MItems[i].name) == 0) return i;
        if (SAT_IsEqual(name,MItems[i].name)) return i;
    }
    return -1;
}

template <class T>
const char* SAT_Dictionary<T>::getItemName(uint32_t index)
{
    return MItems[index].name;
}

template <class T>
T& SAT_Dictionary<T>::operator [] (uint32_t index)
{
    return MItems[index].value;
}

template <class T>
T& SAT_Dictionary<T>::operator [] (const char* name)
{
    for (uint32_t i=0; i<size(); i++)
    {
        //if (strcmp(name,MItems[i].name) == 0) return MItems[i].value;
        if (SAT_IsEqual(name,MItems[i].name)) return MItems[i].value;
    }
    uint32_t idx = size();
    SAT_DictionaryItem d;
    d.name = name;
    d.value = 0;  // ???
    MItems.append(d);
    return MItems[idx].value;
}

template <class T>
bool SAT_Dictionary<T>::addItem(const char* name, T value)
{
    if (hasItem(name)) return false;
    SAT_DictionaryItem d;
    d.name = name;
    d.value = value;
    MItems.append(d);
    return true;
}

template <class T>
bool SAT_Dictionary<T>::removeItem(uint32_t index)
{
    MItems.remove(index);
    return true;
}

template <class T>
bool SAT_Dictionary<T>::removeItem(const char* name)
{
    for (uint32_t i=0; i<size(); i++)
    {
        //if (strcmp(name,MItems[i].name) == 0)
        if (SAT_IsEqual(name,MItems[i].name))
        {
            MItems.remove(i);
            return true;
        }
    }
    return false;
}
