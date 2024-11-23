#include <iostream>
#include <string>
#include <vector>

#include "BigInt.hpp"

int main ()
{
    BigInt A, B;
    std::cout << "Input A: ";
    std::cin >> A;
    std::cout << "Input B: ";
    std::cin >> B;

    std::cout << "A + B = "; (A + B).output ();
    std::cout << "A - B = "; (A - B).output ();
    std::cout << "A * B = " << A * B << std::endl;
    std::cout << "A / B = " << A / B << std::endl;

    return 0;
}