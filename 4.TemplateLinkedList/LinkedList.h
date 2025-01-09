#pragma once

#include "Node.h"

// 노드를 사용해 자료를 저장하는 링크드 리스트.
template<typename T>
class LinkedList
{
public:
    LinkedList()
    {
        
    }

    ~LinkedList()
    {
        if (first != nullptr)
        {
            Node<T>* current = first;
            Node<T>* deleteNode = nullptr;

            while (current != nullptr)
            {
                deleteNode = current;
                current = current->next;

                delete deleteNode;
            }
        }
    }

    // 헤드에 추가하는 함수.
    void AddToHead(const T& data)
    {
        // 새 노드 생성.
        Node<T>* newNode = new Node<T>(data);

        // #1 - 현재 헤드가 없는 경우.
        if (first == nullptr)
        {
            // 헤드 노드를 newNode로 설정.
            first = newNode;
        }

        // #2 - 헤드가 있는 경우.
        else
        {
            // 새 노드의 다음 노드를 기존 헤드 노드로 설정.
            newNode->next = first;

            // 헤드 노드를 새 노드로 교체.
            first = newNode;
        }

        // 저정된 노드 수 증가 처리.
        ++count;
    }

    // 맨 뒤에 삽입하는 함수.
    void Insert(const T& data)
    {
        // 새 노드 생성.
        Node<T>* newNode = new Node<T>(data);

        // 삽입할 위치 찾기.

        // #1 - 헤드가 비어있는 경우.
        if (first == nullptr)
        {
            first = newNode;
        }
        else
        {
            // 노드 포인터 2개를 사용해 검색.
            Node<T>* current = first;
            Node<T>* trail = nullptr;

            // 위치 검색.
            while (current != nullptr)
            {
                // 값 비교.
                if (current->data >= data)
                {
                    break;
                }

                // 다음 노드로 이동.
                trail = current;
                current = current->next;
            }

            // 검색된 결과를 확인해서 처리.
            // 검색된 노드가 헤드 노드인 경우.
            if (current == first)
            {
                newNode->next = first;
                first = newNode;
            }
            // 검색된 노드가 중간 위치인 경우.
            else
            {
                newNode->next = current;
                trail->next = newNode;
            }
        }

        // 요소 수 증가 처리.
        ++count;
    }

    // 데이터를 지정해 검색 후 삭제하는 함수.
    void Delete(const T& data)
    {
        // 삭제할 노드 찾기.
        // 예외 처리.
        if (first == nullptr)
        {
            std::cout << "리스트가 비어있어 삭제가 불가능 합니다.\n";
            return;
        }

        // 검색 진행.
        Node<T>* current = first;
        Node<T>* trail = nullptr;

        while (current != nullptr)
        {
            // 값 비교.
            if (current->data == data)
            {
                break;
            }

            // 노드 이동.
            trail = current;
            current = current->next;
        }

        // 검색의 결과 2가지.
        // #1 못 찾은 경우.
        if (current == nullptr)
        {
            std::cout << "값 " << data << "를 찾지 못했습니다.\n";
            return;
        }

        // #2 찾은 경우.
        if (current == first)
        {
            // 헤드 노드 교체.
            first = first->next;
        }
        else
        {
            trail->next = current->next;
        }

        // 노드 삭제.
        delete current;

        // 저장된 요소의 수 감소 처리.
        --count;
    }

    // 저장된 요소 출력 함수.
    void Print()
    {
        Node<T>* current = first;
        while (current != nullptr)
        {
            std::cout << *current << "\n";
            // std::cout << "Data: " << current->data << "\n";
            current = current->next;
        }
    }

    // 저장된 요소의 수 반환 함수(Getter).
    /*inline*/ __forceinline int Count() const
    {
        return count;
    }

private:
    // 헤드(시작) 노드.
    Node<T>* first = nullptr;

    // 저장된 자료 수를 나타내는 변수.
    int count = 0;
};