#include <iostream>
#include <climits>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
using namespace std;
int vertexNum = 8;

int miniDist(int distance[], bool Tset[]) // finding minimum distance
{
    int minimum=INT_MAX;
    int U=0;

    for(int k=0;k<vertexNum;k++)
    {
        if(Tset[k]==false && distance[k]<=minimum)
        {
            minimum=distance[k];
            U=k;
        }
    }
    return U;
}

void printPath(int route[], int j)
{
  if (route[j] == -1){
    return;   // j be the source
  }
  printPath(route, route[j]); //trace back
  cout << " -> Shop " << j + 1;
}

void DijkstraAlgo(int graph[8][8], int src, int dst) // adjacency matrix
{
    int distance[8]; // array to calculate the minimum distance for each node
    bool Tset[8];    // boolean array to mark visited and unvisited for each node
    int route[8];    // array to store the route
    
    //initialize
    for(int k = 0; k < vertexNum; k++)
    {
        distance[k] = INT_MAX;
        Tset[k] = false;
        route[src] = -1; // Source vertex  is set -1 in array
    }

    distance[src] = 0;   // Source vertex distance is set 0


    for(int k = 0; k < vertexNum; k++)
    {
        
        int m = miniDist(distance, Tset);
        Tset[m]=true;

        for(int k = 0; k < vertexNum; k++)
        {
            int temporaryDist = 0;
            temporaryDist = distance[m] + graph[m][k];


            // updating the distance of neighbor vertex
            if(!Tset[k] && graph[m][k] && distance[m]!=INT_MAX && temporaryDist<distance[k]){
                distance[k]= temporaryDist;
                route[k] = m;   // update m into route
            }    
        }
    }

    cout<< "\nFrom shop " << src+1 << " to shop " << dst+1 << endl; // print start and end shops
    for(int k = 0; k < vertexNum; k++)
    {
        if (dst==k){
            cout << "Shortest distance: " << distance[k] <<endl; //Shortest distance
            cout << "Diliver route: Shop" << src+1; //src+1 == the start shop
            printPath(route, k);   //call the function PrintPath
        }
    }
 
}

int main()
{
    ifstream in, inFile;
    ofstream out, outFile;  //file object
    in.open("adjacency_matrix.txt");  //open file
     
    int A[8][8];
    cout << "\nReading data....." << endl;
    while(!in.eof()){          //eof condition                            
        for(int i=1;i<=8;i++){
            for(int j=1;j<=8;j++)
            {
                in >> A[i][j]; //append in array
            }
        }
    }
    out.close();  //close file
    //Adjacency matrix
    cout << "Adjacency matrix: ";
    for(int i=1;i<=8;i++){ 
        cout << "\n";       
        for(int j=1;j<=8;j++)
        {
            cout << A[i][j] << " "; //print array A
        }
    }
    //Adjacency list
    cout << "\n\nAdjacency list:";
    for (int i = 1; i <= 8; i++)
    {
        cout << "\n" << i;
        for(int j = 1; j <= 8; j++)
        {
            if (A[i][j] == 1)
            {
                cout << " -> " << j; //turn A array into list representation
            }
        }
    }
    
    //distance matrix
    inFile.open("distance_matrix.txt");
     
    int D[8][8];
    cout << "\n\nReading data....." << endl;
    while(!inFile.eof()){                                
        for(int i=1;i<=8;i++){
            for(int j=1;j<=8;j++)
            {
                inFile >> D[i][j];
            }
        }
    }
    cout << "Distance matrix: ";
    for(int i=1;i<=8;i++)
    { 
        cout << "\n";       
        for(int j=1;j<=8;j++)
        {
            cout << D[i][j] << " ";
        }
    }

    cout << "\n";
    int s, e; 
    cout << "Please input the start shop(1~8):" << endl;  //let user input
    cin >> s;
    cout << "Please input the destinate shop(1~8):" << endl;
    cin >> e;
    int graph[8][8]={     //distance array to determine shortest path
    {0, 8, 0, 0, 3, 0, 0, 0},   
    {0, 0, 0, 7, 0, 4, 0, 0},
    {5, 6, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 6, 0},
    {0, 0, 0, 0, 0, 0, 7, 8},
    {0, 0, 0, 0, 2, 0, 0, 7},
    {0, 6, 0, 0, 0, 0, 0, 9},
    {0, 0, 2, 3, 0, 0, 0, 0}};
    DijkstraAlgo(graph,s-1,e-1); //call the funtion
    
    return 0;
    
}
