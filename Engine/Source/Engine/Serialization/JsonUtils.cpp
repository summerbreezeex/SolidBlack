#include <OgreDataStream.h>
#include <OgreResourceGroupManager.h>

#include "JsonUtils.h"

void JsonUtils::readValueFromFile(const std::string& fileName, Json::Value* jsonValue) {
    std::string json = Ogre::ResourceGroupManager::getSingleton().openResource(fileName)->getAsString();

    Json::Reader reader;
    if (!reader.parse(json, *jsonValue)) {
        throw std::runtime_error("Failed to parse JSON: " + reader.getFormattedErrorMessages());
    }
}

void JsonUtils::writeValueToFile(const Json::Value& jsonValue, const std::string& fileName) {
    auto dataStream =
        Ogre::ResourceGroupManager::getSingleton().createResource(fileName, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, true);

    Json::StyledWriter writer;
    std::string json = writer.write(jsonValue);

    dataStream->write(json.c_str(), json.size());
}