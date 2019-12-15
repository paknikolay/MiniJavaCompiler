//
// Created by nikolai on 24.11.19.
//
#include "Arg.h"
#include "../IRTDotVisitor.h"

int Arg::Accept(Visitor *v) {
    return v->Visit(this);
}
