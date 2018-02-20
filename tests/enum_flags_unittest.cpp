/***************************************************************************
**                                                                        **
**  Overloades for bitwise operators for scoped enumerations.             **
**  Copyright (C) 2017 Jakub Klener                                       **
**                                                                        **
**  This file is part of enum_flags project.                              **
**                                                                        **
**  You can redistribute it and/or modify it under the terms of the       **
**  3-Clause BSD License as published by the Open Source Initiative.      **
**                                                                        **
**  This program is distributed in the hope that it will be useful,       **
**  but WITHOUT ANY WARRANTY; without even the implied warranty of        **
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the          **
**  3-Clause BSD License for more details.                                **
**                                                                        **
**  You should have received a copy of the 3-Clause BSD License along     **
**  with this program.                                                    **
**  If not, see https://opensource.org/licenses/                          **
**                                                                        **
****************************************************************************/


#include <iostream>

#include "gtest/gtest.h"

#include "enum_flags.h"


namespace {


// Tests enum_flags.


// test enumeration
enum struct TestFlags : unsigned char
{
    None  = 0,
    One   = 1 << 0,
    Two   = 1 << 1,
    Three = 1 << 2,
    Four  = 1 << 3,
    Five  = 1 << 4,
    Six   = 1 << 5,
    Seven = 1 << 6,
    Eight = 1 << 7
};


// this redefinition enables bitwise operator usage
constexpr bool enable_bitmask_operators(TestFlags) { return true; }


// test enumeration without bitwise operators
enum struct TestEnum : unsigned char
{
    None  = 0,
    One   = 1 << 0,
    Two   = 1 << 1,
    Three = 1 << 2,
    Four  = 1 << 3,
    Five  = 1 << 4,
    Six   = 1 << 5,
    Seven = 1 << 6,
    Eight = 1 << 7
};


// Tests availability of enable_bitmask_operators functions.
TEST(enum_flags, enable_bitmask_operators) {
  EXPECT_EQ(true, enable_bitmask_operators(TestFlags()));
  EXPECT_EQ(false, ::enable_bitmask_operators(TestEnum()));
}


// Tests | bitwise operator.
TEST(enum_flags, OR) {
  TestFlags a, b, c;
  a = TestFlags::One;
  b = TestFlags::Two;
  c = a | b;
  EXPECT_EQ(3, static_cast<int>(c));
}


// Tests & bitwise operator.
TEST(enum_flags, AND) {
  TestFlags a, b, c;
  a = TestFlags::One;
  b = TestFlags::Two;
  c = a & b;
  EXPECT_EQ(0, static_cast<int>(c));
  a = TestFlags::Two;
  c = a & b;
  EXPECT_EQ(2, static_cast<int>(c));
}


// Tests ^ bitwise operator.
TEST(enum_flags, XOR) {
  TestFlags a, b, c;
  a = TestFlags::One;
  b = TestFlags::Two;
  c = a ^ b;
  EXPECT_EQ(3, static_cast<int>(c));
  a = TestFlags::Two;
  c = a ^ b;
  EXPECT_EQ(0, static_cast<int>(c));
}


// Tests ~ bitwise operator.
TEST(enum_flags, NOT) {
  TestFlags a;
  a = TestFlags::One;
  EXPECT_EQ(254, static_cast<int>(~a));
}


// Tests |= bitwise operator.
TEST(enum_flags, OR_assignment) {
  TestFlags a, b;
  a = TestFlags::One;
  b = TestFlags::Two;
  b |= a;
  EXPECT_EQ(3, static_cast<int>(b));
}


// Tests &= bitwise operator.
TEST(enum_flags, AND_assignment) {
  TestFlags a, b;
  a = TestFlags::One;
  b = TestFlags::Two;
  b &= a;
  EXPECT_EQ(0, static_cast<int>(b));
  a = TestFlags::Two;
  b = TestFlags::Two;
  b &= a;
  EXPECT_EQ(2, static_cast<int>(b));
}


// Tests ^= bitwise operator.
TEST(enum_flags, XOR_assignment) {
  TestFlags a, b;
  a = TestFlags::One;
  b = TestFlags::Two;
  b ^= a;
  EXPECT_EQ(3, static_cast<int>(b));
  a = TestFlags::Two;
  b = TestFlags::Two;
  b ^= a;
  EXPECT_EQ(0, static_cast<int>(b));
}

}  // namespace


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
