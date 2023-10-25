#include <iostream>
#include <climits>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
#include <queue>
#include <cstring>
#include <deque>
#include <stack>
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

void DijkstraAlgo(int graph[8][8], int src, int dst) // adjacency matrix
{
    int distance[8];  // array to calculate the minimum distance for each node
    bool Tset[8];  // boolean array to mark visited and unvisited for each node
    int route[8];
    
    //initialize
    for(int k = 0; k < vertexNum; k++)
    {
        distance[k] = INT_MAX;
        Tset[k] = false;
    }

    distance[src] = 0;  // Source vertex distance is set 0


    for(int k = 0; k < vertexNum; k++)
    {
        // 找到目前距離最小且未拜訪過的點m
        int m = miniDist(distance, Tset);
 
        Tset[m] = true;
        route[k] = m;

        for(int k = 0; k < vertexNum; k++)
        {
            int temporaryDist = 0;
            temporaryDist = distance[m] + graph[m][k];

            // 計算m到當前點的距離
            // updating the distance of neighbor vertex
            if(!Tset[k] && graph[m][k] && distance[m]!=INT_MAX && temporaryDist<distance[k]){
                distance[k] = temporaryDist;
            }
        }
    }

    cout << "\nFrom shop " << src + 1 << " to shop " << dst + 1 << endl;
    for(int k = 0; k < vertexNum; k++)
    {
        if (dst == k) {
            cout << "Shortest distance: " << distance[k] << endl;
        }
    }
    
    stack<int> path;
    int temp = route[dst-1];
    while(temp != 0)
    {
        path.push(temp);
        temp = route[temp-1];
    }
    cout << src;
    while(!path.empty())
    {
        cout << path.top();
        path.pop();
    }
    cout << dst;
    cout << endl;
}

int main()
{
    ifstream in, inFile;
    ofstream out, outFile;
    in.open("adjacency_matrix.txt");
     
    int A[8][8];
    cout << "\nReading data....." << endl;
    while(!in.eof()){                                
        for(int i=1;i<=8;i++){
            for(int j=1;j<=8;j++)
            {
                in >> A[i][j];
            }
        }
    }
    out.close(); 
    cout << "Adjacency matrix: ";
    for(int i=1;i<=8;i++){ 
        cout << "\n";       
        for(int j=1;j<=8;j++)
        {
            cout << A[i][j] << " ";
        }
    }
    cout << "\n\nAdjacency list:";
    for (int i = 1; i <= 8; i++)
    {
        cout << "\n" << i;
        for(int j = 1; j <= 8; j++)
        {
            if (A[i][j] == 1)
            {
                cout << " -> " << j;
            }
        }
    }

    // distance_matrix.txt
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
    // outFile.close(); 


    cout << "\n";
    int s, e; 
    cout << "Please input the start shop:" << endl;
    cin >> s;
    cout << "Please input the destinate shop:" << endl;
    cin >> e;
    int graph[8][8] = {
        {0, 8, 0, 0, 3, 0, 0, 0},   
        {0, 0, 0, 7, 0, 4, 0, 0},
        {5, 6, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 6, 0},
        {0, 0, 0, 0, 0, 0, 7, 8},
        {0, 0, 0, 0, 2, 0, 0, 7},
        {0, 6, 0, 0, 0, 0, 0, 9},
        {0, 0, 2, 3, 0, 0, 0, 0}
    };

    DijkstraAlgo(graph, s-1, e-1); 
    
    return 0;
    
}
