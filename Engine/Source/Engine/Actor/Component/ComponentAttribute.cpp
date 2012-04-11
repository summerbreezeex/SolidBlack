#include <OgreColourValue.h>
#include <OgreQuaternion.h>
#include <OgreVector3.h>
#include <OgreVector4.h>

#include <json/json.h>

#include "ComponentAttribute.h"

ComponentAttributeBase::ComponentAttributeBase(const std::string& name) :
        name(name) {
}

const std::string& ComponentAttributeBase::getName() const {
    return name;
}

template <>
void ComponentAttribute<bool>::serializeToJson(Json::Value* jsonValue) const {
    (*jsonValue) = value;
}

template <>
void ComponentAttribute<int>::serializeToJson(Json::Value* jsonValue) const {
    (*jsonValue) = value;
}

template <>
void ComponentAttribute<Ogre::Real>::serializeToJson(Json::Value* jsonValue) const {
    (*jsonValue) = value;
}

template <>
void ComponentAttribute<std::string>::serializeToJson(Json::Value* jsonValue) const {
    (*jsonValue) = value;
}

template <>
void ComponentAttribute<Ogre::Vector3>::serializeToJson(Json::Value* jsonValue) const {
    jsonValue->append(value.x);
    jsonValue->append(value.y);
    jsonValue->append(value.z);
}

template <>
void ComponentAttribute<Ogre::Vector4>::serializeToJson(Json::Value* jsonValue) const {
    jsonValue->append(value.x);
    jsonValue->append(value.y);
    jsonValue->append(value.z);
    jsonValue->append(value.w);
}

template <>
void ComponentAttribute<Ogre::ColourValue>::serializeToJson(Json::Value* jsonValue) const {
    jsonValue->append(value.r);
    jsonValue->append(value.g);
    jsonValue->append(value.b);
    jsonValue->append(value.a);
}

template <>
void ComponentAttribute<Ogre::Quaternion>::serializeToJson(Json::Value* jsonValue) const {
    jsonValue->append(value.x);
    jsonValue->append(value.y);
    jsonValue->append(value.z);
    jsonValue->append(value.w);
}

template <>
void ComponentAttribute<bool>::deserializeFromJson(const Json::Value& jsonValue) {
    if (jsonValue.isBool()) {
        value = jsonValue.asBool();
    }
}

template <>
void ComponentAttribute<int>::deserializeFromJson(const Json::Value& jsonValue) {
    if (jsonValue.isInt()) {
        value = jsonValue.asInt();
    }
}

template <>
void ComponentAttribute<Ogre::Real>::deserializeFromJson(const Json::Value& jsonValue) {
    if (jsonValue.isDouble()) {
        value = jsonValue.asDouble();
    }
}

template <>
void ComponentAttribute<std::string>::deserializeFromJson(const Json::Value& jsonValue) {
    if (jsonValue.isString()) {
        value = jsonValue.asString();
    }
}

template <>
void ComponentAttribute<Ogre::Vector3>::deserializeFromJson(const Json::Value& jsonValue) {
    if (jsonValue.isArray() && jsonValue.size() == 3) {
        value.x = jsonValue[0].asDouble();
        value.y = jsonValue[1].asDouble();
        value.z = jsonValue[2].asDouble();
    }
}

template <>
void ComponentAttribute<Ogre::Vector4>::deserializeFromJson(const Json::Value& jsonValue) {
    if (jsonValue.isArray() && jsonValue.size() == 4) {
        value.x = jsonValue[0].asDouble();
        value.y = jsonValue[1].asDouble();
        value.z = jsonValue[2].asDouble();
        value.w = jsonValue[3].asDouble();
    }
}

template <>
void ComponentAttribute<Ogre::ColourValue>::deserializeFromJson(const Json::Value& jsonValue) {
    if (jsonValue.isArray() && jsonValue.size() == 3) {
        value.r = (float)jsonValue[0].asDouble();
        value.g = (float)jsonValue[1].asDouble();
        value.b = (float)jsonValue[2].asDouble();
    } else if (jsonValue.isArray() && jsonValue.size() == 4) {
        value.r = (float)jsonValue[0].asDouble();
        value.g = (float)jsonValue[1].asDouble();
        value.b = (float)jsonValue[2].asDouble();
        value.a = (float)jsonValue[3].asDouble();
    }
}

template <>
void ComponentAttribute<Ogre::Quaternion>::deserializeFromJson(const Json::Value& jsonValue) {
    if (jsonValue.isArray() && jsonValue.size() == 4) {
        value.x = jsonValue[0].asDouble();
        value.y = jsonValue[1].asDouble();
        value.z = jsonValue[2].asDouble();
        value.w = jsonValue[3].asDouble();
    }
}