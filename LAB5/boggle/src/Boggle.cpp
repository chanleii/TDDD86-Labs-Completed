#include <sstream>
#include "Boggle.h"
#include "random.h"
#include "shuffle.h"
#include "strlib.h"
#include "iostream"

static const int NUM_CUBES = 16;   // the number of cubes in the game
static const int CUBE_SIDES = 6;   // the number of sides on each cube
static string CUBES[NUM_CUBES] = {        // the letters on all 6 sides of every cube
   "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
   "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
   "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
   "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};

void Boggle::shuffleBoard() {

    for(size_t i=0; i<NUM_CUBES; i++) {
        Cube cube;
        for(char cubeChar: CUBES[i]) {
            cube.sides.push_back(cubeChar);
        }
        shuffle(cube.sides);

        gameBoard.set(i/BOARD_SIZE, i%BOARD_SIZE, cube);
    }

    shuffle(gameBoard);


}

void Boggle::setBoard(const string &boardConfig) {
    for(unsigned int i=0; i<boardConfig.size(); i++) {
        Cube cube;
        cube.sides.push_back(boardConfig[i]);

        gameBoard.set(i / BOARD_SIZE, i % BOARD_SIZE, cube);
    }
}

bool Boggle::wordExist(const string &word) {
    for(int row = 0; row < gameBoard.nRows; row++) {
        for(int col = 0; col < gameBoard.nCols; col++) {
            if (checkNeighbours(word, row, col)) {
                return true;
            }
        }
    }


    return false;
}

bool Boggle::checkNeighbours(const string &word, const int &row, const int &col) {

    if(word.length() == 1 && word[0] == gameBoard.get(row, col).getUpFacing()) {
        return true;
    } else if(word[0] != gameBoard.get(row, col).getUpFacing()) {
        return false;
    }


    Cube cube = gameBoard.get(row, col);
    cube.isMarked = true;
    gameBoard.set(row, col, cube);

    for(int i = -1; i < 2; i++) {
        for(int j = -1; j < 2; j++) {
            if((i != 0 || j != 0) && gameBoard.inBounds(row+i, col+j) && ! gameBoard.get(row+i, col+j).isMarked) {

                if (checkNeighbours(word.substr(1), row+i, col+j)) {
                    cube.isMarked = false;
                    gameBoard.set(row, col, cube);
                    return true;
                }
            }
        }
    }

    cube.isMarked = false;
    gameBoard.set(row, col, cube);

    return false;
}

void Boggle::findAllWords() {
    for(int row = 0; row < gameBoard.nRows; row++) {
        for(int col = 0; col < gameBoard.nCols; col++) {
            findAllWords_rec("", row, col);
        }
    }

}

int Boggle::getComputerScore() const {
    return computerScore;
}

string Boggle::getComputerWords() {
    return computerWords.toString();
}

void Boggle::findAllWords_rec(string word, const int &row, const int &col) {

    Cube cube = gameBoard.get(row, col);
    cube.isMarked = true;
    gameBoard.set(row, col, cube);

    word.append(1, cube.getUpFacing());


    if(!lexicon.containsPrefix(word)) {

        cube.isMarked = false;
        gameBoard.set(row, col, cube);
        return;
    } else if(word.length() >= 4 && lexicon.contains(word) && !computerWords.contains(word) && !playerwords.contains(word)) {
        computerWords.add(word);
        computerScore += word.length() - 3;
    }

    for(int i = -1; i < 2; i++) {
        for(int j = -1; j < 2; j++) {
            if((i != 0 || j != 0) && gameBoard.inBounds(row+i, col+j) && !gameBoard.get(row+i, col+j).isMarked) {
                findAllWords_rec(word, row+i, col+j);
            }
        }
    }

    cube.isMarked = false;
    gameBoard.set(row, col, cube);
}

string Boggle::getBoardString() const {
    string boardString;
    for(int i = 0; i < gameBoard.numRows(); i++) {
        for(int j = 0; j < gameBoard.numCols(); j++) {
            boardString += gameBoard.get(i, j).getUpFacing();
        }
        boardString += "\n";
    }
    return boardString;
}

int Boggle::countComputerWords() const {
    return computerWords.size();
}

bool Boggle::validateWord(const string &word) {
    return !playerwords.contains(word) && word.size() >= 4 && wordExist(word) && lexicon.contains(word);
}

string Boggle::getPlayerWords() {
    return playerwords.toString();
}

int Boggle::countWords() const {
    return playerwords.size();
}

int Boggle::getPlayerScore() const {
    return score;
}

void Boggle::addWord(const string &word) {
    score += word.length() - 3;
    playerwords.add(word);
}


bool Boggle::playerHasGuessed(const string &word) const {
    if(playerwords.contains(word)) {
        return true;
    }

    return false;
}

void Boggle::reset() {
    playerwords.clear();
    score = 0;
    computerScore = 0;
    computerWords.clear();
}
