#include "CSVtokenlist.h"
#include "strmanip.h"

#include <cassert>
#include <algorithm>
#include <stdexcept>



using std::string;
using std::vector;


namespace SDR
{
	namespace etc
	{



const char _DELIM =',', DQUOTE ='"', SQUOTE ='\'';
const int COMMA = ',', FS = 0x1C;


class noTRAILINGQUOTE {};



CSVtokenlist::CSVtokenlist(const string& buf, int _d) : L(buf), _no_EOL_DQUOTE(0), DELIM(_d)
{
	B = E = ltrim(L.begin(), L.end());

	if (L.find(FS) != string::npos) DELIM = FS; // FS overrides

	if (B != L.end()) // non-blank line
		try
		{
			next_token();

			while (B != L.end())
			{
				if (*E != DELIM)
					throw std::domain_error("//nopossible");

				B = ++E;

				next_token();
			}

			assert(E == B);
		}
		catch(noTRAILINGQUOTE)
		{
			_no_EOL_DQUOTE = 1; //... and fall through
		}
}



string CSVtokenlist::operator[](int idx) const
{
	assert(size() > idx);
	if (size() <= idx)
		return ""; // to deliver endless trailing fields:
				   // the possible side effects of this are: csvtokenlist will not
				   // complain or fail in other contexts where the missing fields is
				   // supposed to be detected.

	if (idx < 0 || size() <= idx) // we already covered size() <= idx but left it for historical sake
		throw std::domain_error("//notoken");

	return std::string(base().begin() + tokens[idx].first,
					   base().begin() + tokens[idx].second);
}



string CSVtokenlist::unscan(string s)
{
	std::replace(s.begin(), s.end(), DQUOTE, SQUOTE);

	if (s.find(_DELIM) != string::npos)
		s = '"' + s + '"';

	return s;
}

string CSVtokenlist::unscanD(string s, const char useDELIM)
{
	std::replace(s.begin(), s.end(), DQUOTE, SQUOTE);

	if (s.find(useDELIM) != string::npos)
		s = '"' + s + '"';

	return s;
}



static string::const_iterator end_quote(string::const_iterator B,
										string::const_iterator E)
{
	string::const_iterator s;

	s = std::find(B, E, DQUOTE);

	return s;
}



void CSVtokenlist::next_token()
{
	B = E = ltrim(E, L.end());

	bool Q = E != L.end() && *E == DQUOTE;

	if (Q)
	{
		B = E = ltrim(++E, L.end());

		E = end_quote(B, string::const_iterator(L.end()));
	}
	else
		E = std::find(B, string::const_iterator(L.end()), DELIM);

	int i1 = B - L.begin();
	int i2 = rtrim(B, E) - L.begin();

	tokens.push_back(std::make_pair(B - L.begin(), rtrim(B, E) - L.begin()));

	if (Q)
	{
		if (E == L.end())
			throw noTRAILINGQUOTE();

		assert(*E == DQUOTE);

		E = ltrim(++E, L.end());
	}

	B = E;
}



	}
}
