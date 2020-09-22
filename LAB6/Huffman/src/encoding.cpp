#include "encoding.h"
#include <queue>

map<int, int> buildFrequencyTable(istream& input) {
    map<int, int> freqTable;

    int character;
    do {

        character = input.get();

        if(character == -1) {
            character = PSEUDO_EOF;
        }

        freqTable[character]++;

    } while (character != PSEUDO_EOF);
    return freqTable;
}

HuffmanNode* buildEncodingTree(const map<int, int> &freqTable) {
    priority_queue<HuffmanNode> queue;

    for(auto item: freqTable) {
        queue.push(HuffmanNode(item.first, item.second));
    }

    while(queue.size() > 1) {
        HuffmanNode first = queue.top();
        queue.pop();

        HuffmanNode second = queue.top();
        queue.pop();


        queue.push(HuffmanNode(NOT_A_CHAR, first.count+second.count, new HuffmanNode(first), new HuffmanNode(second)));

    }


    return new HuffmanNode(queue.top());
}

void traverseTree(string encoding, HuffmanNode* encodingTree, map<int, string> &encMap) {
    if(encodingTree == nullptr) {
        return;
    } else if(encodingTree->isLeaf()) {
        encMap.insert(pair<int, string>(encodingTree->character, encoding));
    }

    traverseTree(encoding+"0", encodingTree->zero, encMap);
    traverseTree(encoding+"1", encodingTree->one, encMap);

}

map<int, string> buildEncodingMap(HuffmanNode* encodingTree) {
    map<int, string> encodingMap;
    traverseTree("", encodingTree, encodingMap);
    return encodingMap;
}

void encodeData(istream& input, const map<int, string> &encodingMap, obitstream& output) {
    int inputStream;
    string inputCode;
    do {
        inputStream = input.get();


        if(inputStream == -1) {
            inputCode = encodingMap.at(PSEUDO_EOF);
        } else {
            inputCode = encodingMap.at(inputStream);
        }

        for(size_t i = 0; i < inputCode.size(); i++) {
            output.writeBit(inputCode[i] == '1' ? 1 : 0);
        }

    } while(inputStream != -1);
}

void decodeData(ibitstream& input, HuffmanNode* encodingTree, ostream& output) {
    HuffmanNode* root = encodingTree;
    HuffmanNode* current = encodingTree;

    while(true) {
        int bit = input.readBit();

        if(bit == 0) {
            current = current->zero;
        } else {
            current = current->one;
        }


        if(current->isLeaf()) {
            if(current->character == PSEUDO_EOF) {
                break;
            }
            output.put(current->character);
            current = root;
        }
    }
}

void compress(istream& input, obitstream& output) {
    map<int, int> freqTable = buildFrequencyTable(input);
    HuffmanNode* encodingTree = buildEncodingTree(freqTable);
    map<int, string> encodingMap = buildEncodingMap(encodingTree);

    output << '{';
    for(map<int, int>::iterator it = freqTable.begin(); it != freqTable.end(); it++) {
        output << it->first << ':' << it->second;


        map<int, int>::iterator tempIterator = it;
        tempIterator++;
        if(tempIterator != freqTable.end()) {
            output << ", ";
        }
    }
    output << '}';

    input.clear();
    input.seekg(0, input.beg);
    encodeData(input, encodingMap, output);

    freeTree(encodingTree);

}

map<int, int> fetchHeader(ibitstream& input) {
    map<int, int> freqTable;
    string first, second;
    input.get();
    char temp;

    while (true) {

        while (true) {
            temp = input.get();
            if (temp == ':') break;

            if (temp == '}') return freqTable;
            first.push_back(temp);
        }

        while (true) {

            temp = input.get();
            if (temp == ' ' || temp == '}') break;
            second.push_back(temp);

        }

        freqTable[stoi(first)] = stoi(second);

        if(temp == '}')
            return freqTable;

        first.clear();
        second.clear();


    }
}

void decompress(ibitstream& input, ostream& output) {
    map<int, int> header = fetchHeader(input);
    HuffmanNode* tree = buildEncodingTree(header);
    decodeData(input, tree, output);

    freeTree(tree);
}

void freeTree(HuffmanNode* node) {
    if(node == nullptr) {
        return;
    }

    if(node->isLeaf()) {
        delete node;
    } else {
        freeTree(node->zero);
        freeTree(node->one);

        delete node;
    }


}
