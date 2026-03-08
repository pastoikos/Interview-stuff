

#include <iostream>
using namespace std;
#include <vector>


bool valid_color(int u, int c, vector<vector<int>>& g, vector<int> &color){

    for( auto v : g[u]){
        if(color[v] == c){
            return false;
        }
    }
    return true;
}

// bool dfs(int u, int n, int M, vector<vector<int>>& g, vector<int> &color) {

//     for( auto c : color){
//       cout << c << " ";
//     }
//     cout << endl;

//     if ( u == n+1) return true;

//     for( int c=1; c <= M; c++){
//         if( valid_color(u,c,g,color) ){
//             color[u] = c;
//             if (dfs(u+1, n, M, g, color)) return true;
//             color[u] = 0;
//         }
//     }

//     return false;

// }



void dfs(int u, int n, int M, vector<vector<int>>& g, vector<int> &color, vector<vector<int>>& solutions) {

    for( auto c : color){
      cout << c << " ";
    }
    cout << endl;

    if ( u == n+1){
        solutions.push_back(color);
        return;
    } 

    for( int c=1; c <= M; c++){
        if( valid_color(u,c,g,color) ){
            color[u] = c;
            dfs(u+1, n, M, g, color, solutions);
            color[u] = 0;
        }
    }

}

vector<vector<int>> graphColoringBacktracking(int n, int M, vector<vector<int>>& g) { 

    vector<int> color(n+1,0);
    vector<vector<int>> solutions;

    dfs(1, n, M, g, color, solutions);

    return solutions;

}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n, e, M;
        cin >> n >> e >> M;

        vector<vector<int>> g(n + 1);
        for (int i = 0; i < e; i++) {
            int u, v;
            cin >> u >> v;
            g[u].push_back(v);
            g[v].push_back(u);
        }

        vector<vector<int>> colors = graphColoringBacktracking(n, M, g);

        if (colors.empty()) {
            cout << "NO\n";
        } else {
            cout << "YES\n";
            for(auto color : colors){
                for (int i = 1; i <= n; i++) {
                    cout << color[i] << (i == n ? '\n' : ' ');
                }
            }
        }
    }
    return 0;
}

/*
1
4 5 3
1 2
1 3
2 3
2 4
3 4

YES
1 2 3 1
*/