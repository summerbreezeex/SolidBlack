#pragma once

#include <json/json.h>

#include "Engine/StlCommon.h"

class JsonUtils {
public:
    static void readValueFromFile(const std::string& fileName, Json::Value* root);
    static void writeValueToFile(const Json::Value& root, const std::string& fileName);
};