#include <iostream>
#include "Queue.h"

int main()
{
    Queue queue;
    for (int ix = 0; ix < 10; ++ix)
    {
        queue.Enqueue(ix + 10);
    }

    // 큐 출력.
    queue.Print();

    std::cout << "===큐 요소 제거===\n";
    int value;
    
    queue.Dequeue(value);
    queue.Dequeue(value);
    queue.Dequeue(value);
    queue.Print();
}