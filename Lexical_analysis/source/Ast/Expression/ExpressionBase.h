//
// Created by nikolai on 22.10.19.
//

#ifndef MINI_JAVA_COMPILER_EXPRESSION_H
#define MINI_JAVA_COMPILER_EXPRESSION_H

#include "ExpressionBase.h"
#include "../BaseNode.h"
#include <memory>

class ExpressionBase : public BaseNode {
public:
    ExpressionBase(std::pair<int, int> pos_);
    ExpressionBase();

};


#endif //MINI_JAVA_COMPILER_EXPRESSION_H
