#include <stdio.h>
#include <bangtal>
#include "puzzle.h"

using namespace bangtal;
 
int main() {

    // ���� �ʱ� ���� 
	srand((unsigned int)time(NULL));
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_ROOM_TITLE, false);

	Puzzle gamePuzzle;  // ���� Ŭ������ "��������"(���� ĳ���ͷ� ���ߴ� ����) ��ü ����.  (puzzle.h, puzzle.cpp ���� ����)

    // ������ ���� ���� �ڵ�
    for (int i = 0; i < 9; i++) {
        gamePuzzle.getBoard(i)->setOnMouseCallback([&](auto piece, auto x, auto y, auto action)->bool {
            int index = gamePuzzle.getClickedIndex(piece);
            if (gamePuzzle.checkPiece(index)) {
                gamePuzzle.swapPieces(index);
                if (gamePuzzle.checkEnd())
                    gamePuzzle.endPuzzle();
            }
            return true;
        });
    }

    // ��ư ���� �ڵ� 
    gamePuzzle.getStartBtn()->setOnMouseCallback([&](auto, auto, auto, auto)->bool {
        gamePuzzle.getStartBtn()->hide();
        gamePuzzle.startShuffle();
        return true;
    });

    // Ÿ�̸� ���� �ڵ� 
    gamePuzzle.getTimer()->setOnTimerCallback([&](auto)->bool {
        gamePuzzle.swapPieces(gamePuzzle.randomMove());
        gamePuzzle.subtractOneMixCount();
        if (gamePuzzle.checkMixCount())
            gamePuzzle.startTimer();
        return true;
    });


    startGame(gamePuzzle.getScene());
	return 0;
}