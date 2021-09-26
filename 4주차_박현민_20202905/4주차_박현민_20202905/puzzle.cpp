#include "Puzzle.h"

Puzzle::Puzzle() {
    scene = Scene::create("Ω√¿€»ƒ", "Images/blankBackgroundLast.png");
    char imgPath[20];
    for (int i = 0; i < 9; i++) {
        sprintf(imgPath, "Images/%d.png", i + 1);
        board[i] = Object::create(imgPath, scene, indexToX(i), indexToY(i));
        answerBoard[i] = board[i];
    }
    startBtn = Object::create("Images/startButton.png", scene, 450, 100); 
    animationTime = 0.01f;
    mixCount = 200;
    timer = Timer::create(animationTime);
}

ScenePtr Puzzle::getScene() {
    return scene;
}

int Puzzle::getHidedIndex() {
    return hidedIndex;
}

int Puzzle::getClickedIndex(ObjectPtr piece) {
    for (int i = 0; i < 9; i++) {
        if (board[i] == piece)
            return i;
    }
    return -1; 
}

void Puzzle::swapPieces(int index) {
    auto temp = board[index];
    board[index] = board[hidedIndex];
    board[index]->locate(scene, indexToX(index), indexToY(index));
    board[hidedIndex] = temp;
    board[hidedIndex]->locate(scene, indexToX(hidedIndex), indexToY(hidedIndex));
    hidedIndex = index;
}

int Puzzle::indexToX(int index) {
    return 322 + 200 * (index % 3);
}

int Puzzle::indexToY(int index) {
    return 449 - 200 * (index / 3);
}

bool Puzzle::checkPiece(int index) {
    return (hidedIndex % 3 > 0 && index == hidedIndex - 1) || (hidedIndex % 3 < 2 && index == hidedIndex + 1) || (hidedIndex / 3 > 0 && index == hidedIndex - 3) || (hidedIndex / 3 < 2 && index == hidedIndex + 3); 
}

int Puzzle::randomMove() {
    int index = rand() % 9;
    while (!checkPiece(index))
        index = rand() % 9;
    return index;
} 

void Puzzle::startShuffle() {
    mixCount = 200;
    timer->set(animationTime);
    timer->start();
    hidedIndex = rand() % 9;
    board[hidedIndex]->hide();
}

bool Puzzle::checkEnd() {
    for (int i = 0; i < 9; i++) {
        if (board[i] != answerBoard[i])
            return false;
    }
    return true;
}

void Puzzle::endPuzzle() {
    board[hidedIndex]->show();
    showMessage("Completed!!");
    startBtn->setImage("Images/startButton.png");
    startBtn->show();
}

ObjectPtr Puzzle::getBoard(int index) {
    return board[index];
}

ObjectPtr Puzzle::getStartBtn() {
    return startBtn;
}

TimerPtr Puzzle::getTimer() {
    return timer;
}

int Puzzle::getMixCount() {
    return mixCount;
}

bool Puzzle::checkMixCount() {
    return mixCount > 0; 
}

void Puzzle::startTimer() {
    timer->set(animationTime);
    timer->start(); 
}

void Puzzle::subtractOneMixCount() {
    mixCount--;
}