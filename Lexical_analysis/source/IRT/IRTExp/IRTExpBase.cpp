//
// Created by nikolai on 24.11.19.
//

#include "IRTNodeBase.h"
#include "../IRTDotVisitor.h"
#include "IRTExpBase.h"


int ExpList::Accept(Visitor *v) {
    return v->Visit(this);
}

int IRTExpBase::Accept(Visitor *visit) {
    return 0;
}
