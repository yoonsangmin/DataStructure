#include <iostream>
#include "LinkedList.h"

#include <forward_list>

class Test
{
public:
    Test(int data)
        : data(data)
    {

    }

    friend std::ostream& operator<<(std::ostream& os, const Test& other)
    {
        return os << "TestData: " << other.data;
    }
    
    bool operator>=(const Test& other)
    {
        return data >= other.data;
    }

    bool operator==(const Test& other)
    {
        return data == other.data;
    }

public:
    int data;
};

int main()
{
    std::forward_list<int> forwardList;
    forwardList.push_front(10);
    forwardList.insert_after(forwardList.begin(), 20);

    LinkedList<int> list;

    list.Insert(10);
    list.Insert(20);
    list.Insert(30);
    list.Insert(40);
    list.Insert(50);

    std::cout << "----- 리스트 데이터 출력 -----\n";
    list.Print();

    list.Delete(30);
    list.Delete(50);

    list.Delete(60);
    list.Delete(5);

    std::cout << "----- 데이터 삭제 후 출력 -----\n";
    list.Print();

    //LinkedList<Test> list;

    //list.Insert(10);
    //list.Insert(20);
    //list.Insert(30);
    //list.Insert(40);
    //list.Insert(50);

    //std::cout << "----- 리스트 데이터 출력 -----\n";
    //list.Print();

    //list.Delete(30);
    //list.Delete(50);

    //list.Delete(60);
    //list.Delete(5);

    //std::cout << "----- 데이터 삭제 후 출력 -----\n";
    //list.Print();

    std::cin.get();
}