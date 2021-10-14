#include "stair.h"

// 생성자 구현 (최적화필요)
Stair::Stair() {
	srand((unsigned int)time(NULL));
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_ROOM_TITLE, false);

	// stages 설정 
	Stair::setStages();

	// characters 설정 
	


	// Home 화면 설정 
	Stair::setHome(); 

	// startBtn 콜백 설정 
	Stair::setStartBtn();

	// Blocks 초기화  
	Stair::setBlockPosition();

	// stageNum에 따라서 화면 생성 
	Stair::makeBlocks(0);
	Stair::setCharacter(0, DRAGON); // 0stage에 캐릭터 생성 

	// stages의 keyboard 콜백 설정 
	Stair::setStagesKey();


	
	// blockIsExist 확인 
	//for (int i = 0; i < 10; i++) {
	//	for (int j = 0; j < 10; j++)
	//	{

	//		if (blocks[j][i])
	//			printf("%04d ", blocks[j][i]->ID());
	//		else
	//			printf("NULL ", blocks[j][i]);
	//	}
	//	printf("\n");
	//}
	startGame(home);
}

void Stair::setStages() {
	stage = 0;
	// stages 설정 
	for (int i = 0; i < 3; i++) {
		sprintf(path1, "stage%d", i + 1);
		sprintf(path2, "Images/stage%d.png", i + 1);
		stages[i] = Scene::create(path1, path2);
	}
}

void Stair::setHome() {
	home = Scene::create("home", "Images/stage1.png");
	gameToy = Object::create("Images/gameToy.png", home, 256, 144);
	// 현재선택된 캐릭터에 따라 달라져야함 
	homeCharacter = Object::create("Images/dragon1.png", home, 576, 330);  
	//ObjectPtr checkChar = Object::create("Images/dragon3.png", home, 576 + 64, 330 + 31);
	characterSelectBtn = Object::create("Images/characterSelectBtn.png", home, 512, 216);
	startBtn = Object::create("Images/startBtn.png", home, 640, 216);
}

void Stair::setStartBtn() {
	startBtn->setOnMouseCallback([&](auto, auto, auto, auto)->bool {
		stages[0]->enter();
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

void Stair::setStagesKey() {
	// 방향키 설정 
	for (int i = 0; i < 3; i++) {
		stages[i]->setOnKeyboardCallback([&](ScenePtr scene, KeyCode key, bool pressed)->bool {
			// dragon's height == i == 0층 == 최종층 도달했다면 다음 스테이지로 이동 
			if (pressed) {
				if (key == KeyCode::KEY_RIGHT_ARROW) {
			     	//현재 어딜 바라보고 있는가 
					if (characterS == LEFT_STAND) {
						sprintf(path2, characterName[characterN], LEFT_MOVE + 1);
						mainCharacter->setImage(path2);
						// 바라보는 방향의 다음 블록으로 이동. 
						mainCharacter->locate(scene, dj[--characterJ], di[--characterI] + 22); // 바닥 높이 22 고려해서 옴기기
						characterS = LEFT_MOVE;

						// 블럭위에 섰는지 확인 필요. 
						if (blocks[characterI][characterJ]) {
							// 최상위 블럭이라면 다음스테이지. 
							if (characterI == 0) {
								//validation check 필요 stage < 2
								stages[++stage]->enter();
							}
						}
						// 허공에 섰다면
						else {
							// 사망 모션 표현 후 게임 종료 점수판 화면으로 이동. -> 일단 endGame()으로 대체 
							endGame();
						}

					}
					else if (characterS == RIGHT_STAND) {
						sprintf(path2, characterName[characterN], RIGHT_MOVE + 1);
						mainCharacter->setImage(path2);
						mainCharacter->locate(scene, dj[++characterJ], di[--characterI] + 22); // 바닥 높이 22 고려해서 옴기기
						characterS = RIGHT_MOVE;
						// 블럭위에 섰는지 확인 필요. 
						if (blocks[characterI][characterJ]) {
							// 최상위 블럭이라면 다음스테이지. 
							if (characterI == 0) {
								//validation check 필요 stage < 2
								stages[++stage]->enter();
							}
						}
						// 허공에 섰다면
						else {
							// 사망 모션 표현 후 게임 종료 점수판 화면으로 이동. -> 일단 endGame()으로 대체 
							endGame();
						}
					}
				}
				// 방향 전환 & 이동 
				else if (key == KeyCode::KEY_LEFT_ARROW) {
					// 왼쪽 바라보고 있다면, 오른쪽 변환, 오른쪽 이동, 복구 
					if (characterS == LEFT_STAND) {
						sprintf(path2, characterName[characterN], RIGHT_MOVE + 1);
						mainCharacter->setImage(path2);
						// 바라보는 방향의 다음 블록으로 이동. 
						mainCharacter->locate(scene, dj[++characterJ], di[--characterI] + 22); // 바닥 높이 22 고려해서 옴기기
						characterS = RIGHT_MOVE;
						if (blocks[characterI][characterJ]) {
							// 최상위 블럭이라면 다음스테이지. 
							if (characterI == 0) {
								//validation check 필요 stage < 2
								stages[++stage]->enter();
							}
						}
						// 허공에 섰다면
						else {
							// 사망 모션 표현 후 게임 종료 점수판 화면으로 이동. -> 일단 endGame()으로 대체 
							endGame();
						}

					}
					else if (characterS == RIGHT_STAND) {
						sprintf(path2, characterName[characterN], LEFT_MOVE + 1);
						mainCharacter->setImage(path2);
						// 바라보는 방향의 다음 블록으로 이동. 
						mainCharacter->locate(scene, dj[--characterJ], di[--characterI] + 22); // 바닥 높이 22 고려해서 옴기기
						characterS = LEFT_MOVE;

						// 블럭위에 섰는지 확인 필요. 
						if (blocks[characterI][characterJ]) {
							// 최상위 블럭이라면 다음스테이지. 
							if (characterI == 0) {
								//validation check 필요 stage < 2
								stages[++stage]->enter();
							}
						}
						// 허공에 섰다면
						else {
							// 사망 모션 표현 후 게임 종료 점수판 화면으로 이동. -> 일단 endGame()으로 대체 
							endGame();
						}
					}
				}
			}
			// !pressed
			else {
				// 이동 모션 후 원상복구 
				if (characterS == LEFT_MOVE) {
					characterS = LEFT_STAND;
					sprintf(path2, characterName[characterN], LEFT_STAND + 1);
					mainCharacter->setImage(path2);
				}
				else if (characterS == RIGHT_MOVE) {
					characterS = RIGHT_STAND;
					sprintf(path2, characterName[characterN], RIGHT_STAND + 1);
					mainCharacter->setImage(path2);
				}
			}

			return true;
		});
	}
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
	int beforeI = 9;
	int curJ;
	for (int curI = 8; curI >= 0; curI--) {
		curJ = rand() % 2;
		curJ = curJ == 0 ? -1 + beforeJ : 1 + beforeJ;
		if (curJ < 8 && curJ > 1) {
			blocks[curI][curJ] = Object::create("Images/block.png", stages[stageNum], dj[curJ], di[curI]);
			beforeJ = curJ;
		}
		else
			curI++;
	}
}

void Stair::setCharacter(int stageNum, characterSelection name) {
	
	// 선택한 캐릭터, stage에서 첫 위치 설정 
	sprintf(path2, characterName[name], LEFT_STAND + 1);
	mainCharacter = Object::create(path2, stages[stageNum], dj[5], di[9]);
	characterI = 9;
	characterJ = 5;
	characterS = LEFT_STAND;
}
