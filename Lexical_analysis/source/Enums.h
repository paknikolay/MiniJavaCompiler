#pragma once

enum class EModifier {
    PUBLIC,
    PRIVATE
};

enum class EBool {
    TRUE,
    FALSE
};

enum class EBinOp {
    PLUS,
    MINUS,
    MUL,
    DIV,
    MOD,
    OR,
    AND,
    NEQ, // !=
    EQ, // ==
    LE, // <=
    GE, // >=
    L, // <
    G // >
};