#include <iostream>
#include <vector>       // 동적 배열.
#include <list>         // 연결 리스트.

// 수학 라이브러리. - DX에서
// Vector2 / Vector3 / Vector4.

// 반복자(Iterator) 클래스.
template<typename Vector>
class VectorIterator
{
public:
    // 타입 지정.
    using ValueType = typename Vector::ValueType;
    using PointerType = ValueType*;
    using ReferenceType = ValueType&;

public:
    VectorIterator(PointerType pointer)
        : pointer(pointer)
    {
    }

    // 포인터 증가 연산자 오버로딩.
    // 전위 증가 연산자.
    VectorIterator& operator++()
    {
        ++pointer;
        return *this;
    }

    // 포인터 후위 증가 연산자 오버로딩.
    VectorIterator& operator++(int)
    {
        VectorIterator iterator = *this;
        ++(*this);
        return *this;
    }

    // 전위 감소 연산자 오버로딩.
    VectorIterator& operator--()
    {
        --pointer;
        return *this;
    }

    // 포인터 후위 감소 연산자 오버로딩.
    VectorIterator& operator--(int)
    {
        VectorIterator iterator = *this;
        --(*this);
        return *this;
    }
    
    // 인덱스 연산자 오버로딩.
    ReferenceType& operator[](int index)
    {
        return *(pointer + index);
    }

    // 포인터 연산자 오버로딩.
    PointerType operator->()
    {
        return pointer;
    }

    // 값 반환 연산자.
    ReferenceType operator*()
    {
        return *pointer;
    }

    // 비교 연산자.
    bool operator==(const VectorIterator& other) const
    {
        return pointer == other.pointer;
    }

    bool operator!=(const VectorIterator& other) const
    {
        //return pointer != other.pointer;
        return !(*this == other);
    }

private:
    PointerType pointer;
};

// 동적 배열(리스트) 클래스.
// 템플릿.
template<typename T>
class List
{
public:
    using ValueType = T;
    using Iterator = VectorIterator<List<T>>;

    List()
    {
        // 초기 데이터 공간 설정.
        data = new T[capacity];
    }

    ~List()
    {
        // 포인터가 가리키는 힙 배열 변수 삭제.
        if (data != nullptr)
        {
            delete[] data;
        }
    }

    // 원소 추가.
    void PushBack(const T& value)
    {
        // 자료를 추가할 수 있는 충분한 공간이 있는지 확인.
        if (count == capacity)
        {
            ReAllocate(capacity * 2);
            // 초반에 너무 자주 재할당함
            // Reallocate(capcity + capacity / 2);
        }

        // 현재 배열의 마지막 요소에 전달받은 데이터 설정.
        data[count] = value;

        // 저장된 요소의 수 증가 처리.
        ++count;
    }

    // Move 추가.
    void PushBack(T&& value)
    {
        // 자료를 추가할 수 있는 충분한 공간이 있는지 확인.
        if (count == capacity)
        {
            ReAllocate(capacity * 2);
        }

        // 현재 배열의 마지막 요소에 전달받은 데이터 설정.
        data[count] = std::move(value);

        // 저장된 요소의 수 증가 처리.
        ++count;
    }

    // 접근 함수.
    T& At(int index)
    {
        // 예외 처리.
        if (index >= count)
        {
            // 디버그로 실행 시 break가 걸림
            __debugbreak();
        }

        return data[index];
    }

    // 접근 함수.
    const T& At(int index) const
    {
        // 예외 처리.
        if (index >= count)
        {
            __debugbreak();
        }

        return data[index];
    }

    // 연산자 오버로딩.
    T& operator[](int index)
    {
        // 예외 처리.
        if (index >= count)
        {
            __debugbreak();
        }

        return data[index];
    }

    // 연산자 오버로딩.
    const T& operator[](int index) const
    {
        // 예외 처리.
        if (index >= count)
        {
            __debugbreak();
        }

        return data[index];
    }

    // Iterator 관련 함수.
    Iterator begin()
    {
        return Iterator(data);
    }

    Iterator end()
    {
        return Iterator(data + count);
    }

    // Getter.
    // 요소 수 반환.
    int Count() const { return count; }
    
    // 저장 용량 반환.
    int Capacity() const { return capacity; }

    // 배열 주소 반환.
    T* Data() const { return data; }
    
private:
    // 저장할 공간이 부족할 때 공간을 늘리는 함수.
    void ReAllocate(int newCapacity)
    {
        // 1. 새로운 메모리 공간 할당(Allocate).
        // 2. 기존 데이터 복사.
        // 3. 기존 데이터 및 임시 데이터 삭제.
        
        T* newBlock = new T[newCapacity];
        memset(newBlock, 0, sizeof(T) * newCapacity);

        // 복사.
        //for (int ix = 0; ix < count; ++ix)
        //{
        //    // T가 클래스인 경우 - 복사 대입 연산자가 깊은 복사를 할 경우 성능이 너무 느림
        //    //newBlock[ix] = data[ix];
        //    // 이동 연산자로 얕은 복사
        //    newBlock[ix] = std::move(data[ix]);
        //}

        // 메모리 복사.
        memcpy(newBlock, data, sizeof(T) * count);

        delete[] data;
        data = newBlock;
        capacity = newCapacity;
    }

private:
    // 데이터 선언. (힙에 할당할 배열 변수).
    T* data = nullptr;

    // 용량.
    int capacity = 2;

    // 배열 원소의 수.
    int count = 0;
};

List<int*>* Function()
{
    List<int*>* llist = new List<int*>();

    int a = 10;
    int* aptr = &a;

    llist->PushBack(aptr);

    return llist;
}

void Function2()
{
    int* aptr;
    int* aptr2;
    {
        int a = 10;
        aptr = &a;
    }

    std::cout << *aptr << " ";
    std::cout << "\n";

    {
        int a = 50;
        aptr2 = &a;
    }

    std::cout << *aptr << " ";
    std::cout << "\n";

    //List<int*> llist;

    //{
    //    int a = 10;
    //    int* aptr = &a;

    //    //llist.PushBack(aptr);
    //    llist.PushBack(&a);
    //}
    //
    //std::cout << *llist.At(0) << " ";
    //std::cout << "\n";

    //{
    //    //std::vector<int> dummyData(1000, 42); // 스택 메모리를 차지함
    //    int b = 50;
    //}

    //std::cout << *llist.At(0) << " ";
    //std::cout << "\n";

    //List<int*> llist;

    //int i = 0;
    //while (i < 2)
    //{
    //    if (i == 0)
    //    {
    //        int a = 10;
    //        int* aptr = &a;

    //        //llist.PushBack(aptr);
    //        llist.PushBack(&a);
    //    }
    //    else
    //    {
    //        //std::vector<int> dummyData(1000, 42); // 스택 메모리를 차지함
    //        int b = 50;
    //    }
    //    ++i;
    //}
    //

    //std::cout << *llist.At(0) << " ";
    //std::cout << "\n";
}

int main()
{
    // 스택 메모리 연구
    //List<int*>* llist = Function();
    //// 스택 메모리를 덮어쓰기 위해 다른 함수 호출
    //std::vector<int> dummyData(1000, 42); // 스택 메모리를 차지함
    //for (int ix = 0; ix < 1; ++ix)
    //{
    //    std::cout << *llist->At(ix) << " ";
    //}
    //std::cout << "\n";

    Function2();


    // 동적 배열 객체 생성.
    List<int> list;

    // 원소 추가.
    for (int ix = 0; ix < 100; ++ix)
    {
        list.PushBack(ix);
    }

    char buffer[256];
    snprintf(buffer, 256, "%d, %d\n", list.Count(), list.Capacity());

    //const int& value = list[100];

    //std::cout << list.Count() << ", " << list.Capacity() << "\n";
    std::cout << buffer;

    // Standard Template Library(STL) 동적 배열.
    std::vector<int> vector;
    //{
    //    1, 2, 3, 4, 5
    //};

    for (int ix = 0; ix < 100; ++ix)
    {
        vector.push_back(ix);
        // 기존엔 이동 연산하려면 emplace_back 사용 - 지금은 push_back으로도 가능
        //vector.emplace_back(10);
    }

    // 읽기.
    // Range-Based Loop / Ranged Loop.
    // forEach/Foreach.
    //for (const auto& item : vector)
    //{
    //    std::cout << item << " ";
    //}

    for (const auto& item : list)
    {
        std::cout << item << " ";
    }

    //for (List<int>::Iterator iterator = list.begin(); iterator != list.end(); ++iterator)
    //{
    //    std::cout << *iterator << " ";
    //}

    std::cout << "\n";

    snprintf(buffer, 256, "%d, %d", 
        static_cast<int>(vector.size()), 
        static_cast<int>(vector.capacity()));
    std::cout << buffer;

    std::cout << "\n\n";
    std::vector<int> aaaa;
    
    for (int i = 0; i < 10; ++i)
    {
        std::cout << aaaa.capacity() << " ";
        aaaa.push_back(i);
    }
}