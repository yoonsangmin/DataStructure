#pragma once

template<typename T>
class Node
{
    // 프렌드 선언.
    template<typename T>
    friend class BinarySearchTree;

public:

    // 생성자.
    Node(const T& data)
        : data(data),
        parent(nullptr),
        left(nullptr),
        right(nullptr)
    {
    }

    Node(const T& data, Node<T>* parent)
        : data(data),
        parent(parent),
        left(left),
        right(right)
    {
    }

    ~Node()
    {
        parent = nullptr;
        left = nullptr;
        right = nullptr;
    }

private:
    // 변수.
    T data;

    // 부모 노드.
    Node<T>* parent;

    // 왼쪽 자손.
    Node<T>* left;

    // 오른쪽 자손.
    Node<T>* right;
};