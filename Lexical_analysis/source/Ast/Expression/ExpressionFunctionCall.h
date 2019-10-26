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
    ExpressionFunctionCall(std::shared_ptr<ExpressionBase> &object,
                           std::vector<std::shared_ptr<ExpressionBase>> &args_) : object(object){
        args.resize(args_.size());
        for (size_t i = 0; i < args_.size(); ++i) {
            args[i] = std::shared_ptr<ExpressionBase>(args_[i]);
        }
    }

    const std::shared_ptr<ExpressionBase>& GetObject(){ return object; };
    const std::vector<std::shared_ptr<ExpressionBase>>& GetArgs(){ return args; };
private:
    std::shared_ptr<ExpressionBase> object;
    std::vector<std::shared_ptr<ExpressionBase>> args;
};


#endif //MINI_JAVA_COMPILER_EXPRESSIONFUNCTIONCALL_H
