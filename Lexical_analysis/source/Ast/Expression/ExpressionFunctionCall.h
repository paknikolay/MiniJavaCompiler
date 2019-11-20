//
// Created by nikolai on 22.10.19.
//
#pragma once

#include "ExpressionBase.h"
#include <vector>
#include <memory>

class ExpressionFunctionCall : public ExpressionBase{
public:
    ExpressionFunctionCall(const std::shared_ptr<ExpressionBase> &object,
                           const std::string& name_,
                           const std::vector<std::shared_ptr<ExpressionBase>> &args_) : object(object),
                           name(name_) {
        args.resize(args_.size());
        for (size_t i = 0; i < args_.size(); ++i) {
            args[i] = std::shared_ptr<ExpressionBase>(args_[i]);
        }
    }

    ExpressionFunctionCall(const std::shared_ptr<ExpressionBase> &object, const std::string& name_) : object(object),
    name(name_) {
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


