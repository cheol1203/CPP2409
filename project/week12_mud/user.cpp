#include "user.h"

User::User() : hp(20), itemCnt(0) {} // 기본 생성자 초기값 설정

void User::DecreaseHP(int dec_hp){
    hp -= dec_hp; //체력 감소
}

void User::IncreaseHP(int inc_hp){
    hp += inc_hp; //체력 증가
}

int User::GetHP() const{
    return hp; //현재 체력 반환
}

void User::IncreaseItemCnt(){
    itemCnt++; // 아이템 획득 시 카운트 증가
}

int User::GetItemCnt() const {
    return itemCnt; // 먹은 아이템 개수 반환
}

ostream& operator<<(ostream& os, const User& user){
    os << "현재 HP는" << user.GetHP() << "이고, 먹은 아이템은 총 " << user.GetItemCnt() << "개입니다."; // 출력 연산자 중복 정의
    return os;
}