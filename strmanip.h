#ifndef	__SDR_ETC_STRMANIP_H__
#define	__SDR_ETC_STRMANIP_H__

#include <string>
#include <functional>



namespace	SDR
{
	namespace etc
	{



std::string::const_iterator ltrim(std::string::const_iterator b,
								  std::string::const_iterator e);
std::string::const_iterator rtrim(std::string::const_iterator b,
								  std::string::const_iterator e);

std::string ltrim(const std::string&);
std::string rtrim(const std::string&);

std::string trim(const std::string&);

std::string make_upper(const std::string& s);

int strcmp_n(const std::string&, const std::string&, bool pfxcmp =0);



	}
}

#endif
