#include <iostream>
#include "Stack.h"
#include <stdlib.h>
#include <time.h>

// 최소/최대 값 사이의 랜덤을 반환하는 함수.
int RandomRange(int min, int max)
{
    // 차이.
    int diff = (max - min) + 1;
    return ((rand() * diff) / RAND_MAX + 1) + min;
}

int main()
{
    // 난수 발생기 설정.
    srand((unsigned int)time(nullptr));

    // 스택 객체.
    Stack<float, 3> stack;

    if (stack.Push((float)RandomRange(10, 3000)))
    {
        std::cout << "첫 번째 게임 종료 - 경험치 140\n";
    }

    if (stack.Push((float)RandomRange(10, 3000)))
    {
        std::cout << "두 번째 게임 종료 - 경험치 180\n";
    }

    if (stack.Push((float)RandomRange(10, 3000)))
    {
        std::cout << "세 번째 게임 종료 - 경험치 200\n";
    }

    if (stack.Push((float)RandomRange(10, 3000)))
    {
        std::cout << "네 번째 게임 종료 - 경험치 300\n";
    }

    // 출력.
    // 스택이 팝을 하면 개수가 줄기 때문에 따로 저장
    //int count = stack.Count();
    //for (int ix = 0; ix < count; ix++)
    //{
    //    float value;
    //    if (stack.Pop(value))
    //    {
    //        std::cout << "현재 경험치: " << value << "\n";
    //    }
    //}

    while (!stack.IsEmpty())
    {
        float value;
        if (stack.Pop(value))
        {
            std::cout << "현재 경험치: " << value << "\n";
        }
    }

    std::cin.get();
}