#include <iostream>
#include <vector>
#include <utility>
using namespace std;
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <queue>
// θα την υλοποιήσεις εσύ

void createGraph(unordered_map<char,vector<char>> &Graph,const vector<pair<char,char>>& edges){

    for(auto &pair : edges){
        Graph[pair.first].push_back(pair.second);
        Graph[pair.second].push_back(pair.first);
    }

}

void dfs(char src_node, unordered_map<char,vector<char>> &Graph, unordered_set<char> &visited, vector<char> & group){
    group.push_back(src_node);
    visited.insert(src_node);

    for ( auto neigh : Graph[src_node]){
        if(!visited.count(neigh))
            dfs(neigh, Graph, visited, group);
    }

}
vector<vector<char>> findGroups(const vector<pair<char,char>>& edges){

    unordered_map<char,vector<char>> Graph;
    unordered_set<char> visited;
    vector<vector<char>> groups;

    createGraph(Graph,edges);

    for(auto nei : Graph){
        char node = nei.first;
        if(!visited.count(node)){
            vector<char> group ={};
            dfs(node, Graph, visited, group);
            groups.push_back(group);
        }
    }

    return groups;
}




void iter_bfs(unordered_set<char> &visited,  unordered_map<char,vector<char>> & Graph, char src_node, vector<char> &group){

    queue<char> queue;

    queue.push(src_node);
    visited.insert(src_node);

    while(!queue.empty()){

        int node = queue.front();
        queue.pop();
        group.push_back(node);

        for ( auto & neigh : Graph[node]){
            if(!visited.count(neigh)){
                queue.push(neigh);
                visited.insert(neigh);
            }
        }
    }

}


vector<vector<char>> findGroups_bfs(const vector<pair<char,char>>& edges){


    unordered_map<char,vector<char>> Graph;
    for( auto & edge : edges){
        Graph[edge.first].push_back(edge.second);
        Graph[edge.second].push_back(edge.first);
    }

    vector<vector<char>> groups;
    unordered_set<char> visited;
    int nodes_num = Graph.size();

    for(auto &nodes : Graph){

        vector<char> group;
        char src_node = nodes.first;
        if(!visited.count(src_node)){
            iter_bfs(visited, Graph, src_node, group);
            groups.push_back(group);
        }
        
    }

    return groups;

}

int main() {
    int N;
    cin >> N;

    vector<pair<char,char>> edges;

    for (int i = 0; i < N; i++) {
        char a, b;
        cin >> a >> b;
        edges.push_back({a, b});
    }
    
    vector<vector<char>> groups = findGroups_bfs(edges);

    for (const auto& group : groups) {
        cout << "group: ";
        for (char c : group)
            cout << c << " ";
        cout << endl;
    }

    return 0;
}
