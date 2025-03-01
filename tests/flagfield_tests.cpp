#include <gtest/gtest.h>
#include "flagfield.hpp"

TEST(FlagFieldTests, SetFlag) {
    FlagField<8> ff;
    ff.setFlag(3);
    EXPECT_TRUE(ff.isFlagSet(3));
}

TEST(FlagFieldTests, ClearFlag) {
    FlagField<8> ff;
    ff.setFlag(5);
    ff.clearFlag(5);
    EXPECT_FALSE(ff.isFlagSet(5));
}

TEST(FlagFieldTests, ToggleFlag) {
    FlagField<8> ff;
    ff.toggleFlag(2);
    EXPECT_TRUE(ff.isFlagSet(2));
    ff.toggleFlag(2);
    EXPECT_FALSE(ff.isFlagSet(2));
}

TEST(FlagFieldTests, IsFlagSet) {
    FlagField<8> ff;
    EXPECT_FALSE(ff.isFlagSet(1));
    ff.setFlag(1);
    EXPECT_TRUE(ff.isFlagSet(1));
}

TEST(FlagFieldTests, MultipleFlags) {
    FlagField<8> ff;
    ff.setFlag(0);
    ff.setFlag(1);
    ff.setFlag(7);
    EXPECT_TRUE(ff.isFlagSet(0));
    EXPECT_TRUE(ff.isFlagSet(1));
    EXPECT_TRUE(ff.isFlagSet(7));
    ff.clearFlag(1);
    EXPECT_FALSE(ff.isFlagSet(1));
}

TEST(FlagFieldTests, DifferentSizeConstructor) {
    FlagField<12> ff(3, 4, 5);
    EXPECT_TRUE(ff.isFlagSet(3));
    EXPECT_TRUE(ff.isFlagSet(4));
    EXPECT_TRUE(ff.isFlagSet(5));
    EXPECT_FALSE(ff.isFlagSet(0));
    EXPECT_FALSE(ff.isFlagSet(2));
    EXPECT_FALSE(ff.isFlagSet(11));
}

TEST(FlagFieldTests, ConstructorWithMultipleFlags) {
    FlagField<8> ff(1, 3, 4);
    EXPECT_TRUE(ff.isFlagSet(1));
    EXPECT_TRUE(ff.isFlagSet(3));
    EXPECT_TRUE(ff.isFlagSet(4));
    EXPECT_FALSE(ff.isFlagSet(0));
    EXPECT_FALSE(ff.isFlagSet(2));
    EXPECT_FALSE(ff.isFlagSet(5));
}

TEST(FlagFieldTests, CopyConstructor) {
    FlagField<8> ff;
    ff.setFlag(3);
    FlagField<8> ff2(ff);
    EXPECT_TRUE(ff2.isFlagSet(3));
}

TEST(FlagFieldTests, DefaultConstructor) {
    FlagField ff;
    EXPECT_FALSE(ff.isFlagSet(3));
}

TEST(FlagFieldTests, NumberOfManagedFlags) {
    FlagField<2> ff2;
    FlagField<16> ff16;
    FlagField<1234> ff1234;
    EXPECT_EQ(ff2.size(), 2);
    EXPECT_EQ(ff16.size(), 16);
    EXPECT_EQ(ff1234.size(), 1234);
    ff2 += 0;
    ff16 += 15;
    ff1234 += 1000;
    EXPECT_TRUE(ff2 & (size_t)0); // Explicit cast to size_t
    EXPECT_TRUE(ff16 & (size_t)15);
    EXPECT_TRUE(ff1234(1000));
}

TEST(FlagFieldTests, BinaryIntegerOperators) {
    FlagField<8> ff;
    ff = 3;
    EXPECT_TRUE(ff.isFlagSet(3));
    EXPECT_FALSE(ff.isFlagSet(2));
    EXPECT_TRUE(ff[0] == (1 << 3));
    EXPECT_TRUE(ff[0] &  (1 << 3));
    ff &= 3;
    EXPECT_FALSE(ff.isFlagSet(3));
    ff |= 3;
    EXPECT_TRUE(ff.isFlagSet(3));
    ff ^= 3;
    EXPECT_FALSE(ff.isFlagSet(3));
    ff += 3;
    EXPECT_TRUE(ff.isFlagSet(3));
    ff -= 3;
    EXPECT_FALSE(ff.isFlagSet(3));
}

TEST(FlagFieldTests, BinaryBooleanOperators) {
    FlagField<8> ff;
    ff = 3;
    FlagField<8> ff2 = ff * true;
    EXPECT_TRUE(ff2.isFlagSet(3));
    ff2 *= false;
    EXPECT_FALSE(ff2.isFlagSet(3));
}

TEST(FlagFieldTests, BinaryFlagFieldOperators) {
    FlagField<8> ff1;
    FlagField<8> ff2;
    ff1.setFlag(3);
    ff2.setFlag(5);
    FlagField<8> ff3 = ff1 & ff2;
    EXPECT_FALSE(ff3.isFlagSet(3));
    EXPECT_FALSE(ff3.isFlagSet(5));
    ff3 = (ff1 | ff2);
    EXPECT_TRUE(ff3.isFlagSet(3));
    EXPECT_TRUE(ff3.isFlagSet(5));
    ff3 = (ff1 ^ ff2);
    EXPECT_TRUE(ff3.isFlagSet(3));
    EXPECT_TRUE(ff3.isFlagSet(5));
    ff1 &= ff2;
    EXPECT_FALSE(ff1.isFlagSet(3));
    ff1 |= ff2;
    EXPECT_TRUE(ff1.isFlagSet(5));
    ff1 ^= ff2;
    EXPECT_FALSE(ff1.isFlagSet(5));
}

TEST(FlagFieldTests, MemberAccessOperators) {
    FlagField<8> ff;
    ff.setFlag(3);
    EXPECT_TRUE(ff(3));
    EXPECT_EQ(ff[0], 8);
}

TEST(FlagFieldTests, UnaryPrefixOperators) {
    FlagField<8> ff;
    EXPECT_TRUE(!ff);
    ff.setFlag(3);
    EXPECT_FALSE(!ff);
    ~ff;
    EXPECT_FALSE(ff.isFlagSet(3));
    uint8_t* flags = &ff;
    EXPECT_NE(flags, nullptr);
    EXPECT_TRUE((bool)ff);
}

TEST(FlagFieldTests, UnaryPostfixOperators) {
    FlagField<8> ff;
    ++ff;
    EXPECT_TRUE(ff.isFlagSet(0));
    EXPECT_TRUE(ff.isFlagSet(7));
    --ff;
    EXPECT_FALSE(ff.isFlagSet(0));
    EXPECT_FALSE(ff.isFlagSet(7));
}

TEST(FlagFieldTests, SetAndClearAllFlags) {
    FlagField<32> ff;
    ++ff;
    for (size_t i = 0; i < 32; ++i) {
        EXPECT_TRUE(ff.isFlagSet(i));
    }
    --ff;
    for (size_t i = 0; i < 32; ++i) {
        EXPECT_FALSE(ff.isFlagSet(i));
    }
}

TEST(FlagFieldTests, ToggleAllFlags) {
    FlagField<8> ff;
    ~ff;
    for (size_t i = 0; i < 8; ++i) {
        EXPECT_TRUE( ff(i) );
    }
    ~ff;
    for (size_t i = 0; i < 8; ++i) {
        EXPECT_FALSE( ff(i) );
    }
}

TEST(FlagFieldTests, CopyAssignmentOperator) {
    FlagField<8> ff1;
    ff1.setFlag(2);
    ff1.setFlag(4);
    FlagField<8> ff2;
    ff2 = ff1;
    EXPECT_TRUE(ff2.isFlagSet(2));
    EXPECT_TRUE(ff2.isFlagSet(4));
    EXPECT_FALSE(ff2.isFlagSet(1));
}

TEST(FlagFieldTests, EqualityAndInequalityOperators) {
    FlagField<8> ff1;
    FlagField<8> ff2;
    ff1.setFlag(3);
    ff2.setFlag(3);
    EXPECT_TRUE(ff1 == ff2);
    ff2.setFlag(4);
    EXPECT_FALSE(ff1 == ff2);
    EXPECT_TRUE(ff1 != ff2);
}