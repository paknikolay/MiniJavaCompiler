//
// Created by nikolai on 22.10.19.
//

#ifndef MINI_JAVA_COMPILER_EXPRESSIONINDEX_H
#define MINI_JAVA_COMPILER_EXPRESSIONINDEX_H

#include <memory>
#include "ExpressionBase.h"

class ExpressionIndex :public ExpressionBase {
public:
    ExpressionIndex(std::pair<int, int> pos_, const std::shared_ptr<ExpressionBase> &array, const std::shared_ptr<ExpressionBase> &index) : array(
            array), index(index)
    {
        SetPosition(pos_);
    }

    const std::shared_ptr<ExpressionBase>& GetArray() const { return array; };
    const std::shared_ptr<ExpressionBase>& GetIndex() const { return index; };
    int Accept(Visitor* v);
private:
    std::shared_ptr<ExpressionBase> array;
    std::shared_ptr<ExpressionBase> index;
};


#endif //MINI_JAVA_COMPILER_EXPRESSIONINDEX_H
