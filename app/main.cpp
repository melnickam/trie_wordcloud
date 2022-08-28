#include <iostream>
#include "../code/MenuFuncs.h"

using namespace std;

int main(){
    
  cout << "Welcome to the Word Box generator. This program will process .txt files and print word boxes of the most frequent words!" << endl << endl;
  
  MenuFuncs menu;
  menu.MainMenuSelect();

  return 0;
}