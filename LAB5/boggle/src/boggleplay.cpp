#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "Boggle.h"
#include "bogglemain.h"
#include "strlib.h"


void manualBoard(Boggle &boggle);
bool checkLetter(string checkedString);
/*
 * Plays one game of Boggle using the given boggle game state object.
 */
void playOneGame(Boggle& boggle) {
    boggle.reset();

    if(yesOrNo("Do you want to generate a random board?")) {
        boggle.shuffleBoard();
    } else {
        manualBoard(boggle);
    }

    std::cout << "Your turn!" << std::endl;

    string guess;

    while(true) {

        showBoard(boggle);

        std::cout << "Your words (" << boggle.countWords() << "): " << boggle.getPlayerWords() << std::endl;
        std::cout << "Your score: " << boggle.getPlayerScore() << std::endl;

        std::cout << "Type a word (or press Enter to end your turn): ";
        std::getline(std::cin, guess);
        clearConsole();

        if(guess.empty()) {
            break;
        }

        guess = toUpperCase(guess);

        if(boggle.validateWord(guess)) {
            std::cout << "You found a new word! \"" << guess << '"' << std::endl;
            boggle.addWord(guess);
        } else if(guess.length() < 4) {
            std::cout << "That word is not long enough!" << std::endl;
        } else if (boggle.playerHasGuessed(guess)) {
            std::cout << "You have already guessed that word." << std::endl;
        } else if (!boggle.wordExist(guess)) {
            std::cout << "That word can't be formed on this board." << std::endl;
        } else {
            std::cout << "That word is not in the dictionary!" << std::endl;
        }

    }




    boggle.findAllWords();
    std::cout << "It's my turn!" << std::endl;
    std::cout << "My words (" << boggle.countComputerWords() << "): " << boggle.getComputerWords() << std::endl;
    std::cout << "My score: " << boggle.getComputerScore() << std::endl;


    if(boggle.getPlayerScore() < boggle.getComputerScore()) {
        std::cout << "Ha ha ha, I destroyed you. Better luck next time, puny human!" << std::endl;
    } else {
        std::cout << "You won!" << std::endl;
    }
}

void showBoard(Boggle& boggle) {
    std::cout << boggle.getBoardString() << std::endl;
}

void manualBoard(Boggle& boggle) {
    std::cout << "Please enter your manual configuration using 16 characters:" << std::endl;
    string answer;
    while(true) {
        std::cin >> answer;

        if(answer.size() == 16 && checkLetter(answer)) {
            boggle.setBoard(answer);
            std::cin.clear();
            std::cin.get();
            break;
        } else {
            std::cout << "Input invalid, make sure your input is 16 characters long and only contains letters! \n Try again:" << std::endl;
        }
    }
}

bool checkLetter(string checkedString) {
    for(char letter: checkedString) {
        if(!std::isalpha(letter)) {
            return false;
        }
    }
    return true;
}

/*
 * Erases all currently visible text from the output console.
 */
void clearConsole() {
#if defined(_WIN32) || defined(_WIN64)
    std::system("CLS");
#else
    // assume POSIX
    std::system("clear");
#endif
}
