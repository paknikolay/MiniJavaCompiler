//
// Created by nikolai on 22.10.19.
//

#ifndef MINI_JAVA_COMPILER_EXPRESSIONFUNCTIONCALL_H
#define MINI_JAVA_COMPILER_EXPRESSIONFUNCTIONCALL_H

#include "ExpressionBase.h"
#include <vector>
#include <memory>

class ExpressionFunctionCall : public ExpressionBase{
public:
    ExpressionFunctionCall(std::pair<int, int> pos_,
                           const std::shared_ptr<ExpressionBase> &object,
                           const std::string& name_,
                           const std::vector<std::shared_ptr<ExpressionBase>> &args_) : object(object),
                           name(name_) {
        SetPosition(pos_);

        args.resize(args_.size());
        for (size_t i = 0; i < args_.size(); ++i) {
            args[i] = std::shared_ptr<ExpressionBase>(args_[i]);
        }
    }

    ExpressionFunctionCall(std::pair<int, int> pos_, const std::shared_ptr<ExpressionBase> &object, const std::string& name_) : object(object),
    name(name_) {
        SetPosition(pos_);
    }
    
    const std::shared_ptr<ExpressionBase>& GetObject() const { return object; };
    const std::string& GetName() const { return name; }
    const std::vector<std::shared_ptr<ExpressionBase>>& GetArgs() const { return args; };
    int Accept(Visitor* v);
private:
    std::shared_ptr<ExpressionBase> object;
    std::string name;
    std::vector<std::shared_ptr<ExpressionBase>> args;
};


#endif //MINI_JAVA_COMPILER_EXPRESSIONFUNCTIONCALL_H
