//
// Created by nikolai on 22.10.19.
//

#ifndef MINI_JAVA_COMPILER_EXPRESSIONBASEOP_H
#define MINI_JAVA_COMPILER_EXPRESSIONBASEOP_H

#include "ExpressionBase.h"
#include "../../Enums.h"


class ExpressionBinOp : public ExpressionBase {
public:
    ExpressionBinOp(std::pair<int, int> pos_, const std::shared_ptr<ExpressionBase> &left, const std::shared_ptr<ExpressionBase> &right,
                    EBinOp binOp1) : left(left), right(right), binOp(binOp1)
    {
        SetPosition(pos_);
    }

    const std::shared_ptr<ExpressionBase>& GetLeft() const { return left; };
    const std::shared_ptr<ExpressionBase>& GetRight() const { return right; };
    const EBinOp& GetBinOp() const { return binOp; };
    int Accept(Visitor* v);
private:
    std::shared_ptr<ExpressionBase> left, right;
    EBinOp binOp;

};


#endif //MINI_JAVA_COMPILER_EXPRESSIONBASEOP_H
