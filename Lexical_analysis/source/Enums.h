#pragma once

enum class EModifier {
    PUBLIC,
    PRIVATE
};

enum class EBool {
    FALSE,
    TRUE
};

enum class EBinOp {
    PLUS,
    MINUS,
    MUL,
    DIV,
    MOD,
    XOR,
    OR,
    AND,
    NEQ, // !=
    EQ, // ==
    LE, // <=
    GE, // >=
    L, // <
    G // >
};

enum class TypeScope {
    ARGUMENT,
    LOCAL_VARIABLE,
    CLASS_VARIABLE
};