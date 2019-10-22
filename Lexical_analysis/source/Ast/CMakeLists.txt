add_library(Ast STATIC Expression/ExpressionBase.cpp Expression/ExpressionBinOp.cpp Expression/ExpressionBool.cpp
        Expression/ExpressionFunctionCall.cpp Expression/ExpressionGetLength.cpp Expression/ExpressionIdentifier.cpp
        Expression/ExpressionIndex.cpp Expression/ExpressionInt.cpp Expression/ExpressionNegation.cpp
        Expression/ExpressionNewIdentifier.cpp Expression/ExpressionThis.cpp Expression/ExpressionNewIntArray.cpp
        BaseNode.cpp
        )

target_include_directories(Ast PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_library(CMakeExample::Ast ALIAS Ast)
