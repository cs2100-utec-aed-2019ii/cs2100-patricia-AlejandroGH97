#include "Trie.h"

using namespace std;

int main(){
    Trie* trie = new Trie();

    trie->insert("hola");
    trie->insert("hols");
    trie->insert("holitas");
    // cout<<trie->search("hola")<<"\n";
    // cout<<trie->prefix("hol")<<"\n";
    // cout<<"\n";
    // trie->print();
    // trie->deleteWord("hola");
    // cout<<trie->search("hola")<<"\n";
    // cout<<trie->search("hols")<<"\n";
    // cout<<"\n";
    trie->print();

    trie->patricia();
    
    cout<<"\n";

    trie->print();


    return 0;
}