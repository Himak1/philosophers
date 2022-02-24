#include "gtest/gtest.h"

extern "C"
{
	#include "../include/input.h"
}

TEST(ft_atoi, str_100)
{
	ASSERT_EQ(ft_atoi("100"), 100);
}

/*
TEST(ft_atoi, str_-120)
{
	ASSERT_EQ(ft_atoi("-120"), -120);
}

TEST(ft_atoi, str_0)
{
	ASSERT_EQ(ft_atoi("0"), 0);
}

TEST(ft_atoi, str_2341241481041048018)
{
	ASSERT_EQ(ft_atoi("2341241481041048018"), -1);
}
*/