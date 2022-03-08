#include "gtest/gtest.h"

extern "C"
{
	#include "../include/input.h"
    #include "../include/data.h"
}

/*
**  
**  
*/

TEST(get_parameters, non_numeric_strings)
{
    t_data  data;
    int     argc    = 5;
    char    *arg_1[] = {"pipex", "1234", "hello", "1234", "yeet"};
    char    *arg_2[] = {"pipex", "1234", "  12", "1234", "5"};

    int ret_1 = get_parameters(&data, argc, arg_1);
    ASSERT_EQ(ret_1, -1);

    int ret_2 = get_parameters(&data, argc, arg_2);
    ASSERT_EQ(ret_2, -1);
}

TEST(get_parameters, correct_parameters)
{
    t_data  data;
    int     argc    = 5;
    char    *arg[] = {"pipex", "1234", "3", "5", "5"};

    int ret = get_parameters(&data, argc, arg);
    ASSERT_EQ(ret, 0);
}

TEST(get_parameters, too_few_args)
{
    t_data  data;
    int     argc    = 4;
    char    *arg[] = {"pipex", "1234", "3", "5"};

    int ret = get_parameters(&data, argc, arg);
    ASSERT_EQ(ret, -1);
}

TEST(get_parameters, too_many_args)
{
    t_data  data;
    int     argc    = 7;
    char    *arg[] = {"pipex", "1234", "3", "5", "5", "6", "7"};

    int ret = get_parameters(&data, argc, arg);
    ASSERT_EQ(ret, -1);
}

TEST(get_parameters, args_too_small)
{
    t_data  data;
    int     argc    = 6;
    char    *arg_1[] = {"pipex", "1234", "3", "5", "5", "-1"};
    char    *arg_2[] = {"pipex", "1234", "3", "5", "0", "1"};

    int ret1 = get_parameters(&data, argc, arg_1);
    ASSERT_EQ(ret1, -1);

    int ret2 = get_parameters(&data, argc, arg_1);
    ASSERT_EQ(ret2, -1);
}
