//
// Created by nikolai on 24.11.19.
//

#include "Local.h"
#include "../IRTDotVisitor.h"

int Local::Accept(Visitor *v) {
    return v->Visit(this);
}
