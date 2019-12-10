//
// Created by nikolai on 24.11.19.
//
#include "Const.h"
#include "../IRTDotVisitor.h"

int Const::Accept(Visitor *v) {
    return v->Visit(this);
}
