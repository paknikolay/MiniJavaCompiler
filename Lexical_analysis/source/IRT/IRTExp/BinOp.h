//
// Created by nikolai on 24.11.19.
//
#pragma once

#include "IRTExpBase.h"
#include "../../Enums.h"

class BinOp : public IRTExpBase {
    EBinOp op;
    std::shared_ptr<IRTExpBase> left = nullptr;
    std::shared_ptr<IRTExpBase> right = nullptr;
public:
    BinOp(EBinOp op_, const std::shared_ptr<IRTExpBase>& left_, const std::shared_ptr<IRTExpBase>& right_) :
            op(op_),
            left(left_),
            right(right_) {}
};



