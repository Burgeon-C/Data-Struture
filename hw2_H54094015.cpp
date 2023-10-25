#include <iostream>
#include <iomanip>
#include <ctime>
#include <string>
#include <vector>

// CPP program to find last man standing 
// #include<bits/stdc++.h> 
using namespace std; 
  
/* structure for a node in circular 
   linked list */
struct Node 
{ 
    char data; 
    struct Node *next;
    int pos;  
}; 
  
// To create a new node of circular 
// linked list 
Node *newNode(int pos,char data) 
{ 
   Node *temp = new Node; 
   temp->next = temp; 
   temp->data = data; 
} 
  
/* Function to find the only person left 
   after one in every m-th node is killed 
   in a circle of n nodes */
void getJosephusPosition(int n) 
{ 
    // Create a circular linked list of 
    // size N. 
    Node *head = newNode(0,'A'); 
    cout<<"Current position:";
    cout<<head->data;
    
    Node *prev = head; 
    for (int i = 1; i < n; i++) 
    { 
        prev->next = newNode(1+i,char('A'+i)); 
        prev = prev->next; 
        cout<<"->";
        cout<<prev->data;
   
    }
    cout<<"\n";
    prev->next = head; // Connect last node to first 
    
    
    /* while only one node is left in the linked list*/
    Node *ptr1 = head, *ptr2 = head; 

    int i = 1;
    int move;
    int pos=0;
    srand(time(NULL)); 
    while (1) 
    { 
        
        move=rand()%4;  
        cout<<"--------------------------------"<<endl;
        cout<<"Round:"<<i<<endl;
        cout<<"Bomb move:"<<move<<endl;
        // Find m-th node 
        int count = 1; 
        while (count != move) 
        { 
            ptr2 = ptr1; 
            ptr1 = ptr1->next; 
            count++; 
        } 
  
        /* Remove the m-th node */
        if (count == move){
            ptr2->next = ptr1->next; 
            ptr1 = ptr2->next; 
            cout<<"deleted"<<ptr1->data<<endl; 
            i++;
            if(ptr1->next == ptr1){
                break;
            }
        }
    } 
    cout<<"\n";
    printf ("Winner""(Josephus Position) is %d",char(ptr1->data)); 
} 
  
/* Driver program to test above functions */
int main() 
{ 
    int n;
        cout<<"Please input players numbers: "<<endl;
        cin>>n;
        if (n >10 or n < 4){
            cout<<"Wrong number of players, Game over"<<endl;
            return 0;
        }
     
    getJosephusPosition(n); 
    return 0; 
} 