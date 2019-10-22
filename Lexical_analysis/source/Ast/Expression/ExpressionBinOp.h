//
// Created by nikolai on 22.10.19.
//

#ifndef MINI_JAVA_COMPILER_EXPRESSIONBASEOP_H
#define MINI_JAVA_COMPILER_EXPRESSIONBASEOP_H

#include "Expression/ExpressionBase.h"
#include <memory>


class ExpressionBinOp : public ExpressionBase {

private:
    std::unique_ptr<ExpressionBase> left, right;

};


#endif //MINI_JAVA_COMPILER_EXPRESSIONBASEOP_H
