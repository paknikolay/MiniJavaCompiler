//
// Created by nikolai on 22.10.19.
//

#ifndef MINI_JAVA_COMPILER_EXPRESSIONNEW_INT_H
#define MINI_JAVA_COMPILER_EXPRESSIONNEW_INT_H

#include "../Expression/ExpressionBase.h"
#include <memory>

class ExpressionNewIntArray : public ExpressionBase {
public:
    ExpressionNewIntArray(std::unique_ptr<ExpressionBase> &count) : count(count.release()) {}

private:
    std::unique_ptr<ExpressionBase> count;
};


#endif //MINI_JAVA_COMPILER_EXPRESSIONNEW_INT_H
