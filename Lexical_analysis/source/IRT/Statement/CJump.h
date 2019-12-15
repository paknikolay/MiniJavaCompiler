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
            EBinOp binOp_,
            const std::shared_ptr<IRTExpBase>& left_,
            const std::shared_ptr<IRTExpBase>& right_,
            const std::string& true_label_,
            const std::string& false_label_
         )
         : binOp(binOp_),
           left(left_),
           right(right_),
           true_label(true_label_),
           false_label(false_label_)
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

    int Accept(Visitor* v);

private:
    EBinOp binOp;
    std::shared_ptr<IRTExpBase> left;
    std::shared_ptr<IRTExpBase> right;
    std::string true_label;
    std::string false_label;

};
