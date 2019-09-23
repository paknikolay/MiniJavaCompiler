//
// Created by nikolai on 23.09.19.
//

#include "Forest.h"

bool Forest::Node::operator<(const Node& other) const {
    return name < other.name;
}

const int Forest::GetNumberOfNeighbours(const string& name) const {
    return forest.at(name).first.size();
}

bool Forest::AddVertice(const string& name) {
    Node* current = new Node(name);
    auto key_node = forest.find(name);
    if (key_node != forest.end()) {
        delete current;
        return false;
    }

    forest.insert({name, std::make_pair(set<Node*> (), pool.size())});
    pool.push_back(current);
}

bool Forest::AddEdge(const string& from, const string& to) {
    auto key_from_node = forest.find(from);
    auto key_to_node = forest.find(to);

    if (key_from_node == forest.end() or key_to_node == forest.end()) {
        return false;
    }

    key_from_node->second.first.insert(pool[key_to_node->second.second]);
}

void Forest::Dump(FILE* filename) const {
    fprintf(filename, "digraph {");
    for (auto iter = forest.begin(); iter != forest.end(); ++iter) {
        if (iter == forest.begin()) {
            fprintf(filename, "\n");
        }
        fprintf(filename, "    %s -> {", iter->first.c_str());
        for (auto neighbour = iter->second.first.begin(); neighbour != iter->second.first.end(); ++neighbour) {
            fprintf(filename, "%s", (*neighbour)->name.c_str());
            if (neighbour != (--iter->second.first.end())) {
                fprintf(filename, " ");
            }
        }
        fprintf(filename, "}\n");
    }
    fprintf(filename, "}");
}

Forest::~Forest() {
    for (auto it = pool.begin(); it != pool.end(); ++it) {
        delete *it;
    }
}