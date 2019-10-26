//
// Created by nikolai on 22.10.19.
//

#ifndef MINI_JAVA_COMPILER_EXPRESSIONGETLENGTH_H
#define MINI_JAVA_COMPILER_EXPRESSIONGETLENGTH_H

#include "../Expression/ExpressionBase.h"

#include <memory>

class ExpressionGetLength : public ExpressionBase{
public:
    ExpressionGetLength(std::unique_ptr<ExpressionBase> &container) : container(container.release()) {}

private:
    std::unique_ptr<ExpressionBase> container;
};


#endif //MINI_JAVA_COMPILER_EXPRESSIONGETLENGTH_H
