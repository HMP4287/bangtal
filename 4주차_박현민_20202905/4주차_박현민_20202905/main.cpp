//#include <bangtal>
//using namespace bangtal;

//int main() {
	// 1280 X 720
//	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	//setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);

//	auto outerScene = Scene::create("외곽퍼즐", "Images/background.png");
//	auto startButton = Object::create("Images/startButton.png", outerScene, 450, 100); 

//	startButton->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool{
//		if (checkIn(x, y))
		
	//)


	
	//startGame(outerScene);
	//return 0;
	
//}

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
int hided[2]; 
int hidedId;


int check(int clicked_id) {
   // 상하 좌우로 확인후 갈 곳이 있으면 이동. 
    printf("cli %d\n", clicked_id);
    printf("hid %d\n", hidedId);




    return 0;
}
typedef struct _Node {
    ObjectPtr puzzleData;
    int puzzleNumber;
};


int main()
{

    setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
    setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);
    setGameOption(GameOption::GAME_OPTION_ROOM_TITLE, false);

    auto outerScene = Scene::create("외곽퍼즐", "Images/backGround.png");
    auto innerScene = Scene::create("안쪽퍼즐", "Images/blankBackgroundLast.png");


    //auto countTime = Timer::create(30.f);
    
    //int x[9] = { 322 , 522, 722, 322 , 522, 722, 322 , 522, 722 };
    //int y[9] = { 449, 449, 449, 249, 249, 249, 49, 49, 49 };
    // 
    // 랜덤 배열 생성 
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

    // 반복문 사용 시 편의를 위해 반대로하여 사용 
    //int y[3] = { 322 , 522, 722 };
    //int x[3] = { 449, 249, 49 };

    // ObjectPtr puzzlesDataReal[3][3]; 

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
    hided[0] = 2;
    hided[1] = 2;
    puzzlesDataReal[2][2]->hide();
    hidedId = puzzlesDataReal[2][2]->ID();



    //ObjectPtr puzzlesDataTemp[3][3] = {
    //    {
    //        Object::create(one, innerScene, 322, 449),
    //        Object::create("Images/2.png", innerScene, 522, 449),
    //        Object::create("Images/3.png", innerScene, 722, 449)
    //    },
    //    {
    //        Object::create("Images/4.png", innerScene, 322, 249),
    //        Object::create("Images/5.png", innerScene, 522, 249),
    //        Object::create("Images/6.png", innerScene, 722, 249)
    //    },
    //    {
    //        Object::create("Images/7.png", innerScene, 322, 49),
    //        Object::create("Images/8.png", innerScene, 522, 49),
    //        Object::create("Images/9.png", innerScene, 722, 49)
    //    }
    //};



    //ObjectPtr puzzlesDataTemp[9] = {
    //
    //    Object::create("Images/1.png", innerScene, 322, 449),
    //    Object::create("Images/2.png", innerScene, 522, 449),
    //    Object::create("Images/3.png", innerScene, 722, 449),
   
    //    Object::create("Images/4.png", innerScene, 322, 249),
    //    Object::create("Images/5.png", innerScene, 522, 249),
    //    Object::create("Images/6.png", innerScene, 722, 249),
   
    //    Object::create("Images/7.png", innerScene, 322, 49),
    //    Object::create("Images/8.png", innerScene, 522, 49),
    //    Object::create("Images/9.png", innerScene, 722, 49)
    //};



    auto startButton = Object::create("Images/startButton.png", outerScene, 450, 100);
    startButton->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
        innerScene->Scene::enter();

        return true;
        });

    startGame(outerScene);

    return 0;
}