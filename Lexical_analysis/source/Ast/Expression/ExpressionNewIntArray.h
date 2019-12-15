//
// Created by nikolai on 22.10.19.
//

#ifndef MINI_JAVA_COMPILER_EXPRESSIONNEW_INT_H
#define MINI_JAVA_COMPILER_EXPRESSIONNEW_INT_H

#include "ExpressionBase.h"
#include <memory>

class ExpressionNewIntArray : public ExpressionBase {
public:
    ExpressionNewIntArray(std::pair<int, int> pos_, const std::shared_ptr<ExpressionBase> &count) : count(count)
    {
        SetPosition(pos_);
    }

    std::shared_ptr<ExpressionBase> GetCount() {
        return count;
    }


    int Accept(Visitor* v);
private:
    std::shared_ptr<ExpressionBase> count;
};


#endif //MINI_JAVA_COMPILER_EXPRESSIONNEW_INT_H
