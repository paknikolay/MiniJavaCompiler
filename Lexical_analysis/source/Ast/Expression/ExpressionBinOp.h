//
// Created by nikolai on 22.10.19.
//

#ifndef MINI_JAVA_COMPILER_EXPRESSIONBASEOP_H
#define MINI_JAVA_COMPILER_EXPRESSIONBASEOP_H

#include "Expression/ExpressionBase.h"
#include <memory>


class ExpressionBinOp : public ExpressionBase {
public:
    ExpressionBinOp(std::unique_ptr<ExpressionBase> &left, std::unique_ptr<ExpressionBase> &right) : left(
            left.release()), right(right.release()) {}

private:
    std::unique_ptr<ExpressionBase> left, right;

};


#endif //MINI_JAVA_COMPILER_EXPRESSIONBASEOP_H
