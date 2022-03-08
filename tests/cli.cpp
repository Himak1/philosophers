/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cli.cpp                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: zaiba <zaiba@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/28 20:10:24 by zaiba         #+#    #+#                 */
/*   Updated: 2022/03/08 11:23:54 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "gtest/gtest.h"
#include <cstdlib>

TEST(cli_tests, return_code)
{
	int		ret;
	char	cmd[] = "../philo";

	ret = system(cmd);
	ASSERT_EQ(ret, 256);
}
