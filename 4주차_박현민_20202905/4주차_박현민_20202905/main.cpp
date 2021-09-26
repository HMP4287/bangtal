#include <stdio.h>
#include <bangtal>
#include "puzzle.h"

using namespace bangtal;
 
int main() {

    // 게임 초기 설정 
	srand((unsigned int)time(NULL));
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_ROOM_TITLE, false);

	Puzzle gamePuzzle;  // 퍼즐 클래스로 "게임퍼즐"(게임 캐릭터로 맞추는 퍼즐) 객체 생성.  (puzzle.h, puzzle.cpp 파일 참고)

    // 각각의 퍼즐 관련 코드
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

    // 버튼 관련 코드 
    gamePuzzle.getStartBtn()->setOnMouseCallback([&](auto, auto, auto, auto)->bool {
        gamePuzzle.getStartBtn()->hide();
        gamePuzzle.startShuffle();
        return true;
    });

    // 타이머 관련 코드 
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