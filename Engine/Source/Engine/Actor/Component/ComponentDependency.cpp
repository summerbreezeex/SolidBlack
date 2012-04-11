#include "ComponentDependency.h"

ComponentDependencyBase::ComponentDependencyBase(const std::string& typeName) :
            typeName(typeName) {
}

const std::string& ComponentDependencyBase::getTypeName() const {
    return typeName;
}