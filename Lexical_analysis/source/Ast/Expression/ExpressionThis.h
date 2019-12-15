//
// Created by nikolai on 22.10.19.
//

#ifndef MINI_JAVA_COMPILER_EXPRESSIONTHIS_H
#define MINI_JAVA_COMPILER_EXPRESSIONTHIS_H

#include "ExpressionBase.h"

class ExpressionThis : public ExpressionBase {
public:
    ExpressionThis(std::pair<int, int> pos_)
    {
        SetPosition(pos_);
    }
    int Accept(Visitor* v);
};


#endif //MINI_JAVA_COMPILER_EXPRESSIONTHIS_H
