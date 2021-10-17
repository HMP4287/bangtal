#include "stair.h"

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
	Stair::makeBlocks();
	Stair::setCharacter();
	Stair::setScoreBoard();
	Stair::setTimerBoard();
	Stair::setStageKey();
}

void Stair::setStageNum() {
	stage = 0;
}

void Stair::setHome() {
	home = Scene::create("home", stagesPath[0]);
	gameToy = Object::create("Images/gameToy.png", home, 256, 144);
	sprintf(path, charactersPath[characterN], LEFT_STAND + 1);
	homeCharacter = Object::create(path, home, 576, 330);  
	characterSelectBtn = Object::create("Images/characterSelectBtn.png", home, 512, 216);
	startBtn = Object::create("Images/startBtn.png", home, 640, 216);
}

void Stair::setStartBtn() {
	startBtn->setOnMouseCallback([&](auto, auto, auto, auto)->bool {
		// stages 초기화 
		Stair::setStageNum();
		// score 초기화 
		Stair::setScore();
		// timer 생성 및 초기화 
		Stair::setTimers();
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
				Stair::addScore();
				if (Stair::isOnTop()) {
					// 마지막 스테이지라면 마지막스테이지 반복 
					if (Stair::isFinalStage()) {
						Stair::setStage();
						stages[stage]->enter();
					}
					else {
						++stage;
						Stair::setStage();
						stages[stage]->enter();
					}
				}
			}
			// !onBlock
			else {
				Stair::setGameOver();
				gameOver->enter();
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
		if (curJ < 7 && curJ > 2) {  // 범위를 좁힐수록 다양한 패턴 생성 
			blocks[curI][curJ] = Object::create("Images/block.png", stages[stage], dj[curJ], di[curI]);
			beforeJ = curJ;
		}
		else
			curI++;
	}
}

void Stair::setCharacter() {
	sprintf(path, charactersPath[characterN], LEFT_STAND + 1);
	mainCharacter = Object::create(path, stages[stage], dj[5], di[9]);
	characterI = 9;
	characterJ = 5;
	characterS = LEFT_STAND;
}

void Stair::setCharacterNum(int characterName) {
	characterN = characterName;
}

void Stair::moveToLeft(ScenePtr scene) {
	sprintf(path, charactersPath[characterN], LEFT_MOVE + 1);
	mainCharacter->setImage(path);
	mainCharacter->locate(scene, dj[--characterJ], di[--characterI] + 22); 
	characterS = LEFT_MOVE;
}

void Stair::moveToRight(ScenePtr scene) {
	sprintf(path, charactersPath[characterN], RIGHT_MOVE + 1);
	mainCharacter->setImage(path);
	mainCharacter->locate(scene, dj[++characterJ], di[--characterI] + 22); 
	characterS = RIGHT_MOVE;
}

void Stair::moveBackLeft() {
	characterS = LEFT_STAND;
	sprintf(path, charactersPath[characterN], LEFT_STAND + 1);
	mainCharacter->setImage(path);
}

void Stair::moveBackRight() {
	characterS = RIGHT_STAND;
	sprintf(path, charactersPath[characterN], RIGHT_STAND + 1);
	mainCharacter->setImage(path);
}

bool Stair::isOnBlock() {
	return (blocks[characterI][characterJ]!=NULL);
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
	if (score < 10) {
		scoreNumbers[0]->hide();
		scoreNumbers[1]->hide();
		scoreNumbers[2]->setImage(scoresPath[score]);
		scoreNumbers[2]->show();
		scoreNumbers[3]->hide();
	}
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

	for (int i = 0; i < 5; i++)
		timers[i]->stop();

	homeCharacter->locate(gameOver, dj[characterJ], di[9]);
	deadRing = Object::create("Images/diyedRing.png", gameOver, dj[characterJ], di[8]);


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
		homeCharacter->locate(home, 576, 330);
		deadRing->hide();
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
	characterSelect = Scene::create("charSelect", stagesPath[3]);
	selectToy = Object::create("Images/charSelect.png", characterSelect, 256, 144);
	Stair::setCharacterSelectBtns();
}

void Stair::setCharacterSelectBtn() {
	characterSelectBtn->setOnMouseCallback([&](auto, auto, auto, auto)->bool {
		Stair::setCharacterSelect(); 
		characterSelect->enter();
		return true;
	});
}

void Stair::setCharacterSelectBtns() {
	characterSelectBtns[DRAGON] = Object::create("Images/selectBtn.png", characterSelect, 256 + 200 + (128 * 0), 216);

	characterSelectBtns[DRAGON]->setOnMouseCallback([&](auto, auto, auto, auto)->bool {
		Stair::setCharacterNum(DRAGON);
		sprintf(path, charactersPath[characterN], LEFT_STAND + 1);
		homeCharacter->setImage(path);
		home->enter();
		return true;
	});
	characterSelectBtns[HIPO] = Object::create("Images/selectBtn.png", characterSelect, 256 + 200 + (128 * 1), 216);
	characterSelectBtns[HIPO]->setOnMouseCallback([&](auto, auto, auto, auto)->bool {
		Stair::setCharacterNum(HIPO);
		sprintf(path, charactersPath[characterN], LEFT_STAND + 1);
		homeCharacter->setImage(path);
		home->enter();
		return true;
	});
	characterSelectBtns[DOG] = Object::create("Images/selectBtn.png", characterSelect, 256 + 200 + (128 * 2), 216);
	characterSelectBtns[DOG]->setOnMouseCallback([&](auto, auto, auto, auto)->bool {
		Stair::setCharacterNum(DOG);
		sprintf(path, charactersPath[characterN], LEFT_STAND + 1);
		homeCharacter->setImage(path);
		home->enter();
		return true;
	});
}


void Stair::setTimers() {
	for (int i = 0; i < 5; i++) {
		timerIsOff[i] = false;
		timerBars[i] = NULL;
		timers[i] = NULL;
	}

	timers[0] = Timer::create(30.f);
	timers[0]->setOnTimerCallback([&](TimerPtr)->bool {
		timerBars[0]->hide();
		timerIsOff[0] = true;
		Stair::setGameOver();
		gameOver->enter();
		return true;
	});
	timers[1] = Timer::create(24.f);
	timers[1]->setOnTimerCallback([&](TimerPtr)->bool {
		timerBars[1]->hide();
		timerIsOff[1] = true;
		return true;
	});
	timers[2] = Timer::create(18.f);
	timers[2]->setOnTimerCallback([&](TimerPtr)->bool {
		timerBars[2]->hide();
		timerIsOff[2] = true;
		return true;
	});
	timers[3] = Timer::create(12.f);
	timers[3]->setOnTimerCallback([&](TimerPtr)->bool {
		timerBars[3]->hide();
		timerIsOff[3] = true;
		return true;
	});
	timers[4] = Timer::create(6.f);
	timers[4]->setOnTimerCallback([&](TimerPtr)->bool {
		timerBars[4]->hide();
		timerIsOff[4] = true;
		return true;
	});

	timers[4]->start();
	timers[3]->start();
	timers[2]->start();
	timers[1]->start();
	timers[0]->start();
}

void Stair::setTimerBoard() {
	
	timerBoard = Object::create("Images/timerBoard.png", stages[stage], dj[7] + 64, di[2]);
	timerBars[0] = Object::create("Images/redbar.png", stages[stage], dj[7] + 72, di[2] + 24);
	timerBars[1] = Object::create("Images/jubar.png", stages[stage], dj[7] + 72 + 47, di[2] + 24);
	timerBars[2] = Object::create("Images/yellbar.png", stages[stage], dj[7] + 72 + 47 + 47, di[2] + 24);
	timerBars[3] = Object::create("Images/greenbar.png", stages[stage], dj[7] + 72 + 47 + 47 + 47, di[2] + 24);
	timerBars[4] = Object::create("Images/bluebar.png", stages[stage], dj[7] + 72 + 47 + 47 + 47 + 47, di[2] + 24);

	for (int i = 0; i < 5; i++) {
		if (timerIsOff[i]) {
			timerBars[i]->hide();
		}
	}
}

bool Stair::isOnTop() {
	return (characterI == 0);
}

bool Stair::isFinalStage() {
	return (stage >= 3);
}
