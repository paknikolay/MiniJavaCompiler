//
// Created by nikolai on 24.11.19.
//
#pragma once

#include "IRTExpBase.h"


class Const : public IRTExpBase{
    int value;
public:
    Const(int value) : value(value) {}
};

