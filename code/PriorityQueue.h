#ifndef PRIORITYQUEUE_H__
#define PRIORITYQUEUE_H__

#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>

using namespace std;

struct pqElement{

  float priority;
  string text;

};

// Edit this to flesh out the pq structure as appropriate. You may
// also add the function prototypes for anything else, and implement
// them in pq.cpp.
struct pq {
    vector<pqElement> pqVector;
};



class PriorityQueue {
public:
    // constructor, you should set all values in array to zero
    PriorityQueue();

    //deconstructor, you don't need to add anything here since you are gonna use smart pointers
    ~PriorityQueue();

    // init_priority_queue allocates memory for a pq structure (which you
    // are responsble for defining in the pq_struct.h file. It is
    // completely up to you how this should work.
    shared_ptr<pq> InitPriorityQueue();

    // insert adds the given text to the queue, using the specified
    // priority. If there is a tie, the given string should be placed at
    // the back of the group that it ties with, so all other strings with
    // this priority will be removed first.
    void Insert(shared_ptr<pq> queue, string text, float priority);

    // remove will access the highest priority element in the queue,
    // remove it from the queue, and return it. if the queue is empty it
    // should return the empty string.
    pqElement Remove(shared_ptr<pq> queue);

    // ppek will access the highest priority element in the queue and
    // return it without modifying the queue. if the queue is empty it
    // should return the empty string.
    string Peek(shared_ptr<pq> queue);

    //Will remove the specified number of elements, returning a vector containing them in order
    vector<pqElement> ExpandedRemove(shared_ptr<pq> queue, int numToRemove);

    //Prints out the contents of the results vector containing the most frequent words. For debug purposes
    void PrintResults(vector<pqElement> resultsVector);

private:
    // you can add add more private member variables and member functions here if you need

    //function that will loop, swapping an element of the queue into its proper place from right to left
    void Percolate_Up(shared_ptr<pq> queue, int tailIndex);

    //function that will loop, swapping an element of the queue into its proper place from left to right
    void Percolate_Down(shared_ptr<pq> queue, int elemIndex);

    //function that will swap two elements at the provided indices
    void Swap(shared_ptr<pq> queue, int indexLeft, int indexRight);
};

#endif  // PRIORITYQUEUE_H__
