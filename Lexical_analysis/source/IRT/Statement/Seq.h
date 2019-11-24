//
// Created by nikolai on 24.11.19.
//
#pragma once

#include "IRTStatementBase.h"

class Seq : public IRTStatementBase{
public:
    Seq(
            const std::shared_ptr<IRTStatementBase>& left,
            const std::shared_ptr<IRTStatementBase>& right
        )
        : right(right), left(left)
        {
        }


private:
    std::shared_ptr<IRTStatementBase> left;
    std::shared_ptr<IRTStatementBase> right;
};

