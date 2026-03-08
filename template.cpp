
#include <iostream>

using namespace std;
template <typename T>  T myMax(T a, T b){

    return (a>b)? a:b;
    
}

template <typename T> class greek{

    public:
        T x;
        T y;
    
        greek(T a, T b):x(a),y(b){};
    
};


int main (){

    cout<<myMax<int>(2,3)<<endl;

    greek<int>  greek_int(2,3);

    cout<< greek_int.x << " " << greek_int.y <<endl;
    return 0;
}