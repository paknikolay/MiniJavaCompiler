//
// Created by nikolai on 10.12.19.
//

#include "IRTDotVisitor.h"
#include <sstream>

int Visit(CJump* node) {

}


int IRTDotVisitor::Visit(Arg* node)
{
    ++n;
    f << n << " [label=\"ARG\"]\n";
    int number = n;
    std::stringstream s;
    ++n;
    f << n << " [label = \"INT\" (" << node->GetIndex() << ")]\n";
    s << number << " -> " << n << "\n";

    f << s.str();
    return number;
}

int IRTDotVisitor::Visit(BinOp* node)
{
    ++n;
    std::vector<std::string> bin_ops = {"+", "-", "*", "/", "%", "^", "||", "&&", "!=", "==", "<=", ">=", "<", ">"};
    f << n << " [label=\" BINOP \"]\n";
    int number = n;

    ++n;
    int binop_num = n;
    f << binop_num << " [label=\" int binop (" << bin_ops[static_cast<int>(node->GetBinOp())] << ") \"]\n";


    std::stringstream s;
    s << number << " -> {" << binop_num  << ", " << node->GetLeft()->Accept(this) << ", " << node->GetRight()->Accept(this) << "}\n";
    f << s.str();
    return number;
}

int IRTDotVisitor::Visit(Call* node)
{
    ++n;
    int num = n;
    f << num<< " [label = \"Call\"]\n";


    std::stringstream s;
    s << num << " -> {" << node->GetFunc()->Accept(this)  << ", " << node->GetList()->Accept(this) << "}\n";
    f << s.str();
    return num;
}

int IRTDotVisitor::Visit(Const* node)
{
    ++n;
    f << n << " [label=\"int( " << node->GetValue() << ")\"]\n";
    int number = n;
    ++n;
    f << n << "[label=\"Const\"]\n";
    std::stringstream s;
    s << n << " -> " << number << "\n";
    f << s.str();
    return number;
}

int IRTDotVisitor::Visit(Local* node)
{
    ++n;
    f << n << " [label=\"string( " << node->GetString() << ")\"]\n";
    int number = n;
    ++n;
    f << n << "[label=\"Local\"]\n";
    std::stringstream s;
    s << n << " -> " << number << "\n";
    f << s.str();
    return number;
}

int IRTDotVisitor::Visit(ESeq* node)
{
    ++n;
    int num = n;
    f << num<< " [label = \"Eseq\"]\n";


    std::stringstream s;
    s << num << " -> {" << node->GetExpr()->Accept(this)  << ", " << node->GetStat()->Accept(this) << "}\n";
    f << s.str();
    return num;
}

int IRTDotVisitor::Visit(Mem* node)
{
    ++n;
    f << n << " [label=\"Mem\"]\n";
    int number = n;
    std::stringstream s;
    s << number << " -> " << node->GetExpr()->Accept(this) << "\n";
    f << s.str();
    return number;
}

int IRTDotVisitor::Visit(Name* node)
{
    ++n;
    f << n << " [label=\"string( " << node->GetString() << ")\"]\n";
    int number = n;
    ++n;
    f << n << "[label=\"Name\"]\n";
    std::stringstream s;
    s << n << " -> " << number << "\n";
    f << s.str();
    return number;
}

int IRTDotVisitor::Visit(Temp* node)
{
    ++n;
    f << n << " [label=\"string( " << node->GetString() << ")\"]\n";
    int number = n;
    ++n;
    f << n << "[label=\"Temp\"]\n";
    std::stringstream s;
    s << n << " -> " << number << "\n";
    f << s.str();
    return number;
}


int IRTDotVisitor::Visit(ExpList* node)
{
    ++n;
    f << n << " [label=\"new ExpList\"]\n";
    int number = n;

    std::stringstream s;
    if (node->GetHead() != nullptr) {
        s << number << " -> " << node->GetHead()->Accept(this) << " [label=\"head\"]\n";
    }

    if (node->GetTail() != nullptr) {
        s << number << " -> " << node->GetTail()->Accept(this) << " [label=\"tail\"]\n";
    }

    f << s.str();
    return number;
}
