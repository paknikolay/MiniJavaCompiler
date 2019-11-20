//
// Created by nikolai on 22.10.19.
//

#pragma once

class Visitor; // forward-declaration

class BaseNode {
public:
    virtual int Accept(Visitor* v);
};

