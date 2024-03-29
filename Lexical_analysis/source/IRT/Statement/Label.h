//
// Created by nikolai on 24.11.19.
//
#pragma once

#include "IRTStatementBase.h"


class Label : public IRTStatementBase {
public:
    Label(std::string label_) : label(label_){
    };

    const std::string& GetLabel(){
        return label;
    }

    int Accept(Visitor* visitor);

private:
    std::string label;

};
