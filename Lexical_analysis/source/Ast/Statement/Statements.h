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

    const std::shared_ptr<ExpressionBase> &GetIfExpression() const {
        return ifExpression;
    }

    const std::shared_ptr<StatementBase> &GetIfStatement() const {
        return ifStatement;
    }

    const std::shared_ptr<StatementBase> &GetElseStatement() const {
        return elseStatement;
    }

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

    const std::shared_ptr<ExpressionBase> &GetWhileExpression() const {
        return whileExpression;
    }

    const std::shared_ptr<StatementBase> &GetWhileStatement() const {
        return whileStatement;
    }

private:
    std::shared_ptr<ExpressionBase> whileExpression;
    std::shared_ptr<StatementBase> whileStatement;

};

//////////////////////////////////////////////

class StatementAssign : public StatementBase {
public:
    StatementAssign(const std::string& identifier,
                    const std::shared_ptr<ExpressionBase>& expression):
                        identifier(identifier),
                        expression(expression)
    {}

    const std::string &GetIdentifier() const {
        return identifier;
    }

    const std::shared_ptr<ExpressionBase> &GetExpression() const {
        return expression;
    }

private:
    std::string identifier;
    std::shared_ptr<ExpressionBase> expression;
};


//////////////////////////////////////////////

class StatementAssignContainerElement : public StatementBase {
public:
    StatementAssignContainerElement(const std::string& identifier,
                                    const std::shared_ptr<ExpressionBase>& index,
                                    const std::shared_ptr<ExpressionBase>& expression):
                        identifier(identifier),
                        index(index),
                        expression(expression)
    {}

    const std::string &GetIdentifier() const {
        return identifier;
    }

    const std::shared_ptr<ExpressionBase> &GetIndex() const {
        return index;
    }

    const std::shared_ptr<ExpressionBase> &GetExpression() const {
        return expression;
    }

private:
    std::string identifier;
    std::shared_ptr<ExpressionBase> index;
    std::shared_ptr<ExpressionBase> expression;
};


//////////////////////////////////////////////

class StatementPrint : public StatementBase {
public:
    StatementPrint(const std::shared_ptr<ExpressionBase>& expression):
            expression(expression)
    {}

    const std::shared_ptr<ExpressionBase> &GetExpression() const {
        return expression;
    }

private:
    std::shared_ptr<ExpressionBase> expression;
};

//////////////////////////////////////////////

class StatementSequence : public StatementBase {
public:
    explicit
    StatementSequence(const std::vector<std::shared_ptr<StatementBase>>& statementArray) {array = statementArray;}

private:
    std::vector<std::shared_ptr<StatementBase>> array;
};
