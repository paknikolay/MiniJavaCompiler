//
// Created by nikolai on 22.10.19.
//

#pragma once

#include "ExpressionBase.h"

class ExpressionNewIdentifier : public ExpressionBase {
public:
    ExpressionNewIdentifier(const std::string& identifier) : identifier(identifier) {}

    const std::string &GetIdentifier() const {
        return identifier;
    }

    int Accept(Visitor* v);
private:
    std::string identifier;
};

