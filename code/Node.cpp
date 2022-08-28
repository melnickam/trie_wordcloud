#include "Node.h"

Node::Node(string inWord){
    index = 0;
    frequency = 0;
    for (int i = 0; i < 26; i++){
        alphabet[i] = NULL;
    }
    word = inWord;
}

Node::~Node(){};

void Node::SetFrequency(int freq){
  frequency = freq;
}

int Node::GetFrequency(){
    return frequency;
}

void Node::SetIndex(int newIndex){
    index = newIndex;
}

int Node::GetIndex(){
    return index;
}

void Node::SetWord(string newWord){
    word = newWord;
}

string Node::GetWord(){
    return word;
}

shared_ptr<Node> Node::GetAlphabetIndex(int index){
    return alphabet[index];
}



shared_ptr<Node> Node::UpdateCursor(shared_ptr<Node> currNode, int letter){
    if (currNode->alphabet[letter] == NULL){ //if no Node occupies the space
      shared_ptr<Node> newNode(new Node("")); //make new node
      currNode->alphabet[letter] = newNode; //place new node in correct spot
      currNode = newNode; //update cursor
    }
    else { //if node does occupy the space
      currNode = currNode->alphabet[letter];
    }
    return currNode;
}