#include "PriorityQueue.h"

PriorityQueue::PriorityQueue(){
}

PriorityQueue::~PriorityQueue(){
    // You don't need to add anything here
}

// Implement this after defining struct in .h file
shared_ptr<pq> PriorityQueue::InitPriorityQueue(){
    shared_ptr<pq> newPQ(new pq); //create a shared pointer to a new pq object
    return newPQ;
}

// Implement this second
void PriorityQueue::Insert(shared_ptr<pq> queue, string text, float priority){
    pqElement newEntry;
    newEntry.text= text;
    newEntry.priority = priority;

    queue->pqVector.push_back(newEntry);
    Percolate_Up(queue, queue->pqVector.size()-1);
}

// Implement this third
pqElement PriorityQueue::Remove(shared_ptr<pq> queue){
    pqElement result;
    if (queue->pqVector.size() == 0){ //return empty string if queue is empty
        return result;
    }
    else {
      result = queue->pqVector[0]; // set result to first element
      Swap(queue, 0, queue->pqVector.size()-1); //swap the first and last elements
      queue->pqVector.erase(queue->pqVector.end()); //erase the highest-priorty element
      Percolate_Down(queue, 0); //fix the invariant of the heap
    }
    return result;    // return the desired element
}

// Implement this last
string PriorityQueue::Peek(shared_ptr<pq> queue){
    string result = "";
    if (queue->pqVector.size() == 0){ //if empty, return empty vector
        return result;
    }
    else{
      result = queue->pqVector[0].text; //otherwise set result to text of first element
      return result;    // return desired text
    }
}

vector<pqElement> PriorityQueue::ExpandedRemove(shared_ptr<pq> queue, int numToRemove){
  vector<pqElement> wordFreqs; 
  if (!queue){
    cout << "Nothing in queue; returning empty vector" << endl;
    return wordFreqs;
  }
  if (numToRemove > queue->pqVector.size()){ //if queue is too short, limit it to vector size
    numToRemove = queue->pqVector.size();
  }
  for (int i = 0; i < numToRemove; i++){
    wordFreqs.push_back(Remove(queue));
  }
  return wordFreqs;
}

void PriorityQueue::PrintResults(vector<pqElement> resultsVector){
  for (int i = 0; i < resultsVector.size(); i++){
    cout << resultsVector[i].text << "     " << resultsVector[i].priority << endl;
  }
}

void PriorityQueue::Percolate_Up(shared_ptr<pq> queue, int elemIndex){
  while (elemIndex > 0){ //loop until reaching "root"
      int parentIndex = (elemIndex - 1) / 2;
      if (queue->pqVector[parentIndex].priority < queue->pqVector[elemIndex].priority){ //if parent is greater than child, swap
          Swap(queue, elemIndex, parentIndex);
      }
    elemIndex = parentIndex; //now look at parent and see if it moves up again
  }
}

void PriorityQueue::Percolate_Down(shared_ptr<pq> queue, int elemIndex){
    int prevIndex = elemIndex; //used to determine if loop is repeating
    int maxIndex = -1;
    while(elemIndex < queue->pqVector.size() && prevIndex != maxIndex){ //continue until reaching end of vector or repeating the same loop (if no swap is made)
        maxIndex = elemIndex;
        int maxOfThree = queue->pqVector[elemIndex].priority; //set to element in question to test against both children
        for (int i = 1; i < 3; i++){ //iterate through both children, finding max value
          int childIndex = elemIndex * 2 + i;
          if (childIndex < queue->pqVector.size() && queue->pqVector[childIndex].priority > queue->pqVector[maxIndex].priority){ //if child is greater
              maxOfThree = queue->pqVector[childIndex].priority; //set max to child priority
              maxIndex = childIndex; //and index to child index
          }
        }
        Swap(queue, elemIndex, maxIndex); //swap the element and the max element (may be the same element)
        prevIndex = elemIndex; //updated previous index
        elemIndex = maxIndex; //update current element index
    }
}

void PriorityQueue::Swap(shared_ptr<pq> queue, int indexLeft, int indexRight){
    pqElement temp = queue->pqVector[indexLeft]; // save pq element at left index
    queue->pqVector[indexLeft] = queue->pqVector[indexRight]; //copy right index to left
    queue->pqVector[indexRight] = temp; //replace right index with temp (original left)
}

