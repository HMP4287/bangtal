#include "stair.h"

// 생성자 구현
Stair::Stair() {
	srand((unsigned int)time(NULL));
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_ROOM_TITLE, false);

	// 코드 순서가 프로그렘에 지장이 없는 순

	// stages 설정 
	Stair::setStages();

	// Blocks 초기화  
	Stair::setBlockPosition();

	// stageNum에 따라서 화면 생성
	// startBtn 누르고나서 설정하고 표시해도 된다. 
	// setStages()아래에만 있으면 된다.
	Stair::makeBlocks(stage); // blocks 배열을 1개만 만들기 위해 스테이지 블럭을 각각생성 

	// characters 설정 
	Stair::setCharacter(stage, DRAGON); // 0stage에 캐릭터 생성 
	// stages의 keyboard 콜백 설정 
	// setCharacter 이후에 setStagesKey() 와야함 
	Stair::setStageKey(stage);

	// Home 화면 설정 
	Stair::setHome(); 
	// startBtn 콜백 설정 
	Stair::setStartBtn();



	
	startGame(home);
}

void Stair::setStages() {
	stage = 0;
	// stages 설정 
	for (int i = 0; i < 4; i++) {
		sprintf(path1, "stage%d", i + 1);
		sprintf(path2, "Images/stage%d.png", i + 1);
		stages[i] = Scene::create(path1, path2);
	}
}

void Stair::setHome() {
	home = Scene::create("home", "Images/stage1.png");
	gameToy = Object::create("Images/gameToy.png", home, 256, 144);
	// 현재선택된 캐릭터에 따라 달라져야함 
	// 코드의 실행순서가 문제 
	sprintf(path2, charactersPath[characterN], LEFT_STAND + 1);
	homeCharacter = Object::create(path2, home, 576, 330);  
	//mainCharacter = Object::create("Images/dragon1.png", home, 576, 330);  

	//ObjectPtr checkChar = Object::create("Images/dragon3.png", home, 576 + 64, 330 + 31);
	characterSelectBtn = Object::create("Images/characterSelectBtn.png", home, 512, 216);
	startBtn = Object::create("Images/startBtn.png", home, 640, 216);
}

void Stair::setStartBtn() {
	startBtn->setOnMouseCallback([&](auto, auto, auto, auto)->bool {
		stages[stage]->enter();
		return true;
	});
}

void Stair::setBlockPosition() {
	// Block 좌표 설정 
	for (int i = 0; i < 10; i++) {
		di[i] =  648 - (72 * i);
		dj[i] = 128 * i;
	}
}

void Stair::setStageKey(int stageNum) {
	// 방향키 설정 
	stages[stageNum]->setOnKeyboardCallback([&](ScenePtr scene, KeyCode key, bool pressed)->bool {
		if (pressed) {
			if (key == KeyCode::KEY_RIGHT_ARROW) {
				if (characterS == LEFT_STAND) {
					Stair::moveToLeft(scene);
				}
				else if (characterS == RIGHT_STAND) {
					Stair::moveToRight(scene);
				}
			}
			// 방향 전환 & 이동 
			else if (key == KeyCode::KEY_LEFT_ARROW) {
				if (characterS == LEFT_STAND) {
					Stair::moveToRight(scene);
				}
				else if (characterS == RIGHT_STAND) {
					Stair::moveToLeft(scene);
				}
			}

			// Validation 
			if (Stair::isOnBlock()) {
				// 제일 위 블록에 도착 시 다음 스테이지로 이동. 
				if (characterI == 0) {
					if (stage < 3) {
						++stage; 
						Stair::setStageKey(stage);
						Stair::makeBlocks(stage);
						Stair::setCharacter(stage, characterN);
						stages[stage]->enter();
					}
					// 마지막스테이지라면, 마지막스테이지 반복. 
					else {
						stages[stage] = Scene::create("stage4", "Images/stage4.png");
						Stair::setStageKey(stage);
						Stair::makeBlocks(stage);
						Stair::setCharacter(stage, characterN);
						stages[stage]->enter();
					
					}
				}
			}
			else {
				endGame();
			}
		}

		// !pressed
		else {
			// 이동 모션 후 원상복구 
			if (characterS == LEFT_MOVE) {
				Stair::moveBackLeft();
			}
			else if (characterS == RIGHT_MOVE) {
				Stair::moveBackRight();
			}
		}

		return true;
	});
}


void Stair::makeBlocks(int stageNum) {

	// blocks 초기화 
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			blocks[i][j] = NULL;
		}
	}
	// Block 생성 
	int beforeJ = 5;
	int curJ;
	for (int curI = 8; curI >= 0; curI--) {
		curJ = rand() % 2;
		curJ = curJ == 0 ? -1 + beforeJ : 1 + beforeJ;
		if (curJ < 7 && curJ > 2) {  // 범위를 좁힐수록 다양한 패턴, 
			blocks[curI][curJ] = Object::create("Images/block.png", stages[stageNum], dj[curJ], di[curI]);
			beforeJ = curJ;
		}
		else
			curI++;
	}
}

void Stair::setCharacter(int stageNum, int characterName) {
	// 선택한 캐릭터, stage에서 첫 위치 설정 
	sprintf(path2, charactersPath[characterName], LEFT_STAND + 1);
	//mainCharacter->locate(stages[stageNum], dj[5], di[9]);
	mainCharacter = Object::create(path2, stages[stageNum], dj[5], di[9]);
	characterI = 9;
	characterJ = 5;
	characterS = LEFT_STAND;
	characterN = characterName;
}

void Stair::moveToLeft(ScenePtr scene) {
	sprintf(path2, charactersPath[characterN], LEFT_MOVE + 1);
	mainCharacter->setImage(path2);
	mainCharacter->locate(scene, dj[--characterJ], di[--characterI] + 22); // 바닥 높이 22 고려해서 옴기기
	characterS = LEFT_MOVE;
}

void Stair::moveToRight(ScenePtr scene) {
	sprintf(path2, charactersPath[characterN], RIGHT_MOVE + 1);
	mainCharacter->setImage(path2);
	mainCharacter->locate(scene, dj[++characterJ], di[--characterI] + 22); // 바닥 높이 22 고려해서 옴기기
	characterS = RIGHT_MOVE;
}

void Stair::moveBackLeft() {
	characterS = LEFT_STAND;
	sprintf(path2, charactersPath[characterN], LEFT_STAND + 1);
	mainCharacter->setImage(path2);
}

void Stair::moveBackRight() {
	characterS = RIGHT_STAND;
	sprintf(path2, charactersPath[characterN], RIGHT_STAND + 1);
	mainCharacter->setImage(path2);
}

bool Stair::isOnBlock() {
	return (blocks[characterI][characterJ]!=NULL);
}
