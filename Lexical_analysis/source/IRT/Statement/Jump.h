//
// Created by nikolai on 27.11.19.
//
#pragma once
#include "IRTStatement.h"
class Jump : public IRTStatementBase {
public:
    Jump(std::string label) : label(label) {
    }

    const std::string &getLabel() const {
        return label;
    }

private:
    std::string label;
};