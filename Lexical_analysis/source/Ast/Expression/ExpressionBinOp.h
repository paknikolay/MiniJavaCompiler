//
// Created by nikolai on 22.10.19.
//

#ifndef MINI_JAVA_COMPILER_EXPRESSIONBASEOP_H
#define MINI_JAVA_COMPILER_EXPRESSIONBASEOP_H

#include "Expression/ExpressionBase.h"
#include "../../Enums.h"


class ExpressionBinOp : public ExpressionBase {
public:
    ExpressionBinOp(std::shared_ptr<ExpressionBase> &left, std::shared_ptr<ExpressionBase> &right,
                    EBinOp binOp1) : left(left), right(right), binOp(binOp1) {}

    const std::shared_ptr<ExpressionBase>& GetLeft(){ return left; };
    const std::shared_ptr<ExpressionBase>& GetRight(){ return right; };
    const EBinOp& GetBinOp(){ return binOp; };
private:
    std::shared_ptr<ExpressionBase> left, right;
    EBinOp binOp;

};


#endif //MINI_JAVA_COMPILER_EXPRESSIONBASEOP_H
