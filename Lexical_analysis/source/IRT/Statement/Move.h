//
// Created by nikolai on 24.11.19.
//

#pragma once

#include "IRTStatementBase.h"
#include "../IRTExp/IRTExp.h"


class Move : public  IRTStatementBase {
public:

    Move(const std::shared_ptr<IRTExpBase>& dst, const std::shared_ptr<IRTExpBase>& src)
      : dst(dst),
        src(src)
    {
    }

    std::shared_ptr<IRTExpBase> GetSrc() {
        return src;
    }

    std::shared_ptr<IRTExpBase> GetDst() {
        return dst;
    }

    int Accept(Visitor* v);


private:
    std::shared_ptr<IRTExpBase> src;
    std::shared_ptr<IRTExpBase> dst;

};
