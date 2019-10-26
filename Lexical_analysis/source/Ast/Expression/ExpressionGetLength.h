//
// Created by nikolai on 22.10.19.
//

#ifndef MINI_JAVA_COMPILER_EXPRESSIONGETLENGTH_H
#define MINI_JAVA_COMPILER_EXPRESSIONGETLENGTH_H

#include "../Expression/ExpressionBase.h"

#include <memory>

class ExpressionGetLength : public ExpressionBase{
public:
    ExpressionGetLength(std::shared_ptr<ExpressionBase> &container) : container(container) {}

    const std::shared_ptr<ExpressionBase>& GetContainer(){ return container; };
private:
    std::shared_ptr<ExpressionBase> container;
};


#endif //MINI_JAVA_COMPILER_EXPRESSIONGETLENGTH_H
