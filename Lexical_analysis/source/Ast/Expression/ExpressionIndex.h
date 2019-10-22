//
// Created by nikolai on 22.10.19.
//

#ifndef MINI_JAVA_COMPILER_EXPRESSIONINDEX_H
#define MINI_JAVA_COMPILER_EXPRESSIONINDEX_H

#include <memory>
#include "ExpressionBase.h"

class ExpressionIndex :public ExpressionBase {

private:
    std::unique_ptr<ExpressionBase> array;
    std::unique_ptr<ExpressionBase> index;
};


#endif //MINI_JAVA_COMPILER_EXPRESSIONINDEX_H
