#include <iostream>
#include <string>
using namespace std;

bool checkNumber(int a){
    bool b=false;
    string numStr = to_string(a);
        if((numStr[0]!=numStr[1])&&(numStr[1]!=numStr[2])&&(numStr[2]!=numStr[0])){
            b = true;
        }
    return b;
}

int main() {
	int randomNum; // 맞춰야 하는 3자리수의 숫자 저장 변수
	int firstNum; // 정답의 첫번째 자리수
	int secondNum; // 정답의 두번째 자리수
	int thirdNum; // 정답의 세번째 자리수

	while (1) {		
		randomNum = rand() % 900 + 100; // 랜덤한 3자리수 생성

		// TODO 1: 3자리 숫자의 자릿수를 추출하고, 모든 수가 다른지 체크하는 코드블록 작성
        bool same = checkNumber(randomNum); // 모든 수가 다를 경우 true를 갖는 변수

		if (same == true) {
			break;
		}
	}

    firstNum=randomNum/100;
    secondNum=(randomNum/10)%10;
    thirdNum=randomNum%10;

	int turn = 0;
	while (1) {
		cout << turn + 1 << "번째 시도입니다. " << endl;

		int userNumber; // 사용자가 입력한 세자리수 저장 변수
		int guessFirst; // 추측한 숫자의 첫번째 자리수
		int guessSecond; // 추측한 숫자의 두번째 자리수
		int guessThird; // 추측한 숫자의 세번째 자리수


		// 사용자에게 세자리 수를 입력받는 코드 블록
		while (1) {
			cout << "세자리 수를 입력해주세요: ";
			cin >> userNumber;

			
			// TODO 1: 3자리 숫자의 자릿수를 추출하고, 모든 수가 다른지 체크하는 코드블록 작성
            bool same = checkNumber(userNumber); // 모든 수가 다를 경우 true를 갖는 변수


			if (to_string(userNumber).length() != 3) {
				cout << "입력된 숫자가 3자리 수가 아닙니다. 다시 입력하세요." << endl;
				continue;
			}

			if (same == true) {
				break;
			}
		}

        guessFirst=userNumber/100;
        guessSecond=(userNumber/10)%10;
        guessThird=userNumber%10;


		int strike = 0; // 스트라이크 갯수를 저장하는 변수
		int ball = 0; // 볼 갯수를 저장하는 변수

		// TODO 2: 정답과 추측한 숫자의 자릿수와 숫자를 비교하며 힌트를 주기 위한 코드블록 작성
        if(firstNum == guessFirst)
            strike++;
        else if(firstNum == guessSecond || firstNum==guessThird)
            ball++;

        if(secondNum == guessSecond)
            strike++;
        else if(secondNum == guessFirst || secondNum == guessThird)
            ball++;
        
        if(thirdNum==guessThird)
            strike++;
        else if(thirdNum == guessSecond || thirdNum == guessFirst)
            ball++;
        
        
		

		cout << userNumber << "의 결과 : " << strike << " 스트라이크, " << ball << "볼 입니다." << endl;
		
		if (strike == 3) {
			cout << "정답을 맞췄습니다. 축하합니다.";
			break;
		}

		turn += 1;
	}

	return 0;
}
