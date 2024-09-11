#include <iostream>

using namespace std;

int main()
{
    double a;
    double b; 

    cout << "화씨온도를 입력하시오 : ";
    
    cin >> a;
    b=  (5.0 / 9.0) * (a - 32);
    cout << "섭씨온도는 = " << b <<endl;
    return 0;
}