/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrun <agrun@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 10:55:49 by agrun             #+#    #+#             */
/*   Updated: 2023/10/03 10:55:52 by agrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <algorithm>
# include <cstdlib>
# include <list>
# include <vector>
# include <ctime>

# define BUFFER_SIZE 5000

class PmergeMe
{
	private:
		std::vector<int>	_vector;		//supports indexing
		std::list<int>		_list;
		std::string		_input[BUFFER_SIZE];
		int			_nbr[BUFFER_SIZE];	//converted numbers
		int			_n;			//number of elements
	public:
		PmergeMe();
		PmergeMe(char **input, int n);
		PmergeMe(std::string input[3000], int n);	//for testing
		PmergeMe &operator=(const PmergeMe &copy);
		PmergeMe(const PmergeMe &copy);
		~PmergeMe();

		int			convertIntoInt(std::string nbr);
		void			checkInput();
		void			sortVectorInput();
		void			updateVector(int i, std::vector<int>::iterator j, int mode);
		void			sortListInput();
		void			updateList(int i, std::list<int>::iterator j, int mode);

		class InputError : public std::exception
		{
			public:
				virtual const char	*what() const throw();
		};

		class FormatError : public std::exception
		{
			public:
				virtual const char	*what() const throw();
		};
};

#endif