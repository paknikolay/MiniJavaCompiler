//
// Created by nikolai on 24.11.19.
//

#include "IRTBuilderVisitor.h"
#include "../IRT/IRTExp/Const.h"
#include "../IRT/IRTExp/Name.h"
#include "../IRT/IRTExp/BinOp.h"
#include "../IRTExp/IRTExp.h"
#include "Statement/IRTStatement.h"


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