
#include <string>
#include <iostream>
#include <vector>

using namespace std;
bool formsRectangle(const string& moves) {
    // TODO: Γράψε εδώ τη λύση σου
    // Hint: θα χρειαστείς να παρακολουθείς διαδρομή, κορυφές, και να ελέγξεις ότι
    // τελικά έχεις 4 πλευρές και 4 γωνίες (ορθές), κλείνει στο (0,0), κτλ.


    vector<string> angles = { "^<", "^>", "<^", ">^", "v<", "v>", "<v", ">v"};

    int count_angles = 0;

    for(auto angle : angles){
        if (moves.find(angle)!= string::npos){
            count_angles++;
        }
    }
    // cout << "count_angles: " << count_angles<< endl;
    if ( !(count_angles ==3 || count_angles ==4))
        return false;

    int left_right =0, up_down=0;

    for(auto move : moves){
        if(move == '<'){
            left_right++;
        }
        else if(move == '>'){
            left_right--;
        }
        else if(move == '^'){
            up_down++;
        }
        else{
            up_down--;
        }
    }

    if (up_down != 0 || left_right != 0)
        return false;
    
  


    return true;
}


bool formsRectangle(const string& s) {
    int x = 0, y = 0;

    auto step = [&](char c){
        if(c=='^') y++;
        else if(c=='v') y--;
        else if(c=='>') x++;
        else if(c=='<') x--;
    };

    int turns = 0;
    for (int i = 1; i < (int)s.size(); i++)
        if (s[i] != s[i-1]) turns++;

    // μέτρα και την αλλαγή τελευταίου->πρώτου
    if (!s.empty() && s.back() != s.front()) turns++;

    for(char c: s) step(c);

    if (x != 0 || y != 0) return false;
    return turns == 4;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;                 // αριθμός test cases
    while (T--) {
        string s;
        cin >> s;             // το string κινήσεων (χωρίς κενά)
        cout << (formsRectangle(s) ? "YES" : "NO") << "\n";
    }
    return 0;
}