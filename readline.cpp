#include "readline.h"

#include <vector>



namespace SDR
{
	namespace etc
	{


enum tokens 
{
	T_q,
	T_d,
	T_b,
	T_v,
	T_error,
	T_num
};

enum states
{
	S_s,
	S_uq,
	S_uqo,
	S_qf,
	S_qfo,
	S_wait,
	S_num
};

static int trans_table[S_num][T_num] = 
{
//start
	{S_qf, S_s, S_s, S_uq, S_s},
//unquoted field
    {S_uqo, S_s, S_uq, S_uq, S_s},
//unquoted field odd
	//{S_qf, S_s, S_s, S_uq, S_s},
	{S_uq, S_uqo, S_uqo, S_uqo, S_s},
//quoted field
	{S_wait, S_qf, S_qf, S_qf, S_s},
//qouted field odd
	{S_qf, S_qfo, S_qfo, S_qfo, S_s},
//wait
	{S_qf, S_s, S_wait, S_qfo, S_s},
};


inline bool q(char c) { return c == '\"'; }
inline bool d(char c, char delim) { return c == delim; }
inline bool b(char c) { return c == ' ' || c == '\t'; }
inline bool v(char c, char delim) { return !(q(c) || d(c, delim) || b(c) || c == '\0' || c == '\r' || c == '\f'); }


inline tokens token(char c, char delim)
{ 
	if (q(c)) return T_q;
	else if (d(c, delim)) return T_d;
	else if (b(c)) return T_b;
	else if (v(c, delim)) return T_v;
	else return T_error;
}

extern const char FS;

bool readline(std::string& S, std::istream& is)
{
	char c;
	states cur = S_s;
	char delim = ',';
	
	bool more = is.get(c) != 0;
	int could_be_endq = 0;
	bool mapped = 0; //debug purposes; now testing

	if (more)
	{
		is.putback(c);

		std::vector<char> V; // guaranteed linear-time push_back() [AUS99]

		while (is.get(c) && c != '\r' && c != '\n')
		{
			if (c == 0x1C)
				delim = 0x1C;

			tokens tok = token(c, delim);
			if (q(c))
			{
				if (!(cur == S_s || cur == S_qf))
					c = '\'';
	
				if (cur == S_qf) // remember the last quoted
					could_be_endq = V.size();
			}
			
			if (cur == S_wait &&  v(c, delim)) // moving to qfo from wait; map the last seen " to '
				V[could_be_endq] = '\'';
	
			cur = (states) trans_table[cur][tok]; 
			
			V.push_back(c);
		}

		if (c == '\r' && (c = is.get()) != '\n')
			is.putback(c);

		S.resize(V.size());
		std::copy(V.begin(), V.end(), S.begin());
	}
	
	return more;
}



	}
}
