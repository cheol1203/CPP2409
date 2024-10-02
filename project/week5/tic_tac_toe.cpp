#include <iostream>
using namespace std;

int main() {
    const int numCell = 3;
    char board[numCell][numCell];
    char currentUser = 'X'; 
    int x, y;

    // 1. 보드 초기화
    for (int i = 0; i < numCell; i++) {
        for (int j = 0; j < numCell; j++) {
            board[i][j] = ' ';
        }
    }

    while (true) {
        

        // 1. 누구의 차례인지 출력
        // 2. 좌표 입력 받기
        cout << "(" << currentUser << ") 차례입니다. 좌표를 입력하세요 (x y): ";
        cin >> x >> y;

        // 3. 입력 받은 좌표 유효성 체크
        if (x < 0 || x >= numCell || y < 0 || y >= numCell || board[x][y] != ' ') {
            cout << "잘못된 입력입니다. 다시 시도하세요." << endl;
            continue;
        }

        // 4. 보드에 돌을 놓기
        board[x][y] = currentUser;

        // 5. 현재 보드판 출력
        for (int i = 0; i < numCell; i++) {
            cout << "---|---|---" << endl;
            for (int j = 0; j < numCell; j++) {
                cout << " " << board[i][j];
                if (j < numCell - 1) cout << " |";
            }
            cout << endl;
        }
        cout << "---|---|---" << endl;

        // 승리 조건 확인
        bool a = false;

        // 가로 확인
        for (int i = 0; i < numCell; i++) {
            if (board[x][i] != currentUser) {
                break;
            }
            if (i == numCell - 1) {
                a = true;
            }
        }

        // 세로 확인
        for (int i = 0; i < numCell; i++) {
            if (board[i][y] != currentUser) {
                break;
            }
            if (i == numCell - 1) {
                a = true;
            }
        }

        // 대각선 확인 (왼쪽 위에서 오른쪽 아래로)
        if (x == y) {
            for (int i = 0; i < numCell; i++) {
                if (board[i][i] != currentUser) {
                    break;
                }
                if (i == numCell - 1) {
                    a = true;
                }
            }
        }

        // 대각선 확인 (오른쪽 위에서 왼쪽 아래로)
        if (x + y == numCell - 1) {
            for (int i = 0; i < numCell; i++) {
                if (board[i][(numCell - 1) - i] != currentUser) {
                    break;
                }
                if (i == numCell - 1) {
                    a = true;
                }
            }
        }

        // 6. 빙고 시 승자 출력 후 종료
        if (a) {
            for (int i = 0; i < numCell; i++) {
                cout << "---|---|---" << endl;
                for (int j = 0; j < numCell; j++) {
                    cout << " " << board[i][j];
                    if (j < numCell - 1) cout << " |";
                }
                cout << endl;
            }
            cout << "---|---|---" << endl;

            cout << currentUser << "가 승리했습니다!" << endl;
            break;
        }

        // 7. 모든 칸이 찼으면 종료
        bool b = true;
        for (int i = 0; i < numCell; i++) {
            for (int j = 0; j < numCell; j++) {
                if (board[i][j] == ' ') {
                    b = false;
                    break;
                }
            }
            if (!b) {
                break;
            }
        }

        if (b) {
            for (int i = 0; i < numCell; i++) {
                cout << "---|---|---" << endl;
                for (int j = 0; j < numCell; j++) {
                    cout << " " << board[i][j];
                    if (j < numCell - 1) cout << " |";
                }
                cout << endl;
            }
            cout << "---|---|---" << endl;

            cout << "무승부입니다!" << endl;
            break;
        }

     // 플레이어 교체
        currentUser = (currentUser == 'X') ? 'O' : 'X';   
    }

    return 0;
}