#include "LinkedList.h"

#ifdef _DEBUG
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define new new
#endif

LinkedList::LinkedList()
{
}

LinkedList::~LinkedList()
{
    if (head != nullptr)
    {
        Node* current = head;
        Node* deleteNode = nullptr;

        while (current != nullptr)
        {
            deleteNode = current;
            current = current->next;

            delete deleteNode;
        }
    }
}

void LinkedList::AddToHead(int data)
{
    // 새 노드 생성.
    Node* newNode = new Node(data);
    
    // #1 - 현재 헤드가 없는 경우.
    if (head == nullptr)
    {
        // 헤드 노드를 newNode로 설정.
        head = newNode;
    }

    // #2 - 헤드가 있는 경우.
    else
    {
        // 새 노드의 다음 노드를 기존 헤드 노드로 설정.
        newNode->next = head;

        // 헤드 노드를 새 노드로 교체.
        head = newNode;
    }

    // 저정된 노드 수 증가 처리.
    ++count;
}

void LinkedList::Insert(int data)
{
    // 새 노드 생성.
    Node* newNode = new Node(data);

    // 삽입할 위치 찾기.

    // #1 - 헤드가 비어있는 경우.
    if (head == nullptr)
    {
        head = newNode;
    }
    else
    {
        // 노드 포인터 2개를 사용해 검색.
        Node* current = head;
        Node* trail = nullptr;

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
        if (current == head)
        {
            newNode->next = head;
            head = newNode;
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

void LinkedList::Delete(int data)
{
    // 삭제할 노드 찾기.
    // 예외 처리.
    if (head == nullptr)
    {
        std::cout << "리스트가 비어있어 삭제가 불가능 합니다.\n";
        return;
    }
    
    // 검색 진행.
    Node* current = head;
    Node* trail = nullptr;

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
    if (current == head)
    {
        // 헤드 노드 교체.
        head = head->next;
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

void LinkedList::Print()
{
    Node* current = head;
    while (current != nullptr)
    {
        std::cout << *current << "\n";
        current = current->next;
    }
}

int LinkedList::Count() const
{
    return count;
}
