#pragma once

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

template <typename T, int SIZE>
class SAT_Stack
{
    public:
        SAT_Stack();
        ~SAT_Stack();
    public:
        void    setNullItem(T AItem);
        void    reset();
        int     getSize();
        int     getNumItems();
        bool    isEmpty();
        T*      getTop();
        void    push(T AItem);
        T       pop();
        void    dup();
        void    dup2();
        void    drop();
    private:
        T       MStack[SIZE]    = {0};
        int32_t MStackTop       = 0;
        T       MNullItem       = (T)0;
};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

template <typename T, int SIZE>
SAT_Stack<T,SIZE>::SAT_Stack()
{
}

template <typename T, int SIZE>
SAT_Stack<T,SIZE>::~SAT_Stack()
{
}

//------------------------------
//
//------------------------------

template <typename T, int SIZE>
void SAT_Stack<T,SIZE>::setNullItem(T AItem)
{
    MNullItem = AItem;
}

template <typename T, int SIZE>
void SAT_Stack<T,SIZE>::reset()
{
    MStackTop = 0;
}

template <typename T, int SIZE>
int SAT_Stack<T,SIZE>::getSize()
{
    return SIZE;
}

template <typename T, int SIZE>
int SAT_Stack<T,SIZE>::getNumItems()
{
    return MStackTop;
}

template <typename T, int SIZE>
bool SAT_Stack<T,SIZE>::isEmpty()
{
    //return (MStackTop > 0);
    return (MStackTop == 0);
}

template <typename T, int SIZE>
T* SAT_Stack<T,SIZE>::getTop(void)
{
    return &MStack[MStackTop-1];
}

template <typename T, int SIZE>
void SAT_Stack<T,SIZE>::push(T AItem)
{
    if (MStackTop < SIZE)
    {
        MStack[MStackTop++] = AItem;
    }
    else
    {
        //printf("Error! Stack overflow\n");
    }
}

template <typename T, int SIZE>
T SAT_Stack<T,SIZE>::pop()
{
    if (MStackTop > 0)
    {
        return MStack[--MStackTop];
    }
    else
    {
        //printf("Error! Stack empty\n");
        return MNullItem;
    }
}

template <typename T, int SIZE>
void SAT_Stack<T,SIZE>::dup(void)
{
    MStack[MStackTop] = MStack[MStackTop-1];
    MStackTop++;
}

template <typename T, int SIZE>
void SAT_Stack<T,SIZE>::dup2(void)
{
    MStack[MStackTop] = MStack[MStackTop-2];
    MStackTop++;
}

template <typename T, int SIZE>
void SAT_Stack<T,SIZE>::drop(void)
{
    MStackTop--;
}

