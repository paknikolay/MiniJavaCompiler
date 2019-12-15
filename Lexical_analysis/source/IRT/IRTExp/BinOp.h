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
    BinOp(EBinOp op, const std::shared_ptr<IRTExpBase>& left, const std::shared_ptr<IRTExpBase>& right) :
            op(op),
            left(left),
            right(right) {}

    int Accept(Visitor* v);

    EBinOp GetBinOp() {
        return op;
    }

    std::shared_ptr<IRTExpBase> GetLeft() {
        return  left;
    }

    std::shared_ptr<IRTExpBase> GetRight() {
        return  right;
    }

};



