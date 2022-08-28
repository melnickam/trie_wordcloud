#include "WordTrie.h"

WordTrie::WordTrie(){
  shared_ptr<Node> newNode(new Node(""));
  root = newNode;
  shared_ptr<Node> newFilter(new Node("Off"));
  filterRoot = newFilter;
  shared_ptr<Node> newCustom(new Node(""));
  customRoot = newCustom;
  collectedText = "";
}

WordTrie::~WordTrie(){}

void WordTrie::ClearTrie(){
  shared_ptr<Node> newNode(new Node(""));
  root = newNode;
  collectedText = ""; //also clear collectedText
}

void WordTrie::ClearFilter(){
  shared_ptr<Node> newFilter(new Node("Off"));
  filterRoot = newFilter;
}

void WordTrie::ClearCustom(){
  shared_ptr<Node> newCustom(new Node(""));
  customRoot = newCustom;
}

shared_ptr<Node> WordTrie::GetRoot(){
    return root;
}

shared_ptr<Node> WordTrie::GetFilterRoot(){
    return filterRoot;
}

shared_ptr<Node> WordTrie::GetCustomRoot(){
    return customRoot;
}

void WordTrie::AddToCollectedText(string sentence){
  collectedText = collectedText + sentence;
}

string WordTrie::GetCollectedText(){
  return collectedText;
}

shared_ptr<Node> WordTrie::Insert(shared_ptr<Node> root, string newWord){
  shared_ptr<Node> targetNode = Find(root, newWord); //determines where to add or increment
  targetNode->SetFrequency(targetNode->GetFrequency()+1); //increment frequency
  if (targetNode->GetWord() == ""){ //if word hasn't been added yet
    targetNode->SetWord(newWord); //add word
    targetNode->SetIndex(newWord.length()); //set index 
  }
  return targetNode; 
}

void WordTrie::ParseDocument(shared_ptr<Node> root, string filename){
  ifstream inDoc;
  //open specified file
  inDoc.open(filename);
  //test if file is valid; return if not
  if (!inDoc){
    cout << "File not found or unable to open." << endl;
    return;
  }
  else {
    cout << "File opened successfully. Processing..." << endl;
  }
  int lastRound = 1; // counter to ensure last sentence is processed if no period
  char currChar; // holds current character in text file
  string currWord = ""; //holds current word
  string lastWord; //for testing special cases
  vector<string> currSentence; //holds word in current sentence
  while (inDoc >> std::noskipws >> currChar || lastRound-- > 0){
    if (lastRound == 0){
      currChar = '.';
    }
    if (IsPartOfWord(currChar)){ //test if character is a letter
      currWord = currWord + currChar; //if so, add to the current word
    }
    else { //if not, we've reached the end of the current word, add it to the current sentence
      if (currWord != ""){
        currSentence.push_back(currWord);
        lastWord = currWord; //to test for special cases.
        currWord = ""; //blank the current word
      }
      //now test if it is the end of the sentence and not a title
      if ((currChar == '.' && !(lastWord == "Mr" || lastWord == "Mrs")) || currChar == '!' || currChar == '?'){
        ProcessSentence(root, currSentence);
        currSentence.clear();
      }

      //if char isn't a letter or a sentence-ending punctuation mark, it should be skipped
    }
  }
  cout << "Operation Complete" << endl;
}

void WordTrie::ParseString(shared_ptr<Node> root, string textToParse, string targetWord){
  int lastRound = 1; // counter to ensure last sentence is processed if no period
  char currChar; // holds current character in text file
  string currWord = ""; //holds current word
  string lastWord; //for testing special cases
  vector<string> currSentence; //holds word in current sentence
  stringstream strStream(textToParse);
  while (strStream >> std::noskipws >> currChar || lastRound-- > 0){
    if (lastRound == 0){
      currChar = '.';
    }
    if (IsPartOfWord(currChar)){ //test if character is a letter
      currWord = currWord + currChar; //if so, add to the current word
    }
    else { //if not, we've reached the end of the current word, add it to the current sentence
      if (currWord != ""){
        currSentence.push_back(currWord);
        lastWord = currWord;
        currWord = ""; //blank the current word
      }
      //now test if it is the end of the sentence and not a title
      if ((currChar == '.' && !(lastWord == "Mr" || lastWord == "Mrs")) || currChar == '!' || currChar == '?'){
        //only add to trie if target word is part of sentence
        if (ContainsWord(targetWord, currSentence)){ 
          ProcessSentence(root, currSentence);
        }
        currSentence.clear();
      }

      //if char isn't a letter or a sentence-ending punctuation mark, it should be skipped
    }
  }
}

shared_ptr<pq> WordTrie::EnqueueTrie(shared_ptr<Node> root){
  PriorityQueue PQ; //for accessing priority queue functions
  shared_ptr<pq> triePQ = PQ.InitPriorityQueue(); //new queue object
  RecursiveEnqueue(triePQ, root, PQ); //this function will actually build the queue
  return triePQ;
}

void WordTrie::CreateFilter(string dictName){
  ParseDocument(GetFilterRoot(), dictName); //dictname is a list of words to be filtered
  GetFilterRoot()->SetWord("On");
}

shared_ptr<pq> WordTrie::EnqueueCustomTrie(string targetWord){
  if (!InTrie(GetRoot(), targetWord)){ //if supplied word is not in Trie, return null
    cout << targetWord<< " " << "not found in Trie. Unable to build sub-trie." << endl;
    return NULL;
  }
  shared_ptr<Node> targetNode = Find(GetRoot(), targetWord); //find the node to target
  ParseString(GetCustomRoot(), GetCollectedText(), targetWord); //turn string into trie located in customRoot
  return EnqueueTrie(GetCustomRoot());
}

int WordTrie::WordCount(shared_ptr<Node> root, string targetWord){
  shared_ptr<Node> targetNode = Find(root, targetWord);
  return targetNode->GetFrequency();
}

void WordTrie::PrintWordCloud(string targetWord){
  PriorityQueue pqFunctions;
  shared_ptr<pq> wordPQ;
  if (targetWord == ""){
    wordPQ = EnqueueTrie(GetRoot());
  }
  else{
    wordPQ = EnqueueCustomTrie(targetWord);
  }
  if (wordPQ && wordPQ->pqVector.size() < 25){ //filter for word collections that are too small
    cout << "Number of words too small to output." << endl;
    return;
  }
  else if (wordPQ){ //Only if wordPQ is not NULL
    vector<pqElement> results = pqFunctions.ExpandedRemove(wordPQ, 25); //extract vector for ease of use
    int topFrequency = results[0].priority;
    vector<int> rowOne {21, 13, 9, 14, 22};
    vector<int> rowTwo {15, 5, 1, 6, 16};
    vector<int> rowThree {10, 2, 0, 3, 11};
    vector<int> rowFour {17, 7, 4, 8, 18};
    vector<int> rowFive {23, 19, 12, 20, 24};
    vector<vector<int>> outputOrder;
    outputOrder.push_back(rowOne);
    outputOrder.push_back(rowTwo);
    outputOrder.push_back(rowThree);
    outputOrder.push_back(rowFour);
    outputOrder.push_back(rowFive);
    for (int i = 0; i < 5; i++){
      for (int j = 0; j < 5; j++){
        string numStars = NumberStars(results[outputOrder[i][j]].priority, topFrequency);
        string outputText =  numStars + results[outputOrder[i][j]].text + numStars;
        cout << setw(20) << outputText;
      }
      cout << endl;
    }
  }
}

//PRIVATE functions follow from this point

shared_ptr<Node> WordTrie::Find(shared_ptr<Node> root, string& targetWord){
  //Change string to lower case and load into vector
  vector<int> wordInts;
  for (unsigned int i = 0; i < targetWord.length(); i++){
    if (targetWord[i] != 39 && targetWord[i] != 45){ //skip apostrophe and hyphen
      targetWord[i] = tolower(targetWord[i]);
      wordInts.push_back(targetWord[i] - 97);
    }
  }
  //Follow or build tree to appropriate node
  shared_ptr<Node> currNode = root; //cursor node
  for (unsigned int i = 0; i < wordInts.size(); i++){
    int letter = wordInts[i];
    currNode = currNode->UpdateCursor(currNode, letter);
  }
  return currNode;
}

void WordTrie::ProcessSentence(shared_ptr<Node> root, vector<string> sentence){
  if (GetRoot() == root){ //if adding to the root Trie 
    string rebuiltSentence = "."; //rebuild string to store in each associated node
    for (auto it: sentence){
      rebuiltSentence = " " + it + rebuiltSentence;
    }
    for (auto it: sentence){
      shared_ptr<Node> targetNode = Insert(root, it); //insert each word into Trie
    }
    AddToCollectedText(rebuiltSentence); // for use in building custom Tries
  }
  else { //if adding to the filter or custom trie
    for (auto it: sentence){
      Insert(root, it); //insert each word into Trie
    }
  }
}

void WordTrie::RecursiveEnqueue(shared_ptr<pq> triePQ, shared_ptr<Node> root, PriorityQueue PQ){
  for (int i = 0; i < 26; i++){ //iterate through children
    if (root->GetAlphabetIndex(i)){ //if non-null, search those
      RecursiveEnqueue(triePQ, root->GetAlphabetIndex(i), PQ);
    }
  }
  if (root->GetFrequency() > 0 && !InTrie(GetFilterRoot(), root->GetWord())){ //if this node contains a word, enqueue it with frequency as priority
    PQ.Insert(triePQ, root->GetWord(), root->GetFrequency());
  }
} 

bool WordTrie::IsPartOfWord(char& currChar){
    if (currChar >= 97 && currChar <= 122){ //test for lower case a-z
      return true;
    }
    else if (currChar >= 65 && currChar <= 90){ //test for upper case A-Z
      currChar = tolower(currChar);
      return true;
    }
    else if (currChar == 39 || currChar == 45){ //test for apostrophe or hyphen
      return true;
    }
    return false;
  }

  bool WordTrie::InTrie(shared_ptr<Node> root, string word){
    shared_ptr<Node> targetNode = Find(root, word); //find where the word should be
    if (targetNode->GetFrequency() > 0){ //if frequency is greater than zero, word is in trie
      return true;
    }
    return false; //otherwise word is not in trie, even if node exists
  }

string WordTrie::NumberStars(int wordFreq, int topFreq){
  if (wordFreq > topFreq * 0.75){
    return "***";
  }
  else if (wordFreq > topFreq * 0.5){
    return "**";
  }
  else if (wordFreq > topFreq * 0.25){
    return "*";
  }
  else{
    return "";
  }
}

bool WordTrie::ContainsWord(string& targetWord, vector<string> sentence){
  for (unsigned int i; i < targetWord.length(); i++){ //convert to lower-case for matching
    targetWord[i] = tolower(targetWord[i]);
  }
  
  for (auto it: sentence){ //look through sentence to see if word is present
    if (it == targetWord){
      return true;
    }
  }
  return false;
}
