//
// Created by nikolai on 24.11.19.
//

#pragma once

#include "IRTExpBase.h"

class ESeq : public IRTExpBase {

public:
    ESeq(std::shared_ptr<IRTExpBase> expr_, std::shared_ptr<IRTStatementBase> stat_) :
    expr(expr_), stat(stat_) {

    }

    int Accept(Visitor* v);

    std::shared_ptr<IRTExpBase> GetExpr() {
        return expr;
    }

    std::shared_ptr<IRTStatementBase> GetStat() {
        return stat;
    }

private:
    std::shared_ptr<IRTExpBase> expr;
    std::shared_ptr<IRTStatementBase> stat;
};
