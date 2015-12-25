#include <iostream>

#include "ulAssetManager.h"

ulAssetManager::ulAssetManager()
{
}

ulAssetManager::~ulAssetManager()
{
}

bool ulAssetManager::preload(std::string character, std::string expression)
{
	return false;
}

lineAsset ulAssetManager::get(std::string character, std::string expression)
{
	return {std::vector<std::string>(), "", 1};
}
