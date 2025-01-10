#pragma once

template<typename KeyType, typename ValueType>
class Pair
{
public:
    Pair()
        : key(), value()
    {
    }

    Pair(KeyType key, ValueType value)
        : key(key), value(value)
    {
    }

    // 연산자 오버로딩.
    bool operator==(const Pair<KeyType, ValueType>& other)
    {
        return key == other.key && value == other.value; 
    }

    bool operator!=(const Pair<KeyType, ValueType>& other)
    {
        return key != other.key || value != other.value;
    }

public:
    // 키(Key).
    KeyType key;

    // 값(Value).
    ValueType value;
};