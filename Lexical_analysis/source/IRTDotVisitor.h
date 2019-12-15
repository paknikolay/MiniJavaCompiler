//
// Created by nikolai on 10.12.19.
//

#pragma once

#include <fstream>

#include "IRT/IRTNodeBase.h"
#include "IRT/Statement/IRTStatement.h"
#include "IRT/IRTExp/IRTExp.h"
#include "Visitor.h"



class IRTDotVisitor : public Visitor {
private:
    int n = 0;          // Номер вершины при обходе.
    std::ofstream& f;    // Файл, в который будет печататься дерево.
public:
    explicit
    IRTDotVisitor(std::ofstream& f_, IRTNodeBase* base) : f(f_){
        n = 0;
        f << "digraph tree {\n";
        base->Accept(this);
        f << "}";
    }

    void IncN() {
        ++n;
    }


    int DrawSubtree(IRTNodeBase* node);

    int Visit(Arg* node);
    int Visit(BinOp* node);
    int Visit(Call* node);
    int Visit(Const* node);
    int Visit(ESeq* node);
    int Visit(IRTExpBase* node);
    int Visit(Local* node);
    int Visit(Mem* node);
    int Visit(Name* node);
    int Visit(Temp* node);
    int Visit(ExpList* node);
    int Visit(Label* node);
    int Visit(Seq* node);
    int Visit(Move* node);


    int Visit(CJump* node);
    //int Visit(Jump);
    int Visit(Jump* node);
//    int Visit(Label* node);
//    int Visit(Move* node);
//    int Visit(NOP* node);
};

