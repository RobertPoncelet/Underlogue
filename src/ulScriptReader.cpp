#include <iostream>

#include "ulScriptReader.h"

ulScriptReader::ulScriptReader()
{
}

ulScriptReader::~ulScriptReader()
{
}

void ulScriptReader::parseArguments(int argc, char* argv[])
{
	for (int i = 0; i < argc; ++i)
    {
		m_script.push_back(std::string(argv[i]));
	}
}

void ulScriptReader::printScript()
{
	for (std::vector<std::string>::iterator it = m_script.begin(); it != m_script.end(); ++it)
	{
		std::cout<<(*it)<<std::endl;
	}
}
