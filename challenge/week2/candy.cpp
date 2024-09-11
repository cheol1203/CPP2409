#include <iostream>

using namespace std;

int main()
{
    int money;
    int price;
    

    cout << "가지고 있는 돈을 입력하시오 : ";
    cin >> money;
    cout << "사탕의 가격을 입력하시오 : ";
    cin >> price;
    int a;
    int b;
    a=money/price;
    b=money%price;

    cout << "최대로 살 수 있는 캔디 = " << a <<endl;
    cout << "캔디 구입 후 남은 돈 = " << b <<endl;
    return 0;
}