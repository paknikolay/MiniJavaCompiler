#pragma once

#include <string>
#include "BaseNode.h"

class Type : public BaseNode {
public:
    enum class EType {
        STANDARD_TYPE,
        STANDARD_TYPE_ARRAY,
        IDENTIFIER
    };

    Type(EType type, const std::string& typeName ): type(type), typeName(typeName)
    {}

    EType GetType() const {
        return type;
    }

    const std::string &getTypeName() const {
        return typeName;
    }

private:
    EType type;
    std::string typeName;
};