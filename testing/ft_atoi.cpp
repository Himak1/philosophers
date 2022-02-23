#include "gtest/gtest.h"

extern "C"
{
	#include "../include/ft_atoi.h"
}

TEST(ft_atoi, str_100)
{
	ASSERT_EQ(ft_atoi("100"), 100);
}

