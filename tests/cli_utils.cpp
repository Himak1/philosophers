/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cli_bonus.cpp                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: zaiba <zaiba@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/28 20:10:24 by zaiba         #+#    #+#                 */
/*   Updated: 2022/03/04 16:23:40 by jhille        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "gtest/gtest.h"
#include <cstdlib>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

/* 
** the following functions can be used to parse CLI output
** needs to be expanded
*/


//######################//
//	Utility Functions	//
//######################//

string	file_to_string(string filename)
{
	ifstream		file(filename);
	string			str;
	ostringstream	ss;

	if (file)
	{
		ss << file.rdbuf();
		str = ss.str();
	}
	else
		str = "";
	return (str);
}

int	memleaks_find(string output)
{
	if (output.find("All heap blocks were freed") != string::npos)
		return (0);
	else
		return (-1);
}

int	vg_still_reachable(string output)
{
	if (output.find("still reachble: 0 bytes in 0 blocks") != string::npos)
		return (0);
	else
		return (-1);
}

