#pragma once

#include <string>
#include <memory>
#include "../BaseNode.h"

class Type : public BaseNode {
public:
    enum class EType {
        STANDARD_TYPE,
        STANDARD_TYPE_ARRAY,
        IDENTIFIER
    };

    Type(std::pair<int, int> pos_, EType type, const std::string& typeName ): type(type), typeName(typeName)
    {
        SetPosition(pos_);
    }

    Type(std::pair<int, int> pos_, const std::shared_ptr<Type>& other): type(other->type), typeName(other->typeName)
    {
        SetPosition(pos_);
    }

    EType GetType() const {
        return type;
    }

    const std::string &getTypeName() const {
        return typeName;
    }

    int Accept(Visitor* v);

private:
    EType type;
    std::string typeName;
};