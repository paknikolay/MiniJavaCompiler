//
// Created by nikolai on 24.11.19.
//
#pragma once

#include "IRTExpBase.h"

class Mem : public IRTExpBase {
public:
    Mem(const std::shared_ptr<IRTExpBase>& expression) : expression_(expression) {

    }

    std::shared_ptr<IRTExpBase> GetExpr() {
        return expression_;
    }

    int Accept(Visitor* v);
private:
    std::shared_ptr<IRTExpBase> expression_;
};
