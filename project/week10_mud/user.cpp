#include "user.h"

User::User(){
    hp=20; // 초기 체력 20으로 설정
}

void User::DecreaseHP(int dec_hp){
    hp -= dec_hp; //체력 감소
}

void User::IncreaseHP(int inc_hp){
    hp += inc_hp; //체력 증가
}

int User::GetHP(){
    return hp; //현재 체력 반환
}