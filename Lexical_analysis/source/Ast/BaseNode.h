//
// Created by nikolai on 22.10.19.
//

#ifndef MINI_JAVA_COMPILER_BASENODE_H
#define MINI_JAVA_COMPILER_BASENODE_H


class Visitor; // forward-declaration

class BaseNode {
public:
    virtual int Accept(Visitor* v);
};


#endif //MINI_JAVA_COMPILER_BASENODE_H
