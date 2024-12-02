#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <exception>
#include "user.h"
using namespace std;

// 맵의 크기를 정의
const int MAP_X = 5;
const int MAP_Y = 5;

// 함수 선언
bool CheckXY(int user_x, int map_x, int user_y, int map_y);
void DisplayMap(const vector<vector<int>>& map, int user_x, int user_y, User* current_user);
bool CheckGoal(const vector<vector<int>>& map, int user_x, int user_y);
void CheckState(const vector<vector<int>>& map, int user_x, int user_y, User& user);
bool CheckUser(User* user);
vector<vector<int>> LoadMap(const string& file_name);

int main() {
    vector<vector<int>> map;
    try {
        // 맵 파일을 읽어서 초기화
        map = LoadMap("map.txt");
    } catch (const exception& e) {
        // 예외 처리: 파일을 읽을 수 없거나 형식이 잘못된 경우
        cerr << e.what() << endl;
        return 1;
    }

    User* current_user = nullptr;
    int user_x = 0, user_y = 0;

    // 사용자 직업 선택
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

    // 게임 루프
    while (true) {
        string user_input;
        cout << "현재 HP: " << current_user->GetHP() << " 명령어를 입력하세요 (up, down, left, right, map, info, attack, exit): ";
        cin >> user_input;

        int prev_x = user_x;
        int prev_y = user_y;

        // 명령어에 따라 사용자 위치 변경
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

        // 맵을 벗어나는지 확인
        if (!CheckXY(user_x, MAP_X, user_y, MAP_Y)) {
            cout << "맵을 벗어났습니다. 다시 돌아갑니다." << endl;
            user_x = prev_x;
            user_y = prev_y;
            continue;
        }

        // 맵 표시 및 상태 확인
        DisplayMap(map, user_x, user_y, current_user);
        CheckState(map, user_x, user_y, *current_user);

        // HP 감소
        current_user->DecreaseHP(1);
        if (!CheckUser(current_user)) {
            cout << "HP가 0 이하입니다. 게임이 종료됩니다." << endl;
            break;
        }

        // 목표 지점에 도달했는지 확인
        if (CheckGoal(map, user_x, user_y)) {
            cout << "목적지에 도달했습니다! 축하합니다!" << endl;
            break;
        }
    }

    delete current_user;
    return 0;
}

// 맵 파일을 읽어서 2차원 벡터로 반환
vector<vector<int>> LoadMap(const string& file_name) {
    ifstream file(file_name);
    if (!file) {
        throw runtime_error("파일을 열 수 없습니다.");
    }

    int row, col;
    file >> row >> col;
    vector<vector<int>> map(row, vector<int>(col));

    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            if (!(file >> map[i][j])) {
                throw runtime_error("파일 형식이 잘못되었습니다.");
            }
        }
    }

    return map;
}

// 맵을 출력
void DisplayMap(const vector<vector<int>>& map, int user_x, int user_y, User* current_user) {
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[i].size(); j++) {
            if (i == user_y && j == user_x) {
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

// 사용자 위치가 맵 안에 있는지 확인
bool CheckXY(int user_x, int map_x, int user_y, int map_y) {
    return (user_x >= 0 && user_x < map_x && user_y >= 0 && user_y < map_y);
}

// 사용자가 목표 지점에 도달했는지 확인
bool CheckGoal(const vector<vector<int>>& map, int user_x, int user_y) {
    return map[user_y][user_x] == 4;
}

// 현재 위치의 상태를 확인하고 사용자 상태 변경
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

// 사용자의 HP가 0 이상인지 확인
bool CheckUser(User* user) {
    return user->GetHP() > 0;
}
