#include <iostream>
using namespace std;

const int numCell = 5; // 보드판의 크기 설정
char board[numCell][numCell]{}; // 전역 변수 보드판

// 유효성 체크 함수
bool isValid(int x, int y) {
    if (x < 0 || y < 0 || x >= numCell || y >= numCell) { // 좌표 범위 벗어남
        cout << x << ", " << y << ": 좌표가 보드판을 벗어났습니다." << endl;
        return false;
    }
    if (board[x][y] != ' ') { // 이미 다른 돌이 있음
        cout << x << ", " << y << ": 이미 돌이 놓여 있습니다." << endl;
        return false;
    }
    return true;
}

// 승리 체크 함수
bool checkWin(char currentUser) {
    // 가로, 세로 체크
    for (int i = 0; i < numCell; i++) {
        bool rowWin = true;
        bool colWin = true;
        for (int j = 0; j < numCell; j++) {
            if (board[i][j] != currentUser) {
                rowWin = false;
            }
            if (board[j][i] != currentUser) {
                colWin = false;
            }
        }
        if (rowWin) {
            cout << "가로에 모두 돌이 놓였습니다!!" << endl;
            return true;
        }
        if (colWin) {
            cout << "세로에 모두 돌이 놓였습니다!!" << endl;
            return true;
        }
    }

    // 대각선 체크
    bool leftToRight = true;
    bool rightToLeft = true;
    for (int i = 0; i < numCell; i++) {
        if (board[i][i] != currentUser) {
            leftToRight = false;
        }
        if (board[i][numCell - 1 - i] != currentUser) {
            rightToLeft = false;
        }
    }
    if (leftToRight) {
        cout << "왼쪽 위에서 오른쪽 아래 대각선으로 모두 돌이 놓였습니다!" << endl;
        return true;
    }
    if (rightToLeft) {
        cout << "오른쪽 위에서 왼쪽 아래 대각선으로 모두 돌이 놓였습니다!" << endl;
        return true;
    }

    return false; // 승리 조건이 만족되지 않음
}

int main() {
    int k = 0;  // 차례
    char currentUser = 'X';

    // 보드판 초기화
    for (int i = 0; i < numCell; i++) {
        for (int j = 0; j < numCell; j++) {
            board[i][j] = ' ';
        }
    }

    while (true) {
        // 1. 누구 차례인지 출력
        switch (k % 3) {
            case 0: currentUser = 'X'; break;
            case 1: currentUser = 'O'; break;
            case 2: currentUser = 'H'; break;
        }
        cout << k % 3 + 1 << "번 유저(" << currentUser << ")의 차례입니다. -> ";

        // 2. 좌표 입력 받기
        cout << "(x, y) 좌표를 입력하세요: ";
        int x, y;
        cin >> x >> y;

        // 3. 유효성 체크 함수 호출
        if (!isValid(x, y)) continue;

        // 4. 현재 유저의 돌 놓기
        board[x][y] = currentUser;

        // 5. 현재 보드 판 출력
        for (int i = 0; i < numCell; i++) {
            for (int j = 0; j < numCell - 1; j++) cout << "---|";
            cout << "---" << endl;
            for (int j = 0; j < numCell; j++) {
                cout << board[i][j];
                if (j < numCell - 1) cout << "  |";
            }
            cout << endl;
        }
        for (int i = 0; i < numCell - 1; i++) cout << "---|";
        cout << "---" << endl;

        // 6. 승리 체크 함수 호출
        if (checkWin(currentUser)) {
            cout << k % 3 + 1 << "번 유저(" << currentUser << ")의 승리입니다!" << endl;
            break;
        }

        // 7. 모든 칸이 다 찼는지 체크
        int checked = 0;
        for (int i = 0; i < numCell; i++) {
            for (int j = 0; j < numCell; j++) {
                if (board[i][j] == ' ') checked++;
            }
        }
        if (checked == 0) {
            cout << "모든 칸이 다 찼습니다. 종료합니다." << endl;
            break;
        }

        k++;
    }
}