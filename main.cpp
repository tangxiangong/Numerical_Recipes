#include <iostream>
#include "nr.hpp"

using namespace nr;
int main() {
    int a = 90;
    Vector<int> v {3, a};
    v.print();
    v[1] = 3;
    v.print();
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
