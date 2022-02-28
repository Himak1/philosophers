#include "gtest/gtest.h"

extern "C"
{
	#include "../include/input.h"
}

TEST(ft_sfatoi, basic_tests)
{
	int	value;

	ASSERT_EQ(ft_sfatoi("100", &value), 0);
	ASSERT_EQ(value, 100);
}
