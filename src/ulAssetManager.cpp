#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>
#include <cassert>

// For amending file path
#include <sys/types.h>
#include <unistd.h>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "ulAssetManager.h"

ulAssetManager::ulAssetManager(std::string artFilePath)
{
    // Should probably find a better way of doing this bit
    int len = 256;
    char pBuf[len];
    char szTmp[32];
    sprintf(szTmp, "/proc/%d/exe", getpid());
    int bytes = std::min((int)readlink(szTmp, pBuf, len), len - 1);
    if(bytes >= 0)
    {
        pBuf[bytes] = '\0';
    }

    progDir = std::string(pBuf);
    progDir = progDir.substr(0, progDir.length() - 10);

    std::ifstream artFile(progDir + artFilePath);
    if (!artFile.is_open())
    {
        std::cerr<<"Could not open art definition file ("<<progDir + artFilePath<<")"<<std::endl;
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
    if (character == "" || expression == "")
    {
        // There's nothing to preload so who cares
        return false;
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
                    std::ifstream frameFile(progDir + filePath);
                    if (!frameFile.is_open())
                    {
                        std::cerr<<"Could not open frame "<<progDir + filePath<<std::endl;
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
        avatar.push_back("I am a total dingus\n");
        return {avatar, "", 1.0f};
    }
    return assets[key];
}

std::vector< std::pair<std::string, std::string> > ulAssetManager::getAllExpressions()
{
    /*for(auto it = doc.ConstMemberIterator; it != doc.End(); it++)
    {
       if (it->IsObject())
       {
           std::cout<<it
       }
    }*/

    std::vector< std::pair<std::string, std::string> > ret;
    std::cout<<assets.size()<<" available expressions\n";
    for (auto asset : assets)
    {
        ret.push_back(asset.first);
    }
    return ret;
}
