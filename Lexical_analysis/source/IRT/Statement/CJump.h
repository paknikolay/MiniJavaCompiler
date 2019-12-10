//
// Created by nikolai on 24.11.19.
//

#pragma once

#include "../IRTExp/IRTExpBase.h"
#include "IRTStatementBase.h"
#include "../../Enums.h"

class CJump : public IRTStatementBase {
public:
    CJump(
            EBinOp binOp,
            const std::shared_ptr<IRTExpBase>& left,
            const std::shared_ptr<IRTExpBase>& right,
            const std::string& true_label,
            const std::string& false_label
         )
         : binOp(binOp),
           left(left),
           right(right),
           true_label(true_label),
           false_label(false_label)
    {
    }

    EBinOp getBinOp() const {
        return binOp;
    }

    const std::shared_ptr<IRTExpBase> &getLeft() const {
        return left;
    }

    const std::shared_ptr<IRTExpBase> &getRight() const {
        return right;
    }

    const std::string &getTrueLabel() const {
        return true_label;
    }

    const std::string &getFalseLabel() const {
        return false_label;
    }

private:
    EBinOp binOp;
    std::shared_ptr<IRTExpBase> left;
    std::shared_ptr<IRTExpBase> right;
    std::string true_label;
    std::string false_label;

};
