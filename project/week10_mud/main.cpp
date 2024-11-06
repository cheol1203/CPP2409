#include <iostream>
#include "user.h"
#include <string>
#include <vector>
using namespace std;

const int mapX = 5;
const int mapY = 5;

// 사용자 정의 함수
bool checkXY(int user_x, int mapX, int user_y, int mapY);
void displayMap(const vector<vector<int>>& map, int user_x, int user_y);
bool checkGoal(const vector<vector<int>>& map, int user_x, int user_y);
void checkState(const vector<vector<int>>& map, int user_x, int user_y, User &user); // 상태 체크 함수
bool CheckUser(User user);
// 메인  함수
int main() {
	// 0은 빈 공간, 1은 아이템, 2는 적, 3은 포션, 4는 목적지
	vector<vector<int>> map = { {0, 1, 2, 0, 4},
					        	{1, 0, 0, 2, 0},
					        	{0, 0, 0, 0, 0},
					        	{0, 2, 3, 0, 0},
					        	{3, 0, 0, 0, 2} };


	// 유저의 위치를 저장할 변수
	int user_x = 0; // 가로 번호
	int user_y = 0; // 세로 번호
    User user; //유저 객체 생성

	// 게임 시작 
	while (1) { // 사용자에게 계속 입력받기 위해 무한 루프

		// 사용자의 입력을 저장할 변수
		string user_input = "";

		cout << "현재 HP: "<< user.GetHP() << " 명령어를 입력하세요 (up,down,left,right,map,exit): ";
		cin >> user_input;

		int prev_x = user_x; // 이전 위치 저장
        int prev_y = user_y;

        // 이동에 따른 좌표 변경
        if (user_input == "up") user_y -= 1;
        else if (user_input == "down") user_y += 1;
        else if (user_input == "left") user_x -= 1;
        else if (user_input == "right") user_x += 1;
        else if (user_input == "map"){
            displayMap(map, user_x, user_y);
            continue;
        } //지도 보여주기 함수 호출
        else if (user_input == "exit") {
            cout << "종료합니다." << endl;
            break;
        } else {
            cout << "잘못된 입력입니다." << endl;
            continue;
        }

        // 맵 유효성 체크 및 원상복구
        if (!checkXY(user_x, mapX, user_y, mapY)) {
            cout << "맵을 벗어났습니다. 다시 돌아갑니다." << endl;
            user_x = prev_x;
            user_y = prev_y;
            continue;
        }

        // 이동 메시지 출력
        if (user_input == "up") cout << "위로 한 칸 올라갑니다." << endl;
        else if (user_input == "down") cout << "아래로 한 칸 내려갑니다." << endl;
        else if (user_input == "left") cout << "왼쪽으로 이동합니다." << endl;
        else if (user_input == "right") cout << "오른쪽으로 이동합니다." << endl;

        displayMap(map, user_x, user_y);
        checkState(map, user_x, user_y, user);
        
        // 체력 감소 및 상태 체크
        user.DecreaseHP(1); // 이동 시 체력 1 감소

        if (!CheckUser(user)) {
            cout << "HP가 0 이하가 되었습니다. 실패했습니다." << endl;
            break;
        }

		// 목적지에 도달했는지 체크
		bool finish = checkGoal(map, user_x, user_y);
		if (finish == true) {
			cout << "목적지에 도착했습니다! 축하합니다!" << endl;
			cout << "게임을 종료합니다." << endl;
			break;
		}

	}
	return 0;
}

// 지도와 사용자 위치 출력하는 함수
void displayMap(const vector<vector<int>>& map, int user_x, int user_y) {
	for (int i = 0; i < mapY; i++) {
		for (int j = 0; j < mapX; j++) {
			if (i == user_y && j == user_x) {
				cout << " USER |"; // 양 옆 1칸 공백
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
		cout << " -------------------------------- " << endl;
	}
}

// 이동하려는 곳이 유효한 좌표인지 체크하는 함수
bool checkXY(int user_x, int mapX, int user_y, int mapY) {
	bool checkFlag = false;
	if (user_x >= 0 && user_x < mapX && user_y >= 0 && user_y < mapY) {
		checkFlag = true;
	}
	return checkFlag;
}

// 유저의 위치가 목적지인지 체크하는 함수
bool checkGoal(const vector<vector<int>>& map, int user_x, int user_y) {
	// 목적지 도착하면
	if (map[user_y][user_x] == 4) {
		return true;
	}
	return false;
}

// 유저가 만난 대상에 따라 체력이 증감하는 함수
void checkState(const vector<vector<int>>& map, int user_x, int user_y, User &user) {
    int state = map[user_y][user_x];
    switch (state) {
        case 1:
            cout << "아이템이 있습니다." << endl;
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

bool CheckUser(User user){
    return user.GetHP() > 0;
}