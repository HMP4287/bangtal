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
	ObjectPtr homeCharacter;
	ObjectPtr characterSelectBtn;
	ObjectPtr startBtn;



	// in Game ���� 
	ObjectPtr moveBtn;
	ObjectPtr changeMoveBtn;
	// ȭ��, �� �� ĳ���� 
	ScenePtr stages[3];
	ObjectPtr blocks[10][10];
	bool blockIsExist[10][10];

	// select ĳ���� 
	enum characterSelection {DRAGON};

	// �� ��ǥ ���� 
	int dx[10]; 
	int dy[10];

	// ĳ���� ��ǥ�� ���� 
	int characterPosition[3]; // x, y, enum direction (LEFT_STAND, RIGHT_STAND) 

	// ȭ��, �� �� ĳ���� 

	enum Moves {LEFT_STAND, RIGHT_STAND, LEFT_MOVE, RIGHT_MOVE};
	//direction characterStatus;
	ObjectPtr characters[3][4]; // �¼��ֱ�, ���̵�, �켭�ֱ�, ���̵�






public:
	Stair();
	void setStages();
};
