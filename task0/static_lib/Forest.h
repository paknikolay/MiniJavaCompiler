#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::map;
using std::vector;
using std::set;
using std::pair;

class Forest {
public:
    struct Node{
        string name;

        Node(const string name_) : name(name_) {}
        bool operator<(const Node& other) const;
    };

    bool AddVertice(const string& name);

    bool AddEdge(const string& from, const string& to);

    void Dump(FILE* filename) const;

    const int GetNumberOfNeighbours(const string& name) const;

    ~Forest();

private:
    map<string, pair<set<Node*>, int>> forest;
    vector<Node*> pool;
};

