//
// Created by nikolai on 24.11.19.
//
#pragma once

#include "IRTExpBase.h"

class Arg : IRTExpBase{
    int index;
public:
    Arg(int index) : index(index) {}
};
