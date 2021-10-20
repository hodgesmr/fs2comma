#ifndef	__SDR_ETC_CSVTOKENLIST_H__
#define	__SDR_ETC_CSVTOKENLIST_H__

#include <string>
#include <vector>



namespace	SDR
{
	namespace etc
	{

extern const int FS, COMMA;


class CSVtokenlist
{
public:
	explicit CSVtokenlist(const std::string& ="", int D = ',');

	bool no_EOL_DQUOTE() const { return _no_EOL_DQUOTE; }

	int size() const
	{
		return tokens.size();
	}

	std::string operator[](int idx) const;

	const std::string& base() const
	{
		return L;
	}

public:
	// utility : replace '"' with '\'', and delimit with '"' if embedded ','
	static std::string unscan(std::string);
	std::string unscanD(std::string, const char useDelim);

private:
	std::string L;

	typedef std::pair<std::string::size_type, std::string::size_type> TokenPos;

	std::vector<TokenPos> tokens;

	bool _no_EOL_DQUOTE;
private: // parser implementation
	void next_token();
private:
	std::string::const_iterator B, E;
	int DELIM;
};



	}
}

using SDR::etc::FS;
using SDR::etc::COMMA;

#endif
