//
// Created by nikolai on 24.11.19.
//
#pragma once

#include "../IRTNodeBase.h"
#include <memory>

class IRTStatementBase : public IRTNodeBase{

};

class StmList {
private:
    std::shared_ptr<IRTStatementBase> head = nullptr;
    std::shared_ptr<StmList> tail = nullptr;
public:
    StmList(std::shared_ptr<IRTStatementBase> head_, std::shared_ptr<StmList> tail_) : head(head_), tail(tail_) {}
};