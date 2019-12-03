//
// Created by nikolai on 24.11.19.
//

#pragma once

#include "IRTExpBase.h"

class Local : public IRTExpBase{
public:
    Local(const std::string& value) : value_(value) {

    }
private:
    std::string value_;
};