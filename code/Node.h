#ifndef NODE_H__
#define NODE_H__

#include<iostream>
#include<memory>
#include<string>

using namespace std;

class Node {
  public:

  Node(string inWord);
  ~Node();
  
  //Setter for frequency
  void SetFrequency(int freq);

  //Getter for frequency
  int GetFrequency();

  //Setter for index
  void SetIndex(int newIndex);

  //Getter for index
  int GetIndex();

  //Setter for word
  void SetWord(string newWord);

  //Getter for word
  string GetWord();

  //Getter for alphabet index
  shared_ptr<Node> GetAlphabetIndex(int index);

  //This function will take the pointer to a node and an int representing a char a-z
  //adding a node if necessary and returning the node located at that int index
  shared_ptr<Node> UpdateCursor(shared_ptr<Node> currNode, int index);

  private:

  int index; //tracks height of node within Trie/# of letters so far
  int frequency; //tracks frequency of complete words within text
  shared_ptr<Node> alphabet[26]; //Directs to children, index is letter
  string word;

};

#endif // TRIE_H__