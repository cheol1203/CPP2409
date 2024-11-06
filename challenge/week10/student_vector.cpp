#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<int> scores;
    int score;

    while (true){
        cout << "성적을 입력하세요 (종료는 -1) : ";
        cin >> score;
        if (score == -1){ // 종료 조건
            break;
        }
        scores.push_back(score); // 벡터에 성적 추가
    }

    int sum = 0;
    for (int s : scores){
        sum += s; // 성적의 합 계산
    }
    double average = (double)sum / scores.size(); // 평균 계산
    cout << "성적 평균=" << average << endl;

    return 0;
}