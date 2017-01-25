#include "zipfunctions.h"
#include <queue>
#include <fstream>
#include <vector>
#include <cstdint>
#include <iostream>

using namespace std;

ZipFunctions::ZipFunctions() {
}

void ZipFunctions::zipFile(string fileToZip, string fileToWriteTo) {
    unordered_map<char,int>* charOccurances = countChars(fileToZip);
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, ComparingHuffmanNodes> priorityQueue;
    unordered_map<char,string>* code = NULL;
    for (auto it = charOccurances->begin();
            it != charOccurances->end();
            it++) {
        priorityQueue.push(new HuffmanNode(pair<char,int>(it->first, it->second)));
    }
    //after this while loop there will be one node left, the root of the
    //complete huffman tree:
    HuffmanNode* leftChild;
    HuffmanNode* rightChild;
    while(priorityQueue.size() > 1) {
        leftChild = priorityQueue.top();
        priorityQueue.pop();
        rightChild = priorityQueue.top();
        priorityQueue.pop();
        HuffmanNode* newNode = new HuffmanNode(pair<char,int>(NULL,
                leftChild->weight + rightChild->weight));

        newNode->leftChild = leftChild;
        newNode->rightChild = rightChild;
        priorityQueue.push(newNode);
    }
    code = getCode(priorityQueue.top());
    ifstream inputStream(fileToZip);
    char character;
    string buffer = "";
    while(inputStream.get(character)) {
        buffer += code->at(character);
    }

    string toWrite;
    vector<char> byteVector;
    char byteToWrite;
    int bufferLengthToWrite;
    while(buffer.length() > 0) {
        //we want to write 8 bits at a time unless there are less than 8 left
        bufferLengthToWrite = buffer.length() > 8 ? 8 : buffer.length();
        toWrite = buffer.substr(0,bufferLengthToWrite);
        buffer.erase(0,bufferLengthToWrite);
        byteToWrite = 0b00000000;
        for(int i = 0; i<bufferLengthToWrite; i++) {
            if(toWrite[i] == '1') {
                byteToWrite |= (1<<(7-i));
            }
        }
        byteVector.push_back(byteToWrite);
    }
    string codeString = "";
    for (auto it = code->begin();
            it != code->end();
            it++) {
        codeString += it->second + "{" + it->first + "}\n";
    }
    codeString += "end";
    ofstream oFileToWriteCodeTo(fileToWriteTo + "key");
    oFileToWriteCodeTo << codeString;
    ofstream oFileToWriteTo(fileToWriteTo);
    for(int i = 0; i < byteVector.size(); i++) {
        oFileToWriteTo << byteVector[i];
    }
}

void ZipFunctions::unZipFile(string fileToUnzip, string fileToWriteTo) {
    string binaryString;
    string character;
    unordered_map<string,char>* code = new unordered_map<string,char>;

    ifstream keyInputStream(fileToUnzip + "key");
    getline(keyInputStream, binaryString, '{');
    while(binaryString.compare("end") != 0) {
        getline(keyInputStream, character);
        if(character.find('}') == -1) {
            string garbage;
            getline(keyInputStream, garbage);
            //this hopes that the character was intentionally a new line
        }
        code->insert(make_pair(binaryString, character[0]));
        getline(keyInputStream, binaryString, '{');
    }



/*
    getline(keyInputStream, binary, '=');
    while(binary.compare("end") != 0) {
        getline(keyInputStream, character);
        code->insert(make_pair(binary, character[0]));
        getline(keyInputStream, binary, '=');
    }
*/



    ifstream inputStream(fileToUnzip);
    char byte;
    queue<char> coded;
    while(inputStream.get(byte)) {
        string byteAsString = byteToStringByte(byte);
        for(int i = 0; i < 8; i++) {
            coded.push(byteAsString[i]);
        }
    }
    string buffer = "";
    string reconstructed = "";
    while(coded.size() > 0) {
        buffer.push_back(coded.front());
        coded.pop();
        try {
            reconstructed += code->at(buffer);
            buffer = "";
        } catch (std::out_of_range& e) {
            //do nothing
        }
    }
    ofstream oFileToWriteTo(fileToWriteTo);
    oFileToWriteTo << reconstructed;
}

unordered_map<char,int>* ZipFunctions::countChars(
        string fileToCountCharsOf) {

    unordered_map<char,int>* charOccurances = new unordered_map<char,int>;
    ifstream inputStream(fileToCountCharsOf);

    char character;
    while(inputStream.get(character)) { //until you have reached eof...
        try {
            //if the character is already mapped then increment count
            charOccurances->at(character)++;
        } catch (std::out_of_range& e) {
            charOccurances->insert(make_pair(character, 1));
        }
    }
    return charOccurances;
}

unordered_map<char,string>* ZipFunctions::getCode(
        HuffmanNode* huffmanNode) {

    unordered_map<char,string>* code = new unordered_map<char,string>;
    huffmanNode->code = "";
    recursivelyGetCode(huffmanNode, code);
    return code;
}

void ZipFunctions::recursivelyGetCode(HuffmanNode* huffmanNode,
        unordered_map<char,string>* code) {

    if(huffmanNode->isRoot()) {
        code->insert(make_pair(huffmanNode->character, huffmanNode->code));
    } else {
    if(huffmanNode->leftChild != NULL) {
        huffmanNode->leftChild->code = huffmanNode->code + "0";
        recursivelyGetCode(huffmanNode->leftChild, code);
    }

    if(huffmanNode->rightChild != NULL){
        huffmanNode->rightChild->code = huffmanNode->code + "1";
        recursivelyGetCode(huffmanNode->rightChild, code);
    }
  }
}

string ZipFunctions::byteToStringByte(char byte) {
    string answer = "";
    for(int i = 0; i < 8; i++) {
        char toAdd =((byte & (1<<(7-i))) ? '1' : '0');
        answer += toAdd;
    }
    return answer;
}
