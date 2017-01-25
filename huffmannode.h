#ifndef _HUFFMANNODE_H_
#define _HUFFMANNODE_H_

#include <utility>
#include <string>

using std::pair;
using std::string;

class HuffmanNode {
public:
    HuffmanNode(pair<char,int> specs);
    bool isRoot();
    bool operator <(HuffmanNode& other);

    string code;
    char character;
    int weight;
    HuffmanNode* leftChild;
    HuffmanNode* rightChild;
};

class ComparingHuffmanNodes {
public:
    bool operator() (HuffmanNode* leftHuffmanNode,
            HuffmanNode* rightHuffmanNode) const {
        return (leftHuffmanNode->weight > rightHuffmanNode->weight);
    }
};

#endif /* _HUFFMANNODE_H_ */
