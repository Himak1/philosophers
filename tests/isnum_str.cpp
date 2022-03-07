/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   isnum_str.cpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jhille <jhille@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/07 16:11:52 by jhille        #+#    #+#                 */
/*   Updated: 2022/03/07 16:15:24 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "gtest/gtest.h"

extern "C"
{
	#include "../include/input.h"
}

TEST(isnum_str, invalid_strings)
{
	int	value;

	value = 0;

	ASSERT_EQ(isnum_str("-"), -1);

	ASSERT_EQ(isnum_str(""), -1);

	ASSERT_EQ(isnum_str("  -1023"), -1);

	ASSERT_EQ(isnum_str("-1 000"), -1);

	ASSERT_EQ(isnum_str("0  "), -1);

	ASSERT_EQ(isnum_str("1-"), -1);
}
