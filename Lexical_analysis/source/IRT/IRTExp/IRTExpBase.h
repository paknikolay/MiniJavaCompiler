//
// Created by nikolai on 24.11.19.
//

#pragma once

#include <string>

#include "../Statement/IRTStatementBase.h"

class IRTExpBase : public IRTStatementBase {
public:

    std::string GetRetType() {
        return ret_type;
    }

private:
    std::string ret_type;

};
