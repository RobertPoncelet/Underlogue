#ifndef ULASSETMANAGER_H__
#define ULASSETMANAGER_H__

#include <string>
#include <vector>
#include <map>

struct lineAsset
{
	std::vector<std::string> avatar;
	std::string sound;
	int printSpeed;
};

class ulAssetManager
{
public:
	ulAssetManager();
	~ulAssetManager();
	
    bool preload(std::string character, std::string expression);
	lineAsset get(std::string character, std::string expression);
	
private:
	std::map<std::pair<std::string, std::string>, lineAsset> assets;
};

#endif
