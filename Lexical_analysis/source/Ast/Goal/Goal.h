//
// Created by malik on 26.10.2019.
//

#ifndef MINI_JAVA_COMPILER_GOAL_H
#define MINI_JAVA_COMPILER_GOAL_H

#include <vector>

#include "../MainClass/MainClass.h"
#include "../ClassDeclaration/ClassDeclaration.h"
#include "../BaseNode.h"

class Goal: public BaseNode {
public:
    Goal(std::pair<int, int> pos_, const std::shared_ptr<MainClass>& main) : main_class(main)
    {
        SetPosition(pos_);
    }
    Goal(std::pair<int, int> pos_, const std::shared_ptr<MainClass>& main, const std::vector<std::shared_ptr<ClassDeclaration>> classes
        ) :
            main_class(main),
            class_declarations(classes)
    {
        SetPosition(pos_);
    }

    const std::shared_ptr<MainClass> &GetMainClass() const {
        return main_class;
    }

    const std::vector<std::shared_ptr<ClassDeclaration>> &GetClassDeclarations() const {
        return class_declarations;
    }

    int Accept(Visitor* v);
private:
    std::shared_ptr<MainClass> main_class;
    std::vector<std::shared_ptr<ClassDeclaration>> class_declarations;
};

#endif //MINI_JAVA_COMPILER_GOAL_H
