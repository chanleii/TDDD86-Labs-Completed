#ifndef _boggle_h
#define _boggle_h

#include <iostream>
#include <string>
#include <vector>
#include <grid.h>
#include <lexicon.h>
#include <set>


using namespace std;

class Boggle {
public:
    const string DICTIONARY_FILE = "EnglishWords.dat";
    const int MIN_WORD_LENGTH = 4;
    const int BOARD_SIZE = 4;


    // Shuffles all cubes and places them on the board.)
    void shuffleBoard();
    // Returns the board as a string
    string getBoardString() const;
    //Sets the board config
    void setBoard(const string &boardConfig);
    //Checks if a word meets the requirements for a valid word.
    bool validateWord(const string &word);
    //Adds word to the player word list.
    void addWord(const string &word);
    //Returns all words discovered by the player
    string getPlayerWords();
    //Returns the player's score
    int getPlayerScore() const;
    //Returns the computer's score
    int getComputerScore() const;
    //Returns the number of words discovered by player
    int countWords() const;
    //Returns the number of words discovered by computer
    int countComputerWords() const;
    //Returns all words discovered by computer.
    string getComputerWords();
    //Checks if a particular word exists on the board.
    bool wordExist(const string &word);
    //Helper function for wordExist
    bool checkNeighbours(const string &word, const int &row, const int &col);
    //Finds all words on the current board not already discovered by the player.
    void findAllWords();
    //helper function for findAllWords()
    void findAllWords_rec(const string word, const int &row, const int &col);
    //Checks if the player has guessed a particular word.
    bool playerHasGuessed(const string &word) const;
    //Resets the board.
    void reset();

private:
    //List of player and computer words.
    Set<string> playerwords;
    Set<string> computerWords;
    //Player score
    int score = 0;
    //Computer score
    int computerScore = 0;

    const Lexicon lexicon = Lexicon(DICTIONARY_FILE);

    //Cube representation
    struct Cube {
        vector<char> sides;

        bool isMarked = false;

        char getUpFacing() const {
            return sides[0];
        }
    };

    Grid<Cube> gameBoard = Grid<Cube>(BOARD_SIZE, BOARD_SIZE);

};

#endif
