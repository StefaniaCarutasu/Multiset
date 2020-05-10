#pragma once
template<typename T>  class Comparator
{
public:
	int operator () (const T& cmp1, const T& cmp2)
	{
		if (cmp1 == cmp2)
			return 0;
		else if (cmp1 < cmp2)
			return -1;
		else return 1;
	}
};
template<>
class Comparator<double>
{
public:
	int operator () (const double& cmp1, const double& cmp2)
	{
		if (cmp1 - int(cmp1) == cmp2 - int(cmp2))
			return 0;
		else if (cmp1 - int(cmp1) < cmp2 - int(cmp2))
			return -1;
		else return 1;
	}
};

