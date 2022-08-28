#ifndef MENUFUNCS_H__
#define MENUFUNCS_H__

#include <string>
#include <memory>
#include <iostream>
#include <sys/types.h>
#include <dirent.h>
#include "WordTrie.h"

using namespace std;

class MenuFuncs {

  public:
  
  MenuFuncs();
  ~MenuFuncs();

  //Function that will print menu
  void PrintMenu(shared_ptr<WordTrie> wordTrie);

  //Getter for menuTrie
  shared_ptr<WordTrie> GetTrie();

  //Looped selection function
  void MainMenuSelect(int selection = 0);

  //Performs selected function...
  //1 disables or enables the filter
  //2 Parses a document into the trie
  //3 Prints the main word cloud
  //4 Prints the word cloud associated with the supplied string
  //5 Clears the main trie or custom trie
  //6 Quits the program
  void PerformFunction(int selection);
  
  private:
  
  shared_ptr<WordTrie> menuTrie;

  void PrintAvailableDocs();

};

#endif // MENUFUNCS_H__