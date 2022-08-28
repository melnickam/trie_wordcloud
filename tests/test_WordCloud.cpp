// If you change anything in this file, your changes will be ignored 
// in your homework submission.
// Chekout TEST_F functions bellow to learn what is being tested.
#include <gtest/gtest.h>
#include "../code/WordTrie.h"

#include <iostream>
#include <string>

using namespace std;

class test_WordCloud : public ::testing::Test {
protected:
	// This function runs only once before any TEST_F function
	static void SetUpTestCase(){
	}

	// This function runs after all TEST_F functions have been executed
	static void TearDownTestCase(){
	}
    
	// this function runs before every TEST_F function
	void SetUp() override {
    }

	// this function runs after every TEST_F function
	void TearDown() override {
	}
};

TEST_F(test_WordCloud, TestParseDocumentShort){
    WordTrie testTrie;
	ASSERT_TRUE(testTrie.GetRoot());
	testTrie.ParseDocument(testTrie.GetRoot(), "..//documents//dickandjane.txt");
	ASSERT_EQ(7, testTrie.WordCount(testTrie.GetRoot(), "Oh"));
	ASSERT_EQ(7, testTrie.WordCount(testTrie.GetRoot(), "oh"));
    ASSERT_EQ(2, testTrie.WordCount(testTrie.GetRoot(), "Spot"));
	ASSERT_EQ(0, testTrie.WordCount(testTrie.GetRoot(), "b"));
	ASSERT_EQ(0, testTrie.WordCount(testTrie.GetRoot(), "Sauron"));
}

TEST_F(test_WordCloud, TestParseDocumentSimpleLong){
    WordTrie testTrie;
	ASSERT_TRUE(testTrie.GetRoot());
	testTrie.ParseDocument(testTrie.GetRoot(), "..//documents//example.txt");
	ASSERT_EQ(6000, testTrie.WordCount(testTrie.GetRoot(), "stars"));
    ASSERT_EQ(3000, testTrie.WordCount(testTrie.GetRoot(), "like"));
	ASSERT_EQ(0, testTrie.WordCount(testTrie.GetRoot(), "b"));
	ASSERT_EQ(0, testTrie.WordCount(testTrie.GetRoot(), "Sauron"));
}

TEST_F(test_WordCloud, TestParseDocumentChristmasCarol){
    WordTrie testTrie;
	ASSERT_TRUE(testTrie.GetRoot());
	testTrie.ParseDocument(testTrie.GetRoot(), "..//documents//christmascarol.txt");
	ASSERT_EQ(90, testTrie.WordCount(testTrie.GetRoot(), "ghost"));
    ASSERT_EQ(48, testTrie.WordCount(testTrie.GetRoot(), "scrooge's"));
	ASSERT_EQ(0, testTrie.WordCount(testTrie.GetRoot(), "b"));
	ASSERT_EQ(0, testTrie.WordCount(testTrie.GetRoot(), "Sauron"));
}

//War and Peace test -- Works but takes a long time to process
TEST_F(test_WordCloud, TestParseDocumentWarAndPeace){
    WordTrie testTrie;
	ASSERT_TRUE(testTrie.GetRoot());
	testTrie.ParseDocument(testTrie.GetRoot(), "..//documents//warpeace.txt");
	ASSERT_EQ(718, testTrie.WordCount(testTrie.GetRoot(), "moscow"));
    ASSERT_EQ(718, testTrie.WordCount(testTrie.GetRoot(), "began"));
	ASSERT_EQ(8, testTrie.WordCount(testTrie.GetRoot(), "b"));
	//There are 8 b entries (4 " b ", 2 " b." and 2 " b'")
	ASSERT_EQ(0, testTrie.WordCount(testTrie.GetRoot(), "Sauron"));
}


TEST_F(test_WordCloud, TestEnqueueNoFilter){
	WordTrie testTrie;
	PriorityQueue testQueue;
	ASSERT_TRUE(testTrie.GetRoot());
	testTrie.ParseDocument(testTrie.GetRoot(), "..//documents//dickandjane.txt");
    shared_ptr<pq> testPQ = testTrie.EnqueueTrie(testTrie.GetRoot());
	ASSERT_TRUE(testQueue.Remove(testPQ).text == "go");
	ASSERT_TRUE(testQueue.Remove(testPQ).text == "said");
}

TEST_F(test_WordCloud, TestEnqueueWithFilter){
	WordTrie testTrie;
	PriorityQueue testQueue;
	ASSERT_TRUE(testTrie.GetRoot());
	testTrie.CreateFilter("..//documents//badwords.txt");
	testTrie.ParseDocument(testTrie.GetRoot(), "..//documents//dickandjane.txt");
    shared_ptr<pq> testPQ = testTrie.EnqueueTrie(testTrie.GetRoot());
	ASSERT_TRUE(testQueue.Remove(testPQ).text == "look");
	ASSERT_TRUE(testQueue.Remove(testPQ).text == "oh");
}