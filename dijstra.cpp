
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <iostream>
#include <queue>
#include <stack>
using namespace std;

// Θα την συμπληρώσεις εσύ:
// Επιστρέφει {minDistance, pathNodes}
// Αν δεν υπάρχει μονοπάτι: minDistance = LLONG_MAX και path = {}
pair<int, vector<char>> dijkstra_path(
    unordered_map<char, vector<pair<char,int>>> &g, unordered_set<char> &nodes,
    char src,
    char dst
){

    unordered_map<char,int> dist;
    unordered_map<char,char> path_rev;
    stack<char> st;
    vector<char> path;

    for(auto &node :nodes) 
        dist[node] = INT_MAX;
    dist[src] =0;

    priority_queue<pair<int,char>,vector<pair<int,char>>,greater<pair<int,char>>> pq;
    pq.push({0,src});

    while(!pq.empty()){
        auto min_pair = pq.top();
        pq.pop();

        int dist_u = min_pair.first;
        char u = min_pair.second;

        for( auto &adj_pair : g[u]){
            int w = adj_pair.second;
            int v = adj_pair.first;
            if ( dist_u + w < dist[v]){
                dist[v] = dist_u + w;
                pq.push({dist[v],v});
                path_rev[v] = u;
            }
        }
    }

    pair<int, vector<char>> res = {INT_MAX,{}};
    if(path_rev.count(dst)){
        int dst_res = dist[dst];
        while( src != dst ){
            st.push(dst);
            dst = path_rev[dst];
        }
        while(!st.empty()){
            path.push_back(st.top());
            st.pop();
        }
        res = {dst_res, path};
    } 

    return res;

}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    char type;
    int N;
    cin >> type >> N;

    unordered_map<char, vector<pair<char,int>>> g;
    unordered_set<char> nodes;

    for (int i = 0; i < N; i++) {
        char u, v;
        int w;
        cin >> u >> v >> w;
        g[u].push_back({v, w});
        nodes.insert(u);
        nodes.insert(v);
    }

    char src, dst;
    cin >> src >> dst;

    auto res = dijkstra_path(g, nodes, src, dst);

    int dist = res.first;
    vector<char> path = res.second;

    if (dist == INT_MAX || path.empty()) {
        cout << "NO PATH\n";
        return 0;
    }

    cout << dist << "\n";
    for (int i = 0; i < (int)path.size(); i++) {
        if (i) cout << ' ';
        cout << path[i];
    }
    cout << "\n";

    return 0;
}