// fs2comma.cpp : scans the file and converts all FS to commas
//

#include "stdafx.h"
#include "CSVtokenlist.h"
#include <fstream>
#include <string>
#include "readline.h"


//const char COMMA = ',', FS = 0x1C;

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		puts("fs2comma version 6.1.1.0 NIC Technologies Inc 2006-2010");
		puts("Usage: fs2comma 123.fec [out.csv]");
		puts("if the second parameter is specified, that will be used as the output");
		puts("if not, 123.csv will be the output");
		exit(-1);
	}

	std::ifstream is(argv[1]);

	std::string outf;

	if (argc > 2)
		outf = argv[2];
	else
	{
		outf = argv[1];
		outf = outf.substr(0, outf.find('.')) + ".csv";
	}

	std::ofstream os(outf.c_str());
	std::string S;

	while (SDR::etc::readline(S, is))
	{
		if (S.size() == 0)
			continue;

		SDR::etc::CSVtokenlist C(S, FS);
		
		if (C.size() == 0 || C[0][0] == '#')
			continue;

		for (int f = 0; f < C.size(); ++f)
		{
			if (f != 0)
				os << (char)COMMA;
			
			os << C.unscanD(C[f], COMMA);
		}

		os << std::endl;
	}

	return 0;
}

