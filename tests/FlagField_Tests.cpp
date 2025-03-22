#include <iostream>
#include <cassert>

#define FLAGFIELD_DEBUG
// #define FLAGFIELD_NO_VALIDATE
#include <FlagField.hpp>

typedef enum BasicFlags {
    FlagA,
    FlagB,
    FlagC,
    FlagD,
    FlagE,
    FlagF,
    FlagG,
    FlagH,
    BasicMAX
} BasicFlags;

typedef enum StdFlags {
    INITALIZED,
    ERROR,
    CLOSED,
    SHOULD_CLOSE,
    UNUSED_1,
    UNUSED_2,
    UNUSED_3,
    SHOULD_MINIMIZE,
    MINIMIZED,
    SHOULD_FULLSCREEN,
    FULLSCREEN,
    MAX_FLAG
} StdFlags;

typedef enum BigEnum {
    Flag0x00, Flag0x01, Flag0x02, Flag0x03, Flag0x04, Flag0x05, Flag0x06, Flag0x07,
    Flag0x08, Flag0x09, Flag0x0A, Flag0x0B, Flag0x0C, Flag0x0D, Flag0x0E, Flag0x0F,
    Flag0x10, Flag0x11, Flag0x12, Flag0x13, Flag0x14, Flag0x15, Flag0x16, Flag0x17,
    Flag0x18, Flag0x19, Flag0x1A, Flag0x1B, Flag0x1C, Flag0x1D, Flag0x1E, Flag0x1F,
    Flag0x20, Flag0x21, Flag0x22, Flag0x23, Flag0x24, Flag0x25, Flag0x26, Flag0x27,
    Flag0x28, Flag0x29, Flag0x2A, Flag0x2B, Flag0x2C, Flag0x2D, Flag0x2E, Flag0x2F,
    Flag0x30, Flag0x31, Flag0x32, Flag0x33, Flag0x34, Flag0x35, Flag0x36, Flag0x37,
    Flag0x38, Flag0x39, Flag0x3A, Flag0x3B, Flag0x3C, Flag0x3D, Flag0x3E, Flag0x3F,
    Flag0x40, Flag0x41, Flag0x42, Flag0x43, Flag0x44, Flag0x45, Flag0x46, Flag0x47,
    Flag0x48, Flag0x49, Flag0x4A, Flag0x4B, Flag0x4C, Flag0x4D, Flag0x4E, Flag0x4F,
    Flag0x50, Flag0x51, Flag0x52, Flag0x53, Flag0x54, Flag0x55, Flag0x56, Flag0x57,
    Flag0x58, Flag0x59, Flag0x5A, Flag0x5B, Flag0x5C, Flag0x5D, Flag0x5E, Flag0x5F,
    Flag0x60, Flag0x61, Flag0x62, Flag0x63, Flag0x64, Flag0x65, Flag0x66, Flag0x67,
    Flag0x68, Flag0x69, Flag0x6A, Flag0x6B, Flag0x6C, Flag0x6D, Flag0x6E, Flag0x6F,
    Flag0x70, Flag0x71, Flag0x72, Flag0x73, Flag0x74, Flag0x75, Flag0x76, Flag0x77,
    Flag0x78, Flag0x79, Flag0x7A, Flag0x7B, Flag0x7C, Flag0x7D, Flag0x7E, Flag0x7F,
    Flag0xMAX
} BigEnum;

void test_constructors() {
    {   std::cout << "Testing basic constructors..." << std::endl;
        FlagField ff;
        std::cout << "\tTesting out stream compatability: \n\t" << ff << std::endl;
        ff.set(1);
        assert(ff.isSet(1));
        FlagField ff2(ff);
        assert(ff2.isSet(1));
        FlagField ff3(0, 1, 2, 3);
        assert(ff3.isSet(0, 1, 2, 3));
    }

    {   std::cout << "Testing large FlagField constructors..." << std::endl;
        FlagField<128> ff128(100);
        std::cout << "\tLarge cout: \n\t" << ff128 << std::endl;
        assert(ff128.isSet(100));
        FlagField<1020> ff1020(1000);
        assert(ff1020.isSet(1000));
    }

    {   std::cout << "Testing basic enum FlagFields..." << std::endl;
        FlagField<BasicMAX, BasicFlags> ff_e;
        ff_e.set(FlagA, FlagB);
        std::cout << "\tEnum cout: \n\t" << ff_e << std::endl;
        // ff_e.set(3); // Error
        assert(ff_e.isSet(FlagA));
        assert(ff_e.isSet(FlagG, FlagH) == false);
        FlagField ff_e2 = ff_e;
        ff_e2.set(FlagD, FlagE);
        // ff_e2.set(3); // Error
        assert(ff_e2.isSet(FlagA, FlagD));
    }

    {   std::cout << "Testing big enum FlagFields..." << std::endl;
        FlagField<Flag0xMAX, BigEnum> ff;
        ff.set(Flag0x00, Flag0x01, Flag0x02, Flag0x03);
        std::cout << "\tBig enum FlagField: \n\t" << ff << std::endl;
        assert(ff.isSet(Flag0x00));
        assert(ff.isSet(Flag0x7F) == false);
        FlagField ff2 = ff;
        assert(ff2.isSet(Flag0x03));
        assert(ff2.isSet(Flag0x0F) == false);
        // ff2.set(Flag0xMAX);
    }
}

void test_functions() {
    std::cout << "Testing functions..." << std::endl;
    {   std::cout << "Testing set()" << std::endl;
        FlagField ff, ff2(1, 2, 3);
        ff.set(7);
        assert(ff.isSet(7));
        assert(ff.isSet(6) == false);
        ff.set(6, 5, 4);
        assert(ff.isSet(6));
        assert(ff.isSet(3) == false);
        ff.set(ff2);
        assert(ff.isSet(6));
        assert(ff.isSet(0) == false);
        ff.set();
        assert(ff.isSet(0));
    }
    {   std::cout << "Testing clear()" << std::endl;
        FlagField ff(0, 1, 2, 3, 5, 6, 7), ff2(5, 6, 7);
        ff.clear(1);
        assert(ff.isSet(1) == false);
        assert(ff.isSet(2));
        ff.clear(2, 3);
        assert(ff.isSet(2) == false);
        assert(ff.isSet(5));
        ff.clear(ff2);
        assert(ff.isSet(5) == false);
        assert(ff.isSet(0));
        ff.clear();
        assert(ff.isSet(0) == false);
    }
    {   std::cout << "Testing toggle()" << std::endl;
        FlagField ff, ff2(4, 5, 6);
        ff.toggle(0);
        assert(ff.isSet(0));
        assert(ff.isSet(1) == false);
        ff.toggle(0, 1, 2, 4);
        assert(ff.isSet(0) == false);
        assert(ff.isSet(1));
        assert(ff.isSet(4));
        ff.toggle(ff2);
        assert(ff.isSet(4) == false);
        assert(ff.isSet(5));
        assert(ff.isSet(6));
        ff.toggle();
        assert(ff.isSet(4));
        assert(ff.isSet(0));
        assert(ff.isSet(7));
    }
    {   std::cout << "Testing isSet()" << std::endl;
        FlagField<4> ff(0, 1, 2, 3), ff2, ff3(0, 1), ff4(2, 3);
        assert(ff.isSet());
        assert(!ff2.isSet());
        assert(ff.isSet(0));
        assert(ff2.isSet(0) == false);
        assert(ff.isSet(ff3));
        assert(ff3.isSet(1, 2) == false);
        assert(ff4.isSet(2, 3));
    }
    {   std::cout << "Testing other functions" << std::endl;
        FlagField<4> ff4;
        FlagField<1024> ff1024;
        FlagField<BasicMAX, BasicFlags> ff_e;
        FlagField<Flag0xMAX, BigEnum> ff_be;
        assert(ff4.size() == 4);
        assert(ff1024.size() == 1024);
        assert(ff_e.size() == 8);
        assert(ff_be.size() == 128);
        
        assert(ff4.sizeBytes() == 1);
        assert(ff1024.sizeBytes() == 128);
        assert(ff_e.sizeBytes() == 1);
        assert(ff_be.sizeBytes() == 16);

        std::cout << "ff4.name()    -> " << ff4.name() << std::endl;
        std::cout << "ff1024.name() -> " << ff1024.name() << std::endl;
        std::cout << "ff_e.name()   -> " << ff_e.name() << std::endl;
        std::cout << "ff_be.name()  -> " << ff_be.name() << std::endl;

        ff4.toggle();
        assert(ff4.numSetFlags() == 4);
        assert(ff1024.numSetFlags() == 0);
        ff_e.toggle();
        assert(ff_e.numSetFlags() == 8);
        assert(ff_be.numSetFlags() == 0);
    }
}

void test_unary_operators() {
    std::cout << "Testing unary operators..." << std::endl;
    {
        FlagField ff;
        assert(!ff);
        uint8_t* ptr = *ff;
        std::cout << "flags_ ptr: " << ptr << std::endl;
        std::cout << ff << std::endl;
        +ff;
        std::cout << ff << std::endl;
        FlagField<BasicMAX, BasicFlags> ff2(FlagA, FlagB, FlagD);
        assert(ff2.isSet(FlagC) == false);
        // ++ff2;
        ff2++;
        assert(ff2.isSet(FlagC));
        assert(ff2.isSet(FlagA));
        // --ff2;
        ff2--;
        assert(ff2.isSet(FlagC));
        assert(ff2.isSet(FlagA) == false);
        ~ff2;
        assert(ff2.isSet(FlagC) == false);
        assert(ff2.isSet(FlagA));
        -ff2;
        assert(!ff2);
    }
}

void test_binary_operators() {
    std::cout << "Testing Binary Operators..." << std::endl;
    {   std::cout << "Operator: ," << std::endl;
        FlagField<MAX_FLAG, StdFlags> ff(INITALIZED), ff2(UNUSED_1, UNUSED_2, UNUSED_3);
        ff, SHOULD_CLOSE, SHOULD_MINIMIZE;
        assert(ff.isSet(SHOULD_MINIMIZE));
        assert(ff.isSet(SHOULD_FULLSCREEN) == false);
        assert(ff.isSet(UNUSED_1) == false);
        ff, ff2;
        assert(ff.isSet(UNUSED_1));
    }
    {   std::cout << "Operators: ==, !=" << std::endl;
        FlagField<MAX_FLAG, StdFlags> ff(INITALIZED, SHOULD_CLOSE), ff2(INITALIZED, MINIMIZED, SHOULD_CLOSE);
        assert(ff == INITALIZED);
        assert(ff != SHOULD_MINIMIZE);
        assert(ff == ff);
        assert(ff != ff2);
        assert(ff2 == ff);
    }
    {   std::cout << "Operators: <, <=, >, >=" << std::endl;
        FlagField ff1(1, 2, 3), ff2(1, 2, 3, 4), ff3(0, 1, 2);
        assert(ff1 <  ff2);
        assert(!(ff1 >  ff2));
        assert(ff1 <= ff2);
        assert(!(ff1 >= ff2));
        assert(ff2 >  ff1);
        assert(!(ff2 <  ff1));
        assert(ff2 >= ff1);
        assert(!(ff2 <= ff1));
        assert(ff3 >= ff1);
        assert(ff3 <= ff1);
    }
    {   std::cout << "Operators: &&, &=, &" << std::endl;
        FlagField ff1(1, 2), ff2(2, 3), ff3(1, 2);
        assert(ff1 && 1);
        assert(!(ff1 && 0));
        assert(ff1 && ff3);
        assert(!(ff1 && ff2));

        assert(ff2.isSet(2) == true);
        ff2 &= 2;
        assert(ff2.isSet(2) == true);
        assert(ff2.isSet(3) == false);

        assert(ff3.isSet(1) == true);
        assert(ff3.isSet(2) == true);
        ff3 &= ff2;
        assert(ff3.isSet(1) == false);
        assert(ff3.isSet(2) == true);

        FlagField ff4, ff5;
        ff4 = ff1 & 1;
        ff5 = (ff1 & ff2);
        assert(ff4.isSet(1) == true);
        assert(ff4.isSet(2) == false);
        assert(ff5.isSet(1) == false);
        assert(ff5.isSet(2) == true);
    }
    {   std::cout << "Operators: ||, |=, |" << std::endl;
        FlagField ff1(1, 2), ff2(2, 3), ff3(3, 4);
        assert(ff1 || 1);
        assert(!(ff1 || 0));
        assert(ff1 || ff2);
        assert(!(ff1 || ff3));

        assert(ff2.isSet(1) == false);
        assert(ff2.isSet(2) == true);
        ff2 |= 1;
        assert(ff2.isSet(1) == true);
        assert(ff2.isSet(2) == true);

        assert(ff3.isSet(2) == false);
        assert(ff3.isSet(3) == true);
        ff3 |= ff2;
        assert(ff3.isSet(2) == true);
        assert(ff3.isSet(3) == true);

        FlagField ff4, ff5;
        ff4 = ff1 | 3;
        ff5 = ff1 | ff2;
        assert(ff4 || 1);
        assert(ff5 || 1);
    }
}

void run_all_tests() {
    test_constructors();
    test_functions();
    test_unary_operators();
    test_binary_operators();
    // test_member_access_operators();
    std::cout << "All tests passed!" << std::endl;
}

int main() {
    run_all_tests();
    return 0;
}