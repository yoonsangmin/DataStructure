#include <iostream>
#include "HashTable.h"

int main()
{
    // 해쉬 테이블 객체.
    HashTable table;

    table.Add("Ronnie", "010-123456");
    table.Add("Ronnie", "010-123456");
    table.Add("Taejun", "010-123456");
    table.Add("Baker", "010-123456");
    table.Add("Ijun", "010-123456");
    
    table.Print();

    Pair<std::string, std::string> value;
    if (table.Find("Backer", value))
    {
        std::cout << "키 Backer 항목을 찾았습니다.\n";
    }
    else
    {
        std::cout << "키 Backer 항목을 못 찾았습니다.\n";
    }

    table.Delete("Ronnie");

    std::cout << "삭제 후 출력----\n";
    table.Print();

    std::cin.get();
}