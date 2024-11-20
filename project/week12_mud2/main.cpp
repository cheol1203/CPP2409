#include <iostream>
#include "user.h"
#include <string>
#include <vector>
using namespace std;

const int MAP_X = 5;
const int MAP_Y = 5;

// 사용자 정의 함수
bool CheckXY(int user_x, int mapX, int user_y, int mapY);
void DisplayMap(const vector<vector<int>>& map, int magician_x, int magician_y, int warrior_x, int warrior_y);
bool CheckGoal(const vector<vector<int>>& map, int user_x, int user_y);
void CheckState(const vector<vector<int>>& map, int user_x, int user_y, User &user); // 상태 체크 함수
bool CheckUser(User user);

int main() {
    // 0은 빈 공간, 1은 아이템, 2는 적, 3은 포션, 4는 목적지
    vector<vector<int>> map = { {0, 1, 2, 0, 4},
                                {1, 0, 0, 2, 0},
                                {0, 0, 0, 0, 0},
                                {0, 2, 3, 0, 0},
                                {3, 0, 0, 0, 2} };

    // 유저의 위치를 저장할 변수
    int* current_x = nullptr; // 현재 캐릭터의 x 좌표
    int* current_y = nullptr; // 현재 캐릭터의 y 좌표
    Magician magician; // Magician 객체 생성
    Warrior warrior;   // Warrior 객체 생성
    User* current_user = &magician; // 기본적으로 Magician이 먼저 시작
    int k=0; //차례
    int magician_x = 0, magician_y = 0; // Magician의 위치
    int warrior_x = 0, warrior_y = 0;   // Warrior의 위치

    // 게임 시작
    while (true) {
        string user_input = ""; // 사용자의 입력을 저장할 변수
        switch (k % 2) {
            case 0: current_user = &magician; break;
            case 1: current_user = &warrior; break;
        }
        current_x = (current_user == &magician) ? &magician_x : &warrior_x;
        current_y = (current_user == &magician) ? &magician_y : &warrior_y; // magician, warrior 각각의 차례일 때 각각의 위치 저장
        cout << "현재 플레이어: " << (current_user == &magician ? "Magician" : "Warrior") << endl; // 현재 플레이어 출력
        cout << "현재 "<< (current_user == &magician ? "Magician" : "Warrior") << "의 HP: " << current_user->GetHP()
             << " 명령어를 입력하세요 (up,down,left,right,map,info,attack,exit): ";
        cin >> user_input;

        int prev_x = *current_x; // 이전 위치 저장
        int prev_y = *current_y;

        // 이동에 따른 좌표 변경
        if (user_input == "up") *current_y -= 1;
        else if (user_input == "down") *current_y += 1;
        else if (user_input == "left") *current_x -= 1;
        else if (user_input == "right") *current_x += 1;
        else if (user_input == "map") {
            DisplayMap(map, magician_x, magician_y, warrior_x, warrior_y);
            continue;
        } // 지도 보여주기 함수 호출
        else if (user_input == "info") {
            cout << *current_user << endl;
            continue;
        } else if (user_input == "attack") {
            // 현재 유저의 공격 실행
            current_user->DoAttack();
            continue;
        } else if (user_input == "exit") {
            cout << "게임을 종료합니다." << endl;
            break;
        } else {
            cout << "잘못된 입력입니다." << endl;
            continue;
        }

        // 맵 유효성 체크 및 원상복구
        if (!CheckXY(*current_x, MAP_X, *current_y, MAP_Y)) {
            cout << "맵을 벗어났습니다. 다시 돌아갑니다." << endl;
            *current_x = prev_x;
            *current_y = prev_y;
            continue;
        }

        // 이동 메시지 출력
        if (user_input == "up") cout << "위로 한 칸 올라갑니다." << endl;
        else if (user_input == "down") cout << "아래로 한 칸 내려갑니다." << endl;
        else if (user_input == "left") cout << "왼쪽으로 이동합니다." << endl;
        else if (user_input == "right") cout << "오른쪽으로 이동합니다." << endl;

        DisplayMap(map, magician_x, magician_y, warrior_x, warrior_y);
        CheckState(map, *current_x, *current_y, *current_user);
        
        // 체력 감소 및 상태 체크
        current_user->DecreaseHP(1); // 이동 시 체력 1 감소

        if (!CheckUser(*current_user)) {
            cout << "HP가 0 이하가 되었습니다. " << (current_user == &magician ? "Magician" : "Warrior") << "이(가) 실패했습니다." << endl;
            break;
        }

        // 목적지에 도달했는지 체크
        bool finish = CheckGoal(map, *current_x, *current_y);
        if (finish == true) {
            cout << "목적지에 도착했습니다! 축하합니다!" << endl;
            cout << "게임을 종료합니다." << endl;
            break;
        }
        k++;
    }
    return 0;
}

// 지도와 사용자 위치 출력하는 함수
void DisplayMap(const vector<vector<int>>& map, int magician_x, int magician_y, int warrior_x, int warrior_y) {
    for (int i = 0; i < MAP_Y; i++) {
        for (int j = 0; j < MAP_X; j++) {
           // 두 캐릭터가 같은 위치에 있을 경우 처리
            if (i == magician_y && j == magician_x && i == warrior_y && j == warrior_x) {
                cout << " MA&WA|"; // 두 캐릭터를 합쳐서 표시
            }
            // Magician만 있는 경우
            else if (i == magician_y && j == magician_x) {
                cout << " MAGIC|";
            }
            // Warrior만 있는 경우
            else if (i == warrior_y && j == warrior_x) {
                cout << " WARRI|";
            }
            else {
                int posState = map[i][j];
                switch (posState) {
                case 0:
                    cout << "      |"; // 6칸 공백
                    break;
                case 1:
                    cout << "아이템|";
                    break;
                case 2:
                    cout << "  적  |"; // 양 옆 2칸 공백
                    break;
                case 3:
                    cout << " 포션 |"; // 양 옆 1칸 공백
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

// 이동하려는 곳이 유효한 좌표인지 체크하는 함수
bool CheckXY(int user_x, int mapX, int user_y, int mapY) {
    return (user_x >= 0 && user_x < mapX && user_y >= 0 && user_y < mapY);
}

// 유저의 위치가 목적지인지 체크하는 함수
bool CheckGoal(const vector<vector<int>>& map, int user_x, int user_y) {
    return map[user_y][user_x] == 4;
}

// 유저가 만난 대상에 따라 체력이 증감하는 함수
void CheckState(const vector<vector<int>>& map, int user_x, int user_y, User &user) {
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

bool CheckUser(User user) {
    return user.GetHP() > 0;
}
