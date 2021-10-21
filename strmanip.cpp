#include "strmanip.h"

#include <vector>
#include <algorithm>



namespace	SDR
{
	namespace etc
	{



std::string::const_iterator ltrim(std::string::const_iterator b,
								  std::string::const_iterator e)
{
	return std::find_if(b, e,
						std::not1(std::pointer_to_unary_function<int, int>
																(isspace)));
}



std::string::const_iterator rtrim(std::string::const_iterator b,
								  std::string::const_iterator e)
{
	std::string::const_iterator r =
		std::find_if(std::string::const_reverse_iterator(e),
					 std::string::const_reverse_iterator(b),
					 std::not1(std::pointer_to_unary_function<int, int>
															 (isspace))).base();

	return r;
}



std::string ltrim(const std::string& s)
{
	return std::string(ltrim(s.begin(), s.end()), s.end());
}



std::string rtrim(const std::string& s)
{
	return std::string(s.begin(), rtrim(s.begin(), s.end()));
}



std::string trim(const std::string& s)
{
	return std::string(ltrim(s.begin(), s.end()), rtrim(s.begin(), s.end()));
}



std::string make_upper(const std::string& s)
{
	std::vector<char> V;

	std::insert_iterator< std::vector<char> > I(V, V.begin());

	std::transform(s.begin(), s.end(), I, toupper);

	return std::string(V.begin(), V.end());
}



int strcmp_n(const std::string& S1, const std::string& S2, bool pfxcmp)
{
	int r = 0;

	for (int s1 =0, s2 =0; r == 0; ++s1, ++s2)
	{
		//TODO parameterize 'skipper'...
		for (; s1 < (int)S1.size() && isspace(S1[s1]); ++s1);
		for (; s2 < (int)S2.size() && isspace(S2[s2]); ++s2);

		if (s1 >= (int)S1.size())
		{
			if (!pfxcmp)
				r = -(s2 < (int)S2.size());

			break;
		}
		else if (s2 >= (int)S2.size())
		{
			if (!pfxcmp)
				r = s1 < (int)S1.size();

			break;
		}

		//... and 'normalizer' policies
		char c1 = toupper(S1[s1]), c2 = toupper(S2[s2]);

		r = c1 < c2 ? -1 : c1 > c2 ? 1 : 0;
	}

	return r;
}



	}
}
