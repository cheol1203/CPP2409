#include "user.h"

ostream& operator<<(ostream& os, const User& user) {
    os << "현재 HP는 " << user.GetHP() << "이고, 먹은 아이템은 총 " << user.GetItemCnt() << "개입니다.";
    return os;
}

// Magician 구현
Magician::Magician() : hp(20), itemCnt(0) {}

void Magician::DecreaseHP(int dec_hp) {
    hp -= dec_hp;
}

void Magician::IncreaseHP(int inc_hp) {
    hp += inc_hp;
}

int Magician::GetHP() const {
    return hp;
}

void Magician::IncreaseItemCnt() {
    itemCnt++;
}

int Magician::GetItemCnt() const {
    return itemCnt;
}

void Magician::DoAttack() const {
    cout << "마법 사용" << endl;
}

// Warrior 구현
Warrior::Warrior() : hp(20), itemCnt(0) {}

void Warrior::DecreaseHP(int dec_hp) {
    hp -= dec_hp;
}

void Warrior::IncreaseHP(int inc_hp) {
    hp += inc_hp;
}

int Warrior::GetHP() const {
    return hp;
}

void Warrior::IncreaseItemCnt() {
    itemCnt++;
}

int Warrior::GetItemCnt() const {
    return itemCnt;
}

void Warrior::DoAttack() const {
    cout << "베기 사용" << endl;
}

