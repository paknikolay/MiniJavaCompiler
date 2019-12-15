//
// Created by nikolai on 24.11.19.
//
#include "Name.h"
#include "../IRTDotVisitor.h"

int Name::Accept(Visitor *v) {
    return v->Visit(this);
}
