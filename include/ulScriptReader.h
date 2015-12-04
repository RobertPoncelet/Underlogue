#ifndef ULSCRIPTREADER_H__
#define ULSCRIPTREADER_H__

#include <string>
#include <vector>

class ulScriptReader
{
public:
	ulScriptReader();
	~ulScriptReader();
	
	void parseArguments(int argc, char* argv[]);
	void debugPrintScript();
	std::string getNextLine();
	void reset();
	
private:
	std::vector<std::string> m_script;
	std::vector<std::string>::iterator m_currentLine;
};

#endif
