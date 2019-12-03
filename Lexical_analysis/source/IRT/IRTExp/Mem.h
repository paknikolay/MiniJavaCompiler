//
// Created by nikolai on 24.11.19.
//
#pragma once

#include "IRTExpBase.h"

class Mem : public IRTExpBase {
public:

    Mem(std::shared_ptr<IRTExpBase> expr) : expr(expr) {
    }

private:
    std::shared_ptr<IRTExpBase> expr;

};
