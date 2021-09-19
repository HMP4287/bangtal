#include <bangtal>
#include <iostream>
#include <time.h>
#include <stdio.h>
#include <string.h>

using namespace std;
using namespace bangtal;


ObjectPtr puzzlesDataReal[3][3];
int y[3] = { 322 , 522, 722 };
int x[3] = { 449, 249, 49 };
int hidedId;


int check(int clickedId) {
   // 상하 좌우로 확인후 갈 곳이 있으면 이동. 
    //printf("cli %d\n", clickedId);
    //printf("hid %d\n", hidedId);

    // 갈곳과 위치변경. 

    return 0;
}

int main()
{

    setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
    setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);
    setGameOption(GameOption::GAME_OPTION_ROOM_TITLE, false);

    auto outerScene = Scene::create("외곽퍼즐", "Images/backGround.png");
    auto innerScene = Scene::create("안쪽퍼즐", "Images/blankBackgroundLast.png");


    //auto countTime = Timer::create(30.f); 
    // 랜덤 퍼즐 위치 생성 
    srand((unsigned int)time(NULL));
    int puzzlesMap[3][3];
    bool usedNumber[9] = { false, };
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            int temp = rand() % 9 + 1;  // 1 - 9 
            if (usedNumber[temp - 1]) {
                j--;
                continue;
            }
            puzzlesMap[i][j] = temp;
            usedNumber[temp - 1] = true;
        }
    }

    int idx = 0; 
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {

            puzzlesDataReal[i][j] = Object::create("Images/" + std::to_string(puzzlesMap[i][j]) + ".png", innerScene, y[j], x[i]);
            puzzlesDataReal[i][j]->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
                
                if (check(object->ID())) { // 주변에 이동할 수 있다면 이동 (이동 후 정답인지 확인), 없다면 아무것도 안한다. 
                    
                }
                return true;
                });

        }
    }

    // 9번 퍼즐
    puzzlesDataReal[2][2]->hide();
    hidedId = puzzlesDataReal[2][2]->ID();

    auto startButton = Object::create("Images/startButton.png", outerScene, 450, 100);
    startButton->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
        innerScene->Scene::enter();
        return true;
        });

    startGame(outerScene);

    return 0;
}
