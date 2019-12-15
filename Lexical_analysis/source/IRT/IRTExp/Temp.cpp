//
// Created by nikolai on 24.11.19.
//

#include "Temp.h"
#include "../IRTDotVisitor.h"

int Temp::Accept(Visitor *v) {
    return v->Visit(this);
}