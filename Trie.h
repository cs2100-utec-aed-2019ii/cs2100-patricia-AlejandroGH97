#include <string>
#include <iostream>
#include <stack>
#include "Node.h"
#include <queue>

using namespace std;

typedef pair<string,Node*> child;

class Trie{
private:
    Node* root;
    
public:
    Trie();
    ~Trie();

    Node* getRoot(){return root;}

    void insert(string word);
    void deleteWord(string word);
    bool prefix(string word);
    bool search(string word);
    void print();
    void print(Node* node);

    void patricia();
};

Trie::Trie(){
    root = new Node();
}

Trie::~Trie(){
}

void Trie::insert(string word){
    Node* cur = root;
    int index = 0;
    while(index < word.size()){
        if(cur->exists(string(1,word[index]))){//key found
            cur = (*cur)[string(1,word[index])].second;
        }
        else{
            //cout<<"Created new node for: "<<word[index]<<"\n";
            cur->children.push_back(child(string(1,word[index]),new Node()));
            cur = (*cur)[string(1,word[index])].second;
        }
        index++;
    }
    cur->state = word;
}

void Trie::deleteWord(string word){
    Node* cur = root;
    int index = 0;
    stack<Node*> route;
    while(index < word.size()){
        if(cur->exists(string(1,word[index]))){//key found
            route.push(cur);
            cur = (*cur)[string(1,word[index])].second;
        }
        else{
            cout<<"Word not found.\n";
            return;
        }
        index++;
    }

    index--;
    cur->state = "";

    while(!route.empty()){
        if(cur->state == "" && cur->children.size() == 0){
            //cout<<"Deleting link to "<<word[index]<<"\n";
            delete cur;
            cur = route.top();
            route.pop();
            cur->erase(string(1,word[index]));
            index--;
        }
        if(cur->children.size() != 0){
            return;
        }
    }
    
}

bool Trie::prefix(string word){
    Node* cur = root;
    int index = 0;
    while(index < word.size()){
        if(cur->exists(string(1,word[index]))){//key found
            cur = (*cur)[string(1,word[index])].second;
        }
        else{
            return false;
        }
        index++;
    }
    return cur->state == "";
}

bool Trie::search(string word){
    Node* cur = root;
    int index = 0;
    while(index < word.size()){
        if(cur->exists(string(1,word[index]))){//key found
            cur = (*cur)[string(1,word[index])].second;
        }
        else{
            return false;
        }
        index++;
    }
    return cur->state == word;
}

void Trie::print(){
    if(!root){
        cout<<"Empty tree.\n";
        return;
    }
    Node* node = root;
    for(const auto pair: node->children){
        cout<<pair.first<<" ";
    }
    cout<<"\n";
    for(const auto pair: node->children){
        print((*node)[pair.first].second);
    }
}

void Trie::print(Node* node){
    for(const auto pair: node->children){
        cout<<pair.first<<" ";
    }
    cout<<"\n";
    for(const auto pair: node->children){
        print((*node)[pair.first].second);
    }
}

void Trie::patricia(){

    if(!root){
        cout<<"Empty tree.\n";
        return;
    }

    string new_key;
    Node* new_node = nullptr;

    Node* cur = nullptr;

    queue<Node*> nodes;

    nodes.push(root);

    while(!nodes.empty()){
        
        cur = nodes.front();
        
        nodes.pop();
        
        for(int it = 0; it < cur->children.size(); it++){
            cout<<"Optimizing link: "<<cur->children[it].first<<"\n";
            if(cur->children[it].second->children.size() == 1){
                new_key = cur->children[it].first + cur->children[it].second->children[0].first;
                cout<<"Created new key: "<<new_key<<"\n";    
                new_node = cur->children[it].second->children[0].second;
                cur->children.push_back({new_key,new_node});
                cur->children.erase(cur->children.begin()+it);
                it--;
            }
        }
        
        for(auto node: cur->children){
            nodes.push(node.second);
        }
    }


    

}