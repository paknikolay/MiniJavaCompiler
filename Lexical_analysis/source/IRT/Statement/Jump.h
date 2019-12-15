//
// Created by nikolai on 27.11.19.
//
#pragma once
#include "IRTStatement.h"

class Jump : public IRTStatementBase {
public:
    Jump(std::string label_) : label(label_) {
    }

    const std::string &getLabel() const {
        return label;
    }

    int Accept(Visitor* visit);

private:
    std::string label;
};