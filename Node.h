#include <vector>

using namespace std;
class Trie;

class Node{
private:
    friend class Trie;
    string state;
    vector<pair<string,Node*>> children;
public:
    Node();
    Node(string _state);
    ~Node();

    bool exists(string key){
        for(auto e: children){
            if(e.first == key){
                return true;
            }
        }
        return false;
    }

    void erase(string key){
        for(auto it = children.begin(); it != children.end();it++){
            if(it->first == key){
                children.erase(it);
                return;
            }
        }
    }

    pair<string,Node*> operator [](string key){
        for(auto e: children){
            if(e.first == key){
                return e;
            }
        }
    }
};

Node::Node(){
    this->state = "";
}

Node::Node(string _state){
    this->state = _state;
}

Node::~Node(){
}
