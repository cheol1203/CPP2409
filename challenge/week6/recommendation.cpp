#include <iostream>
using namespace std;

const int NUM_USERS = 3;
const int NUM_ITEMS = 3;
int userPreferences[NUM_USERS][NUM_ITEMS];

void initializePreferences(int preferences[NUM_USERS][NUM_ITEMS]){
    
    // 사용자와 항목 간의 선호도를 입력 받아 2차원 배열 초기화
    for(int i = 0; i < NUM_USERS; ++i){
        cout << "사용자 " << (i + 1) << "의 선호도를 입력하세요 (";
        cout << NUM_ITEMS << "개의 항목에 대해): ";
        for (int j =0; j < NUM_ITEMS;++j){
            cin >> userPreferences[i][j];
        }
    }
}

void findRecommendedItems(const int preferences[NUM_USERS][NUM_ITEMS]){
    
    // 각 사용자에 대한 추천 항목 찾기
    for (int i =0; i < NUM_USERS; ++i){
        int maxPreferenceIndex = 0;
        for (int j =1; j < NUM_ITEMS;++j){
            if (userPreferences[i][j] > userPreferences[i][maxPreferenceIndex]){
                maxPreferenceIndex = j;
            }
        }

        // 사용자에게 추천하는 항목 출력
        cout << "사용자 " << (i + 1) << "에게 추천하는 항목: ";
        cout << (maxPreferenceIndex + 1) << std::endl;
    }
}
int main(){

    //선호도를 초기화하고 사용자에게 추천할 항목 찾기
    initializePreferences(userPreferences);
    findRecommendedItems(userPreferences);

    return 0;
}