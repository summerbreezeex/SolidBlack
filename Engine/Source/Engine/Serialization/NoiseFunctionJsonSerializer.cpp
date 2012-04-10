#include "Engine/StlCommon.h"
#include "Engine/Noise/Noise.h"

#include "NoiseFunctionJsonSerializer.h"

NoiseFunction* NoiseFunctionJsonSerializer::deserialize(const Json::Value& jsonValue) {
    if (!jsonValue.isObject()) {
        throw std::runtime_error("Invalid noise std::function JSON.");
    }

    std::string typeName = jsonValue["type"].asString();

    if (typeName == "Add") {
        auto f = new AddOperator();

        const Json::Value& sources = jsonValue["sources"];
        for (int i = 0; i < (int)sources.size(); ++i) {
            f->addFunction(deserialize(sources[i]));
        };
        return f;
    }

    if (typeName == "Multiply") {
        auto f = new MultiplyOperator();

        const Json::Value& sources = jsonValue["sources"];
        for (int i = 0; i < (int)sources.size(); ++i) {
            f->addFunction(deserialize(sources[i]));
        };
        return f;
    }

    if (typeName == "Select") {
        auto f = new SelectOperator();
        f->setControlPoint(jsonValue.get("controlPoint", f->getControlPoint()).asDouble());
        f->setFalloff(jsonValue.get("falloff", f->getFalloff()).asDouble());
        f->setControlFunction(deserialize(jsonValue["controlFunction"]));
        f->setTopFunction(deserialize(jsonValue["topFunction"]));
        f->setBottomFunction(deserialize(jsonValue["bottomFunction"]));
        return f;
    }

    if (typeName == "Furrowed") {
        auto f = new FurrowedNoise();
        f->setSeed(jsonValue.get("seed", f->getSeed()).asInt());
        f->setScale(jsonValue.get("scale", f->getScale()).asDouble());
        f->setOctaveCount(jsonValue.get("octaveCount", f->getOctaveCount()).asInt());
        f->setFrequency(jsonValue.get("frequency", f->getFrequency()).asDouble());
        f->setLacunarity(jsonValue.get("lacunarity", f->getLacunarity()).asDouble());
        f->initialize();
        return f;
    }

    if (typeName == "Turbulent") {
        auto f = new TurbulentNoise();
        f->setSeed(jsonValue.get("seed", f->getSeed()).asInt());
        f->setScale(jsonValue.get("scale", f->getScale()).asDouble());
        f->setOctaveCount(jsonValue.get("octaveCount", f->getOctaveCount()).asInt());
        f->setPersistance(jsonValue.get("persistance", f->getPersistance()).asDouble());
        f->initialize();
        return f;
    }

    if (typeName == "Ridged") {
        auto f = new RidgedNoise();
        f->setSeed(jsonValue.get("seed", f->getSeed()).asInt());
        f->setScale(jsonValue.get("scale", f->getScale()).asDouble());
        f->setOctaveCount(jsonValue.get("octaveCount", f->getOctaveCount()).asInt());
        f->setLacunarity(jsonValue.get("lacunarity", f->getLacunarity()).asDouble());
        f->setGain(jsonValue.get("gain", f->getGain()).asDouble());
        f->initialize();
        return f;
    }

    if (typeName == "Constant") {
        return new ConstantValue(jsonValue.get("value", 0.0).asDouble());
    }

    throw std::runtime_error(std::string("Unknown noise type '") + typeName + "'.");
}