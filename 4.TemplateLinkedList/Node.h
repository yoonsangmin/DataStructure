﻿#pragma once

#include <iostream>

// 링키드 리스트의 요소인 노드 클래스.
template<typename T>
class Node
{
    // 예외.
    template<typename T>
    friend class LinkedList;

public:
    // std::cout 에 쉽게 출력할 수 있도록 오버로딩.
    friend std::ostream& operator<<(std::ostream& os, const Node<T>& node)
    {
        os << "Data: " << node.data;
        return os;
    };

    // 생성자.
    Node()
        : data()
    {
    }
    Node(T data)
        : data(data)
    {
    }

private:
    // 데이터 필드.
    T data;

    // 링크 필드.
    Node<T>* next = nullptr;
};