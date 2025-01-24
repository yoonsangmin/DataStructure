﻿#pragma once

#include "Node.h"

// 이진 탐색 트리 클래스.
template<typename T>
class BinarySearchTree
{
public:
    BinarySearchTree()
        : root(nullptr)
    {

    }

    ~BinarySearchTree()
    {
        // 재귀 삭제 함수 호출.
        Destroy();
    }

    // 검색.
    // 메소드 - 메시지(인터페이스/프로토콜).
    // 공개 / 감출지.
    bool SearchNode(const T& data)
    {
        // 루트부터 재귀적으로 검색.
        return SearchNodeRecursive(root, data);
    }

    // 삽입.
    // 규칙 ->
    // 0. 중복 허용하지 않음.
    // 1. 시작 -> 루트에서부터 비교 시작.
    // 1-1. 루트가 비어 있으면 새 노드를 루트로 지정.
    // 2. 새로 추가하는 값이 비교 노드보다 작으면 왼쪽 하위 트리로 비교를 이어간다.
    // 3. 새로 추가하는 값이 비교 노드보다 크면 오른쪽 하위 트리로 비교를 이어간다.
    bool InsertNode(const T& newData)
    {
        // 중복을 허용하지 않기 때문에 이미 있으면 실패.
        if (SearchNode(newData))
        {
            // 오류 메시지 출력.
            std::cout << "Error: 이미 중복된 값이 있어 추가 불가능.\n";
            return false;
        }

        // case1. 루트가 null.
        if (root == nullptr)
        {
            // 루트 생성 후 성공.
            root = new Node<T>(newData);
            return true;
        }

        // case2/3. 재귀 함수로 처리.
        root = InsertNodeRecursive(root, nullptr, newData);
        return true;
    }

    // 삭제.
    bool DeleteNode(const T& deleteData)
    {
        // 삭제할 노드가 없으면 실패.
        if (!SearchNode(deleteData))
        {
            return false;
        }

        // 재귀적으로 검색해 삭제하는 함수 호출.
        root = DeleteNodeRecursive(root, deleteData);
        return true;
    }

    // 순회 (중위 순회).
    void InorderTraverse(int depth = 0)
    {
        std::cout << "==== 중위 순회 시작 ==== \n";

        // 재귀 함수 호출.
        InorderTraverseRecursive(root, depth);
        
        std::cout << "==== 중위 순회 종료 ==== \n";
    }

private:

    // 모든 노드를 제거할 때 사용하는 함수.
    void Destroy()
    {
        // 루트 노드가 null이면 종료.
        if (root == nullptr)
        {
            return;
        }

        // 왼쪽 자손 > 오른쪽 자손 > 루트 순으로 제거.
        DestroyRecursive(root);
    }

    void DestroyRecursive(Node<T>* node)
    {
        // 재귀함수 종료 조건.
        if (node == nullptr)
        {
            return;
        }

        // 왼쪽 자손 / 오른쪽 자손 확인.
        Node<T>* left = node->left;
        Node<T>* right = node->right;

        // 자손이 없는 경우.
        if (left == nullptr && right == nullptr)
        {
            // 노드 삭제 후 함수 종료.
            delete node;
            return;
        }

        DestroyRecursive(left);
        DestroyRecursive(right);

        delete node;
    }

    // node: 현재 방문하려는 노드.
    // depth: 출력에 사용할 깊이 값.
    void InorderTraverseRecursive(Node<T>* node, int depth = 0)
    {
        // 종료 조건.
        if (node == nullptr)
        {
            // 깊이 출력.
            for (int ix = 0; ix < depth; ++ix)
            {
                // 두칸 빈칸.
                std::cout << "  ";
            }

            std::cout << "null\n";
            return;
        }

        // 왼쪽 하위 트리 방문.
        InorderTraverseRecursive(node->left, depth + 1);

        // 깊이 출력.
        for (int ix = 0; ix < depth; ++ix)
        {
            // 두칸 빈칸.
            std::cout << "  ";
        }

        // 부모 노드 방문.
        std::cout << node->data << "\n";

        // 오른쪽 하위 트리 방문.
        InorderTraverseRecursive(node->right, depth + 1);
    }

    // node가 현재 검색 대상 노드.
    // deleteData: 삭제할 데이터.
    Node<T>* DeleteNodeRecursive(Node<T>* node, const T& deleteData)
    {
        // 종료 조건.
        if (node == nullptr)
        {
            return nullptr;
        }

        // 작은 경우/큰 경우.
        if (node->data > deleteData)
        {
            node->left = DeleteNodeRecursive(node->left, deleteData);
        }
        else if (node->data < deleteData)
        {
            node->right = DeleteNodeRecursive(node->right, deleteData);
        }
        // 삭제할 노드를 찾은 경우.
        else
        {
            // 1. 자식이 없는 경우.
            if (node->left == nullptr && node->right == nullptr)
            {
                // 노드 삭제 후 종료.
                delete node;
                return nullptr;
            }

            // 2. 자식이 둘인 경우.
            if (node->left != nullptr && node->right != nullptr)
            {
                // 왼쪽에서 최대값 또는 오른쪽에서 최소값 노드 찾기.
                node->data = SearchMinValue(node->right)->data;

                // 위에서 구한 가장 작은 값을 가진 노드 삭제.
                node->right = DeleteNodeRecursive(node->right, node->data);
            }

            // 3. 자식이 하나인 경우.
            else
            {
                // 왼쪽 자식만 있는 경우.
                if (node->left != nullptr)
                {
                    // 임시 저장.
                    Node<T>* left = node->left;

                    // 삭제.
                    delete node;

                    // 왼쪽 자손 반환.
                    return left;
                }
                // 오른쪽 자식만 있는 경우.
                if (node->right != nullptr)
                {
                    // 임시 저장.
                    Node<T>* right = node->right;

                    // 삭제.
                    delete node;

                    // 왼쪽 자손 반환.
                    return right;
                }
            }
        }

        return node;
    }

    // 최소값을 검색하는 함수.
    // node: 검색을 시작하는 노드.
    Node<T>* SearchMinValue(Node<T>* node)
    {
        // assert.

        // 왼쪽 노드가 없을 때까지 찾은 후 반환.
        while (node->left != nullptr)
        {
            node = node->left;
        }

        return node;
    }


    // 재귀적으로 타겟 데이터를 검색하는 함수.
    bool SearchNodeRecursive(Node<T>* node, const T& data)
    {
        // 검색 실패.
        if (node == nullptr)
        {
            return false;
        }

        // 검색 성공.
        if (node->data == data)
        {
            return true;
        }

        // 작으면 왼쪽으로, 크면 오른쪽으로 검색.
        if (node->data > data)
        {
            return SearchNodeRecursive(node->left, data);
        }
        else
        {
            return SearchNodeRecursive(node->right, data);
        }
    }

    // node: 현재 비교하는 노드.
    // parent: node의 부모 노드.
    // newData: 삽입하려는 데이터.
    Node<T>* InsertNodeRecursive(Node<T>* node, Node<T>* parent, const T& newData)
    {
        // node가 null이면 추가.
        if (node == nullptr)
        {
            return new Node<T>(newData, parent);
        }

        // 작은 경우.
        if (node->data > newData)
        {
            node->left = InsertNodeRecursive(node->left, node, newData);
        }
        // 큰 경우.
        else
        {
            node->right = InsertNodeRecursive(node->right, node, newData);
        }

        return node;
    }

private:
    // 루트 노드.
    Node<T>* root;
};