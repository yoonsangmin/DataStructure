#pragma once

#include <vector>
#include "Pair.h"
#include <string>

class HashTable
{
    // Alias(별칭) 선언.
    using Entry = Pair<std::string, std::string>;

public:
    // 명시적으로 기본 생성자로 선언.
    HashTable() = default;

    // 명시적으로 기본 소멸자로 선언.
    ~HashTable() = default;

    void Add(const std::string& key, const std::string& value);
    void Delete(const std::string& key);
    bool Find(const std::string& key, Entry& outValue);
    void Print();

private:
    // 내장 저장소의 크기 (소수(Prime Number)를 사용하는 것이 유리).
    static const int bucketCount = 19;
    //std::vector<Pair<const char*, const char*>> table[bucketCount];
    std::vector<Entry> table[bucketCount];
};