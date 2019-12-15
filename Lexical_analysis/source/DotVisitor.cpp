//
// Created by Илья on 27.10.2019.
//

#include "DotVisitor.h"
#include <vector>
#include <sstream>


void DotVisitor::DrawTree(const std::shared_ptr<BaseNode>& node, const std::string& filename)
{
    n = 0;
    f.open(filename);
    f << "digraph tree {\n";
    DrawSubtree(node);
    f << "}";
    f.close();
}

int DotVisitor::DrawSubtree(const std::shared_ptr<BaseNode>& node)
{
    ++n;
    if (node) {
        return node->Accept(this);
    } else {
        return VisitEmpty();
    }
}

int DotVisitor::VisitEmpty()
{
    f << n << " [label=\"NULL\"]\n";
    return n;
}

//////////////////////////////////////////////////////
//Обрабатываем Expressions

int DotVisitor::Visit(ExpressionBinOp* node)
{
    std::vector<std::string> bin_ops = {"+", "-", "*", "/", "%", "||", "&&", "!=", "==", "<=", ">=", "<", ">"};
    f << n << " [label=\"" << bin_ops[static_cast<int>(node->GetBinOp())] << "\"]\n";
    int number = n;
    std::stringstream s;
    s << number << " -> {" << DrawSubtree(node->GetLeft()) << ", " << DrawSubtree(node->GetRight()) << "}\n";
    f << s.str();
    return number;
}

int DotVisitor::Visit(ExpressionBool* node)
{
    f << n << " [label=\"bool " << node->GetValue() << "\"]\n";
    return n;
}

int DotVisitor::Visit(ExpressionFunctionCall* node)
{
    f << n << " [label=\"call " << node->GetName() << "\"]\n";
    int number = n;
    std::stringstream s;
    s << number << " -> " << DrawSubtree(node->GetObject()) << " [label=\"object\"]\n";
    for (auto arg : node->GetArgs()) {
        s << number << " -> "  << DrawSubtree(arg) << " [label=\"arg\"]\n";
    }
    f << s.str();
    return number;
}

int DotVisitor::Visit(ExpressionGetLength* node)
{
    f << n << " [label=\"length\"]\n";
    int number = n;
    std::stringstream s;
    s << number << " -> " << DrawSubtree(node->GetContainer()) << " [label=\"container\"]\n";
    f << s.str();
    return number;
}

int DotVisitor::Visit(ExpressionIdentifier* node)
{
    f << n << " [label=\"id " << node->GetIdentifier() << "\"]\n";
    return n;
}

int DotVisitor::Visit(ExpressionIndex* node)
{
    f << n << " [label=\"index\"]\n";
    int number = n;
    std::stringstream s;
    s << number << " -> " << DrawSubtree(node->GetArray()) << " [label=\"array\"]\n";
    s << number << " -> " << DrawSubtree(node->GetIndex()) << " [label=\"index\"]\n";
    f << s.str();
    return number;
}

int DotVisitor::Visit(ExpressionInt* node)
{
    f << n << " [label=\"int " << node->GetValue() << "\"]\n";
    return n;
}

int DotVisitor::Visit(ExpressionNegation* node)
{
    f << n << " [label=\"!\"]\n";
    int number = n;
    std::stringstream s;
    s << number << " -> " << DrawSubtree(node->GetValue()) << " [label=\"value\"]\n";
    f << s.str();
    return number;
}

int DotVisitor::Visit(ExpressionNewIdentifier* node)
{
    f << n << " [label=\"new " << node->GetIdentifier() << "\"]\n";
    return n;
}

int DotVisitor::Visit(ExpressionNewIntArray* node)
{
    f << n << " [label=\"new int[]\"]\n";
    int number = n;
    std::stringstream s;
    s << number << " -> " << DrawSubtree(node->GetCount()) << " [label=\"count\"]\n";
    f << s.str();
    return number;
}

int DotVisitor::Visit(ExpressionThis* node)
{
    f << n << " [label=\"this " << "\"]\n";
    return n;
}

//////////////////////////////////////////////////////
//Обрабатываем Statements

int DotVisitor::Visit(StatementIf* node)
{
    f << n << " [label=\"if\"]\n";
    int number = n;
    std::stringstream s;
    s << number << " -> " << DrawSubtree(node->GetIfExpression()) << " [label=\"expr\"]\n";
    s << number << " -> " << DrawSubtree(node->GetIfStatement()) << " [label=\"if stat\"]\n";
    s << number << " -> " << DrawSubtree(node->GetElseStatement()) << " [label=\"else stat\"]\n";
    f << s.str();
    return number;
}

int DotVisitor::Visit(StatementWhile* node)
{
    f << n << " [label=\"while\"]\n";
    int number = n;
    std::stringstream s;
    s << number << " -> " << DrawSubtree(node->GetWhileExpression()) << " [label=\"expr\"]\n";
    s << number << " -> " << DrawSubtree(node->GetWhileStatement()) << " [label=\"stat\"]\n";
    f << s.str();
    return number;
}

int DotVisitor::Visit(StatementAssign* node)
{
    f << n << " [label=\"" << node->GetIdentifier() << " = \"]\n";
    int number = n;
    std::stringstream s;
    s << number << " -> " << DrawSubtree(node->GetExpression()) << " [label=\"expr\"]\n";
    f << s.str();
    return number;
}

int DotVisitor::Visit(StatementAssignContainerElement* node)
{
    f << n << " [label=\"" << node->GetIdentifier() << "[] = \"]\n";
    int number = n;
    std::stringstream s;
    s << number << " -> " << DrawSubtree(node->GetIndex()) << " [label=\"index\"]\n";
    s << number << " -> " << DrawSubtree(node->GetExpression()) << " [label=\"expr\"]\n";
    f << s.str();
    return number;
}

int DotVisitor::Visit(StatementPrint* node)
{
    f << n << " [label=\"print\"]\n";
    int number = n;
    std::stringstream s;
    s << number << " -> " << DrawSubtree(node->GetExpression()) << " [label=\"expr\"]\n";
    f << s.str();
    return number;
}

int DotVisitor::Visit(StatementSequence* node)
{
    f << n << " [label=\"seq of stats\"]\n";
    int number = n;
    std::stringstream s;
    for (auto st : node->GetArray()) {
        s << number << " -> " << DrawSubtree(st) << "\n";
    }
    f << s.str();
    return number;
}

//////////////////////////////////////////////////////
//Обрабатываем всё остальное

int DotVisitor::Visit(Type* node)
{
    std::vector<std::string> type_name = {"standard type", "standard type array", "identifier"};
    f << n << " [label=\"" << type_name[static_cast<int>(node->GetType())] << " " << node->getTypeName() << "\"]\n";
    return n;
}

int DotVisitor::Visit(VarDeclaration* node)
{
    f << n << " [label=\"var " << node->GetName() << "\"]\n";
    int number = n;
    std::stringstream s;
    s << number << " -> " << DrawSubtree(node->GetType()) << " [label=\"type\"]\n";
    f << s.str();
    return number;
}

int DotVisitor::Visit(MethodBody* node)
{
    f << n << " [label=\"method body\"]\n";
    int number = n;
    std::stringstream s;
    for (auto var : node->GetVars()) {
        s << number << " -> " << DrawSubtree(var) << " [label=\"vars\"]\n";
    }
    for (auto st : node->GetStatements()) {
        s << number << " -> " << DrawSubtree(st) << " [label=\"stat\"]\n";
    }
    s << number << " -> " << DrawSubtree(node->GetReturnExpr()) << " [label=\"ret\"]\n";
    f << s.str();
    return number;
}

int DotVisitor::Visit(MethodDeclaration* node)
{
    std::vector<std::string> modifier = {"public", "private"};
    f << n << " [label=\"" << modifier[static_cast<int>(node->GetPrivacyModifier())] << " method declaration"
      << node->GetMethodName() << "\"]\n";
    int number = n;
    std::stringstream s;
    s << number << " -> " << DrawSubtree(node->GetReturnType()) << " [label=\"ret type\"]\n";

    for (auto arg : node->GetArgs()) {
        s << number << " -> " << DrawSubtree(arg.first) << "[label = \"arg " << arg.second << "\"]\n";
    }

    s << number << " -> " << DrawSubtree(node->GetMethodBody()) << " [label=\"body\"]\n";
    f << s.str();
    return number;
}

int DotVisitor::Visit(ClassDeclaration* node)
{
    f << n << " [label=\"class " << node->GetClassName() << " extends " << node->GetExtends() << "\"]\n";
    int number = n;
    std::stringstream s;
    for (auto var : node->GetVars()) {
        s << number << " -> " << DrawSubtree(var) << "[label = \"var\"]\n";
    }
    for (auto method : node->GetMethods()) {
        s << number << " -> " << DrawSubtree(method) << "[label = \"method\"]\n";
    }
    f << s.str();
    return number;
}

int DotVisitor::Visit(MainClass* node)
{
    f << n << " [label=\"main class " << node->GetClassName() << "(" << node->GetArgsName() << ")\"]\n";
    int number = n;
    std::stringstream s;
    s << number << " -> " << DrawSubtree(node->GetStatement()) << "[label = \"stat\"]\n";
    f << s.str();
    return number;
}

int DotVisitor::Visit(Goal* node)
{
    f << n << " [label=\"goal\"]\n";
    int number = n;
    std::stringstream s;
    s << number << " -> " << DrawSubtree(node->GetMainClass()) << "[label = \"main class\"]\n";

    for (const auto& cl : node->GetClassDeclarations()) {
        s << number << " -> " << DrawSubtree(cl) << "[label = \"class\"]\n";
    }
    f << s.str();
    return number;
}