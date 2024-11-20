#include <iostream>
using namespace std;

class User{
private:
    int hp;
    int itemCnt; // 아이템 먹은 횟수

public:
    User(); //생성자
    void DecreaseHP(int dec_hp); //체력 감소
    void IncreaseHP(int inc_hp); //체력 증가
    int GetHP() const; //현재 체력 반환
    void IncreaseItemCnt(); //아이템 획득 시 카운트 증가
    int GetItemCnt() const; //먹은 아이템 개수 반환
    friend ostream& operator<<(ostream& os, const User& user); // 출력 연산자 중복 정의
};