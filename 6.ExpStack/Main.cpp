#include <iostream>
#include "ExpStack.h"

int main()
{
    // 스택 객체.
    ExpStack stack;

    std::cout << "첫 번째 게임 종료 - 경험치 140\n";
    stack.Push(140.0f);

    std::cout << "두 번째 게임 종료 - 경험치 180\n";
    stack.Push(180.0f);

    std::cout << "세 번째 게임 종료 - 경험치 200\n";
    stack.Push(200.0f);

    std::cout << "네 번째 게임 종료 - 경험치 300\n";
    stack.Push(300.0f);

    // 출력.
    // 스택이 팝을 하면 개수가 줄기 때문에 따로 저장
    int count = stack.Count();
    for (int ix = 0; ix < count; ix++)
    {
        float value;
        if (stack.Pop(value))
        {
            std::cout << "현재 경험치: " << value << "\n";
        }
    }

    //while (!stack.IsEmpty())
    //{
    //    float value;
    //    if (stack.Pop(value))
    //    {
    //        std::cout << "현재 경험치: " << value << "\n";
    //    }
    //}

    std::cin.get();
}