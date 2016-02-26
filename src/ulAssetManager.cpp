#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>
#include <cassert>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "ulAssetManager.h"

ulAssetManager::ulAssetManager(std::string artFilePath)
{
    std::ifstream artFile(artFilePath);
    if (!artFile.is_open())
    {
        std::cerr<<"Could not open art definition file ("<<artFilePath<<")"<<std::endl;
    }
    else
    {
        std::string jsonString((std::istreambuf_iterator<char>(artFile)),
                         std::istreambuf_iterator<char>());
        doc.Parse(jsonString.c_str());
        assert(!doc.HasParseError());
    }
}

ulAssetManager::~ulAssetManager()
{
}

// Returns true if there was an error preloading this asset, false otherwise
bool ulAssetManager::preload(std::string character, std::string expression)
{
    if (character == "")
    {
        character = "Default";
    }
    if (expression == "")
    {
        expression = "Default";
    }

    std::pair<std::string, std::string> key(character, expression);
    if (assets.find(key) != assets.end())
    {
        // We already preloaded this
        return true;
    }

    if (!doc.HasMember(character.c_str()))
    {
        std::cerr<<"Invalid character name: "<<character<<std::endl;
        return true;
    }
    rapidjson::Value& charValue = doc[character.c_str()];

    if (!charValue.HasMember(expression.c_str()))
    {
        std::cerr<<"Invalid expression name: "<<expression<<std::endl;
        return true;
    }
    rapidjson::Value& exprValue = charValue[expression.c_str()];

    // If we've gotten this far then let's assume there's a valid asset
    lineAsset asset;

    if (!exprValue.HasMember("sprites") || !exprValue["sprites"].IsArray())
    {
        std::cerr<<"No sprites available for character "<<character
                 <<" expressing "<<expression<<std::endl;
    }
    else
    {
        rapidjson::Value& spriteArray = exprValue["sprites"];

        if (spriteArray.Size() == 0)
        {
            asset.avatar.push_back("");
        }
        else
        {
            for (int i = 0; i < (int)spriteArray.Size(); ++i)
            {
                if (spriteArray[i].IsString())
                {
                    std::string filePath = spriteArray[i].GetString();
                    std::ifstream frameFile(filePath);
                    if (!frameFile.is_open())
                    {
                        std::cerr<<"Could not open frame "<<filePath<<std::endl;
                    }
                    else
                    {
                        std::string frame((std::istreambuf_iterator<char>(frameFile)),
                                                std::istreambuf_iterator<char>());
                        asset.avatar.push_back(frame);
                    }
                }
            }
        }
    }


    if (!exprValue.HasMember("speed"))
    {
        std::cerr<<"Invalid print speed for character "<<character
                 <<" expressing "<<expression<<std::endl;
        asset.printSpeed = 1.0f;
    }
    else
    {
        rapidjson::Value& speed = exprValue["speed"];
        asset.printSpeed = speed.GetDouble();
    }

    // No sounds for now so who cares
    asset.sound = "";

    //std::pair<std::string, std::string> key(character, expression);
    assets[key] = asset;
    return false;
}

lineAsset ulAssetManager::get(std::string character, std::string expression)
{
    if (character == "")
    {
        character = "Default";
    }
    if (expression == "")
    {
        expression = "Default";
    }

    std::pair<std::string, std::string> key(character, expression);

    if(assets.find(key) == assets.end() && preload(character, expression))
    {
        std::cerr<<"No existing asset for "<<character<<" expressing "<<expression<<std::endl;
        std::vector<std::string> avatar;
        avatar.push_back("I am a total dinkus\n");
        return {avatar, "", 1.0f};
    }
    return assets[key];
}
