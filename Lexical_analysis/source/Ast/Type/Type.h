#pragma once

#include "BaseNode.h"

class Type : public BaseNode {
public:
    enum class EType {
        STANDARD_TYPE,
        STANDARD_TYPE_ARRAY,
        IDENTIFIER
    };

    Type(EType type): type(type)
    {}

    EType GetType() const {
        return type;
    }

private:
    EType type;
};