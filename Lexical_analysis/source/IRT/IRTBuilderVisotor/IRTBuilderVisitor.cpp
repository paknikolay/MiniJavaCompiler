//
// Created by nikolai on 24.11.19.
//

#include "IRTBuilderVisitor.h"
#include "IRT/IRTExp/Const.h"
#include "IRT/IRTExp/Name.h"
#include "IRT/IRTExp/BINOP.h"


int IRTBuilderVisitor::Visit(ExpressionBinOp* node) {
    Visit(node->GetLeft().get());
    std::shared_ptr<IRTNodeBase> leftChild = lastResult;
    Visit(node->GetRight().get());
    std::shared_ptr<IRTNodeBase> rightChild = lastResult;
    lastResult = std::make_shared<BinOp>(node->GetBinOp(), leftChild, rightChild);
    return 0;
}

int IRTBuilderVisitor::Visit(ExpressionIdentifier* node) {
    lastResult = std::make_shared<Name>(Name(node->GetValue()));
    return 0;
}

int IRTBuilderVisitor::Visit(ExpressionInt* node) {
    lastResult = std::make_shared<Const>(Const(node->GetValue()));
    return 0;
}