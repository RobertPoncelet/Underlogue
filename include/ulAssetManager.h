#ifndef ULASSETMANAGER_H__
#define ULASSETMANAGER_H__

#include <string>
#include <vector>
#include <map>
#include <rapidjson/document.h>

struct lineAsset
{
	std::vector<std::string> avatar;
	std::string sound;
    float printSpeed;
};

class ulAssetManager
{
public:
    ulAssetManager(std::string artFilePath);
	~ulAssetManager();
	
    bool preload(std::string character, std::string expression);
    lineAsset get(std::string character, std::string expression);
    std::vector< std::pair<std::string, std::string> > getAllExpressions();
	
private:
	std::map<std::pair<std::string, std::string>, lineAsset> assets;
    rapidjson::Document doc;
};

#endif
