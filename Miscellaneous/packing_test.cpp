#include <cstdint>
#include <iostream>

struct TestStruct1 {
    char a;
    uint32_t b;
    uint64_t c;
};

struct TestStruct2 {
    uint32_t b;
    uint64_t c;
    char a;
};

class TestClass1 {
public:
    TestClass1() {}

    ~TestClass1() {}

    void doSomething() {
        a = 'a';
    }

private:
    char a;
    uint32_t b;
    uint64_t c;
};

class TestClass2 {
public:
    TestClass2() {}

    ~TestClass2() {}

    void doSomething() {
        a = 'a';
    }

private:
    uint32_t b;
    uint64_t c;
    char a;
};

int main() {
    std::cout << sizeof(TestStruct1) << std::endl;
    std::cout << sizeof(TestStruct2) << std::endl;
    std::cout << sizeof(TestClass1) << std::endl;
    std::cout << sizeof(TestClass2) << std::endl;
    TestClass1 tc1[5];
    TestClass2 tc2[5];
    std::cout << sizeof(tc1) << std::endl;
    std::cout << sizeof(tc2) << std::endl;
}
