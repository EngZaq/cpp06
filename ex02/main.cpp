#include <iostream>
#include <cstdlib>
#include <ctime>
#include <exception>
#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

// -----------------------------------------------------------------------------
// Core Functions
// -----------------------------------------------------------------------------

Base* generate(void) {
    // Generate a random number between 0 and 2
    int random = std::rand() % 3;

    if (random == 0) {
        std::cout << "Generated: A" << std::endl;
        return new A();
    } else if (random == 1) {
        std::cout << "Generated: B" << std::endl;
        return new B();
    } else {
        std::cout << "Generated: C" << std::endl;
        return new C();
    }
}

void identify(Base* p) {
    // Pointers return NULL if the dynamic_cast fails.
    // We simply check if the result is valid.
    if (dynamic_cast<A*>(p)) {
        std::cout << "Pointer identified as: A" << std::endl;
    } else if (dynamic_cast<B*>(p)) {
        std::cout << "Pointer identified as: B" << std::endl;
    } else if (dynamic_cast<C*>(p)) {
        std::cout << "Pointer identified as: C" << std::endl;
    } else {
        std::cout << "Pointer identified as: Unknown Type" << std::endl;
    }
}

void identify(Base& p) {
    // References cannot be NULL. If dynamic_cast fails on a reference, 
    // it throws an exception. We must use try/catch blocks.
    
    // Check A
    try {
        A& a = dynamic_cast<A&>(p);
        (void)a; // Silence the "unused variable" warning
        std::cout << "Reference identified as: A" << std::endl;
        return;
    } catch (const std::exception& e) {}

    // Check B
    try {
        B& b = dynamic_cast<B&>(p);
        (void)b;
        std::cout << "Reference identified as: B" << std::endl;
        return;
    } catch (const std::exception& e) {}

    // Check C
    try {
        C& c = dynamic_cast<C&>(p);
        (void)c;
        std::cout << "Reference identified as: C" << std::endl;
        return;
    } catch (const std::exception& e) {}

    std::cout << "Reference identified as: Unknown Type" << std::endl;
}

// -----------------------------------------------------------------------------
// Test Program
// -----------------------------------------------------------------------------
int main() {
    // Seed the random number generator using the current time
    std::srand(static_cast<unsigned int>(std::time(NULL)));

    std::cout << "--- Test 1 ---" << std::endl;
    Base* obj1 = generate();
    identify(obj1);
    identify(*obj1);
    delete obj1;
    std::cout << std::endl;

    std::cout << "--- Test 2 ---" << std::endl;
    Base* obj2 = generate();
    identify(obj2);
    identify(*obj2);
    delete obj2;
    std::cout << std::endl;

    std::cout << "--- Test 3 ---" << std::endl;
    Base* obj3 = generate();
    identify(obj3);
    identify(*obj3);
    delete obj3;
    std::cout << std::endl;

    return 0;
}