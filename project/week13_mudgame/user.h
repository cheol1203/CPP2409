#include <iostream>
using namespace std;

class User {
public:
    virtual ~User() {};
    virtual void DecreaseHP(int dec_hp) = 0; // 체력 감소
    virtual void IncreaseHP(int inc_hp) = 0; // 체력 증가
    virtual int GetHP() const = 0; // 현재 체력 반환
    virtual void IncreaseItemCnt() = 0; // 아이템 획득 시 카운트 증가
    virtual int GetItemCnt() const = 0; // 먹은 아이템 개수 반환
    virtual void DoAttack() const = 0; // 공격 메서드
    friend ostream& operator<<(ostream& os, const User& user); // 출력 연산자 중복 정의
};

class Magician : public User {
private:
    int hp;
    int itemCnt;

public:
    Magician(); // 생성자
    ~Magician() override {}
    void DecreaseHP(int dec_hp) override;
    void IncreaseHP(int inc_hp) override;
    int GetHP() const override;
    void IncreaseItemCnt() override;
    int GetItemCnt() const override;
    void DoAttack() const override;
};

class Warrior : public User {
private:
    int hp;
    int itemCnt;

public:
    Warrior(); // 생성자
    ~Warrior() override {}
    void DecreaseHP(int dec_hp) override;
    void IncreaseHP(int inc_hp) override;
    int GetHP() const override;
    void IncreaseItemCnt() override;
    int GetItemCnt() const override;
    void DoAttack() const override;
};
