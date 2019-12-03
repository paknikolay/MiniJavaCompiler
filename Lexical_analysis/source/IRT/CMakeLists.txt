add_library(Irt STATIC IRTNodeBase.cpp IRTExp/Temp.cpp IRTExp/IRTExpBase.cpp Statement/IRTStatementBase.cpp
        IRTExp/Call.cpp IRTExp/Const.cpp IRTExp/Arg.cpp IRTExp/BinOp.cpp IRTExp/ESeq.cpp
        IRTExp/Local.cpp IRTExp/Mem.cpp IRTExp/Name.cpp Statement/CJump.cpp Statement/Label.cpp
        Statement/Move.cpp Statement/Seq.cpp Statement/Jump.cpp
        IRTBuilderVisotor/IRTBuilderVisitor.cpp)


target_include_directories(Irt PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_library(CMakeExample::Irt ALIAS Irt)
