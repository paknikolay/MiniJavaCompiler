//
// Created by nikolai on 24.11.19.
//

#include "IRTBuilderVisitor.h"
#include "Statement/IRTStatement.h"
#include "IRTExp/IRTExp.h"

int IRTBuilderVisitor::Visit(ExpressionBinOp* node) {
    node->GetLeft()->Accept(this);
    std::shared_ptr<IRTNodeBase> leftChild = lastResult;
    node->GetRight()->Accept(this);
    std::shared_ptr<IRTNodeBase> rightChild = lastResult;
    lastResult = std::make_shared<BinOp>(node->GetBinOp(), std::dynamic_pointer_cast<IRTExpBase>(leftChild),
                                         std::dynamic_pointer_cast<IRTExpBase>(rightChild));
    return 0;
}

int IRTBuilderVisitor::Visit(ExpressionBool* node) {
    lastResult = std::make_shared<Const>(Const(node->GetValue() ? 1 : 0));
    return 0;
}


int IRTBuilderVisitor::Visit(ExpressionFunctionCall* node) {
    node->GetObject()->Accept(this);
    std::shared_ptr<IRTNodeBase> func = lastResult;

    std::vector<std::shared_ptr<ExpressionBase>> args = node->GetArgs();
    std::vector<std::shared_ptr<IRTExpBase>> argsParsed;
    for (auto arg : args) {
        arg->Accept(this);
        argsParsed.push_back(std::dynamic_pointer_cast<IRTExpBase>(lastResult));
    }

    lastResult = std::make_shared<Call>(std::dynamic_pointer_cast<IRTExpBase>(func), std::make_shared<ExpList>(argsParsed));
    return 0;
}

int IRTBuilderVisitor::Visit(ExpressionGetLength* node) {
    node->GetContainer()->Accept(this);
    std::shared_ptr<IRTNodeBase> str = lastResult;

    lastResult = std::make_shared<Call>(std::dynamic_pointer_cast<IRTExpBase>(str), std::dynamic_pointer_cast<ExpList>(node->GetContainer()));
    return 0;
}

int IRTBuilderVisitor::Visit(ExpressionIdentifier* node) {
    lastResult = std::make_shared<Name>(node->GetIdentifier());
    return 0;
}

int IRTBuilderVisitor::Visit(ExpressionInt* node) {
    lastResult = std::make_shared<Const>(node->GetValue());
    return 0;
}