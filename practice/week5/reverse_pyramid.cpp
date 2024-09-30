#include <iostream>
using namespace std;

int main(){
    int floor;
    cout << "몇 층을 쌓겠습니까? (5~100):";
    cin >> floor;
    for (int i = floor-1 ; i >=0 ; i--){
        for (int j = 0 ; j < floor - i -1 ; j++){
            cout << "S";
        }
        for (int k = 0 ; k < i*2+1; k++){
            cout << "*";
        }
        cout << endl;
    }

    return 0;
}