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
    lastResult = std::make_shared<Name>(Name(node->GetIdentifier()));
    return 0;
}

int IRTBuilderVisitor::Visit(ExpressionInt* node) {
    lastResult = std::make_shared<Const>(Const(node->GetValue()));
    return 0;
}

int IRTBuilderVisitor::Visit(StatementIf* node) {
    node->GetIfExpression()->Accept(this);
    auto expr = std::dynamic_pointer_cast<IRTExpBase>(lastResult);

    auto labEnd = std::make_shared<Label>(getNextLabel());


    // ifStatementLabel ifStatement jump(EndLabel)
    node->GetIfStatement()->Accept(this);
    auto labIf = std::make_shared<Label>(getNextLabel());
    auto ifStatement = std::make_shared<Seq>(labIf, std::dynamic_pointer_cast<IRTStatementBase>(lastResult));
    ifStatement = std::make_shared<Seq>(ifStatement, std::make_shared<Jump>(labEnd->GetLabel()));

    // elseStatementLabel elseStatement jump(EndLabel)
    node->GetElseStatement()->Accept(this);
    auto labElse = std::make_shared<Label>(getNextLabel());
    auto elseStatement = std::make_shared<Seq>(labElse, std::dynamic_pointer_cast<IRTStatementBase>(lastResult));
    elseStatement = std::make_shared<Seq>(elseStatement, std::make_shared<Jump>(labEnd->GetLabel()));


    auto ifExp = std::make_shared<CJump>(EBinOp::AND, expr, std::make_shared<Const>(1), labIf->GetLabel(), labElse->GetLabel());

    auto ifExpIfSt = std::make_shared<Seq>(ifExp, elseStatement);
    auto ifExpIfStElseSt = std::make_shared<Seq>(ifExpIfSt, ifStatement);

    auto ifExpIfStElseStEndLabel = std::make_shared<Seq>(ifExpIfStElseSt, labEnd);
    lastResult = ifExpIfStElseStEndLabel;


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
    whileStatement = std::make_shared<Seq>(labBody, whileStatement);
    //labExp: if (exp) {body... goto labExp} else {goto labEnd}   :labEnd

    //jump должно выполнятся последним
    auto whileCycle = std::make_shared<Jump>(labExp->GetLabel());

    //if(expr) goto labBody else goto End
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

std::shared_ptr<IRTExpBase> IRTBuilderVisitor::getAddressOfVariable(std::string identifier) {
    std::shared_ptr<IRTExpBase> rez(0);

    auto varInfo = methodTable->GetVariable(identifier);
    if (methodTable->GetVariableScope(identifier) == TypeScope::ARGUMENT) {
        rez = std::make_shared<Arg>(varInfo->position);
    } else {
        rez = std::make_shared<Local>(identifier);
    }

    return rez;
}

int IRTBuilderVisitor::Visit(StatementAssign* node) {

    node->GetExpression()->Accept(this);
    auto expr = std::dynamic_pointer_cast<IRTExpBase>(lastResult);
    auto memExpr = std::make_shared<Mem>(expr);


    auto dst = getAddressOfVariable(node->GetIdentifier());

    lastResult = std::make_shared<Move>(dst, memExpr);

    return 0;
}

int IRTBuilderVisitor::Visit(StatementAssignContainerElement* node) {
    node->GetExpression()->Accept(this);
    auto expr = std::dynamic_pointer_cast<IRTExpBase>(lastResult);
    auto memExpr = std::make_shared<Mem>(expr);

    node->GetIndex()->Accept(this);
    auto index = std::dynamic_pointer_cast<IRTExpBase>(lastResult);

    auto varInfo = methodTable->GetVariable(node->GetIdentifier());

    auto dst = getAddressOfVariable(node->GetIdentifier());

    auto binOp = std::make_shared<BinOp>(EBinOp::PLUS, dst, index);

    auto memBinOp = std::make_shared<Mem>(binOp);

    lastResult = std::make_shared<Move>(memBinOp, memExpr);

    return 0;
}

