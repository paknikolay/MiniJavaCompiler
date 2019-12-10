//
// Created by nikolai on 24.11.19.
//
#pragma once

#include "IRTExpBase.h"
#include <memory>


class Call : public IRTExpBase{
    std::shared_ptr<IRTExpBase> func;
    std::shared_ptr<ExpList> args;
public:
    Call(const std::shared_ptr<IRTExpBase>& func_, const std::shared_ptr<ExpList>& args_) : func(func_), args(args_) {}
    int Accept(Visitor* v);

    std::shared_ptr<ExpList> GetList() {
        return args;
    }

    std::shared_ptr<IRTExpBase> GetFunc() {
        return func;
    }
};
