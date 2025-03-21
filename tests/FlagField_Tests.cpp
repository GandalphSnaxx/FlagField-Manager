#include <iostream>
#include <cassert>

#define FLAGFIELD_DEBUG
// #define FLAGFIELD_NO_VALIDATE
#include <FlagField.hpp>

void test_constructors() {
    FlagField ff;
    ff.set(1);
    assert(ff.isSet(1));
    FlagField ff2(ff);
    assert(ff2.isSet(1));
    FlagField ff3(0, 1, 2, 3);
    assert(ff3.isSet(0, 1, 2, 3));
}

void run_all_tests() {
    test_constructors();
    // test_functions();
    // test_binary_operators();
    // test_unary_operators();
    // test_member_access_operators();
    std::cout << "All tests passed!" << std::endl;
}

int main() {
    run_all_tests();
    return 0;
}