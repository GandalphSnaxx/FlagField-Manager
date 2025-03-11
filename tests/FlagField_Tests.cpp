#include <iostream>
#include <cassert>
#include "FlagField.hpp"

void test_default_constructor() {
    std::cout << "Testing default constructor" << std::endl;
    FlagField<8> ff;
    assert(ff.size() == 8);
    assert(!ff);
}

void test_sizes() {
    std::cout << "Testing different sizes" << std::endl;
    FlagField<8> ff1;
    assert(ff1.size() == 8);
    FlagField<16> ff2;
    assert(ff2.size() == 16);
    FlagField<32> ff3;
    assert(ff3.size() == 32);
    FlagField<36> ff4;
    assert(ff4.size() == 36);
    FlagField<75> ff5;
    assert(ff5.size() == 75);
}

void test_explicit_constructor() {
    std::cout << "Testing explicit constructor" << std::endl;
    FlagField<8> ff(1, 3, 5);
    assert(ff.isFlagSet(1));
    assert(ff.isFlagSet(3));
    assert(ff.isFlagSet(5));
    assert(!ff.isFlagSet(0));
}

void test_copy_constructor() {
    std::cout << "Testing copy constructor" << std::endl;
    FlagField<8> ff1(1, 3, 5);
    FlagField<8> ff2(ff1);
    assert(ff2.isFlagSet(1));
    assert(ff2.isFlagSet(3));
    assert(ff2.isFlagSet(5));
    assert(!ff2.isFlagSet(0));
}

void test_constructors() {
    test_default_constructor();
    test_sizes();
    test_explicit_constructor();
    test_copy_constructor();
}

void test_setFlag() {
    std::cout << "Testing setFlag" << std::endl;
    FlagField<8> ff;
    ff.setFlag(2);
    assert(ff.isFlagSet(2));
}

void test_clearFlag() {
    std::cout << "Testing clearFlag" << std::endl;
    FlagField<8> ff(2);
    ff.clearFlag(2);
    assert(!ff.isFlagSet(2));
}

void test_toggleFlag() {
    std::cout << "Testing toggleFlag" << std::endl;
    FlagField<8> ff;
    ff.toggleFlag(2);
    assert(ff.isFlagSet(2));
    ff.toggleFlag(2);
    assert(!ff.isFlagSet(2));
}

void test_setFlags() {
    std::cout << "Testing setFlags" << std::endl;
    FlagField<8> ff;
    ff.setFlags(1, 3, 5);
    assert(ff.isFlagSet(1));
    assert(ff.isFlagSet(3));
    assert(ff.isFlagSet(5));
}

void test_are_flags_set() {
    std::cout << "Testing areFlagsSet" << std::endl;
    FlagField<> ff(1, 3, 5);
    assert(ff.areFlagsSet(1, 3, 5));
    assert(!ff.areFlagsSet(1, 2, 5));
    assert(ff.areFlagsSet(1));
    assert(!ff.areFlagsSet(2));
}

void test_functions() {
    test_setFlag();
    test_clearFlag();
    test_toggleFlag();
    test_setFlags();
    test_are_flags_set();
}

void test_binary_int_operators() {
    std::cout << "Testing binary int operators" << std::endl;
    FlagField<32> ff1(30);
    assert(ff1 == 30);
    assert(ff1 & 30);
    ff1 &= 30;
    assert(!ff1);
    ff1 |= 30;
    assert(ff1.isFlagSet(30));
    ff1 ^= 30;
    assert(!ff1.isFlagSet(30));
    ff1 += 30;
    assert(ff1.isFlagSet(30));
    ff1 -= 30;
    assert(!ff1.isFlagSet(30));
}

void test_binary_boolean_operators() {
    std::cout << "Testing binary bool operators" << std::endl;
    FlagField<8> ff(1, 3, 5);
    FlagField<8> ff2 = ff * true;
    assert(ff2.isFlagSet(1));
    ff2 *= false;
    assert(!ff2.isFlagSet(1));
}

void test_binary_ff_operators() {
    std::cout << "Testing binary FlagField operators" << std::endl;
    FlagField<> ff1(1, 3, 5);
    FlagField<> ff2(1, 2, 5);
    FlagField<> ff3;
    ff3 = ff1 & ff2;
    assert(ff3.isFlagSet(1));
    ff3 = ff1 | ff2;
    assert(ff3(1, 2, 3, 5));
    ff3 = ff1 ^ ff2;
    assert(ff3(2, 3));
    ff3 = ff1 - ff2;
    assert(ff3(3));
    ff3 = ff1 + ff2;
    assert(ff3(1, 2, 3, 5));
}

void test_binary_ff_comparisons() {
    std::cout << "Testing binary FlagField comparisons" << std::endl;
    FlagField<> ff1(1, 3, 5);
    FlagField<> ff2(1, 2, 3, 4, 5);
    FlagField<> ff3(0, 1, 2, 3, 4);
    std::cout << "\tTesting Op ==" << std::endl;
    assert(!(ff1 == ff2));
    std::cout << "\tTesting Op !=" << std::endl;
    assert(ff1 != ff2);
    std::cout << "\tTesting Op <" << std::endl;
    assert(ff1 < ff2);
    std::cout << "\tTesting Op >" << std::endl;
    assert(ff2 > ff1);
    std::cout << "\tTesting Op >=" << std::endl;
    assert(ff3 >= ff2);
    std::cout << "\tTesting Op <=" << std::endl;
    assert(ff3 <= ff2);
}

void test_binary_operators() {
    test_binary_int_operators();
    test_binary_boolean_operators();
    test_binary_ff_operators();
    test_binary_ff_comparisons();
}

void test_unary_operators() {
    std::cout << "Testing unary operators" << std::endl;
    FlagField<128> ff1;
    assert(!ff1);
    ~ff1;
    assert((bool)ff1);
    FlagField<128> *pFF = &ff1;
    pFF->clearFlag(0);
    assert(!ff1(0));
    uint8_t *pByte = *ff1;
    *pByte = 0;
    assert(!ff1(0, 1, 2, 3, 4, 5, 6, 7));
    FlagField<> ff;
    ++ff;
    assert((bool)ff);
    --ff;
    assert(!ff);
}

void test_member_access_operators() {
    std::cout << "Testing member assess operators" << std::endl;
    FlagField<8> ff(1, 3, 5);
    assert(ff(1));
    assert(ff[0] == 0b00101010);
}

void test_ostream() {
    std::cout << "Testing ostream operator" << std::endl;
    FlagField<> ff1(1, 3, 5);
    FlagField<128> ff2(127, 126, 125, 124);
    std::cout << ff1 << std::endl;
    std::cout << ff2 << std::endl;
}

void run_all_tests() {
    test_constructors();
    test_functions();
    test_binary_operators();
    test_unary_operators();
    test_member_access_operators();
    std::cout << "All tests passed!" << std::endl;
}

int main() {
    run_all_tests();
    return 0;
}