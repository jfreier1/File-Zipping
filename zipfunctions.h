#ifndef _ZIPFUNCTIONS_H_
#define _ZIPFUNCTIONS_H_

#include "huffmannode.h"
#include <unordered_map>

using std::string;
using std::unordered_map;

class ZipFunctions {
public:
    ZipFunctions();
    void zipFile(string fileToZip, string fileToWriteTo);
    void unZipFile(string fileToUnzip, string fileToWriteTo);
private:
    unordered_map<char,int>* countChars(string fileToCountCharsOf);
    unordered_map<char,string>* getCode(HuffmanNode* huffmanNode);
    void recursivelyGetCode(HuffmanNode* huffmanNode, unordered_map<char,string>* code);
    string byteToStringByte(char byte);
};

#endif /* _ZIPFUNCTIONS_H_ */
