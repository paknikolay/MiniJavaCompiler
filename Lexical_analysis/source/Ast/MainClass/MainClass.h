//
// Created by malik on 26.10.2019.
//
#pragma once

#include <memory>
#include <string>
#include "../Statement/Statements.h"
#include "../BaseNode.h"

class MainClass : public BaseNode {
public:
    MainClass(const std::string& name, const std::string& a_name, const std::shared_ptr<StatementBase>& stat) :
    class_name(name), args_name(a_name), statement(stat) {
        int a = 4;
    }
    MainClass() {}

    const std::string &GetClassName() const {
        return class_name;
    }

    const std::string &GetArgsName() const {
        return args_name;
    }

    const std::shared_ptr<StatementBase> &GetStatement() const {
        return statement;
    }

    int Accept(Visitor* v);

private:
    std::string class_name;
    std::string args_name;
    std::shared_ptr<StatementBase> statement;
};

