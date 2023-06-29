#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <vector>
#include <utility>
#include <unordered_set>
using namespace std;

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";

void findNeighbor(const string &w1, const unordered_set<string> &dict, stack<string> &partialChain,
                  unordered_set<string> &usedWords, vector<string> &copyVector){
    /*
     * Finds the neighbor to the current word, which is the current word with a 1 letter difference.
     */

    string currentWord;
    vector<string> tempVector;

    for(size_t i = 0; i < w1.size(); i++) {
        currentWord = partialChain.top();
        for(char alphaLetter: ALPHABET) {
            currentWord[i] = alphaLetter;
            if(dict.count(currentWord) && !usedWords.count(currentWord)) {
                usedWords.insert(currentWord);
                tempVector.push_back(currentWord);

            }
        }
    }
    copyVector = tempVector;
}

void wordChain(const string &w1, const string &w2, const unordered_set<string> &dict, stack<string> &rStack) {
    /*
     * Generates the most efficient word-chain from w1 to w2 using BFS and sets the reference
     * of rStack to the stack containing the most efficient wordchain.
     */

    unordered_set<string> usedWords;
    queue<stack<string>> stackQueue;
    stack<string> wordStack;
    stack<string> partialChain;
    stack<string> copyStack;
    vector<string> copyVector;


    wordStack.push(w1);
    stackQueue.push(wordStack);
    usedWords.insert(w1);

    while(!stackQueue.empty()) {
        partialChain = stackQueue.front();
        stackQueue.pop();

        if(partialChain.top() == w2) {
            rStack = partialChain;
        } else {
            findNeighbor(w1, dict, partialChain, usedWords, copyVector);
            while (!copyVector.empty()) {
               copyStack = partialChain;
               copyStack.push(copyVector.front());
               copyVector.erase(copyVector.begin());
               stackQueue.push(copyStack);
            }
        }
    }
}

void fetchDictionary(string dictionaryName, unordered_set<string> &dictSet) {
    /*
     * Fetches dictionary with the name dictionaryName to wordSet and sets the value of the fetched wordList to dictSet.
     */
    ifstream infile(dictionaryName);
    string line;

    unordered_set<string> wordSet;

    while(getline(infile, line)) {
        wordSet.insert(line);
    }

    dictSet = wordSet;
}

int main() {
    cout << "Welcome to TDDD86 Word Chain." << endl;
    cout << "If you give me two English words, I will transform the" << endl;
    cout << "first into the second by changing one letter at a time." << endl;
    cout << endl;

    cout << "Please type two words: ";

    unordered_set<string> wordList;
    fetchDictionary("dictionary.txt", wordList);

    cout << wordList.size() << endl;

    cout << "Dict fetched \n";
    cout << endl;

    string w1, w2;
    stack<string> returnStack;

    cout << "Please enter two words of equal length: ";
    cin >> w1 >> w2;

    wordChain(w1,w2, wordList, returnStack);

    if(returnStack.empty()) {
        cout << "No chain found" << endl;
    }

    while(!returnStack.empty()) {
        cout << returnStack.top() << " ";
        returnStack.pop();
    }
    cout << endl;

    return 0;
}
