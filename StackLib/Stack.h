#ifndef _TSTACK_
#define _TSTACK_

#include <iostream>

using namespace std;

template <class T>
class TStack
{
protected:
  int length;
  T* x;
  int top;
  bool f;
public:
  TStack(int size=1, bool _f=true);
  TStack(TStack<T>& _v);
  ~TStack();

  TStack<T>& operator =(TStack<T>& _v);

  void Push(T d);
  T Get();
  void SetData(T* _x, int _size, int _top);

  bool IsEmpty() const;
  bool IsFull() const;

  template <class T1>
  friend ostream& operator<< (ostream& ostr, const TStack<T1> &A);
  template <class T1>
  friend istream& operator >> (istream& istr, TStack<T1> &A);

  int Length();
  int GetCount();
  void Resize(int _size);
};

template <class T1>
ostream& operator<< (ostream& ostr, const TStack<T1> &A) {
  for (int i = 0; i < A.top; i++) {
    ostr << A.x[i] << " ";
  }
  return ostr;
}

template <class T1>
istream& operator >> (istream& istr, TStack<T1> &A) {
    int count;
    istr >> count;
  for (int i = 0; i < count; i++) 
  {
      T1 d;
      istr >> d;
      A.Push(d);
  }
  return istr;
}

template<class T>
inline TStack<T>::TStack(int size,bool _f)
{
    if (size > 0)
    {
        this->length = size;
        this->f = _f;
        if (f)
        {
            x = new T[length];
            for (int i = 0; i < length; i++)
                x[i] = 0;
        }
        this->top = 0;
    }
    else
        throw new exception;
}

template <class T>
TStack<T>::TStack(TStack<T>& _v)
{
  length = _v.length;
  top = _v.top;
  f = _v.f;
  if (f)
  {
      x = new T[length];
      for (int i = 0; i < length; i++)
          x[i] = _v.x[i];
  }
  else
  {
      x = _v.x;
  }
}

template <class T>
TStack<T>::~TStack()
{
  length = 0;
  if (f) 
  {
      if (x != NULL)
      {
          delete[] x;
      }
      x = NULL;
  }
 // x = 0;
}

template <class T>
TStack<T>& TStack<T>::operator =(TStack<T>& _v)
{
  if (this == &_v)
    return *this;

  this->length = _v.length;
  this->f = _v.f;
  if (f)
  {
      if(x!=NULL)
        delete[] x;
      this->x = new T[length];
      for (int i = 0; i < length; i++)
          x[i] = _v.x[i];
  }
  else
  {
      x = _v.x;
  }
  this->top = _v.top;
  return *this;
}

template<class T>
inline void TStack<T>::Push(T d)
{
    if (top >= length)
        throw new exception;

    x[top] = d;
    top++;
}

template<class T>
inline T TStack<T>::Get()
{
    if (top == 0)
        throw new exception;

    T d = x[top - 1];
    top--;
    return d;
}

template<class T>
inline void TStack<T>::SetData(T* _x, int _size, int _top)
{
    if (f)
        if(x!=NULL)
            delete[] x;

    this->length = _size;
    f = false;
    x = _x;
    top = _top;
}

template<class T>
inline bool TStack<T>::IsEmpty(void) const
{
    return top == 0;
}

template<class T>
inline bool TStack<T>::IsFull(void) const
{
    return (top >= length);
}

template <class T>
int TStack<T>::Length()
{
  return length;
 }

template <class T>
int TStack<T>::GetCount()
{
    return top;
}

template<class T>
inline void TStack<T>::Resize(int _size)
{
    if (_size <= 0)
        throw new exception;
    if (x == NULL)
    {
        delete[] x;
        x = new T[_size];
    }
    else
    {
        T* d = new T[_size];
        for (int i = 0; i < this->GetCount(); i++)
            d[i] = Get();
        delete[] x;
        x = new T[_size];
        for (int i = 0; i < 1; i++)
            x[i] = d[i];
    }
}


#endif