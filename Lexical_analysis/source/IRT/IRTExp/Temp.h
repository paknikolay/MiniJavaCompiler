//
// Created by nikolai on 24.11.19.
//

#pragma once

#include "IRTExpBase.h"

class Temp : public IRTExpBase {
public:
    Temp(const std::string& temp_) : temp(temp_) {

    }

    std::string GetString() {
        return temp;
    }

    int Accept(Visitor* visit);

private:
    std::string temp;
};

