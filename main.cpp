#include <iostream>
#include "nr.hpp"

int main() {
    std::cout << nr::sqr(3) << std::endl;
    int a = 44;
    int b = 12;
    std::cout << nr::max(a, b) << std::endl;
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
