/*
    LARGEST INTEGER FREQUENCY

    Δίνεται ένας πίνακας ακεραίων A μήκους N.

    Ένας ακέραιος X θεωρείται "valid" αν:
        - ο X εμφανίζεται στον πίνακα Α ακριβώς X φορές.

    Ζητείται:
        Να επιστραφεί ο ΜΕΓΑΛΥΤΕΡΟΣ valid ακέραιος X.
        Αν δεν υπάρχει τέτοιος ακέραιος, να επιστραφεί 0.

    Παράδειγμα:
        A = [3, 8, 2, 3, 3, 2]
        freq(2) = 2  -> valid
        freq(3) = 3  -> valid
        freq(8) = 1  -> not valid
        Άρα απάντηση: 3

    Σημειώσεις:
        - Αν X <= 0 δεν μπορεί να είναι valid (δεν έχει νόημα "0 φορές" σαν ζητούμενο).
        - Αν X > N δεν μπορεί να είναι valid, γιατί σε πίνακα N στοιχείων δεν γίνεται να εμφανιστεί πάνω από N φορές.

    Αναμενόμενη πολυπλοκότητα:
        O(N) χρόνο με counting / hashmap.

Input(console):
6
6
3 8 2 3 3 2
5
1 2 2 3 3
4
1 1 1 1
3
1 2 3
5
0 0 0 0 0
8
4 4 4 4 4 4 4 4

Expected Output:
3
2
0
1
0
0

*/

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;


int solution(vector<int> &A) {
    // TODO: Συμπλήρωσε εδώ τη λύση σου

    int N = A.size();
    vector<int> freqs(N+1,0);

    for(int i=0; i<N,0;i++){

        if(A[i] > 0 && A[i]<= N){
            freqs[A[i]] +=1;
        }
    }

    for( int i = N ; i >1; i-- ){
        if(freqs[i] == i)
            return i;
    }

    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;   // αριθμός test cases

    while (T--) {
        int N;
        cin >> N;

        vector<int> A(N);
        for (int i = 0; i < N; i++)
            cin >> A[i];

        cout << solution(A) << "\n";
    }

    return 0;
}
