/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <agrun@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 11:09:41 by agrun             #+#    #+#             */
/*   Updated: 2023/09/27 11:09:44 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "BitcoinExchange.hpp"

// DEBUG WITH INPUT.CSV!! HANDLE OVERFLOW!!

int	main(int argc, char **argv)
{
	if (argc != 2 || !argv[1])
	{
		std::cerr << "Number of arguments insufficient. Shutting down!" << std::endl;
		return 1;
	}

	try
	{
		BitcoinExchange a(argv[1]);
		std::cout << std::endl;
/*		BitcoinExchange b(a);
		b.printBTC();
		std::cout << std::endl;
		
		BitcoinExchange c;
		std::cout << std::endl;
		c.addFile(argv[1]);
		std::cout << std::endl;
		c.addFile(argv[1]);	*/
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
