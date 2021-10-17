#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <bangtal> 
#include <string>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <time.h>

using namespace bangtal;
using std::string;

class Stair
{
private:

	// Scene ����  
	ScenePtr stages[4];				  // ������ �������� (3���������� �ʰ� ��, ���� ���������� 3�������� �ݺ�)
	ScenePtr home;					  // Ȩ ȭ�� 
	ScenePtr gameOver;				  // GameOver ȭ��  
	ScenePtr characterSelect;		  // ĳ���� ���� ȭ�� 
	
	// ���� ĳ���� �� ��, Score, Timer, Home, Gameover, ĳ���� ���� ����
	// ���� ĳ���� �� �� ���� ���� 
	ObjectPtr blocks[10][10];		  // ĳ���Ͱ� ��ƾ� �ϴ� ���� ��ġ ������ �迭
	ObjectPtr mainCharacter;		  // ���� �� ĳ����  
	int stage;						  // ĳ���Ͱ� ��ġ�� �������� 
	int characterI;					  // ĳ������ ���� y ��ǥ 
	int characterJ;					  // ĳ������ ���� x ��ǥ
	int characterS;					  // ĳ���Ͱ� �ٶ󺸰� �ִ� ����. (status)
	int characterN;					  // ������ ĳ���� ���� (DRAGON, HIPO, DOG) 

	// Score ���� ���� 
	ObjectPtr scoreNumbers[4];		  // score �� ���� (0 ~ 999+)�� �̹����� ǥ���ϱ� ���� Object
	ObjectPtr scoreBoard;			  // Score ��� 
	int bestScore;					  // �ְ� ��� 
	int score;						  // ���� ��� 

	// Timer ���� ���� 
	ObjectPtr timerBoard;			  // Ÿ�̸� ��� 
	ObjectPtr timerBars[5];			  // Ÿ�̸� ����� ����� �迭 (���͸� ����� ��) 
	TimerPtr timers[5];				  // Timer�� ����� �迭 (���� ���͸��� �پ��� �� ó�� ���̰� �����ϱ� ����)
	bool timerIsOff[5];				  // ���� ���͸� Ȯ�� �� (���͸� ����� �ٰ� �� �� ���� �ִ���)

	// Ȩ ȭ�� ���� 
	ObjectPtr homeCharacter;		  // Ȩ ȭ�鿡�� ���� ���õ� ĳ���� ǥ�� 
	ObjectPtr gameToy;				  // Ȩ, GameOver ȭ�鿡�� ������� ��� 
	ObjectPtr startBtn;				  // Ȩ, GameOver ȭ�鿡�� ���� ���� ��ư 	
	ObjectPtr homeBtn;				  // Ȩ ȭ�� �̵� ��ư 
	ObjectPtr characterSelectBtn;	  // ĳ���� ����ȭ�� �̵� ��ư  

	// GameOver ���� 
	ObjectPtr deadRing;				  // ��� �� ĳ���� ���� ǥ�õǴ� �� 

	// ĳ���� ���� ���� 
	ObjectPtr characterSelectBtns[3]; // ĳ����(DRAGON, HIPO, DOG) �� �����ϴ� ��ư   
	ObjectPtr selectToy;			  // ĳ����(DRAGON, HIPO, DOG) ǥ���ϴ� ������� ���  


	// ��Ÿ ���� 
	// ���� ������ ĳ���� 
	enum characterSelection { DRAGON, HIPO, DOG };
	// ĳ���Ͱ� �ٶ󺸰� �ִ� ����(����)  
	enum characterStatus { LEFT_STAND, RIGHT_STAND, LEFT_MOVE, RIGHT_MOVE };
	// sprintf �� �ӽ� ����
	char path[20];
	// ���Ǵ� ��ǥ 
	int di[10];
	int dj[10];
	// �̹��� ���
	char scoresPath[11][15] = { "Images/0.png", "Images/1.png", "Images/2.png", "Images/3.png", "Images/4.png", "Images/5.png", "Images/6.png", "Images/7.png", "Images/8.png", "Images/9.png", "Images/+.png" };
	char stagesPath[4][20] = { "Images/stage1.png", "Images/stage2.png", "Images/stage3.png", "Images/stage4.png" };
	char stagesName[4][10] = { "stage1", "stage2", "stage3", "stage4" };
	char charactersPath[3][20] = { "Images/dragon%d.png", "Images/hipo%d.png", "Images/dog%d.png" };

public:
	// �ʱ�ȭ (Blocks ��ǥ, ĳ����, �ְ���, Home ȭ��, ���� startBtn ���� �ʱ�ȭ)
	Stair();
	
	// ���� ĳ���� �� ��, Score, Timer, Home, Gameover, ĳ���� ���� ����
	// ���� ĳ���� �� �� ���� 
	void makeBlocks();							// ĳ���Ͱ� ���� blocks ���� 
	void setStage();							// ���� �������� ����. (��, ĳ����, Score, Timer ����)
	void setStageKey();							// ���������� Ű���� �̺�Ʈ �ݹ� �Լ� ����
	void setCharacter();						// ���������� ĳ���� ���� �� ��ġ��Ŵ 
	void setBlockPosition();					// ���Ǵ� ��ǥ �ʱ�ȭ 
	void setStageNum();							// (���� �������� �ʱ�ȭ) stage = 0 
	void moveToLeft(ScenePtr scene);			// ĳ���Ͱ� ������ �ٶ󺸰� ���� ������� �̵� 
	void moveBackLeft();						// ĳ���Ͱ� �ٽ� �������� ���ִ� ����� �ϵ��� ���� 
	void moveToRight(ScenePtr scene);			// ĳ���Ͱ� �������� �ٶ󺸰� ���� ������� �̵� 
	void moveBackRight();						// ĳ���Ͱ� �ٽ� ���������� ���ִ� ����� �ϵ��� ���� 
	bool isOnBlock();							// ĳ���Ͱ� ��� ���� �����ߴ��� �˻� 
	bool isOnTop();								// ĳ���Ͱ� �ش� ���������� �� �� ���� �ִ��� �˻� 
	bool isFinalStage();						// ĳ���Ͱ� ������ �� ���������� �˻�

	// Score ���� 
	void setScore();							// (���� ���ھ� �ʱ�ȭ) score = 0
	void setScoreBoard();						// ���ھ� ���� stages ȭ�鿡 ���
	void setBestScore(int score);				// �ű�� �޼� ��, �ű�� ����
	void addScore();							// ���� ���ھ�++ �� ǥ�� 
	void setScoreNumbers();						// int ���ھ �̹����� ����ϱ� ���� ��ȯ
	bool isBestScore();							// ���� ���ھ �ű������ �˻� 

	// Timer ���� 
	void setTimers();							// Ÿ�̸� ���� �� �ݹ� ��� 
	void setTimerBoard();						// stages ȭ�鿡 Ÿ�̸� ��� 

	// Ȩ ���� 
	void setHome();								// Ȩ ȭ�鱸��
	void setStartBtn();							// ���� start ��ư �ݹ� �Լ� ���� (stage, Score, Timer �ʱ�ȭ �� ���� �������� ����(setStage())) 
	void setHomeBtn();							// Ȩ ��ư �ݹ� �Լ� ����  

	// Gameover ���� 
	void setGameOver();							// ���ӿ��� ȭ�� ���� 
	void setGameOverScore();					// ���ӿ��� ȭ�鿡 ���� score ǥ�� 

	// ĳ���� ���� ���� 
	void setCharacterNum(int characterName);	// ���Ǵ� ĳ���� ����  
	void setCharacterSelect();					// ĳ���� ���� ȭ�� ���� 
	void setCharacterSelectBtn();				// ĳ���� �����ϴ� ȭ������ �̵� ��ư  
	void setCharacterSelectBtns();				// ������ ĳ���� ���� ��ư ���� �� �ݹ� �Լ� ���� 
};
