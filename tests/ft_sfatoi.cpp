/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_sfatoi.cpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/07 16:12:08 by jhille        #+#    #+#                 */
/*   Updated: 2022/03/11 14:51:32 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "gtest/gtest.h"

extern "C"
{
	#include "../include/input.h"
	#include <pthread.h>
}

/* 
** ft_sfatoi() expects a string which has a valid integer number
** first character has to be a number or '-' character
** white space is not tolerated, nor are empty strings, nor strings devoid of a number
** non numeric characters are also forbidden
** RETURN value is expected to be 0 with success. -1 with overflow or invalid strings.
*/

TEST(ft_sfatoi, basic_tests)
{
	int	value;

	ASSERT_EQ(ft_sfatoi("100", &value), 0);
	ASSERT_EQ(value, 100);

	ASSERT_EQ(ft_sfatoi("10", &value), 0);
	ASSERT_EQ(value, 10);

	ASSERT_EQ(ft_sfatoi("203492", &value), 0);
	ASSERT_EQ(value, 203492);
}

TEST(ft_sfatoi, negative_tests)
{
	int	value;

	ASSERT_EQ(ft_sfatoi("-100", &value), 0);
	ASSERT_EQ(value, -100);

	ASSERT_EQ(ft_sfatoi("-1", &value), 0);
	ASSERT_EQ(value, -1);

	ASSERT_EQ(ft_sfatoi("-13450", &value), 0);
	ASSERT_EQ(value, -13450);
}

TEST(ft_sfatoi, zero_tests)
{
	int	value;

	value = -1;
	ASSERT_EQ(ft_sfatoi("-0", &value), 0);
	ASSERT_EQ(value, 0);

	value = -1;
	ASSERT_EQ(ft_sfatoi("0", &value), 0);
	ASSERT_EQ(value, 0);
}

TEST(ft_sfatoi, almost_overflow)
{
	int	value;

	value = 0;
	ASSERT_EQ(ft_sfatoi("2147483647", &value), 0);
	ASSERT_EQ(value, 2147483647);

	value = 0;
	ASSERT_EQ(ft_sfatoi("-2147483647", &value), 0);
	ASSERT_EQ(value, -2147483647);

	value = 0;
	ASSERT_EQ(ft_sfatoi("-2147483648", &value), 0);
	ASSERT_EQ(value, -2147483648);
}

TEST(ft_sfatoi, overflow)
{
	int	value;

	value = 0;

	ASSERT_EQ(ft_sfatoi("2147483648", &value), -1);
	ASSERT_EQ(value, 0);

	ASSERT_EQ(ft_sfatoi("-2147483649", &value), -1);
	ASSERT_EQ(value, 0);

	ASSERT_EQ(ft_sfatoi("2147483699", &value), -1);
	ASSERT_EQ(value, 0);

	ASSERT_EQ(ft_sfatoi("-4147483648", &value), -1);
	ASSERT_EQ(value, 0);

	ASSERT_EQ(ft_sfatoi("4147483649", &value), -1);
	ASSERT_EQ(value, 0);
}
