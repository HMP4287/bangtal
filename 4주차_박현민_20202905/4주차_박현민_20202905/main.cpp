#include <bangtal>
#include <iostream>
#include <time.h>
#include <stdio.h>
#include <string.h>

using namespace std;
using namespace bangtal;

ScenePtr outerScene;
ObjectPtr puzzlesDataReal[3][3];
int puzzlesMap[3][3]; 
int y[3] = { 322 , 522, 722 };
int x[3] = { 449, 249, 49 };
int dx[4] = {-1, 1, 0, 0};
int dy[4] = { 0, 0, -1, 1 };
int hidedId;

// 미완성 
void swapPuzzles(int fromX, int fromY, int toX, int toY) {
    puzzlesDataReal[fromX][fromY]->locate(outerScene, 49, 722);
   // puzzlesDataReal[fromX][Y]->locate(outerScene, y[toX], x[toY]);
    //puzzlesDataReal[toX][toY]->locate(outerScene, y[fromX], x[fromY]);

    ObjectPtr temp;
    temp = puzzlesDataReal[fromX][fromY];
    puzzlesDataReal[fromX][fromY] = puzzlesDataReal[toX][toY];
    puzzlesDataReal[toX][toY] = temp;
    // check needed
    hidedId = puzzlesDataReal[toX][toY]->ID();
}

bool check(int clickedId) {

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (puzzlesDataReal[i][j]->ID() == clickedId) {
                // 상하좌우에 hidedId 가 있는지 확인. 
                for (int k = 0; k < 4; k++) {
                    // 배열 범위 안 일때 
                    int nx = dx[k] + i;
                    int ny = dy[k] + j; 
                    if (nx < 3 && nx >= 0 && ny < 3 && ny >= 0 && puzzlesDataReal[nx][ny]->ID() == hidedId) {
                        printf("OK\n");
                        swapPuzzles(i, j, nx, ny); // fromx fromy tox toy 
                        return true; 
                    }
                }
            }
        }
    }
    printf("NO\n");
    return false;
}
bool isEqual() {
   
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (puzzlesMap[i][j] != puzzlesDataReal[i][j]->ID())
                return false; 
        }
    }
    return true; 
}

// ID() 가 계속 변할 수 있다. 
int main()
{

    setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
    setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);
    setGameOption(GameOption::GAME_OPTION_ROOM_TITLE, false);

    outerScene = Scene::create("외곽퍼즐", "Images/backGround.png");
    auto innerScene = Scene::create("안쪽퍼즐", "Images/blankBackgroundLast.png");


    //auto countTime = Timer::create(30.f); 
    // 랜덤 퍼즐 위치 생성 
    srand((unsigned int)time(NULL));
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

                printf("%d\n", object->ID());
                if (check(object->ID())) { // 주변에 이동할 수 있다면 이동 (이동 후 정답인지 확인), 없다면 아무것도 안한다. 
                    if (isEqual()) {
                        endGame();
                    }
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

    auto endButton = Object::create("Images/endButton.png", innerScene, 900, 100); 
    endButton->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
        endGame();
        return true;
        });
    startGame(outerScene);

    return 0;
}
