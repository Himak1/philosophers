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
    char    *arg[] = {"pipex", "1234", "hello", "1234", "yeet"};

    int ret = get_parameters(&data, argc, arg);
}
