#include "PmergeMe.hpp"
#include <iterator>

struct PairData
{
	int small;
	int big;
};

int PmergeMe::nbr_of_comps = 0;

PmergeMe::PmergeMe() {}
PmergeMe::PmergeMe(const PmergeMe& other) { (void)other; }
PmergeMe& PmergeMe::operator=(const PmergeMe& other) { (void)other; return *this; }
PmergeMe::~PmergeMe() {}

bool PmergeMe::compare(int a, int b)
{
	++nbr_of_comps;
	return a < b;
}


int PmergeMe::binaryInsertVector(std::vector<int>& main, int value, int boundIndex)
{
	int low = 0;
	int high = boundIndex;

	while (low < high)
	{
		int middle = low + (high - low) / 2;
		if (compare(main[middle], value))
			low = middle + 1;
		else
			high = middle;
	}
	main.insert(main.begin() + low, value);
	return low;
}

void PmergeMe::fordJohnsonVector(std::vector<int>& elements)
{
	if (elements.size() <= 1)
		return;

	std::vector<PairData> pairs;
	std::vector<PairData> sorted;
	std::vector<int> bigs;
	std::vector<int> main;
	bool hasOdd = (elements.size() % 2 != 0);
	int odd = hasOdd ? elements.back() : 0;

	for (size_t i = 0; i + 1 < elements.size(); i += 2)
	{
		PairData p;
		if (compare(elements[i + 1], elements[i]))
		{
			p.small = elements[i + 1];
			p.big = elements[i];
		}
		else
		{
			p.small = elements[i];
			p.big = elements[i + 1];
		}
		pairs.push_back(p);
		bigs.push_back(p.big);
	}

	fordJohnsonVector(bigs);

	std::vector<char> used(pairs.size(), 0);
	for (size_t i = 0; i < bigs.size(); ++i)
	{
		for (size_t j = 0; j < pairs.size(); ++j)
		{
			if (!used[j] && pairs[j].big == bigs[i])
			{
				sorted.push_back(pairs[j]);
				used[j] = 1;
				break;
			}
		}
	}

	main.push_back(sorted[0].small);           
	for (size_t i = 0; i < bigs.size(); ++i)  
		main.push_back(bigs[i]);

	int m = static_cast<int>(sorted.size());
	int pending = m + (hasOdd ? 1 : 0);
	int jPrev = 1;
	int jCur = 3;
	while (jPrev < pending)                
	{
		int end = (jCur < pending) ? jCur : pending;
		for (int k = end; k > jPrev; --k)
		{
			int value;
			int bound;
			if (k > m)           
			{
				value = odd;
				bound = static_cast<int>(main.size());
			}
			else
			{
				value = sorted[k - 1].small;
				bound = 0;
				while (main[bound] != sorted[k - 1].big)
					++bound;
			}
			binaryInsertVector(main, value, bound);
		}
		int next = jCur + 2 * jPrev;
		jPrev = jCur;
		jCur = next;
	}
	elements = main;
}

void PmergeMe::sortWithVector(std::vector<int>& input)
{
	fordJohnsonVector(input);
}


std::list<int>::iterator PmergeMe::binaryInsertList(std::list<int>& main,
	int value, std::list<int>::iterator boundIt)
{
	std::list<int>::iterator first = main.begin();
	long count = std::distance(main.begin(), boundIt);

	while (count > 0)
	{
		long step = count / 2;
		std::list<int>::iterator it = first;
		std::advance(it, step);
		if (compare(*it, value))
		{
			first = ++it;
			count -= step + 1;
		}
		else
			count = step;
	}
	return main.insert(first, value);
}

void PmergeMe::fordJohnsonList(std::list<int>& elements)
{
	if (elements.size() <= 1)
		return;

	std::list<PairData> pairs;
	std::list<PairData> sorted;
	std::list<int> bigs;
	std::list<int> main;
	bool hasOdd = (elements.size() % 2 != 0);
	int odd = hasOdd ? elements.back() : 0;

	std::list<int>::iterator it = elements.begin();
	while (it != elements.end())
	{
		int first = *it;
		++it;
		if (it == elements.end())
			break;
		int second = *it;
		++it;
		PairData p;
		if (compare(second, first))
		{
			p.small = second;
			p.big = first;
		}
		else
		{
			p.small = first;
			p.big = second;
		}
		pairs.push_back(p);
		bigs.push_back(p.big);
	}

	fordJohnsonList(bigs);

	for (std::list<int>::iterator b = bigs.begin(); b != bigs.end(); ++b)
	{
		for (std::list<PairData>::iterator p = pairs.begin(); p != pairs.end(); ++p)
		{
			if (p->big == *b)
			{
				sorted.push_back(*p);
				pairs.erase(p);
				break;
			}
		}
	}

	main.push_back(sorted.front().small);     
	main.insert(main.end(), bigs.begin(), bigs.end());

	int m = static_cast<int>(sorted.size());
	int pending = m + (hasOdd ? 1 : 0);
	int jPrev = 1;
	int jCur = 3;
	while (jPrev < pending)
	{
		int end = (jCur < pending) ? jCur : pending;
		for (int k = end; k > jPrev; --k)
		{
			int value;
			std::list<int>::iterator bound;
			if (k > m)
			{
				value = odd;
				bound = main.end();
			}
			else
			{
				std::list<PairData>::iterator pit = sorted.begin();
				std::advance(pit, k - 1);
				value = pit->small;
				bound = main.begin();
				while (*bound != pit->big)
					++bound;
			}
			binaryInsertList(main, value, bound);
		}
		int next = jCur + 2 * jPrev;
		jPrev = jCur;
		jCur = next;
	}
	elements = main;
}

void PmergeMe::sortWithList(std::list<int>& input)
{
	fordJohnsonList(input);
}