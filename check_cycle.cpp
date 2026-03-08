#include <iostream>
#include <vector>
#include <utility>
#include <unordered_map>
#include <unordered_set>
using namespace std;

// Θα τις υλοποιήσεις εσύ






void createGraph(const vector<pair<char,char>> &edges, char type, unordered_map<char,vector<char>> &G){

    for( auto & edge : edges){
        G[edge.first].push_back(edge.second);
        if( type == 'u' || type == 'U')
            G[edge.second].push_back(edge.first);
    }

}

bool has_cycle_d(char src_node, unordered_set<char> visited, unordered_set<char> recStack, unordered_map<char,vector<char>> &G){

    visited.insert(src_node);
    recStack.insert(src_node);

    for (auto & neigh : G[src_node]){
        if(!visited.count(neigh)){
            if ( has_cycle_d(neigh, visited, recStack, G)){
                return true;
            }
        }
        else if ( recStack.count(src_node)){
            return true;
        }
    }

    recStack.erase(src_node);
    return false;
}

bool has_cycle_directed(const vector<pair<char,char>>& edges){
    
    unordered_map<char,vector<char>> G;
    unordered_set<char> visited;
    unordered_set<char> recStack;
    createGraph(edges, 'd', G);

    for( auto & nodes : G){

        char src_node = nodes.first;
        if ( !visited.count(src_node)){
            if (has_cycle_d(src_node, visited, recStack, G))
                return true;
        }

    }

    return false;


}


bool has_cycle_und( char src_node, char parent, unordered_set<char> visited, unordered_map<char,vector<char>> &G){

    visited.insert(src_node);

    for( auto & neigh : G[src_node]){
        if(!visited.count(neigh)){
            if ( has_cycle_und(neigh, src_node, visited, G))
                return true;
        }else{
             if (!visited.count(parent))
                return true;
        }
    }

    return false;
}

bool has_cycle_undirected(const vector<pair<char,char>>& edges){

    unordered_map<char,vector<char>> G;
    unordered_set<char> visited;
    createGraph(edges, 'u', G);

    for( auto & nodes : G){

        char src_node = nodes.first;
        if ( !visited.count(src_node)){
            if (has_cycle_und(src_node, '.', visited, G))
                return true;
        }

    }

    return false;

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

    bool cycle = false;

    if (type == 'D' || type == 'd') {
        cycle = has_cycle_directed(edges);
    } else if (type == 'U' || type == 'u') {
        cycle = has_cycle_undirected(edges);
    } else {
        // άκυρος τύπος (προαιρετικό)
        cout << "Invalid graph type\n";
        return 0;
    }

    cout << (cycle ? "YES\n" : "NO\n");
    return 0;
}

/*

U
3
A B
B C
C

D
3
A B
B C
A C









*/