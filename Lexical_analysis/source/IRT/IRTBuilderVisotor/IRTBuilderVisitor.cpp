//
// Created by nikolai on 24.11.19.
//

#include "IRTBuilderVisitor.h"


int IRTBuilderVisitor::Visit(ExpressionBinOp* node) {
    node->GetLeft()->Accept(this);
    std::shared_ptr<IRTExpBase> leftChild = std::dynamic_pointer_cast<IRTExpBase>(lastResult);
    node->GetRight()->Accept(this);
    std::shared_ptr<IRTExpBase> rightChild = std::dynamic_pointer_cast<IRTExpBase>(lastResult);

    auto rez  = std::make_shared<BinOp>(node->GetBinOp(), leftChild, rightChild);
    //считаем, что они имеют один тип
    rez->SetRetType(leftChild->GetRetType());
    lastResult = rez;
    return 0;
}

int IRTBuilderVisitor::Visit(ExpressionBool* node) {
    lastResult = std::make_shared<Const>(Const(node->GetValue() ? 1 : 0));
    return 0;
}


int IRTBuilderVisitor::Visit(ExpressionFunctionCall* node) {

    node->GetObject()->Accept(this);
    auto func = std::dynamic_pointer_cast<IRTExpBase>(lastResult);

    std::vector<std::shared_ptr<ExpressionBase>> args = node->GetArgs();
    std::vector<std::shared_ptr<IRTExpBase>> argsParsed;
    //кладем указатель на объект в начало(this для вызываемой функции)
    argsParsed.push_back(func);
    std::vector<std::string> types;
    for (auto& arg : args) {
        arg->Accept(this);
        auto param = std::dynamic_pointer_cast<IRTExpBase>(lastResult);
        argsParsed.push_back(param);
        types.push_back(param->GetRetType());
    }

    auto b = symbolTable->GetClass(func->GetRetType());
    auto retType = symbolTable->GetClass(func->GetRetType())->GetMethod(node->GetName(), types)->GetTypeName();
    auto funcCall = std::make_shared<Call>(std::make_shared<Name>(node->GetName()), std::make_shared<ExpList>(argsParsed));
    funcCall->SetRetType(retType);
    lastResult = funcCall;
    return 0;
}

int IRTBuilderVisitor::Visit(ExpressionGetLength* node) {
    node->GetContainer()->Accept(this);
    //добавляем this в начало
    auto container = std::make_shared<ExpList>(std::dynamic_pointer_cast<IRTExpBase>(lastResult));

    auto rez = std::make_shared<Call>(std::make_shared<Name>("length"), container);
    rez->SetRetType("int");
    lastResult = rez;
    return 0;
}


int IRTBuilderVisitor::Visit(ExpressionInt* node) {
    auto rez = std::make_shared<Const>(Const(node->GetValue()));
    rez->SetRetType("int");
    lastResult = rez;
    return 0;
}



int IRTBuilderVisitor::Visit(ExpressionThis*) {
    //так как this - 0й аргумент
    auto exprThis = std::make_shared<Arg>(0);
    exprThis->SetRetType(curClass);
    lastResult =  exprThis;
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
    auto rez = std::make_shared<BinOp>(EBinOp::PLUS, array, index);
    //только массивы интов
    rez->SetRetType("int");
    this->lastResult = rez;
    return 0;
}

int IRTBuilderVisitor:: Visit(ExpressionNegation* node) {
    //xor with 1=0
    auto false_xor = std::dynamic_pointer_cast<IRTExpBase>(std::make_shared<Const>(0));

    node->GetValue()->Accept(this);

    auto to_neg = std::dynamic_pointer_cast<IRTExpBase>(this->lastResult);

    auto rez = std::make_shared<BinOp>(EBinOp::XOR, to_neg, false_xor);
    rez->SetRetType(to_neg->GetRetType());
    this->lastResult = rez;
    return 0;
}

int IRTBuilderVisitor::Visit(ExpressionNewIdentifier* node) {

    int size = symbolTable->GetClass(node->GetIdentifier())->GetSize();
    auto size_shared = std::make_shared<Const>(size);
    std::vector<std::shared_ptr<IRTExpBase>> list;
    list.push_back(size_shared);
    auto args = std::make_shared<ExpList>(list);


    auto malloc = std::make_shared<Name>("call");

    auto call = std::make_shared<Call>(malloc, args);


    lastResult = call;
    std::string registerLabel = getNextRegister();
    auto registr = std::make_shared<Temp>(registerLabel);

    auto mem = std::make_shared<Move>(registr, call);

    auto registr_return = std::make_shared<Temp>(registerLabel);

    auto rez = std::make_shared<ESeq>(registr_return, mem);
    rez->SetRetType(node->GetIdentifier());
    lastResult = rez;
    return 0;
}


int IRTBuilderVisitor::Visit(ExpressionNewIntArray* node) {

    node->GetCount()->Accept(this);

    auto temp_size = std::dynamic_pointer_cast<IRTExpBase>(lastResult);

    std::vector<std::shared_ptr<IRTExpBase>> list;
    list.push_back(temp_size);
    auto args = std::make_shared<ExpList>(list);


    auto malloc = std::make_shared<Name>("call");

    auto call = std::make_shared<Call>(malloc, args);


    lastResult = call;
    std::string registerLabel = getNextRegister();
    auto registr = std::make_shared<Temp>(registerLabel);

    auto mem = std::make_shared<Move>(registr, call);

    auto registr_return = std::make_shared<Temp>(registerLabel);

    auto rez = std::make_shared<ESeq>(registr_return, mem);
    rez->SetRetType("int[]");
    lastResult = rez;
    return 0;
}


std::shared_ptr<IRTExpBase> IRTBuilderVisitor::getAddressOfVariable(std::string identifier) {
    std::shared_ptr<IRTExpBase> rez(nullptr);
    auto varInfo = methodTable->GetVariable(identifier);
    if (varInfo == nullptr)
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



int IRTBuilderVisitor::Visit(StatementPrint* node) {
    node->GetExpression()->Accept(this);
    auto expr = std::make_shared<ExpList>(std::dynamic_pointer_cast<IRTExpBase>(lastResult));
    lastResult = std::make_shared<Call>(std::make_shared<Name>("print"), expr);

    return 0;
}

//if is empty lasResult contains nullptr
void IRTBuilderVisitor::handleStatementArray(const std::vector<std::shared_ptr<StatementBase>>& array){

    if (array.empty()) {
        lastResult = std::shared_ptr<IRTNodeBase>(0);
        return;
    }

    if(array.size() == 1) {
        array[0]->Accept(this);
        return;
    }

    array[0]->Accept(this);
    auto statement1 = std::dynamic_pointer_cast<IRTStatementBase>(lastResult);
    array[1]->Accept(this);
    auto statement2 = std::dynamic_pointer_cast<IRTStatementBase>(lastResult);

    auto seq = std::make_shared<Seq>(statement1, statement2);

    for (int iter = 2; iter < array.size(); iter++) {
        array[iter]->Accept(this);
        auto statement = std::dynamic_pointer_cast<IRTStatementBase>(lastResult);
        seq = std::make_shared<Seq>(seq, statement);
    }

    lastResult = seq;

}

//if is empty lasResult contains nullptr
int IRTBuilderVisitor::Visit(StatementSequence* node) {

    auto& array = node->GetArray();

    handleStatementArray(array);

    return 0;
}


//do nothing, skip
int IRTBuilderVisitor::Visit(Type*){
    return 0;
}
// skip
int IRTBuilderVisitor::Visit(VarDeclaration*){
    return 0;
}

int IRTBuilderVisitor::Visit(MethodBody* node){

    handleStatementArray(node->GetStatements());

    return 0;
}

int IRTBuilderVisitor::Visit(MethodDeclaration* node) {
    auto argsType = node->GetArgsTypes();
    methodTable = symbolTable->GetClass(curClass)->GetMethod(node->GetMethodName(), argsType);

    node->GetMethodBody()->Accept(this);

    FuncInfo f(curClass, argsType, node->GetMethodName(), lastResult);
    irtTrees.push_back(f);
    return 0;
}
int IRTBuilderVisitor::Visit(ClassDeclaration* node) {
    curClass = node->GetClassName();
    for (auto& method : node->GetMethods()) {
        method->Accept(this);

    }
}
int IRTBuilderVisitor::Visit(MainClass* node) {
    curClass = node->GetClassName();
    std::vector<std::string> argsType;
    argsType.emplace_back("String[]");

    methodTable = symbolTable->GetClass(curClass)->GetMethod("main", argsType);
    node->GetStatement()->Accept(this);
    irtTrees.emplace_back(FuncInfo(curClass, argsType, "main", lastResult));
}

int IRTBuilderVisitor::Visit(Goal* node) {

    node->GetMainClass()->Accept(this);

    for (auto& class_decl : node->GetClassDeclarations()) {
        class_decl->Accept(this);
    }

}