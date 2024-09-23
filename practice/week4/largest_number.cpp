#include <iostream>
using namespace std;

int main(){
    int a,b,c,largest;

    cout << "3개의 정수를 입력하시오: ";
    cin >> a >> b >> c;

    if (a > b && a > c){
        largest = a;
    }
    else if (b > a && b > c){
        largest = b;
    }
    else if (a==b && a>c){
        largest = a;
    } // a와 b가 같을 때 경우의 수 추가
    else if (a==c && a>b){
        largest = a;
    } // a와 c가 같을 때 경우의 수 추가
    else if (b==c && b>a){
        largest = b;
    } // b와 c가 같을 때 경우의 수 추가
    else{
        largest = c;
    }

    cout << "가장 큰 정수는" << largest << endl;

    return 0;
    
}