//
// Created by nikolai on 22.10.19.
//

#ifndef MINI_JAVA_COMPILER_EXPRESSIONFUNCTIONCALL_H
#define MINI_JAVA_COMPILER_EXPRESSIONFUNCTIONCALL_H

#include "Expression/ExpressionBase.h"
#include <vector>
#include <memory>

class ExpressionFunctionCall : public ExpressionBase{
public:
    ExpressionFunctionCall(std::unique_ptr<ExpressionBase> &object,
                           std::vector<std::unique_ptr<ExpressionBase>> &args) : object(object.release()), args(args) {}

private:
    std::unique_ptr<ExpressionBase> object;
    std::vector<std::unique_ptr<ExpressionBase>> args;
};


#endif //MINI_JAVA_COMPILER_EXPRESSIONFUNCTIONCALL_H
