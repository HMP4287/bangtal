#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <bangtal>  // 필요한가 ??
#include <cstdlib>
#include <ctime>
#include <Windows.h>
using namespace bangtal;  // using namesapce 선언 위치 ?

class Puzzle 
{
private:
	// 필요 변수.
	ScenePtr scene;
	ObjectPtr board[9];
	ObjectPtr answerBoard[9]; 
	ObjectPtr startBtn;
	TimerPtr timer;

	int hidedIndex;
	float animationTime;
	int mixCount;

public:
	// 필요 함수. 생성자. (소멸자는 생략)
	Puzzle();

	ScenePtr getScene();
	ObjectPtr getBoard(int index);
	ObjectPtr getStartBtn(); 
	TimerPtr getTimer();
	

	int getHidedIndex(); 
	int getClickedIndex(ObjectPtr piece);
	int getMixCount();

	bool checkMixCount();
	void swapPieces(int index); 
	int indexToX(int index);
	int indexToY(int index); 
	bool checkPiece(int index);

	int randomMove();
	void startShuffle(); 
	bool checkEnd();
	void endPuzzle();
	void subtractOneMixCount();
	void startTimer();

};