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
    OR,
    AND,
    NEQ, // !=
    EQ, // ==
    LE, // <=
    GE, // >=
    L, // <
    G // >
};