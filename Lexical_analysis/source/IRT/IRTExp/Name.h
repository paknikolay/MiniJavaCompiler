//
// Created by nikolai on 24.11.19.
//
#pragma once

#include "IRTExpBase.h"


class Name : public IRTExpBase{
    std::string value;
public:
    Name(std::string value) : value(value) {}

    std::string GetString() {
        return value;
    }

    int Accept(Visitor* v);
};

