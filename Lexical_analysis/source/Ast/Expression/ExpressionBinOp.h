//
// Created by nikolai on 22.10.19.
//

#pragma once

#include "ExpressionBase.h"
#include "../../Enums.h"


class ExpressionBinOp : public ExpressionBase {
public:
    ExpressionBinOp(const std::shared_ptr<ExpressionBase> &left, const std::shared_ptr<ExpressionBase> &right,
                    EBinOp binOp1) : left(left), right(right), binOp(binOp1) {}

    const std::shared_ptr<ExpressionBase>& GetLeft() const { return left; };
    const std::shared_ptr<ExpressionBase>& GetRight() const { return right; };
    const EBinOp& GetBinOp() const { return binOp; };
    int Accept(Visitor* v);
private:
    std::shared_ptr<ExpressionBase> left, right;
    EBinOp binOp;

};


