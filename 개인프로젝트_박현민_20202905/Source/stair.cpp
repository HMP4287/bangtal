#include "stair.h"

// ������ ����
Stair::Stair() {
	srand((unsigned int)time(NULL));
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_ROOM_TITLE, false);

	// �ڵ� ������ ���α׷��� ������ ���� ��

	// stages ���� 
	Stair::setStages();

	// Blocks �ʱ�ȭ  
	Stair::setBlockPosition();

	// stageNum�� ���� ȭ�� ����
	// startBtn �������� �����ϰ� ǥ���ص� �ȴ�. 
	// setStages()�Ʒ����� ������ �ȴ�.
	Stair::makeBlocks(stage); // blocks �迭�� 1���� ����� ���� �������� ���� �������� 

	// characters ���� 
	Stair::setCharacter(stage, DRAGON); // 0stage�� ĳ���� ���� 
	// stages�� keyboard �ݹ� ���� 
	// setCharacter ���Ŀ� setStagesKey() �;��� 
	Stair::setStageKey(stage);

	// Home ȭ�� ���� 
	Stair::setHome(); 
	// startBtn �ݹ� ���� 
	Stair::setStartBtn();



	
	startGame(home);
}

void Stair::setStages() {
	stage = 0;
	// stages ���� 
	for (int i = 0; i < 4; i++) {
		sprintf(path1, "stage%d", i + 1);
		sprintf(path2, "Images/stage%d.png", i + 1);
		stages[i] = Scene::create(path1, path2);
	}
}

void Stair::setHome() {
	home = Scene::create("home", "Images/stage1.png");
	gameToy = Object::create("Images/gameToy.png", home, 256, 144);
	// ���缱�õ� ĳ���Ϳ� ���� �޶������� 
	// �ڵ��� ��������� ���� 
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
	// Block ��ǥ ���� 
	for (int i = 0; i < 10; i++) {
		di[i] =  648 - (72 * i);
		dj[i] = 128 * i;
	}
}

void Stair::setStageKey(int stageNum) {
	// ����Ű ���� 
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
			// ���� ��ȯ & �̵� 
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
				// ���� �� ��Ͽ� ���� �� ���� ���������� �̵�. 
				if (characterI == 0) {
					if (stage < 3) {
						++stage; 
						Stair::setStageKey(stage);
						Stair::makeBlocks(stage);
						Stair::setCharacter(stage, characterN);
						stages[stage]->enter();
					}
					// �����������������, �������������� �ݺ�. 
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
			// �̵� ��� �� ���󺹱� 
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

	// blocks �ʱ�ȭ 
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			blocks[i][j] = NULL;
		}
	}
	// Block ���� 
	int beforeJ = 5;
	int curJ;
	for (int curI = 8; curI >= 0; curI--) {
		curJ = rand() % 2;
		curJ = curJ == 0 ? -1 + beforeJ : 1 + beforeJ;
		if (curJ < 7 && curJ > 2) {  // ������ �������� �پ��� ����, 
			blocks[curI][curJ] = Object::create("Images/block.png", stages[stageNum], dj[curJ], di[curI]);
			beforeJ = curJ;
		}
		else
			curI++;
	}
}

void Stair::setCharacter(int stageNum, int characterName) {
	// ������ ĳ����, stage���� ù ��ġ ���� 
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
	mainCharacter->locate(scene, dj[--characterJ], di[--characterI] + 22); // �ٴ� ���� 22 ����ؼ� �ȱ��
	characterS = LEFT_MOVE;
}

void Stair::moveToRight(ScenePtr scene) {
	sprintf(path2, charactersPath[characterN], RIGHT_MOVE + 1);
	mainCharacter->setImage(path2);
	mainCharacter->locate(scene, dj[++characterJ], di[--characterI] + 22); // �ٴ� ���� 22 ����ؼ� �ȱ��
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
