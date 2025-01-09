#pragma once

#include "Node.h"

// 노드를 사용해 자료를 저장하는 링크드 리스트.
template<typename T>
class LinkedList
{
public:
    // 오류가 발생했을 때 실행할 함수를 저장할 함수 포인터 변수.
    using ListEmptyErrorEvent = void (*)();

    //// 비교 함수 타입 선언.
    //using Comparer = bool (*)(T& left, T& right);

    LinkedList()
        : first(new Node<T>()),last(new Node<T>())
    {
        // 시작할 때는 first와 last가 서로를 가리키도록 설정.
        first->next = last;
        last->previous = first;
    }

    LinkedList(ListEmptyErrorEvent erroHandler)
        : LinkedList<T>()
    {
        errorEvent = erroHandler;
    }

    ~LinkedList()
    {
        // TODO: 삭제 함수 구현 후 호출 해야 함.
        if (count > 0)
        {
            Clear();
        }

        delete first;
        delete last;
    }

    // 리스트 안에 모든 노드를 제거하는 함수.
    void Clear()
    {
        // 리스트가 비었으면 오류 발생.
        if (count == 0)
        {
            RaiseEmptyErrorEvent();
            return;
        }

        // 첫 노드에서 부터 시작.
        Node<T>* current = first->next;

        // 모든 노드 삭제.
        while (current != nullptr && current != last)
        {
            // 삭제 로직.
            Node<T>* next = current->next;
            delete current;
            current = next;
        }

        // 남은 데이터 정리.
        count = 0;
        first->next = last;
        last->previous = first;
    }

    // 리스트가 비었을 때 오류 이벤트를 발생시키는 함수.
    // Invoke(간접 호출).
    void RaiseEmptyErrorEvent()
    {
        // 함수 포인터가 설정되었으면 해당 함수 호출.
        if (errorEvent != nullptr)
        {
            errorEvent();
        }
    }

    // 헤드에 추가하는 함수.
    void AddToFirst(const T& data)
    {
        // 새 노드 생성.
        Node<T>* newNode = new Node<T>(data);

        // 새 노드의 다음 노드를 first->next 노드로 설정.
        // 새 노드의 이전 노드를 first로 설정.
        Node<T>* next = first->next;
        newNode->next = next;
        newNode->previous = first;

        // 첫 노드(first->next)를 새 노드로 설정.
        // 기존 첫 노드의 이전 노드를 새 노드로 설정.
        first->next = newNode;
        next->previous = newNode;

        // 저정된 노드 수 증가 처리.
        ++count;
    }

    // 맨 뒤에 삽입하는 함수.
    void AddToLast(const T& data)
    {
        // 새 노드 생성.
        Node<T>* newNode = new Node<T>(data);

        Node<T>* previous = last->previous;
        newNode->previous = previous;
        newNode->next = last;

        previous->next = newNode;
        last->previous = newNode;

        // 저정된 노드 수 증가 처리.
        ++count;
    }

    // 데이터를 지정해 검색 후 삭제하는 함수.
    void Delete(const T& data/*, Comparer comparer = nullptr*/)
    {
        // 예외 처리.
        if (count == 0)
        {
            RaiseEmptyErrorEvent();
            return;
        }

        //// 수도 코드.
        //Node<T>* current;
        ////if (current->data == data)
        //if (comparer(current->data, data))
        //{

        //}
         
        // 삭제할 노드 검색.
        Node<T>* deleteNode = first->next;
        while (deleteNode != nullptr && deleteNode != last)
        {
            // 찾았으면 루프 종료.
            if (deleteNode->data == data)
            {
                break;
            }

            // 다음 노드로 이동 (검색 계속 진행).
            deleteNode = deleteNode->next;
        }

        // 예외 처리.
        if (deleteNode == nullptr || deleteNode == last)
        {
            RaiseEmptyErrorEvent();
            return;
        }

        // 삭제.
        deleteNode->previous->next = deleteNode->next;
        deleteNode->next->previous = deleteNode->previous;

        delete deleteNode;
        --count;
    }

    //// 아웃 파라미터, bool 반환
    //bool<T>* Find(const T& data, Node<T>* outNode)
    //{
    //}

    Node<T>* Find(const T& data)
    {
        Node<T>* current = first->next;

        while (current != nullptr && current != last)
        {
            if (current->data == data)
            {
                return current;
            }

            current = current.next;
        }

        return nullptr;
    }

    //Node<T>* FindReverse(const T& data)
    //{
    //}

    // 저장된 요소 출력 함수.
    void Print()
    {
        Node<T>* current = first->next;
        while (current != nullptr && current != last)
        {
            std::cout << "Data: " << current->data << "\n";
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

    // 마지막 노드.
    Node<T>* last = nullptr;

    // 저장된 자료 수를 나타내는 변수.
    int count = 0;

    // 함수 포인터 변수.
    ListEmptyErrorEvent errorEvent = nullptr;
};