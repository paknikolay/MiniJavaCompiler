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

//int IRTBuilderVisitor::Visit(ExpressionIdentifier* node) {
//    lastResult = std::make_shared<Name>(Name(node->GetIdentifier()));
//    return 0;
//}

int IRTBuilderVisitor::Visit(ExpressionInt* node) {
    lastResult = std::make_shared<Const>(Const(node->GetValue()));
    return 0;
}

int IRTBuilderVisitor::Visit(StatementIf* node) {
    node->GetIfExpression()->Accept(this);
    auto expr = std::dynamic_pointer_cast<IRTExpBase>(lastResult);

    node->GetIfStatement()->Accept(this);
    auto labIf = std::make_shared<Label>(getNextLabel());
    auto ifStatement = std::make_shared<Seq>(std::dynamic_pointer_cast<IRTStatementBase>(lastResult), labIf);


    node->GetElseStatement()->Accept(this);
    auto labElse = std::make_shared<Label>(getNextLabel());
    auto elseStatement = std::make_shared<Seq>(std::dynamic_pointer_cast<IRTStatementBase>(lastResult), labElse);


    auto ifExp = std::make_shared<CJump>(EBinOp::AND, expr, std::make_shared<Const>(1), labIf->GetLabel(), labElse->GetLabel());

    auto ifExpIfSt = std::make_shared<Seq>(ifExp, elseStatement);
    auto ifExpIfStElseSt = std::make_shared<Seq>(ifExpIfSt, ifStatement);

    lastResult = ifExpIfStElseSt;


    return 0;
}

int IRTBuilderVisitor::Visit(StatementWhile* node) {
    node->GetWhileExpression()->Accept(this);
    auto expr = std::dynamic_pointer_cast<IRTExpBase>(lastResult);

    auto labExp = std::make_shared<Label>(getNextLabel());
    auto labEnd = std::make_shared<Label>(getNextLabel());
    auto labBody = std::make_shared<Label>(getNextLabel());
    node->GetWhileStatement()->Accept(this);
    auto whileStatement = std::dynamic_pointer_cast<IRTStatementBase>(lastResult);

    //labExp: if (exp) {body...} else {goto labEnd}  goto labExp :labEnd

    //while(true) должно выполнятся последним
    auto whileCycle = std::make_shared<CJump>(EBinOp::OR, std::make_shared<Const>(1), std::make_shared<Const>(1), labExp->GetLabel(), labExp->GetLabel());

    //if(expr)
    auto whileIf = std::make_shared<CJump>(EBinOp::AND, expr, std::make_shared<Const>(1), labBody->GetLabel(), labEnd->GetLabel());

    //Expr: if(expr)
    auto bodyIf = std::make_shared<Seq>(labExp, whileIf);

    //Expr: if(expr) {body}
    auto whileIfBody = std::make_shared<Seq>(bodyIf, whileStatement);
    //Expr: if(expr) {body} goto labExpr
    auto whileBodyCycle = std::make_shared<Seq>(whileIfBody, whileCycle);
    //Expr: if(expr) {body} goto labExpr : labEnd
    auto whileBodyCycleEnd = std::make_shared<Seq>(whileBodyCycle, labEnd);

    lastResult = whileBodyCycleEnd;

    return 0;
}

int IRTBuilderVisitor::Visit(ExpressionIdentifier *node) {
    auto element = this->methodTable->GetVariableScope(node->GetIdentifier());
    auto variable = this->methodTable->GetVariable(node->GetIdentifier());
    if (element == TypeScope::ARGUMENT) {
        this->lastResult = std::make_shared<Arg>(variable->position);
    } else {
        this->lastResult = std::make_shared<Local>(node->GetIdentifier());
    }

    std::dynamic_pointer_cast<IRTExpBase>(this->lastResult)->SetRetType(
            variable->type_name
    );

    return 0;
}

int IRTBuilderVisitor::Visit(ExpressionIndex* node) {
    node->GetArray()->Accept(this);
    auto array = std::dynamic_pointer_cast<IRTExpBase>(this->lastResult);
    node->GetIndex()->Accept(this);
    auto index = std::dynamic_pointer_cast<IRTExpBase>(this->lastResult);
    this->lastResult = std::make_shared<BinOp>(EBinOp::PLUS, array, index);
    return 0;
}

int IRTBuilderVisitor:: Visit(ExpressionNegation* node) {
    //xor with 1=0
    auto false_xor = std::dynamic_pointer_cast<IRTExpBase>(std::make_shared<Const>(0));

    node->GetValue()->Accept(this);

    auto to_neg = std::dynamic_pointer_cast<IRTExpBase>(this->lastResult);

    this->lastResult = std::make_shared<BinOp>(EBinOp::XOR, to_neg, false_xor);

    return 0;
}

int IRTBuilderVisitor::Visit(ExpressionThis *node) {
    this->lastResult = std::make_shared<Arg>(0);
    return 0;
}
/*
int IRTBuilderVisitor::Visit(ExpressionNewIdentifier* node) {

    int size = symbolTable->GetClass(node->GetIdentifier()).;
    auto size_shared = std::shared_ptr<Const>(size);

    return 0;
}
 */