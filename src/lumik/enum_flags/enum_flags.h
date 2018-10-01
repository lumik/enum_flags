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
 * \ingroup   group_enum_flags
 *
 * \author    Jakub Klener <lumiksro@centrum.cz>
 * \date      2018-07-03
 * \copyright Copyright (C) 2018 Jakub Klener. All rights reserved.
 *
 * \copyright This project is released under the 3-Clause BSD License. You should have received a copy of the 3-Clause
 *            BSD License along with this program. If not, see https://opensource.org/licenses/.
 * \sa group_enum_flags.
 */


#ifndef LUMIK_ENUM_FLAGS_ENUM_FLAGS_H_
#define LUMIK_ENUM_FLAGS_ENUM_FLAGS_H_

#include<type_traits>

/*!
 * \defgroup group_enum_flags enum_flags
 * \ingroup group_lumik
 * \brief The enum_flags library.
 *
 * If you want bitwise operators to work for your enumeration, you have to specialize
 * lumik::enum_flags::EnableBitmaskOperators struct template. The library utilizes _SFINAE_ concept, specifically the
 * fact, that interpretation of bitwise operators fails when `lumik::enum_flags::EnableBitmaskOperators::value` is
 * `false` for used datatype `E`.
 *
 * @{
 */

/*!
 * \namespace lumik::enum_flags
 * \brief Namespace containing enum_flags library.
 */


namespace lumik {
namespace enum_flags {

/*!
 * \brief This struct template has to be specialized in order to allow bitwise operators usage for user defined
 * enumeration.
 *
 * If you want bitwise operators to work for your enumeration, you have to specialize this struct to contain public
 * member `value = true`. The struct have to be defined inside lumik::enum_flags namespace.
 *
 * \code
 * #include <lumik/enum_flags/enum_flags.h>
 *
 * namespace my_namespace {
 *
 * enum struct TestFlags : unsigned char
 * {
 *     One   = 1 << 0,
 *     Two   = 1 << 1,
 * };
 *
 * }  // namespace my_namespace
 *
 * namespace lumik {
 * namespace enum_flags {
 *
 * template<>
 * struct EnableBitmaskOperators<my_namespace::TestFlags> {
 *     static constexpr bool value = true;
 * };
 *
 * }  // namespace lumik
 * }  // namespace enum_flags
 *
 * int main(int argc, char **argv) {
 *     my_namespace::TestFlags a, b, c;
 *     a = TestFlags::One;
 *     b = TestFlags::Two;
 *     c = a | b;
 * }
 * \endcode
 * \tparam E The enumeration type
 * \sa EnableBitmaskOperators::value
 */
template<typename E>
struct EnableBitmaskOperators {
    static constexpr bool value = false;
};

}  // namespace enum_flags
}  // namespace lumik


/*!
 * \brief Overloaded bitwise operator|().
 * \param a left operand.
 * \param b right operand.
 * \return resulting value of type `E`.
 * \sa operator&(), operator^(), operator~(), operator|=().
 */
template<typename E>
inline constexpr typename std::enable_if<lumik::enum_flags::EnableBitmaskOperators<E>::value, E>::type
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
inline constexpr typename std::enable_if<lumik::enum_flags::EnableBitmaskOperators<E>::value, E>::type
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
inline constexpr typename std::enable_if<lumik::enum_flags::EnableBitmaskOperators<E>::value, E>::type
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
inline typename std::enable_if<lumik::enum_flags::EnableBitmaskOperators<E>::value, E>::type
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
inline typename std::enable_if<lumik::enum_flags::EnableBitmaskOperators<E>::value, E&>::type
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
inline typename std::enable_if<lumik::enum_flags::EnableBitmaskOperators<E>::value, E&>::type
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
typename std::enable_if<lumik::enum_flags::EnableBitmaskOperators<E>::value, E&>::type
    operator^=(E &a, E b)
{
    typedef typename std::underlying_type<E>::type underlying;
    a = static_cast<E>(static_cast<underlying>(a) ^ static_cast<underlying>(b));
    return a;
}

/*! @}*/  // enum_flags


/*!
 * \var EnableBitmaskOperators::value
 * \brief Enables bitwise operators on the specified enumeration type.
 */


#endif  // LUMIK_ENUM_FLAGS_ENUM_FLAGS_H_
