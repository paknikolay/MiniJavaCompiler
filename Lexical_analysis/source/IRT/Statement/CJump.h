//
// Created by nikolai on 24.11.19.
//

#pragma once

#include "../IRTExp/IRTExpBase.h"
#include "IRTStatementBase.h"
#include "../../Enums.h"

class CJump : public IRTStatementBase {
public:
    CJump(
            EBinOp binOp,
            const std::shared_ptr<IRTExpBase>& left,
            const std::shared_ptr<IRTExpBase>& right,
            const std::string& true_label,
            const std::string& false_label
         )
         : binOp(binOp),
           left(left),
           right(right),
           true_label(true_label),
           false_label(false_label)
    {
    }

private:
    EBinOp binOp;
    std::shared_ptr<IRTExpBase> left;
    std::shared_ptr<IRTExpBase> right;
    std::string true_label;
    std::string false_label;

};
