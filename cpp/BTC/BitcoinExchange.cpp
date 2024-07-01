/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp	                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <agrun@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 12:23:01 by agrun             #+#    #+#             */
/*   Updated: 2023/09/23 12:23:01 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

float	BitcoinExchange::ft_stof(const std::string &str)
{
	float			num;
	std::stringstream	nb(str);

	nb >> num;
	return num;
}

////////////////////////////////////////////////////////////////////////////////

BitcoinExchange::~BitcoinExchange()
{
	return ;
}

float 	BitcoinExchange::findReference(std::map<std::string, float>::iterator i)
{
	std::map<std::string, float>::iterator k = _table.begin();
	std::map<std::string, float>::iterator l = _table.end();
	std::map<std::string, float>::iterator m;

	std::string buffer;
	size_t v = 0;
	size_t w = 0;
	size_t x = 1;

	buffer.clear();
	while (x < i->first.size())				//saving date from file for comparison
	{
		buffer.append(1, i->first[x]);
		x++;
	}
	m = l;
	m--;
	if (m->first < buffer)					//in case the date is in the future
		return (m->second);
	m = k;

	while (k != l)
	{
		while (buffer[v] && k->first[v] == buffer[v])
		{
			v++;
			if (v > w)
			{
				m = k;
				w = v;
			}
		}
		v = 0;
		k++;
	}
	if (m->first == buffer)
		return (m->second);
	else 
	{
		while (m != l && m->first < buffer)		//skipping older dates
			m++;
		while (1)
		{
			if (m != k && m->first > buffer)	//going back if needed
				m--;
			else if (m->first < buffer)
				return (m->second);
		}
	}
	return (0);
}

void	BitcoinExchange::printBTC()
{
	if (_table.empty() == true || _file.empty() == true)
		return ;

	std::map<std::string, float>::iterator i = _file.begin();
	std::map<std::string, float>::iterator j = _file.end();

	std::map<std::string, float>::iterator k = _table.begin();
	std::map<std::string, float>::iterator l = _table.end();
	std::map<std::string, float>::iterator m = k;

	std::string buffer;
	this->_entry = 0;
	float nbr = -1;
	size_t x = 1;

	while (i != j)
	{
		if (this->_error[_entry].empty() == false)
			std::cout << this->_error[_entry] << std::endl;
		else
		{
			while (x < i->first.size())
			{
				buffer.append(1, i->first[x]);
				x++;
			}
			while (k != l && nbr < 0)
			{
				if (buffer == k->first)
					nbr = k->second;
				k++;
			}
			if (nbr < 0)
				nbr = this->findReference(i);
			std::cout << buffer << " => " << _save[_entry] << " = ";	//calculate value
			std::cout << (nbr * _save[_entry]) << std::endl;
			//std::cout << " (x" << nbr << ")" << std::endl;		//debugger
		}
		x = 1;
		k = m;
		nbr = -1;
		buffer.clear();
		this->_entry++;
		i++;
	}
}

//////////////////////////////// TABLE CONVERSION ////////////////////////////////

void	BitcoinExchange::convertTable(std::ifstream *fd)
{
	char		c;
	float		nb;
	std::string	nbr;
	std::string	str;

	this->_table.clear();							//reset/cleanup in case of rerun
	while (!fd->eof() && *fd >> std::noskipws >> c)				//skipping first line ("date | value")
		if (c == '\n')
			break ;
	while (!fd->eof())
	{
		while (*fd >> std::noskipws >> c)				//reading the date
		{
			if (c != ',')
				str += c;
			else
				break ;
		}
		while (*fd >> std::noskipws >> c && c == ',')			//skipping to next parameter
			(void)c;
		if (*fd && !fd->eof()
			&& ((c >= '0' && c <= '9') || c == '-' || c == '+'))
			nbr += c;
		while (*fd >> std::noskipws >> c				//reading the value
			&& c != 9 && c != 10 && c != 32)
			nbr += c;
		if (nbr.empty() == false)
			nb = ft_stof(nbr);
		else
			nb = 0;

		this->_table.insert(std::pair<std::string, float>(str, nb));
		str.clear();
		nbr.clear();
	}
}

bool	BitcoinExchange::fillTable()
{
	std::ifstream	fd;

	fd.open("data.csv");
	if (!fd.is_open())
		return false;
	this->convertTable(&fd);
	fd.close();
	return true;
}

//////////////////////////////// FILE CONVERSION ////////////////////////////////

int	BitcoinExchange::checkDate(std::string date)
{
	unsigned int i(0);

	while (i < date.size())
	{
		if (i == 4 || i == 7)				//example: 2000-01-01
		{
			if (date[i] != '-')
				return 1;
		}
		else
		{
			if (date[i] < '0' || date[i] > '9')
				return 1;
		}
		i++;
	}
	i = 0;
	while (i < date.size())
	{
		if (i != 4 && i != 7)				//check for viable dates
		{
			if ((i == 5 && date[i] > '1')
				|| (i == 8 && date[i] > '3'))
				return 1;
			else if (i == 6 && date[i - 1] == '1')
			{
				if (date[i] > '2')
					return 1;
			}
			else if (i == 9 && date[i - 1] == '3')
			{
				if (date[i] > '1')
					return 1;
			}
		}
		i++;
	}
	return 0;
}

int	BitcoinExchange::checkNumber(std::string nbr)
{
	int	i(0);
	int	dots(0);

	if (nbr.empty() == true)
		return 1;
	if (nbr[i] && (nbr[i] == '+' || nbr[i] == '-'))
		i++;
	if (nbr[i] && (nbr[i] < '0' || nbr[i] > '9'))
		return 1;
	while (nbr[i])
	{
		if (nbr[i] == '.' && !dots)
			dots++;
		else if (nbr[i] < '0' || nbr[i] > '9')
			return 1;
		i++;
	}
	return 0;
}

void	BitcoinExchange::checkLine(std::string str, std::string nbr, int flag)
{
	char failsafe(-1);							//to deal with same dates
	failsafe -= BUFFER_SIZE - (char)this->_file.size();			//invisible character

	if (str.empty() == true && nbr.empty() == true)				//dealing with empty input
		return ;
	if (str.empty() == true && nbr.empty() == false)			//empty str
	{
		if (_entry < BUFFER_SIZE)
			this->_error[_entry] = "Error: bad input => " + nbr;
		this->_file.insert(std::pair<std::string, float>
		((char)failsafe + str, (float)_entry));
		return ;
	}
	else if (str.empty() == false && nbr.empty() == true && flag == 1)	//empty nbr
	{
		if (_entry < BUFFER_SIZE)
			this->_error[_entry] = "Error: bad input => " + str;
		this->_file.insert(std::pair<std::string, float>
		((char)failsafe + str, (float)_entry));
		return ;
	}
	else if (flag != 1 || this->checkNumber(nbr) || this->checkDate(str))	//no "|" or too many "." OR illegal characters
	{
		if (_entry < BUFFER_SIZE)
			this->_error[_entry] = "Error: bad input => " + str + " " + nbr;
		this->_file.insert(std::pair<std::string, float>
		((char)failsafe + str, (float)_entry));
		return ;
	}
	float nb = ft_stof(nbr);
	if (nb > 1000)								//too large
	{
		if (_entry < BUFFER_SIZE)
			this->_error[_entry] = "Error: too large a number";
		this->_file.insert(std::pair<std::string, float>
		((char)failsafe + str, (float)_entry));
		return ;
	}
	else if (nbr[0] == '-' || nb < 0)					//negative number
	{
		if (_entry < BUFFER_SIZE)
			this->_error[_entry] = "Error: not a positive number";
		this->_file.insert(std::pair<std::string, float>
		((char)failsafe + str, (float)_entry));
		return ;
	}
	this->_save[_entry] = nb;						//securing order of numbers
	nb = _entry;

	this->_file.insert(std::pair<std::string, float>((char)failsafe + str, nb));
}

void	BitcoinExchange::convertFile(std::ifstream *fd)
{
	char		c;
	std::string	nbr;
	std::string	str;
	int		flag(0);
	int		n_found(0);

	this->_file.clear();							//reset/cleanup in case of rerun
	for (int x = 0; x < BUFFER_SIZE; x++)
		_error[x].clear();

/////////////////////////////////////////////////////////////////////

	while (!fd->eof() && *fd >> std::noskipws >> c)				//skipping first line ("date | value")
		if (c == '\n')
			break ;
	while (!fd->eof())
	{
		while (!n_found && *fd >> std::noskipws >> c			//reading the date
			&& std::isprint(c) && c != 9 && c != 32)
		{
			if (c == 10)
				n_found = 1;
			str += c;
		}
		while (!n_found && (*fd >> std::noskipws >> c)			//checking for "|"
			&& (c == '|' || c == 9 || c == 32))
		{
			if (c == 10)
				n_found = 1;
			else if (c == '|')
				flag++;
		}
		if (c == 10)
			n_found = 1;
		else if (!n_found && *fd && !fd->eof())
			//&& ((c >= '0' && c <= '9') || c == '-' || c == '+'))
			nbr += c;
		while (!n_found && *fd >> std::noskipws >> c
			&& c != 9 && c != 32)
		{
			if (c == 10)
				n_found = 1;
			else if (std::isprint(c) && c != 9 && c != 10 && c != 32)
				nbr += c;
		}
/*DEBUGGER =>*/	//std::cout << "[" << str << "] & [" << nbr << "]" << std::endl;

		this->checkLine(str, nbr, flag);				//adding to container
		if (str.empty() == false || nbr.empty() == false)		//dealing with EOF and empty lines
			this->_entry++;
		str.clear();							//clearing out buffer
		nbr.clear();
		flag = 0;
		n_found = 0;
	}
}

/////////////////////////////////////////////////////////////////////

bool	BitcoinExchange::readFile(const char *filename)
{
	std::ifstream	fd;

	fd.open(filename);
	if (!fd.is_open())
		return false;
	this->convertFile(&fd);
	fd.close();

	this->printBTC();
	return true;
}

void	BitcoinExchange::addFile(const char *filename)
{
	this->_entry = 0;

	if (this->_file.begin() != this->_file.end())
	{
		std::cout << "Warning! Existing file will be overwritten!" << std::endl;
		this->_file.clear();
		for (int i = 0; i < BUFFER_SIZE; i++)
			_save[i] = 0;
		for (int i = 0; i < BUFFER_SIZE; i++)
			_error[i].erase();
	}
	if (this->readFile(filename) == false)
		throw FileNotFound();
	return ;
}

BitcoinExchange::BitcoinExchange(const char *filename)
{
	this->_entry = 0;

	std::cout << "Initialized object constructor... ";
	if (this->fillTable() == false)
		throw TableNotFound();

	std::cout << "Checking file!" << std::endl;
	if (this->readFile(filename) == false)
		throw FileNotFound();
	return ;
}

BitcoinExchange	&BitcoinExchange::operator=(const BitcoinExchange &copy)
{
	_entry = copy._entry;

	_file.clear();
	_table.clear();
	_file = copy._file;
	_table = copy._table;

	for (int i = 0; i < BUFFER_SIZE; i++)
		_save[i] = copy._save[i];
	for (int i = 0; i < BUFFER_SIZE; i++)
		_error[i] = copy._error[i];
	return *this;
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &copy)
{
	*this = copy;
}

BitcoinExchange::BitcoinExchange()
{
	if (this->fillTable() == false)
		throw TableNotFound();

	this->_entry = 0;
	std::cout << "Default BitcoinExchange object was created." << std::endl;
	std::cout << "Please add a viable file for conversion next!" << std::endl;
}

//////////////////////////////// EXCEPTIONS ////////////////////////////////

const char	*BitcoinExchange::TableNotFound::what() const throw()
{
	return ("There is no (viable) BTC-datatable! Shutting down program.");
};

const char	*BitcoinExchange::FileNotFound::what() const throw()
{
	return ("There is no file to be read! Shutting down program.");
};
