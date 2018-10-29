// -*-c++-*-

/***************************************************************************
**                                                                        **
**  Overloades for bitwise operators for scoped enumerations.             **
**  Copyright (C) 2018 Jakub Klener                                       **
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


/*!
 * \file      enum_flags_unittest.cpp
 * \brief     Tests for enum_flags.
 * \ingroup   group_enum_flags
 *
 * \author    Jakub Klener <lumiksro@centrum.cz>
 * \date      2018-07-03
 * \copyright Copyright (C) 2018 Jakub Klener. All rights reserved.
 *
 * \copyright This project is released under the 3-Clause BSD License. You should have received a copy of the 3-Clause
 *            BSD License along with this program. If not, see https://opensource.org/licenses/.
 */


#include <iostream>

#include "gtest/gtest.h"

#include "lumik/enum_flags/enum_flags.h"


namespace {


// Tests enum_flags.


// test enumeration
enum struct TestFlags : unsigned char {
    None = 0u,
    One = 1u << 0u,
    Two = 1u << 1u,
    Three = 1u << 2u,
    Four = 1u << 3u,
    Five = 1u << 4u,
    Six = 1u << 5u,
    Seven = 1u << 6u,
    Eight = 1u << 7u
};

}  // namespace

namespace lumik {
namespace enum_flags {

// this redefinition enables bitwise operator usage
template<>
struct EnableBitmaskOperators<TestFlags>
{
    static constexpr bool value = true;
};

// declaration of members of partialy specialized structs (not needed in c++17, which introduces inline variables and
// make constexpr variables inline by default)
constexpr bool EnableBitmaskOperators<TestFlags>::value;

}  // namespace enum_flags
}  // namespace lumik

namespace {

// test enumeration without bitwise operators
enum struct TestEnum : unsigned char {
    None = 0u,
    One = 1u << 0u,
    Two = 1u << 1u,
    Three = 1u << 2u,
    Four = 1u << 3u,
    Five = 1u << 4u,
    Six = 1u << 5u,
    Seven = 1u << 6u,
    Eight = 1u << 7u
};

namespace dummy1 {
// test enumeration without bitwise operators
enum struct TestNamespacedEnum : unsigned char {
    None = 0u,
    One = 1u << 0u,
    Two = 1u << 1u,
    Three = 1u << 2u,
    Four = 1u << 3u,
    Five = 1u << 4u,
    Six = 1u << 5u,
    Seven = 1u << 6u,
    Eight = 1u << 7u
};
}  // namespace dummy1

}  // namespace

namespace lumik {
namespace enum_flags {

// this redefinition enables bitwise operator usage
template<>
struct EnableBitmaskOperators<dummy1::TestNamespacedEnum>
{
    static constexpr bool value = true;
};

// declaration of members of partialy specialized structs (not needed in c++17, which introduces inline variables and
// make constexpr variables inline by default)
constexpr bool EnableBitmaskOperators<dummy1::TestNamespacedEnum>::value;

}  // namespace enum_flags
}  // namespace lumik


namespace {

// Tests availability of enable_bitmask_operators functions.
// NOLINTNEXTLINE(cppcoreguidelines-owning-memory,cert-err58-cpp,cppcoreguidelines-special-member-functions,modernize-use-equals-delete)
TEST(enum_flags, enable_bitmask_operators)
{
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-vararg)
    EXPECT_EQ(true, lumik::enum_flags::EnableBitmaskOperators<TestFlags>::value);
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-vararg)
    EXPECT_EQ(false, lumik::enum_flags::EnableBitmaskOperators<TestEnum>::value);
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-vararg)
    EXPECT_EQ(true, lumik::enum_flags::EnableBitmaskOperators<dummy1::TestNamespacedEnum>::value);
}

// Test operators in namespace
namespace dummy2 {
// NOLINTNEXTLINE(cppcoreguidelines-owning-memory,cert-err58-cpp,cppcoreguidelines-special-member-functions,modernize-use-equals-delete)
TEST(enum_flags, namespace)
{
    dummy1::TestNamespacedEnum a, b, c;
    a = dummy1::TestNamespacedEnum::One;
    b = dummy1::TestNamespacedEnum::Two;
    c = a | b;
    EXPECT_EQ(3, static_cast<int>(c));  // NOLINT(cppcoreguidelines-pro-type-vararg)
}
}  // namespace dummy2


// Tests | bitwise operator.
// NOLINTNEXTLINE(cppcoreguidelines-owning-memory,cert-err58-cpp,cppcoreguidelines-special-member-functions,modernize-use-equals-delete)
TEST(enum_flags, OR)
{
    TestFlags a, b, c;
    a = TestFlags::One;
    b = TestFlags::Two;
    c = a | b;
    EXPECT_EQ(3, static_cast<int>(c));  // NOLINT(cppcoreguidelines-pro-type-vararg)
}


// Tests & bitwise operator.
// NOLINTNEXTLINE(cppcoreguidelines-owning-memory,cert-err58-cpp,cppcoreguidelines-special-member-functions,modernize-use-equals-delete)
TEST(enum_flags, AND)
{
    TestFlags a, b, c;
    a = TestFlags::One;
    b = TestFlags::Two;
    c = a & b;
    EXPECT_EQ(0, static_cast<int>(c));  // NOLINT(cppcoreguidelines-pro-type-vararg)
    a = TestFlags::Two;
    c = a & b;
    EXPECT_EQ(2, static_cast<int>(c));  // NOLINT(cppcoreguidelines-pro-type-vararg)
}


// Tests ^ bitwise operator.
// NOLINTNEXTLINE(cppcoreguidelines-owning-memory,cert-err58-cpp,cppcoreguidelines-special-member-functions,modernize-use-equals-delete)
TEST(enum_flags, XOR)
{
    TestFlags a, b, c;
    a = TestFlags::One;
    b = TestFlags::Two;
    c = a ^ b;
    EXPECT_EQ(3, static_cast<int>(c));  // NOLINT(cppcoreguidelines-pro-type-vararg)
    a = TestFlags::Two;
    c = a ^ b;
    EXPECT_EQ(0, static_cast<int>(c));  // NOLINT(cppcoreguidelines-pro-type-vararg)
}


// Tests ~ bitwise operator.
// NOLINTNEXTLINE(cppcoreguidelines-owning-memory,cert-err58-cpp,cppcoreguidelines-special-member-functions,modernize-use-equals-delete)
TEST(enum_flags, NOT)
{
    TestFlags a;
    a = TestFlags::One;
    EXPECT_EQ(254, static_cast<int>(~a));  // NOLINT(cppcoreguidelines-pro-type-vararg)
}


// Tests |= bitwise operator.
// NOLINTNEXTLINE(cppcoreguidelines-owning-memory,cert-err58-cpp,cppcoreguidelines-special-member-functions,modernize-use-equals-delete)
TEST(enum_flags, OR_assignment)
{
    TestFlags a, b;
    a = TestFlags::One;
    b = TestFlags::Two;
    b |= a;
    EXPECT_EQ(3, static_cast<int>(b));  // NOLINT(cppcoreguidelines-pro-type-vararg)
}


// Tests &= bitwise operator.
// NOLINTNEXTLINE(cppcoreguidelines-owning-memory,cert-err58-cpp,cppcoreguidelines-special-member-functions,modernize-use-equals-delete)
TEST(enum_flags, AND_assignment)
{
    TestFlags a, b;
    a = TestFlags::One;
    b = TestFlags::Two;
    b &= a;
    EXPECT_EQ(0, static_cast<int>(b));  // NOLINT(cppcoreguidelines-pro-type-vararg)
    a = TestFlags::Two;
    b = TestFlags::Two;
    b &= a;
    EXPECT_EQ(2, static_cast<int>(b));  // NOLINT(cppcoreguidelines-pro-type-vararg)
}


// Tests ^= bitwise operator.
// NOLINTNEXTLINE(cppcoreguidelines-owning-memory,cert-err58-cpp,cppcoreguidelines-special-member-functions,modernize-use-equals-delete)
TEST(enum_flags, XOR_assignment)
{
    TestFlags a, b;
    a = TestFlags::One;
    b = TestFlags::Two;
    b ^= a;
    EXPECT_EQ(3, static_cast<int>(b));  // NOLINT(cppcoreguidelines-pro-type-vararg)
    a = TestFlags::Two;
    b = TestFlags::Two;
    b ^= a;
    EXPECT_EQ(0, static_cast<int>(b));  // NOLINT(cppcoreguidelines-pro-type-vararg)
}

}  // namespace


int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
