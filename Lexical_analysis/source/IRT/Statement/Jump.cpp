//
// Created by nikolai on 27.11.19.
//

#include "Jump.h"
#include "../IRTDotVisitor.h"

int Jump::Accept(Visitor *v) {
    return v->Visit(this);
}
