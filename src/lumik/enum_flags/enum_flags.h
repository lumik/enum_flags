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
 * \file      enum_flags.h
 * \brief     Templates for bitwise operators are defined in this file.
 *
 * \author    Jakub Klener <lumiksro@centrum.cz>
 * \date      2018-07-03
 * \copyright Copyright (C) 2018 Jakub Klener. All rights reserved.
 *
 * \copyright This project is released under the 3-Clause BSD License. You should have received a copy of the 3-Clause
 *            BSD License along with this program. If not, see https://opensource.org/licenses/.
 *
 * If you want bitwise operators to work for your enumeration, you have to overload enable_bitmask_operators()
 * function to return true. The library utilizes _SFINAE_ concept, specifically the fact, that interpretation of
 * bitwise operators fails when enable_bitmask_operators() function returns `false` for used datatype.
 *
 * \code
 * #include <lumik/enum_flags/enum_flags.h>
 *
 * enum struct TestFlags : unsigned char
 * {
 *     One   = 1 << 0,
 *     Two   = 1 << 1,
 * };
 *
 * constexpr bool enable_bitmask_operators(TestFlags) { return true; }
 *
 * int main(int argc, char **argv) {
 *     TestFlags a, b, c;
 *     a = TestFlags::One;
 *     b = TestFlags::Two;
 *     c = a | b;
 * }
 * \endcode
 *
 * \sa enable_bitmask_operators()
 */


#ifndef LUMIK_ENUM_FLAGS_ENUM_FLAGS_H_
#define LUMIK_ENUM_FLAGS_ENUM_FLAGS_H_

#include<type_traits>


/*!
 * \brief This function template has to be overloaded in order to allow bitwise operators usage for user defined
 * enumeration.
 * \return true if bitwise operators should be enabled for this enum type.
 *
 * If you want bitwise operators to work for your enumeration, you have to overload this function to return true.
 * The only parameter is a dummy parameter for template function resolution.
 *
 * \code
 * #include <lumik/enum_flags/enum_flags.h>
 *
 * enum struct TestFlags : unsigned char
 * {
 *     One   = 1 << 0,
 *     Two   = 1 << 1,
 * };
 *
 * constexpr bool enable_bitmask_operators(TestFlags) { return true; }
 *
 * int main(int argc, char **argv) {
 *     TestFlags a, b, c;
 *     a = TestFlags::One;
 *     b = TestFlags::Two;
 *     c = a | b;
 * }
 * \endcode
 */
template<typename E>
constexpr bool enable_bitmask_operators(E) { return false; }


/*!
 * \brief Overloaded bitwise operator|().
 * \param a left operand.
 * \param b right operand.
 * \return resulting value of type `E`.
 * \sa operator&(), operator^(), operator~(), operator|=().
 */
template<typename E>
inline constexpr typename std::enable_if<enable_bitmask_operators(E()), E>::type
    operator|(E a, E b)
{
    typedef typename std::underlying_type<E>::type underlying;
    return static_cast<E>(static_cast<underlying>(a) | static_cast<underlying>(b));
}


/*!
 * \brief Overloaded bitwise operator&().
 * \param a left operand.
 * \param b right operand.
 * \return resulting value of type `E`.
 * \sa operator|(), operator^(), operator~(), operator&=().
 */
template<typename E>
inline constexpr typename std::enable_if<enable_bitmask_operators(E()), E>::type
    operator&(E a, E b)
{
    typedef typename std::underlying_type<E>::type underlying;
    return static_cast<E>(static_cast<underlying>(a) & static_cast<underlying>(b));
}


/*!
 * \brief Overloaded bitwise operator^().
 * \param a left operand.
 * \param b right operand.
 * \return resulting value of type `E`.
 * \sa operator|(), operator&(), operator~(), operator^=.
 */
template<typename E>
inline constexpr typename std::enable_if<enable_bitmask_operators(E()), E>::type
    operator^(E a, E b)
{
    typedef typename std::underlying_type<E>::type underlying;
    return static_cast<E>(static_cast<underlying>(a) ^ static_cast<underlying>(b));
}


/*!
 * \brief Overloaded bitwise operator~().
 * \param a operand.
 * \return resulting value of type `E`.
 * \sa operator|(), operator&(), operator^().
 */
template<typename E>
inline typename std::enable_if<enable_bitmask_operators(E()), E>::type
    operator~(E a)
{
    typedef typename std::underlying_type<E>::type underlying;
    return static_cast<E>(~static_cast<underlying>(a));
}


/*!
 * \brief Overloaded bitwise operator|=().
 * \param a left operand.
 * \param b right operand.
 * \return resulting value of type `E`.
 * \sa operator&=(), operator^=, operator|().
 */
template<typename E>
inline typename std::enable_if<enable_bitmask_operators(E()), E&>::type
    operator|=(E &a, E b)
{
    typedef typename std::underlying_type<E>::type underlying;
    a = static_cast<E>(static_cast<underlying>(a) | static_cast<underlying>(b));
    return a;
}


/*!
 * \brief Overloaded bitwise operator&=().
 * \param a left operand.
 * \param b right operand.
 * \return resulting value of type `E`.
 * \sa operator|=(), operator^=, operator&().
 */
template<typename E>
inline typename std::enable_if<enable_bitmask_operators(E()), E&>::type
    operator&=(E &a, E b)
{
    typedef typename std::underlying_type<E>::type underlying;
    a = static_cast<E>(static_cast<underlying>(a) & static_cast<underlying>(b));
    return a;
}


/*!
 * \brief Overloaded bitwise operator^=().
 * \param a left operand.
 * \param b right operand.
 * \return resulting value of type `E`.
 * \sa operator|=(), operator&=, operator^().
 */
template<typename E>
typename std::enable_if<enable_bitmask_operators(E()), E&>::type
    operator^=(E &a, E b)
{
    typedef typename std::underlying_type<E>::type underlying;
    a = static_cast<E>(static_cast<underlying>(a) ^ static_cast<underlying>(b));
    return a;
}

#endif  // LUMIK_ENUM_FLAGS_ENUM_FLAGS_H_
