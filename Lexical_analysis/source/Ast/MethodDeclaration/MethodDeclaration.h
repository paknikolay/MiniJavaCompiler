#pragma once

#include <string>
#include <vector>
#include <memory>

#include "../BaseNode.h"
#include "../../Enums.h"
#include "../Type/Type.h"
#include "../VarDeclaration/VarDeclaration.h"
#include "../Statement/Statements.h"
#include "../Expression/ExpressionBase.h"

class MethodBody : public BaseNode {
public:
    MethodBody(const std::vector<std::shared_ptr<VarDeclaration>>& vars,
               const std::vector<std::shared_ptr<StatementBase>>& statements,
               const std::shared_ptr<ExpressionBase>& returnExpr) :
                  vars(vars),
                  statements(statements),
                  returnExpr(returnExpr)
    {}

    MethodBody(const std::vector<std::shared_ptr<StatementBase>>& statements,
               const std::shared_ptr<ExpressionBase>& returnExpr) :
            statements(statements),
            returnExpr(returnExpr)
    {}

    MethodBody(const std::vector<std::shared_ptr<VarDeclaration>>& vars,
               const std::shared_ptr<ExpressionBase>& returnExpr) :
            vars(vars),
            returnExpr(returnExpr)
    {}
    MethodBody(const std::shared_ptr<ExpressionBase>& returnExpr) :
            returnExpr(returnExpr)
    {}


    const std::vector<std::shared_ptr<VarDeclaration>> &GetVars() const {
        return vars;
    }

    const std::vector<std::shared_ptr<StatementBase>> &GetStatements() const {
        return statements;
    }

    const std::shared_ptr<ExpressionBase> &GetReturnExpr() const {
        return returnExpr;
    }
  
  int Accept(Visitor* v);

private:
    std::vector<std::shared_ptr<VarDeclaration>> vars;
    std::vector<std::shared_ptr<StatementBase>> statements;
    std::shared_ptr<ExpressionBase> returnExpr;
};


class MethodDeclaration : public BaseNode {
public:
    MethodDeclaration(EModifier privacyModifier,
                      const std::shared_ptr<Type> &returnType,
                      const std::string &methodName,
                      const std::shared_ptr<MethodBody> &methodBody,
                      const std::vector<std::pair<std::shared_ptr<Type>, std::string>> &args =
                              std::vector<std::pair<std::shared_ptr<Type>, std::string>>()
                      ) :
                          privacyModifier(privacyModifier),
                          returnType(returnType),
                          methodName(methodName),
                          args(args),
                          methodBody(methodBody)
    {}

    EModifier GetPrivacyModifier() const {
        return privacyModifier;
    }

    const std::shared_ptr<Type> &GetReturnType() const {
        return returnType;
    }

    const std::string &GetMethodName() const {
        return methodName;
    }

    const std::vector<std::pair<std::shared_ptr<Type>, std::string>> &GetArgs() const {
        return args;
    }


    std::vector<std::string> GetArgsTypes() const {
        std::vector<std::string> types;
        for (auto pair : args) {
            types.push_back(pair.first->getTypeName());
            if (pair.first->GetType() == Type::EType ::STANDARD_TYPE_ARRAY) {
                types.back().append("[]");
            }
        }
        return types;
    }

    const std::shared_ptr<MethodBody> &GetMethodBody() const {
        return methodBody;
    }

  int Accept(Visitor* v);
  
private:
    EModifier privacyModifier;
    std::shared_ptr<Type> returnType;
    std::string methodName;
    std::vector<std::pair<std::shared_ptr<Type>, std::string>> args;
    std::shared_ptr<MethodBody> methodBody;
};