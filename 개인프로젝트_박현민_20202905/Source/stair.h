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

	// Scene 변수  
	ScenePtr stages[4];				  // 게임의 스테이지 (3스테이지를 초과 시, 최종 스테이지인 3스테이지 반복)
	ScenePtr home;					  // 홈 화면 
	ScenePtr gameOver;				  // GameOver 화면  
	ScenePtr characterSelect;		  // 캐릭터 선택 화면 
	
	// 메인 캐릭터 및 블럭, Score, Timer, Home, Gameover, 캐릭터 선택 관련
	// 메인 캐릭터 및 블럭 관련 변수 
	ObjectPtr blocks[10][10];		  // 캐릭터가 밟아야 하는 발판 위치 저장한 배열
	ObjectPtr mainCharacter;		  // 게임 내 캐릭터  
	int stage;						  // 캐릭터가 위치한 스테이지 
	int characterI;					  // 캐릭터의 현재 y 좌표 
	int characterJ;					  // 캐릭터의 현재 x 좌표
	int characterS;					  // 캐릭터가 바라보고 있는 방향. (status)
	int characterN;					  // 선택한 캐릭터 종류 (DRAGON, HIPO, DOG) 

	// Score 관련 변수 
	ObjectPtr scoreNumbers[4];		  // score 의 숫자 (0 ~ 999+)를 이미지로 표현하기 위한 Object
	ObjectPtr scoreBoard;			  // Score 배경 
	int bestScore;					  // 최고 기록 
	int score;						  // 현재 기록 

	// Timer 관련 변수 
	ObjectPtr timerBoard;			  // 타이머 배경 
	ObjectPtr timerBars[5];			  // 타이머 모양이 저장된 배열 (배터리 모양의 바) 
	TimerPtr timers[5];				  // Timer가 저장된 배열 (실제 베터리가 줄어드는 것 처럼 보이게 구현하기 위함)
	bool timerIsOff[5];				  // 나간 베터리 확인 용 (배터리 모양의 바가 몇 개 꺼져 있는지)

	// 홈 화면 관련 
	ObjectPtr homeCharacter;		  // 홈 화면에서 현재 선택된 캐릭터 표시 
	ObjectPtr gameToy;				  // 홈, GameOver 화면에서 배경으로 사용 
	ObjectPtr startBtn;				  // 홈, GameOver 화면에서 게임 시작 버튼 	
	ObjectPtr homeBtn;				  // 홈 화면 이동 버튼 
	ObjectPtr characterSelectBtn;	  // 캐릭터 선택화면 이동 버튼  

	// GameOver 관련 
	ObjectPtr deadRing;				  // 사망 시 캐릭터 위에 표시되는 링 

	// 캐릭터 선택 관련 
	ObjectPtr characterSelectBtns[3]; // 캐릭터(DRAGON, HIPO, DOG) 중 선택하는 버튼   
	ObjectPtr selectToy;			  // 캐릭터(DRAGON, HIPO, DOG) 표시하는 배경으로 사용  


	// 기타 변수 
	// 선택 가능한 캐릭터 
	enum characterSelection { DRAGON, HIPO, DOG };
	// 캐릭터가 바라보고 있는 방향(상태)  
	enum characterStatus { LEFT_STAND, RIGHT_STAND, LEFT_MOVE, RIGHT_MOVE };
	// sprintf 용 임시 변수
	char path[20];
	// 사용되는 좌표 
	int di[10];
	int dj[10];
	// 이미지 경로
	char scoresPath[11][15] = { "Images/0.png", "Images/1.png", "Images/2.png", "Images/3.png", "Images/4.png", "Images/5.png", "Images/6.png", "Images/7.png", "Images/8.png", "Images/9.png", "Images/+.png" };
	char stagesPath[4][20] = { "Images/stage1.png", "Images/stage2.png", "Images/stage3.png", "Images/stage4.png" };
	char stagesName[4][10] = { "stage1", "stage2", "stage3", "stage4" };
	char charactersPath[3][20] = { "Images/dragon%d.png", "Images/hipo%d.png", "Images/dog%d.png" };

public:
	// 초기화 (Blocks 좌표, 캐릭터, 최고기록, Home 화면, 게임 startBtn 관련 초기화)
	Stair();
	
	// 메인 캐릭터 및 블럭, Score, Timer, Home, Gameover, 캐릭터 선택 관련
	// 메인 캐릭터 및 블럭 관련 
	void makeBlocks();							// 캐릭터가 밟을 blocks 생성 
	void setStage();							// 게임 스테이지 구성. (블럭, 캐릭터, Score, Timer 생성)
	void setStageKey();							// 스테이지에 키보드 이벤트 콜백 함수 설정
	void setCharacter();						// 스테이지에 캐릭터 생성 후 위치시킴 
	void setBlockPosition();					// 사용되는 좌표 초기화 
	void setStageNum();							// (현재 스테이지 초기화) stage = 0 
	void moveToLeft(ScenePtr scene);			// 캐릭터가 왼쪽을 바라보게 다음 블록으로 이동 
	void moveBackLeft();						// 캐릭터가 다시 왼쪽으로 서있는 모습을 하도록 변경 
	void moveToRight(ScenePtr scene);			// 캐릭터가 오른쪽을 바라보게 다음 블록으로 이동 
	void moveBackRight();						// 캐릭터가 다시 오른쪽으로 서있는 모습을 하도록 변경 
	bool isOnBlock();							// 캐릭터가 블록 위에 착지했는지 검사 
	bool isOnTop();								// 캐릭터가 해당 스테이지의 맨 위 블럭에 있는지 검사 
	bool isFinalStage();						// 캐릭터가 마지막 스 테이지인지 검사

	// Score 관련 
	void setScore();							// (현재 스코어 초기화) score = 0
	void setScoreBoard();						// 스코어 판을 stages 화면에 등록
	void setBestScore(int score);				// 신기록 달성 시, 신기록 저장
	void addScore();							// 현재 스코어++ 후 표시 
	void setScoreNumbers();						// int 스코어를 이미지로 사용하기 위해 변환
	bool isBestScore();							// 현재 스코어가 신기록인지 검사 

	// Timer 관련 
	void setTimers();							// 타이머 생성 및 콜백 등록 
	void setTimerBoard();						// stages 화면에 타이머 등록 

	// 홈 관련 
	void setHome();								// 홈 화면구성
	void setStartBtn();							// 게임 start 버튼 콜백 함수 설정 (stage, Score, Timer 초기화 후 게임 스테이지 구성(setStage())) 
	void setHomeBtn();							// 홈 버튼 콜백 함수 설정  

	// Gameover 관련 
	void setGameOver();							// 게임오버 화면 구성 
	void setGameOverScore();					// 게임오버 화면에 현재 score 표시 

	// 캐릭터 선택 관련 
	void setCharacterNum(int characterName);	// 사용되는 캐릭터 변경  
	void setCharacterSelect();					// 캐릭터 선택 화면 생성 
	void setCharacterSelectBtn();				// 캐릭터 선택하는 화면으로 이동 버튼  
	void setCharacterSelectBtns();				// 각각의 캐릭터 선택 버튼 생성 및 콜백 함수 설정 
};
