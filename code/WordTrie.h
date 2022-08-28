#ifndef TRIE_H__
#define TRIE_H__

#include <string>
#include <memory>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "Node.h"
#include "PriorityQueue.h"

using namespace std;

class WordTrie{
  public:
  WordTrie();
  ~WordTrie();

  //clears and resets the roots 
  void ClearTrie();
  void ClearFilter();
  void ClearCustom();


  //Getter for roots
  shared_ptr<Node> GetRoot();
  shared_ptr<Node> GetFilterRoot();
  shared_ptr<Node> GetCustomRoot();

  //Adds supplied string to collectedText
  void AddToCollectedText(string sentence);

  //Getter for collectedText
  string GetCollectedText();

  //Inserts a new word into the trie. If word exists, increment frequency. If not, create node with frequency 1
  shared_ptr<Node> Insert(shared_ptr<Node> root, string newWord);

  //Parses a .txt document, inserting the contained words into the trie
  void ParseDocument(shared_ptr<Node> root, string filename);

  //Parses a string, inserting contained words into a trie
  void ParseString(shared_ptr<Node> root, string textToParse, string targetWord);

  //compiles entire Trie into a priority queue and returns a shared pointer to the queue
  shared_ptr<pq> EnqueueTrie(shared_ptr<Node> root); 

  //creates a trie that contains inconsequential words for filtering
  void CreateFilter(string dictName);

  //compile internal Trie of specified word into priority queue
  shared_ptr<pq> EnqueueCustomTrie(string targetWord);

  //Returns frequency of a specific word in Trie
  int WordCount(shared_ptr<Node> root, string targetWord);

  //Prints a stylized representation of the top 25 most frequent words.
  //Provide string argument to print a cloud in relation to that word
  void PrintWordCloud(string targetWord = "");

  private:
 
  string collectedText;
  shared_ptr<Node> root;
  shared_ptr<Node> filterRoot;
  shared_ptr<Node> customRoot;

  //Returns the node where TargetWord belongs
  shared_ptr<Node> Find(shared_ptr<Node> root, string& targetWord);

  //Helper function to process each sentence or phrase
  //iterates through strings in sentence vector, adding them to the appropriate trie
  //if adding to the main trie, will also store the sentence itself with each word
  //for later processing
  void ProcessSentence(shared_ptr<Node> root, vector<string> sentence);

  //Helper function to recursively search for and enqueue nodes
  void RecursiveEnqueue(shared_ptr<pq> triePQ, shared_ptr<Node> root, PriorityQueue PQ);
  
  //helper function to test if character is letter, apostrophe, or dash
  bool IsPartOfWord(char& currChar);
  
  //Determines if a word is present in the specified Trie
  bool InTrie(shared_ptr<Node> root, string word);

  //Helper function to output correct number of stars
  string NumberStars(int wordFreq, int topFreq);

  //Helper function that determines if a word is contained in a vector
  bool ContainsWord(string& targetWord, vector<string> sentence);

};

#endif // TRIE_H__