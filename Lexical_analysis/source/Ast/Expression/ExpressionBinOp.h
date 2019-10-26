//
// Created by nikolai on 22.10.19.
//

#ifndef MINI_JAVA_COMPILER_EXPRESSIONBASEOP_H
#define MINI_JAVA_COMPILER_EXPRESSIONBASEOP_H

#include "Expression/ExpressionBase.h"
#include "../../Enums.h"
#include <memory>


class ExpressionBinOp : public ExpressionBase {
public:
    ExpressionBinOp(std::shared_ptr<ExpressionBase> &left, std::shared_ptr<ExpressionBase> &right) : left(
            left), right(right) {}

    const std::shared_ptr<ExpressionBase>& GetLeft(){ return left; };
    const std::shared_ptr<ExpressionBase>& GetRight(){ return right; };
    const EBool& GetBinOp(){ return binOp; };

private:
    std::shared_ptr<ExpressionBase> left, right;
    EBool binOp;

};


#endif //MINI_JAVA_COMPILER_EXPRESSIONBASEOP_H
