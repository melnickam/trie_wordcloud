#include "MenuFuncs.h"

MenuFuncs::MenuFuncs(){
    shared_ptr<WordTrie> newTrie(new WordTrie);
    menuTrie = newTrie;
}

MenuFuncs::~MenuFuncs(){
}

void MenuFuncs::PrintMenu(shared_ptr<WordTrie> wordTrie){
    string filterStatus = wordTrie->GetFilterRoot()->GetWord();
      
    cout << "1) Enable/Disable filter (Filter is currently: " << filterStatus << ")" << endl;
    cout << "2) Add text to database" << endl;
    cout << "3) Print overall word cloud" << endl;
    cout << "4) Print custom word cloud" << endl;
    cout << "5) Clear database" << endl;
    cout << "6) Quit" << endl;
}

void MenuFuncs::MainMenuSelect(int selection){
  if(selection == 0){
    PrintMenu(GetTrie());
    cout << "Please select an option from 1-6:" << endl;
  }
  cin >> selection;  
  if (cin.fail()){
    string garbage;
    cin.clear(); //reset cin
    getline(cin, garbage); //clear garbage
  }
  else if (selection < 1 || selection > 6){ //if selection out of bounds
    string garbage;
    getline(cin, garbage); //clear garbage
  }
  else if (selection == 6){
    cout << "Quitting..." << endl;
    return;
  }
  else{
    PerformFunction(selection);
  }
  MainMenuSelect(0);
  return;
}

void MenuFuncs::PerformFunction(int selection){
  if (selection == 1){ //Filter off/on
    if (GetTrie()->GetFilterRoot()->GetWord() == "Off"){
      GetTrie()->CreateFilter("..//documents//badwords.txt");
    }
    else { //clear filter
      GetTrie()->ClearFilter();
    }
  }
  else if (selection ==2){
    string filename = "..//documents//";
    string inName;
    PrintAvailableDocs();
    cout << "Please enter the filename of the .txt file located in the /documents folder: " << endl;
    cout << "Example: littlewomen.txt" << endl;
    cin >> inName;
    filename = filename + inName;
    cout << "Attempting to open: " << filename << endl;
    GetTrie()->ParseDocument(GetTrie()->GetRoot(), filename);
  }
  else if (selection == 3){
    cout << endl << endl;
    GetTrie()->PrintWordCloud();
    cout << endl << endl;
  }
  else if (selection == 4){
    cout << "Please enter the word to act as nucleus of custom word cloud: " << endl;
    string targetWord;
    cin >> targetWord;
    cout << endl << endl;
    GetTrie()->PrintWordCloud(targetWord);
    GetTrie()->ClearCustom();
    cout << endl << endl;
  }
  else if (selection == 5){
    GetTrie()->ClearTrie();
  }
}

shared_ptr<WordTrie> MenuFuncs::GetTrie(){
  return menuTrie;
}

void MenuFuncs::PrintAvailableDocs(){
  cout << "The following documents are available: " << endl;
  vector<string> fileNames;
  DIR* dirPath = opendir("..//documents//");
  struct dirent * dp; //establish dirent object
  while ((dp = readdir(dirPath)) != NULL) { //iterate through folder
          fileNames.push_back(dp->d_name);
          //cout << dp->d_name << endl;
  }
  closedir(dirPath);
  fileNames.erase(fileNames.begin(),fileNames.begin()+2);
  for (auto it: fileNames){
    cout << it << endl;
  }
}