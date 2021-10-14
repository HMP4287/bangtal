#include "stair.h"

// ������ ���� (����ȭ�ʿ�)
Stair::Stair() {
	srand((unsigned int)time(NULL));
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_ROOM_TITLE, false);

	// stages ���� 
	Stair::setStages();

	// characters ���� 
	


	// Home ȭ�� ���� 
	Stair::setHome(); 

	// startBtn �ݹ� ���� 
	Stair::setStartBtn();

	// Blocks �ʱ�ȭ  
	Stair::setBlockPosition();

	// stageNum�� ���� ȭ�� ���� 
	Stair::makeBlocks(0);
	Stair::setCharacter(0, DRAGON); // 0stage�� ĳ���� ���� 

	// stages�� keyboard �ݹ� ���� 
	Stair::setStagesKey();


	
	// blockIsExist Ȯ�� 
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
	// stages ���� 
	for (int i = 0; i < 3; i++) {
		sprintf(path1, "stage%d", i + 1);
		sprintf(path2, "Images/stage%d.png", i + 1);
		stages[i] = Scene::create(path1, path2);
	}
}

void Stair::setHome() {
	home = Scene::create("home", "Images/stage1.png");
	gameToy = Object::create("Images/gameToy.png", home, 256, 144);
	// ���缱�õ� ĳ���Ϳ� ���� �޶������� 
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
	// Block ��ǥ ���� 
	for (int i = 0; i < 10; i++) {
		di[i] =  648 - (72 * i);
		dj[i] = 128 * i;
	}
}

void Stair::setStagesKey() {
	// ����Ű ���� 
	for (int i = 0; i < 3; i++) {
		stages[i]->setOnKeyboardCallback([&](ScenePtr scene, KeyCode key, bool pressed)->bool {
			// dragon's height == i == 0�� == ������ �����ߴٸ� ���� ���������� �̵� 
			if (pressed) {
				if (key == KeyCode::KEY_RIGHT_ARROW) {
			     	//���� ��� �ٶ󺸰� �ִ°� 
					if (characterS == LEFT_STAND) {
						sprintf(path2, characterName[characterN], LEFT_MOVE + 1);
						mainCharacter->setImage(path2);
						// �ٶ󺸴� ������ ���� ������� �̵�. 
						mainCharacter->locate(scene, dj[--characterJ], di[--characterI] + 22); // �ٴ� ���� 22 ����ؼ� �ȱ��
						characterS = LEFT_MOVE;

						// ������ ������ Ȯ�� �ʿ�. 
						if (blocks[characterI][characterJ]) {
							// �ֻ��� ���̶�� ������������. 
							if (characterI == 0) {
								//validation check �ʿ� stage < 2
								stages[++stage]->enter();
							}
						}
						// ����� ���ٸ�
						else {
							// ��� ��� ǥ�� �� ���� ���� ������ ȭ������ �̵�. -> �ϴ� endGame()���� ��ü 
							endGame();
						}

					}
					else if (characterS == RIGHT_STAND) {
						sprintf(path2, characterName[characterN], RIGHT_MOVE + 1);
						mainCharacter->setImage(path2);
						mainCharacter->locate(scene, dj[++characterJ], di[--characterI] + 22); // �ٴ� ���� 22 ����ؼ� �ȱ��
						characterS = RIGHT_MOVE;
						// ������ ������ Ȯ�� �ʿ�. 
						if (blocks[characterI][characterJ]) {
							// �ֻ��� ���̶�� ������������. 
							if (characterI == 0) {
								//validation check �ʿ� stage < 2
								stages[++stage]->enter();
							}
						}
						// ����� ���ٸ�
						else {
							// ��� ��� ǥ�� �� ���� ���� ������ ȭ������ �̵�. -> �ϴ� endGame()���� ��ü 
							endGame();
						}
					}
				}
				// ���� ��ȯ & �̵� 
				else if (key == KeyCode::KEY_LEFT_ARROW) {
					// ���� �ٶ󺸰� �ִٸ�, ������ ��ȯ, ������ �̵�, ���� 
					if (characterS == LEFT_STAND) {
						sprintf(path2, characterName[characterN], RIGHT_MOVE + 1);
						mainCharacter->setImage(path2);
						// �ٶ󺸴� ������ ���� ������� �̵�. 
						mainCharacter->locate(scene, dj[++characterJ], di[--characterI] + 22); // �ٴ� ���� 22 ����ؼ� �ȱ��
						characterS = RIGHT_MOVE;
						if (blocks[characterI][characterJ]) {
							// �ֻ��� ���̶�� ������������. 
							if (characterI == 0) {
								//validation check �ʿ� stage < 2
								stages[++stage]->enter();
							}
						}
						// ����� ���ٸ�
						else {
							// ��� ��� ǥ�� �� ���� ���� ������ ȭ������ �̵�. -> �ϴ� endGame()���� ��ü 
							endGame();
						}

					}
					else if (characterS == RIGHT_STAND) {
						sprintf(path2, characterName[characterN], LEFT_MOVE + 1);
						mainCharacter->setImage(path2);
						// �ٶ󺸴� ������ ���� ������� �̵�. 
						mainCharacter->locate(scene, dj[--characterJ], di[--characterI] + 22); // �ٴ� ���� 22 ����ؼ� �ȱ��
						characterS = LEFT_MOVE;

						// ������ ������ Ȯ�� �ʿ�. 
						if (blocks[characterI][characterJ]) {
							// �ֻ��� ���̶�� ������������. 
							if (characterI == 0) {
								//validation check �ʿ� stage < 2
								stages[++stage]->enter();
							}
						}
						// ����� ���ٸ�
						else {
							// ��� ��� ǥ�� �� ���� ���� ������ ȭ������ �̵�. -> �ϴ� endGame()���� ��ü 
							endGame();
						}
					}
				}
			}
			// !pressed
			else {
				// �̵� ��� �� ���󺹱� 
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

	// blocks �ʱ�ȭ 
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			blocks[i][j] = NULL;
		}
	}
	// Block ���� 
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
	
	// ������ ĳ����, stage���� ù ��ġ ���� 
	sprintf(path2, characterName[name], LEFT_STAND + 1);
	mainCharacter = Object::create(path2, stages[stageNum], dj[5], di[9]);
	characterI = 9;
	characterJ = 5;
	characterS = LEFT_STAND;
}
