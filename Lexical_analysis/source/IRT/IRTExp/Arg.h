//
// Created by nikolai on 24.11.19.
//
#pragma once

#include "IRTExpBase.h"

class Arg : public IRTExpBase{
    int index_;
public:
    Arg(int index) : index_(index) {}
};
