#ifndef _TMULTISTACK_
#define _TMULTISTACK_

#include <iostream>
#include <math.h>

#include "Stack.h"

using namespace std;

template <class T>
class MultiStack
{
protected:
    int length; // data size
    T* data;
    int stackCount;
    TStack<T>* stacks;

    T** oldData;

    void StackRelocation(int i);

public:
    MultiStack(int size = 1, int _stackCount=1);
    MultiStack(MultiStack<T>& _v);
    ~MultiStack();

    MultiStack<T>& operator =(MultiStack<T>& _v);

    void Push(T d, int i);
    T Get(int i);

    bool IsEmpty(int i) const;
    bool IsFull(int i) const;

    template <class T1>
    friend ostream& operator<< (ostream& ostr, const MultiStack<T1>& A);
    template <class T1>
    friend istream& operator >> (istream& istr, MultiStack<T1>& A);

    int Length();

    void Resize(int size = 1, int _stackCount = 1);
};

template <class T1>
ostream& operator<< (ostream& ostr, const MultiStack<T1>& A) {
    for (int i = 0; i < A.stackCount; i++) {
        ostr << (A.stacks[i]) << " ";
    }
    return ostr;
}

template <class T1>
istream& operator >> (istream& istr, MultiStack<T1>& A) {
    int stCount=0;
    istr >> stCount;
    int size = 0;
    istr >> size;
    A.Resize(size, stCount);
    for (int i = 0; i < stCount; i++)
    {
        istr >> A.stacks[i];
    }
    return istr;
}

template<class T>
inline void MultiStack<T>::StackRelocation(int index)
{
    int freeSize=0;
    for (int i = 0; i < stackCount; i++)
    {
        freeSize += stacks[i].Length() - stacks[i].GetCount();
    }

    if (freeSize == 0)
        throw new exception;

    int count = int(floor(double(freeSize) / stackCount));
    int* sizes = new int[this->stackCount];

    for (int i = 0; i < (stackCount - 1); i++)
    {
        sizes[i] = stacks[i].GetCount() + count;
    }
    int c = stacks[stackCount - 1].GetCount();
    sizes[this->stackCount - 1] = c +(freeSize -  (count * (this->stackCount - 1)));

    T** newData = new T * [stackCount];

    int k = 0;
    for (int i = 0; i < stackCount; i++)
    {
        newData[i] = &(data[k]);
        k = k + sizes[i];
    }

    for (int i = 0; i < stackCount; i++)
    {
        if (newData[i] == oldData[i])
        {
            stacks[i].SetData(newData[i], sizes[i], stacks[i].GetCount());
        }
        else if (newData[i] < oldData[i])
        {
            for (int j = 0; j < stacks[i].GetCount(); j++)
            {
                newData[i][j] = oldData[i][j];
            }
            stacks[i].SetData(newData[i], sizes[i], stacks[i].GetCount());
        }
        else if (newData[i] > oldData[i])
        {
            int k = i;
            for (; k < stackCount; k++)
            {
                if (newData[k] > oldData[k])
                    continue;
                else
                    break;
            }
            k--;

            for (int s = k; s <= i; s--)
            {
                for (int j = stacks[s].GetCount()-1; j >=0; j--)
                {
                    newData[s][j] = oldData[s][j];
                }
                stacks[s].SetData(newData[s], sizes[s], stacks[s].GetCount());

            }
        }
    }
    
    T** buf = oldData;
    oldData = newData;
    delete[] buf;
    delete[] sizes;
}

template<class T>
inline MultiStack<T>::MultiStack(int size, int _stackCount)
{
    if ((size > 0)&&(_stackCount>0))
    {
        this->length = size;
        this->stackCount = _stackCount;

        data = new T[length];
        for (int i = 0; i < length; i++)
           data[i] = 0;

        int count = int(floor(double(size) / stackCount));
        int* sizes = new int[this->stackCount];

        for (int i=0;i<(stackCount-1);i++)
        {
            sizes[i] = count;
        }

        sizes[stackCount - 1] = size - (count * (stackCount-1));

        oldData = new T * [stackCount];
        this->stacks = new TStack<T>[stackCount];
        int k = 0;

        for (int i = 0; i < stackCount; i++)
        {
            this->stacks[i].SetData(&(data[k]), sizes[i], 0);
            this->oldData[i] = &(data[k]);
            k = k + sizes[i];
        }
    }
    else
        throw new exception;
}

template <class T>
MultiStack<T>::MultiStack(MultiStack<T>& _v)
{
    length = _v.length;
    stackCount = _v.stackCount;

    data = new T[length];
    for (int i = 0; i < length; i++)
        data[i] = _v.data[i];

    stacks = new TStack<T>[stackCount];
    for (int i = 0; i < stackCount; i++)
    {
        stacks[i] = _v.stacks[i];
    }
    oldData = _v.oldData;
}

template <class T>
MultiStack<T>::~MultiStack()
{
    length = 0;
    stackCount = 0;

    if (data != NULL)
    {
        delete[] data;
        data = 0;
    }

    if(stacks!=NULL)
        delete[] stacks;

}

template <class T>
MultiStack<T>& MultiStack<T>::operator =(MultiStack<T>& _v)
{
    if (this == &_v)
        return *this;

    this->length = _v.length;

    if(data!=NULL)
        delete[] data;
    if(stacks!=NULL)
        delete[] stacks;

    this->data = new T[length];
    for (int i = 0; i < length; i++)
        data[i] = _v.data[i];

    stacks = new TStack<T>[stackCount];
    for (int i = 0; i < stackCount; i++)
    {
        stacks[i] = _v.stacks[i];
    }

    return *this;
}

template<class T>
inline void MultiStack<T>::Push(T d, int i)
{
    if (i < 0 || i >= stackCount)
        throw new exception;

    if (stacks[i].IsFull())
    {
        StackRelocation(i);
    }

    stacks[i].Push(d);
}

template<class T>
inline T MultiStack<T>::Get(int i)
{
    if (i < 0 || i >= stackCount)
        throw new exception;

    if (stacks[i].IsEmpty())
        throw new exception;

    T d = stacks[i].Get();
    return d;
}

template<class T>
inline bool MultiStack<T>::IsEmpty(int i) const
{
    if (i < 0 || i >= stackCount)
        throw new exception;

    return stacks[i].IsEmpty();
}

template<class T>
inline bool MultiStack<T>::IsFull(int i) const
{
    if (i < 0 || i >= stackCount)
        throw new exception;

    return stacks[i].IsFull();
}

template <class T>
int MultiStack<T>::Length()
{
    return length;
}

template<class T>
inline void MultiStack<T>::Resize(int size, int _stackCount)
{
    stacks[_stackCount].Resize(size);
}

#endif