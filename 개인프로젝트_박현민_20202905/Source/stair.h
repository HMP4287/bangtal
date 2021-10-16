#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <bangtal> 
#include <string>
#include <cstdlib>
#include <ctime>
#include <windows.h>

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
	ScenePtr gameOver;
	ObjectPtr gameToy;
	ObjectPtr homeCharacter;  // 배경화면 캐릭터 
	ObjectPtr characterSelectBtn;
	ObjectPtr startBtn;
	ObjectPtr homeBtn;



	// in Game 관련 
	int bestScore;
	int score;
	ObjectPtr scoreNumbers[4]; // 0 ~ 999
	char scoresPath[11][15] = { "Images/0.png", "Images/1.png", "Images/2.png", "Images/3.png", "Images/4.png", "Images/5.png", "Images/6.png", "Images/7.png", "Images/8.png", "Images/9.png", "Images/+.png"};


	ObjectPtr moveBtn;
	ObjectPtr changeMoveBtn;
	// 화면, 블럭 및 캐릭터 
	ScenePtr stages[4];
	char stagesPath[4][20] = { "Images/stage1.png", "Images/stage2.png", "Images/stage3.png", "Images/stage4.png" };
	char stagesName[4][10] = { "stage1", "stage2", "stage3", "stage4" };
	int stage; 
	// stages 마다 하나씩 필요 -> stages 끝날때 블럭 새로 만들기. setBlock에서 stages 입력받아, 해당 스테이지에만 블럭생성 
	ObjectPtr blocks[10][10];
	// stages 마다의 block 위치
	//bool blockIsExist[10][10]; // Stages 마다 3개 씩 필요하다.. ->blocks만으로 확인할 방법 찾기 

	// select 캐릭터 
	enum characterSelection {DRAGON, BIRD, DOG};
	char charactersPath[3][20] = {"Images/dragon%d.png", "Images/dragon%d.png", "Images/dragon%d.png"};
	int characterI;
	int characterJ;
	int characterS; //status
	int characterN; //name 


	// 블럭 좌표 저장 
	int di[10]; 
	int dj[10];

	// 캐릭터 좌표와 방향 
	// 
	// 
	// 
	//int characterPosition[3]; // x, y, enum direction (LEFT_STAND, RIGHT_STAND) 

	// 화면, 블럭 및 캐릭터 

	enum characterStatus {LEFT_STAND, RIGHT_STAND, LEFT_MOVE, RIGHT_MOVE};
	//direction characterStatus;
	//ObjectPtr characters[3][4]; // 좌서있기, 좌이동, 우서있기, 우이동
	ObjectPtr mainCharacter; 

	ObjectPtr scoreBoard;

public:
	Stair();

	// setter 
	void setStage();
	void setStageNum();
	void setHome(); // 홈화면 캐릭터 입력값 
	void setStartBtn(); // stage1 
	void setHomeBtn();
	void setBlockPosition(); // 블록 좌표 초기화 
	void setStageKey();

	void setCharacter(); 
	void setCharacterNum(int characterName);

	// score
	void setScore();
	void setScoreBoard();
	void setBestScore(int score);
	void addScore(); 
	void setScoreNumbers();
	bool isBestScore();



	// making func
	void makeBlocks(); 
	// moving func

	void moveToLeft(ScenePtr scene);
	void moveBackLeft();
	void moveToRight(ScenePtr scene);
	void moveBackRight();
	bool isOnBlock();
	void dyingAction(); // 좌우로 움직이며 죽는 모션 표현 

	void setGameOver();
	void setGameOverScore();
};
