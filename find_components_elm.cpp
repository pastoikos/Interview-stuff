// main.cpp
// Template: Διάβασε mesh (elements ως λίστες από node χαρακτήρες),
// βρες disconnected components και τύπωσε:
//   1) group_elements: elements ανά component
//   2) group_nodes: nodes (χαρακτήρες) ανά component
//
// Εσύ θα συμπληρώσεις τη "λύση" (DSU/DFS) στα TODO σημεία.

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

/* =========================
   Βοηθητικά: printing
   ========================= */
static void print_groups_elements(const vector<vector<int>>& groups) {
    cout << "\n=== group_elements (component -> element ids) ===\n";
    for (int cid = 0; cid < (int)groups.size(); ++cid) {
        cout << "Component " << cid << ": ";
        for (int e : groups[cid]) cout << e << " ";
        cout << "\n";
    }
}

static void print_groups_nodes(const vector<vector<char>>& groups) {
    cout << "\n=== group_nodes (component -> node labels) ===\n";
    for (int cid = 0; cid < (int)groups.size(); ++cid) {
        cout << "Component " << cid << ": ";
        for (char c : groups[cid]) cout << c << " ";
        cout << "\n";
    }
}

/* ==========================================================
   TODO: Εδώ θα βάλεις την υλοποίηση σου (DSU ή DFS).
   Συνάρτηση που πρέπει να γεμίσεις:

   Input:
     elem_to_nodes : vector of elements, each element is vector<char> node labels

   Output:
     group_elements : vector of components, each component is vector<int> element indices
     group_nodes    : vector of components, each component is vector<char> node labels

   ΣΗΜΕΙΩΣΗ:
     - Τα node labels είναι χαρακτήρες (π.χ. 'A', 'b', '7').
     - Πρέπει να ομαδοποιήσεις disconnected regions με node-connectivity
       (αν μοιράζονται έστω 1 κόμβο).
   ========================================================== */

class DSU{

    public:
        vector<int> parent;
        vector<int> rank;
    
    DSU(int n):parent(n),rank(n,0){

        // parent.resize(n);
        // rank.assign(n,0);
        for(int i =0; i < n;i ++) 
            parent[i] = i;
    }

    int find(int x){

        while(parent[x]!=x){
            parent[x] = parent[parent[x]];
            x = parent[x];
        }
        return x;
    }

    void unite( int elm1, int elm2){

        int pa = find(elm1);
        int pb = find(elm2);

        int ra = rank[pa];
        int rb = rank[pb];

        if ( ra < rb)
            swap(pa,pb);
        parent[pb] = pa;

        if (ra == rb)
         rank[pa] +=1;

    }


};
void solve_components(
    const vector<vector<char>>& elem_to_nodes,
    vector<vector<int>>& group_elements,
    vector<vector<char>>& group_nodes
) {
    // TODO: Γράψε εδώ τη λύση σου.
    //
    // Προτεινόμενη ιδέα (πρακτική):
    // 1) DSU πάνω στα elements (μέγεθος E)
    // 2) node_owner: unordered_map<char, int> που κρατά "πρώτο element που είδε τον κόμβο"
    // 3) union(elements) όταν ξαναδείς τον ίδιο κόμβο
    // 4) group_elements: root -> list of elements
    // 5) group_nodes: root -> set<char> από κόμβους των elements
    //
    // Εναλλακτικά: DSU πάνω στους nodes (θα χρειαστεί mapping char->int).
    //
    // ΑΡΚΕΙ να γεμίσεις τα group_elements και group_nodes.

    unordered_map<char,int> node_owner;
    int size_elm = elem_to_nodes.size();
    DSU dsu(size_elm);

    for( int e =0; e < size_elm; e++){

        for( auto &n : elem_to_nodes[e]){
            if ( node_owner.count(n)){
                dsu.unite(e,node_owner[n]);
            }{
                node_owner[n] = e;
            }
        }
        
    }

   unordered_map<int,vector<int>> comp_to_elms;
   for( int e =0; e < size_elm; e++){
        int comp = dsu.find(e);
        comp_to_elms[comp].push_back(e);
   }

    for( auto & comp : comp_to_elms){
        group_elements.push_back(comp.second);
    }

    unordered_map<int,unordered_set<char>> comp_to_nodes;
    for( int e =0; e < size_elm; e++){
        int comp = dsu.find(e);
        for( auto &n : elem_to_nodes[e]){
            comp_to_nodes[comp].insert(n);
        }
    }

     for( auto & comp : comp_to_nodes){
        group_nodes.emplace_back(comp.second.begin(), comp.second.end());
    }




}

/* ===================
        MAIN
   =================== */
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int E;
    cout << "Give number of elements E: ";
    cin >> E;

    // Διαβάζουμε elements ως strings (π.χ. "ABCD" ή "a1Z")
    // Κάθε χαρακτήρας είναι ένας node.
    cout << "Give each element as a string of node labels (no spaces).\n";
    cout << "Example for 3 elements:\n";
    cout << "  ABCD\n";
    cout << "  CDXY\n";
    cout << "  PQRS\n\n";

    vector<vector<char>> elem_to_nodes;
    elem_to_nodes.reserve(E);

    for (int e = 0; e < E; ++e) {
        string s;
        cin >> s;

        vector<char> nodes;
        nodes.reserve(s.size());
        for (char c : s) nodes.push_back(c);

        elem_to_nodes.push_back(std::move(nodes));
    }

    // Κάλεσε τη λύση σου
    vector<vector<int>> group_elements;
    vector<vector<char>> group_nodes;

    solve_components(elem_to_nodes, group_elements, group_nodes);

    // Εκτύπωσε αποτέλεσμα
    print_groups_elements(group_elements);

    // Προαιρετικά: ταξινόμηση nodes για πιο "σταθερή" εκτύπωση
    for (auto& comp : group_nodes) {
        sort(comp.begin(), comp.end());
        comp.erase(unique(comp.begin(), comp.end()), comp.end());
    }
    print_groups_nodes(group_nodes);

    return 0;
}