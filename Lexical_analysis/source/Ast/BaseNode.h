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
    Position(std::pair<int, int> pos) : line(pos.first), column(pos.second) {}
    Position() {}
};

class BaseNode {
public:
    virtual int Accept(Visitor* v);
    virtual Position GetPosition() {
        return pos;
    }
    virtual void SetPosition(std::pair<int, int> pos_) {
        pos = std::move(Position(pos_));
    }
    BaseNode(std::pair<int, int> pos_) {
        SetPosition(pos_);
    }
    BaseNode() {}


    Position pos;
};


#endif //MINI_JAVA_COMPILER_BASENODE_H
