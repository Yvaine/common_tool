
#include <iostream>
#include <memory>

int main()
{
    auto numbers = std::unique_ptr<int[]>( { 42, 69, 86, 99 });
    std::cout << numbers << std::endl;

    return 0;
}
