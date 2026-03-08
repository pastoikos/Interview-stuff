#include <iostream>
#include <vector>
using namespace std;


int main(){

     // Declares an empty vector
    vector<int> v1;
    
    // Declares vector with given size
    // and fills it with a value
    vector<int> v2(3, 5);  

    for (auto v : v2){
        cout << v << endl;
    }
    return 1;
}
