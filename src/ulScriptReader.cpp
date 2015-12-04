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
	// Skip the first "argument" as it is the command to start the program
	for (int i = 1; i < argc; ++i)
    {
		m_script.push_back(std::string(argv[i]));
	}
	
	reset();
}

void ulScriptReader::debugPrintScript()
{
	//for (std::vector<std::string>::iterator it = m_script.begin(); it != m_script.end(); ++it)
	//{
	//	std::cout<<(*it)<<std::endl;
	//}
}

std::string ulScriptReader::getNextLine()
{
	std::string rtn = (*m_currentLine);
	++m_currentLine;
	return rtn;
}

void ulScriptReader::reset()
{
	m_currentLine = m_script.begin();
}
