//
// Created by nikolai on 22.10.19.
//

#ifndef MINI_JAVA_COMPILER_BASENODE_H
#define MINI_JAVA_COMPILER_BASENODE_H

#include <string>

class Visitor; // forward-declaration

struct Position {
    int line = 0, column = 0;

    std::string ToString() {
        return "line  = " + std::to_string(line) + ", column = " + std::to_string(column);
    }
};

class BaseNode {
public:
    virtual int Accept(Visitor* v);
    virtual Position GetPosition() {
        return {0, 0};
    }
};


#endif //MINI_JAVA_COMPILER_BASENODE_H
