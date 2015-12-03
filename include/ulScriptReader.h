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
	void printScript();
	
private:
	std::vector<std::string> m_script;
};

#endif
