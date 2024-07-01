/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <agrun@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:09:41 by agrun             #+#    #+#             */
/*   Updated: 2023/10/03 11:09:44 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <sstream>

int	main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cerr << "Number of arguments insufficient. Shutting down!" << std::endl;
		return 1;
	}

	try
	{
		PmergeMe a(argv, argc - 1);
		//PmergeMe p(a);
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}

////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	srand(time(0));
	int random(0);
	std::stringstream buffer;
	std::string conversion;
	std::string total[3000];

	random = rand();

	int z(0);
	while (z < 10)
	{
		for (int x = 0; x < 3000; x++)
		{
			random = rand();
			while (random > 10000)
				random /= 10;
			buffer << random;
			buffer >> conversion;
			total[x] = conversion;
			conversion.clear();
			buffer.clear();
		}
		try
		{
			PmergeMe b(total, 3000);
		}
		catch (const std::exception &e)
		{
			std::cerr << e.what() << std::endl;
		}
		z++;
	}
*/
	return 0;
}
