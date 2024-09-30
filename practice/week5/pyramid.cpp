#include <iostream>
using namespace std;

int main(){
    int floor;
    cout << "몇 층을 쌓겠습니까? (5~100):";
    cin >> floor;
    for (int i = 1 ; i <= floor ; i++){             //floor가 5라고 할때, i= 1~5 반복
        for (int j = 0 ; j < floor - i ; j++){      //"S"는 4 ,3, 2, 1, 0 번 출력
            cout << "S";
        }
        for (int k = 0 ; k < i*2-1; k++){
            cout << "*";                            //"*"은 1 3 5 7 9 번 출력
        }
        cout << endl;
    }

    return 0;
}