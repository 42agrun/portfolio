/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <agrun@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 10:55:49 by agrun             #+#    #+#             */
/*   Updated: 2023/09/27 10:55:52 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <iostream>
# include <sstream>
# include <fstream>
# include <algorithm>
# include <string>
# include <map>

# define BUFFER_SIZE 1000

class BitcoinExchange
{
	private:
		std::map<std::string, float>		_table;
		std::map<std::string, float>		_file;

		int					_entry;
		std::string				_error[BUFFER_SIZE];
		float					_save[BUFFER_SIZE];
	public:
		BitcoinExchange();
		BitcoinExchange(const char *filename);
		BitcoinExchange(const BitcoinExchange &copy);
		BitcoinExchange	&operator=(const BitcoinExchange &copy);
		~BitcoinExchange();

		bool			fillTable();
		bool			readFile(const char *filename);
		void			addFile(const char *filename);
		void			convertTable(std::ifstream *fd);
		void			convertFile(std::ifstream *fd);
		void			checkLine(std::string str, std::string nbr, int flag);
		void			printBTC();

		float 			findReference(std::map<std::string,float>::iterator i);
		float			ft_stof(const std::string &str);
		int			checkNumber(std::string nbr);
		int			checkDate(std::string date);

		class TableNotFound : public std::exception
		{
			public:
				virtual const char	*what() const throw();
		};

		class FileNotFound : public std::exception
		{
			public:
				virtual const char	*what() const throw();
		};
};

#endif
