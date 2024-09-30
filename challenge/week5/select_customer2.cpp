#include <iostream>
#include <string>
using namespace std;

int main(){
    const int maxPeople = 5;
    string names[maxPeople];
    int ages[maxPeople];

    cout << maxPeople << "명의 회원 정보를 입력해주세요." << endl;

    for (int i = 0; i <maxPeople; i++){
        cout << "사람 " << i+1 << "의 이름: ";
        cin >> names[i];
        cout << "사람 " << i+1 << "의 나이: ";
        cin >> ages[i];

       
    }

    int choice;
    cout << "메뉴를 선택하세요" << endl;
    cout << "1. 가장 나이가 많은 사람 출력" << endl;
    cout << "2. 가장 나이가 적은 사람 출력" << endl;
    cout << "3. 종료" << endl;
    cin >> choice;

    switch (choice) {
        case 1: { // 가장 나이가 많은 사람 출력
            int max_age = ages[0];
            int max_index = 0;
            for (int i = 1; i < maxPeople; i++) {
                if (ages[i] > max_age) {
                    max_age = ages[i];
                    max_index = i;
                }
            }
            cout << "가장 나이가 많은 사람은 " << names[max_index] << " (" << ages[max_index] << "세) 입니다." << endl;
            break;
        }
        case 2: { // 가장 나이가 적은 사람 출력
            int min_age = ages[0];
            int min_index = 0;
            for (int i = 1; i < maxPeople; i++) {
                if (ages[i] < min_age) {
                    min_age = ages[i];
                    min_index = i;
                }
            }
            for (int i = 0; i < maxPeople; i++) {
                if (ages[i] == min_age) {
                    cout << "가장 나이가 적은 사람은 " << names[i] << " (" << ages[i] << "세) 입니다." << endl;
                }
            }
            break;
        }
        case 3: // 프로그램 종료
            cout << "프로그램을 종료합니다." << endl;
            break;
        default: // 그 외 숫자 입력 시 메시지 출력 후 종료
            cout << "잘못된 입력입니다. 프로그램을 종료합니다." << endl;
            break;
    }

    

    return 0;
}