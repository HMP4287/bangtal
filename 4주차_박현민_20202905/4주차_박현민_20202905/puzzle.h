#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <bangtal>  
#include <cstdlib>
#include <ctime>
#include <Windows.h>
using namespace bangtal;

class Puzzle 
{
private:
	ScenePtr scene;
	ObjectPtr board[9];
	ObjectPtr answerBoard[9]; 
	ObjectPtr startBtn;
	TimerPtr timer;

	int hidedIndex;
	float animationTime;
	int mixCount;

public:
	Puzzle();  // 멤버변수 초기화 

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
