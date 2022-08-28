Overview:
This Project "WordCloud", takes one or more pieces of prose text in .txt format and parses the text to determine and track the frequency of each unique word. Output is a printed 5x5 array of the 25 most-common words with the most common words closer to the center.

Method:
A trie is used to store the frequency of each unique word within the WordTrie object. Once the trie is complete, a priority queue sorts the words by frequency and can be used to determine the top 25 most common.

Contents:
Node.cpp & .h >> contains the Node class definition; each node contains a word or acts as a pathway to a word
PriorityQueue.cpp & .h >> contains the PriorityQueue class definitions used to sort the WordTrie
WordTrie.cpp & .h >> contains the WordTrie class functions used to parse input documents, insert the contents into the Trie, and output the word cloud
MainFunctions.cpp & .h >> contains helper functions to run main.cpp
main.cpp >> contains main function and interface
test_WordCloud.cpp >> contains test functions

Instructions:
1) Compile using cmake with the standard ctrl-shift-b shortcut in VSCode

2) Testing: the test_WordCloud.cpp file will perform operational tests on the following functions:
Test 1: ParseDocument with short input (Fun With Dick and Jane)
Test 2: ParseDocument with a simple, long input (example.txt: A sentence repeated 3,000 times.)
Test 3: ParseDocument with a medium, standard input (A Christmas Carol)
Test 4: ParseDocument with a long, standard input (War and Peace)
Test 5: EnqueTrie without filter (filters for common words)
Test 6: EnqueueTrie with filter

3) Main Function: Place any document you wish to parse in the WordCloud/Documents folder. There are sample texts included already to assist in testing or demonstrating the program:
filename                    Title
callofthewild.txt           Call of the Wild by Jack London
christmascarol.txt          A Christmas Carol by Charles Dickens
dickandjane.txt             Fun With Dick and Jane (Children's Book)
ihaveadream.txt             Dr. Martin Luther King Jr.'s "I Have a Dream" speech
littlewomen.txt             Little Women by Louisa May Alcott
prideandprejudice.txt       Pride and Prejudice by Jane Austen
warpeace.txt                War and Peace by Leo Tolstoy

4) "Run App" to run the main.cpp function

5) Description of menu options:
[1] Enable or Disable filter for generic words (i.e. "a", "go", "her"). Default is off.
[2] Add text to a database. Enter the filename to add to the Trie. Can be done with multiple files.
[3] Prints the overall word cloud of combined texts processed into database
[4] (User Input: single word) Prints a word cloud based on the combined texts processed into the database according to which words occur in the same sentence as the user-input word.
[5] Resets Trie to an empty one
[6] Quit the program