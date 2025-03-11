/**
 * @file FlagField_Tests2.cpp
 * @brief Tests for the FlagField class.
 * @author Ray Richter
 */
#define FF_USE_HEAP
// #define FLAGFIELD_DEBUG
#include "FlagField.hpp"
#include <iostream>

using namespace std;

int main() {
    cout << "Running FlagField tests...\n" << endl;

    cout << "Out Stream tests:" << endl;
    cout << "FlagField<8> ff; => " << FlagField<8>() << endl;
    cout << "FlagField<8> ff(3, 4, 5); => " << FlagField<8>(3, 4, 5) << endl;
}