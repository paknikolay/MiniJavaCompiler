//
// Created by nikolai on 24.11.19.
//
#pragma once

#include "IRTExpBase.h"

class Mem :IRTExpBase {
public:
    Mem(const std::shared_ptr<IRTExpBase>& expression) : expression_(expression) {

    }
private:
    std::shared_ptr<IRTExpBase> expression_;
};
