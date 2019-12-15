#pragma once

#include "../BaseNode.h"
#include "../Expression/ExpressionBase.h"
#include "../Expression/ExpressionIdentifier.h"

#include <memory>
#include <vector>

class StatementBase : public BaseNode{

public:
    StatementBase(std::pair<int, int> pos_) {
        SetPosition(pos_);
    }

    StatementBase() {

    }
};

//////////////////////////////////////

class StatementIf : public StatementBase {
public:
    StatementIf(std::pair<int, int> pos_,
                const std::shared_ptr<ExpressionBase>& ifExpression_,
                const std::shared_ptr<StatementBase>& ifStatement_,
                const std::shared_ptr<StatementBase>& elseStatement_):
                    ifExpression(ifExpression_),
                    ifStatement(ifStatement_),
                    elseStatement(elseStatement_)
    {
        SetPosition(pos_);
    }

    const std::shared_ptr<ExpressionBase> &GetIfExpression() const {
        return ifExpression;
    }

    const std::shared_ptr<StatementBase> &GetIfStatement() const {
        return ifStatement;
    }

    const std::shared_ptr<StatementBase> &GetElseStatement() const {
        return elseStatement;
    }

    int Accept(Visitor* v);

private:
    std::shared_ptr<ExpressionBase> ifExpression;
    std::shared_ptr<StatementBase> ifStatement;
    std::shared_ptr<StatementBase> elseStatement;

};

////////////////////////////////////////////

class StatementWhile : public StatementBase {
public:
    StatementWhile(std::pair<int, int> pos_,
                   const std::shared_ptr<ExpressionBase>& WhileExpression,
                   const std::shared_ptr<StatementBase>& WhileStatement):
                        whileExpression(WhileExpression),
                        whileStatement(WhileStatement)
    {
        SetPosition(pos_);
    }

    const std::shared_ptr<ExpressionBase> &GetWhileExpression() const {
        return whileExpression;
    }

    const std::shared_ptr<StatementBase> &GetWhileStatement() const {
        return whileStatement;
    }

    int Accept(Visitor* v);

private:
    std::shared_ptr<ExpressionBase> whileExpression;
    std::shared_ptr<StatementBase> whileStatement;

};

//////////////////////////////////////////////

class StatementAssign : public StatementBase {
public:
    StatementAssign(std::pair<int, int> pos_,
                    const std::string& identifier,
                    const std::shared_ptr<ExpressionBase>& expression):
                        identifier(identifier),
                        expression(expression)
    {
        SetPosition(pos_);
    }

    const std::string &GetIdentifier() const {
        return identifier;
    }

    const std::shared_ptr<ExpressionBase> &GetExpression() const {
        return expression;
    }

    int Accept(Visitor* v);

private:
    std::string identifier;
    std::shared_ptr<ExpressionBase> expression;
};


//////////////////////////////////////////////

class StatementAssignContainerElement : public StatementBase {
public:
    StatementAssignContainerElement(std::pair<int, int> pos_,
                                    const std::string& identifier,
                                    const std::shared_ptr<ExpressionBase>& index,
                                    const std::shared_ptr<ExpressionBase>& expression):
                        identifier(identifier),
                        index(index),
                        expression(expression)
    {
        SetPosition(pos_);
    }

    const std::string &GetIdentifier() const {
        return identifier;
    }

    const std::shared_ptr<ExpressionBase> &GetIndex() const {
        return index;
    }

    const std::shared_ptr<ExpressionBase> &GetExpression() const {
        return expression;
    }

    int Accept(Visitor* v);

private:
    std::string identifier;
    std::shared_ptr<ExpressionBase> index;
    std::shared_ptr<ExpressionBase> expression;
};


//////////////////////////////////////////////

class StatementPrint : public StatementBase {
public:
    StatementPrint(std::pair<int, int> pos_, const std::shared_ptr<ExpressionBase>& expression):
            expression(expression)
    {
        SetPosition(pos_);
    }

    const std::shared_ptr<ExpressionBase> &GetExpression() const {
        return expression;
    }

    int Accept(Visitor* v);

private:
    std::shared_ptr<ExpressionBase> expression;
};

//////////////////////////////////////////////

class StatementSequence : public StatementBase {
public:
    explicit
    StatementSequence(std::pair<int, int> pos_, const std::vector<std::shared_ptr<StatementBase>>& statementArray) {
        SetPosition(pos_);
        array = statementArray;
    }

    const std::vector<std::shared_ptr<StatementBase>> &GetArray() const {
        return array;
    }

    int Accept(Visitor* v);

private:
    std::vector<std::shared_ptr<StatementBase>> array;
};
