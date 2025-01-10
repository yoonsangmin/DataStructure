#include "HashTable.h"
#include <iostream>

// 해시 함수.
int GenerateHash(std::string keyString)
{
    // 전달 받은 문자열의 길이 확인.
    //int length = (int)strlen(keyString);

    // 생성할 키.
    int hash = 0;
    for (int ix = 0; ix < (int)keyString.size(); ++ix)
    {
        // 해시 함수 핵심 로직.
        hash = hash * 31 + keyString[ix];
    }
    
    //return hash < 0 ? -hash: hash;
    return std::abs(hash);
}

void HashTable::Add(const std::string& key, const std::string& value)
{
    // 인덱스 구하기.
    int bucketIndex = GenerateHash(key) % bucketCount;

    // 저장할 위치에 있는 컨테이너 가져오기.
    auto& position = table[bucketIndex];

    // 해시 테이블은 중복을 허용하지 않음.
    // 검색.
    for (int ix = 0; ix < (int)position.size(); ++ix)
    {
        // 키 비교.
        //if (position[ix].key == key) // 주소를 비교하게 됨
        //if (strcmp(position[ix].key, key) == 0)
        if (position[ix].key == key)
        {
            std::cout << "이미 같은 키가 저장되어 있어 삽입 실패.\n";
            return;
        }
    }

    // 데이터 삽입.
    position.push_back(Entry(key, value));
}

void HashTable::Delete(const std::string& key)
{
    // 인덱스 구하기.
    int bucketIndex = GenerateHash(key) % bucketCount;
    // 삭제할 위치에 있는 컨테이너 가져오기.
    auto& position = table[bucketIndex];

    // 검색.
    for (int ix = 0; ix < (int)position.size(); ++ix)
    {
        // 키 비교.
        //if (strcmp(position[ix].key, key) == 0)
        if (position[ix].key == key)
        {
            position.erase(position.begin() + ix);
            std::cout << "키: " << key << " 항목을 삭제.\n";
            return;
        }
    }

    // 검색 실패.
    std::cout << "삭제할 항목을 찾지 못했습니다.\n";
}

bool HashTable::Find(const std::string& key, Entry& outValue)
{
    // 인덱스 구하기.
    int bucketIndex = GenerateHash(key) % bucketCount;
    // 검색할 위치에 있는 컨테이너 가져오기.
    auto& position = table[bucketIndex];

    // 예외 처리.
    if (position.size() == 0)
    {
        std::cout << "해당 키로 항목을 찾지 못했습니다.\n";
        return false;
    }

    // 검색.
    for (int ix = 0; ix < (int)position.size(); ++ix)
    {
        // 키 비교.
        //if (strcmp(position[ix].key, key) == 0)
        if (position[ix].key == key)
        {
            // 검색에 성공했으면, 값 출력.
            outValue = position[ix];
            return true;
        }
    }

    std::cout << "해당 키로 항목을 찾지 못했습니다.\n";
    return false;
}

void HashTable::Print()
{
    for (int ix = 0; ix < bucketCount; ++ix)
    {
        // 건너뛰기.
        if (table[ix].size() == 0)
        {
            continue;
        }

        // 출력.
        for (auto& entry : table[ix])
        {
            std::cout << "키: " << entry.key << " 값: " << entry.value << "\n";
        }
    }
}
