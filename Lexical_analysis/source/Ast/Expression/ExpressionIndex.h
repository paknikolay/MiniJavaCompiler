//
// Created by nikolai on 22.10.19.
//

#ifndef MINI_JAVA_COMPILER_EXPRESSIONINDEX_H
#define MINI_JAVA_COMPILER_EXPRESSIONINDEX_H

#include <memory>
#include "ExpressionBase.h"

class ExpressionIndex :public ExpressionBase {
public:
    ExpressionIndex(std::shared_ptr<ExpressionBase> &array, std::shared_ptr<ExpressionBase> &index) : array(
            array), index(index) {}

    const std::shared_ptr<ExpressionBase>& GetArray(){ return array; };
    const std::shared_ptr<ExpressionBase>& GetIndex(){ return index; };
private:
    std::shared_ptr<ExpressionBase> array;
    std::shared_ptr<ExpressionBase> index;
};


#endif //MINI_JAVA_COMPILER_EXPRESSIONINDEX_H
