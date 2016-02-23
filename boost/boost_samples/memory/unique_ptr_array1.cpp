
// c++ --std=c++11 unique_ptr_array1.cpp 

#include <iostream>
#include <memory>

int main()
{
    auto buffer = std::unique_ptr<int[]>(new int[1024]);

    unsigned N = 12;
    int* a = new int[N] { 10, 12, 15, 23, 24, 42, 61, 69, 72, 86, 91, 99 };

    std::fill(buffer.get(), buffer.get() + 1024, 0x5a);

    for (unsigned i = 0; i < 16; i++)
        std::cout << buffer[i] << std::endl;

    for (unsigned i = 0; i < N; i++)
        std::cout << a[i] << std::endl;

    return 0;
}
