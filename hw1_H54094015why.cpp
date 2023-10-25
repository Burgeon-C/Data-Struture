#include <iostream>
#include <ctime>
using namespace std;

template <class T> class circularChain;

template <class T> class circularChainNode {
  friend class circularChain <T>;
  private:
    T data;
    circularChainNode <T> *link;

  public:
    circularChainNode(const T& D) {
      this->data = D;
      this->link = NULL;
    }
    void setNextNode(circularChainNode<T> *nextNode) {
      this->link = nextNode;
    }
    char printNode() {
      // cout << this->data << " ";
      return this->data;
    }
};

template <class T> class circularChain {
  private:
    circularChainNode <T> *first;

  public:
    circularChain() {
      first = 0;
    }
    void setFirstNode(circularChainNode<T> *node) {
      this->first = node;
    }
    // getNode: get(return) the Node at the specific position
    circularChainNode <T> * getNode(int pos) {
      circularChainNode <T> *target = this->first;
      for (int i = 0; i < pos; i++) {
        // if the pos is much bigger then Chain's len, we break and return the last node
        if(target->link == NULL) {
          break;
        }
        target = target->link;
      }
      return target;
    }

    // insert a new Node in the specific position
    void insertNode(int pos, T data) {
      circularChainNode <T> *newNode = new circularChainNode <T> (data);
      circularChainNode <T> *target = getNode(pos);
      if (pos == 0) {
        newNode->link = target;
        this->first = newNode;
      } else {
        circularChainNode <T> *prev = getNode(pos-1);
        circularChainNode <T> *tmp = prev->link;
        prev->link = newNode;
        newNode->link = tmp;
      }
    }
    // delete the Node in the specific position
    void deleteNode(int pos) {
      circularChainNode <T> *target = getNode(pos);
      if ((pos-1) < 0) {    // no beforeNode, we delete the first one
        this->first = this->first->link;
      } else {
        circularChainNode <T> *prev = getNode(pos-1);
        prev->link = target->link;
      }
    }
    char printCurrentNode(int pos) {                // print all Node's data one by one
      circularChainNode<T> *curNode = this->first;
      for (int i = 0; i < pos; i++) {
        if (curNode->link == NULL) {
          curNode->link = first;
          break;
        }
        curNode = curNode->link;
      }
      return curNode->printNode();
    }
    
    void printList(int playerNum) {            // print all Node's data one by one
      circularChainNode<T> *curNode = this->first;
      int counter = 0;
      while(curNode) {
        cout << curNode->printNode() << " ";
        curNode = curNode->link;
        counter++;
        if (counter == playerNum) {
          break;
        }
      }
      cout << endl;
    }
};
int main(){
  circularChainNode <char> *fn = new circularChainNode <char> ('A');   // set first node
  circularChain <char> *LS = new circularChain<char>;  // linked list named LS

  // Gaming initializer
  int n;                //players numbers
  int round=1;          //start from round
  int bombPos=0;        //bomb current position
  int move;             //bomb movement position
  int index=-1;
  int lose_n=n-1;       //only one winner left, we have n-1 losers 
  char Loser[n];
  
  cout<<"Please input players numbers: ";
  cin>>n;
  if (n >10 | n < 4){
      cout<<"Wrong number of players, Game over"<<endl;
      return 0;
  }
  LS->setFirstNode(fn);
  for (int i = 1; i < n; i++) {
    LS->insertNode(i, char(65 + i));
  }
  cout << "Players order: ";
  LS->printList(n);
  cout << endl;

  srand(time(NULL));
  while (1) {
    move=rand() % 4;

    // Deliver the bomb
    cout <<"--------------------"<<endl;
    cout <<"Round " << round<<endl;
    round++;
    cout <<"Startrd from player "<<LS->printCurrentNode(bombPos)<<endl;
    cout <<"Bomb move to the next "<<move<<" player"<<" at ";bombPos+=move;
    while (bombPos >= n) {
      bombPos -= n;
    }
    cout << LS->printCurrentNode(bombPos) << "." << endl;

    // Check if the Bomb explode or not
    if (rand() % 10 < 4) {  // bomb explode
      cout <<"Boom!(Exploded) " << endl;
      cout <<"Player " << LS->printCurrentNode(bombPos);
      cout <<" out, remain " << --n << " players!" << endl;
      Loser[++index] = LS->printCurrentNode(bombPos);
      LS->deleteNode(bombPos);

    } else {  // safe
      cout << "Safe..." << endl;
    }

    // Remain players
    cout << "Players left: ";
    LS->printList(n);
    while (bombPos >= n) {
      bombPos -= n;
    }


    // Game over (then break this while-loop)
    if (n == 1) {
      cout << "Loser order: ";
      for (int i = 0; i<lose_n; i++) {
        cout << Loser[i];
        if (i != lose_n-1) {
          cout << " -> ";
        }
      }
      cout << "\nWinner: ";
      LS->printList(n);
      cout << endl;
      
      break;
    }

  }

  system("pause");

  return 0;
}