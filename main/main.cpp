#include <iostream>
#include "Stack.h"
#include "MultiStack.h"


int main()
{
    TMultiStack<int> b(9, 3);
    b.Push(11, 0);
    b.Push(12, 1);
    b.Push(12, 1);
    b.Push(12, 1);

    b.Push(15, 1);
    
    std::cout<<b<<"\n";
    return 0;
}
