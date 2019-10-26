#pragma once

#include "BaseNode.h"
#include "Expression/ExpressionBase.h"
#include "Expression/ExpressionIdentifier.h"

#include <memory>
#include <vector>

class StatementBase : public BaseNode{

};

//////////////////////////////////////

class StatementIf : public StatementBase {
public:
    StatementIf(const std::shared_ptr<ExpressionBase>& ifExpression,
                const std::shared_ptr<StatementBase>& ifStatement,
                const std::shared_ptr<StatementBase>& elseStatement):
                    ifExpression(ifExpression),
                    ifStatement(ifStatement),
                    elseStatement(elseStatement)
    {}

private:
    std::shared_ptr<ExpressionBase> ifExpression;
    std::shared_ptr<StatementBase> ifStatement;
    std::shared_ptr<StatementBase> elseStatement;

};

////////////////////////////////////////////

class StatementWhile : public StatementBase {
public:
    StatementWhile(const std::shared_ptr<ExpressionBase>& WhileExpression,
                   const std::shared_ptr<StatementBase>& WhileStatement):
                        whileExpression(whileExpression),
                        whileStatement(whileStatement)
    {}

private:
    std::shared_ptr<ExpressionBase> whileExpression;
    std::shared_ptr<StatementBase> whileStatement;

};

//////////////////////////////////////////////

class StatementAssign : public StatementBase {
public:
    StatementAssign(const std::shared_ptr<ExpressionIdentifier>& identifier,
                    const std::shared_ptr<ExpressionBase>& expression):
                        identifier(identifier),
                        expression(expression)
    {}


private:
    std::shared_ptr<ExpressionIdentifier> identifier;
    std::shared_ptr<ExpressionBase> expression;
};


//////////////////////////////////////////////

class StatementAssignContainerElement : public StatementBase {
public:
    StatementAssignContainerElement(const std::shared_ptr<ExpressionIdentifier>& identifier,
                                    const std::shared_ptr<ExpressionBase>& index,
                                    const std::shared_ptr<ExpressionBase>& expression):
                        identifier(identifier),
                        index(index),
                        expression(expression)
    {}


private:
    std::shared_ptr<ExpressionIdentifier> identifier;
    std::shared_ptr<ExpressionBase> index;
    std::shared_ptr<ExpressionBase> expression;
};


//////////////////////////////////////////////

class StatementPrint : public StatementBase {
public:
    StatementPrint(const std::shared_ptr<ExpressionBase>& expression):
            expression(expression)
    {}


private:
    std::shared_ptr<ExpressionBase> expression;
};

//////////////////////////////////////////////

class StatementSequence : public StatementBase {
public:
    StatementSequence(const std::shared_ptr<StatementBase>& statement) {array.push_back(statement);}
    StatementSequence() {}


private:
    std::vector<std::shared_ptr<StatementBase>> array;
};