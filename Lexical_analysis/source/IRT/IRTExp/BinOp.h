//
// Created by nikolai on 24.11.19.
//
#pragma once

#include "IRTExpBase.h"
#include "../Enums.h"

class BinOp : IRTExpBase {
    EBinOp op;
    std::shared_ptr<IRTExpBase> left;
    std::shared_ptr<IRTExpBase> right;
public:
    BinOp(EBinOp op, const std::shared_ptr<IRTExpBase>& left, const std::shared_ptr<IRTExpBase>& right) :
            op(op),
            left(left),
            right(right) {}
};



