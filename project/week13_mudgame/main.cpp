#include <iostream>
#include <string>
#include <vector>
#include "user.h"
using namespace std;

const int MAP_X = 5;
const int MAP_Y = 5;

bool CheckXY(int user_x, int mapX, int user_y, int mapY);
void DisplayMap(const vector<vector<int>>& map, int user_x, int user_y, User* current_user);
bool CheckGoal(const vector<vector<int>>& map, int user_x, int user_y);
void CheckState(const vector<vector<int>>& map, int user_x, int user_y, User& user);
bool CheckUser(User* user);

int main() {
    vector<vector<int>> map = {
        {0, 1, 2, 0, 4},
        {1, 0, 0, 2, 0},
        {0, 0, 0, 0, 0},
        {0, 2, 3, 0, 0},
        {3, 0, 0, 0, 2}
    };

    // 캐릭터 선택
    User* current_user = nullptr;
    int user_x = 0, user_y = 0;

    re:
    cout << "직업을 선택하세요 (1: Magician, 2: Warrior): ";
    int choice;
    cin >> choice;

    if (choice == 1) {
        current_user = new Magician();
        cout << "Magician을 선택했습니다." << endl;
    } else if (choice == 2) {
        current_user = new Warrior();
        cout << "Warrior를 선택했습니다." << endl;
    } else {
        cout << "잘못된 선택입니다. 다시 선택하시오." << endl;
        goto re;
    }

    while (true) {
        string user_input;
        cout << "현재 HP: " << current_user->GetHP() << " 명령어를 입력하세요 (up, down, left, right, map, info, attack, exit): ";
        cin >> user_input;

        int prev_x = user_x;
        int prev_y = user_y;

        if (user_input == "up") user_y -= 1;
        else if (user_input == "down") user_y += 1;
        else if (user_input == "left") user_x -= 1;
        else if (user_input == "right") user_x += 1;
        else if (user_input == "map") {
            DisplayMap(map, user_x, user_y, current_user);
            continue;
        } else if (user_input == "info") {
            cout << *current_user << endl;
            continue;
        } else if (user_input == "attack") {
            current_user->DoAttack();
            continue;
        } else if (user_input == "exit") {
            cout << "게임을 종료합니다." << endl;
            break;
        } else {
            cout << "잘못된 명령어입니다." << endl;
            continue;
        }

        if (!CheckXY(user_x, MAP_X, user_y, MAP_Y)) {
            cout << "맵을 벗어났습니다. 다시 돌아갑니다." << endl;
            user_x = prev_x;
            user_y = prev_y;
            continue;
        }

        DisplayMap(map, user_x, user_y, current_user);
        CheckState(map, user_x, user_y, *current_user);

        current_user->DecreaseHP(1);
        if (!CheckUser(current_user)) {
            cout << "HP가 0 이하입니다. 게임이 종료됩니다." << endl;
            break;
        }

        if (CheckGoal(map, user_x, user_y)) {
            cout << "목적지에 도달했습니다! 축하합니다!" << endl;
            break;
        }
    }

    delete current_user;
    return 0;
}

// 지도 출력
void DisplayMap(const vector<vector<int>>& map, int user_x, int user_y, User* current_user) {
    for (int i = 0; i < MAP_Y; i++) {
        for (int j = 0; j < MAP_X; j++) {
            if (i == user_y && j == user_x) {
                // current_user의 타입에 따라 다르게 출력
                if (dynamic_cast<Magician*>(current_user)) {
                    cout << " MAGIC|";
                } else if (dynamic_cast<Warrior*>(current_user)) {
                    cout << " WARRI|";
                }
            } else {
                int posState = map[i][j];
                switch (posState) {
                case 0:
                    cout << "      |";
                    break;
                case 1:
                    cout << "아이템|";
                    break;
                case 2:
                    cout << "  적  |";
                    break;
                case 3:
                    cout << " 포션 |";
                    break;
                case 4:
                    cout << "목적지|";
                    break;
                }
            }
        }
        cout << endl;
        cout << " ----------------------------------- " << endl;
    }
}

bool CheckXY(int user_x, int mapX, int user_y, int mapY) {
    return (user_x >= 0 && user_x < mapX && user_y >= 0 && user_y < mapY);
}

bool CheckGoal(const vector<vector<int>>& map, int user_x, int user_y) {
    return map[user_y][user_x] == 4;
}

void CheckState(const vector<vector<int>>& map, int user_x, int user_y, User& user) {
    int state = map[user_y][user_x];
    switch (state) {
    case 1:
        cout << "아이템이 있습니다." << endl;
        user.IncreaseItemCnt();
        break;
    case 2:
        user.DecreaseHP(2);
        cout << "적이 있습니다. HP가 2 줄어듭니다." << endl;
        break;
    case 3:
        user.IncreaseHP(2);
        cout << "포션이 있습니다. HP가 2 늘어납니다." << endl;
        break;
    default:
        break;
    }
}

bool CheckUser(User* user) {
    return user->GetHP() > 0;
}
