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
	// 임시 변수 관련 
	char path1[10];
	char path2[20];
	
	// home 관련 (추후 stages, caracters배열에서 추출하도록 변경 고려)
	ScenePtr home;
	ObjectPtr gameToy;
	ObjectPtr homeCharacter;
	ObjectPtr characterSelectBtn;
	ObjectPtr startBtn;



	// in Game 관련 
	ObjectPtr moveBtn;
	ObjectPtr changeMoveBtn;
	// 화면, 블럭 및 캐릭터 
	ScenePtr stages[3];
	ObjectPtr blocks[10][10];
	bool blockIsExist[10][10];

	// select 캐릭터 
	enum characterSelection {DRAGON};

	// 블럭 좌표 저장 
	int dx[10]; 
	int dy[10];

	// 캐릭터 좌표와 방향 
	int characterPosition[3]; // x, y, enum direction (LEFT_STAND, RIGHT_STAND) 

	// 화면, 블럭 및 캐릭터 

	enum Moves {LEFT_STAND, RIGHT_STAND, LEFT_MOVE, RIGHT_MOVE};
	//direction characterStatus;
	ObjectPtr characters[3][4]; // 좌서있기, 좌이동, 우서있기, 우이동






public:
	Stair();
	void setStages();
};
