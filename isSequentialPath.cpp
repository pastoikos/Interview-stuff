// #include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <unordered_set>
#include <string>
// #include <bits/stdc++.h>
using namespace std;

/*
    Implement this function.
    Return true if edges contain all pairs:
    (0->1), (1->2), ..., (n-1 -> n)
*/

void createGraph(vector<vector<int>> &Graph, vector<vector<int>>& edges){

    for( auto edge : edges){
        int u = edge[0];
        int v = edge[1];

        Graph[u].push_back(v);
        Graph[v].push_back(u);
    }
}

bool dfs( vector<vector<int>> &Graph, vector<bool> &visited, int src, int dst){

    visited[src] = true;

    if (src == dst)
        return true;
    
    for ( auto neigh : Graph[src]){
        if ( !visited[neigh] )
            if (dfs( Graph, visited, neigh, dst))
                return true;
    }

    return false;
}

// bool isSequentialPath(int n, vector<vector<int>>& edges) {

//     vector<vector<int>> Graph(n+1);
//     createGraph(Graph, edges);
    
//     for(int u = 0; u < n-1; u++ ){
//         int v = u+1;
//         vector<bool> visited(n,false);
//         if (!dfs(Graph,  visited,  u,  v))
//             return false;

//     }
//     // TODO: Write your code here

//     return true;
// }


string key (int u, int v){
    return to_string(u)+"_"+to_string(v);
}
bool isSequentialPath(int n, vector<vector<int>>& edges) {

    unordered_set<string> edges_set;

    for(auto edge : edges){
        edges_set.insert(key(min(edge[0],edge[1]), max(edge[0],edge[1])));
    }  

    for (auto set : edges_set)
        cout << set << endl;

    for(int i = 0; i < n-1; i++){
        int u = i;   
        int v = i+1; 
        // we want to see if u->v edge exists 
        if (edges_set.find(key(u,v))== edges_set.end())
            return false;
    }
    // TODO: Write your code here

    return true;
}


int main() {

int n = 3;
vector<vector<int>> edges = {
    {0,1},{0,1},{2,1},{2,3},{2,3}
};
    // δοκίμασε να σβήσεις π.χ. {2,3} για να γίνει false

    if (isSequentialPath(n, edges))
        cout << "true\n";
    else
        cout << "false\n";

    return 0;
}
