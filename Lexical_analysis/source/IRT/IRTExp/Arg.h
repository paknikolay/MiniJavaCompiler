//
// Created by nikolai on 24.11.19.
//
#pragma once

#include "IRTExpBase.h"

class Arg : public IRTExpBase{
    int index;
public:
    Arg(int index) : index(index) {}

    int GetIndex() {
        return index;
    }

    int Accept(Visitor *v);
};
