#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <unordered_set>
using namespace std;

const string alphabet  = "abcdefghijklmnopqrstuvwxyz";

void fetchDictionary(vector<string> &dict, string dictName, string::size_type &wordLength) {
    //Fetches dictionary and overwrites the given vector.
    ifstream dictFile(dictName);
    string line;

    if(dictFile.is_open()) {
        while(getline(dictFile, line)) {
            if(line.size() == wordLength) {
                dict.push_back(line);
            }
        }
    }
}

char guessLetter(unordered_set<char> &guessedLetters) {
    //Takes all the guessed letters and compares if the letter has been used before. If it hasn't return the char.
    string input;

    while(true) {
        cout << "Guess a letter: " << endl;
        cin >> input;

        if(input.size() == 1 && guessedLetters.find(input[0]) == guessedLetters.end() && alphabet.find(input[0]) != string::npos) {
            guessedLetters.insert(input[0]);
            return input[0];
        } else {
            cout << "Your input was either invalid or you have already guessed this letter!" << endl;
        }
    }
}

void partitionWords(vector<string> &dict, const int &wordLength, const char letter, string &currentWord, int &guesses) {
    //Iterates through the dictionary and looks for letters with the given char, then it categorizes them based on
    //the position of the given char.
    //Overwrites the current dictionary with the largest word group.

    map<string, vector<string>> wordGroups;
    string wordGroup(wordLength, '-');

    for(string word: dict) {
        wordGroup = string(wordLength, '-');
        for(int i = 0; i < wordLength; i++) {
            if(word[i] == letter) {
                wordGroup[i] = letter;
            } else {
                wordGroup[i] = currentWord[i];
            }
        }

        if(wordGroups.count(wordGroup) == 0) {
            wordGroups[wordGroup] = vector<string>{};
        }

        wordGroups[wordGroup].push_back(word);
    }

    //Finds the largest group
    string largestKey;
    unsigned int largestSize = 0;

    for(auto it = wordGroups.begin(); it != wordGroups.end(); it++) {
        if(largestSize < wordGroups[it->first].size()) {
            largestKey = it->first;
            largestSize = wordGroups[it->first].size();
        }
    }

    if(currentWord == largestKey) {
        guesses--;
    }

    dict = wordGroups[largestKey];
    currentWord = largestKey;
}


int main() {

    char guessedLetter;
    vector<string> dict;
    string::size_type wordLength;
    unordered_set<char> guessedLetters;
    string inputMsg;
    int guesses = 0;
    bool showRemainingWords;
    bool playAgain;
    string currentWord;

    while(true) {
        guesses = 0;
        guessedLetters.clear();
        dict.clear();

        cout << "Welcome to Hangman." << endl;

        while(true) {
            cout << "Please enter a wordlength: " << endl;
            cin >> wordLength;

            fetchDictionary(dict, "dictionary.txt", wordLength);

            if(dict.size() > 0) {
                break;
            }

            cout << "No words with the entered length found! Please try again." << endl;
        }

        currentWord = string(wordLength, '-');

        while(guesses < 1) {
            cout << "How many guesses do you want? " << endl;
            cin >> guesses;
        }


        while (true) {
            cout << "Do you want to see how many words that remain in the word list? [y/n]" << endl;
            cin >> inputMsg;

            if(inputMsg == "y") {
                showRemainingWords = true;
                break;
            } else if (inputMsg == "n") {
                showRemainingWords = false;
                break;
            }
        }


        while(guesses > 0) {
            cout << "You have " << guesses << " guesses left. " << endl;
            cout << "Guessed letters: ";
            for(char c: guessedLetters) {
                cout << c << " ";
            }
            cout << endl << currentWord << endl;

            if(showRemainingWords) {
                cout << "Remaining words: " << dict.size() << endl;
            }

            guessedLetter = guessLetter(guessedLetters);

            partitionWords(dict, wordLength, guessedLetter, currentWord, guesses);

            if(currentWord.find('-') == string::npos) {
                cout << "Congratulations! You won! The correct word was: " << currentWord << endl;
                break;
            } else if(guesses == 0) {
                cout << "You lost! The correct word was: " << dict[0] << endl;
            }
        }

        while(true) {
            cout << "Do you want to play again?? [y/n]" << endl;
            cin >> inputMsg;

            if(inputMsg == "y") {
                playAgain = true;
                break;
            } else if (inputMsg == "n") {
                playAgain = false;
                break;
            }
        }

        if(playAgain == false) {
            break;
        }

    }

    return 0;
}
