#include "Integer.h"
#include <iostream>

int main() {
    // Constructors
    Integer a;
    Integer b(true, 10);
    Integer c(-5);
    Integer d(3.14);
    Integer e(true);
    Integer f(" -12345");

    // Output
    std::cout << "a: " << a << std::endl;
    std::cout << "b: " << b << std::endl;
    std::cout << "c: " << c << std::endl;
    std::cout << "d: " << d << std::endl;
    std::cout << "e: " << e << std::endl;
    std::cout << "f: " << f << std::endl;

    // Predicates
    std::cout << "c is even: " << c.isEven() << std::endl;
    std::cout << "c is prime: " << c.isPrime() << std::endl;

    // Operations
    Integer sum = b + c;
    std::cout << "b + c: " << sum << std::endl;

    Integer product = b * c;
    std::cout << "b * c: " << product << std::endl;

    try {
        Integer division = b / c;
        std::cout << "b / c: " << division << std::endl;
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    Integer num1(12);
    Integer num2(18);
    std::cout << "GCD of " << num1 << " and " << num2 << " is: " << num1.GCD(num2) << std::endl;
    std::cout << "LCM of " << num1 << " and " << num2 << " is: " << num1.LCM(num2) << std::endl;

    Integer num3(28);
    std::cout << "Prime factors of " << num3 << " are: ";
    std::vector<long long> factors = num3.primeFactors();
    for (long long factor : factors) {
        std::cout << factor << " ";
    }
    std::cout << std::endl;

    Integer int1(5);
    Integer int2(10);
    std::cout << "int1 > int2: " << (int1 > int2) << std::endl;
    std::cout << "int1 < int2: " << (int1 < int2) << std::endl;
    std::cout << "int1 == int2: " << (int1 == int2) << std::endl;
    return 0;
}