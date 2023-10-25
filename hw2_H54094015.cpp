#include <ctime>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
using namespace std;

template <class T> class circularChain;       //using TA class code to adjust
template <class T> class circularChainNode {
  friend class circularChain<T>;

private:
  T data;
  circularChainNode<T> *link;

public:
  circularChainNode(const T &D) {
    this->data = D;
    this->link = NULL;
  }
  void setNextNode(circularChainNode<T> *nextNode) { this->link = nextNode; }
  char printNode() {
    
    return this->data;
  }
};

template <class T> class circularChain {
private:
  circularChainNode<T> *first;

public:
  circularChain() { first = 0; }
  void setFirstNode(circularChainNode<T> *node) { this->first = node; }
  // getNode: get(return) the Node at the specific position
  circularChainNode<T> *getNode(int pos) {
    circularChainNode<T> *target = this->first;
    for (int i = 0; i < pos; i++) {
      // if the pos is much bigger then Chain's len, we break and return the
      // last node
      if (target->link == NULL) {
        target->link = first;     //make a linked list become a circular linked list 
        break;
      }
      target = target->link;
    }
    return target;
  }

  // insert a new Node in the specific position
  void insertNode(int pos, T data) {
    circularChainNode<T> *newNode = new circularChainNode<T>(data);
    circularChainNode<T> *target = getNode(pos);
    if (pos == 0) {
      newNode->link = target;
      this->first = newNode;
    } else {
      circularChainNode<T> *prev = getNode(pos - 1);
      circularChainNode<T> *tmp = prev->link;
      prev->link = newNode;
      newNode->link = tmp;
    }
  }
  // delete the Node in the specific position
  void deleteNode(int pos) {
    circularChainNode<T> *target = getNode(pos);
    if ((pos - 1) < 0) { // no beforeNode, we delete the first one
      this->first = this->first->link;
    } else {
      circularChainNode<T> *prev = getNode(pos - 1);
      prev->link = target->link;
    }
  }

  void printlist(int n) { // print every node's data 
    circularChainNode<T> *curNode = this->first;
    int i = 0;
    char temp = curNode->printNode();
    while (i != n) {
      i++;
      cout << curNode->printNode();
      cout << " -> ";
      curNode = curNode->link;
    }
    cout << temp <<endl;         // print the first node's data in screen
  }
  char printBombnode(int pos) {  //use to print Bomb's node current data
    circularChainNode<T> *curNode = this->first;
    int i = 0;
    while (i < pos) {
      curNode = curNode->link;
      i++;
    }
    return curNode->printNode();
  }
};
int gaming(int n) {
  
  int pos = 0;   // bomb current position
  int move;      // bomb movement position
  int lose_n = n-1;   // only one winner left, we have n-1 losers  
  char Loser[n];      //an array to store losers
  int index = 0;      //array index=0 (the first loser)
  
  circularChainNode<char> *FN = new circularChainNode<char>('A');              // set first node FN
  circularChain<char> *CLS = new circularChain<char>;                           // Circular linked list named CLS  (both from TA's method)
  CLS->setFirstNode(FN);

  for (int i = 1; i < n; i++) 
  {
    CLS->insertNode(i, char('A' + i));  //create n-1 number of node (first node has already been create)
  }
  cout << "\n-Josephus game start-"<<endl;
  cout << "Players order: ";
  CLS->printlist(n);
  cout<<"(Note that -> is a circular order repesentation)";

  
  cout << "\n";
  int round = 1; // start from round 1
  srand(time(NULL)); 
  while (1) {
    cout << "--------------------" << endl; // Deliver the bomb to the next m player
    cout << "Round " << round << endl;
    round++;
    cout << "Startrd from player " << CLS->printBombnode(pos) << endl;
    move = rand() % 4;
    pos = pos + move;
    cout << "Bomb move to the next " << move << " player" << " at ";
    
    for (int i = 0; i <= n; i++) 
    {                             // if bomp position run over every node then refine its position 
      if (pos >= n) {
        pos = pos-n;
      }
    }
    cout << CLS->printBombnode(pos) << endl;
    

    if (rand() % 10 < 4) 
    {   // Check if the Bomb explode or not (prob.=0.4)
      --n;                                 //player decrease
      cout << "Boom!(Exploded) " << endl; // bomb explode
      cout << CLS->printBombnode(pos);
      cout << " is dead" << endl;

      Loser[index++] = CLS->printBombnode(pos);  //insert into Loser array
      CLS->deleteNode(pos);
    } 
    else 
    { // the bomp did not explode
      cout << "Didn't boom!" << endl;
    }
    if (n!=1)
    {
    cout << "There are " <<n;
    cout<< " players left" << endl;
    cout << "Players' order left now: ";   // if there still ome more Players left in game
    CLS->printlist(n);
    }

    if (n == 1) 
    {
      cout << "\nThe Winner of (Josephus Position): ";
      CLS->printlist(0);
      cout << "Deletion order:"<< Loser[0];
      for (int i = 1; i < lose_n; i++) {
        cout << "->" << Loser[i];
      }
      cout <<"\nGame over";
      break; // Game over codition
    }
  }
  return 0;
}
int main() {
  int n;
  while(1){
  cout << "Please input players numbers: " << endl;     // input to start a game
  cin >> n;
  if (n > 10 || n < 4) {
    cout << "Wrong number of players, try again" << endl;    // if number not in range 
    }
  else 
    {
    break;
    }
  }
  
  gaming(n); // call funtion to play the game

  return 0;
}