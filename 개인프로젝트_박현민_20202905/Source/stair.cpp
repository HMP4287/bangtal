#include "stair.h"

// 생성자 구현
Stair::Stair() {
	srand((unsigned int)time(NULL));
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_ROOM_TITLE, false);

	// Blocks 좌표 초기화 
	Stair::setBlockPosition();

	// 드래곤으로 캐릭터 초기화 
	Stair::setCharacterNum(DRAGON);

	// 최고기록 초기화 
	Stair::setBestScore(0);

	// Home 화면 설정 
	Stair::setHome(); 

	


	// 게임 start 설정  
	Stair::setStartBtn();
	Stair::setCharacterSelectBtn();
	
	startGame(home);
}

void Stair::setStage() {
	
	stages[stage] = Scene::create(stagesName[stage], stagesPath[stage]);
	Stair::makeBlocks(); // blocks 배열을 1개만 만들기 위해 스테이지 블럭을 각각생성 
	// 캐릭터 스테이지에 위치시키기 
	Stair::setCharacter(); // 0stage에 캐릭터 생성 


	Stair::setScoreBoard();
	
	
	Stair::setStageKey();
}

void Stair::setStageNum() {
	stage = 0;
}

void Stair::setHome() {
	home = Scene::create("home", stagesPath[0]);
	gameToy = Object::create("Images/gameToy.png", home, 256, 144);
	// 현재선택된 캐릭터에 따라 달라져야함 
	sprintf(path2, charactersPath[characterN], LEFT_STAND + 1);
	homeCharacter = Object::create(path2, home, 576, 330);  
	//mainCharacter = Object::create(path2, home, 576, 330);  

	//ObjectPtr checkChar = Object::create("Images/dragon3.png", home, 576 + 64, 330 + 31);
	characterSelectBtn = Object::create("Images/characterSelectBtn.png", home, 512, 216);
	startBtn = Object::create("Images/startBtn.png", home, 640, 216);
}

void Stair::setStartBtn() {
	startBtn->setOnMouseCallback([&](auto, auto, auto, auto)->bool {
		// stages 초기화 
		Stair::setStageNum();
		
		// timer 초기화 
		// score 초기화 
		Stair::setScore();
		// stage 생성 
		Stair::setStage();

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

void Stair::setStageKey() {
	// 방향키 설정 
	stages[stage]->setOnKeyboardCallback([&](ScenePtr scene, KeyCode key, bool pressed)->bool {
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

			// Validation 
			if (Stair::isOnBlock()) {
				// 제일 위 블록에 도착 시 다음 스테이지로 이동. 
				// score 올리고 보여주기 

				Stair::addScore();



				if (characterI == 0) {
					if (stage < 3) {
						++stage;
						Stair::setStage();
						stages[stage]->enter();
					}
					// 마지막스테이지라면, 마지막스테이지 반복. 
					else {
						Stair::setStage();
						stages[stage]->enter();
					}
				}
			}
			else {
				//dyingAction();
				//if (Stair::isBestScore())
				//	Stair::setBestScore(score);
				//
				Stair::setGameOver();
				gameOver->enter();

				//endGame();
			}
		}

		return true;
	});
}


void Stair::makeBlocks() {

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
			blocks[curI][curJ] = Object::create("Images/block.png", stages[stage], dj[curJ], di[curI]);
			beforeJ = curJ;
		}
		else
			curI++;
	}
}

void Stair::setCharacter() {
	// 선택한 캐릭터, stage에서 첫 위치 설정 
	sprintf(path2, charactersPath[characterN], LEFT_STAND + 1);
	//mainCharacter->locate(stages[stageNum], dj[5], di[9]);
	mainCharacter = Object::create(path2, stages[stage], dj[5], di[9]);
	//mainCharacter->locate(stages[stage], dj[5], di[9]);
	characterI = 9;
	characterJ = 5;
	characterS = LEFT_STAND;
}

void Stair::setCharacterNum(int characterName) {
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

void Stair::dyingAction() {
	ScenePtr dyingScene = Scene::create(stagesName[stage], stagesPath[stage]);
	mainCharacter->locate(dyingScene, dj[characterJ], di[characterI]);
	dyingScene->enter(); 
	for (int i = 0; i < 10; i++) {
		printf("DYINGING~~~");
		Sleep(1000);
	}
}

void Stair::setScore() {
	score = 0;
}
void Stair::setBestScore(int score) {
	bestScore = score; 
}

void Stair::setScoreBoard() {
	scoreBoard = Object::create("Images/back.png", stages[stage], dj[0] + 64 + 0, di[1]);
	scoreNumbers[0] = Object::create(scoresPath[0], stages[stage], dj[0] + 64, di[2]); 
	scoreNumbers[1] = Object::create(scoresPath[0], stages[stage], dj[0] + 64 + 33, di[2]);
	scoreNumbers[2] = Object::create(scoresPath[0], stages[stage], dj[0] + 64 + 33 + 33, di[2]);
	scoreNumbers[3] = Object::create(scoresPath[10], stages[stage], dj[0] + 64 + 33 + 33 + 33, di[2]);
	Stair::setScoreNumbers();
}
void Stair::addScore() {
	score++; 
	Stair::setScoreNumbers();
}

void Stair::setScoreNumbers() {
	// 숫자 패드 다시 만들어서 보여줘야 함. 
// 한 자릿수라면 중간좌표(dj[0] + 64 + 33)에 숫자표시할거
	if (score < 10) {
		scoreNumbers[0]->hide();
		scoreNumbers[1]->hide();
		scoreNumbers[2]->setImage(scoresPath[score]);
		scoreNumbers[2]->show();
		scoreNumbers[3]->hide();
	}
	// 두 자리 중간좌표 + 세번쨰좌표 
	else if (score < 100) {
		string numStr = std::to_string(score);

		int a = numStr.at(0) - '0';
		int b = numStr.at(1) - '0';
		scoreNumbers[0]->hide();

		scoreNumbers[1]->setImage(scoresPath[a]);
		scoreNumbers[1]->show();

		scoreNumbers[2]->setImage(scoresPath[b]);
		scoreNumbers[2]->show();
		scoreNumbers[3]->hide();
	}
	else if (score < 1000) {
		string numStr = std::to_string(score);

		int a = numStr.at(0) - '0';
		int b = numStr.at(1) - '0';
		int c = numStr.at(2) - '0';
		scoreNumbers[0]->setImage(scoresPath[a]);
		scoreNumbers[0]->show();
		scoreNumbers[1]->setImage(scoresPath[b]);
		scoreNumbers[1]->show();
		scoreNumbers[2]->setImage(scoresPath[c]);
		scoreNumbers[2]->show();
		scoreNumbers[3]->hide();
	}
	else {
		scoreNumbers[3]->show();
		score = 999;
	}
}

bool Stair::isBestScore() {
	return (score > bestScore);
}

void Stair::setGameOver() {
	gameOver = Scene::create("gameOver", stagesPath[0]);
	gameToy = Object::create("Images/gameOver.png", gameOver, 256, 72);
	homeBtn = Object::create("Images/homeBtn.png", gameOver, 512, 186);
	if (Stair::isBestScore()) {
		scoreBoard = Object::create("Images/bestScore.png", gameOver, 556, 400);
		Stair::setGameOverScore();
		Stair::setBestScore(score);
	}
	else {
		scoreBoard = Object::create("Images/back.png", gameOver, 556, 400);
		Stair::setGameOverScore();
	}
	Stair::setHomeBtn();

	startBtn->locate(gameOver, 640, 186);
}

void Stair::setHomeBtn() {
	homeBtn->setOnMouseCallback([&](auto, auto, auto, auto)->bool {
		startBtn->locate(home, 640, 216);
		home->enter();
		return true;
	});
}

void Stair::setGameOverScore() {
	scoreBoard->setScale(1.5f);
	scoreNumbers[0] = Object::create(scoresPath[0], gameOver, 566, 328);
	scoreNumbers[1] = Object::create(scoresPath[0], gameOver, 566 + 33, 328);
	scoreNumbers[2] = Object::create(scoresPath[0], gameOver, 566 + 33 + 33, 328);
	scoreNumbers[3] = Object::create(scoresPath[10], gameOver, 566 + 33 + 33 + 33, 328);
	Stair::setScoreNumbers();
}

void Stair::setCharacterSelect() {
	//characterSelect = Scene::create("charSelect", "Images/charSelect.png");
	////gameToy = Object::create("Images/selection.png", characterSelect, 256, 144);


	//for (int i = 0; i < 3; i++) {
	//	sprintf(path1, "selectBtn%d", i + 1);
	//	characterSelectBtns[i] = Object::create("Images/selectBtn.png", characterSelect, 256 + 200 + (128 * i), 216);

	//	characterSelectBtns[i]->setOnMouseCallback([&](auto, auto, auto, auto)->bool {
	//		Stair::setCharacterNum(i);
	//		sprintf(path2, charactersPath[characterN], LEFT_STAND + 1);
	//		homeCharacter->setImage(path2);
	//		//Stair::setHome();
	//		//characterSelect->enter();
	//		home->enter();
	//		return true;
	//	});
	//}
}

void Stair::setCharacterSelectBtn() {
	characterSelectBtn->setOnMouseCallback([&](auto, auto, auto, auto)->bool {
		Stair::setCharacterSelect(); 
		characterSelect->enter();
		return true;
	});
}
