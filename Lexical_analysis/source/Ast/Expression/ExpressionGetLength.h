//
// Created by nikolai on 22.10.19.
//

#ifndef MINI_JAVA_COMPILER_EXPRESSIONGETLENGTH_H
#define MINI_JAVA_COMPILER_EXPRESSIONGETLENGTH_H

#include "ExpressionBase.h"

#include <memory>

class ExpressionGetLength : public ExpressionBase{
public:
    ExpressionGetLength(std::pair<int, int> pos_, const std::shared_ptr<ExpressionBase> &container) : container(container)
    {
        SetPosition(pos_);
    }

    const std::shared_ptr<ExpressionBase>& GetContainer() const { return container; };
    int Accept(Visitor* v);
private:
    std::shared_ptr<ExpressionBase> container;
};


#endif //MINI_JAVA_COMPILER_EXPRESSIONGETLENGTH_H
