#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <stack>
using namespace std;

void dfs1(char node, unordered_set<char> &visited, unordered_map<char,vector<char>> &G, stack<char> &st){

    visited.insert(node);
    for( auto & neigh : G[node]){
        if(!visited.count(neigh)){
            dfs1(neigh, visited, G, st);
        }
    }
    st.push(node);
}

void dfs2(char node, unordered_set<char> &visited, unordered_map<char,vector<char>> &G, vector<char> &scc){

    visited.insert(node);
    scc.push_back(node);

    for( auto & neigh : G[node]){
        if(!visited.count(neigh)){
            dfs2(neigh, visited, G, scc);
        }
    }

}
vector<vector<char>> find_sccs(vector<pair<char,char>> & edges){

    unordered_map<char,vector<char>> G;
    unordered_set<char> visited;

    for( auto &edge : edges){
        G[edge.first].push_back(edge.second);
    }

    stack<char> st;

    for( auto & g : G){
        char node = g.first;
        if(!visited.count(node)){
            dfs1(node, visited, G, st);
        }
    }

    unordered_map<char,vector<char>> revG;
    for( auto &edge : edges){
        revG[edge.second].push_back(edge.first);
    }

    visited.clear();
    vector<vector<char>>  sccs;
    while(!st.empty()){
        char node = st.top();
        st.pop();
        vector<char> scc;
        if(!visited.count(node)){
            dfs2(node, visited, revG, scc);
            sccs.push_back(scc);
        }
    }

    return sccs;

}




int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    char type;
    int N;
    cin >> type >> N;

    vector<pair<char,char>> edges;
    edges.reserve(N);

    for (int i = 0; i < N; i++) {
        char a, b;
        cin >> a >> b;
        edges.push_back({a, b});
    }



    vector<vector<char>> sccs = find_sccs(edges);

    // Output: one SCC per line
    for (auto &scc : sccs) {
        cout << "scc : ";
        for (int i = 0; i < (int)scc.size(); i++) {
            if (i) cout << ' ';
            cout << scc[i];
        }
        cout << "\n";
    }
    // -----------------------------------

    return 0;
}

/*
D 10
C A
A B
B C
C D
D E
E F
F G
G E
E H
G H



*/