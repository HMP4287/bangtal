#include "stair.h"

// 생성자 구현 (최적화필요)
Stair::Stair() {
	srand((unsigned int)time(NULL));
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_ROOM_TITLE, false);

	Stair::setStages();


	//// stages 설정 
	//for (int i = 0; i < 3; i++) {
	//	sprintf(path1, "stage%d", i + 1);
	//	sprintf(path2, "Images/stage%d.png", i + 1);
	//	stages[i] = Scene::create(path1, path2);
	//	
	//}

	// Home 화면 설정 
	// drago 128*72 (발밑에 겹치게 컷)
	home = Scene::create("home", "Images/stage1.png");
	gameToy = Object::create("Images/gameToy.png", home, 256, 144);
	homeCharacter = Object::create("Images/dragon1.png", home, 576, 330);
	characterSelectBtn = Object::create("Images/characterSelectBtn.png", home, 512, 216);
	startBtn = Object::create("Images/startBtn.png", home, 640, 216);
	// Home 화면 설정 

	startBtn->setOnMouseCallback([&](auto, auto, auto, auto)->bool {
		// start 버튼 누르면 stages[0]부터 시작. 
		stages[0]->enter();
		return true;
	});

	// Block 좌표 설정 
	for (int i = 0; i < 10; i++) {
		dx[i] = 128 * i; 
		dy[i] = 648 - (72 * i);
	}

	// 캐릭터 생성 및 제일 아래 블럭 중간에 왼쪽 바라보는 캐릭터 생성
	for (int i = 0; i < 3; i++) {
		sprintf(path2, "Images/dragon%d.png", i + 1);
		characters[DRAGON][LEFT_STAND] = Object::create(path2, stages[i], dx[5], dy[9]);

		// 현재 캐릭터 위치 저장 
		characterPosition[0] = dx[5];
		characterPosition[1] = dy[9];
		characterPosition[2] = LEFT_STAND;

		// Block 생성 
		int beforeX = 5;
		int beforeY = 9;
		int curX;
		for (int curY = 8; curY >= 0; curY--) {
			curX = rand() % 2; // 0이면 좌, 1이면 우
			curX = curX == 0 ? -1 + beforeX : 1 + beforeX;
			if (curX < 9 && curX >= 0) { // 범위 안이라면, 
				// block make 
				blocks[curX][curY] = Object::create("Images/block.png", stages[i], dx[curX], dy[curY]); // stages[] 라서 함수로 빼기 ?
				beforeX = curX;
			}
			else {
				curY++;
				continue;
			}
		}
		stages[i]->setOnKeyboardCallback([&](ScenePtr scene, KeyCode key, bool pressed)->bool {
			if (key == KeyCode::KEY_RIGHT_ARROW) {
				printf("moveUP");
			}
			else if (key == KeyCode::KEY_LEFT_ARROW) {
				printf("changeMove");
			}
			return true;
		});
	}
	startGame(home);
}

void Stair::setStages() {

	// stages 설정 
	for (int i = 0; i < 3; i++) {
		sprintf(path1, "stage%d", i + 1);
		sprintf(path2, "Images/stage%d.png", i + 1);
		stages[i] = Scene::create(path1, path2);

	}
}
