//
// Created by nikolai on 10.12.19.
//

#pragma once

#include <fstream>

#include "IRT/IRTNodeBase.h"
#include "IRT/Statement/IRTStatement.h"
#include "IRT/IRTExp/IRTExp.h"



class IRTDotVisitor {
private:
    int n = 0;          // Номер вершины при обходе.
    std::ofstream& f;    // Файл, в который будет печататься дерево.
public:
    explicit
    IRTDotVisitor(std::ofstream& f) : f(f){}

    //int Visit(CJump* node);
};

