#include <iostream>
using namespace std;

class User{
private:
    int hp;
public:
    User(); //생성자
    void DecreaseHP(int dec_hp); //체력 감소
    void IncreaseHP(int inc_hp); //체력 증가
    int GetHP(); //현재 체력 반환
};