#pragma once

#include <json/json.h>

class NoiseFunction;

class NoiseFunctionJsonSerializer {
public:
    static NoiseFunction* deserialize(const Json::Value& jsonValue);
};