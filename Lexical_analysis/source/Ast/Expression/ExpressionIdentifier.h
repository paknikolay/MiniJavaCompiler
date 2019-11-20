//
// Created by nikolai on 22.10.19.
//
#pragma once

#include "ExpressionBase.h"
#include <string>

class ExpressionIdentifier : public ExpressionBase {
public:
    ExpressionIdentifier(const std::string& identifier_): identifier(identifier_) {}

    const std::string& GetIdentifier() const { return identifier; };
    int Accept(Visitor* v);
private:
    std::string identifier;
};
