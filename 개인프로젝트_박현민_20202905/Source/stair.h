#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <bangtal> 
#include <string>
#include <cstdlib>
#include <ctime>

using namespace bangtal;
using std::string;

class Stair
{
private:
	// �ӽ� ���� ���� 
	char path1[10];
	char path2[20];
	
	// home ���� (���� stages, caracters�迭���� �����ϵ��� ���� ���)
	ScenePtr home;
	ObjectPtr gameToy;
	ObjectPtr homeCharacter;  // ���ȭ�� ĳ���� 
	ObjectPtr characterSelectBtn;
	ObjectPtr startBtn;



	// in Game ���� 



	ObjectPtr moveBtn;
	ObjectPtr changeMoveBtn;
	// ȭ��, �� �� ĳ���� 
	ScenePtr stages[3];
	int stage; 
	// stages ���� �ϳ��� �ʿ� -> stages ������ �� ���� �����. setBlock���� stages �Է¹޾�, �ش� ������������ ������ 
	ObjectPtr blocks[10][10];
	// stages ������ block ��ġ
	// 
	//bool blockIsExist[10][10]; // Stages ���� 3�� �� �ʿ��ϴ�.. ->blocks������ Ȯ���� ��� ã�� 

	// select ĳ���� 
	enum characterSelection {DRAGON, BIRD, DOG};
	char characterName[3][20] = {"Images/dragon%d.png", "Images/dragon%d.png", "Images/dragon%d.png"};
	int characterI;
	int characterJ;
	int characterS; //status
	int characterN; //name 


	// �� ��ǥ ���� 
	int di[10]; 
	int dj[10];

	// ĳ���� ��ǥ�� ���� 
	int characterPosition[3]; // x, y, enum direction (LEFT_STAND, RIGHT_STAND) 

	// ȭ��, �� �� ĳ���� 

	enum characterStatus {LEFT_STAND, RIGHT_STAND, LEFT_MOVE, RIGHT_MOVE};
	//direction characterStatus;
	//ObjectPtr characters[3][4]; // �¼��ֱ�, ���̵�, �켭�ֱ�, ���̵�
	ObjectPtr mainCharacter; 

	int MOVE_MAX;
	int MOVE_MIN;





public:
	Stair();

	// setter 
	void setStages();
	void setHome(); // Ȩȭ�� ĳ���� �Է°� 
	void setStartBtn(); // stage1 
	void setBlockPosition(); // ��� ��ǥ �ʱ�ȭ 
	void setStagesKey();

	void setCharacter(int stageNum, characterSelection name); 
	
	// making func
	void makeBlocks(int stageNum); 
	// moving func
	void standToMove();
	void moveToStand();

};
