#include <iostream>
#include <string>
using namespace std;

// 소문자로 변환하는 함수
string toLowerStr(string str) {
    for (char &c : str) {
        if (c >= 'A' && c <= 'Z') {
            c += 'a' - 'A';
        }
    }
    return str;
}

// 대문자로 변환하는 함수
string toUpperStr(string str) {
    for (char &c : str) {
        if (c >= 'a' && c <= 'z') {
            c -= 'a' - 'A';
        }
    }
    return str;
}

// 해밍 거리 계산 함수 (대소문자 무시)
int calcHammingDist(string s1, string s2) {
    s1 = toLowerStr(s1);
    s2 = toLowerStr(s2);
    
    int count = 0;
    for (int i = 0; i < s1.length(); i++) {
        if (s1[i] != s2[i]) {
            count++;
        }
    }
    return count;
}

int main() {
    string s1, s2;
    
    while (true) {
        cout << "첫 번째 문자열 입력: ";
        cin >> s1;
        cout << "두 번째 문자열 입력: ";
        cin >> s2;
        
        if (s1.length() == s2.length()) {
            break;
        } else {
            cout << "문자열의 길이가 같지 않습니다. 다시 입력해주세요." << endl;
        }
    }
    
    int count = calcHammingDist(s1, s2);
    cout << "해밍 거리는: " << count << endl;

    return 0;
}