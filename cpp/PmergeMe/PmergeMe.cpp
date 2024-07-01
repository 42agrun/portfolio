/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp	                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <agrun@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 12:23:01 by agrun             #+#    #+#             */
/*   Updated: 2023/10/03 12:23:01 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::~PmergeMe()
{
	return ;
}

/*	The Ford-Johnson sorting algorithm is mandatory for this project, e.g.:

	[5][4][3][2][4]		STEP 1
	 o  o

	[4][5][3][2][4]		STEP 2
	 o     o

	[3][4][5][2][4]		STEP 3
         o        o

	[2][3][4][5][4]		STEP 4
	       o     o

	[2][3][4][4][5]		RESULT
										*/

////////////////////////////////////////////////////////////////////////////////////////////////////////

void	PmergeMe::updateList(int i, std::list<int>::iterator j, int mode)
{
	std::list<int> buffer;
	std::list<int>::iterator b = _list.begin();
	std::list<int>::iterator e = _list.end();

	if (!mode || j == e)
		return ;
	else if (mode == 1)						//mode 1: nbr is smaller
	{
		while (b != j)
		{
			buffer.push_back(*b);
			b++;
		}
		buffer.push_back(_nbr[i]);
		while (j != e)
		{
			buffer.push_back(*j);
			j++;
		}
	}
	else if (mode == 2)						//mode 2: nbr is larger or equal
	{
		while (b != j)
		{
			buffer.push_back(*b);
			b++;
		}
		buffer.push_back(*j);
		buffer.push_back(_nbr[i]);
		j++;
		while (j != e)
		{
			buffer.push_back(*j);
			j++;
		}
	}
	_list.clear();
	_list = buffer;
	buffer.clear();
}

void	PmergeMe::sortListInput()
{
	int i = 1;		//used for nbr
	int l;
	int el = 1;		//number of elements in container

	int smallest(_nbr[0]);
	int biggest(_nbr[0]);

	if (_n == 1)
	{
		std::cout << "This is just a single number, there is nothing to sort!" << std::endl;
		return ;
	}
	_list.clear();
	_list.push_back(_nbr[0]);					//add first number to container

	std::list<int>::iterator j = _list.begin();
	std::list<int>::iterator r;
	std::list<int>::iterator f;
	std::list<int>::iterator e;

	while (i < _n && i < BUFFER_SIZE)
	{
		if (*j > _nbr[i])					//smallest value goes to front
			this->updateList(i, j, 1);
		else
			this->updateList(i, j, 2);			//equal or bigger -> add to back
		el++;
		if (el == _n || el >= BUFFER_SIZE)			//quit if no more numbers left
			break ;
		if (_nbr[i] > biggest)
			biggest = _nbr[i];
		else if (_nbr[i] < smallest)
			smallest = _nbr[i];

		j = _list.begin();
		if (_nbr[i + 1] >= biggest)
		{
			while (*j != biggest)
				j++;
			r = j, f = ++r;
			e = _list.end();
			while (f != e && *j == *f)
				f++, j++;
		}
		else if (_nbr[i + 1] <= smallest)
		{
			while (*j != smallest)
				j++;
			if (j != _list.begin())
				j--;
		}
		else
		{
			l = 0;
			r = _list.begin();
			while (l < el)
			{
				if (*r < _nbr[i + 1] && *r > *j)
					j = r;
				e = j, f = ++e;
				e = _list.end();
				while (f != e && *j == *f)
					f++, j++;
				r++, l++;
			}
		}
		i++;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

void	PmergeMe::updateVector(int i, std::vector<int>::iterator j, int mode)
{
	std::vector<int> buffer;
	std::vector<int>::iterator b = _vector.begin();
	std::vector<int>::iterator e = _vector.end();

	if (!mode || j == e)
		return ;
	else if (mode == 1)						//mode 1: nbr is smaller
	{
		while (b != e && b != j)
		{
			buffer.push_back(*b);
			b++;
		}
		buffer.push_back(_nbr[i]);
		while (j != e)
		{
			buffer.push_back(*j);
			j++;
		}
	}
	else if (mode == 2)						//mode 2: nbr is larger or equal
	{
		while (b != e && b != j)
		{
			buffer.push_back(*b);
			b++;
		}
		buffer.push_back(*j);
		buffer.push_back(_nbr[i]);
		j++;
		while (j != e)
		{
			buffer.push_back(*j);
			j++;
		}
	}
	_vector.clear();
	_vector = buffer;
	buffer.clear();
}

void	PmergeMe::sortVectorInput()
{
	int	i = 1;		//used for nbr
	int	l;
	int	el = 1;		//number of elements in container

	int	smallest(_nbr[0]);
	int	biggest(_nbr[0]);

	if (_n == 1)
	{
		std::cout << "This is just a single number, there is nothing to sort!" << std::endl;
		return ;
	}

	_vector.clear();
	_vector.push_back(_nbr[0]);					//add first number to container

	std::vector<int>::iterator j = _vector.begin();
	std::vector<int>::iterator r;
	std::vector<int>::iterator f;
	std::vector<int>::iterator e;

	while (i < _n && i < BUFFER_SIZE)
	{
		if (*j > _nbr[i])					//smallest value goes to front
			this->updateVector(i, j, 1);
		else							//equal or bigger -> add to back
			this->updateVector(i, j, 2);
		el++;
		if (el == _n || el >= BUFFER_SIZE)			//quit if no more numbers left
			break ;
		if (_nbr[i] > biggest)
			biggest = _nbr[i];
		else if (_nbr[i] < smallest)
			smallest = _nbr[i];

		j = _vector.begin();
		if (_nbr[i + 1] >= biggest)
		{
			while (*j != biggest)
				j++;
			r = j;
			f = ++r;
			e = _vector.end();
			while (j != e && f != e && *j == *f)
				f++, j++;
		}
		else if (_nbr[i + 1] <= smallest)
		{
			while (*j != smallest)
				j++;
			if (j != _vector.begin())
				j--;
		}
		else
		{
			l = 0;
			r = _vector.begin();
			while (l < el && r != _vector.end())		//added end-check
			{
				if (*r < _nbr[i + 1] && *r > *j)
					j = r;
				e = j, f = ++e;
				e = _vector.end();
				while (j != e && f != e && *j == *f)
					f++, j++;
				if (r != _vector.end())
					r++;
				l++;
			}
		}
		i++;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

int	PmergeMe::convertIntoInt(std::string nbr)
{
	int		result = 0;
	int		i = 0;

	while (nbr[i] && nbr[i] >= '0' && nbr[i] <= '9')
	{
		result *= 10;
		result += nbr[i++] - '0';
	}
	return (result);
}

void	PmergeMe::checkInput()
{
	int	i = 0;
	int	j = 0;

	if (_n < 1)
		throw PmergeMe::InputError();
	for (int n = 0; n < _n; n++)
		_nbr[n] = 0;

	while (i < _n)
	{
		if (_input[i][j] < '0' || _input[i][j] > '9')
			throw PmergeMe::FormatError();
		j++;
		if (!_input[i][j])
		{
			j = 0;
			i++;
		}
	}
	for (int k = 0; k < i; k++)
		_nbr[k] = this->convertIntoInt(_input[k]);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

PmergeMe::PmergeMe(char **input, int n) : _n(n)
{
	if (!input || !_n || _n < 1)
		throw PmergeMe::InputError();
	if (_n == 1)
	{
		std::cout << "This is just a single number, there is nothing to sort!" << std::endl;
		return ;
	}
	int i = 0;
	int j = 1;
	while (input[j] && j < BUFFER_SIZE)
	{
		_input[i] = input[j];
		i++;
		j++;
	}
	this->checkInput();					//will throw an exception if faulty

	std::cout << "Before:	";
	for (int i = 0; i < n && i < BUFFER_SIZE; i++)
		std::cout << _nbr[i] << " ";
	std::cout << std::endl;

	clock_t start;
	clock_t end;
	double vector_time;
	double list_time;

	start = clock();
	this->sortVectorInput();
	end = clock();
	vector_time = (double)(end - start) / CLOCKS_PER_SEC * 1000;

	start = clock();
	this->sortListInput();
	end = clock();
	list_time = (double)(end - start) / CLOCKS_PER_SEC * 1000;

	std::cout << "After :	";					//vector sorting
	std::vector<int>::iterator ss = _vector.begin();
	std::vector<int>::iterator tt = _vector.end();
	while (ss != tt)
	{
		std::cout << *ss << " ";
		ss++;
	}
	std::cout << std::endl;
/*
	std::cout << "After :	";					//list sorting
	std::list<int>::iterator s = _list.begin();
	std::list<int>::iterator t = _list.end();
	while (s != t)
	{
		std::cout << *s << " ";
		s++;
	}
	std::cout << std::endl;
*/
	std::cout << "Time to process a range of " << n << " elements with std::vector : ";
	std::cout << vector_time << " us" << std::endl;
	std::cout << "Time to process a range of " << n << " elements with std::list   : ";
	std::cout << list_time << " us" << std::endl;

	std::vector<int>::iterator dd = _vector.begin();
	std::vector<int>::iterator vv;
	std::vector<int>::iterator uu;
	uu = dd;
	vv = ++uu;
	uu = _vector.end();
	while (dd != uu)
	{
		if (vv == _vector.end())	//required to avoid invalid reads
			break ;
		if (*dd > *vv && vv != uu)
		{
			std::cout << "[ERROR] THIS VECTOR IS NOT PROPERLY SORTED: ";
			std::cout << *dd << " & " << *vv << std::endl;
			break ;
		}
		vv++, dd++;
	}

	std::list<int>::iterator d = _list.begin();
	std::list<int>::iterator v;
	std::list<int>::iterator u;
	u = d;
	v = ++u;
	u = _list.end();
	while (d != u)
	{
		if (*d > *v && v != u)
		{
			std::cout << "[ERROR] THIS LIST IS NOT PROPERLY SORTED: ";
			std::cout << *d << " & " << *v << std::endl;
			break ;
		}
		v++, d++;
	}
}

PmergeMe	&PmergeMe::operator=(const PmergeMe &copy)
{
	_list = copy._list;
	_vector = copy._vector;
	_n = copy._n;

	for (int i = 0; i < copy._n; i++)
	{
		_nbr[i] = copy._nbr[i];
		_input[i] = copy._input[i];
	}
	return *this;
}

PmergeMe::PmergeMe(const PmergeMe &copy)
{
	*this = copy;
}

PmergeMe::PmergeMe()
{
	throw PmergeMe::InputError();
}

//////////////////////////////////////////////////////////////////////////// TESTING 3000 RANDOM NUMBERS

PmergeMe::PmergeMe(std::string input[3000], int n) : _n(n)
{
	if (!_n || _n < 1)
		throw PmergeMe::InputError();
	if (_n == 1)
	{
		std::cout << "This is just a single number, there is nothing to sort!" << std::endl;
		return ;
	}
	int i = 0;
	while (i < _n && i < BUFFER_SIZE)
	{
		_input[i] = input[i];
		i++;
	}
	this->checkInput();					//will throw an exception if faulty

	clock_t start;
	clock_t end;
	double vector_time;
	double list_time;

	start = clock();
	this->sortVectorInput();
	end = clock();
	vector_time = (double)(end - start) / CLOCKS_PER_SEC * 1000;

	start = clock();
	this->sortListInput();
	end = clock();
	list_time = (double)(end - start) / CLOCKS_PER_SEC * 1000;

	std::cout << "Time to process a range of " << n << " elements with std::vector : ";
	std::cout << vector_time << " us" << std::endl;
	std::cout << "Time to process a range of " << n << " elements with std::list   : ";
	std::cout << list_time << " us" << std::endl;

	std::vector<int>::iterator dd = _vector.begin();
	std::vector<int>::iterator vv;
	std::vector<int>::iterator uu;
	uu = dd;
	vv = ++uu;
	uu = _vector.end();
	while (dd != uu)
	{
		if (vv == _vector.end())	//required to avoid invalid reads
			break ;
		if (*dd > *vv && vv != uu)
		{
			std::cout << "[ERROR] THIS VECTOR IS NOT PROPERLY SORTED: ";
			std::cout << *dd << " & " << *vv << std::endl;
			break ;
		}
		vv++, dd++;
	}

	std::list<int>::iterator d = _list.begin();
	std::list<int>::iterator v;
	std::list<int>::iterator u;
	u = d;
	v = ++u;
	u = _list.end();
	while (d != u)
	{
		if (*d > *v && v != u)
		{
			std::cout << "[ERROR] THIS LIST IS NOT PROPERLY SORTED: ";
			std::cout << *d << " & " << *v << std::endl;
			break ;
		}
		v++, d++;
	}
}

//////////////////////////////// EXCEPTIONS ////////////////////////////////

const char	*PmergeMe::InputError::what() const throw()
{
	return ("Error: no input was found, discarding action.");
};

const char	*PmergeMe::FormatError::what() const throw()
{
	return ("Error: the input format is faulty, discarding action.");
};
