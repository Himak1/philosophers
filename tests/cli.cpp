/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cli_tests.cpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: zaiba <zaiba@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/28 20:10:24 by zaiba         #+#    #+#                 */
/*   Updated: 2022/02/28 20:48:58 by zaiba         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "gtest/gtest.h"
#include <cstdlib>

TEST(cli_tests, return_code)
{
	int		ret;
	char	cmd[] = "../philosophers";

	ret = system(cmd);
	ASSERT_EQ(ret, 0);
}