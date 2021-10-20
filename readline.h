#ifndef	__SDR_ETC_READLINE_H__
#define	__SDR_ETC_READLINE_H__

#include <string>
#include <iostream>



namespace SDR
{
	namespace etc
	{

/*	Read bytes upto EOL (CR/LF/CRLF/EOF); discard EOL.

	Return 1, or 0 if there are no more bytes to read.	*/

bool readline(std::string& S, std::istream& is); // guaranteed O(LINESIZE)



	}
}

#endif
