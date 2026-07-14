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
    int random = std::rand() % 3;

    if (random == 0) {
        return new A();
    } else if (random == 1) {
        return new B();
    } else {
        return new C();
    }
}

void identify(Base* p) {
    if (dynamic_cast<A*>(p)) {
        std::cout << "A" << std::endl;
    } else if (dynamic_cast<B*>(p)) {
        std::cout << "B" << std::endl;
    } else if (dynamic_cast<C*>(p)) {
        std::cout << "C" << std::endl;
    } else {
        std::cout << "Unknown Type" << std::endl;
    }
}

void identify(Base& p) {
    try {
        A& a = dynamic_cast<A&>(p);
        (void)a;
        std::cout << "A" << std::endl;
        return;
    } catch (const std::exception& e) {}

    try {
        B& b = dynamic_cast<B&>(p);
        (void)b;
        std::cout << "B" << std::endl;
        return;
    } catch (const std::exception& e) {}

    try {
        C& c = dynamic_cast<C&>(p);
        (void)c;
        std::cout << "C" << std::endl;
        return;
    } catch (const std::exception& e) {}

    std::cout << "Unknown Type" << std::endl;
}

// -----------------------------------------------------------------------------
// Test Program
// -----------------------------------------------------------------------------
int main() {
    std::srand(static_cast<unsigned int>(std::time(NULL)));

    Base* obj1 = generate();
    identify(obj1);
    identify(*obj1);
    delete obj1;

    Base* obj2 = generate();
    identify(obj2);
    identify(*obj2);
    delete obj2;

    Base* obj3 = generate();
    identify(obj3);
    identify(*obj3);
    delete obj3;

    return 0;
}