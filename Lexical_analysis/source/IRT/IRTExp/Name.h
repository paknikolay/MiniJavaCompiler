//
// Created by nikolai on 24.11.19.
//
#pragma once

#include "IRTExpBase.h"


class Name : public IRTExpBase{
    string value;
public:
    Name(string value) : value(value) {}
};

