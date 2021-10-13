#include "stair.h"

// ������ ���� (����ȭ�ʿ�)
Stair::Stair() {
	srand((unsigned int)time(NULL));
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_ROOM_TITLE, false);

	Stair::setStages();


	//// stages ���� 
	//for (int i = 0; i < 3; i++) {
	//	sprintf(path1, "stage%d", i + 1);
	//	sprintf(path2, "Images/stage%d.png", i + 1);
	//	stages[i] = Scene::create(path1, path2);
	//	
	//}

	// Home ȭ�� ���� 
	// drago 128*72 (�߹ؿ� ��ġ�� ��)
	home = Scene::create("home", "Images/stage1.png");
	gameToy = Object::create("Images/gameToy.png", home, 256, 144);
	homeCharacter = Object::create("Images/dragon1.png", home, 576, 330);
	characterSelectBtn = Object::create("Images/characterSelectBtn.png", home, 512, 216);
	startBtn = Object::create("Images/startBtn.png", home, 640, 216);
	// Home ȭ�� ���� 

	startBtn->setOnMouseCallback([&](auto, auto, auto, auto)->bool {
		// start ��ư ������ stages[0]���� ����. 
		stages[0]->enter();
		return true;
	});

	// Block ��ǥ ���� 
	for (int i = 0; i < 10; i++) {
		dx[i] = 128 * i; 
		dy[i] = 648 - (72 * i);
	}

	// ĳ���� ���� �� ���� �Ʒ� �� �߰��� ���� �ٶ󺸴� ĳ���� ����
	for (int i = 0; i < 3; i++) {
		sprintf(path2, "Images/dragon%d.png", i + 1);
		characters[DRAGON][LEFT_STAND] = Object::create(path2, stages[i], dx[5], dy[9]);

		// ���� ĳ���� ��ġ ���� 
		characterPosition[0] = dx[5];
		characterPosition[1] = dy[9];
		characterPosition[2] = LEFT_STAND;

		// Block ���� 
		int beforeX = 5;
		int beforeY = 9;
		int curX;
		for (int curY = 8; curY >= 0; curY--) {
			curX = rand() % 2; // 0�̸� ��, 1�̸� ��
			curX = curX == 0 ? -1 + beforeX : 1 + beforeX;
			if (curX < 9 && curX >= 0) { // ���� ���̶��, 
				// block make 
				blocks[curX][curY] = Object::create("Images/block.png", stages[i], dx[curX], dy[curY]); // stages[] �� �Լ��� ���� ?
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

	// stages ���� 
	for (int i = 0; i < 3; i++) {
		sprintf(path1, "stage%d", i + 1);
		sprintf(path2, "Images/stage%d.png", i + 1);
		stages[i] = Scene::create(path1, path2);

	}
}
