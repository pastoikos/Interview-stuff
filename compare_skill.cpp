/*
    TOURNAMENT ROUNDS PROBLEM

    Δίνεται ένας πίνακας ακεραίων skills μήκους N.

    - skills[i] είναι το skill level του παίκτη i.
    - Όλα τα skills είναι ΜΟΝΑΔΙΚΑ.
    - Το N είναι δύναμη του 2 (2, 4, 8, 16, ...).

    Οι παίκτες συμμετέχουν σε knockout tournament.

    Δομή του τουρνουά:
    ------------------
    Γύρος 1:
        (0 vs 1), (2 vs 3), (4 vs 5), ...

    Γύρος 2:
        Νικητές των προηγούμενων ζευγαριών

    ...
    
    Σε κάθε αγώνα:
        Κερδίζει ο παίκτης με το μεγαλύτερο skill.
        Ο χαμένος αποκλείεται.

    Το τουρνουά συνεχίζεται μέχρι να μείνει ένας νικητής.

    Ζητείται:
    ----------
    Να επιστραφεί ένας πίνακας result ίδιου μεγέθους,
    όπου:

        result[i] = ο τελευταίος γύρος στον οποίο
                    συμμετείχε ο παίκτης i.

    Δηλαδή:
        - Αν ο παίκτης αποκλειστεί στον γύρο k,
          τότε result[i] = k
        - Αν είναι ο τελικός νικητής,
          τότε result[i] = συνολικοί γύροι

    Παράδειγμα:
    ----------
    Input:
        N = 8
        skills = [4,2,7,3,1,8,6,5]

    Output:
        [2,1,3,1,1,3,2,1]

    Περιορισμοί:
    ------------
    1 ≤ N ≤ 262144
    N είναι δύναμη του 2
    Όλα τα skills είναι διαφορετικά

    Αναμενόμενη πολυπλοκότητα:
    O(N)


Input (console):
5
2
9 1
4
4 2 1 3
4
3 4 2 1
8
4 2 7 3 1 8 6 5
8
1 2 3 4 5 6 7 8

Expected Output
1 1
2 1 1 2
1 2 2 1
2 1 3 1 1 3 2 1
1 2 1 3 1 2 1 3
*/


#include <iostream>
#include <vector>
using namespace std;

struct Node{
    int idx;
    int round;
};

// pavlos solution on codility
Node compare_skills(vector<int> &skills, vector<int> &results, int l_idx, int r_idx){
    
    if (l_idx == r_idx){
        return { l_idx, 0};
    }

    int mid = (l_idx+r_idx)/2;
    Node node_l = compare_skills( skills, results, l_idx, mid);
    Node node_r = compare_skills( skills, results, mid+1, r_idx);

    int round = node_l.round +1;

    if (skills[node_l.idx] > skills[node_r.idx]){
        results[node_r.idx] = round;
        return {node_l.idx, round};
    }else{
        results[node_l.idx] = round;
        return {node_r.idx, round};
    }
}

// pavlos solution on codility

// vector<int> solution(vector<int> &skills) {
//     // TODO: γράψε εδώ τη λύση σου
//     vector<int> results(skills.size());
//     int l_idx  = 0; int r_idx = skills.size()-1;
    
//     Node node_res = compare_skills( skills, results, l_idx, r_idx);
//     results[node_res.idx] = node_res.round;

//     return results;
// }

// iterative solution
vector<int> solution(vector<int> &skills) {
    // TODO: γράψε εδώ τη λύση σου
    vector<int> results(skills.size());

    vector<int> curr_round_idx(skills.size());
    for( int i =0; i < skills.size(); i++)
        curr_round_idx[i]  = i;
    
    int round = 1;

    while (curr_round_idx.size() > 1){
        // cout <<" N "<<  N << " ";
        
        vector<int> next_round_idx;
        for (int i =0 ; i <curr_round_idx.size(); i=i+2){
            int l_idx = curr_round_idx[i];
            int r_idx = curr_round_idx[i+1];

            if (skills[l_idx] > skills[r_idx]){
                results[r_idx] = round;
                next_round_idx.push_back(l_idx);
            }
            else{
                results[l_idx] = round;
                next_round_idx.push_back(r_idx);
            }
        }
        curr_round_idx = next_round_idx;

        round++;
    }
    
    results[curr_round_idx[0]] =round -1;

    return results;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;   // αριθμός test cases

    while (T--) {
        int N;
        cin >> N;

        vector<int> skills(N);
        for (int i = 0; i < N; i++)
            cin >> skills[i];

        vector<int> ans = solution(skills);

        for (int i = 0; i < ans.size(); i++) {
            if (i) cout << " ";
            cout << ans[i];
        }
        cout << "\n";
    }

    return 0;
}
